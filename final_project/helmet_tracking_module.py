import cv2
import torch
from deep_sort_realtime.deepsort_tracker import DeepSort

class HelmetTracker:
    def __init__(self, model_path='best.pt', conf_thresh=0.4, max_age=30):
        # YOLOv5 커스텀 모델 로드
        self.model = torch.hub.load('ultralytics/yolov5', 'custom', path=model_path)
        self.model.conf = conf_thresh

        # DeepSORT 초기화
        self.tracker = DeepSort(max_age=max_age)

        # 트래킹 ID와 헬멧 착용 상태 매핑
        self.id_has_helmet = {}

    def compute_iou(self, box1, box2):
        xA = max(box1[0], box2[0])
        yA = max(box1[1], box2[1])
        xB = min(box1[2], box2[2])
        yB = min(box1[3], box2[3])
        inter_w = max(0, xB - xA)
        inter_h = max(0, yB - yA)
        inter_area = inter_w * inter_h
        area1 = (box1[2] - box1[0]) * (box1[3] - box1[1])
        area2 = (box2[2] - box2[0]) * (box2[3] - box2[1])
        union = area1 + area2 - inter_area
        return inter_area / union if union != 0 else 0

    def process_frame(self, frame):
        results = self.model(frame)
        detections = results.xyxy[0].cpu().numpy()

        person_dets = []
        helmet_boxes = []
        no_helmet_boxes = []

        for *xyxy, conf, cls in detections:
            x1, y1, x2, y2 = map(int, xyxy)
            cls = int(cls)
            box = [x1, y1, x2 - x1, y2 - y1]

            if cls == 2:  # person
                person_dets.append((box, conf, 'person'))
            elif cls == 0:  # helmet
                helmet_boxes.append([x1, y1, x2, y2])
            elif cls == 1:  # no-helmet
                no_helmet_boxes.append([x1, y1, x2, y2])

        tracks = self.tracker.update_tracks(person_dets, frame=frame)

        for track in tracks:
            if not track.is_confirmed():
                continue

            x1, y1, x2, y2 = map(int, track.to_ltrb())
            track_id = track.track_id
            head_box = [x1, y1, x2, y1 + int((y2 - y1) * 0.3)]

            has_helmet = any(self.compute_iou(head_box, helmet) > 0.3 for helmet in helmet_boxes)
            self.id_has_helmet[track_id] = has_helmet

            color = (0, 255, 0) if has_helmet else (0, 0, 255)
            status = "Helmet" if has_helmet else "No Helmet"

            cv2.rectangle(frame, (x1, y1), (x2, y2), color, 2)
            cv2.putText(frame, f"ID:{track_id} {status}", (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)

        return frame

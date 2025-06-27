import cv2
import torch
from deep_sort_realtime.deepsort_tracker import DeepSort
import pandas as pd

# YOLOv5 커스텀 모델 로드 (클래스: 0=helmet, 1=no-helmet, 2=person)
model = torch.hub.load('ultralytics/yolov5', 'custom', path='/home/lws/kulws2025/kubig2025/final_project/yolov5/runs/train/helmet_detect/weights/best.pt')
model.conf = 0.4

# DeepSORT 초기화
tracker = DeepSort(max_age=30)

# 트래킹 ID와 헬멧 착용 상태 매핑
id_has_helmet = {}

# 비디오 열기
cap = cv2.VideoCapture(0)  # 또는 동영상 경로

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    # YOLO 추론
    results = model(frame)
    detections = results.xyxy[0].cpu().numpy()  # [x1, y1, x2, y2, conf, class]

    person_dets = []
    helmet_boxes = []
    no_helmet_boxes = []

    for *xyxy, conf, cls in detections:
        x1, y1, x2, y2 = map(int, xyxy)
        cls = int(cls)
        box = [x1, y1, x2 - x1, y2 - y1]  # x, y, w, h 형식

        if cls == 2:
            person_dets.append((box, conf, 'person'))
        elif cls == 0:
            helmet_boxes.append([x1, y1, x2, y2])
        elif cls == 1:
            no_helmet_boxes.append([x1, y1, x2, y2])

    # 트래커 업데이트
    tracks = tracker.update_tracks(person_dets, frame=frame)

    # IOU 기반 헬멧 여부 판단 함수
    def compute_iou(box1, box2):
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

    # 각 트랙별로 상태 업데이트 및 시각화
    for track in tracks:
        if not track.is_confirmed():
            continue

        x1, y1, x2, y2 = map(int, track.to_ltrb())
        track_id = track.track_id

        # 머리 영역 기준 (상단 30%)
        head_box = [x1, y1, x2, y1 + int((y2 - y1) * 0.3)]

        # IOU로 헬멧 착용 여부 판단
        has_helmet = any(compute_iou(head_box, helmet) > 0.3 for helmet in helmet_boxes)
        id_has_helmet[track_id] = has_helmet

        # 박스 색상 설정
        color = (0, 255, 0) if has_helmet else (0, 0, 255)  # 초록 or 빨강

        # 시각화
        cv2.rectangle(frame, (x1, y1), (x2, y2), color, 2)
        status = "Helmet" if has_helmet else "No Helmet"
        cv2.putText(frame, f"ID:{track_id} {status}", (x1, y1 - 10),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)

    # 결과 출력
    cv2.imshow("Helmet Detection", frame)
    if cv2.waitKey(1) == 27:
        break

cap.release()
cv2.destroyAllWindows()

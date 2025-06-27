from helmet_tracking_module import HelmetTracker
import cv2

tracker = HelmetTracker(model_path='best.pt')

cap = cv2.VideoCapture(0)
while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    processed = tracker.process_frame(frame)
    cv2.imshow("Helmet Detection", processed)

    if cv2.waitKey(1) == 27:
        break

cap.release()
cv2.destroyAllWindows()

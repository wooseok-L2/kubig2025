import os
import threading
import time
from typing import Optional, Tuple
from urllib.parse import urlparse

import cv2
import numpy as np
import requests


class Esp32CamViewer:
    """ESP32-CAM 스트림을 OpenCV로 표시하는 클래스"""

    def __init__(self, ip_address: str, port: int = 80):
        """
        ESP32-CAM 뷰어 초기화

        Args:
            ip_address: ESP32-CAM의 IP 주소
            port: 웹서버 포트 (기본값: 80)
        """
        self.ipAddress = ip_address
        self.port = port
        self.streamUrl = f"http://{ip_address}:{port}/stream"
        self.homeUrl = f"http://{ip_address}:{port}/"
        self.isRunning = False
        self.currentFrame: Optional[np.ndarray] = None
        self.frameCount = 0
        self.startTime = time.time()
        self.fps = 0.0

    def checkConnection(self) -> bool:
        """
        ESP32-CAM 연결 상태 확인

        Returns:
            연결 가능 여부
        """
        try:
            response = requests.get(self.homeUrl, timeout=5)
            if response.status_code == 200:
                print(f"Successfully connected to ESP32-CAM at {self.ipAddress}")
                return True
            else:
                print(f"Connection failed with status code: {response.status_code}")
                return False
        except requests.exceptions.RequestException as e:
            print(f"Connection error: {e}")
            return False

    def parseStreamFrame(
        self, stream_response: requests.Response
    ) -> Optional[np.ndarray]:
        """
        MJPEG 스트림에서 프레임 파싱

        Args:
            stream_response: 스트림 응답 객체

        Returns:
            파싱된 프레임 또는 None
        """
        try:
            # 스트림 데이터를 청크 단위로 읽기
            boundary = b"--frame"
            data = b""

            for chunk in stream_response.iter_content(chunk_size=1024):
                if not chunk:
                    break

                data += chunk

                # 프레임 경계 찾기
                while True:
                    start = data.find(boundary)
                    if start == -1:
                        break

                    # 다음 프레임 경계 찾기
                    next_start = data.find(boundary, start + len(boundary))
                    if next_start == -1:
                        break

                    # 프레임 데이터 추출
                    frame_data = data[start:next_start]
                    data = data[next_start:]

                    # JPEG 헤더 찾기
                    jpeg_start = frame_data.find(b"\xff\xd8")
                    if jpeg_start == -1:
                        continue

                    # JPEG 데이터 추출
                    jpeg_data = frame_data[jpeg_start:]

                    # OpenCV로 디코딩
                    frame = cv2.imdecode(
                        np.frombuffer(jpeg_data, np.uint8), cv2.IMREAD_COLOR
                    )
                    if frame is not None:
                        return frame

        except Exception as e:
            print(f"Error parsing frame: {e}")
            return None

    def streamReader(self) -> None:
        """스트림 읽기 스레드"""
        try:
            with requests.get(self.streamUrl, stream=True, timeout=10) as response:
                if response.status_code != 200:
                    print(f"Stream request failed with status: {response.status_code}")
                    return

                print("Stream started successfully")

                # 스트림 데이터 처리
                boundary = b"--frame"
                data = b""

                for chunk in response.iter_content(chunk_size=1024):
                    if not self.isRunning:
                        break

                    if not chunk:
                        continue

                    data += chunk

                    # 프레임 경계 찾기
                    while True:
                        start = data.find(boundary)
                        if start == -1:
                            break

                        # 다음 프레임 경계 찾기
                        next_start = data.find(boundary, start + len(boundary))
                        if next_start == -1:
                            break

                        # 프레임 데이터 추출
                        frame_data = data[start:next_start]
                        data = data[next_start:]

                        # JPEG 헤더 찾기
                        jpeg_start = frame_data.find(b"\xff\xd8")
                        if jpeg_start == -1:
                            continue

                        # JPEG 데이터 추출
                        jpeg_data = frame_data[jpeg_start:]

                        # OpenCV로 디코딩
                        frame = cv2.imdecode(
                            np.frombuffer(jpeg_data, np.uint8), cv2.IMREAD_COLOR
                        )
                        if frame is not None:
                            self.currentFrame = frame
                            self.frameCount += 1

                            # FPS 계산
                            currentTime = time.time()
                            elapsed = currentTime - self.startTime
                            if elapsed >= 1.0:
                                self.fps = self.frameCount / elapsed
                                self.frameCount = 0
                                self.startTime = currentTime

        except Exception as e:
            print(f"Stream reader error: {e}")

    def addInfoToFrame(self, frame: np.ndarray) -> None:
        """
        프레임에 정보 텍스트 추가

        Args:
            frame: OpenCV 프레임
        """
        height, width = frame.shape[:2]

        # 배경 사각형 (반투명)
        overlay = frame.copy()
        cv2.rectangle(overlay, (10, 10), (350, 80), (0, 0, 0), -1)
        cv2.addWeighted(overlay, 0.7, frame, 0.3, 0, frame)

        # 텍스트 추가
        cv2.putText(
            frame,
            f"ESP32-CAM Stream",
            (15, 30),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.7,
            (0, 255, 0),
            2,
        )
        cv2.putText(
            frame,
            f"IP: {self.ipAddress} | FPS: {self.fps:.1f}",
            (15, 50),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.5,
            (255, 255, 255),
            1,
        )
        cv2.putText(
            frame,
            f"Size: {width}x{height} | Press 'q' to quit",
            (15, 70),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.4,
            (255, 255, 255),
            1,
        )

    def saveScreenshot(self, frame: np.ndarray) -> None:
        """
        스크린샷 저장

        Args:
            frame: 저장할 프레임
        """
        timestamp = time.strftime("%Y%m%d_%H%M%S")
        screenshotDir = "/home/aa/kuBig2025/platformio/screenshots"
        filename = f"{screenshotDir}/esp32cam_{timestamp}.jpg"

        try:
            os.makedirs(screenshotDir, exist_ok=True)
            cv2.imwrite(filename, frame)
            print(f"Screenshot saved: {filename}")
        except Exception as e:
            print(f"Error saving screenshot: {e}")

    def startViewing(self) -> None:
        """스트림 뷰잉 시작"""
        if not self.checkConnection():
            print("Cannot connect to ESP32-CAM. Please check:")
            print(f"1. ESP32-CAM is running at {self.ipAddress}")
            print("2. You are on the same network")
            print("3. Firewall settings")
            return

        self.isRunning = True
        windowName = "ESP32-CAM Live Stream"
        cv2.namedWindow(windowName, cv2.WINDOW_AUTOSIZE)

        # 스트림 읽기 스레드 시작
        streamThread = threading.Thread(target=self.streamReader)
        streamThread.daemon = True
        streamThread.start()

        print("Stream viewer started")
        print("Controls:")
        print("  q: Quit")
        print("  s: Save screenshot")
        print("  f: Toggle fullscreen")
        print("  r: Reset FPS counter")

        isFullscreen = False

        try:
            while self.isRunning:
                if self.currentFrame is not None:
                    frame = self.currentFrame.copy()

                    # 정보 표시
                    self.addInfoToFrame(frame)

                    # 화면에 표시
                    cv2.imshow(windowName, frame)
                else:
                    # 연결 대기 중 표시
                    waitingFrame = np.zeros((240, 320, 3), dtype=np.uint8)
                    cv2.putText(
                        waitingFrame,
                        "Waiting for stream...",
                        (50, 120),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        0.6,
                        (255, 255, 255),
                        2,
                    )
                    cv2.imshow(windowName, waitingFrame)

                # 키보드 입력 처리
                key = cv2.waitKey(30) & 0xFF
                if key == ord("q"):
                    break
                elif key == ord("s") and self.currentFrame is not None:
                    self.saveScreenshot(self.currentFrame)
                elif key == ord("f"):
                    if isFullscreen:
                        cv2.setWindowProperty(
                            windowName, cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_NORMAL
                        )
                        isFullscreen = False
                    else:
                        cv2.setWindowProperty(
                            windowName, cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN
                        )
                        isFullscreen = True
                elif key == ord("r"):
                    self.frameCount = 0
                    self.startTime = time.time()
                    print("FPS counter reset")

        except KeyboardInterrupt:
            print("\nStopping stream...")
        finally:
            self.cleanup()

    def cleanup(self) -> None:
        """리소스 정리"""
        self.isRunning = False
        cv2.destroyAllWindows()
        print("Cleanup completed")


def main():
    """메인 함수"""
    # ESP32-CAM IP 주소 설정 (작동하는 IP 주소 사용)
    ESP32_CAM_IP = "192.168.0.103"

    print("ESP32-CAM OpenCV Viewer")
    print("======================")
    print(f"Target IP: {ESP32_CAM_IP}")
    print(f"Stream URL: http://{ESP32_CAM_IP}/stream")
    print(f"Home URL: http://{ESP32_CAM_IP}/")
    print()

    viewer = Esp32CamViewer(ESP32_CAM_IP)
    viewer.startViewing()


if __name__ == "__main__":
    main()
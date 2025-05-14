import threading
import time


def task(name, duration):
    print(f"쓰레드 {name} 시작")
    time.sleep(duration)
    print(f"쓰레드 {name} {duration}초 후 완료")


def main():
    # task("first", 5)  # 동기화코드 sync code
    # task("first", 5)
    threads = []
    for i in range(4):
        t = threading.Thread(target=task, args=(f"T{i+1}", 5 + i))
        threads.append(t)
        t.start()

    # threads[0].join()
    # print("main 은 언제 실행될까요??")
    # threads[1].join()
    # print("두번째 쓰레드가 끝났네요!!")
    for t in threads:
        t.join()
    print("main 은 언제 실행될까요??")


if __name__ == "__main__":
    main()
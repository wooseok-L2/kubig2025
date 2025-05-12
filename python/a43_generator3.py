def test():
    print("test A")
    yield 1
    print("test B")
    yield 2
    print("test C")
    yield 3


def main():
    print("main A")
    output = test()  # return object 만들고 실행은 따로

    print("main B")
    a = next(output)  # generator 첫 시퀴스 실행
    print(a)

    a = next(output)  # generator 두번째 시퀴스 실행
    print(a)

    a = next(output)  # generator 세번째 시퀴스 실행
    print(a)

    try:
        a = next(output)  # generator 두번째 시퀴스 실행
        print(a)
    except StopIteration:
        print("Stop Iteration Error!")

    print("main C")


if __name__ == "__main__":
    main()
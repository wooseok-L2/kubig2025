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
    for i in output:
        print(i)
    print("main C")


if __name__ == "__main__":
    main()
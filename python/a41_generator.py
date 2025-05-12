def test():
    print("test 함수가 호출되었씁니다.")
    yield "test"


def main():
    print("A")
    test()  # return object 만들고 실행은 따로

    print("B")
    test()
    print(test())


if __name__ == "__main__":
    main()
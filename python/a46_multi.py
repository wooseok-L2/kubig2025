class MinusError(Exception):
    def __init__(self, e):
        super().__init__()
        self.args = [e]  # type: ignore


def main():
    li = list(range(0, 101, 5))
    while True:
        try:
            input_int = int(input("정수 입력 (1 ~21 까지) 0->break: "))
            if not input_int:
                break
            if input_int < 0:
                raise MinusError("마이너스 에러")
            print(f"이 리스트의 {input_int-1} 요소는 {li[input_int-1]} 입니다.")
        except ValueError as e:
            print(e)
            print("정수만 입력하세요.")
        except IndexError as e:
            print(e)
            print("0~21 까지만 입력 하세요.")
        except KeyboardInterrupt:
            print("키보드로 멈추었네요!!")
            break
        except MinusError as e:
            #print(e)
            print(f"음수입니다.{e}!!")


if __name__ == "__main__":
    main()
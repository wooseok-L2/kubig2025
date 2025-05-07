# 섭씨->화씨 변환 프로그램 input -> casting -> 연산 -> 출력
def main():
    bo = True
    degree = input("썹씨 온도를 넣어 주세요: ")
    for i in degree.split('.'):
        if not i.isdigit():
            bo = False
    if bo:
        print(f"썹씨 온도 {degree} 의 화씨 온도는 {float(degree)*1.8+32:.2f} 입니다.")
    else:
        print("썹씨 온도가 숫자가 아닙니다.")

if __name__ == "__main__":
    main()
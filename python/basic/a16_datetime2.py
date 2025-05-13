# if elif else 사용해서 현재 시각 오전 오후 표시
# 계절을 표시 하는 프로그램
# datetime 모듈 활용
# input 받아서 나타나게(시간,월) -> "now"-> now() 함수를 불러와서 표시.
import datetime


def main():
    user_input = input("시간과 월을 넣어 주세요 (now) 현재 시간-> 시간, 월: ")
    hour = 0
    month = 0
    if user_input == "now":
        ptime = datetime.datetime.now()
        hour = int(ptime.hour)
        month = int(ptime.month)
    else:
        hour, month = user_input.split(",")
        hour = int(hour.strip())
        month = int(month.strip())

    if hour < 12:
        period = "오전"
    elif 12 <= hour < 24:
        period = "오후"
    else:
        print("시간을 다시 입력해주세요")

    if 3 <= month <= 5:
        season = "봄"
    elif month <= 8:
        season = "여름"
    elif month <=11:
        season = "가을"
    elif month == 12 or month <= 2:
        season = "겨울"
    else:
        print("월을 다시 입력해주세요")

    print(f"현재 오전/오후 : {period} | 계절 : {season} 입니다.")

if __name__ == "__main__":
    main()
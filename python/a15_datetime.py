import datetime

import test_package


class Myclass:
    def __str__(self):
        return "test My class"

# 1. PATH PYTHONPATH 에 있는 ~.py 파일들 대상 불러온다.
# 2. package 가 임포트
# 3. .so 파일을 임포트 (dynamic loading) <- C 모듈 만들기(Cpython) -> GIL 우회
#     .(pyi(stub) .so) --> github. -> 실행속도가 빠르다. || 병렬처리.
#     GIL global interpreter lock -> PVM
def main():
    ptime = datetime.datetime.now()
    print(ptime) # __str__ 오버로딩이 되어서 나온다.
    
    myclass =Myclass()
    print(myclass)
    
    print(ptime.month)
    print(f"{ptime.year} 년 {ptime.month} 월 {ptime.day} 일")

if __name__ == "__main__":
    main()
def print_n_times1(value: str, n: int=2):
    for _ in range(n):
        print(value)
        
def print_n_times2(a, b, c, *value: str, n: int=2):   # 가변인자는 디폴트 앞에 위치
    print(a, b, c)
    for _ in range(n):
        print(value)

def print_n_times3(a, b, c, n=2):   
    for _ in range(n):
        print(a, b, c)


def main():
    print_n_times1("hello") # default n = 2
    print_n_times1("hello!!!", n=3)
    print_n_times1("hello!!!", 3)
    
    print_n_times2(12, 13, 45, "abc", "def")
    # print_n_times2(12, 13, 45, "abc", "def", 5)  # error occur
    print_n_times2(12, 13, 45, "abc", "def", n=5)  # 가변매게변수가 있으면 순서 못바꿈
    print_n_times3(b=12, a=13, c=45)  
    # 함수인자 순서: positional argUment!, variable length argument, default argument



if __name__ == "__main__":
    main()
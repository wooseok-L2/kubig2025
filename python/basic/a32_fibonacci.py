cnt = 0

def fibonacci(n):
    global cnt  # 전역 변수로 선언
    cnt += 1
    if n == 1:
        return 1
    elif n == 2:
        return 1
    else:
        return fibonacci(n-1) + fibonacci(n-2)
    
    
def main():
    print(fibonacci(10))
    print(f"fibonacci count {cnt}")
    

if __name__ == "__main__":
    main()
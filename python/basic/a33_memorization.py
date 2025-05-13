cnt = 0
dictionary = {1:1, 2:1}

def fibonacci(n):
    global cnt  # 전역 변수로 선언
    cnt += 1
    # if n == 1:
    #     return 1
    # elif n == 2:
    #     return 1
    if n in dictionary:
        return dictionary[n]
    else:
        output = fibonacci(n-1) + fibonacci(n-2)
        dictionary[n] = output
        return output
    
    
def main():
    print(fibonacci(10))
    print(f"fibonacci count {cnt}")
    

if __name__ == "__main__":
    main()
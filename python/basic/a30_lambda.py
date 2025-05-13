def call_n_times(func, n):
    for _ in range(n):
        func()
        
def print_hello():
    #static
    if not hasattr(print_hello, "i"):
        print_hello.i = 0
    print(f"hello {print_hello.i}")
    print_hello.i += 1
    
def power(x):
    return x**2

def under_3(x):
    return x < 3

def under_50(x):
    return x < 50


def main():
    temp_func = print_hello
    call_n_times(temp_func, 10) #use func like object, obviously it is object
    
    lambda_func1 = power
    lambda_func2 = lambda x : x**2
    
    print(lambda_func1(5))
    print(lambda_func2(5))
    
    lambda_under1 = under_3
    lambda_under2 = lambda x: x < 3
    
    print(lambda_under1(2))
    print(lambda_under2(2))
    
    # map 
    li = [x for x in range(100)]
    #output = map(power, li)
    output = map(lambda x: x**2, li)
    print(list(output))
    
    #filter
    #output = filter(under_50, li)
    output = filter(lambda x: x<50, li)
    print(list(output))
    output = filter(lambda x: x%2, li)
    print(list(output))
    
    
if __name__ == "__main__":
    main()
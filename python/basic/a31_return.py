class DataArgument:
    def __init__(self):
        self.a = 10

def return_func(a):
    print("func is running..")
    if isinstance(a, list):
        a[0] += 1
    elif isinstance(a, DataArgument):
        a.a += 1
    else:
        a = a + 1
    b = 3.14
    c = "Lee"
    
    return a, b, c

def main():
    a = 10
    re = return_func(a)
    print(re)
    print(f"main a: {a} ")
    
    a, *b = return_func(a)
    print(type(a), type(b))
    print(a, b)
    
    # reference
    a = [10]
    re = return_func(a)  # value copy is basically shallow copy, not deep copy
    print(re)
    
    # variable of class can be changed?
    data = DataArgument()
    print(data.a)
    re = return_func(data)  # return address
    print(re, re[0].a)
    print(data.a)
    
    
if __name__ == "__main__":
    main()
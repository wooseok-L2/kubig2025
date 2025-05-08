def main():
    print(range(10))
    print(a:=range(10))
    print(a.count(2))
    print(a.step)
    print(a.index(1))
    print(list(a))
    
    for i in range(10):
        print(f"{i+1} output")
        
    list_a = ["Lee", 123, 3.3]
    #i = 0
    for i, ele in enumerate(list_a):
        print(f"{i} element value is {ele}")
        #i += 1
    
    num = [0, 1, 2]
    for ele, i in zip(list_a, num):
        print(f"{i} element value is {ele}")
    
if __name__ == "__main__":
    main()
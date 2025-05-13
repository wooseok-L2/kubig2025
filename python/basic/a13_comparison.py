def main():
    print(10 == 100)
    print(10 != 100)
    
    print(not True)
    print(not (10 < 100))
    
    if True:
        print("True")
        
    if False:
        print("False")
    
    while True:    
        a = int(input("Enter over than 100: "))
        
        if a > 200:
            print(a, " is over than 200", sep = "")
        elif a > 100:
            print(a, " is over than 100 less than 200", sep = "")
        else :
            print(a, " is less than 100")
        
        if a == 0:
            break
        

if __name__ == "__main__":
    main()
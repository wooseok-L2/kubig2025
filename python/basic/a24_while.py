def main():
    i = int()
    while i < 10:
        print(f"{i} execute")
        i += 1
        
    li = [1, 2, 3, 4, 5, 6, 7, 2, 1]
    
    while 2 in li:
        print("remove")
        li.remove(2)
    print (li)
    
    string_a = "this is a python class in Le"
    
    while "i" in string_a:
        print("replace")
        string_a = string_a.replace("i", "a")
    print(string_a)
    
    for number in li:
        if number > 3:
            print(number, end = " ")
    print()
    
    for number in li:
        if number > 3:
            continue
        print(number, end = " ")
    print()  
      
    for number in li:
        if number > 3:
            break
        print(number, end = " ")
    print()
        
    
if __name__ == "__main__":
    main()
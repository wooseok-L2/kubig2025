def main():
    input_var = input("enter nums : ")
    print(type(input_var), input_var)
    if input_var.isdigit():
        print("input_var + 100 : ", int(input_var) + 100)
    else :
        print(input_var, " is not nums", sep="")
    
    
if __name__ == "__main__":
    main()
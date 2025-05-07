#구구단 출력

def main():
    # input_val = input("enter nums: ")
    # sp_val = input_val.split()
    
    # print(int(sp_val[0]) * int(sp_val[1]))
    
    for i in range(2,10):
        for j in range(1,10):
            print(i, "*", j, "=", i*j, "|", end = ' ') 
        print()
    
    
if __name__ == "__main__":
    main()
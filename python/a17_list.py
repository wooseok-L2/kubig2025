import datetime

def main():
    #list hasn't limit of size and type. it means list can have any types
    list_a = list()
    list_b = [1, 2, [3, 4, 5]]
    
    print(type(list_a), type(list_b))
    
    ptime = datetime.datetime.now()
    list_c = [1, 2, 3.14, "Lee", ptime]
    
    print(list_c[3], list_c[4])
    print(list_b[1:3])
    print(list_b[2][1], list_b[2][2])
    
    
    
if __name__ == "__main__":
    main()
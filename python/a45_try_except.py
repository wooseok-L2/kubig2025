import traceback

def main():
    user_input = input("enter int : ")
    try:
        number = int(user_input)
    except ValueError as e:
        print("it is not int")
        print(e)
        traceback.print_exc()
    else:
        print("radius : ", number)
        print("area : ", 3.141592 * number**2)
    finally:
        print("remove resource and exit")
    
    
if __name__ == "__main__":
    main()
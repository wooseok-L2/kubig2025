def print_3_times():     #PyTypeObject  always return
    print("hello")
    print("hello")
    print("hello")
    
def print_n_times(value: str, n: int):  # usually insert Type  or check Type
    print("it is working")
    if not isinstance(n, int):
        print("error")
        return
    for _ in range(n):
        print(value)
        
def print_n_times_variable(n: int, *value: tuple[str]):  # 가변인자는 항상 맨 뒤에 사용
    """ n times print function

    Args:
        n (int): iterate
        *value(str) : enter str
    """
    print("it is working")
    print(type(value))
    if not isinstance(n, int):
        print("error")
        return
    for _ in range(n):
        for ele in value:
            print(ele, end = " ")
            print()

def main():
    print_3_times()
    print()
    print_3_times()
    print()
    
    print_n_times("hello", 5)
    print_n_times("hello", "five")  # error occured
    print_n_times_variable(7, "hi", "hello", "hola")
    
    
    
if __name__ == "__main__":
    main()
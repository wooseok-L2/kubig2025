class Test:
    def __init__(self, name):
        self.name = name
        print(f"{self.name} - created")
        
    def __del__(self):
        print(f"{self.name} - destroyed")

def main():
    a = Test("A")
    b = Test("B")
    c = Test("C")
    
    print(a, b, c)
    li = [a, b, c]
    del li[2]
    del c # destroyed without garbage collector
    print(li)
    print(c)



if __name__ == "__main__":
    main()
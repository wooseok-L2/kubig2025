class Myclass:
    def __init__(self, value):
        self.value = value
        
    def __eq__(self, other):
        return self.value == other.value

def main():
    a = Myclass(10)
    b = Myclass(10)
    
    if a == b:
        print("a and b are same")
    
    
    
    
    
if __name__ == "__main__":
    main()
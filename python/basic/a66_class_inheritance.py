class Parent:
    def __init__(self, value):
        self.value = "parents"
        self.value2 = value
        print("parent class __init__ method run")
        
    def test(self):
        print("parent class test method")
        
class Child(Parent):
    def __init__(self, value):
        super().__init__(value)
        print("child class __init__ method run")
        
    def child_test(self):
        print("child method run")
    
    def test(self):
        super().test()
        print("it is child class test method")


def main():
    child = Child("23")
    child.test()
    print(child.value2)
    print(child.__dict__)
    print(child.__dir__())
    print(Child.mro())  # provide from python
    
if __name__ == "__main__":
    main()
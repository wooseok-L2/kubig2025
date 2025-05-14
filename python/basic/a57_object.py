from collections.abc import Iterable
import random

# everything is inharitated object class

class TestClass:   #class TestClass(object);
    pass

def main():
    t1 = TestClass()
    if isinstance(t1, TestClass):
        print("t1 is object of TestClass")
    if isinstance(1, TestClass):
        print("int(1) is object of TestClass")
    else :
        print("int(1) is not object of TestClass")
        
    if issubclass(int, TestClass):
        print("int is inheritated from TestClass")
    else :
        print("int is not inheritated from TestClass")
        
    if issubclass(list, Iterable):
        print("list is inheritated")
    else:
        print("list is not inheritated from Iterable")
        
    if isinstance(TestClass, object):
        print("TestClass is inheritated")
    else :
        print("TestClass is not inheritated")
        
    print(
        issubclass(int, object),
        issubclass(float, object),
        issubclass(list, object),
        issubclass(str, object),
        issubclass(dict, object),
        issubclass(tuple, object),
        issubclass(random.Random, object),
        
    )
    
    
if __name__ == "__main__":
    main()
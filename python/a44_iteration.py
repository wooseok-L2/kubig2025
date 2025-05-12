from collections.abc import Iterable

class SimpleIter:
    def __init__(self, start, end):
        self.current = start
        self.end = end
        
    def __iter__(self):
        return self
    
    def __next__(self):
        if self.current >= self.end:
            raise StopIteration
        value = self.current
        self.current += 1
        return value
        

def main():
    iter_a = SimpleIter(1, 10)
    
    for i in iter_a:
        print(i)
        
    li = list()
    dict_a = dict()
    if isinstance(li, Iterable):
        print("li is Iterable")
        
    if isinstance(dict_a, Iterable):
        print("dict_a is Iterable")
    
    if isinstance(iter_a, Iterable):
        print("iter_a is Iterable")



if __name__ == "__main__":
    main()
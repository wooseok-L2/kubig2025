# tuple is iterable and there is no diff with list

def afun():
    a = 10
    b = 20
    return a, b    #(a, b) return

def main():
    a = tuple()
    c = 123
    b = a, c
    
    print(type(b))
    
    #swap
    a = 10
    b = 20
    a, b = b, a #(a, b) = (b, a)
    print(a, b)
    print(afun())
    
    for ele in afun():
        print(ele)
    
if __name__ == "__main__":
    main()
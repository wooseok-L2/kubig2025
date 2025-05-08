
def main():
    list_a = [1, 2, 3]
    list_b = [4, 5, 6]
    
    print(list_a + list_b)
    print(list_a, list_b)
    
    list_a.extend(list_b)
    print(list_a, list_b)
    list_a = list_a * 4
    print(len(list_a))
    print(list_a)
    
    list_b.append(7)
    list_b.append(8)
    print(list_b)
    
    list_b.insert(3, 0)
    print(list_b)
    list_b.insert(4, 6.5)
    print(list_b)
    
    list_b.remove(7)
    print(list_b)
    
    print(list_b.pop())
    print(list_b)
        
    
if __name__ == "__main__":
    main()
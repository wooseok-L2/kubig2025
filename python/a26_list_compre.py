def main():
    li = [i for i in range(101) if i % 2 == 0]
    print(li)
    
    li = [i+1 for i in range(101) if i % 2 == 0]
    print(li)
    
    
    
if __name__ == "__main__":
    main()
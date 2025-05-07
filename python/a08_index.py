def main():
    print("hello")
    print("hello" [0])
    print("hello" [1])
    print("hello" [2])
    print("hello" [3])
    print("hello" [4])
    
    say_hello = "hello"
    print(say_hello[0], end = ' ')
    print(say_hello[1], end = ' ')
    print(say_hello[2], end = ' ')
    print(say_hello[3], end = ' ')
    print(say_hello[4])
    
    for c in say_hello:
        print(c, end = ' ')
    print()
    
    say_hello *= 3
    
    print(say_hello)
    print(say_hello[5:10])
    print(say_hello[-3:])
    print(say_hello[5:10:2])
    print(say_hello[-1::-1 ])
    print("say_hello len :", len(say_hello))
    print("say_hello len :", say_hello.__len__())
    
    
if __name__ == "__main__":
    main()
    
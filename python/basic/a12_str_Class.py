def main():
    a = "leeWs"
    b = "LeeWs"
    c = "LeeWS"
    
    print(a.upper())  #it didnt change data just return 
    print(a)
    print(b.lower())
    print(c.lower())
    
    c = "    lee    "
    print(c + "end")
    print(c.strip() + 'end')
    print(c.lstrip() + 'end')
    print(c.rstrip() + 'end')
    
    d = "this is a python in ict, out class is best of IT class"
    print(d.find("a"))
    print(d[d.find("a")])
    print(d.rfind("a"))
    print(d[d.rfind("a")])
    
    idx = int()
    while d.find("a", idx) != -1:
        idx = d.find("a", idx)
        print(idx, end = ' ')
        idx += 1
    print()
    
    f = "TrainA10".isalnum()
    print(f)
    
    f = "Train_A10".isalnum()
    print(f)
    
    f = "10a".isdecimal()
    print(f)
    
    f = "10ff".isspace()
    print(f)
    g = d.split()
    print(g)
    
    print("he" in "hello")
    print("ha" in "youha")
    
if __name__ == "__main__":
    main()
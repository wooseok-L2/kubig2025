def main():
    string = 'abc'
    string2 = 'this is format test: {}'.format(10)
    print(string)
    print(string2)
    string3 = 'this is format test: {2} {1} {0}'.format(10, 20, 30)
    print(string3)
    
    string3 = 'this is format test: {2:d} {1:5d} {0:05d}'.format(10, 20, 30)
    print(string3)
    
    string3 = 'this is format test: {2:+d} {1:+5d} {0:+05d}'.format(-10, 20, -30)
    print(string3)
    
    string3 = 'this is format test: {2:+f} {1:+5.2f} {0:+05.2f}'.format(-10.123, 20.53, -30)
    print(string3)
    
    #fstring
    string3 = f'this is format test: {-30:+f} {20.53:+5.2f} {-10.126:+05.2f}'
    print(string3)
    
if __name__ == "__main__":
    main()
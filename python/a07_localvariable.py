b = [1,2,3, 'four']

def main():
    a = 123
    print("local 변수: ", locals(), a)
    print("vars 변수(b): ", vars(main))
    print("globals", globals())

if __name__ == "__main__":
    main()
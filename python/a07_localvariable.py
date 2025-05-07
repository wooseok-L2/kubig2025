b = [1, 2, 3, 'four']

def main():
    a = 123
    print("local : ", locals())
    print("vars : ", vars())
    print("globals : ", globals())


if __name__ == "__main__":
    main()
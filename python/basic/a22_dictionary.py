def main():
    dict_a = dict()
    dict_b = {1 : 1, 2 : 2, 3 : 3}
    # dict_b = {1, 2, 3}  => set
    print(type(dict_a), type(dict_b))
    
    a = "d"
    dict_c = {"a" : 100, "b" : 200, "c" : 300, a : 400}
    print(dict_c["a"])
    dict_c["d"] = 500
    print(dict_c["d"])
    dict_c["e"] = 600   # add data
    print(dict_c)
    # print(dict_c["f"])   # key error
    print(dict_c.get("f"))  # 에러로 인한 프로그램 정지 방지
    
    
if __name__ == "__main__":
    main()
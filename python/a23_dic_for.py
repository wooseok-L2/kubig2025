def main():
    dict_a = dict()
    list_a = ["gone", "exits"]
    dict_b = {1 : 1, 2 : 2, 3 : list_a}
    # dict_b = {1, 2, 3}  => set
    print(type(dict_a), type(dict_b))
    
    a = "d"
    dict_c = {"a" : 100, "b" : 200, "c" : 300, a : 400}
    # for i in dict_c:
    #     print(i, dict_c[i], end = " ")
    # print()
    
    for k, v in dict_c.items():
        print(k, v, end = ", ")
    print()
    
    dict_b.update(dict_c) # 내부데이터가 변하는 메소드
    print(dict_b)
    
    del dict_b[3]
    print(dict_b)
    print(list_a)   # didnt remove
    del list_a      # removed
    
    print(dict_b.pop(2))   # remove and use data
    print(dict_b)
    
    
if __name__ == "__main__":
    main()
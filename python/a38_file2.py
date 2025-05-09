def main():
    with open("data/text.txt", "r", encoding="utf-8") as f:
        # str = f.read()
        # sentences = str.split("/n")
        # for line in sentences:
        #     print(line)
        # print(str)
        
        # lines = f.readlines()
        # for line in lines:
        #     print(line + "// per line")
            
        while(line := f.readline()):
            print(line)

        
        
if __name__ == "__main__":
    main()
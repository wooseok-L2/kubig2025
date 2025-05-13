def main():
    # f = open("data/text.txt", "w")
    # print(f.fileno())   #file descriptor
    # f.write("hello, Python Programming, hi everyone!")
    
    # #stardard IO func fputs, fprintf, f....
    # f.close()
    
    with open("data/text.txt", "a") as f:              # always close file descripter 
        f.write("hello Python!! second input")
        f.write("\n")
    
if __name__ == "__main__":
    main()
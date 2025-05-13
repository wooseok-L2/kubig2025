import os

def main():
    print(os.name)
    print(os.getcwd())    # workspace dir
    print(os.listdir())   # workspace folder list
    
    os.mkdir("test_dir")
    print("folder has been created")
    os.chdir(os.getcwd() + "/test_dir")
    print(os.getcwd())
    input()
    os.rmdir("test_dir")
    print("folder has been deleted")
    
    print(os.system("ls-al"))
    
if __name__ == "__main__": 
    main()
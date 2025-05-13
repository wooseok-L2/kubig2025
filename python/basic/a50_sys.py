import sys
import argparse

def main():
    print(sys.argv)
    for value in sys.argv:
        print(value)
        
    print("version", sys.version)
    print("version_info", sys.version_info)
    print("copyright", sys.copyright)
    print("getprofile", sys.getprofile())
    
    sys.exit()
    
    
if __name__ == "__main__":
    main()
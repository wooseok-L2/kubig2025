import sys

def main():
    a = "hello"
    print(f"stdin file descreptor no: {sys.stdin.fileno()}")
    print(f"stdout file descreptor no: {sys.stdout.fileno()}")     
    print(f"stderr file descreptor no: {sys.stderr.fileno()}")
    print(f"error message", file = sys.stderr)
    with open("data/text.txt", "a", encoding = "utf-8") as f:
        print(f"{a} Python", file = f)
    
    
if __name__ == "__main__":
    main()
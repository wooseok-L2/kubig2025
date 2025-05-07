import sys

abc = int()
abc2 = list()
frame = sys._getframe()
print("current frame : ", frame)
print("code object : ", frame.f_code)
print("local variable : ", frame.f_locals)
print(frame.f_globals.items())
print(frame.f_globals[__name__])
print(globals.items())
print("current module_frame : ", frame.f_code.co_name)

def main():
    a = 123
    b = [3, 4, 5]
    main_frame = sys._getframe()
    print("current main_frame : ", main_frame.f_code.co_name)
    print("local variable : ", main_frame.f_locals)
    print("global variable : ", main_frame.f_globals)


if __name__ == "__main__":
    main()
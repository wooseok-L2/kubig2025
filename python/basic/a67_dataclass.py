from dataclasses import dataclass


@dataclass
class Student:
    name: str
    korean: int
    math: int
    english: int
    science: int

    def get_sum(self):
        return self.korean + self.english + self.math + self.science

def main():
    st1 = Student("aaa", 23, 45, 67, 47)
    st2 = Student("bbb", 23, 56, 37, 47)
    print(st1.name, st1.korean, st1.english)
    print(st2.name, st2.korean, st2.english)
    print(st1.get_sum())
    
    
if __name__ == "__main__":
    main()
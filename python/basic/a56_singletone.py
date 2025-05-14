import random


class Student:
    count_ = int()
    students_ = list()

    def __init__(self, name, korean, math, english, science):
        # *this = self (this->) cpp 에서는 생략 가능
        # 파이썬 에서는 인스턴스 변수는 self 를 반드시 붙여야 한다.
        self.name = name
        self.korean = korean
        self.math = math
        self.english = english
        self.science = science
        self.num = 4
        Student.count_ += 1
        Student.students_.append(self)
        print(f"{Student.count_} 번째 학생이 생성 되었습니다.")

    def student_get_sum(self):
        return self.korean + self.math + self.english + self.science

    def student_get_average(self):
        return self.student_get_sum() / self.num

    def student_to_string(self):
        return f"{self.name}\t{self.student_get_sum()}\t{self.student_get_average()}"

    def __str__(self):
        return f"{self.name}\t{self.student_get_sum()}\t{self.student_get_average()}"

    def __gt__(self, value):
        return self.student_get_sum() > value.student_get_sum()

    def __eq__(self, value):
        return self.student_get_sum() == value.student_get_sum()

    def __ne__(self, value):
        return self.student_get_sum() != value.student_get_sum()

    @classmethod
    def print(cls):
        print(f"현재 생성된 학생수는 {cls.count_} 입니다.")
        print("--------------학생 목록--------------")
        for student in cls.students_:
            print(student.student_to_string())
        print("------------------------------------")

    # ge , le, lt


def main():
    hanguls = list("최강박이손정적고구류오김송곽유")
    hanguls2 = list("가나다라마바사아자차카파타하길진재형준석화섭윤진")
    for _ in range(50):
        Student(
            random.choice(hanguls) + "".join(random.choices(hanguls2, k=2)),
            random.randint(65, 100),
            random.randint(65, 100),
            random.randint(65, 100),
            random.randint(65, 100),
        )
    Student.print()


if __name__ == "__main__":
    main()
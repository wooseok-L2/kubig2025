from dataclasses import dataclass


@dataclass
class StudentData:
    name: str = ""
    korean: int = 0
    math: int = 0
    english: int = 0
    science: int = 0
    num: int = 4


class Student:
    def __init__(self, **kwarg):
        self.num = 4
        for k in kwarg:
            setattr(self, k, kwarg.get(k, 0))  # 동적으로 인스턴스 변수 추가!!

    def student_get_sum(self):
        return self.korean + self.math + self.english + self.science

    def student_get_average(self):
        return self.student_get_sum() / self.num

    def student_to_string(self):
        return f"{self.name}\t{self.student_get_sum()}\t{self.student_get_average()}"


class GraduateStudent:
    def __init__(self, arg: StudentData):
        self.name = arg.name
        self.korean = arg.korean
        self.math = arg.math
        self.english = arg.english
        self.science = arg.science
        self.num = arg.num

    def student_get_sum(self):
        return self.korean + self.math + self.english + self.science

    def student_get_average(self):
        return self.student_get_sum() / self.num

    def student_to_string(self):
        return f"{self.name}\t{self.student_get_sum()}\t{self.student_get_average()}"


def main():
    students = []
    graduateStudents = []
    with open("/home/lws/kulws2025/kubig2025/python/basic/students.txt", "r") as f:
        while data := f.readline():
            split_data = data.split()
            students.append(
                Student(
                    name=split_data[0],
                    korean=int(split_data[1]),
                    math=int(split_data[2]),
                    english=int(split_data[3]),
                    science=int(split_data[4]),
                )
            )
            graduateStudents.append(
                GraduateStudent(
                    StudentData(
                        split_data[0],
                        int(split_data[1]),
                        int(split_data[2]),
                        int(split_data[3]),
                        int(split_data[4]),
                    )
                )
            )

    for student in students:
        print(student.student_to_string())
    for student in graduateStudents:
        print(student.student_to_string())


if __name__ == "__main__":
    main()
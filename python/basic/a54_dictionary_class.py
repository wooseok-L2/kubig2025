import random


def create_student(name, korean, math, english, science):
    return {
        "name": name,
        "korean": korean,
        "math": math,
        "english": english,
        "science": science,
    }


def student_get_sum(student):
    return student["korean"] + student["math"] + student["english"] + student["science"]


def student_get_average(student, num):
    return student_get_sum(student) / num


def student_to_string(student, num):
    return f'{student["name"]}\t{student_get_sum(student)}\t{student_get_average(student, num)}'


def main():
    hanguls = list("최강박이손정적고구류오김송곽유")
    hanguls2 = list("가나다라마바사아자차카파타하길진재형준석화섭윤진")
    students = [
        create_student(
            random.choice(hanguls) + "".join(random.choices(hanguls2, k=2)),
            random.randint(65, 100),
            random.randint(65, 100),
            random.randint(65, 100),
            random.randint(65, 100),
        )
        for _ in range(50)
    ]
    for student in students:
        print(student_to_string(student, 4))


if __name__ == "__main__":
    main()
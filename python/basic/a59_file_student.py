import random
import os


class Students: 
    def __init__(self, name, korean, math, english, science):
        # this = self
        # instance variable should use self at python  
        self.name = name
        self.korean = korean
        self.math = math
        self.english = english
        self.science = science
        self.num = 4
    
    def __str__(self):
        return f"{self.name} {self.korean} {self.math} {self.english} {self.science}"

    def student_get_sum(self):
        return self.korean + self.math + self.english + self.science

    def student_get_average(self):
        return self.student_get_sum() / self.num

    def student_to_string(self):
        return f'{self.name}\t{self.student_get_sum()}\t{self.student_get_average()}'


def main():
    hanguls = list("최강박이손정적고구류오김송곽유")
    hanguls2 = list("가나다라마바사아자차카파타하길진재형준석화섭윤진")

    file_path = "python/basic/students.txt"

    if not os.path.exists(file_path):
        with open(file_path, "w") as f:  # "w" 모드로 새 파일 생성
            f.write("\n".join(
                str(Students(
                    random.choice(hanguls) + "".join(random.choices(hanguls2, k=2)),
                    random.randint(65, 100),
                    random.randint(65, 100),
                    random.randint(65, 100),
                    random.randint(65, 100),
                )) for _ in range(100)
            ))
            #f.write("\n")  # 줄바꿈 추가


    with open(file_path, "r") as f:
        for line in f:
            data = line.strip().split()  # 문자열을 리스트로 변환
            student = Students(data[0], int(data[1]), int(data[2]), int(data[3]), int(data[4]))  # 객체 생성
            print(student.student_to_string())  # 정상 출력



if __name__ == "__main__":
    main()
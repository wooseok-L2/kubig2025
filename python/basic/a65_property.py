import math


class Circle:
    def __init__(self, radius):
        self._radius = radius
        self.__hidden = radius

    def get_area(self):
        return math.pi * self._radius**2

    @property
    def radius(self):
        return self._radius

    @radius.getter
    def radius(self):
        # .. 얻어내는 과정에 개입을 해서 제한하는 코드..
        return self._radius

    @radius.setter
    def radius(self, value):
        # .. 중간 코드..
        if value < 0:
            self._radius = 0
        if value > 100:
            self._radius = 100
        else:
            self._radius = value


def main():
    circle = Circle(10)
    # print(circle._radius)
    circle.radius = 150
    print(circle.radius)
    print(circle.get_area())
    # print(circle.__hidden)  # 언더바 2번이면 강제성이 있다! 은닉은..... 못함...
    # print(circle.askldjhf)


if __name__ == "__main__":
    main()
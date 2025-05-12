# matplotlib
# pip install matplotlib
# sudo python3 -m pip install matplotlib
# uniform -> 균등 , gauss, normal.. -> 정규...
# uniform -> 정규분포 만들기.( 중심 극한 정리...)
import math
import random

import matplotlib.pyplot as plt
import numpy as np


def main():
    n_samples = 100000
    sample_size = 300
    a = 0
    b = 1

    means = []
    # uniform 균등 분포 결과 테스트
    for _ in range(n_samples):
        value = random.uniform(a, b)
        means.append(value)
    plt.hist(means, bins=sample_size)
    plt.show()

    means = []
    # uniform 균등 분포 평균결과 테스트
    for _ in range(n_samples):
        sample = [random.uniform(a, b) for _ in range(sample_size)]
        mean = sum(sample) / sample_size
        means.append(mean)
    print("표준 편차: ", np.std(means))
    plt.hist(means, bins=sample_size)
    plt.show()

    # gauss() 함수 테이터
    mu = (a + b) / 2
    sigma = math.sqrt((b - a) ** 2 / (12 * sample_size))  # 표준 편차
    print("sigma: ", sigma)
    gauss_data = []
    for _ in range(n_samples):
        gauss_data.append(random.gauss(mu=mu, sigma=sigma))
    print(np.std(gauss_data))

    plt.hist(gauss_data, bins=sample_size)
    plt.show()


if __name__ == "__main__":
    main()
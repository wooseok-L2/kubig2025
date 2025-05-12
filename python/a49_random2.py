import matplotlib.pyplot as plt
import math
import random

def main():
    n_samples = 10000
    sample_size = 30
    a = 0
    b = 1
    
    #uniform result test
    means = []
    for _ in range(n_samples):
        sample = [random.uniform(a, b) for _ in range(sample_size)]
        mean = sum(sample) / sample_size
        means.append(mean)

    plt.hist(means, bins = sample_size)
    
    mu = (a + b) / 2
    sigma = math.sqrt((b - a) ** 2 / (12 * sample_size)) 
    
    # x = [mu-4*sigma+i(8*sigma/100) for i in range(100)]
    # y = [random.gauss(t, mu, sigma) for t in x]
    
    # x = [i for i in range(1000)]
    # y = [i * 2 for i in range(1000)]
    
    # plt.plot(x, y)
    plt.show()
    

if __name__ == "__main__":
    main()
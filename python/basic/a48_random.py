import random

def main():
    for _ in range(10):
        print("random() : ", random.random())  #0~1
        print("uniform(10,20) : ", random.uniform(10, 20))
        print("randint() : ", random.randint(3, 15))
        print("range(200) : ", random.randrange(200))    
        print("choice : ", random.choice([1, 2, 3, 4, 5]))
        print("choices : ", random.choices([1, 2, 3, 4, 5], k=5))
        
        li = [1, 2, 3, 4, 5]
        random.shuffle(li)
        print("shuffle : ", li)
        print("sample ; ", random.sample(li, k=5)) 
        
        print("----------------------------------------")
    
if __name__  == "__main__":
    main()
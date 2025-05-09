import time

def main():
    print(time.asctime())
    print(time.time())
    print(time.clock_gettime_ns(1))
    
    ptime = time.time()
    cnt = int()
    while time.time() < ptime + 5:
        cnt += 1
    print(f"this com can count {cnt} for 5sec")
        
    cnt = 0
    ptime = time.time()
    for _ in range(10_000_000):
        cnt += 1
    endtime = time.time()
    
    print(f"{endtime-ptime}")
    
if __name__ == "__main__":
    main()
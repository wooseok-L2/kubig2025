import asyncio
import time

async def hello():
    print("hello world")
    await asyncio.sleep(5.0)
    
def hello2():
    print("hello world")
    time.sleep(5)
    
    
async def main():
    # sync
    # for _ in range(3):
    #     await hello()
    # print("main func end")
    
    # async
    # tasks = [hello(), hello(), hello()]
    # await asyncio.gather(*tasks)
    # print("main func end")
    
    # await hello()
    
    # tasks = [asyncio.create_task(hello()) for _ in range(3)]
    # for task in tasks:
    #     await task
    
    t1 = asyncio.create_task(hello())
    t2 = asyncio.create_task(hello())
    t3 = asyncio.create_task(hello())
    
    await t1
    await t2
    await t3
    
    print("main func end")
    
if __name__ == "__main__":
    asyncio.run(main())
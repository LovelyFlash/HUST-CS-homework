abs(-5)        # 绝对值 → 5
# round(3.1415, 2) # 四舍五入 → 3.14
# pow(2, 3)      # 幂运算 → 8（等价于 2**3）
# sum([1,2,3])   # 求和 → 6
# max('Python')  # 最大字符 → 'y'
#
# bin(10)        # 十进制转二进制 → '0b1010'
# hex(255)       # 十进制转十六进制 → '0xff'
# ord('A')       # 字符转ASCII码 → 65
# chr(97)        # ASCII码转字符 → 'a'
# bool(0)        # 转布尔值 → False
#
# list(range(1,5))    # 生成序列 → [1,2,3,4]
# len('华科')         # 字符长度 → 2（中文默认按字符计算）
# sorted([3,1,2], reverse=True)  # 降序排序 → [3,2,1]
# enumerate(['a','b']) # 生成(索引,值)对 → (0,'a'), (1,'b')
# zip([1,2], ['a','b']) # 合并序列 → (1,'a'), (2,'b')
#
# id(x)          # 获取对象内存地址
# type(3.14)     # 查看类型 → <class 'float'>
# isinstance(5, int)  # 类型检查 → True
# hasattr(str, 'split') # 检查方法是否存在 → True
#
# open('test.txt', 'r', encoding='utf-8')  # 文件读取

# 字典创建的6种方法
# a={"吕布":"口口布","关羽":"关习习","刘备":"刘Baby"}
# b=dict(吕布="口口布",关羽="关习习",刘备="刘Baby")
# c= dict([("吕布","口口布"),("关羽","关习习"), ("刘备","刘Baby")])
# d= dict({"吕布":"口口布","关羽":"关习习","刘备":"刘Baby"})
# e=dict({"吕布":"口口布","关羽":"关习习"},刘备="刘Baby")
# f=dict(zip(["吕布","关羽","刘备"],["口口布","关习习","刘Baby"]))

#以下是装饰器部分
# import time
#     def logger(msg):
#         def time_master(func):
#             def call_func():
#                 start = time.time()
#                 func()
#                 stop = time.time()
#                 print(f"[{msg}]一共耗费了【{(stop-start):.2f}")
#         return cail_func
#     return time_master

# def funA():
#     time.sleep(1)
#     print("正在调用funA...")
# def funB():
#     ime.sleep(1)
#     print("正在调用funB...")

# funA = logger(msg="A") (funA)
# funB = logger(msg="B") (funB)

# greet("Alice")
# def prefix_function(s):
#     n = len(s)
#     pi = [0] * n
#     for i in range(1, n):
#         j = pi[i - 1]
#         while j > 0 and s[i] != s[j]:
#             j = pi[j - 1]
#         if s[i] == s[j]:
#             j += 1
#         pi[i] = j
#     return pi
# print(prefix_function(input()))
from typing import Union

from fastapi import FastAPI

app = FastAPI()


@app.get("/")
def read_root():
    return {"Hello": "World"}


@app.get("/items/{item_id}")
def read_item(item_id: int, q: Union[str, None] = None):
    return {"item_id": item_id, "q": q}
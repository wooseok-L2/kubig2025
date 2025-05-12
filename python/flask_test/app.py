# 웹 프레임워크!! back-end -> 핸드폰!! 연동.
# flask run -> 웹 공부를 하고 싶으면 검색 !!

# jdango flask fastapi .... 역사와 전통이 있는...

# gradio (머신 러닝.. openUI..)
# streamlit (대시보드.)
# dash (데이터 시각화!!)
# ...

# GUI 프로그램. (windows, unix)
# pythonQT, tkinter -> window 프로그램
# pygame, matplotlib, openCV
# windows OS -> C# MSC(c++) ,linux -> SDL, vulkan, .....
# Unity, Unreal...

# AI 관련 라이브러리
# numpy, pandas, matplotlib, tensorflow( keras ), pytorch, sk-learn(머신러닝)
# orange3


from flask import Flask

app = Flask(__name__)


@app.route("/")
def hello():
    return "<h1>Hello Word! I'm python Flask!!</h1>"
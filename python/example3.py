# 문자열을 입력 받아서 단어를 카운트 해서 결과를 출력하세요
def main():
    text = """
Yesterday all my troubles seemed so far away.
Now it looks as though they're here to stay.
Oh, I believe in yesterday.

Suddenly I'm not half the man I used to be.
There's a shadow hanging over me.
Oh, yesterday came suddenly.

Why she had to go, I don't know, she wouldn't say.
I said something wrong, now I long for yesterday.

Yesterday love was such an easy game to play.
Now I need a place to hide away.
Oh, I believe in yesterday.

Why she had to go, I don't know, she wouldn't say.
I said something wrong, now I long for yesterday.

Yesterday love was such an easy game to play.
Now I need a place to hide away.
Oh, I believe in yesterday.
"""
    unique_word = ","
    word = ""
    i = 0
    text = text.lower()
    while i < len(text):
        if text[i].isalnum() or text[i] == " ":
            word += text[i]
        else:
            word += " "
        if text[i] == " " or text[i] == "\n":
            if word.strip() and word.strip() not in unique_word:
                unique_word += word.strip() + ","
                count = len(text.split(word.strip()))
                print(word.strip(), ":", count, "번")
            word = ""
        i += 1

if __name__ == "__main__":
    main()
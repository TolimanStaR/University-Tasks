answer, count = 0, 0

for number in range(1, 1001):
    ans: int = number
    cnt: int = 0
    while number != 1:
        number = number * 3 + 1 if number % 2 else number // 2
        cnt += 1

    if cnt > count:
        count = cnt
        answer = ans

print(f'Answer is {answer} with {count} iterations')

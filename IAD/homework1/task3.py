from typing import Any
import random

phrase: list = [

]

larger: list = [
    'Куда так много то!!?',
    'У меня микросхемы от таких чисел трещат, давай поменьше',
    'Еще long long введи. Попробуй мешьше',
    'Гос. Долг США меньше твоих чисел, введи поменьше',
    'Не знаю, простое ли твоё число, но оно точно больше, чем нужно',
    'Не попал. Попробуй опустить ствол, дружок',
]

smaller: list = [
    'Слишком мало, человечишка.',
    'Не дотягиваешь до ответа, попробуй больше',
    'Мелковат',
    'Попробуй угадать ответ, а не свой накоп по матану',
]

not_a_digit: list = [
    'Ты ввел не число. Сейчас кому-то будет больно. ',
    'В колено себе выстрели своими символами!',
]

out_of_range: list = [
    'Что вы себе позволяете! Ваше число выходит за все границы!',
]


def print_random_phrase(array):
    print(array[random.randint(0, len(array) - 1)])


def give_answer(action: Any = None) -> None:
    '''
    action -1 means out of range
    action 2 means larger
    action 1 means equal
    action 0 means smaller
    if action is none, it means that user is idiot
    '''

    if action is None:
        print_random_phrase(not_a_digit)
        exit(0)

    if action == -1:
        print_random_phrase(out_of_range)

    if action == 2:
        print_random_phrase(larger)

    if action == 0:
        print_random_phrase(smaller)

    if action == 1:
        print('Победа за тобой, друг. Еще увидимся...')

    pass


def get_secret_number() -> int:
    return random.randint(1, 100)


def game(secret_number: int) -> None:
    while True:
        user_answer: Any = input()

        if not user_answer.isdigit():
            give_answer(None)
            return

        user_answer = int(user_answer)

        if not -1 < user_answer < 101:
            give_answer(-1)

        action = 0 if user_answer < secret_number else (1 if secret_number == user_answer else 2)
        give_answer(action)

        if user_answer == secret_number:
            return


if __name__ == '__main__':
    print(
        '''
        Добро пожаловать в игру "Сдохни или умри"!
        
        Тупая машина загадывает число, мешок с костями должен его отгадать.
        
        Алгоритм игры такой:
        1) Ты, дорогой пользователь, вводишь число.
        2) Компьютер дает тебе подсказку: больше это число загаданного, меньше, или равно.
        3) Так продолжается, пока не надоест, или, не дай Б-г, ты не выиграешь.
        
        p.s. и не вздумай вводить чего еще кроме чисел, кожанный ублюдок! (Всю оперативку тебе испорчу!!!)
        '''
    )

    answer: int = get_secret_number()
    game(answer)

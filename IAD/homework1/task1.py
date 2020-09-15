import re
from typing import Any


def count_words(target_file: str) -> int:
    file = open(target_file, 'r')
    answer: int = 0

    for line in file.readlines():
        answer += len(line.split())
    file.close()

    return answer


def find_most_popular_words(target_file: str, amount: int) -> tuple:
    file = open(target_file, 'r')
    words: dict = dict()

    for line in file.readlines():
        for word in line.split():
            words[word] = 0

    file.seek(0)

    for line in file.readlines():
        for word in line.split():
            words[word] += 1

    result = tuple(sorted(
        [(key, amount) for key, amount in zip(words.keys(), words.values())],
        key=lambda x: x[1],
        reverse=True)[:amount])

    return result


def reverse_sentences(target_file: str) -> str:
    file = open(target_file, 'r')
    text: str = str()
    sentences: str = str()
    sentence: Any = str()
    separators = (
        '...',
        '!?',
        '!',
        '?',
        '.',
    )

    for line in file.readlines():
        text += line

    index = 0
    while index < len(text):
        for separator in separators:
            if text[index:index + len(separator)] == separator:
                sentence = sentence.replace('\n', ' ')
                sentence = sentence.split()
                sentence.reverse()
                for word in sentence:
                    sentences += f' {word}'
                sentences += separator
                sentence = ''
                index += len(separator)
                break
        else:
            sentence += text[index]
            index += 1

    return sentences


if __name__ == '__main__':
    file_name = 'text.txt'

    print(f'Total words count: {count_words(target_file=file_name)}', end='\n')
    print(*[f'\n{word}: {count}' for word, count in find_most_popular_words(file_name, 10)])
    print(reverse_sentences(file_name))

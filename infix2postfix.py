# -*- coding: utf-8 -*-
import sys
import string


OPERATION = ['*', '/', '-', '+']
NUM = string.digits
ALPHA = string.ascii_lowercase
ALPHANUM = NUM + ALPHA

EMPTY = string.whitespace

OPEN_BRACKET = ['(']
CLOSE_BRACKET = [')']


def priority_char(ch):
    '''
    Функция приоритета
    '''
    if ch in ['(', ')', 'e']:
        return 0
    if ch in ['+', '-']:
        return 1
    if ch in ['*', '/']:
        return 2


def infix2postfix(str_iter):
    '''
    python style
    '''
    stack = []
    number_str = ''
    stack.append('e')

    for ch in str_iter:
        if ch not in NUM and number_str:
            yield number_str
            number_str = ''

        if ch in OPERATION:
            while True:
                if priority_char(ch) > priority_char(stack[-1]):
                    stack.append(ch)
                    break
                else:
                    yield stack.pop()

        elif ch in ALPHANUM:
            number_str += ch

        elif ch in OPEN_BRACKET:
            stack.append(ch)

        elif ch in CLOSE_BRACKET:
            while True:
                ch = stack.pop()
                if ch in OPEN_BRACKET:
                    break
                else:
                    yield ch
    if number_str:
        yield number_str

    for s in reversed(stack[1:]):
        yield s

FUNC_MAP = {
        '+': lambda x, y: x + y,
        '-': lambda x, y: x - y,
        '/': lambda x, y: x / y,
        '*': lambda x, y: x * y,
        }


def postfix_calculate(iterator, stack=None):
    if not stack:
        stack = []
    for char in iterator:
        try:
            stack.append(float(char))
        except ValueError:
            func = FUNC_MAP[char]
            y = stack.pop()
            x = stack.pop()
            stack.append(func(x, y))

    return stack[0]


def test():
    result = list(infix2postfix("(1+2)/(3*2)-5"))
    assert " ".join(result) == '1 2 + 3 2 * / 5 -', result
    assert postfix_calculate(result) == -4.5

    result = list(infix2postfix("(1+12)/(30*232)-50"))
    assert " ".join(result) == '1 12 + 30 232 * / 50 -', result
    assert -49.9 >= postfix_calculate(result) >= -50.0

    result = list(infix2postfix("1 + 2 * (3 - 4) / 5"))
    assert " ".join(result) == '1 2 3 4 - * 5 / +', result
    assert postfix_calculate(result) == (1. + 2. * (3. - 4.) / 5.)

    result = list(infix2postfix("(1) + (1)"))
    assert " ".join(result) == '1 1 +', result
    assert postfix_calculate(result) == (1 + 1)


def file_reader(file_obj, buf_size=1024):
    '''
    Посимвольное чтение из файла
    '''
    str_buf = file_obj.read(buf_size)
    while str_buf:
        for ch in str_buf:
            yield ch
        str_buf = file_obj.read(buf_size)


def main():
    try:
        file_obj = open(sys.argv[1])
    except IndexError:
        file_obj = sys.stdin

    print postfix_calculate(infix2postfix(file_reader(file_obj)))


if __name__ == '__main__':
    main()
    #test()
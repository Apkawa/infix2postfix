# -*- coding: utf-8 -*-
import sys
import random

OPERATORS = '*/-+'

OPEN_BRACKET = 1
CLOSE_BRACKET = 2
NUMBER = 3
OPERATOR = 4


def get_operator():
    rnd = random.random()

    rate = 0.0
    rate += 0.10
    if rnd <= rate:
        return random.choice("/*")

    return random.choice("-+")


def get_number():
    return random.randint(1, 1000)


def generate_infix(max_symbol=1024):
    state = random.choice([OPEN_BRACKET, NUMBER])
    bracket_num = 0
    for i in xrange(max_symbol):
        if state == OPEN_BRACKET:
            state = NUMBER
            bracket_num += 1
            yield "("

        elif state == CLOSE_BRACKET:
            bracket_num -= 1
            state = OPERATOR
            yield ")"

        elif state == NUMBER:
            next_states = [OPERATOR]

            if bracket_num:
                next_states.append(CLOSE_BRACKET)

            state = random.choice(next_states)
            yield get_number()

        elif state == OPERATOR:
            state = random.choice([NUMBER, OPEN_BRACKET])
            yield " "
            yield get_operator()
            yield " "

    if state == OPERATOR:
        yield get_operator()
        state = NUMBER

    if state == OPEN_BRACKET:
        state = NUMBER

    if state == NUMBER:
        yield get_number()

    if bracket_num > 0:
        for i in xrange(bracket_num):
            yield ")"


def test():
    for i in xrange(1024):
        for r in xrange(100):
            try:
                result = " ".join(map(str, generate_infix(i)))
                result, ' = ', eval(result)
                print "OK"
            except ZeroDivisionError:
                print "ZeroDivisionError"

def main():
    try:
        length = int(sys.argv[1])
    except:
        length = 1024

    #f = open("test.txt", "wb")
    f = sys.stdout

    for symbol in generate_infix(length):
        f.write(str(symbol))

if __name__ == '__main__':
    #test()
    main()

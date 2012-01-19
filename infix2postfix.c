#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define OPEN_BRACKET_STATE 1
#define CLOSE_BRACKET_STATE 2
#define NUMBER_STATE 3
#define OPERATOR_STATE 4


char OPERATORS[] = {'/', '*', '-', '+'};

const char OPEN_BRACKET = '(';
const char CLOSE_BRACKET = ')';
const char SPACE = ' ';


void write_symbol(char ch) {
    printf("%c", ch);
}

void write_int(int ch) {
    printf("%i", ch);
}

int randint(int from, int to) {
    return from + rand() % to;
}

int rand_choice_int(int *array, int array_length) {
    return array[randint(0, array_length)];
}

char rand_choice_char(char *array, int array_length) {
    return array[randint(0, array_length)];
}

char get_operator(void) {
   return rand_choice_char(OPERATORS, 4);
}

char get_number(void) {
    return randint(0, 5000);
}


void generate_infix(long max_symbol_count) {
    int open_bracket_number_array[] = {OPEN_BRACKET_STATE, NUMBER_STATE};

    int state = rand_choice_int(open_bracket_number_array, 2);
    long bracket_num = 0;

    long i;
    for (i = 0; i <= max_symbol_count; i++) {
        switch (state) {
            case OPEN_BRACKET_STATE:
                {
                    state = NUMBER_STATE;
                    bracket_num++;
                    write_symbol(OPEN_BRACKET);
                    break;
                }

            case CLOSE_BRACKET_STATE:
                {
                    bracket_num--;
                    state = OPERATOR_STATE;
                    write_symbol(CLOSE_BRACKET);
                    break;
                }

            case NUMBER_STATE:
                {
                    if (bracket_num) {
                        int next_state[] = {OPERATOR_STATE, CLOSE_BRACKET_STATE};
                        state = rand_choice_int(next_state, 2);
                    }
                    else {
                        state = OPERATOR_STATE;
                    }
                    write_int(get_number());
                }

            case OPERATOR_STATE:
                {
                    state = rand_choice_int(open_bracket_number_array, 2);
                    write_symbol(SPACE);
                    write_symbol(get_operator());
                    write_symbol(SPACE);
                }

        }
    }


    if (state == OPERATOR_STATE)
    {
        write_symbol(SPACE);
        write_symbol(get_operator());
        write_symbol(SPACE);
        state = NUMBER_STATE;
    }

    if (state == OPEN_BRACKET_STATE) {
        state = NUMBER_STATE;
    }

    if (state == NUMBER_STATE) {
        write_int(get_number());
    }

    if (bracket_num > 0) {
        for (i = 0; i < bracket_num; i++) {
            write_symbol(CLOSE_BRACKET);
        }
    }

}

int main(int argc, const char *argv[])
{
    long max_symbol_count;
    srand(time(NULL));
    if (argc > 1)
    {
        max_symbol_count = strtol(argv[1], NULL, 10);
    } else {
        max_symbol_count = 1024;
    }

    generate_infix(max_symbol_count);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#define size_array(array) (sizeof array)/(sizeof array[0])


char OPERATION[] = {'*', '/', '-', '+'};
char NUMBER[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
char OPEN_BRACKET[] = {'('};
char CLOSE_BRACKET[] = {')'};


int priority_char(char ch)
{
    switch (ch){
        case '(':
            return 0;
        case ')':
            return 0;
        case 'e':
            return 0;
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;

    }
}


int char_in_array(char ch, char *array, int array_len) {
    int i;
    for (i = 0; i < array_len; i++) {
        if (ch == array[i]) {
            return 1;
        }
    }
    return 0;
}

void write_result(char ch) {
    printf("%c", ch);
}

void infix2postfix(FILE * file) {
    int i;
    int c;
    char stack[255];

    char ch;
    char number_str[255];
    int number_str_len = 0;
    i = 0;
    stack[0] = 'e';

    while ((ch = (char)fgetc(file)) != -1) {
        if (!char_in_array(ch, NUMBER, size_array(NUMBER)) && number_str_len) {
            printf("%s ", number_str);
            number_str_len = 0;
        }
        if (char_in_array(ch, OPERATION, size_array(OPERATION)))
            {
                while (1)
                {
                    if (priority_char(ch) > priority_char(stack[i]))
                    {
                        i++;
                        stack[i] = ch;
                        break;
                    }
                    else {
                        write_result(stack[i]);
                        i--;
                    }
                }
            continue;
            }

        if (char_in_array(ch, NUMBER, size_array(NUMBER)))
        {
            number_str[number_str_len] = ch;
            number_str[number_str_len + 1] = '\0';
            number_str_len++;
            continue;
        }

        if (char_in_array(ch, OPEN_BRACKET, size_array(OPEN_BRACKET)))
        {
            i++;
            stack[i] = ch;
            continue;
        }

        if (char_in_array(ch, CLOSE_BRACKET, size_array(CLOSE_BRACKET)))
        {
                while (1)
                {
                    if (char_in_array(stack[i], OPEN_BRACKET, size_array(OPEN_BRACKET)))
                    {
                        i--;
                        break;
                    }
                    else
                    {
                        write_result(stack[i]);
                        i--;
                    }
                }
            continue;
        }
    }
    int j;
    for (j = 1; i < j; j++) {
        write_result(stack[i]);
    }
}

int main(int argc, const char *argv[])
{
    FILE * file;
    if (argc > 1)
    {
        file = fopen(argv[1], "r");
    } else {
        file = stdin;
    }
    infix2postfix(file);
    printf("\n");
    return 0;
}

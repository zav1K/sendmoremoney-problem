#include <stdio.h>
#define length(array) ((int)(sizeof(array)/sizeof(array[0])))

/*
problem :
  s e n d
+ m o r e
---------
m o n e y
mapping:
s e n d m o r y
0 1 2 3 4 5 6 7
*/

int send[] = { 0, 1, 2, 3 };
int more[] = { 4, 5, 6, 1 };
int money[] = { 4, 5, 2, 1, 7 };
int values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

int test_proposal() {
    int number1 = 0, number2 = 0, result = 0, i, l;
    if ((values[send[0]] == 0) || (values[more[0]] == 0) || (values[money[0]] == 0)) {
        return 0;
    }

    for (i = 0, l = length(send); i < l; ++i) number1 = number1 * 10 + values[send[i]];
    for (i = 0, l = length(more); i < l; ++i) number2 = number2 * 10 + values[more[i]];
    for (i = 0, l = length(money); i < l; ++i) result = result * 10 + values[money[i]];

    i = (number1 + number2) == result;
    if (i) {
        printf("Solution found!: \n   %4d \n+  %4d \n= %5d", number1, number2, result);
    }
    return i;
}

int free_digits[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int free_digits_count = 10;

int make_proposal(int id) {
    int i, tmp;
    for (i = 0; i < free_digits_count; ++i) {
        tmp = free_digits[i];
        values[id] = tmp;

        if (id + 1 < length(values)) {
            free_digits_count--;
            free_digits[i] = free_digits[free_digits_count];
            free_digits[free_digits_count] = tmp;

            if (make_proposal(id + 1)) return 1;
            free_digits[free_digits_count] = free_digits[i];
            free_digits[i] = tmp;
            free_digits_count++;
        }
        else {
            if (test_proposal()) return 1;
        }
    }
    return 0;
}

int main() {
    int found = make_proposal(0);
    if (!found) {
        printf("No solution found:\n");
    }
}
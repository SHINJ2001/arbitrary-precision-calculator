#include <stdio.h>
#include "bc.h"
#include <string.h>

int main(){

    dll i1 = NULL, i2 = NULL, result = NULL, f1 = NULL, f2 = NULL;
    char string[300], token, *str;
    printf("bc\n");

    start:
    while(scanf("%[^\n]%*c", string) != -1){

        str = string;
        if(!strcmp(string, "quit"))
            return 0;
        while(*str != '\0'){
            token = get_token(str);

            init_string(&str, &i1, &i2, &f1, &f2);

            switch(token){

                case '+':
                
                    result = add(&i1, &i2, &f1, &f2);
                    i1 = result;
                    break;

                case '-':

                    result = subtract(&i1, &i2, &f1, &f2);
                    i1 = result;
                    break;
                
                case '*':
                    result = multiply(&i1, &i2, &f1, &f2);
                    i1 = result;
                    break;

                case '/':
                   result = divide(&i1, &i2);
                   i1 = result;
                   break;

                case '%':
                   result = modulo(&i1, &i2);
                   i1 = result;
                   break;

                case '^':
                   result = exponent(&i1, &i2);
                   i1 = result;
                   break;

                default:
                    printf("(standard_error) syntax error\n");
                    i1 = NULL;
                    i2 = NULL;
                    goto start;
            }

        }
        traverse(result);
        printf("\n");
        i1 = NULL;
        i2 = NULL;
        f1 = NULL;
        f2 = NULL;
    }

    return 0;
}

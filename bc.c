#include <stdio.h>
#include "bc.h"
#include <stdlib.h>

char get_token(char* string){
    
    /*Estimating which operation needs to be performed beforehand*/    
    while(((*string >= '0'&&*string <= '9')||(*string == ' '))&&(*string != '\0')||(*string == '.'))
         string++;
    if(*string == '\0')
        return '$';     /*Return '$' in case no other token found till end of line*/
    return *string; /*Returning the operator character*/

}

void init_string(char **str_input, dll *input1, dll *input2, dll *float1, dll *float2){

    char *str = *str_input, token;
    dll i1 = *input1, q = NULL;

    token = get_token(str);
     if(*input1){                                                               
         *input2 = NULL;
         *float2 = NULL;
         *float1 = NULL;
        while(i1 && (i1 -> data != '.'))
            i1 = i1 -> next;
        

        while(i1){
            if(i1 -> data == '.')
                goto delete;
            append(float1, i1 -> data);
delete:
            q = i1 -> prev;
            if(q)
                q -> next = i1 -> next;
            i1 = i1 -> next;
            if(i1)
                i1 -> prev = q;
        }
         goto in2;         /*Store the next input only in i2 if an operation has 
                             already been performed and result stored in i2*/
     }                                                                          
                                                                                
     while((*str != token) && (*str != ' ') && (*str != '.')){    /*Append the input values in the first linked list*/
         append(input1, *str - '0');       
         str++;
     }
     
     if(*str == '.'){
         str=str+1;
         while((*str != token) && (*str != ' ')){
                 append(float1, *str - '0');
                 str++;
        }
     }

    in2:                                                                       
        while(*str == ' ')                                                         
            str++;                                                                 
                                                                              
        if(*str == token)                                                          
             str+=1;                                                                
                                                                                
        token = get_token(str);               

        /*Append the values in the second linked list*/                                     
        while((*str != token) && (*str != ' ') && (*str != '\0') && (*str != '.')){                     
            append(input2, *str - '0');                       
            str++;
        }

        if(*str == '.'){
            str = str + 1;
            while((*str != token) && (*str != ' ') && (*str != '\0')){
                append(float2, *str - '0');
                str++;
            }
        }
                            
        /*altering the value of the input string upto the point the inputs have
          been stored*/
        *str_input = str;                                                          
        return; 
}

dll add(dll *input1, dll *input2, dll *float1, dll *float2){
    int carry = 0, sum;
    dll a = *input1, b = *input2, result = NULL, f1 = *float1, f2 = *float2;

    if(f1 || f2){

        init_floats(&f1, &f2);

        while (f1 != NULL || f2 != NULL){ /*Evaluate until both lists are empty*/    
                                                                           
            if (f1 != NULL && f2 != NULL){    /*add the values of a and b and store the extra carry in another variable*/
                                                                           
                sum = ((f1 -> data) + (f2 -> data) + carry) % 10;                    
                carry = ((f1 -> data) + (f2 -> data) + carry) / 10;                  
                f1 = f1 -> prev;                                                     
                f2 = f2 -> prev;                                                     
                                                                           
            }                                                                      
            else if (f1 == NULL && f2 != NULL){                                      
                                                                           
                sum = ((f2 -> data) + carry) % 10;                                  
                carry = ((f2 -> data) + carry) / 10;                                
                f2 = f2 -> prev;  /*Evauating the remaining values of b and the carry*/
                                                                           
            }

            else if (f1 != NULL && f2 == NULL){                                      
                                                                           
                sum = ((f1 -> data) + carry) % 10;                                  
                carry = ((f1 -> data) + carry) / 10;                                
                f1 = f1 -> prev;  /*Evaluating the remaining values of a and the carry*/
                                                                           
            }                                                                      
                                                                           
            // Inserting the sum digit                                             
            insert(&result, sum, 0);                                               
        }                                                                          
                                                                           
        insert(&result, '.', 0);
    }
    

    while(a -> next != NULL)
        a = a -> next;

    while(b -> next != NULL)
        b = b -> next;

    while (a != NULL || b != NULL){ /*Evaluate until both lists are empty*/

        if (a != NULL && b != NULL){    /*add the values of a and b and store the extra carry in another variable*/

            sum = ((a -> data) + (b -> data) + carry) % 10;
            carry = ((a -> data) + (b -> data) + carry) / 10;
            a = a -> prev;
            b = b -> prev;

        }
        else if (a == NULL && b != NULL){   

            sum = ((b -> data) + carry) % 10;
            carry = ((b -> data) + carry) / 10;
            b = b -> prev;  /*Evauating the remaining values of b and the carry*/

        }
        else if (a != NULL && b == NULL){

            sum = ((a -> data) + carry) % 10;
            carry = ((a -> data) + carry) / 10;
            a = a -> prev;  /*Evaluating the remaining values of a and the carry*/

        }

        // Inserting the sum digit
        insert(&result, sum, 0);    
    }

    // Inserting last carry
    if (carry != 0)
        insert(&result, carry, 0);
    return result;

}

dll subtract(dll *input1, dll* input2, dll *float1, dll *float2){
    int borrow = 0, diff;
    dll a = *input1, b = *input2, result = NULL, f1 = *float1, f2 = *float2;
    
    if(f1 || f2){
        init_floats(&f1, &f2);
        
        while (f1 != NULL || f2 != NULL){

            if (f1 != NULL && f2 != NULL){

                if ((f1 -> data) + borrow >= (f2 -> data)){

                    diff = ((f1 -> data) + borrow - (f2 -> data));    /*Directly subracting the values when value in a is greater than that in b
                                                                    and storing them in diff*/
                    borrow = 0;     /*Nothing borrowed in this case*/
                }
            
                else{

                    diff = ((f1 -> data) + borrow + 10 - (f2 -> data));   /*Otherwise borrow 10 from previous digit*/
                    borrow = -1;    /*And set borrow to -1*/
                }
                f1 = f1 -> prev;
                f2 = f2 -> prev;
            }
            else if (f1 != NULL && f2 == NULL){

                if (f1 -> data >= 1){

                    diff = ((f1 -> data) + borrow);  /*In case a not empty, store the value of a and add borrow if any remaining in diff*/
                    borrow = 0;

                }
                else{

                    if (borrow != 0){   

                        diff = ((f1 -> data) + 10 + borrow);     /*if a = 0 and borrow remaining, add 10 and borrow and store in diff*/
                        borrow = -1;
                    }
                    else
                        diff = f1 -> data;
                }

                f1 = f1 -> prev;      
            }
            insert(&result, diff, 0);

        }
        insert(&result, '.', 0);
    }

    /*Traversing to end of lists*/
    while(a -> next != NULL)
        a = a -> next;
    while(b -> next != NULL)
        b = b -> next;

    while (a != NULL || b != NULL){

        if (a != NULL && b != NULL){

            if ((a -> data) + borrow >= (b -> data)){

                diff = ((a -> data) + borrow - (b -> data));    /*Directly subracting the values when value in a is greater than that in b
                                                                    and storing them in diff*/
                borrow = 0;     /*Nothing borrowed in this case*/
            }
            else{

                diff = ((a -> data) + borrow + 10 - (b -> data));   /*Otherwise borrow 10 from previous digit*/
                borrow = -1;    /*And set borrow to -1*/
            }
            a = a -> prev;
            b = b -> prev;
        }
        else if (a != NULL && b == NULL){

            if (a -> data >= 1){

                diff = ((a -> data) + borrow);  /*In case a not empty, store the value of a and add borrow if any remaining in diff*/
                borrow = 0;

            }
            else{

                if (borrow != 0){   

                    diff = ((a -> data) + 10 + borrow);     /*if a = 0 and borrow remaining, add 10 and borrow and store in diff*/
                    borrow = -1;
                }
                else
                    diff = a -> data;
            }

            a = a -> prev;      
        }
        insert(&result, diff, 0);

    }

    return result;
}

dll multiply(dll *input1, dll *input2, dll *float1, dll *float2){
    int k = 0, i, size = 0, sum = 0, carry = 0, size2 = 0;
    dll a = *input1, b = *input2, temp = NULL, product = NULL, result = NULL, null = NULL, f1 = *float1, f2 = *float2;
    append(&result, 0);
  
    if(f1 || f2){

        while(f1){
            f1 = f1 -> next;
            size++;
        }
        
        while(f2){
            f2 = f2 -> next;
            size++;
        }
    }
    /*Traversing to end of lists*/
    while(a -> next != NULL)
        a = a-> next;
    while(b -> next != NULL)
        b = b -> next;
    
    a -> next = *float1;
    b -> next = *float2;
    if(*float1)                       //Appending float lists to end of integer lists
        (*float1) -> prev = a;
    if(*float2)
        (*float2) -> prev = b;

    while(a -> next != NULL){
        a = a-> next;
    }

    while(b -> next != NULL){
        b = b -> next;
    }
    
    while (b != NULL){

        carry = 0;
        sum = 0;
        temp = a;/*Setting temp back to a everytime the previous multiplication completed*/

        while (temp != NULL){

            sum = ((temp -> data) * (b -> data) + carry) % 10;
            carry = ((temp -> data) * (b -> data) + carry) / 10;
            insert(&product, sum, 0);
            temp = temp -> prev;
        
        }

        if (carry != 0)
            insert(&product, carry, 0); /*Insert carry in the beginning*/

        for (i = 0; i < k; i++)
            append(&product, 0);    /*Equivalent to multiplying by power of ten, where the power is 'one' more than the last iteration*/

        result = add(&result, &product, &null, &null);
        product = NULL;     /*Setting the product back to NULL for next multiplication*/

        k++;

        b = b -> prev;
    }

    temp = result;
    
    while(temp){        //Calculating the length of the list to calculate where the point(.) needs to be inserted 
        temp = temp -> next;
        size2++;
    }

    if(size)
        insert(&result, '.', size2 - size);
    return result;
}

dll divide(dll *input1, dll* input2){

    int i = 0, size_b = 0;
    dll a = *input1, b = *input2, null = NULL, ex = NULL, mp = NULL, pr = NULL, b2 = b, result = NULL, temp = NULL, zero = NULL;
    append(&zero, 0);
   
    if(!cmp(b, zero)){
        printf("Cant divide by zero");
        return null;
    }

    while (b2){     //Calculating the size of the list
        b2 = b2 -> next;
        size_b++;
    }

    for(i = 0; i < size_b; i++) {
        append(&ex, a -> data);
        a = a -> next;
    }

    for (i = 0; i < 10; i++) {

        b2 = b;
        append(&mp, i);     //Calculating the divisor for the first part
        pr = multiply(&b2, &mp, &null, &null);
        if (!cmp(ex, pr))
            break;
        mp = NULL;
        pr = NULL;
    }

    mp = NULL;
    pr = NULL;
    
    append(&mp, i - 1);
    pr = multiply(&b2, &mp, &null, &null);
    ex = subtract(&ex, &pr, &null, &null);
    append(&result, i - 1);
    mp = NULL;
    pr = NULL;
    
    while (a != NULL) {

        append(&ex, a -> data);

        while (ex&&(ex -> data == 0)) {

            ex = ex -> next;

        }
        for (i = 0; i < 10; i++) {
            b2 = b;
            append(&mp, i);
            pr = multiply(&b2, &mp, &null, &null);
            temp = pr;
            if(!ex){
                while(temp && (temp -> data == 0)){
                    append(&ex, 0);
                    temp = temp -> next;
                }
            }

            if (!cmp(ex, pr))
                break;
            mp = NULL;
            pr = NULL;
        }

        mp = NULL;
        pr = NULL;
        append(&mp, i - 1);
        pr = multiply(&b2, &mp, &null, &null);
        ex = subtract(&ex, &pr, &null, &null);
        append(&result, i - 1); 

        mp = NULL;
        pr = NULL;

        a = a -> next;
    }
    
    return result;
}

int cmp(dll a, dll b){
    int size1 = 0, size2 = 0;
    dll a1 = a, b1 = b;
    while(a1){
        a1 = a1 -> next;
        size1++;
    }

    while(b1){
        b1 = b1 -> next;
        size2++;
    }

    if(size1 != size2)
        return ((size1 > size2) ? 1 : 0);
    else{
        while(a && b){
            if(a -> data > b -> data){
                return 1;
            }
            else if (a -> data < b -> data)
                return 0;
            else{
                a = a -> next;
                b = b -> next;
            }
        }
    
        return 2;
    }
}


void init_floats(dll *float1, dll *float2){
    dll f1 = *float1, f2 = *float2;
    int size1 = 0, size2 = 0;

    if(f1){
        while(f1 -> next != NULL){
            f1 = f1 -> next;
            size1++;
        }
    }

    if(f2){
        while(f2 -> next != NULL){
            f2 = f2 -> next;
            size2++;
        }
    }

     while(size1 > size2){
        append(float2, 0);
        f2 = f2 -> next;
        size1--;
    }

    while(size1 < size2){
        append(float1, 0);
        f1 = f1 -> next;
        size2--;
    }
    *float1 = f1;
    *float2 = f2;
    return;
}

dll modulo(dll *input1, dll *input2){
    int i = 0, size_b = 0;
    dll a = *input1, b = *input2, null = NULL, ex = NULL, mp = NULL, pr = NULL, b2 = b, result = NULL, temp = NULL;
    
    while (b2){
        b2 = b2 -> next;
        size_b++;
    }

    for(i = 0; i < size_b; i++) {
        append(&ex, a -> data);
        a = a -> next;
    }

    for (i = 0; i < 10; i++) {

        b2 = b;
        append(&mp, i);
        pr = multiply(&b2, &mp, &null, &null);
        if (!cmp(ex, pr))
            break;
        mp = NULL;
        pr = NULL;
    }

    mp = NULL;
    pr = NULL;
    
    append(&mp, i - 1);
    pr = multiply(&b2, &mp, &null, &null);
    ex = subtract(&ex, &pr, &null, &null);
    append(&result, i - 1);
    mp = NULL;
    pr = NULL;
    
    while (a != NULL) {

        append(&ex, a -> data);

        while (ex&&(ex -> data == 0)) {

            ex = ex -> next;

        }
        for (i = 0; i < 10; i++) {
            b2 = b;
            append(&mp, i);
            pr = multiply(&b2, &mp, &null, &null);
            temp = pr;
            if(!ex){
                while(temp && (temp -> data == 0)){
                    append(&ex, 0);
                    temp = temp -> next;
                }
            }

            if (!cmp(ex, pr))
                break;
            mp = NULL;
            pr = NULL;
        }

        mp = NULL;
        pr = NULL;
        append(&mp, i - 1);
        pr = multiply(&b2, &mp, &null, &null);
        ex = subtract(&ex, &pr, &null, &null);
        append(&result, i - 1); 

        mp = NULL;
        pr = NULL;

        a = a -> next;
    }
    
    return ex;
}

dll exponent(dll *input1, dll *input2){

    dll a = *input1, b = *input2, result = NULL, c = NULL, inc = NULL, null = NULL;
    append(&result, 1);
    append(&c, 0);
    append(&inc, 1);

    while(cmp(c, b) != 2){

        result = multiply(&result, &a, &null, &null);
        c = add(&c, &inc, &null, &null);

    }

    return result;

}

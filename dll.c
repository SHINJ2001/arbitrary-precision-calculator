#include <stdlib.h>
#include "dll.h"
#include <stdio.h>

void init_list(dll *L){

    *L = NULL;
    
    return;

}

void append(dll *L, int d){

    dll q = NULL, p = *L;
   
    if (!p){

        p = (node*)malloc(sizeof(node));
 
        p -> next = NULL;

        p -> data = d;
 
        p -> prev= q;

        *L = p;

        return;

    }

    while(p -> next){
        
        p = p -> next;
        
    }

    q = p;

    p -> next = (node*)malloc(sizeof(node));

    p = p -> next;

    p -> data = d;

    p -> prev= q;

    p -> next = NULL;

    return;

}

int delete_element(dll *L, int d){

    dll p = *L;
    
    if (!(p)){

        printf("List empty \n");
        return 1;
    }

    while (p&&( p -> data != d)){

        p = p -> next;

    }
  
    if (!p){

        printf("Element not found \n");

        return 1;
    
    }

    dll  q = p -> prev;

    if (p -> prev== NULL){
        
        *L = p -> next;

        (*L) -> prev= NULL;

    }

    else if (p){

        q -> next = p -> next;
   
        if (p -> next){

            p = p -> next;

            p -> prev= q;

            return 0;

        }

    
   }
    else{

        *L = p -> next;

        (*L) -> prev= NULL;

    }
    return 0;

}

void traverse(dll L){

   dll p = L;

   printf("\n");
   while (p){ 

       if(p -> data == '.')
           break;
       printf("%d", p -> data);

       p = p -> next;

    }

   if(p){
       if(p -> data == '.'){
            printf(".");
            p = p -> next;
            while(p){
                printf("%d", p -> data);
                p = p -> next;
            }
        }
   }
}

int search(dll L, int d){

    int position = 0;
    
    while ((L -> next)&&(L -> data != d)){

        L = L -> next;

        position ++;

}

    if (L -> data == d)
        
        return position;

    else

        return 0;

}

void sort(dll *l){

    dll index = NULL, current = NULL;

    int temp;

    for(current = *l; current -> next != NULL; current = current -> next){

        for( index = current -> next; index != NULL; index = index -> next){

            if(current -> data > index -> data){

                temp = current -> data;

                current -> data = index -> data;

                index -> data =  temp;
            }
        }
    }
    return;
}

void replace(dll *l, int element, int data){

    dll p = *l;

    while( p -> data != element){

        p = p -> next;

        if(!p){

            printf("Element not found\n Hence could not be replaced\n");
            
            return;
        
        }

    }

    p -> data = data;

    return;
}

void reverse(dll *l){

    dll p = (dll)malloc(sizeof(node));
    
    p -> prev= NULL;

    p -> next = NULL;

    dll n = *l;
    
    dll q, original = p;

    while((n -> next) != NULL)
        
        n = n -> next;

    while( n != NULL){

        p -> data = n -> data;

        if ( n -> prev!= NULL){
            
            p -> next = (dll)malloc(sizeof(node));

            q = p;

            p = p -> next;

            p -> prev= q;

            p -> next = NULL;

            n = n -> prev;
        
        }
        else
            break;
    
    }
    *l = original;

    return;

}

void delete_all(dll *l, int data){

    dll p = *l, nn = NULL;

    while(delete_element( l, data) != 1){;}

    return;

}

void insert(dll *l, int data, int position){

    dll p = *l, q, nn = NULL;

    while(position != 0){

        p = p -> next;

        position--;

    }
    if( p == NULL){

        append(l, data);

    }

    else if( p -> prev== NULL){

        nn = (dll)malloc(sizeof(node));

        nn -> data = data;

        nn -> prev= NULL;

        nn -> next = p;

        *l = nn;

        p -> prev= nn;

    }

    else{

        nn = (dll)malloc(sizeof(node));

        nn -> data = data;

        nn -> next = p;
        
        q = p -> prev;

        p -> prev= nn;

        q -> next = nn;

        nn -> prev= q;

    }

    return;

}

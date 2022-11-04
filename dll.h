typedef struct node{

    int data;
    struct node* prev;
    struct node* next;

}node;

typedef node* dll;

void append(dll *l, int data);
void insert(dll *l, int data, int position);
int search(dll l, int data);
int delete_element(dll *l, int data);
void sort(dll *l);
void delete_all(dll *l, int data);
void replace(dll *l, int element, int data);
void reverse(dll *l);
void traverse(dll l);

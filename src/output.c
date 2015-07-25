#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct result_node{
    char *value;
    struct result_node * next;
} node;

typedef struct {
  int col_size;
  int * col_lengthes;
  struct result_node * node;
} resultset;

node * add_node(char * value, struct result_node * tail, int len){
    struct result_node * node = (struct result_node *)malloc( sizeof(struct result_node) );
    node->value = (char *)malloc(len);
    strcpy(node->value, value);
    node->next = NULL;
    if(tail != NULL){
        tail->next = node;
    }
    return node;
}

void _print_result(struct result_node * node, int * col_length, int col_size);
void _print_boundary(int * col_length, int col_size);
int main (){
  int a[4] = {1,2,3,6};
  _print_boundary(a, 4);

  struct result_node * head = NULL;
  struct result_node * temp = NULL;
  temp = add_node("h", temp, 1024);
  head = temp;
  temp = add_node("ho", temp, 1024);
  temp = add_node("hog", temp, 1024);
  temp = add_node("hoge", temp, 1024);

  struct result_node * head2 = NULL;
  struct result_node * temp2 = NULL;
  temp2 = add_node("1", temp2, 1024);
  head2 = temp2;
  temp2 = add_node("wo", temp2, 1024);
  temp2 = add_node("yos", temp2, 1024);
  temp2 = add_node("hoge", temp2, 1024);
  temp2 = add_node("2", temp2, 1024);
  temp2 = add_node("ho", temp2, 1024);
  temp2 = add_node("hog", temp2, 1024);
  temp2 = add_node("あい", temp2, 1024);

  _print_result(head, a, 4);
  _print_boundary(a, 4);
  _print_result(head2, a, 4);
  _print_boundary(a, 4);
  return 1;
}



void _print_boundary(int * col_length, int col_size){
    int col = 0;
    int i = 0;
    for( col=0; col < col_size; col++){
        printf("+");
        for(i=0; i<col_length[col] +2; i++){
          printf("-");
        }
    }
    printf("+\n");
}

void _print_result(struct result_node * node, int * col_length, int col_size){
    int col = 0;
    int i = 0;
    struct result_node * it = node;
    while(it != NULL ){
        printf("| %s", it->value);
        for(i =0; i<(col_length[col] - strlen(it->value)) ; i++){
            printf(" ");
        }
        printf(" ");
        it = it->next;
        if(col >= col_size -1){
          col=0;
          printf("|\n");
        }else{
          col++;
        }
    }
}

void print_normal(struct result_node * hnode, struct result_node * node, int * max_col_size, int col_size){
      _print_boundary(max_col_size, col_size);
      _print_result(hnode, max_col_size, col_size);
      _print_boundary(max_col_size, col_size);
      _print_result(node, max_col_size, col_size);
      _print_boundary(max_col_size, col_size);
}

void print_pretty(struct result_node * hnode, struct result_node * node, int max_col_size, int col_size){
    int col = 0;
    int i=0;
    struct result_node * it = node;
    struct result_node * ht; 

    while(it != NULL ){
        if(col % col_size == 0){
            ht = hnode; 
            printf("*************************** %d. row ***************************\n", (col/col_size)+1);
        }
        for(i =0; i<(max_col_size - strlen(ht->value)) ; i++){
            printf(" ");
        }
        printf("%s : %s\n", ht->value, it->value);
        it = it->next;
        ht = ht->next;
        col++;
    }
}

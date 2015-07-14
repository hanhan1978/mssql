#include <stdio.h>
#include <string.h>

#include "mssql.h"

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

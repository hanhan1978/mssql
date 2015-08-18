/** @file
 * output.c 
 *
 * define functions related to output query result
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mssql.h"


//private funcs
void _print_pretty(struct result_set * res);
void _print_normal(struct result_set * res);
void _print_normal_result(struct result_node * node, int * col_length, int col_size);
void _print_normal_boundary(int * col_length, int col_size);

//public
void print_result(struct result_set * res){
  if(res->rows == 0 && res->hnode == NULL){
    return;
  }
  if(pretty_print){
      _print_pretty(res);
  }else{
      _print_normal(res);
  }
  if(res->rows > 0){
      printf("\n%d %s in set\n\n", res->rows, res->rows <= 1 ? "row" : "rows");
  }else{
      printf("Empty set\n\n");
  }
}

void _print_normal_boundary(int * col_length, int col_size){
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

void _print_normal_result(struct result_node * node, int * col_length, int col_size){
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


void _print_normal(struct result_set * res){
      _print_normal_boundary(res->each_collen, res->colnum);
      _print_normal_result(res->hnode, res->each_collen, res->colnum);
      _print_normal_boundary(res->each_collen, res->colnum);
      _print_normal_result(res->node, res->each_collen, res->colnum);
      _print_normal_boundary(res->each_collen, res->colnum);
}


void _print_pretty(struct result_set * res){
    int col = 0;
    int i=0;
    int max_col_size = 0;
    struct result_node * it = res->node;
    struct result_node * ht = res->hnode; 

    while(ht != NULL){
      max_col_size = (max_col_size < strlen(ht->value))? strlen(ht->value) : max_col_size;
      ht = ht->next;
    }

    while(it != NULL ){
        if(col % res->colnum == 0){
            ht = res->hnode; 
            printf("*************************** %d. row ***************************\n", (col/res->colnum)+1);
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

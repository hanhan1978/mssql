#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mssql.h"


//private
void _free_result(struct result_node *node);

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


void _free_result(struct result_node *node){
    struct result_node * it = node;
    struct result_node * nxt;
    while(it != NULL ){
        free(it->value);
        nxt = it->next;
        free(it);
        it = nxt;
    }
}

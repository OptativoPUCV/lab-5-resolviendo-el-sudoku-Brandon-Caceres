#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i,k,j;
    
    for (i = 0; i < 9; i++){
        for (k = 0; k < 9; k++){
          if (n->sudo[i][k] != 0){
              for (j = k + 1; j < 9; j++) {
                    if (n->sudo[i][k] == n->sudo[i][j]) {
                        return 0;
                    }
              }
          }
        }
    }

    for (k = 0; k < 9; k++) {
        for (i = 0; i < 9; i++) {
            if (n->sudo[i][k] != 0) {
                for (j = i + 1; j < 9; j++) {
                    if (n->sudo[j][k] == n->sudo[i][k]) {
                        return 0;
                    }
                }
            }
        }
    }

    for (i = 0; i < 9; i++) {
        for (k = 0; k < 9; k++) {
            for (j = 0; j < 9; j++) {
                int x = 3 * i + j / 3;
                int y = 3 * k + j % 3;
                if(n->sudo[x][y] == 0) continue;
                for (int p = j + 1; p < 9; p++){
                    int x2 = 3 * i + p / 3;
                    int y2 = 3 * k + p % 3;
                    if (n->sudo[x][y] == n->sudo[x2][y2]) return 0;
                }
            }
        }
    }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();

    int i,k,j;
    for (i = 0; i < 9; i++){
        for (k = 0; k < 9; k++){
            if (n->sudo[i][k] == 0){
                for (j = 1; j <= 9; j++){
                    Node* nuevo = copy(n);
                    nuevo->sudo[i][k] = j;
                    if (is_valid(nuevo)) pushBack(list, nuevo);
                    else return list;
                }
            }
        }
    }
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/
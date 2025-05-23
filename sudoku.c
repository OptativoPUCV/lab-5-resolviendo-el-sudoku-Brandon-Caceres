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
    int i,k,j,p;
    
    for (i = 0; i < 9; i++){
        int bandera[10] = {0};
        for (k = 0; k < 9; k++){
            int aux = n->sudo[i][k];
            if (aux != 0){
                if (bandera[aux]) return 0;
                bandera[aux] = 1;
          }
        }
    }

    for (i = 0; i < 9; i++){
        int bandera[10] = {0};
        for (k = 0; k < 9; k++){
            int aux = n->sudo[k][i];
            if (aux != 0){
                if (bandera[aux]) return 0;
                bandera[aux] = 1;
          }
        }
    }

    for (i = 0; i < 9; i++) {
        int bandera[10] = {0};
        for (k = 0; k < 9; k++) {
            p = 3 * (i / 3) + (k / 3);
            j = 3 * (i % 3) + (k % 3);
            int val = n->sudo[p][j];
            if (val != 0) {
                if (bandera[val]) return 0;
                bandera[val] = 1;
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
                    else free(nuevo);
                }
                return list;
            }
        }
    }
    return list;
}


int is_final(Node* n){
    for (int i = 0; i < 9; i++){
        for (int k = 0; k < 9; k++){
            if (n->sudo[i][k] == 0) return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack* pila = createStack();
    push(pila, initial);

    while (!is_empty(pila)){
        Node* valor = top(pila);
        pop(pila);
        (*cont)++;
        if (is_final(valor)) return valor;

        List* adyacentes = get_adj_nodes(valor);
        Node* aux = first(adyacentes);
        while (aux != NULL){
            push(pila, aux);
            aux = next(adyacentes);
        }
        free(valor);
        free(aux);
    }
    return NULL;
}




/*int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct elementolista // crio a struct base da lista
{
    int val;
    struct elementolista *next; // ponteiro para struct, que criará o próximo nó da lista
};

typedef struct elementolista item; 

void add (item *cabeca, int val){ // função para adicionar itens na lista
    item*novo = (item*)malloc(sizeof(item)); // aloca espaço de memória para o novo nó
    novo->next= NULL; // define o nó como ulitmo, uma vez que seu next é nulo
    novo->val= val ; // define val como o val do nó

    item *atual = cabeca; // define um ponteiro para struct que representará o cursor 
    while (atual->next!=NULL)
    {
        atual= atual->next;
    }
    
    atual->next=novo;
    

}
void imprimir (item *cabeca){
    item*atual= cabeca;
    atual =  atual->next;

    for (int i=0; atual!=NULL;i++){
        printf("%3d\n",atual->val);
        atual=atual->next;
    }
}
void liberar (item*cabeca){
    item*atual=cabeca->next;
    while (atual!=NULL)
    {
        item*prox= atual->next;
        free(atual);
        atual=prox;
    }
    
}
int main () {
    item cabeca;
    cabeca.next=NULL;

    add(&cabeca, 30);
    add(&cabeca, 55);
    imprimir(&cabeca);

    liberar (&cabeca);

    return 0;

}

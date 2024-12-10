
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


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

item *find (item*cabeca,size_t pos){
        item *cursor = cabeca;
        size_t i = 0;
        while (i<pos)
        {
            cursor= cursor->next;
            i++;
        }
        return cursor;


}

item *achar (item *cabeca,int val){
    item*atual= cabeca;
    while (atual->next!=NULL && atual->next->val!=val)
    {
        atual= atual->next;
    }
    return atual;


}



int main () {
    item cabeca;
    cabeca.next=NULL;

    add(&cabeca, 30);
    add(&cabeca, 55);
    add(&cabeca, 550);
    imprimir(&cabeca);

    item *node2=NULL;
    node2 = find (&cabeca,1);
    printf("list[%d]=%d\n" ,2,node2->next->val);



    liberar(&cabeca);

    return 0;

}

#include "my_lib.h"

int main(){
    void *data;
    struct my_stack  *st = my_stack_init(1);
    my_stack_push(st,data);
    my_stack_push(st,data);
    int l = my_stack_len(st);
    printf("Current length: %d\n", l);
    l = my_stack_purge(st);
    printf("Bytes erased: %d\n", l);
}

size_t my_strlen(const char *str){
    size_t size = 0;
    while (*(str++)){
        size++;
    }
    return size;
}

char *my_strcpy(char *dest, const char *src){
    size_t len = my_strlen(src);
    for (size_t i = 0; i < len; i++){
        *(dest + i) =*(src + i);
    }
    *(dest + len) = '\0';
    return dest;
}

int my_strcmp(const char *str1, const char *str2){
    size_t len1 =  my_strlen(str1);
    size_t len2 = my_strlen(str2);
    int cmp = 0;
    for (size_t i = 0; cmp == 0 && i < len1 && i < len2; i++){
        cmp = *(str1 + i) - *(str2 + i);
    }
    return cmp;
}

char *my_strncpy(char *dest, const char *src, size_t n){
    size_t i = 0;
    for (i; i < n && *(src + i) != '\0'; i++){
        *(dest + i) = *(src + i);
    }
    while (i < n){
        *(dest + i) = '\0';
        i++;
    }
    return dest;
}

char *my_strcat(char *dest, const char *src){
    size_t i = my_strlen(dest);
    size_t j = my_strlen(src);
    for (size_t k = 0; k < j; k++){
        *(dest + i) = *(src+k);
        i++;
    }
    *(dest + i) = '\0';
    return dest;
}

struct my_stack *my_stack_init(int size){
    struct my_stack *newStackPile = malloc(sizeof(struct my_stack));
    if (!newStackPile){
        puts("Error: no hay suficiente memoria dinámica.");
        return NULL;
    }
    newStackPile->size = size;
    newStackPile->first = NULL;
    return newStackPile;
}

int my_stack_push(struct my_stack *stack, void *data){
    if (stack!=NULL && stack->size > 0){
        struct my_stack_node *newNode = malloc(sizeof(struct my_stack_node));
        if (!newNode){
            puts("Error: no se pudo crear un nuevo nodo");
            return EXIT_FAILURE;
        }
        newNode->data = data;
        newNode->next = stack->first;
        stack->first = newNode;
    }else{
        puts("Error: no existe el stack o el tamaño del dato es menor o igual a 0");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void *my_stack_pop(struct my_stack *stack){
    if (stack->first == NULL){
        puts("Error: la pila no tiene nodos");
        return NULL;
    }else{
        void *dataPointer;
        struct my_stack_node *nodePointer = stack->first;
        dataPointer = nodePointer->data;
        stack->first = nodePointer->next;
        free(nodePointer);
        return dataPointer;
    }
}

int get_stack_len(struct my_stack_node *node){
    if (!node){
        return 0;
    }else{
        return get_stack_len(node->next) + 1;
    }
}

int my_stack_len(struct my_stack *stack){
    if (!stack){
        puts("Error: la pila no está inicializada");
        return NULL;
    }
    int stackLen = get_stack_len(stack->first);
    return stackLen;
}

void *get_Something(){

}

int my_stack_purge(struct my_stack *stack){
    int result = 0;
    if (!stack){
        puts("Error: la pila no está inicializada");
        return NULL;
    } else{
        int size = sizeof(struct my_stack_node);
        struct my_stack_node *node = stack->first;
        while (node){
            my_stack_pop(stack);
            node = stack->first;
            result += size;
        }
        free(stack);
        result += sizeof(struct my_stack);
    }
    return result;
}
#include "my_lib.h"
/*
int main(){
    void *data;
    struct my_stack  *st = my_stack_init(21);
    my_stack_push(st,data);
    my_stack_push(st,data);
    int l = my_stack_len(st);
    printf("Current length: %d\n", l);
    l = my_stack_purge(st);
    printf("Bytes erased: %d\n", l);
}
*/
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
    size_t i;
    for (i = 0; i < n && *(src + i) != '\0'; i++){
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
        return -1;
    }
    int stackLen = get_stack_len(stack->first);
    return stackLen;
}

int my_stack_purge(struct my_stack *stack){
    int result = 0;
    if (!stack){
        puts("Error: la pila no está inicializada");
        return -1;
    } else{
        void *dataPointer;
        int nodeSize = sizeof(struct my_stack_node);
        struct my_stack_node *node = stack->first;
        while (node){
            dataPointer = my_stack_pop(stack);
            node = stack->first;
            free(dataPointer);
            result += stack->size;
            result += nodeSize;
        }
        free(stack);
        result += sizeof(struct my_stack);
    }
    return result;
}

struct my_stack *my_stack_read(char *filename){
    int fd = open(filename, O_RDONLY);
    printf("%d", fd);
    if (fd > 0){
        int size;
        if(read(fd,&size,sizeof(int))> 0){
            struct my_stack *newStack = my_stack_init(size);
            void *dataPointer = malloc(size);
            while (read(fd,dataPointer,size)>0){
                my_stack_push(newStack,dataPointer);
                dataPointer = malloc(size);
            }
            free(dataPointer);
            if (close(fd) < 0) {
                puts("Error: el archivo no pudo ser cerrado");
                return NULL;
            }
            return newStack;
        }else{
            puts("Error: no contiene nada el archivo");
            return NULL;
        }   
    }else{
        puts("Error: El archivo no se pudo leer");
        return NULL;
    }
}

int write_nodes(int fileID,int size, struct my_stack_node *node){
    int totalSize = 0;
    if (!node){
        return totalSize;
    }
    totalSize = write_nodes(fileID ,size, node->next);
    write(fileID,node->data,size);
    return totalSize + 1;
}

int my_stack_write(struct my_stack *stack, char *filename){
    if (!stack){
        puts("Error: la pila no esta inicializada");
        return -1;
    }
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd > 0){
        write(fd,&stack->size,sizeof(int));
        int nNodes = write_nodes(fd,stack->size,stack->first);
        if(close(fd) < 0){
            puts("Error: el archivo no pudo ser cerrado");
            return -1;
        }
        return nNodes;
    }else{
        puts("Error: no se pudo escribir en el file");
        return -1;
    }   
}
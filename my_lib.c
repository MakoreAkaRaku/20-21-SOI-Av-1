#include "my_lib.h"

int main(){
    char prova[] = "Hello world";
    char newStr[45];
    my_strcpy(newStr,prova);
    printf("%s", newStr);
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
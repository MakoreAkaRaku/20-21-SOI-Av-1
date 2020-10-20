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
int my_strcmp(const char *str1, const char *str2){
    size_t len1 =  my_strlen(str1);
    size_t len2 = my_strlen(str2);
    int cmp = 0;
    for (size_t i = 0; cmp == 0 && i < len1 && i < len2; i++)
    {
        cmp = *(str1 + i) - *(str2 + i);
    }
    return cmp;
}
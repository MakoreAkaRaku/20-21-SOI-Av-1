#include "my_lib.h"

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
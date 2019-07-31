#include <stdio.h>
int main() {
    char txt[3] = "hey";
    char* ptr = txt;
    
    char otherstuff[10] = "other";
    //*(ptr + 4) = 'c';

    printf("original: %s\n", txt);
    for(int i = 0; i < 5; i++) {
        printf("%c\n", *ptr);
        printf("%c\n", txt[i]);
        ptr++;
    }
}
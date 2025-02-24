// adicione: /build/teste.o
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
/*./build/teste.o: ./teste.c
	gcc ./teste.c ${INCLUDES} -o ./build/teste.o -g -c*/
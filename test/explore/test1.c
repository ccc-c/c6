#include <stdio.h>
#include <fcntl.h>

int main() {
    printf("O_BINARY=%o\n", O_BINARY);
    printf("O_CREAT|O_WRONLY|O_TRUNC|O_BINARY=%o\n", O_CREAT|O_WRONLY|O_TRUNC|O_BINARY);
    printf("O_BINARY|O_RDONLY=%o\n", O_BINARY|O_RDONLY);
}

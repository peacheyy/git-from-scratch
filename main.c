#include <stdio.h>
#include <string.h>

struct blob {
    char file_name[100];
};

int main() {
    struct blob bl1;
    strcpy(bl1.file_name, "test.txt");

    FILE *file;
    char buffer[100];
    size_t bytesRead;

    file = fopen(bl1.file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer) - 1, file)) > 0) {
        buffer[bytesRead] = '\0';

        printf("%s", buffer);
    }

    fclose(file);

    return 0;
}
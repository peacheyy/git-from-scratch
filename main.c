#include <stdio.h>
#include <stdint.h>
#include <string.h>

extern int sha1digest(uint8_t *digest, char *hexdigest, const uint8_t *data, size_t databytes);

struct blob
{
    char file_name[100];
    char blob_hash[41];
};

void generatehex(char *hexdigest, uint8_t *digest)
{
    int idx;

    for (idx = 0; idx < 20; idx++)
    {
        sprintf(hexdigest + (idx * 2), "%02x", digest[idx]);
    }
    hexdigest[40] = '\0';
}

int main()
{
    struct blob bl1;
    strcpy(bl1.file_name, "test.txt");

    FILE *file;
    char buffer[1024];
    size_t bytesRead;
    size_t totalBytes = 0;
    uint8_t digest[20];

    file = fopen(bl1.file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    bytesRead = fread(buffer, 1, sizeof(buffer), file);
    totalBytes = bytesRead;

    fclose(file);

    sha1digest(digest, NULL, buffer, totalBytes);

    generatehex(bl1.blob_hash, digest);

    printf("SHA-1 hash: %s\n", bl1.blob_hash);

    return 0;
}
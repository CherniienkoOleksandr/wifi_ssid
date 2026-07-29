#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
    FILE *f = fopen("./known", "rwa");
    if (f == NULL) {
        perror("failed to open file");
        return 1;
    }
    char line[100] = {};
    fgets(line, 100, f);
    printf("%s", line);
    fgets(line, 100, f);
    printf("%s", line);
    fclose(f);
    return 0;
}

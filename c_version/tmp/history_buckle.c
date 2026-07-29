#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "./history"

int line_counter(FILE *file);
void line_cutter(FILE *file);

int main(void) {
    FILE *F;
    F = fopen(FILE_NAME, "r");
    if (F == NULL) {
        perror("file problem");
        return 1;
    }

    int quantite_lines = line_counter(F);
    printf("%d\n", quantite_lines);
    line_cutter(F);

    fclose(F);
    return 0;
}

void line_cutter(FILE *file) {
    rewind(file);
    char *str = malloc(100 * sizeof(char));
    char buf[100];

    while ((fgets(buf, 100, file)) != NULL) {
        // printf("%s", buf);
        str = buf;
        printf("%s", str);
    }
    free(str);

    return;
}

int line_counter(FILE *file) {
    int count = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            count++;
            continue;
        }
    }

    return count;
}

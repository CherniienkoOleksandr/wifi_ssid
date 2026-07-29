#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *f = fopen("history", "r");
    if (f == NULL) {
        perror("File error");
        return 1;
    }

    char line[80] = {};
    char l[20] = {};
    char w[20] = {};
    char s[20] = {};

    // fscanf(f, "%s %s %s", &l, &w, &s);
    int c;
    for (int i = 0; i < 20; i++) {
        while ((c = getchar()) != ' ')
            l[i] = c;
    }
    printf("line:%s\n", l);
    printf("Word:%s\n", l);
    printf("Symbol:%s\n", l);
    fclose(f);

    return 0;
}

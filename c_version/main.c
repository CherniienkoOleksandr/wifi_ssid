#include <stdio.h>

int main(void) {

    FILE *f = fopen("./known", "r");

    char buffer[100];
    int count = 0;
    while (EOF) {
        fgets(buffer, sizeof(buffer), f);
        fprintf(stdout, "%s", buffer);
        count++;
        if (count == 5)
            break;
    };

    fclose(f);

    return 0;
}

#include <stdio.h>
#include <string.h>

int main() {
    char buffer[100];

    printf("Введите текст: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Красивое удаление символа '\n' через strcspn
        // buffer[strcspn(buffer, "\n")] = '\0';

        printf("Вы ввели: %s\n", buffer);
    }
    return 0;
}

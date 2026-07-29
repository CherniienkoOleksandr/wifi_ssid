
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[256];
    int part = 1;

    printf("Введите очень длинный текст:\n");

    // Цикл работает, пока есть что читать
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("Порция %d: %s", part++, buffer);

        // Проверяем, есть ли перевод строки в конце буфера
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            printf("\n--- Строка закончилась полностью ---\n");
            break; // Выходим, строка прочитана до конца
        }
    }
    return 0;
}

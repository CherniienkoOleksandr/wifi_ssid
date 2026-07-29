
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[256];

    printf("Введите имя (макс 255 символов): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        size_t len = strlen(buffer);

        // Если в конце есть '\n', значит строка поместилась целиком
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0'; // Просто убираем перенос строки
        } else {
            // Если '\n' нет, значит пользователь ввел слишком много!
            // Чистим входной поток (stdin) до конца строки, чтобы не сломать
            // следующий ввод
            int ch;
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF)
                ;

            printf(
                "(Предупреждение: строка была слишком длинной и обрезана)\n");
        }

        printf("Сохраненное имя: %s\n", buffer);
    }
    return 0;
}

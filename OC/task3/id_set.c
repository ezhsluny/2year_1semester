#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    // 1. Создайте файл данных, который может писать и читать только владелец
    FILE *fp;
    fp = fopen("secret_data.txt", "w+");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }
    fclose(fp);
    if (chmod("secret_data.txt", S_IRUSR | S_IWUSR) == -1) {
        perror("chmod");
        exit(1);
    }

    // 2. Печатайте реальный и эффективный идентификаторы пользователя
    printf("Реальный идентификатор пользователя: %d\n", getuid());
    printf("Эффективный идентификатор пользователя: %d\n", geteuid());

    // 3. Откройте файл с помощью fopen(3)
    fp = fopen("secret_data.txt", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }
    fclose(fp);

    // 4. Сделайте, чтобы реальный и эффективный идентификаторы пользователя совпадали
    if (setuid(getuid()) == -1) {
        perror("setuid");
        exit(1);
    }

    // 5. Повторите первые два шага
    printf("\nПосле setuid():\n");
    printf("Реальный идентификатор пользователя: %d\n", getuid());
    printf("Эффективный идентификатор пользователя: %d\n", geteuid());

    return 0;
}



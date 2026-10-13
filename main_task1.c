/*
 * 1-topshiriq, 19-variant: Sezar shifri
 * macOS: clang -std=c11 -Wall -Wextra -pedantic main_task1.c -o task1
 */
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 1024

static int read_long(const char *prompt, long *value) {
    char line[LINE_SIZE];
    char *end = NULL;

    printf("%s", prompt);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    long parsed = strtol(line, &end, 10);
    if (end == line || errno == ERANGE) {
        return 0;
    }
    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
        end++;
    }
    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

/* Satrni joyida o'zgartiradi: yangi massiv kerak emas. */
static void shifrla(char *s, int k) {
    int shift = k % 26;

    for (char *p = s; *p != '\0'; ++p) {
        if (*p >= 'A' && *p <= 'Z') {
            *p = (char)('A' + ((*p - 'A' + shift + 26) % 26));
        } else if (*p >= 'a' && *p <= 'z') {
            *p = (char)('a' + ((*p - 'a' + shift + 26) % 26));
        }
        /* Harf bo'lmagan belgilar o'zgarmaydi. */
    }
}

int main(void) {
    char text[LINE_SIZE];
    long key;
    long choice;

    puts("=== Sezar shifri ===");
    puts("1 - Shifrlash");
    puts("2 - Deshifrlash");

    if (!read_long("Tanlovingiz (1 yoki 2): ", &choice) ||
        (choice != 1 && choice != 2)) {
        puts("Xato: tanlov 1 yoki 2 bo'lishi kerak.");
        return 1;
    }

    printf("Matnni kiriting: ");
    if (fgets(text, sizeof text, stdin) == NULL) {
        puts("Xato: matn o'qilmadi.");
        return 1;
    }
    text[strcspn(text, "\n")] = '\0';

    if (!read_long("Kalitni kiriting (manfiy ham bo'lishi mumkin): ", &key)) {
        puts("Xato: kalit butun son bo'lishi kerak.");
        return 1;
    }

    /* Deshifrlash — shu algoritmni teskari kalit bilan ishlatish. */
    long normalized = key % 26;
    if (choice == 2) {
        normalized = -normalized;
    }
    shifrla(text, (int)normalized);

    printf("Natija: %s\n", text);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SWITCHES 128
#define MAX_NAME_LEN 64

static char switches[MAX_SWITCHES][MAX_NAME_LEN];
static int switch_count = 0;

static void load_switches(void) {

    FILE *f = fopen("names.txt", "r");
    if (!f)
        fprintf(stderr, "Missing switch name\n");
    return;

    while (switch_count < MAX_SWITCHES &&
           fgets(switches[switch_count], MAX_NAME_LEN, f)) {
        switches[switch_count][strcspn(switches[switch_count], "\r\n")] = '\0';

        if (switches[switch_count][0] != '\0')
            switch_count++;
    }
    fclose(f);
}

static void help(void) {
    puts("Usage:");
    puts("	myutil [-p|--print]");
    puts("	myutil [-s|switch NAME]");
}

static void list_switches(void) {
    for (int i = 0; i < switch_count; i++)
        puts(switches[i]);
}

int main(int argc, char *argv[]) {
    load_switches();

    if (argc == 2 && strcmp(argv[1], "--list-switches") == 0) {
        list_switches();
        return 0;
    }

    int print = 0;
    const char *sw = NULL;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "--print")) {
            print = 1;
        } else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--switch")) {
            if (++i >= argc) {
                fprintf(stderr, "Missing switch name\n");
                return 1;
            }
            sw = argv[i];
        } else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            help();
            return 0;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    if (print)
        puts("Print enabled");

    if (sw)
        printf("Switch: %s\n", sw);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("/etc/shadow", "r");
    if (file == NULL) {
        perror("Nie mozna otworzyc pliku");
        return 1;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
    return 0;
}

#include <stdio.h>

int main() {
    FILE *file;
    char filename[] = "ppg_pcg/114 80 84 ngoc.txt";
    char line[100];
    int col1;
    float col2;
    float col3;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%*f %*f %*f %*f %*f %*f %d %f %f", &col1, &col2, &col3);
        printf("Line: %s\n", line);
        printf("Column 7: %d, Column 8: %f, Column 8: %f\n", col1, col2, col3);
        count++;
        if (count == 10) {
            break;
        }
    }

    fclose(file);
    return 0;
}
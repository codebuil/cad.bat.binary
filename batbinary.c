#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1025
#define MAX_FIELDS 100
char filess[1025];
int indexes[6001*5];
int counter=1;
int counter2=0;
void save_binary_file(char *filename, int *array, int size) {
    FILE *fp;
    int i;
    char header[7] = "batcad"; // cabeçalho com 6 caracteres e o caractere nulo
    
    fp = fopen(filename, "wb");
    if(fp == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        exit(1);
    }
    
    fwrite(header, sizeof(char), 6, fp); // escreve o cabeçalho no arquivo
    
    for(i = 0; i < size; i++) {
        fwrite(&array[i], sizeof(int), 1, fp); // escreve cada inteiro no arquivo
    }
    
    fclose(fp);
}

int main(int argc, char *argv[]) {
    printf("\033c\033[44;37m\n");
    if (argc != 2) {
        printf("Usage: %s filename.csv\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char line[MAX_LINE_LENGTH];
    char *fields[MAX_FIELDS];
    int i;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return 1;
    }
    counter=1;
    counter2=0;
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        // Replace newline with null terminator
        line[strcspn(line, "\n")] = '\0';

        // Split line into fields
        i = 0;
        fields[i] = strtok(line, ",");
        while (fields[i] != NULL && i < MAX_FIELDS) {
            i++;
            fields[i] = strtok(NULL, ",");
        }

        // Print fields separated by tabs
        if (i>4)
        {
            indexes[counter]=1;
            for (int j = 0; j < i; j++) 
            {
                if(j>0 && j<6)
                
                indexes[j+counter] =atoi(fields[j]);

            }
            counter=counter+5;   
            counter2++;
        }
        
    }
    indexes[0]=counter2;
    strcpy(filess,filename);
    strcat(filess,".bbt");
    save_binary_file(filess, indexes, counter+1);
    fclose(fp);
    return 0;
}

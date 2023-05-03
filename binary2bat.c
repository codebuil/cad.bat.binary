#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_binary_file(char *filename) {
    FILE *fp;
    int header_size = 6;
    char header[7]; // cabeçalho com 6 caracteres e o caractere nulo
    int file_size;
    int i;
    int num1, num2, num3, num4;
    
    fp = fopen(filename, "rb");
    if(fp == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        exit(1);
    }
    
    fread(header, sizeof(char), header_size, fp); // lê o cabeçalho do arquivo
    header[header_size] = '\0'; // adiciona o caractere nulo ao final do cabeçalho
    
    if(strcmp(header, "batcad") != 0) { // verifica se o cabeçalho é "batcad"
        printf("Formato de ficheiro inválido.\n");
        fclose(fp);
        exit(1);
    }
    
    fread(&file_size, sizeof(int), 1, fp); // lê o tamanho do restante do arquivo
    file_size *= 5 * 4; // multiplica o tamanho por 5 e 4
    
    while(ftell(fp) < file_size) { // lê os dados até atingir o fim do arquivo
        fread(&num1, sizeof(int), 1, fp); // lê o primeiro inteiro
        if(num1 == 1) { // verifica se o primeiro inteiro é 1
        fread(&num1, sizeof(int), 1, fp); // lê o primeiro inteiro
        fread(&num2, sizeof(int), 1, fp); // lê os outros três inteiros
        fread(&num3, sizeof(int), 1, fp);
        fread(&num4, sizeof(int), 1, fp);
            printf("line,%d,%d,%d,%d\r\n", num1, num2, num3, num4); // imprime no formato especificado
        }
        
        
        
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
    load_binary_file(filename);
}
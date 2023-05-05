#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1025
#define MAX_FIELDS 100
char filess[1025];
int indexes[6001*7];
int counter=1;
int counter2=0;
double scale=800.00;
double units=10.00;
double wasm_draw3Dx(double x, double y, double z) {
  double zz=(z+1.00)*1.50;
  double zzz=scale/zz;
  double zzzz=scale/2-zzz/2;
  double zzzzz=(zzz/units)*x;
  double zzzzzz=zzzz+zzzzz;
  return zzzzzz;  
}
double wasm_draw3Dy(double x, double y, double z) {
  double zz=(z+1.00)*1.50;
  double zzz=scale/zz;
  double zzzz=scale/2-zzz/2;
  double zzzzz=(zzz/units)*(units-y);
  double zzzzzz=zzzz+zzzzz-(z*2);
  return zzzzzz;  
}
void setScale(double sc){
  scale=sc;
}
void setunits(double sc){
  units=sc;
}
void save_binary_file(char *filename, int *array, int size) {
    FILE *fp;
    int i;
    char header[7] = "bat3d"; // cabeçalho com 6 caracteres e o caractere nulo
    
    fp = fopen(filename, "wb");
    if(fp == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        exit(1);
    }
    
    fwrite(header, sizeof(char), 5, fp); // escreve o cabeçalho no arquivo
    
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
        if (i>6)
        {
            indexes[counter]=1;
            indexes[1+counter] =atoi(fields[1]);
            indexes[2+counter] =atoi(fields[2]);
            indexes[3+counter] =atoi(fields[3]);
            indexes[4+counter] =atoi(fields[4]);
            indexes[5+counter] =atoi(fields[5]);
            indexes[6+counter] =atoi(fields[6]);
            counter=counter+7;   
            counter2++;
        }
        
    }
    indexes[0]=counter2;
    strcpy(filess,filename);
    strcat(filess,".3bb");
    save_binary_file(filess, indexes, counter+1);
    fclose(fp);
    return 0;
}

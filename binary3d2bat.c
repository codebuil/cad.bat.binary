#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void load_binary_file(char *filename) {
    FILE *fp;
    int header_size = 5;
    char header[7]; // cabeçalho com 6 caracteres e o caractere nulo
    int file_size;
    int i;
    int num1, num2, num3, num4,num5,num6;
    int xx,yy,xx2,yy2;
    
    fp = fopen(filename, "rb");
    if(fp == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        exit(1);
    }
    
    fread(header, sizeof(char), header_size, fp); // lê o cabeçalho do arquivo
    header[header_size] = '\0'; // adiciona o caractere nulo ao final do cabeçalho
    
    if(strcmp(header, "bat3d") != 0) { // verifica se o cabeçalho é "batcad"
        printf("Formato de ficheiro inválido.\n");
        fclose(fp);
        exit(1);
    }
    
    fread(&file_size, sizeof(int), 1, fp); // lê o tamanho do restante do arquivo
    file_size *= 7 * 4; // multiplica o tamanho por 5 e 4
    
    while(ftell(fp) < file_size) { // lê os dados até atingir o fim do arquivo
        fread(&num1, sizeof(int), 1, fp); // lê o primeiro inteiro
        if(num1 == 1) { // verifica se o primeiro inteiro é 1
        fread(&num1, sizeof(int), 1, fp); // lê o primeiro inteiro
        fread(&num2, sizeof(int), 1, fp); // lê os outros três inteiros
        fread(&num3, sizeof(int), 1, fp);
        fread(&num4, sizeof(int), 1, fp);
        fread(&num5, sizeof(int), 1, fp);
        fread(&num6, sizeof(int), 1, fp);
        
            xx =(int)wasm_draw3Dx((double)num1,(double)num2,(double)num3);
            yy =(int)wasm_draw3Dy((double)num1,(double)num2,(double)num3);
            xx2 =(int)wasm_draw3Dx((double)num4,(double)num5,(double)num6);
            yy2 =(int)wasm_draw3Dy((double)num4,(double)num5,(double)num6);;
            printf("line,%d,%d,%d,%d\r\n",xx,yy,xx2,yy2);// imprime no formato especificado
        }
        else{
        fread(&num1, sizeof(int), 1, fp); // lê o primeiro inteiro
        fread(&num2, sizeof(int), 1, fp); // lê os outros três inteiros
        fread(&num3, sizeof(int), 1, fp);
        fread(&num4, sizeof(int), 1, fp);
        fread(&num5, sizeof(int), 1, fp);
        fread(&num6, sizeof(int), 1, fp);
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
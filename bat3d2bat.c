#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1025
#define MAX_FIELDS 100
char filess[1025];
int indexes[6001*5];
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
    strcpy(filess,filename);
    strcat(filess,".bat");
    FILE *fp2 = fopen(filess, "w");
    if (fp2 == NULL) {
        printf("Error opening file %s\n", filess);
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
            indexes[1+counter] =(int)wasm_draw3Dx((double)atoi(fields[1]),(double)atoi(fields[2]),(double)atoi(fields[3]));
            indexes[2+counter] =(int)wasm_draw3Dy((double)atoi(fields[1]),(double)atoi(fields[2]),(double)atoi(fields[3]));
            indexes[3+counter] =(int)wasm_draw3Dx((double)atoi(fields[4]),(double)atoi(fields[5]),(double)atoi(fields[6]));
            indexes[4+counter] =(int)wasm_draw3Dy((double)atoi(fields[4]),(double)atoi(fields[5]),(double)atoi(fields[6]));
            fprintf(fp2,"line,%d,%d,%d,%d\r\n",indexes[1+counter],indexes[2+counter],indexes[3+counter],indexes[4+counter]);
            
            counter=counter+5;   
            counter2++;
        }
        
    }
    indexes[0]=counter2;
    
    
    fclose(fp);
    fclose(fp2);
    return 0;
}

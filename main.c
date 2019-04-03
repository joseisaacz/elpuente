#include <stdio.h>
#include <stdlib.h>
#include "read1.c"
#include "read2.c"
size_t arreglo[]={};
size_t array[]={};
int main(){
        FILE* fp;
        char* filename="config.txt";
        read(fp, filename, arreglo);
        read1(fp, filename, array);
for (int i=0; i< 16; i++){
        printf("%d",arreglo[i]);
printf("\n");
}
printf("\n");
/*for (int i=0; i< 16; i++){
        printf("%d",array[i]);
printf("\n");
}
printf("\n");
printf("%d", arreglo[3]);
printf("\n");*/
        }



        /*char str[MAX];
                fp= fopen(filename, "r");
                if(fp==NULL){
                printf("no se puede abrir %s",filename);
                return 1;
                }
        while(fgets(str, MAX, fp)!= NULL)
        printf("%s", str);
        fclose(fp);
        return 0;*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "creacion.c"
#include <math.h>
#include <time.h>
//datos de configuracion
size_t arreglo[]={};
//arreglo de  mutex recurso compartido 
//el puente
pthread_mutex_t puente[]={};

float randomentre();
float formula(int promedio);
void crearpuente();
void* crearcarro(void* p);
int calculavelocidad(int vmax, int vmin);
int main(){
/*FILE* fp;
char* filename="config.txt";
read(fp, filename, arreglo);
asignavalores(arreglo);*/

printf("%f", formula(200));
printf("\n");
printf("%d", calculavelocidad(8,4));
printf("\n");
}
float formula(int promedio){
        float ln= log(1-randomentre());
        return -promedio * ln;
}
float randomentre(){
        time_t t;
        srand((unsigned) time(&t));

return ( (float) (rand()%10000) / 10000  );
}
int calculavelocidad(int vmax, int vmin){
        time_t t;
        srand((unsigned) time(&t));
        return (rand()%(vmax - vmin+1)) + vmin;
}
void crearpuente(){
for(int i=0; i</*longitudpuente*/10; i++){
pthread_mutex_t s;
pthread_mutex_init(&s, NULL);
puente[i] = s;
        }
}



void* crearcarro(void* p){

}










/* FILE* fp;
        char* filename="config.txt";
        read(fp, filename, arreglo);*/


/*for (int i=0; i< 16; i++){
        printf("%lu",arreglo[i]);#include <math.h>
printf("\n");
}

char str[MAX];
                fp= fopen(filename, "r");
                if(fp==NULL){
                printf("no se puede abrir %s",filename);
                return 1;
                }
        while(fgets(str, MAX, fp)!= NULL)
        printf("%s", str);
        fclose(fp);
        return 0;*/


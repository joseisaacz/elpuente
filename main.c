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
int* probaAmbulancia(int cantidad,int totalCarros);
int cantidadAmbulanciasEste();
int cantidadAmbulanciasOeste();
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

int cantidadAmbulanciasEste(){
return (int)arreglo[9]*100 /arreglo[3];
}
int cantidadAmbulanciasOeste(){
      return (int)arreglo[17]*100 /arreglo[11];  
}

int* probaAmbulancia(int cantidadAmbu,int totalCarros){
 int array[cantidadAmbu];
 srand(time(NULL));
 int rangoReal=(int)totalCarros/cantidadAmbu;
 int rangoVariable;
 int numero=0;
 int i=0;
 for(i; i<cantidadAmbu; i++){
  rangoVariable=numero+rangoReal;
  if(rangoVariable>totalCarros)
        rangoVariable=totalCarros;

  numero=(int)rand() % rangoVariable + (numero+1);
  array[i]=numero;
 }
 return array;
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


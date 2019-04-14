#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "creacion.c"
#include "read.c"
#include <math.h>
#include <time.h>
//datos de configuracion
size_t arreglo[]={};
//arreglo de  mutex recurso compartido 
//el puente
pthread_mutex_t puente[]={};
//random entre 0 y 1
float randomentre();
//funcion que calcula la llegada (nanosleep)
float formula(int promedio);
//funcion para llenar el puente 
void crearpuente();
//crea el thread con todos los parametros este-oeste
void* carroEO(void* p);
//crea el thread con todos los parametros oeste-este
void* carroOE(void* p);
//devuelve un random entre los parametros ingresados
int calculavelocidad(int vmax, int vmin);
//calcula si es ambulancia 
int* probaAmbulancia(int cantidad,int totalCarros);
int cantidadAmbulanciasEste(); //calcula la cantidad de ambulacias en Este
int cantidadAmbulanciasOeste();//calcula la cantidad de ambulacias en Oeste


int main(){
FILE* fp;
char* filename="config.txt";
read(fp, filename, arreglo);
for(int i=0; i<18; i++){
        printf("%lu", arreglo[i]);
        printf("\n");
}
printf("\n");
printf("\n");
asignavalores(arreglo);
printf("%lu", longitudpuente);
printf("\n");
printf("%lu", arreglo[0]);
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
void crearpuente(){
for(int i=0; i<arreglo[0]; i++){
pthread_mutex_t s;
pthread_mutex_init(&s, NULL);
puente[i] = s;
        }
}

void* carroEO(void* p){
int modo= arreglo[1];
int velocidad = calculavelocidad(arreglo[6],arreglo[7]);
pthread_mutex_lock(&puente[0]);
for(int i=1;i<arreglo[0];i++){
pthread_mutex_lock(&puente[i]);
pthread_mutex_unlock(&puente[i-1]);
nanosleep(1/velocidad);
        }
}

void* carroOE(void* p){
int modo= arreglo[1];
int velocidad = calculavelocidad(arreglo[14],arreglo[15]);
pthread_mutex_lock(&puente[0]);
for(int i=1;i<arreglo[0];i++){
pthread_mutex_lock(&puente[i]);
pthread_mutex_unlock(&puente[i-1]);
nanosleep(1/velocidad);
        }
}

int calculavelocidad(int vmax, int vmin){
        time_t t;
        srand((unsigned) time(&t));
        return (rand()%(vmax - vmin+1)) + vmin;
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

//printf("%f", formula(200));
//printf("\n");
//printf("%d", calculavelocidad(8,4));
//printf("\n");
//time_t t;
  //      srand((unsigned) time(&t));
//printf("%d", (rand()%100));
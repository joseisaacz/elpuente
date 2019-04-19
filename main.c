#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include<unistd.h>
#include "creacion.c"
#include "read.c"
#include <math.h>
#include <time.h>
//datos de configuracion
size_t arreglo[]={};
//arreglo de  mutex recurso compartido 
//el puente
pthread_mutex_t puente[10];
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
void probaAmbulancia(int cantidad,int totalCarros, int array[]);
//calcula la cantidad de ambulacias en Este
int cantidadAmbulanciasEste(); 
//calcula la cantidad de ambulacias en Oeste
int cantidadAmbulanciasOeste();
//Contador de carros creados en el este
int contadorCarrosEste=0; 
//Contador de carros creados en el oeste
int contadorCarrosOeste=0; 
//crea los carros para sentido este-oeste
void* CCOE(void* p);
//crea los carros para sentido oeste-este 
void* CCEO(void* p);
//arreglo ambulancias este-oeste
int *arraye_o;
//arreglo ambulancias oeste-este 
int *arrayo_e;
//inicializa las ambulancias oeste-este
void init_ambulanciasOE();
//inicializa las ambulancias este-oeste
void init_ambulanciasEO();
//hilos de direccion
pthread_t OE;
pthread_t EO;
void bloquea(int o);

int main(){
FILE* fp;
char* filename="config.txt";
read_txt(fp, filename, arreglo);
crearpuente();
arrayo_e=(int*)malloc(sizeof(int)*cantidadAmbulanciasOeste());
arraye_o=(int*)malloc(sizeof(int)*cantidadAmbulanciasEste());
pthread_create(&OE, NULL, carroOE, NULL);
//pthread_create(&EO, NULL, CCEO, NULL);
pthread_join(OE, NULL);
//pthread_join(EO, NULL);

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
printf("%ld", arreglo[0]);
pthread_mutex_init(&puente[i], NULL);
        }
}

void* carroEO(void* p){
contadorCarrosEste++;
bool esAmbulancia=false;
int cantidadAmbulancias=cantidadAmbulanciasEste();
for(int i=0; i<cantidadAmbulancias;i++){
        if(contadorCarrosEste==arraye_o[i]){
                esAmbulancia=true;
                break;
        }
}       
int modo= arreglo[1];
int velocidad = calculavelocidad(arreglo[6],arreglo[7]);
pthread_mutex_lock(&puente[0]);
for(int i=1;i<arreglo[0];i++){
pthread_mutex_lock(&puente[i]);
printf("soy carro y voy por la posicion %d",i);
pthread_mutex_unlock(&puente[i-1]);
time_t sec= (time_t) 1/velocidad;
usleep(sec);
        }
}

void* carroOE(void* p){
init_ambulanciasOE();        
contadorCarrosOeste++;
bool esAmbulancia=false;
int cantidadAmbulancias=cantidadAmbulanciasOeste();
for(int i=0;i<cantidadAmbulancias; i++){
        if(arrayo_e[i]==contadorCarrosOeste){
         esAmbulancia=true;
         break;
        }
}     
int modo= arreglo[1];
int velocidad = calculavelocidad(arreglo[14],arreglo[15]);
pthread_mutex_lock(&puente[0]);
//for(int i=1;i<arreglo[0];i++){
//pthread_mutex_unlock(&puente[i-1]);
//pthread_mutex_lock(&puente[i]);
//printf("soy carro y voy por la posicion %d",i);
//time_t sec= (time_t) 1/velocidad;
//usleep(0.5);
       // }
int i=1;
while(i<arreglo[0]){
//pthread_mutex_unlock(&puente[0]);
pthread_mutex_lock(&puente[i]);
usleep(1);
pthread_mutex_unlock(&puente[i-1]);
//pthread_mutex_lock(&puente[i]);
printf("soy carro y voy por la posicion %d",i);
printf("\n");
//time_t sec= (time_t) 1/velocidad;
i++;
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

void probaAmbulancia(int cantidadAmbu,int totalCarros, int array[]){
 
 srand(time(NULL));
 int rangoReal=(int)totalCarros/cantidadAmbu;
 int rangoVariable;
 int numero=0;
 int i=0;
 int aux=0;
 for(i; i<cantidadAmbu; i++){
  rangoVariable=numero+rangoReal;
  if(rangoVariable>totalCarros)
        rangoVariable=totalCarros;
  aux=numero+1;    
  numero=(int)rand() % (rangoVariable-aux) + aux;
  array[i]=numero;
 }
 printf("hola");
}

void* CCEO(void* p){
        init_ambulanciasEO();
        int cant = arreglo[3];
        while(cant!=0){
                pthread_t carro;
pthread_create(&carro, NULL, carroEO, NULL);
time_t sec= (time_t) 1/formula(arreglo[4]);
usleep(sec);
pthread_join(carro, NULL);
cant--;
}
}

void* CCOE(void* p){
        init_ambulanciasEO();
        int cant = arreglo[11];
        while(cant!=0){
                pthread_t carro;
pthread_create(&carro, NULL, carroOE, NULL);
time_t sec= (time_t) 1/formula(arreglo[12]);
usleep(sec);
pthread_join(carro, NULL);
cant--;
}
}

void init_ambulanciasEO(){
probaAmbulancia(cantidadAmbulanciasEste(),arreglo[3], arraye_o);
}
void init_ambulanciasOE(){
 probaAmbulancia(cantidadAmbulanciasOeste(),arreglo[11],arrayo_e );
}
 void bloquea(int o){
pthread_mutex_unlock(&puente[o-1]);
pthread_mutex_lock(&puente[o]);
printf("soy carro y voy por la posicion %d",o);
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

/*for(int i=0; i<18; i++){
        printf("%lu", arreglo[i]);
        printf("\n");
}
printf("\n");
printf("\n");
printf("%lu", longitudpuente);
printf("\n");
printf("%lu", arreglo[0]);
printf("\n");*/
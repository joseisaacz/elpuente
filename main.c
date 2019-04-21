#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include<unistd.h>
#include "creacion.c"
#include "read.c"
#include <math.h>
#include <time.h>
/* STATE_A = THREAD A runs next, STATE_B = THREAD B runs next */
enum { STATE_A, STATE_B } state = STATE_A;
pthread_cond_t      condA  = PTHREAD_COND_INITIALIZER;
pthread_cond_t      condB  = PTHREAD_COND_INITIALIZER;
//datos de configuracion
//Contador de carros creados en el este
int vcontadorCarrosEste=0; 
//Contador de carros creados en el oeste
int contadorCarrosOeste=0; 
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
//crea los carros para sentido este-oeste
void* CCOE(void* p);
//crea los carros para sentido oeste-este 
void* CCEO(void* p);
//inicializa las ambulancias oeste-este
void init_ambulanciasOE();
//inicializa las ambulancias este-oeste
void init_ambulanciasEO();
//hilos de direccion
int contador=0;
int cant;
 int cant2;
pthread_t OE;
pthread_t EO;
void bloquea(int o);
//arreglo ambulancias este-oeste
int *arraye_o;
//arreglo ambulancias oeste-este 
int *arrayo_e;
size_t arreglo[]={};
// pthread_mutex_t fuerzabruta;
// pthread_t fb0;
// pthread_t fb1;
// pthread_cond_t cond;
// void bloqueaf(){
//         pthread_mutex_lock(&fuerzabruta);
// }
// void desbloqueaf(){
//         pthread_mutex_unlock(&fuerzabruta);
// }
// void *fuerzabruta_method1(void *p ){
// bloqueaf();
// pthread_create(&OE, NULL, CCOE, NULL);
// desbloqueaf();
// }
// void* fuerzabruta_method2(void* p){
// bloqueaf();
// pthread_create(&EO, NULL, CCEO, NULL);
// desbloqueaf();
// }

int main(){
FILE* fp;
char* filename="config.txt";
read_txt(fp, filename, arreglo);
crearpuente();
arrayo_e=(int*)malloc(sizeof(int)*cantidadAmbulanciasOeste());
arraye_o=(int*)malloc(sizeof(int)*cantidadAmbulanciasEste());
pthread_create(&OE, NULL,CCOE , NULL);
pthread_create(&EO, NULL, CCEO, NULL);
pthread_join(OE, NULL);
pthread_join(EO, NULL);

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
//printf("%ld", arreglo[0]);
pthread_mutex_init(&puente[i], NULL);
        }
}

void* carroEO(void* p){
//init_ambulanciasOE();  
printf("Creando carro EO\n");     
vcontadorCarrosEste++;
bool esAmbulancia=false;
int cantidadAmbulancias=cantidadAmbulanciasEste();
for(int i=0;i<cantidadAmbulancias; i++){
        if(arraye_o[i]==vcontadorCarrosEste){
         esAmbulancia=true;
         break;
        }
}     
int modo= arreglo[1];
int velocidad = calculavelocidad(arreglo[7],arreglo[8]);
pthread_mutex_lock(&puente[0]);

int i=1;
while(i<arreglo[0]){
printf("Bloqueando y Desbloqueando EO\n");        
pthread_mutex_unlock(&puente[i-1]);    
usleep(1);    
pthread_mutex_lock(&puente[i]);


time_t sec= (time_t) 1/velocidad;
// if(esAmbulancia)
// printf("Soy ambulanciaEO y voy por la posicion %d",i);

// printf("\n");
usleep(sec);
i++;

}
}

void* carroOE(void* p){
//init_ambulanciasOE();  
printf("Creando carro OE\n");      
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

int i=1;
while(i<arreglo[0]){        
pthread_mutex_unlock(&puente[i-1]);
usleep(1);
pthread_mutex_lock(&puente[i]);



time_t sec= (time_t) 1/velocidad;
usleep(sec);
i++;
// if(esAmbulancia)
// printf("Soy ambulancia y voy por la posicion %d",i);

// printf("\n");
}

}

int calculavelocidad(int vmax, int vmin){
        time_t t;
        srand((unsigned) time(&t));
        return (int)(rand()%(vmax - vmin+1)) + vmin;
}


int cantidadAmbulanciasEste(){
return (int)arreglo[9]*arreglo[3]/100;

}
int cantidadAmbulanciasOeste(){
      return (int)arreglo[17]*arreglo[11]/100;  
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
 //printf("hola");
}

void* CCEO(void* p){
       // printf("Funcion CCEO\n");
       init_ambulanciasEO();
        cant = arreglo[3];
        while(cant!=0){

  /* Wait for state A */
  for(int i=0; i<10; i++){
        printf("Bloqueando sentido EO\n");
        pthread_mutex_lock(&puente[i]);
        while (state != STATE_A){
        pthread_cond_wait(&condA, &puente[i]);
          printf("Esperanto sentido EO\n");
        }
        pthread_mutex_unlock(&puente[i]);
  }
                pthread_t carro;

pthread_create(&carro, NULL, carroEO, NULL);
time_t sec= (time_t) 1/formula(arreglo[4]);
usleep(sec);

for(int i=0;i<10;i++){
printf("Desbloqueando sentido EO\n");
  pthread_mutex_lock(&puente[i]);
        state = STATE_B;
        pthread_cond_signal(&condB);
        pthread_mutex_unlock(&puente[i]);
}
//pthread_join(carro, NULL);
cant--;
}
}

void* CCOE(void* p){
        //printf("Funcion CCOE\n");
        init_ambulanciasOE();
        cant2 = arreglo[11];
        while(cant2!=0){
                 /* Wait for state B */
                 for(int i=0;i<10;i++){
        printf("Bloqueando sentido OE\n");
        pthread_mutex_lock(&puente[i]);
        while (state != STATE_B){
            pthread_cond_wait(&condB, &puente[i]);
            printf("Esperanto sentido OE\n");
            }
        pthread_mutex_unlock(&puente[i]);
                 }

//Do stuff
                pthread_t carro;
pthread_create(&carro, NULL, carroOE, NULL);
time_t sec= (time_t) 1/formula(arreglo[12]);
usleep(sec);

 /* Set state to A and wake up thread A */
 for(int i=0;i<10;i++){
         printf("Desbloqueando sentido OE\n");
        pthread_mutex_lock(&puente[i]);
        state = STATE_A;
        pthread_cond_signal(&condA);
        pthread_mutex_unlock(&puente[i]);
        
 }
cant2--;
}
}

void init_ambulanciasEO(){
probaAmbulancia(cantidadAmbulanciasEste(),arreglo[3], arraye_o);
}
void init_ambulanciasOE(){
 probaAmbulancia(cantidadAmbulanciasOeste(),arreglo[11],arrayo_e );
}
//  void bloquea(int o){
// pthread_mutex_unlock(&puente[o-1]);
// pthread_mutex_lock(&puente[o]);
// printf("soy carro y voy por la posicion %d",o);
//  }

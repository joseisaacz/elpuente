#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "creacion.c"
#include "read.c"
#include <math.h>
#include <time.h>

/* STATE_A = THREAD A runs next, STATE_B = THREAD B runs next */
enum
{
        STATE_A,
        STATE_B
} state = STATE_A;
pthread_cond_t condA = PTHREAD_COND_INITIALIZER;
pthread_cond_t condB = PTHREAD_COND_INITIALIZER;

char *direccionCarros;
char *direccionPuente;
//Contador de carros creados en el este
int contadorCarosEO = 0;
//Contador de carros creados en el oeste
int contadorCarosOE = 0;
//direccion representada por un dato numerico
int direccion;
//cantidad de carros que estan cruzando el puente
int cantCarrosenPuente = 0;

int Esperando[2];
pthread_cond_t EsteOeste[2];

//datos de configuracion
//contador de carros por sentido utilizado en la probabilidad de ambulancia
int contadorCarrosOeste = 0;
int contadorCarrosEste = 0;

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
void *carroEO(void *p);
//crea el thread con todos los parametros oeste-este
void *carroOE(void *promediollegada2);
//devuelve un random entre los parametros ingresados
int calculavelocidad(int vmax, int vmin);
//calcula si es ambulancia
void probaAmbulancia(int cantidad, int totalCarros, int array[]);
//calcula la cantidad de ambulacias en Este
int cantidadAmbulanciasEste();
int Max_Run;

//calcula la cantidad de ambulacias en Oeste
int cantidadAmbulanciasOeste();
//inicializa las ambulancias oeste-este
void init_ambulanciasOE();
//inicializa las ambulancias este-oeste
void init_ambulanciasEO();
//hilos de direccion
int esSeguro(int dir);
void LlegaApuente(int dir);
void salePuente(int dir);
//hilo de ejecucion
pthread_t OE;
//mutex que se bloquea para manejar el flujo del transito 
pthread_mutex_t MonitorLock;

void bloquea(int o);
//arreglo ambulancias este-oeste
int *arraye_o;
//arreglo ambulancias oeste-este
int *arrayo_e;
//arreglo donde se guardan los datos de configuracion
size_t arreglo[] = {};

void bloquearPuente();
void desbloquearPuente();
void *crearCarro(void *p);
char *dir(int dir);

int main()
{
        FILE *fp;
        char *filename = "config.txt";
        read_txt(fp, filename, arreglo);
        arrayo_e = (int *)malloc(sizeof(int) * cantidadAmbulanciasOeste());
        arraye_o = (int *)malloc(sizeof(int) * cantidadAmbulanciasEste());
        crearpuente();
        pthread_create(&OE, NULL, crearCarro, NULL);
        pthread_join(OE, NULL);
}

float formula(int promedio)
{
        float ln = log(1 - randomentre());
        return -promedio * ln;
}

float randomentre()
{
        time_t t;
        srand((unsigned)time(&t));
        return ((float)(rand() % 10000) / 10000);
}

void crearpuente()
{
        init_ambulanciasEO();
        init_ambulanciasOE();
        Esperando[0] = Esperando[1] = 0;
        pthread_cond_init(&(EsteOeste[0]), NULL);
        pthread_cond_init(&(EsteOeste[1]), NULL);
        for (int i = 0; i < arreglo[0]; i++)
        {
                pthread_mutex_init(&puente[i], NULL);
        }
}

void *carroEO(void *p)
{
        //init_ambulanciasOE();
        printf("Creando carro EO\n");
        contadorCarrosEste++;
        bool esAmbulancia = false;
        int cantidadAmbulancias = cantidadAmbulanciasEste();
        for (int i = 0; i < cantidadAmbulancias; i++)
        {
                if (arraye_o[i] == contadorCarrosEste)
                {
                        esAmbulancia = true;
                        break;
                }
        }
        int velocidad = calculavelocidad(arreglo[7], arreglo[8]);
}

void *carroOE(void *p)
{
        //init_ambulanciasOE();
        contadorCarrosOeste++;
        bool esAmbulancia = false;
        int cantidadAmbulancias = cantidadAmbulanciasOeste();
        for (int i = 0; i < cantidadAmbulancias; i++)
        {
                if (arrayo_e[i] == contadorCarrosOeste)
                {
                        esAmbulancia = true;
                        break;
                }
        }
        int velocidad = calculavelocidad(arreglo[14], arreglo[15]);
        if (esAmbulancia)
                printf("Soy una ambulanciaOE y vengo a esta velocidad:%d \n", velocidad);
        else
                printf("Soy un CarroOE y vengo a esta velocidad:%d \n", velocidad);
}

int calculavelocidad(int vmax, int vmin)
{
        time_t t;
        srand((unsigned)time(&t));
        return (int)(rand() % (vmax - vmin + 1)) + vmin;
}

int cantidadAmbulanciasEste()
{
        return (int)arreglo[9] * arreglo[3] / 100;
}
int cantidadAmbulanciasOeste()
{
        return (int)arreglo[17] * arreglo[11] / 100;puente
}

void probaAmbulancia(int cantidadAmbu, int totalCarros, int array[])
{
        srand(time(NULL));
        int rangoReal = (int)totalCarros / cantidadAmbu;
        int rangoVariable;
        int numero = 0;
        int i = 0;
        int aux = 0;
        for (i; i < cantidadAmbu; i++)
        {
                rangoVariable = numero + rangoReal;
                if (rangoVariable > totalCarros)
                        rangoVariable = totalCarros;
                aux = numero + 1;
                numero = (int)rand() % (rangoVariable - aux) + aux;
                array[i] = numero;
        }
}
void init_ambulanciasEO()
{
        probaAmbulancia(cantidadAmbulanciasEste(), arreglo[3], arraye_o);
}
void init_ambulanciasOE()
{
        probaAmbulancia(cantidadAmbulanciasOeste(), arreglo[11], arrayo_e);
}
int esSeguro(int dir)
{
        if (cantCarrosenPuente == 0)
                return 1;
        else if (direccion == dir)
                return 1;
        else
                return 0;
}

void LlegaApuente(int dir)
{
        bloquearPuente();
        if (!esSeguro(dir))
        {
                Esperando[dir]++;
                while (!esSeguro(dir))
                        pthread_cond_wait(&(EsteOeste[dir]), &MonitorLock);
                Esperando[dir]--;
        }
        cantCarrosenPuente++;
        direccion = dir;
        desbloquearPuente();
}

void salePuente(int dir)
{
        bloquearPuente();
        cantCarrosenPuente--;
        if (cantCarrosenPuente > 0)
                pthread_cond_signal(&(EsteOeste[dir]));
        else
        {
                if (Esperando[1 - dir] != 0)
                        pthread_cond_signal(&(EsteOeste[1 - dir]));
                else
                        pthread_cond_signal(&(EsteOeste[dir]));
        }
        desbloquearPuente();
}

void bloquearPuente()
{
        for (int i = 0; i < arreglo[0]; i++)
        {
                int num = pthread_mutex_trylock(&puente[i]);
                if (num != 0)
                {
                        pthread_mutex_unlock(&puente[i]);
                        pthread_mutex_lock(&puente[i]);
                        printf("Bloqueando el puente\n");
                }
        }
}
void desbloquearPuente()
{
        for (int i = 0; i < arreglo[0]; i++)
        {

                pthread_mutex_unlock(&puente[i]);
        }
}

void *crearCarro(void *p)
{

        int max = arreglo[3] + arreglo[11];
        for (int i = 1; i <= max; i++)
        {
                int aleatorio;
                if (contadorCarosEO == arreglo[3] && contadorCarosOE == arreglo[11])
                        break;
                else if (contadorCarosEO == arreglo[3] && contadorCarosOE < arreglo[11])
                        aleatorio = 1;
                else if (contadorCarosOE == arreglo[11] && contadorCarosEO < arreglo[3])
                        aleatorio = 0;
                else
                        aleatorio = (int)rand() % 2;
                if (aleatorio == 0)
                        contadorCarosEO++;
                else
                        contadorCarosOE++;

                if (aleatorio == 0)
                {
                        printf("Carro entrando al puente en direccion %s\n", dir(0));
                        LlegaApuente(aleatorio);
                        pthread_t carro;
                        pthread_create(&carro, NULL, carroEO, NULL);
                        salePuente(aleatorio);
                        printf("El carro ha pasado el puente\n");
                }
                else
                {
                        printf("Carro entrando al puente en direccion %s\n", dir(1));
                        LlegaApuente(aleatorio);
                        pthread_t carro;
                        pthread_create(&carro, NULL, carroOE, NULL);
                        salePuente(aleatorio);
                        printf("El carro ha pasado el puente\n");
                }
        }
}

char *dir(int dir)
{
        char *a;
        if (dir == 0)
                return a = "EO";
        else
                return a = "OE";
}
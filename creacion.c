size_t longitudpuente;
size_t modoejecucion;
//datos del Este
size_t cantidaddecarros1;
size_t promediollegada1;
size_t tiempodelsemaforo1;
size_t velominima1;
size_t velomaxima1;
size_t cvpp1;
size_t ambulancias1;
//datos del Oeste
size_t cantidaddecarros2;
size_t promediollegada2;
size_t tiempodelsemaforo2;
size_t velominima2;
size_t velomaxima2;
size_t cvpp2;
size_t ambulancias2;

void asignavalores (size_t * arreglo){
size_t longitudpuente = arreglo[0];
size_t modoejecucion = arreglo[1];
//datos del este
size_t cantidaddecarros1 = arreglo[3];
size_t promediollegada1 = arreglo[4];
size_t tiempodelsemaforo1 = arreglo[5];
size_t velominima1= arreglo[6];
size_t velomaxima1= arreglo[7];
size_t cvpp1= arreglo[8];
size_t ambulancias1=arreglo[9];
//datos del oesfe 
size_t cantidaddecarros2=arreglo[11];
size_t promediollegada2=arreglo[12];
size_t tiempodelsemaforo2=arreglo[13];
size_t velominima2= arreglo[14];
size_t velomaxima2= arreglo[15];
size_t cvpp2=arreglo[16];
size_t ambulancias2= arreglo[17];
}

size_t getlongitudpuente(){
    return longitudpuente;
}

size_t getmodo(){
    return modoejecucion;
}

size_t getcantidaddecarros1(){
    return cantidaddecarros1;
}

size_t getpromediollegada1(){
    return promediollegada1;
}

size_t gettiempodelsemaforo1(){
    return tiempodelsemaforo1;
}

size_t getvelominima1(){
    return velominima1;
}

size_t getvelomaxima1(){
    return velomaxima1;
}

size_t getcvpp1(){
    return cvpp1;
}

size_t getambulancias1(){
    return ambulancias1;
}

size_t getcantidaddecarros2(){
    return cantidaddecarros2;
}

size_t getpromediollegada2(){
    return promediollegada2;
}

size_t gettiempodelsemaforo2(){
    return tiempodelsemaforo2;
}

size_t getvelominima2(){
    return velominima2;
}

size_t getvelomaxima2(){
    return velomaxima2;
}

size_t getcvpp2(){
    return cvpp2;
}

size_t getambulancias2(){
    return ambulancias2;
}
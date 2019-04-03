
    



#define MAX 100

void read(FILE *file, char* name, size_t *arreglo){
    file= fopen(name, "r");
                char str[MAX];
                file= fopen(name, "r");
size_t i=0;
while(/*fscanf(file,"%d", str)==1*/fgets(str, MAX, file)!=NULL){
//fgets(str, MAX, file);
int  good; /*= fscanf(file,"%d", str);*/
good = atoi(str);
if(good){
        arreglo[i]=atoi(str);
        }
                i++;
          }
        fclose(file);

        }
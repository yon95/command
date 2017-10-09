#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int primo(int a) {
  int i,count=0;
  for (i=1;i<=a;i++) if (a%i==0) count ++;
  return count==2;
}

void *hilo(int *args,int *n, int *canlin) {
FILE *arc;
FILE *arc2;
int kiko=*canlin;
int buf[3];
char cadena[3];
char actual[5];
int superarg=*args+1;
char casteo=superarg+'0';
actual[0]=casteo;
actual[1]='.';
actual[2]='t';
actual[3]='x';
actual[4]='t';
printf("Soy el hilo: %i\n",*args+1);
arc=fopen("./hola","r");
int inicio,tope,count=1;
tope=*n*(*args+1); inicio=tope-(*n)+1;
printf("Inicio: %i\n",inicio);
printf("Tope: %i\n",tope);
arc2=fopen(actual,"w+");
int messi=1;
while(messi<*canlin){
  if (count>=inicio && count<=tope){
      int caca=fscanf(arc,"%i",&buf[messi-1]);
      //caca=caca-'0';
      int jose=primo(caca); 
      printf("%i %i\n",caca,jose);
      cadena[0]=caca+'0';cadena[1]=' '; cadena[2]=jose+'0';
      printf("Cadena %c ",cadena[0]);
      printf("Cadena %c ",cadena[1]);
      printf("Cadena %c \n",cadena[2]);
      printf("\n");
      fputs(cadena,arc2);
      fputs("\n",arc2);
  } count ++; messi++;
}
fclose(arc2);
fclose(arc);
}

void master(int n, int j) {
  pthread_t *p;
  int i;
  int ch=j/n;
  int uh=(j/n)+(j%n);
  p=(pthread_t *)malloc(n * sizeof(pthread_t));
  printf("Master\n");
  for (i=0;i<n;i++) {if (i==n-1) pthread_create(&p[i],NULL,hilo(&i,&uh,&j),NULL); else {pthread_create(&p[i],NULL,hilo(&i,&ch,&j),NULL);}} 
  for (i=0;i<n;i++) pthread_join(p[i],NULL);
}

int main (int args, char * argc[]) {
int n,i;
FILE *arc;
char buf[3];
int j=0;
char ceremonia[]="hola";
arc=fopen(ceremonia,"r");
while(fgets(buf,3,arc)!=NULL){
j++;
}
fclose(arc);
printf("M: %i\n",j);
printf("Number of threads: \n");
scanf("%i",&n);
master(n,j);
/*pthread_t *p;
p=(pthread_t *)malloc(n * sizeof(pthread_t));
for (i=0;i<n;i++) pthread_create(&p[i],NULL,hilo(&i),NULL); 
for (i=0;i<n;i++) pthread_join(p[i],NULL);*/
return 0;
}

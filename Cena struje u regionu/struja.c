#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIM 20
#define nizLIM 21

typedef struct paket_st{

    char nazivZ[nizLIM];
    char nazivO[nizLIM];
    int mesecnaP;
    int bsplKW;
    double cenaKW;

}A;

typedef struct cena_st{

    double ukupnaCena;
    char nazivZ[nizLIM];
    char nazivO[nizLIM];

}B;

FILE *safeOpen(char filename[],char mode[],int errorcode){

    FILE *fp=fopen(filename,mode);

    if(fp==NULL)
    {
        printf("Greska prilikom otvaranja datoteke");
        exit(errorcode);
    }

    return fp;
}


int main(int argN,char args[]){

    if(argN!=4)
    {
        printf("Greska prilikom pokretanja programa");
        exit(20);
    }

    char *in_filename=args[2];
    char *out_filename=args[3];
    int potrosenoKWH=atoi(args[1]);

    FILE *in=safeOpen(in_filename,"r",1);
    FILE *out=safeOpen(out_filename,"w",2);
    

    return 0;
}
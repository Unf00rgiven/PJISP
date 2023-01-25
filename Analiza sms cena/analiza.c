#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIM 20

typedef struct paket_st
{
    char nazivPr[20+1];
    char nazivPa[20+1];
    int mesecnaPr;
    int brBP;
    double cenaPo;
}A;

typedef struct cena_st
{
    float ukupnaCena;
    char nazivPr[20+1];
    char nazivPa[20+1];
}B;

FILE *safeOpen(char filename[],char mode[],int errorcode){

    FILE *fp=fopen(filename,mode);

    if(fp==NULL){
        printf("Ne postoji takva datoteka");
        exit(errorcode);
    }

    return fp;

}

void ucitaj(FILE *in,A nizUlaznih[],int *n){
    printf("USAO U F");
     *n = 0;
    while(fscanf(
        in, "%s %s %d %d %lf",
         nizUlaznih[*n].nazivPr,
         nizUlaznih[*n].nazivPa,
        &nizUlaznih[*n].mesecnaPr,
        &nizUlaznih[*n].brBP,
        &nizUlaznih[*n].cenaPo
    ) != EOF) {
        (*n)++;
        printf("USAO JE");  
    }
}

void transform(A nizUlaznih[]   ,B nizIzlaznih[],int n,int mesPoruka){
    
    int i=0;
    for(i;i<n;i++)
    {
        strcpy(nizIzlaznih[i].nazivPa,nizUlaznih[i].nazivPa);
        strcpy(nizIzlaznih[i].nazivPr,nizUlaznih[i].nazivPr);

        int extraSMS=mesPoruka-nizUlaznih[i].brBP;
        double doplata=0;

        if(extraSMS>0)
        {
            doplata=nizUlaznih[i].cenaPo*extraSMS;
        }

        nizIzlaznih[i].ukupnaCena=nizUlaznih[i].mesecnaPr+doplata;
    }
}

void ispis(FILE *out,B nizIzlaznih[],int n){
          
    int i;
    for(i=0; i<n; i++) 
    {  
        fprintf(
            out, "%7.2f %s %s\n",
            nizIzlaznih[i].ukupnaCena,
            nizIzlaznih[i].nazivPr,
            nizIzlaznih[i].nazivPa

        );
    }
}

int main(int argN,char *args[]){

    if(argN!=4)
    {
        printf("Greska prilikom unosa argumenata");
        exit(20);
    }

    char *in_filename=args[2];
    char *out_filename=args[3];
    int mesPoruka=atoi(args[1]);

    int n;

    FILE *in=safeOpen(in_filename,"r",1);
    FILE *out=safeOpen(out_filename,"w",2);

    A nizUlaznih[LIM];
    B nizIzlaznih[LIM];

    ucitaj(in,nizUlaznih,&n);
    transform(nizUlaznih,nizIzlaznih,n,mesPoruka);
    ispis(out,nizIzlaznih,n);

    fclose(in);
    fclose(out);
    


    return 0;
}
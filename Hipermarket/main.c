#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define LIM 20

typedef struct artikal_st 
{
    double cena;
    int brProdatih;
    double procenat;
    char naziv[20+1];   

}A;

typedef struct zarada_st
{
    float ostvZarada;
    char naziv[20+1];
}B;

FILE *safeOpen(char filename[],char mode[],int errorcode)
{
    FILE *fp=fopen(filename,mode);
    if(fp==NULL){

        
        printf("Ne postoji takva datoteka");
        exit(errorcode);
    }
    return fp;
}

void ucitaj_st(FILE *in,A nizUlaznih[],int *n){

    *n=0;
    
    while(fscanf(in,"%lf %d %lf %s", &nizUlaznih[*n].cena,&nizUlaznih[*n].brProdatih,
                &nizUlaznih[*n].procenat,nizUlaznih[*n].naziv)!=EOF)
    {
        (*n)++;
    }
    
}

void izracunaj(A nizUlaznih[],B nizIzlaznih[],int n){
    
    int i=0;
    for(i;i<n;i++)
    { 
        strcpy(nizIzlaznih[i].naziv,nizUlaznih[i].naziv);
        nizIzlaznih[i].ostvZarada=nizUlaznih[i].cena*nizUlaznih[i].brProdatih*nizUlaznih[i].procenat/100;  
    }

}

void ispis(FILE *out,B nizIzlaznih[],int n){

        int i=0;

        for(i;i<n;i++)
        {
            fprintf(out,"%.2f %s \n",nizIzlaznih[i].ostvZarada,nizIzlaznih[i].naziv);
        }


}

int main(int argN,char *args[])
{
    A nizUlaznih[LIM];
    B nizIzlaznih[LIM];

    if(argN!=3)
    { 
            printf("Pogresan unos argumenata"); 
            exit(10);   
    }

    char *in_filename=args[1];
    char *out_filename=args[2];

    FILE *ul=safeOpen(in_filename,"r",1);
    FILE *izl=safeOpen(out_filename,"w",2);


    int n;

    ucitaj_st(ul,nizUlaznih,&n);
    izracunaj(nizUlaznih,nizIzlaznih,n);
    ispis(izl,nizIzlaznih,n);


    fclose(ul);
    fclose(izl);

    



   return 0;
}
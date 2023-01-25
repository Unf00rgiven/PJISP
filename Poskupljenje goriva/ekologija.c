#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIM 20

typedef struct gorivo_st
{
    char grad[2+1];
    char tipGoriva[10+1];
    double cenaGoriva;
}A;

typedef struct analiza_st
{
    double cenaG;
    double procenat;
    char grad[2+1];
    char tipGoriva[10+1];    
}B;

FILE *safeopen(char filename[],char mode[],int errorcode){
        
        FILE *fp=fopen(filename,mode);
        if(fp==NULL)
        {
            printf("Greska");
            exit(errorcode);
        }
        return fp;

}

void ucitavanje(FILE *in,A nizUlaznih[],int *n){

    *n=0;

    while(fscanf(in,"%s %s %lf",nizUlaznih[*n].grad,nizUlaznih[*n].tipGoriva,&nizUlaznih[*n].cenaGoriva)!=EOF)
    {
        (*n)++;
    }


}

void transform(A nizUlaznih[],B nizIzlaznih[],int n,double akciza){

    int i;
    for(i=0;i<n;i++)
    {
        nizIzlaznih[i].cenaG=akciza+nizUlaznih[i].cenaGoriva;
        nizIzlaznih[i].procenat=akciza/nizUlaznih[i].cenaGoriva*100;
        strcpy(nizIzlaznih[i].grad,nizUlaznih[i].grad);
        strcpy(nizIzlaznih[i].tipGoriva,nizUlaznih[i].tipGoriva);
        
    }

}

void ispis(FILE *out,B nizIzlaznih[],int n){

    int i=0;

    for(i=0;i<n;i++)
    {
        fprintf(out,"%6.2lf %5.2lf %s %s\n",nizIzlaznih[i].cenaG,nizIzlaznih[i].procenat,nizIzlaznih[i].grad,nizIzlaznih[i].tipGoriva);
    }

}

void sort(B nizIzlaznih[],int n){

    B temp;
    int i,j;

    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(nizIzlaznih[i].cenaG>nizIzlaznih[j].cenaG)
            {
                temp=nizIzlaznih[i];
                nizIzlaznih[i]=nizIzlaznih[j];
                nizIzlaznih[j]=temp;
            }
        }
    }
}

int main(int argN,char *args[]){

    if(argN!=4)
    {
        printf("Pogresan unos");
        exit(10);
    }

    double akciza=atof(args[1]);
    char *in_filename=args[2];
    char *out_filename=args[3];

    FILE *in=safeopen(in_filename,"r",1);
    FILE *out=safeopen(out_filename,"w",2);

    A nizUlaznih[LIM];
    B nizIzlaznih[LIM];

    int n;

    ucitavanje(in,nizUlaznih,&n);
    transform(nizUlaznih,nizIzlaznih,n,akciza);
    sort(nizIzlaznih,n);
    ispis(out,nizIzlaznih,n);



    fclose(in);
    fclose(out);

    return 0;
}
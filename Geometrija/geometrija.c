#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SLIM 7
#define LIM 20

typedef struct podaci_st
{
    double r;
    double H;
    char vrsta[SLIM];
    
}A;

typedef struct figura_st
{
    char naziv[SLIM];
    double r;
    double H;
    double P;
    double V;
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

void ucitavanje(FILE *in,A nizUlaznih[],int *n){

    *n=0;

    while(fscanf(in,"%lf %lf %s",&nizUlaznih[*n].r,&nizUlaznih[*n].H,nizUlaznih[*n].vrsta)!=EOF)
    {
        (*n)++;
    }


}

void transform(A nizUlaznih[],B nizIzlaznih[],int n){

    int i;
    for(i=0;i<n;i++)
    {
        strcpy(nizIzlaznih[i].naziv,nizUlaznih[i].vrsta);
        nizIzlaznih[i].r=nizUlaznih[i].r;
        nizIzlaznih[i].H=nizUlaznih[i].H;
        nizIzlaznih[i].V=nizUlaznih[i].r*nizUlaznih[i].r*3.14*nizUlaznih[i].H;
        nizIzlaznih[i].P=nizUlaznih[i].r*nizUlaznih[i].r*6.28+2*3.14*nizUlaznih[i].r*nizUlaznih[i].H;
    }


}

void ispis(FILE *out,B nizIzlaznih[],int n){

    int i;

    fprintf(out,"Figure:\n");


    for(i=0;i<n;i++)
    {
        fprintf(out,"\t%lf %lf %s %lf %lf\n",nizIzlaznih[i].r,nizIzlaznih[i].H,nizIzlaznih[i].naziv,nizIzlaznih[i].P,nizIzlaznih[i].V);
    }


}

void sort(FILE *out,B nizIzlaznih[],int n){

    int j,i;
    B temp;

    for(i=0;i<n-1;i++)
    {
        for(j=i;j<n;j++)
        {
            if(nizIzlaznih[i].P<nizIzlaznih[j].P)
            {
                    temp=nizIzlaznih[i];
                    nizIzlaznih[i]=nizIzlaznih[j];
                    nizIzlaznih[j]=temp;
            }
        }
    }
}

void ispis2(FILE *out,B nizIzlaznih[],int n){

    int i;

    fprintf(out,"Sortirane figure:\n");


    for(i=0;i<n;i++)
    {
        fprintf(out,"\t%s %lf %lf\n",nizIzlaznih[i].naziv,nizIzlaznih[i].P,nizIzlaznih[i].V);
    }
}

void OdabranIspis(FILE *out,B nizIzlaznih[],int n,double donjaG,double gornjaG){

    int i;

    fprintf(out,"Figure:\n");


    for(i=0;i<n;i++)
    {
        if((nizIzlaznih[i].P>donjaG && nizIzlaznih[i].P<gornjaG)&&(nizIzlaznih[i].V>donjaG && nizIzlaznih[i].V<gornjaG))
        {
        fprintf(out,"\t%lf %lf %s %lf %lf\n",nizIzlaznih[i].r,nizIzlaznih[i].H,nizIzlaznih[i].naziv,nizIzlaznih[i].P,nizIzlaznih[i].V);
        }    
    }



}

int main(int argN,char *args[]){

    if(argN!=6)
    {
        printf("Greska prilikom upisa argumenata");
        exit(10);
    }
    
    char *in_filename=args[1];
    char *out_filename=args[2];
    char *kupa=args[3];
    double donjaG=atof(args[4]);
    double gornjaG=atof(args[5]);

    FILE *in=safeOpen(in_filename,"r",1);
    FILE *out=safeOpen(out_filename,"w",2);

    if(gornjaG<0 || donjaG<0)
    {
        fprintf(out,"Neispravna vrednost granica!");
        exit(3);
    }
    
    A nizUlaznih[LIM];
    B nizIzlaznih[LIM];

    int i,n;

    ucitavanje(in,nizUlaznih,&n);
    transform(nizUlaznih,nizIzlaznih,n);
    ispis(out,nizIzlaznih,n);
    sort(out,nizIzlaznih,n);
    ispis2(out,nizIzlaznih,n);
    OdabranIspis(out,nizIzlaznih,n,donjaG,gornjaG);

    fclose(in);
    fclose(out);


    return 0;
}
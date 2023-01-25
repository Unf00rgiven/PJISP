#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMRESTORAN 11
#define LIMVRSTA 21

typedef struct restoran_st{

    char nazivRestorana[LIMRESTORAN];
    char vrstaKuhinje[LIMVRSTA];
    double avgOcena;

    struct restoran_st *desni;
    struct restoran_st *levi;

}RE;

FILE *safeOpen(char filename[],char mode[],int errorcode){

    FILE *fp=fopen(filename,mode);
    if(fp==NULL)
    {
        printf("Greska prilikom otvaranja datoteke");
        exit(errorcode);
    }
}

void stablo_init(RE **koren){

    *koren=NULL;
}

void dodajEl(RE *new,RE **koren){

    if(*koren==NULL)
    {
        *koren=new;
    }else if(new->avgOcena >= (*koren)->avgOcena)
    {
        dodajEl(new,&((*koren)->desni));
    }else 
    {
        dodajEl(new,&((*koren)->levi));
    }
}

RE *kreirajNovi(char nazivRestorana[],char vrsta[],double avgOcena){
    RE *new=(RE *)malloc(sizeof(RE));
    if(new=NULL)
    {
        printf("Nedovoljno RAM-a");
        exit(21);
    }

    strcpy(new->nazivRestorana,nazivRestorana);
    strcpy(new->vrstaKuhinje,vrsta);
    new->avgOcena=avgOcena;
    new->desni=NULL;
    new->levi=NULL;

    return new;
}

void citajStablo(FILE *in,RE **koren){

    char tmp_naziv[LIMRESTORAN];
    char tmp_vrsta[LIMVRSTA];
    double tmp_avgOcena;

    while(fscanf(in,"%s %s %lf",tmp_naziv,tmp_vrsta,&tmp_avgOcena)!=EOF)
    {
        RE *new=kreirajNovi(tmp_naziv,tmp_vrsta,tmp_avgOcena);
        dodajEl(new,koren); 
    }

}

void ispisiEL(FILE *out,RE *x){

    fprintf(out,"%lf %s %s",x->avgOcena,x->nazivRestorana,x->vrstaKuhinje);
}

void ispisiStablo(FILE *out,RE *koren){

    if(koren!=NULL)
    {
        ispisiStablo(out,koren->levi);
        ispisiEL(out,koren);
        ispisiStablo(out,koren->desni);
    }

}

void unistiStablo(RE **koren){

    if(*koren!=NULL)
    {
        unistiStablo(&((*koren)->levi));
        unistiStablo(&((*koren)->desni));
        free(*koren);
        *koren=NULL;
    }

}

int main(int argN,char *args[]){

    if(argN!=4)
    {
        printf("Greska prilikom poziva argumenata");
        exit(12);
    }

    char *vrsta=args[1];
    char *in_filename=args[2];
    char *out_filename=args[3];

    FILE *in=safeOpen(in_filename,"r",1);
    FILE *out=safeOpen(out_filename,"w",2);

    RE *koren;
    stablo_init(&koren);

    citajStablo(in,&koren);
    ispisiStablo(in,koren);

    unistiStablo(&koren);

    fclose(in);
    fclose(out);

    return 0;
}
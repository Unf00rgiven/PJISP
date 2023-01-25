#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMgrad 3
#define LIMgorivo 11

typedef struct gorivo_st
{
    char grad[LIMgrad];
    char tipGoriva[LIMgorivo];
    double cena;

    struct gorivo_st *next;
}GO;

FILE *safeOpen(char filename[],char mode[],int errorcode){

    FILE *fp=fopen(filename,mode);
    if(fp==NULL)
    {
        printf("Greska prilikom otvaranja datoteke");
        exit(errorcode);
    }

    return fp;
}

void init_list(GO **glava){

    *glava=NULL;
}

void dodajEl(GO *new,GO **glava){

    if(*glava==NULL)
    {
        *glava=new;
        return;
    }
    dodajEl(new,&((*glava)->next));

}

GO *kreirajEl(char grad[],char tipGoriva[],double cena){
    
    GO *new=(GO *)malloc(sizeof(GO));
    if(new==NULL)
    {
        printf("Nema dovoljno rama");
        exit(22);
    }

    strcpy(new->grad,grad);
    strcpy(new->tipGoriva,tipGoriva);
    new->cena=cena;

    new->next=NULL;

    return new;    

}

void ucitajListu(FILE *in,GO **glava){
    char grad[LIMgrad];
    char gorivo[LIMgorivo];
    double cena;

    while(fscanf(in,"%s %s %lf",grad,gorivo,&cena)!=EOF)
    {
        GO *new=kreirajEl(grad,gorivo,cena);
        dodajEl(new,glava);
    }

}

void ispisEl(FILE *out,GO *x){

    fprintf(out,"6.2f %s %s",x->cena,x->grad,x->tipGoriva);
}

void ispisListe(FILE *out,GO *glava){
    if(glava!=NULL)
    {
        ispisEl(out,glava);
        ispisListe(out,glava->next);
    }
}

void unistiListu(GO **glava){
    if(*glava!=NULL)
    {
        unistiListu(&((*glava)->next));
        free(*glava);
        *glava=NULL;
    }


}

int main(int argN,char *args[]){

    if(argN!=4)
    {
        printf("Greska prilikom poziva programa");
        exit(20);
    }

    char *tipGoriva=args[1];
    char *in_filename=args[2];
    char *out_filename=args[3];

    FILE *in=safeOpen(in_filename,"r",1);
    FILE *out=safeOpen(out_filename,"w",2);

    GO *glava;
    init_list(&glava);


    

    fclose(in);
    fclose(out);


    return 0;
}
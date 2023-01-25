#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LIM 14
#define LIM1 11

typedef struct namirnica_st
{
    char naziv[LIM];
    double kolicinaVitamina;
    char vrsta[LIM1];

    struct namirnica_st *desni;
    struct namirnica_st *levi;

}NA;

FILE *safeOpen(char filename[],char mode[],int errorcode){

    FILE *fp=fopen(filename,mode);
    if(fp==NULL)
    {
        printf("Grijska prilikom otvaranja datoteke");
    }

    return fp;
}

void init_stablo(NA **koren){

    *koren=NULL;
}

void dodajEL(NA *new,NA **koren){

    if(*koren==NULL)
    {
        *koren=new;
    }
    else if(new->kolicinaVitamina >= (*koren)->kolicinaVitamina)
    {
        dodajEL(new,&((*koren)->desni));
    }
    else 
    {
        dodajEL(new,&((*koren)->levi));
    }

}

NA *kreirajNoviEL(char naziv[],double kolicinaVitamina,char vrsta[]){

    NA *new=(NA *)malloc(sizeof(NA));
    if(new==NULL)
    {
        printf("Nijema dovoljno rama");
        exit(21);
    }

    strcpy(new->naziv,naziv);
    new->kolicinaVitamina=kolicinaVitamina;
    strcpy(new->vrsta,vrsta);
    new->desni=NULL;
    new->levi=NULL;

    return new;
}

void citajStablo(FILE *in,NA **koren){

    char tmp_naziv[LIM];
    double tmp_kolicinaVitamina;
    char tmp_vrsta[LIM1];

    while(fscanf(in,"%s %lf %s",tmp_naziv,&tmp_kolicinaVitamina,tmp_vrsta)!=EOF)
    {
        NA *new=kreirajNoviEL(tmp_naziv,tmp_kolicinaVitamina,tmp_vrsta);
        dodajEL(new,koren);
    }

}

void ispisiEL(FILE *out,NA *x){

    fprintf(out,"%3lf %-13s %s\n",x->kolicinaVitamina,x->naziv,x->vrsta);
}

void ispisStabla(FILE *out,NA *koren){
    if(koren!=NULL)
    {
        ispisStabla(out,koren->desni);
        ispisiEL(out,koren);
        ispisStabla(out,koren->levi);
    }
}

void unistiStablo(NA **koren){
    if(*koren!=NULL)
    {
        unistiStablo(&((*koren)->desni));
        unistiStablo(&((*koren)->levi));
        free(*koren);
        *koren=NULL;
    }


}

NA *getbest(NA *koren){

    if(koren==NULL)
    {
        return NULL;
    }

    if(koren->desni==NULL)
    {
        return koren;
    }

    return getbest(koren->desni);

}

int main(int argN,char *args[]){

    if(argN!=3)
    {
        printf("Grijeska prilikom poziva programa! :)");
        exit(21);
    }

    char *in_filename=args[1];
    char *out_filename=args[2];

    FILE *in=safeOpen(in_filename,"r",1);
    FILE *out=safeOpen(out_filename,"w",2);

    NA *koren;
    init_stablo(&koren);

    citajStablo(in,&koren);
    ispisStabla(out,koren);

    NA *best=getbest(koren);
    if(best==NULL)
    {
        fprintf(out,"\nNema namirnica.");
    }
    else
    {            
        fprintf(out,"\n Namirnica sa najvise vitamina C je %lf",best->kolicinaVitamina);
    }

    unistiStablo(&koren);
    fclose(in);
    fclose(out);

    return 0;
}
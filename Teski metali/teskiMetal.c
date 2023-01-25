#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LIM 3
#define LIM1 21

typedef struct element_st{

    char hemijskiS[LIM];    
    char ime[LIM1];
    double atomskaTezina;
    char vrsta[LIM1];

    struct element_st *next;

}EL;

FILE *safeOpen(char filename[],char mode[],int errorcode){

    FILE *fp=fopen(filename,mode);
    if(fp==NULL)
    {
        printf("Greska prilikom otvaranja datoteke");
        exit(errorcode);
    }
}

void initList(EL **head){

    *head=NULL;
}

void addItem(EL *new,EL **head){

    if(*head==NULL)
    {
        *head=new;
        return;
    }

    addItem(new,&(*head)->next);
}

EL *createItem(char hemijskiS[],char ime[],double atomskaTezina,char vrsta[]){

    EL *new=(EL *)malloc(sizeof(EL));
    if(new=NULL)
    {
        printf("Nedovoljno RAM-a");
        exit(666);
    }

    strcpy(new->hemijskiS,hemijskiS);
    strcpy(new->ime,ime);
    new->atomskaTezina=atomskaTezina;
    strcpy(new->vrsta,vrsta);

    new->next=NULL;

    return new;
}

void readlist(FILE *in,EL **head){

    char tmp_simbol[LIM];
    char tmp_ime[LIM1];
    double tmp_tezina;
    char tmp_vrsta[LIM1];

    while(fscanf(in,"%s %s %lf %s",tmp_simbol,tmp_ime,&tmp_tezina,tmp_vrsta)!=EOF)
    {  
        EL *new=createItem(tmp_simbol,tmp_ime,tmp_tezina,tmp_vrsta);
        addItem(new,head);
    }

}

void saveItem(FILE *out,EL *x){

    fprintf(out,"%s %lf %s",x->hemijskiS,x->atomskaTezina,x->vrsta);

}

void saveList(FILE *out,EL *head){

    if(head!=NULL)
    {
        saveItem(out,head);
        saveList(out,head->next);
    }
}

void destroyList(EL **head){

    if(*head==NULL)
    {
          destroyList(&((*head)->next));    
          free(*head);
          *head=NULL;  
    }


}



int main(int argN,char *args[]){

    if(argN!=4)
    {
        printf("GRIJESKA");
        exit(666);
    }

    char *vrsta=args[1];
    char *in_filename=args[2];
    char *out_filename=args[3];

    FILE *in=safeOpen(in_filename,"r",1);
    FILE *out=safeOpen(out_filename,"w",2);

    EL *head;
    initList(&head);

    readlist(in,&head);
    saveList(out,head);

    fclose(in);
    fclose(out);



    return 0;
}
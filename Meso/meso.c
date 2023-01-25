#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIM 3
#define LIM1 21

typedef struct meso_st{

    char nazivGrada[LIM];
    char vrstaMesa[LIM1];
    double cenaKG;
    struct meso_st *next;    

}MESO;

void init_list(MESO **head){

    *head=NULL;
}

void addToList(MESO *new,MESO **head){

    if(*head=NULL)
    {
        *head=new;
        return;
    }
    addToList(new,&(*head)->next);

}

MESO *createNewItem(char nazivGrada[],char vrstaMesa[],double cenaKG){

    MESO *new=(MESO *)malloc(sizeof(MESO));
    if(new==NULL)
    {
        printf("RAM kaze ne meze");
        exit(20);
    }

    strcpy(new->nazivGrada,nazivGrada);
    strcpy(new->vrstaMesa,vrstaMesa);
    new->cenaKG=cenaKG;
    new->next=NULL;

    return new;
}

void readList(FILE *in,MESO **head){

    char tmp_grad[LIM];
    char tmp_vrstaMesa[LIM1];
    double tmp_cena;
    
    while(fscanf(in,"%s %s %lf",tmp_grad,tmp_vrstaMesa,&tmp_vrstaMesa)!=EOF)
    {
            MESO *new=createNewItem(tmp_grad,tmp_vrstaMesa,tmp_cena);
            addToList(new,head);
    }

}

void saveItem(FILE *out,MESO *x){

    fprintf(out,"%6,2lf %s %s",x->cenaKG,x->nazivGrada,x->vrstaMesa);
}

void saveList(FILE *out,MESO *head){

    if(head!=NULL)
    {
        saveItem(out,head);
        saveList(out,head->next);
    }
}

void destroyList(MESO **head){

    if(*head!=NULL)
    {
        destroyList(&(*head)->next);
        free(*head);
        *head=NULL;
    }

}

FILE *safeOpen(char filename[],char mode[],int errorcode){

    FILE *fp=fopen(filename,mode);
    if(fp==NULL)
    {
        printf("Greska prilikom otvaranja datoteke");
        exit(errorcode);
    }

    return fp;

}

MESO *najpovoljnije(MESO *head,char vrsta_mesa[]){

    MESO *best=NULL;
    while(head!=NULL)
    {
        if(strcpy(head->vrstaMesa,vrsta_mesa)==0)
        {
            if(best=NULL)
            {
                best=head;
            }
            if(best->cenaKG<best->cenaKG)
            {
                best=head;
            }
        }
    }
    return best;
}


int main(int argN,char *args[])
{

    if(argN!=4)
    {
        printf("Greska prilikom poziva programa");
        exit(10);
    }

    char *vrsta_mesa=args[1];
    char *in_filename=args[2];
    char *out_filename=args[3];

    FILE *in=safeOpen(in_filename,"r",1);
    FILE *out=safeOpen(out_filename,"w",2);

    MESO *head;
    init_list(&head);

    readList(in,&head);
    saveList(out,head);
    MESO *best=najpovoljnije(head,vrsta_mesa);
    fprintf(out,"Najpovoljnije meso je '%s' je:%lf %s %s",vrsta_mesa,best->cenaKG,best->nazivGrada,best->vrstaMesa);

    destroyList(&head);

    fclose(in);
    fclose(out);

    return 0;
}
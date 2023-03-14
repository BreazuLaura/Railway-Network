#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "header.h"

int main()
{
    FILE *f1,*f2;
    Graph *g1,*g2;
    int **costuri1,**costuri2;
    node_t *node;
    int i1,i2,i,j,max1=0,max2=0,nr_muchii=0,nod1,nod2,aux,grad=0,cost,k,cost2;
    char fisier[20],oras[40],oras2[40],ct[6],ct2[6];
    g1=creare_graf(g1);
    g2=creare_graf(g2);
    node_t *head = NULL;



    /**1.Citirea datelor din arhiva**/
    if((f1=fopen("_all_files.txt","rt"))==NULL)
    {
        puts("Fisierul nu poate fi deschis!\n");
        exit(1);
    }
    while(fscanf(f1,"%s",fisier)!=EOF)
    {
        if((f2=fopen(fisier,"rt"))==NULL)
        {
            puts("Fisierul nu poate fi deschis!\n");
            exit(1);
        }
        while(fgets(oras,40,f2)!=NULL)
        {
            i=0;
            while(oras[i]!=',')
            {
                i++;
            }
            j=i+2;
            k=0;
            while(oras[j]!='\n')
            {
                ct[k]=oras[j];
                k++;
                j++;
            }
            oras[i]='\0';
            ct[k]='\0';
            cost=atoi(ct);
            if(get_node(head,oras)==-1)
            {
                head=append_node(head,g1->v,oras);
                g1->v++;
            }
        }
        fclose(f2);
    }
    g2->v=g1->v;



    /**2.Creare graf neorientat si orientat**/
    alocare_matrice(g1);
    alocare_matrice(g2);
    costuri1 = (int **) malloc(g1->v*sizeof(int*));
    for (i=0;i<g1->v;i++)
        costuri1[i] = (int *) calloc(g1->v, sizeof(int));
    if (costuri1==NULL)
    {
        printf ( " no memory for this matrix");
        exit(1);
    }
    costuri2 = (int **) malloc(g1->v*sizeof(int*));
    for (i=0;i<g1->v;i++)
        costuri2[i] = (int *) calloc(g1->v, sizeof(int));
    if (costuri2==NULL)
    {
        printf ( " no memory for this matrix");
        exit(1);
    }

    fseek(f1,0L,SEEK_SET);
    while(fscanf(f1,"%s",fisier)!=EOF)
    {
        if((f2=fopen(fisier,"rt"))==NULL)
        {
            puts("Fisierul nu poate fi deschis!\n");
            exit(1);
        }
        fgets(oras,40,f2);
        i=0;
        while(oras[i]!=',')
        {
            i++;
        }
        j=i+2;
        k=0;
        while(oras[j]!='\n')
        {
            ct[k]=oras[j];
            k++;
            j++;
        }
        oras[i]='\0';
        ct[k]='\0';
        cost=atoi(ct);
        while(fgets(oras2,40,f2)!=NULL)
        {
            i=0;
            while(oras2[i]!=',')
            {
                i++;
            }
            j=i+2;
            k=0;
            while(oras2[j]!='\n')
            {
                ct2[k]=oras2[j];
                k++;
                j++;
            }
            oras2[i]='\0';
            ct2[k]='\0';
            cost2=atoi(ct2);
            i1=get_node(head, oras);
            i2=get_node(head, oras2);
            g1->a[i1][i2]=1;
            g1->a[i2][i1]=1;
            g2->a[i1][i2]=1;
            costuri1[i1][i2]=cost2-cost;
            costuri1[i2][i1]=cost2-cost;
            costuri2[i1][i2]=cost2-cost;
            strcpy(oras,oras2);
            cost=cost2;
        }
        fclose(f2);
    }
    fclose(f1);

    //Afisare matrice de adiacenta si de costuri
    strcpy(fisier,"graf_neorientat.txt");
    afisare_matrice(f1,g1->a,g1->v,fisier);
    strcpy(fisier,"graf_orientat.txt");
    afisare_matrice(f1,g2->a,g2->v,fisier);
    strcpy(fisier,"costuri_graf_neorientat.txt");
    afisare_matrice(f1,costuri1,g1->v,fisier);
    strcpy(fisier,"costuri_graf_orientat.txt");
    afisare_matrice(f1,costuri2,g2->v,fisier);



    /**3.Statiile consecutive care au distanta minima/maxima intre ele**/
    int max,min,imax,imin,jmax,jmin;
    max=costuri1[0][0];
    min=costuri1[0][0];
    imax=0; jmax=0;
    while(g1->a[imax][jmax]==0)
    {
        jmax++;
        max=costuri1[imax][jmax];
        min=costuri1[imax][jmax];
    }
    imin=imax; jmin=jmax;
    for(i=0;i<g1->v;i++)
    {
        for(j=0;j<g1->v;j++)
        {
            if(costuri1[i][j]>max && g1->a[i][j]==1)
            {
                max=costuri1[i][j];
                imax=i;
                jmax=j;
            }
            if(costuri1[i][j]<min && g1->a[i][j]==1)
            {
                min=costuri1[i][j];
                imin=i;
                jmin=j;
            }
        }
    }
    strcpy(oras,aflare_oras(head,imax));
    strcpy(oras2,aflare_oras(head,jmax));
    if((f1=fopen("max.txt","wt"))==NULL)
    {
        puts("Fisierul nu poate fi deschis!\n");
        exit(1);
    }
    fprintf(f1,"%s\n%s",oras,oras2);
    fclose(f1);
    strcpy(oras,aflare_oras(head,imin));
    strcpy(oras2,aflare_oras(head,jmin));
    if((f1=fopen("min.txt","wt"))==NULL)
    {
        puts("Fisierul nu poate fi deschis!\n");
        exit(1);
    }
    fprintf(f1,"%s\n%s",oras,oras2);
    fclose(f1);




    /**4.Km de cale ferata din baza de date.**/
    int km=0;
    for(i=0;i<g1->v;i++)
    {
        for(j=i;j<g1->v;j++)
        {
            if(g1->a[i][j]==1)
            {
                km+=costuri1[i][j];
            }
        }
    }
    if((f1=fopen("total.txt","wt"))==NULL)
    {
        puts("Fisierul nu poate fi deschis!\n");
        exit(1);
    }
    fprintf(f1,"%d",km);
    fclose(f1);




    /**5.Drumul de cost minim de la București la Buzau**/
    int dist[g1->v],sps[g1->v],pred[g1->v];
    nod1=get_node(head,"Buzau");
    dijkstra(g1,0,costuri1,dist,sps,pred);
    if((f1=fopen("ruta.txt","wt"))==NULL)
    {
        puts("Fisierul nu poate fi deschis!\n");
        exit(1);
    }
    fprintf(f1,"Drumul de cost minim dintre Bucuresti si Buzau este: %d\n", dist[nod1]);
    fclose(f1);
    strcpy(fisier,"ruta.txt");
    drum(dist,pred,0,nod1,head,fisier);




    /**6.Statia (nodul) cea mai departe de Bucuresti si drumul**/
    max=dist[0];
    imax=0;
    for(i=1;i<g1->v;i++)
    {
        if(dist[i]>max)
        {
            max=dist[i];
            imax=i;
        }
    }
    if((f1=fopen("departe.txt","wt"))==NULL)
    {
        puts("Fisierul nu poate fi deschis!\n");
        exit(1);
    }
    strcpy(oras,aflare_oras(head,imax));
    fprintf(f1,"Cea mai departata statie fata de Bucuresti este %s cu costul %d.\n", oras,dist[imax]);
    fclose(f1);
    strcpy(fisier,"departe.txt");
    drum(dist,pred,0,imax,head,fisier);

    return 0;
}




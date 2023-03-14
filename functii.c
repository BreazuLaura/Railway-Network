#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "header.h"
#include "stack.h"

node_t *create(int val, char oras[40])
{
    node_t *node;
	node=(node_t*)malloc(sizeof(node_t));
	node->val=val;
	strcpy(node->oras, oras);
	node->next=NULL;
	return node;
}

node_t *append_node(node_t *list_head, int val, char oras[40])
{
	node_t *aux=list_head;
	node_t *new_node,*head;
	new_node=create(val,oras);
	head=list_head;
	if(list_head==NULL)
    {
        new_node->next=list_head;
        return new_node;
    }
	while(head!=NULL)
    {
        aux=head;
        head=head->next;
    }
    aux->next=new_node;
    new_node->next=NULL;
	return list_head;
}

int get_node(node_t *list_head, char oras[40])
{
	while(list_head!=NULL)
    {
        if(strcmp(list_head->oras,oras)==0)
        {
            return list_head->val;
        }
        list_head=list_head->next;
    }
	return -1;
}

char* aflare_oras(node_t *head, int n)
{
    node_t *node;
    int i;
    node=head;
    for(i=0;i<n;i++)
    {
        node=node->next;
    }
    return node->oras;
}

Graph* creare_graf(Graph *g)
{
    g = (Graph *) malloc (sizeof(Graph));
    if (g==NULL)
    {
        printf ( "no memory for this graph");
        return NULL;
    }
    g->v=0;
    g->e=0;
    return g;
}

/*void alocare_matrice(int ***a,int n)
{
    int i;
    *a = (int **) malloc(n*sizeof(int*));
    for (i=0;i<n;i++)
        *a[i] = (int *) calloc(n, sizeof(int));
    if (a==NULL)
    {
        printf ( " no memory for this matrix");
        exit(1);
    }
}*/
void alocare_matrice(Graph *g)
{
    int i;
    g->a = (int **) malloc(g->v*sizeof(int*));
    for (i=0;i<g->v;i++)
        g->a[i] = (int *) calloc(g->v, sizeof(int));
    if (g->a==NULL)
    {
        printf ( " no memory for this matrix");
        exit(1);
    }
}

void afisare_matrice(FILE *f,int **a,int n,char fisier[20])
{
    int i,j;
    if((f=fopen(fisier,"wt"))==NULL)
    {
        puts("Fisierul nu poate fi deschis!\n");
        exit(1);
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            fprintf(f,"%d ",a[i][j]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}



/**Dijkstra**/
int printSolution(int dist[], int n, int pred[])
{
    FILE *f;
    if((f=fopen("dijkstra.txt","wt"))==NULL)
    {
        puts("Fisierul nu poate fi deschis!\n");
        exit(1);
    }
    fprintf(f,"Varf - Distanta fata de sursa - Varful precedent\n");
    for (int i = 0; i < n; i++)
        fprintf(f,"%d              %d                %d\n", i, dist[i], pred[i]);
    fclose(f);
}

int minDistance(int dist[], int sps[], int V)
{
    int v, min = INT_MAX, min_index;
    for ( v = 0; v < V; v++)
    {
        if (sps[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(Graph *g, int s, int **cost,int dist[], int sps[],int pred[])
{
    int i, j, u;
    for ( i = 0; i < g->v; i++)
    {
        dist[i] = INT_MAX;
        sps[i] = 0;
        pred[i]=-1;
    }
    dist[s] = 0;
    for (j = 0; j < g->v-1; j++)
    {
        u = minDistance(dist, sps, g->v);
        sps[u] = 1;
        for (i = 0; i < g->v; i++)
        {
            if (sps[i] == 0 && g->a[u][i]!=0 && dist[u] != INT_MAX && dist[u]+cost[u][i] < dist[i])
            {
                dist[i] = dist[u] + cost[u][i];
                pred[i]=u;
            }
        }
    }
    printSolution(dist, g->v,pred);
}

void drum(int dist[], int pred[], int nod1, int nod2,node_t *head, char fisier[])
{
    FILE *f;
    if((f=fopen(fisier,"at"))==NULL)
    {
        puts("Fisierul nu poate fi deschis!\n");
        exit(1);
    }
    stack_t *stiva;
    int nod;
    stiva=stack_create();
    stack_push(stiva,nod2);
    while(nod2!=nod1)
    {
        nod2=pred[nod2];
        stack_push(stiva,nod2);
    }
    while(stack_empty(stiva)==0)
    {
        nod=stack_pop(stiva);
        fprintf(f,"%s\n",aflare_oras(head,nod));
    }
}




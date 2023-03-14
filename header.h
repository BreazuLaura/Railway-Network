#include <stdio.h>

typedef struct z
{
    int v;
    int e;
    int **a,**cost;
}Graph;

typedef struct elem
{
	int val;
	char oras[40];
	struct elem *next;

} node_t;

node_t *create(int val, char oras[40]);
node_t *append_node(node_t *list_head, int val, char oras[40]);
int get_node(node_t *list_head, char oras[20]);
Graph* creare_graf(Graph *g);
//void alocare_matrice(int ***a,int n);
void alocare_matrice(Graph *g);
void afisare_matrice(FILE *f,int **a,int n,char fisier[20]);
char* aflare_oras(node_t *head, int n);
int printSolution(int dist[], int n, int pred[]);
int minDistance(int dist[], int sps[], int V);
void dijkstra(Graph *g, int s, int **cost,int dist[], int sps[],int pred[]);
void drum(int dist[], int pred[], int nod1, int nod2,node_t *head, char fisier[]);


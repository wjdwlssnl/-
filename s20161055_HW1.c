//20161055 ������
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS 

typedef struct node {
	int data; //����� �̸�(0~7������ ����) ����
	struct node *parent;
}node;

typedef struct edge {
	node *u;
	int cost;
	node *v;
}edge;

void bubblesort(edge** a, int b);
void MST_Kruskal(int, edge**a, edge**b);
node* Find(node*);
node* Union(node* p, node* q);

int main(void)
{
	int N_v;
	int **A; //��ü �׷���
	int *Asub; //A�� �����ϴ� �迭
	edge **mst; //��� �׷���
	edge **edges; //edge ���� �迭
	node **nodes; //node ���� �迭

				  //In_Kruskal.txt �Է�, N_v�� ���� ���� ����
	FILE*temp = fopen("In_Kruskal.txt", "r");
	fscanf(temp, "%d", &N_v);

	//���� �Ҵ�
	A = (int**)malloc(N_v * sizeof(int*));	
	mst = (edge*)malloc(N_v * sizeof(edge));
	edges = (edge**)malloc((N_v*N_v - N_v) * sizeof(edge*));
	nodes = (node**)malloc(N_v * sizeof(node*));


	//adjacency matrix�� 2���� �迭 A�� ����, ��� ����
	node* u;
	for (int i = 0; i < N_v; i++) {
		Asub = (int*)malloc(N_v * sizeof(int));
		A[i] = Asub;
		for (int j = 0; j < N_v; j++) {
			fscanf(temp, "%d", &Asub[j]);
		}
		u = (node*)malloc(sizeof(node));
		u->data = i; u->parent = NULL;     //�ʱ�ȭ�� ���� ��� parent==NULL
		nodes[i] = u;                      //nodes �迭���� �� ������ �ּҸ� �����Ѵ�
		//printf("%d\n", nodes[i]->data);
	}
	fclose(temp);


	//edges �迭�� edge ���� 
	int k = 0; //k=������ ����, 21
	edge* t;
	for (int i = 0; i < N_v; i++) {
		for (int j = i + 1; j <N_v; j++) {
			t = (edge*)malloc(sizeof(edge));
			t->u = nodes[i];
			t->cost = A[i][j];
			t->v = nodes[j];
			edges[k] = t;   //edges �迭���� �� �������� �ּҸ� �����Ѵ�.
			//printf("k=%d\tcost=%d\n", k,edges[k]->cost);
			k++;
		}
	}
	
	//����ġ ������������ edges �迭 ����
	bubblesort(edges, k);
	

	//kruskal ����
	MST_Kruskal(N_v, edges, mst);


	//output ���: ��� �׷����� �����ϴ� �������� �� �� ���� index �� ���
	FILE *fp = fopen("Out_Kruskal.txt", "w");
	
	for (int i = 0; i < N_v-1; i++) {
		fprintf(fp,"%d %d\n",mst[i]->u->data, mst[i]->v->data);
		printf("%d %d\n\n", mst[i]->u->data, mst[i]->v->data);
	}
	fclose(fp);
	
	system("pause");
	return 0;
}

void bubblesort(edge**X, int len) {
	edge *temp;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len - 1; j++) {
			if (X[j]->cost > X[j + 1]->cost) {
				temp = X[j];
				X[j] = X[j + 1];
				X[j + 1] = temp;
			}
		}		
	}
}


void MST_Kruskal(int N_v, edge **edges, edge **mst) {
	int mst_num = 0; //mst�� ���Ե� edge ��
	edge* e;
	int i = 0; int j = 0;
	node* a;
	node* b;

	while (mst_num < N_v-1) {
		//���ĵ� �迭���� ���� e ����
		//���ĵ� �迭���� ���õ� ������ ������ ����
		//printf("i=%d\n", i);
		e = edges[i]; i++;

		a = Find(e->u); b = Find(e->v);

		if (a != b) {
			Union(a, b);
			//mst�� ���� e �߰�
			mst[mst_num] = e;
			//printf("mst_num=%d e=%d\n", mst_num, e->cost);
			mst_num++;
		}
	}
}

node* Find(node* a) { //a ����� root�� ��ȯ
	while (a->parent != NULL) {
		a = a->parent;
	}
	//printf("\nFOUND A'S PARENT: %d\n", a->data);
	return a;
}


node* Union(node* p, node* q) { //�� ������ ��ģ��
	p->parent = q;
	return q;
}

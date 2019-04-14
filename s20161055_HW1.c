//20161055 김정진
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS 

typedef struct node {
	int data; //노드의 이름(0~7까지의 숫자) 저장
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
	int **A; //전체 그래프
	int *Asub; //A를 구성하는 배열
	edge **mst; //결과 그래프
	edge **edges; //edge 저장 배열
	node **nodes; //node 저장 배열

				  //In_Kruskal.txt 입력, N_v에 정점 개수 저장
	FILE*temp = fopen("In_Kruskal.txt", "r");
	fscanf(temp, "%d", &N_v);

	//동적 할당
	A = (int**)malloc(N_v * sizeof(int*));	
	mst = (edge*)malloc(N_v * sizeof(edge));
	edges = (edge**)malloc((N_v*N_v - N_v) * sizeof(edge*));
	nodes = (node**)malloc(N_v * sizeof(node*));


	//adjacency matrix를 2차원 배열 A에 저장, 노드 생성
	node* u;
	for (int i = 0; i < N_v; i++) {
		Asub = (int*)malloc(N_v * sizeof(int));
		A[i] = Asub;
		for (int j = 0; j < N_v; j++) {
			fscanf(temp, "%d", &Asub[j]);
		}
		u = (node*)malloc(sizeof(node));
		u->data = i; u->parent = NULL;     //초기화된 노드는 모두 parent==NULL
		nodes[i] = u;                      //nodes 배열에는 각 노드들의 주소를 저장한다
		//printf("%d\n", nodes[i]->data);
	}
	fclose(temp);


	//edges 배열에 edge 저장 
	int k = 0; //k=간선의 개수, 21
	edge* t;
	for (int i = 0; i < N_v; i++) {
		for (int j = i + 1; j <N_v; j++) {
			t = (edge*)malloc(sizeof(edge));
			t->u = nodes[i];
			t->cost = A[i][j];
			t->v = nodes[j];
			edges[k] = t;   //edges 배열에는 각 엣지들의 주소를 저장한다.
			//printf("k=%d\tcost=%d\n", k,edges[k]->cost);
			k++;
		}
	}
	
	//가중치 오름차순으로 edges 배열 정렬
	bubblesort(edges, k);
	

	//kruskal 실행
	MST_Kruskal(N_v, edges, mst);


	//output 출력: 결과 그래프를 구성하는 간선들의 양 끝 정점 index 쌍 출력
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
	int mst_num = 0; //mst에 포함된 edge 수
	edge* e;
	int i = 0; int j = 0;
	node* a;
	node* b;

	while (mst_num < N_v-1) {
		//정렬된 배열에서 엣지 e 선택
		//정렬된 배열에서 선택된 엣지는 고려대상 제외
		//printf("i=%d\n", i);
		e = edges[i]; i++;

		a = Find(e->u); b = Find(e->v);

		if (a != b) {
			Union(a, b);
			//mst에 엣지 e 추가
			mst[mst_num] = e;
			//printf("mst_num=%d e=%d\n", mst_num, e->cost);
			mst_num++;
		}
	}
}

node* Find(node* a) { //a 노드의 root를 반환
	while (a->parent != NULL) {
		a = a->parent;
	}
	//printf("\nFOUND A'S PARENT: %d\n", a->data);
	return a;
}


node* Union(node* p, node* q) { //두 집합을 합친다
	p->parent = q;
	return q;
}

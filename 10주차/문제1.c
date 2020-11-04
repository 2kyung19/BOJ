#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//��������Ʈ - �迭
typedef struct incidence { //list
	int edge;
	struct incidence* next;
}INCIDENCE;

typedef struct vertices { //����
	INCIDENCE* incidence;
	int elem;
}VERTICES;

typedef struct edge { //����
	int vertex1;
	int vertex2;
	int weight;
}EDGE;

typedef struct graph {
	VERTICES vertices[7]; //���Ǹ� ���� index�� 1���� ����
	EDGE edges[21];
	int edgeSize;
}GRAPH;

INCIDENCE* getIncidence(int edge) {
	INCIDENCE* node = (INCIDENCE*)malloc(sizeof(INCIDENCE));

	node->next = NULL;
	node->edge = edge;

	return node;
}

void initGraph(GRAPH* graph);
void insertIncidence(int v1, int v2, INCIDENCE* incidence, GRAPH* graph);
void deleteIncidence(int v1, int v2, GRAPH* graph);
void insertEdge(int v1, int v2, int w, GRAPH* graph);
void updateEdge(int v1, int v2, int w, GRAPH* graph);
void deleteEdge(int v1, int v2, GRAPH* graph);
void printEdge(int v, GRAPH* graph);

int main() {
	GRAPH graph;
	char order;
	int a, b, w;

	initGraph(&graph);

	while (1) {
		scanf("%c", &order);
		getchar();

		if (order == 'a') {
			scanf("%d", &a); //node
			getchar();

			printEdge(a, &graph);
		}
		else if (order == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			getchar();

			if (w != 0) updateEdge(a, b, w, &graph);
			else deleteEdge(a, b, &graph);
		}
		else if (order == 'q') break;
	}
	return 0;
}

void initGraph(GRAPH* graph) {
	graph->edgeSize = 0;

	for (int i = 1; i <= 6; i++) {
		graph->vertices[i].incidence = NULL;
		graph->vertices[i].elem = i;
	}

	insertEdge(1, 2, 1, graph);
	insertEdge(1, 3, 1, graph);
	insertEdge(1, 4, 1, graph);
	insertEdge(1, 6, 2, graph);
	insertEdge(2, 3, 1, graph);
	insertEdge(3, 5, 4, graph);
	insertEdge(5, 5, 4, graph);
	insertEdge(5, 6, 3, graph);

}

void insertIncidence(int v1, int v2, INCIDENCE* incidence, GRAPH* graph) {
	EDGE* edge = graph->edges;
	VERTICES* vertices = graph->vertices;
	INCIDENCE* p;
	int other;

	p = vertices[v1].incidence;
	if (p == NULL) vertices[v1].incidence = incidence; //ù ���

	else { //�������� ����
		//head�� ��
		if (edge[p->edge].vertex1 == v1) other = edge[p->edge].vertex2;
		else other = edge[p->edge].vertex1;

		if (other > v2) { //head���� ��ȯ
			incidence->next = p;
			vertices[v1].incidence = incidence;
		}

		else {
			while (p->next != NULL) {
				if (edge[p->next->edge].vertex1 == v1) other = edge[p->next->edge].vertex2;
				else other = edge[p->next->edge].vertex1;

				if (other > v2) break;
				p = p->next;
			}

			if (p->next == NULL) p->next = incidence;
			else {
				incidence->next = p->next;
				p->next = incidence;
			}
		}
	}
}

void deleteIncidence(int v1, int v2, GRAPH* graph) {
	EDGE* edge = graph->edges;
	VERTICES* vertices = graph->vertices;
	INCIDENCE* p, * del = NULL;
	int other;

	p = vertices[v1].incidence;
	if (p == NULL) return;
	
	//head�� ��
	if (edge[p->edge].vertex1 == v1) other = edge[p->edge].vertex2;
	else other = edge[p->edge].vertex1;

	if (other == v2) { //head���� ����
		vertices[v1].incidence = p->next;
		free(p);
	}

	else {
		while (p->next != NULL) {
			if (edge[p->next->edge].vertex1 == v1) other = edge[p->next->edge].vertex2;
			else other = edge[p->next->edge].vertex1;

			if (other == v2) break;

			p = p->next;
		}

		if (p->next == NULL) return;

		else { //�翬��
			p->next = p->next->next;
		}
	}
}

void insertEdge(int v1, int v2, int w, GRAPH* graph) {
	EDGE *edge = graph->edges;
	INCIDENCE *incidence1, *incidence2;
	int other, index = -1;

	//edges list�� �ߺ� �˻� �� �߰�
	for (int i = 0; i < graph->edgeSize; i++) {
		if (edge[i].vertex1 == v1 && edge[i].vertex2 == v2) {
			edge[i].weight = w;
			index = i;
			break;
		}
		if (edge[i].vertex1 == v2 && edge[i].vertex2 == v1) {
			edge[i].weight = w;
			index = i;
			break;
		}
	}

	if (index == -1) {
		index = graph->edgeSize;
	}

	edge[index].vertex1 = v1;
	edge[index].vertex2 = v2;
	edge[index].weight = w;

	//incidence node ���� �� �߰�
	incidence1 = getIncidence(index);
	incidence2 = getIncidence(index);

	insertIncidence(v1, v2, incidence1, graph);

	if (v1 != v2) {
		insertIncidence(v2, v1, incidence2, graph);
	}

	graph->edgeSize += 1;
}

void updateEdge(int v1, int v2, int w, GRAPH* graph) {
	EDGE* edge = graph->edges;
	INCIDENCE* p = graph->vertices[v1].incidence;
	int other, check = 0;

	if (v1 < 1 || v1 > 6 || v2 < 1 || v2 > 6) {
		printf("-1\n");
		return;
	}

	if (p == NULL) insertEdge(v1, v2, w, graph);
	else {
		while (p != NULL) {
			if (edge[p->edge].vertex1 == v1) other = edge[p->edge].vertex2;
			else other = edge[p->edge].vertex1;

			if (other == v2) { //����ġ ����
				edge[p->edge].weight = w;
				check = 1;
				break;
			}
			p = p->next;
		}
		if (check == 0) insertEdge(v1, v2, w, graph); //���ο� ���� ����
	}
}

void deleteEdge(int v1, int v2, GRAPH* graph) {
	EDGE* edge = graph->edges;
	VERTICES* vertices = graph->vertices;
	INCIDENCE* p;
	int other, index = 0;

	if (v1 < 1 || v1 > 6 || v2 < 1 || v2 > 6) {
		printf("-1\n");
		return;
	}

	//edges list�� insert���� �ߺ� �˻��ϹǷ� ���� ���� X
	//incidence node ����
	deleteIncidence(v1, v2, graph);

	if (v1 != v2) {
		deleteIncidence(v2, v1, graph);
	}

	graph->edgeSize -= 1;
}

void printEdge(int v, GRAPH* graph) {
	VERTICES* vertices = graph->vertices;
	EDGE* edge = graph->edges;
	INCIDENCE* p = vertices[v].incidence;
	int other;

	if (v < 1 || v>6) { //�������� �ʴ� ����ȣ
		printf("-1\n");
		return;
	}

	if (p == NULL) return;

	while (p != NULL) {
		if (edge[p->edge].vertex1 == v) other = edge[p->edge].vertex2;
		else other = edge[p->edge].vertex1;

		printf(" %d %d", other, edge[p->edge].weight);
		p = p->next;
	}
	printf("\n");
}
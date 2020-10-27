#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node
{
    int key;
    int c;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

void swap(int* a, int* b)
{
    int tmp;
    tmp = *b;
    *b = *a;
    *a = tmp;
}

Node* getnode() {
    Node* n = (Node*)malloc(sizeof(Node));
    n->left = NULL;
    n->right = NULL;
    return n;
}

void upHeap(Node* v)
{
    if (v->parent == NULL) // �ش� ��尡 ��Ʈ�� ��� ��ȯ
        return;
    if (v->key >= (v->parent)->key) // �ش� ����� Ű�� �θ� ����� Ű���� ũ�ų� ���� ��� ��ȯ
        return;
    swap(&(v->key), &(v->parent)->key); // 1, 2�� �ش����� ������ �� ���� �Ӽ��� ��߳��Ƿ� ����
    upHeap(v->parent); // �θ��带 ���ڷ� ���
}

void expandExternal(Node* z)
{
    Node* l = getnode();
    Node* r = getnode();

    l->parent = z;
    l->c = 1;

    r->parent = z;
    r->c = 2;

    z->left = l;
    z->right = r;

    return;
}

Node* advanceLast(Node* last)
{
    Node* v = last;

    while (v->c == 2) // ���� ��尡 ������ �ڽ��� ����
        v = v->parent; // �θ� ���� �̵�

    while (v->c == 1) // ���� ��尡 ���� �ڽ��� ����
        v = (v->parent)->right; // ���� ���� �̵�

    while (v->left != NULL && v->right != NULL) // ���� ��尡 ���� ����� ���� 
        v = v->left; // ���� �ڽ����� �̵�

    return v;
}

Node* retreatLast(Node* v)
{
    while (v->c == 1) // ���� ��尡 ���� �ڽ��� ����
        v = v->parent; // �θ� ���� �̵�

    while (v->c == 2) // ���� ��尡 ������ �ڽ��� ����
        v = (v->parent)->left; // ���� ���� �̵�

    while (v->left != NULL && v->right != NULL) // ���� ��尡 ���� ����� ����
        v = v->right; // ������ �ڽ����� �̵�
    
    return v;
}

Node* insertItem(int k, Node* last)
{
    Node* z, * L;

    L = advanceLast(last);
    z = L;
    z->key = k;
    expandExternal(z);
    upHeap(z);

    return L;
}

void print_Tree(Node* tree)
{
    if (tree->left != NULL && tree->right != NULL) {
        printf(" %d", tree->key);
        print_Tree(tree->left);
        print_Tree(tree->right);
    }
}

int main()
{
    int i, n, k;

    Node* tree = getnode();
    Node* last = tree;
    tree->parent = NULL;
    tree->c = 0;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &k);

        last = insertItem(k, last);
    }

    print_Tree(tree);

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<time.h>

int* buildList(int n, int min, int max); //��������Ʈ ����
int* copyList(int* L, int n); //��������Ʈ L�� ����
void buildHeap(int* H, int n); //��������Ʈ�� ������
int findKthSmallest(int* H, int n, int k); //k��°�� ���� �� ã��
int removeMin(int* H, int n); //�ּҰ� ����
void downHeap(int* H, int i, int n);
void swapElements(int* H, int i, int j);
void writeList(int* L, int n);

int main(void) {
	int* L, * H;
	int output[5], karray[5] = { 1, 100, 99900, 99999 };
	int e, k;

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	srand(time(NULL));
	QueryPerformanceFrequency(&ticksPerSec);
	
	/* n = 10 */
	L = buildList(10, 1, 100);

	writeList(L, 10); //��������Ʈ L ���

	for (k = 1; k <= 3; k++) { //k(=1,2,3) ��°�� ���� �� ã�� ���
		H = copyList(L, 10); //H�� L�� ����
		output[k] = findKthSmallest(H, 10, k);
	}
	writeList(&output, 3);

	free(L); free(H);

	/* n = 100000 */
	L = buildList(100000, 1, 1000000);
	
	for (k = 0; k < 4; k++) { //k(=1,100,99900,99999) ��°�� ���� �� ã�� ���
		H = copyList(L, 100000); //H�� L�� ����

		QueryPerformanceCounter(&start);

		e = findKthSmallest(H, 100000, karray[k]);

		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%-6d  %8.4fms\n",e, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
	}

	free(L); free(H);

	return 0;
}

int* buildList(int n, int min, int max) {
	int *L = (int*)malloc(sizeof(int) * (n + 1));

	for (int i = 1; i <= n; i++) { //min ~ max ������ rand �� �Ҵ�
		L[i] = ((((long)rand() << 15) | rand()) % max) + min;
	}

	return L;
}

int* copyList(int* L, int n) {
	int* H = (int*)malloc(sizeof(int) * (n + 1));

	for (int i = 1; i <= n; i++) {
		H[i] = L[i]; //�ʱ� ��������Ʈ L�� ���� H�� ����
	}

	return H;
}

void buildHeap(int* H, int n) {
	for (int i = n / 2; i >= 1; i--) {
		downHeap(H, i, n); //�� ���� �Ӽ� ����
	}
}

int findKthSmallest(int* H, int n, int k) {
	int smaller = 0;

	buildHeap(H, n); //����� �� ���� : O(n)

	for (int i = 0; i < k; i++) { //k��°�� ���� �� : O(k)
		smaller = removeMin(H, n); //root ���� : O(log n)
		n--;
	}//O(k*log n)

	
	return smaller;
}

int removeMin(int* H, int n) {
	int key;
	
	//root�� ������ ��� �� ����
	key = H[1];
	H[1] = H[n];

	downHeap(H, 1, --n); //������ ��� ���� �� ������ �Ӽ� ����

	return key; //���� root �� ��ȯ
}

void downHeap(int *H, int i, int n) {
	int smaller;

	if (i * 2 > n) return; //�ڽ��� ������

	//���� �ڽİ� ������ �ڽ� �� ���� ���� ����
	smaller = i * 2;
	if (n >= i * 2 + 1 && H[smaller] > H[i * 2 + 1]) {
		smaller = i * 2 + 1;
	}

	//�ڽĺ��� �θ� �� ���� ���̸�
	if (H[i] <= H[smaller]) return;

	//�ڽ��� �θ𺸴� �� ������
	swapElements(H, i, smaller);

	downHeap(H, smaller, n);
}

void swapElements(int* H, int i, int j) {
	int temp;

	temp = H[i];
	H[i] = H[j];
	H[j] = temp;
}

void writeList(int* L, int n) {
	for (int i = 1; i <= n; i++) {
		printf("%d ", L[i]);
	}
	printf("\n");
}
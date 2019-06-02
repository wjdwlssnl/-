//20161055 ������
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS 

void Merge(int low, int mid, int high);
int *A; // ���� ������ �迭
int *B; // Merge�� �ʿ��� �迭 

int main(void)
{
	int n;	
	int l;
	int i,j;
	int mid, high;

	FILE*temp = fopen("Input.txt", "r");

	while (1) {	
		// Input.txt���� ���� ���� n�� n���� ���� �о� �鿩 A�� ����		
		fscanf(temp, "%d", &n);

		if (n == 0) break; // n�� 0�� �ԷµǸ� �Է� ����.
		if (n == 1) { // n�� 1�ϰ�� ó��
			FILE *fp = fopen("Output.txt", "a");
			A = (int*)malloc(n * sizeof(int));
			fscanf(temp, "%d", &A[0]);
			fprintf(fp, "%d ", A[0]);
			fprintf(fp, "\n");
			fclose(fp);
			printf("%d\n", A[0]);
			continue;
		}

		A = (int*)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) {
			fscanf(temp, "%d", &A[i]);
		}

		// Merge �Լ� ȣ���� ���� A�� bottom-up ������� ����
		l = 1;
		while (l < n) {
			i = 0;
			while (i < n) {
				high = i + l - 1 + l;
				mid = i + l - 1;
				if (high < n) //�����Ѱ͸� �켱 merge
					Merge(i, mid, high);
				else 
					break;
				i += (2 * l);
			}

			//���κ� ó��
			// n�� �ٲ�� high�� n-1�� �ٲ� merge ����
			
			int n_2 = n - 1 - i + 1; //���κ��� ũ��

			if (n_2 > l) { //���� ���κ��� ���̰� �Ӻ��� ��ٸ� merge ����
				Merge(i, i + l - 1, n - 1);
			}
			//���κ��� ���̰� �Ӻ��� ���ų� ������ �״�� �д�
			
			l = 2 * l;
		}
		
		// ���ĵ� ����� Output.txt�� ���
		for (i = 0; i < n; i++) {
			printf("%d ", A[i]);
		}
		printf("\n");

		FILE *fp = fopen("Output.txt", "a");

		for (int i = 0; i < n; i++) {
			fprintf(fp, "%d ", A[i]);			
		}
		fprintf(fp, "\n");
		fclose(fp);
	}

	system("pause");
	return 0;
}

void Merge(int low, int mid, int high)
{
	int m = high - low + 1;
	B = (int*)malloc(m * sizeof(int));
	int k = 0;
	int i = low;
	int j = mid + 1;

	/*A�� ����� �� ���� ���ĵ� ����Ʈ A[low..mid]�� A[mid+1..high]��
	�ϳ��� ���ĵ� ����Ʈ A[low..high]�� �����.*/ 
	while (k < m) {
		if (A[i] <= A[j]) {
			B[k] = A[i]; i++;
			if (i == mid + 1) break;
		}
		else {
			B[k] = A[j]; j++;
			if (j == high + 1) break;
		}
		k++;
	}
	if (i < mid + 1) {
		while (i < mid + 1) {
			k++;
			B[k] = A[i]; i++;
		}
	}
	else if (j < high + 1) {
		while (j < high + 1) {
			k++;
			B[k] = A[j]; j++;
		}
	}

	k = 0;
	for (i = low; i <= high; i++) {
		A[i] = B[k]; k++;
	}
}
//20161055 김정진
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS 

void Merge(int low, int mid, int high);
int *A; // 수를 저장할 배열
int *B; // Merge에 필요한 배열 

int main(void)
{
	int n;	
	int l;
	int i,j;
	int mid, high;

	FILE*temp = fopen("Input.txt", "r");

	while (1) {	
		// Input.txt에서 수의 개수 n과 n개의 수를 읽어 들여 A에 저장		
		fscanf(temp, "%d", &n);

		if (n == 0) break; // n에 0이 입력되면 입력 종료.
		if (n == 1) { // n이 1일경우 처리
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

		// Merge 함수 호출을 통해 A를 bottom-up 방식으로 정렬
		l = 1;
		while (l < n) {
			i = 0;
			while (i < n) {
				high = i + l - 1 + l;
				mid = i + l - 1;
				if (high < n) //가능한것만 우선 merge
					Merge(i, mid, high);
				else 
					break;
				i += (2 * l);
			}

			//끝부분 처리
			// n이 바뀌고 high가 n-1로 바뀐 merge 수행
			
			int n_2 = n - 1 - i + 1; //끝부분의 크기

			if (n_2 > l) { //만약 끝부분의 길이가 ㅣ보다 길다면 merge 수행
				Merge(i, i + l - 1, n - 1);
			}
			//끝부분의 길이가 ㅣ보다 같거나 작으면 그대로 둔다
			
			l = 2 * l;
		}
		
		// 정렬된 결과를 Output.txt에 출력
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

	/*A에 저장된 두 개의 정렬된 리스트 A[low..mid]와 A[mid+1..high]를
	하나의 정렬된 리스트 A[low..high]로 만든다.*/ 
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
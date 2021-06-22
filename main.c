#include "matrix.h"

int main() {
	srand((unsigned int)time(NULL));
	int n, count = 0;
	double time = 0;
	MX* m = (struct Matrix*)malloc(sizeof(struct Matrix));
	m->detScore = NULL;
	printf("Kind matrix input :\n1)Entering data from the keyboard.\n2)Entering data from a file.\n3)Random data entry.\nSelecting the input number: ");
	scanf_s("%d", &n);
	choice(m, &n);
	
	printf("\nDeterminant = %d !\n", m->deter);
	MX* m1 = (struct Matrix*)malloc(sizeof(struct Matrix));
	randMat(m1, 5, 5);
	clock_t begin = clock();
	det(m1);
	clock_t end = clock();
	time = (end - begin);
	if (time > 1) {
		printf("it cost: %lf seconds\n", time / 1000);
	}
	else {
		printf("so ez no time\n");
	}


	//printMatrix(m);
	//det(m);
	//printf("\nDeterminant = %d !\n", m->deter);
	//printMatrix(m);


	freeMem(m1);
	freeMem(m);
	return 0;
}
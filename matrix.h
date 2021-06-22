#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <conio.h>

struct Matrix {
	double** body;
	int rows;
	int cols;
	int deter;
	int detScore;
};

typedef struct Matrix MX;

void safeOpenFile(FILE** in, char* name, char* mode);
int isEmpty(FILE* in);
unsigned int countLin(FILE** in);
unsigned int countColumn(FILE** in);
MX* scanMat(MX* matrix);
MX* fileScanMat(FILE** in, MX* matrix);
void freeMem(MX* matrix);
int randMat(MX* matrix, int rows, int cols);
void printMatrix(MX* matrix);
void scan(MX* matrix);
void fileScan(MX* matrix);
void randEl(MX* matrix);
void choice(MX* matrix, int* n);
int det(MX* matrix);
int gaussElimination(MX* matrix);
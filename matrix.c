#include "matrix.h"

void choice(MX * matrix, int* n) {
    switch (*n) {
    case 1:
        scan(matrix);
        break;
    case 2:
        fileScan(matrix);
        break;
    case 3:
        randEl(matrix);
        break;
    }
}

void scan(MX* matrix) {
    scanMat(matrix);
    printMatrix(matrix);
    if (matrix->rows == matrix->cols) matrix->deter = det(matrix);
    else {
        printf("the determinant of the matrix can't be calculated, write the matrix correctly\n");
        return 0;
    }
}

void fileScan(MX* matrix) {
    FILE* in;
    safeOpenFile(&in, "matrix.txt", "r");
    isEmpty(in);
    int k = fileScanMat(&in, matrix);
    if (k == 0) {
        printf("the determinant of the matrix can't be calculated, write the matrix correctly\n");
        return 0;
    }
    printMatrix(matrix);
    matrix->deter = det(matrix);
}

void randEl(MX* matrix) {
    int lines = 0, colums = 0;
    printf("enter the dimensions of the square matrix: ");
    scanf_s("%d", &lines);
    colums = lines;
    if (!randMat(matrix, lines, colums)) {
        printf("the determinant of the matrix can't be calculated, write the matrix correctly\n");
        return 0;
    }
    else {
        printMatrix(matrix);
        matrix->deter = det(matrix);
    }
}

unsigned int countLin(FILE** in) {
    unsigned line = 0;
    while (!feof(*in)) {
        if (fgetc(*in) == '\n') ++line;
    }
    rewind(*in);
    return(++line);
}

unsigned int countColumn(FILE** in) {
    char ch;
    unsigned column = 0;
    while (!feof(*in)) {
        ch = fgetc(*in);
        if (ch == ' ') {
            ++column;
        }
        if (ch == '\n') {
            ++column;
            break;
        }
    }
    rewind(*in);
    return(column);
}

MX* fileScanMat(FILE** in, MX* matrix) {  
    int rows = countLin(in);
    int cols = countColumn(in);
    (matrix)->rows = rows;
    (matrix)->cols = cols;
    if (rows == cols) {
        matrix->body = (double**)malloc(rows * sizeof(double*));
        for (int i = 0; i < rows; ++i) {
            (matrix->body)[i] = (double*)malloc(cols * sizeof(double));
            for (int j = 0; j < cols; ++j) {
                fscanf_s(*in, "%lf ", &(matrix->body)[i][j]);
            }
        }
        return matrix;
    }
    else return 0;
}

void freeMem(MX* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->body[i]);
    }
    free(matrix);
}

MX* scanMat(MX* matrix) {
    printf("enter matrix size 1-10\n-> ");
    int matrix_size;
    scanf_s("%d", &matrix_size);
    if (matrix_size > 10 || matrix_size < 0) {
        printf("\nwrong size or syntax");
        exit(1);
    }
    printf("\n");
    matrix->body = (double**)malloc(sizeof(double*) * matrix_size);
    for (int i = 0; i < matrix_size; ++i) {
        (matrix->body)[i] = (double*)malloc(sizeof(double) * matrix_size);
    }
    matrix->cols = matrix_size;
    matrix->rows = matrix_size;
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            printf("Enter value of %d-%d of matrix -> ", i, j);
            scanf_s("%lf", &(matrix->body)[i][j]);
            if ((matrix->body)[i][j] > 100 || (matrix->body)[i][j] < -100) {
                printf("so big or wrong syntax");
                exit(2);
            }
        }
    }
    return(matrix);
}

int randMat(MX* matrix, int rows, int cols) {
    matrix->rows = rows;
    matrix->cols = cols;
    if (rows == cols) {
        matrix->body = (double**)malloc(rows * sizeof(double*));
        for (int i = 0; i < rows; ++i) {
            (matrix->body)[i] = (double*)malloc(cols * sizeof(double));
            for (int j = 0; j < cols; ++j) {
                (matrix->body)[i][j]= rand()%10;
            }
        }
        return 1;
    }
    else return 0;
}

int gaussElimination(MX* matrix) {
    int i, j=0, k;
    int swapCount = 0;
    for (i = 0; i < matrix->rows - 1; i++) {
        for (k = i + 1; k < matrix->rows - 1; k++) {
                if (fabs(matrix->body[k][j]) < fabs(matrix->body[i][j])) {
                    swapCount++;
                    for (j = 0; j < matrix->cols; j++) {
                        double temp;
                        temp = matrix->body[i][j];
                        matrix->body[i][j] = matrix->body[k][j];
                        matrix->body[k][j] = temp;
                    }
                }
            }
        for (int k = i + 1; k < matrix->rows; k++) {
            double term = matrix->body[k][i] / matrix->body[i][i];
            for (int j = 0; j < matrix->cols; j++) {
                matrix->body[k][j] -= term * matrix->body[i][j];
            }
        }
    }
    return swapCount;
}

int det(MX* matrix) {
    if (matrix->detScore) return matrix->deter;
    MX** current = (struct Matrix**)malloc(sizeof(struct Matrix*));
   *current = matrix;
    if ((*current)->rows == 1) {
        ++matrix->detScore;
        return (int)(*current)->body[0][0];
    }
    else if ((*current)->rows == 2) {
        ++matrix->detScore;
        return (int)((*current)->body[0][0] * (*current)->body[1][1] - (*current)->body[0][1] * (*current)->body[1][0]);
    }
    else {
        int det = 1;
        int swapCount = gaussElimination(current);
        for (int i = 0; i < (*current)->cols; i++) {
            det = det * (*current)->body[i][i];
        } 
        ++matrix->detScore;
        return (int)det * pow(-1, swapCount);
    }
  
    freeMem(current);
}

void safeOpenFile(FILE** in, char* name, char* mode) {
    int err = (fopen_s(in, name, mode));
    if (err != 0) {
        printf("Can't open file %s\n", name);
        printf(" Value of errno: %d\n ", errno);
        if (errno == 1) printf("Operation not permitted.\n");
        if (errno == 2)printf("No such file or directory.\n");
        if (errno == 3) printf("Permission denied.\n");
        if (errno == 5) printf("I/O error.");
        exit(-1);
    }
}

int isEmpty(FILE* in) {
    char ch;
    fscanf_s(in, "%c", &ch, 1);
    rewind(in);
    if (ch == EOF) {
        return 1;
    }
    else return 0;
}

void printMatrix(MX* matrix) {
    printf("\nMatrix:\n");
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j)
            printf("%.0lf ", matrix->body[i][j]);
        printf("\n");
    }
}
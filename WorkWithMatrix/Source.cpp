#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>

struct Matrix
{
    int rows, cols;
    double** Array;
};

//����������� � ����
void put_on_file(Matrix A)
{
    FILE* f = fopen("NewFile.txt", "a+");
    if (f != NULL)
    {
        fprintf(f, "%d ", A.rows);
        fprintf(f, "%d ", A.cols);
        for (int i = 0; i < A.rows; i++)
        {
            for (int j = 0; j < A.cols; j++)
            {
                fprintf(f, "%lf", A.Array[i][j]);
                fprintf(f, "%c", ' ');
            }
        }
        fprintf(f, "%c", '\n');
        fclose(f);
    }
    else
    {
        printf("������! �� ������� ������� ����!\n");
        return;
    }
}

//������ � �����
//void get_from_file(Matrix A)
//{
//    FILE* f = fopen("NewFile.txt", "r");
//    if (f == NULL)
//    {
//        printf("������! �� ������� ������� ����!\n");
//        return;
//    }
//    for (int i = 0; i < A.rows; i++)
//    {
//        for (int j = 0; j < A.cols; j++)
//        {
//            fscanf(f, "%lf\t", &A.Array[i][j]);
//        }
//    }
//    fclose(f);
//}

//�������� ������ (��������� ������ ��� ���)
Matrix array_alloc(Matrix A)
{
    A.Array = (double**)malloc(A.rows * sizeof(double*));
    for (int i = 0; i < A.rows; i++)
    {
        A.Array[i] = (double*)malloc(A.cols * sizeof(double));
    }
    return A;
}

Matrix matrix_alloc(int n, int m)
{
    Matrix A;
    A.rows = n;
    A.cols = m;
    A.Array = (double**)malloc(A.rows * sizeof(double*));
    for (int i = 0; i < A.rows; i++)
    {
        A.Array[i] = (double*)malloc(A.cols * sizeof(double));
    }
    return A;
}

//������������ ������
void array_free(Matrix A)
{
    for (int i = 0; i < A.rows; i++)
    {
        free(A.Array[i]);
    }
    free(A.Array);
}

//����� ������� �� ����� ������������
void array_print(Matrix A)
{
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            printf("%lf \t", A.Array[i][j]);
        }
        printf("\n");
    }
}

//��������� ���� ������
Matrix array_multiply(Matrix A, Matrix B)
{
    int n = A.rows;
    int m = B.cols;
    Matrix C = matrix_alloc(n, m);
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < B.cols; j++)
        {
            C.Array[i][j] = 0;
            for (int k = 0; k < A.cols; k++)
            {
                C.Array[i][j] += A.Array[i][k] * B.Array[k][j];
            }
        }
    }
    return C;
}

//����� ���� ������
Matrix array_sum(Matrix A, Matrix B)
{
    int n = A.rows;
    int m = A.cols;
    Matrix C = matrix_alloc(n, m);
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            C.Array[i][j] = A.Array[i][j] + B.Array[i][j];
        }
    }
    return C;
}

//��������� �� �����
Matrix array_on_number(Matrix A, int number)
{
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            A.Array[i][j] = A.Array[i][j] * number;
        }
    }
    return A;
}

//���������� ���������
void bubble_sort_toMAX(Matrix A)
{
    double tmp;
    size_t i, j, k, jp, ip;
    size_t size = A.rows * A.cols;
    bool flag;
    do {
        flag = 0;
        for (k = 1; k < size; k++)
        {
            j = k / A.rows;
            i = k - j * A.rows;
            jp = (k - 1) / A.rows;
            ip = (k - 1) - jp * A.rows;
            if (A.Array[i][j] < A.Array[ip][jp])
            {
                tmp = A.Array[i][j];
                A.Array[i][j] = A.Array[ip][jp];
                A.Array[ip][jp] = tmp;
                flag = 1;
            }
        }
    } while (flag);
}

void bubble_sort_toMIN(Matrix A)
{
    double tmp;
    size_t i, j, k, jp, ip;
    size_t size = A.rows * A.cols;
    bool flag;
    do {
        flag = 0;
        for (k = 1; k < size; k++)
        {
            j = k / A.rows;
            i = k - j * A.rows;
            jp = (k - 1) / A.rows;
            ip = (k - 1) - jp * A.rows;
            if (A.Array[i][j] > A.Array[ip][jp])
            {
                tmp = A.Array[i][j];
                A.Array[i][j] = A.Array[ip][jp];
                A.Array[ip][jp] = tmp;
                flag = 1;
            }
        }
    } while (flag);
}

void main()
{
    setlocale(0, "russian");
    srand(time(NULL));
    Matrix A, B;
    do
    {
        printf("������������, ��� ���������� ���������� ������� ��� ��������� ��������� �������� ��� ���������.\n");
        printf("��� ������ ������� ���� ������� �� ������.\n");
        printf("��������� � ���������� �������� ������!\n");
        printf("������� ���������� ����� ������� A: ");
        scanf_s("%d", &A.rows);
        printf("������� ���������� �������� ������� A: ");
        scanf_s("%d", &A.cols);
        A = array_alloc(A);
        for (int i = 0; i < A.rows; i++)
        {
            for (int j = 0; j < A.cols; j++)
            {
                A.Array[i][j] = ((double)rand() / (double)(RAND_MAX)) * 100;
            }
        }
        put_on_file(A);
        printf("���� ������� A:\n");
        array_print(A);

        printf("������� ���������� ����� ������� B: ");
        scanf_s("%d", &B.rows);
        printf("������� ���������� �������� ������� B: ");
        scanf_s("%d", &B.cols);
        B = array_alloc(B);
        for (int i = 0; i < B.rows; i++)
        {
            for (int j = 0; j < B.cols; j++)
            {
                B.Array[i][j] = ((double)rand() / (double)(RAND_MAX)) * 100;
            }
        }
        put_on_file(B);
        printf("���� ������� B:\n");
        array_print(B);
        if (A.cols != B.rows)
        {
            printf("��� ���� ������� ������ �������� ���� �� �����!\n");
            printf("���������: ����� �������� ���� ������� �� ������, ����� ����� ���������� �������� ������� � ��������� � ����������� ����� ������� B! (m1 = n2)\n");
            printf("������� ����� �������� ������!\n");
        }
    } while (A.cols != B.rows);

    Matrix C;
    C.rows = A.rows;
    C.cols = B.cols;
    C = array_multiply(A, B);
    put_on_file(C);
    printf("��� ��������� ������ ���������� ���������:\n");
    array_print(C);

    Matrix D, E;
    do
    {
        printf("������ ������ ���� ������� � ������.\n");
        printf("��������� � ���������� �������� ������!\n");
        printf("������� ���������� ����� ������� D: ");
        scanf_s("%d", &D.rows);
        printf("������� ���������� �������� ������� D: ");
        scanf_s("%d", &D.cols);
        D = array_alloc(D);
        for (int i = 0; i < D.rows; i++)
        {
            for (int j = 0; j < D.cols; j++)
            {
                D.Array[i][j] = ((double)rand() / (double)(RAND_MAX)) * 100;
            }
        }
        put_on_file(D);
        printf("���� ������� D:\n");
        array_print(D);

        printf("������� ���������� ����� ������� E: ");
        scanf_s("%d", &E.rows);
        printf("������� ���������� �������� ������� E: ");
        scanf_s("%d", &E.cols);
        E = array_alloc(E);
        for (int i = 0; i < E.rows; i++)
        {
            for (int j = 0; j < E.cols; j++)
            {
                E.Array[i][j] = ((double)rand() / (double)(RAND_MAX)) * 100;
            }
        }
        put_on_file(E);
        printf("���� ������� E:\n");
        array_print(E);
        if ((D.rows != E.rows) && (D.cols != E.cols))
        {
            printf("��� ���� ������� ������ �������!\n");
            printf("���������: ����� ������� ��� �������, ����� ����� ���������� ����� � �������� ������� D ��������� � ����������� ����� � �������� ������� E!\n");
            printf("������� ����� �������� ������!\n");
        }
    } while ((D.rows != E.rows) && (D.cols != E.cols));

    Matrix F = array_sum(D, E);
    put_on_file(F);
    printf("��� �������� ������ ���������� ���������:\n");
    array_print(F);

    Matrix J, H;
    printf("������ ����������� �������.\n");
    printf("��������� � ���������� �������� ������!\n");
    printf("������� ���������� ����� ������� J: ");
    scanf_s("%d", &J.rows);
    printf("������� ���������� �������� ������� J: ");
    scanf_s("%d", &J.cols);
    J = array_alloc(J);
    for (int i = 0; i < J.rows; i++)
    {
        for (int j = 0; j < J.cols; j++)
        {
            J.Array[i][j] = ((double)rand() / (double)(RAND_MAX)) * 100;
        }
    }
    put_on_file(J);
    printf("���� ������� J:\n");
    array_print(J);
    bubble_sort_toMAX(J);
    put_on_file(J);
    printf("���� ��������������� ������� J �� �����������:\n");
    array_print(J);
    bubble_sort_toMIN(J);
    put_on_file(J);
    printf("���� ��������������� ������� J �� ��������:\n");
    array_print(J);

    printf("������� ������� �� �����.\n");
    printf("��������� � ���������� �������� ������!\n");
    printf("������� ���������� ����� ������� H: ");
    scanf_s("%d", &H.rows);
    printf("������� ���������� �������� ������� H: ");
    scanf_s("%d", &H.cols);
    H = array_alloc(H);
    for (int i = 0; i < H.rows; i++)
    {
        for (int j = 0; j < H.cols; j++)
        {
            H.Array[i][j] = ((double)rand() / (double)(RAND_MAX)) * 10;
        }
    }
    put_on_file(H);
    printf("���� ������� H:\n");
    array_print(H);
    int number = 0;
    printf("������� ����� �����: ");
    scanf_s("%d", &number);
    array_on_number(H, number);
    put_on_file(H);
    printf("���� ����� ������� H, ���������� �� %d:\n", number);
    array_print(H);


    array_free(A);
    array_free(B);
    array_free(C);
    array_free(D);
    array_free(E);
    array_free(F);
    array_free(J);
    array_free(H);
}
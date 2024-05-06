﻿#include <stdio.h>
#include <thread>
#define ROW 3
#define COL 3
#define n = 3
int res = 0;
//Выполнил студент 31 группы Трухачев Максим

void multiplyMatrix(int matrixA[ROW][COL], int matrixB[COL][COL], int result[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            result[i][j] = 0;
            for (int k = 0; k < COL; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}





int matrixelemmult(int index[], int matrixA[ROW][COL], int matrixB[COL][COL], int& res ) {
    int i = index[0];
    int j = index[1];
    for (int k = 0; k < ROW; k++) {
        res += matrixA[i][k] * matrixB[k][j];
    }
    return res;
}

int main() {
    int matrixA[ROW][COL] = { {1, 2, 3}, {4, 5, 6}, {6, 7, 8} };
    int matrixB[COL][COL] = { {7, 8, 9}, {9, 10, 11}, {11, 12, 13} };
    int result[ROW][COL];
    int resultWithoutThreads[ROW][COL];
    int index00[] = { 0,0 };
    int index01[] = { 0,1 };
    int index02[] = { 0,2 };
    int index10[] = { 1,0 };
    int index11[] = { 1,1 };
    int index12[] = { 1,2 };
    int index20[] = { 2,0 };
    int index21[] = { 2,1 };
    int index22[] = { 2,2 };
    int result00 = 0;
    int result01 = 0;
    int result02 = 0;
    int result10 = 0;
    int result11 = 0;
    int result12 = 0;
    int result20 = 0;
    int result21 = 0;
    int result22 = 0;
    
    
    clock_t start1 = clock();
    std::thread th1(matrixelemmult, index00, matrixA, matrixB, std::ref(result00));
    th1.join();
    result[0][0] = result00;
    std::thread th2(matrixelemmult, index01, matrixA, matrixB, std::ref(result01));
    th2.join();
    result[0][1] = result01;
    std::thread th3(matrixelemmult, index02, matrixA, matrixB, std::ref(result02));
    th3.join();
    result[0][2] = result02;
    std::thread th4(matrixelemmult, index10, matrixA, matrixB, std::ref(result10));
    th4.join();
    result[1][0] = result10;
    std::thread th5(matrixelemmult, index11, matrixA, matrixB, std::ref(result11));
    th5.join();
    result[1][1] = result11;
    std::thread th6(matrixelemmult, index12, matrixA, matrixB, std::ref(result12));
    th6.join();
    result[1][2] = result12;
    std::thread th7(matrixelemmult, index20, matrixA, matrixB, std::ref(result20));
    th7.join();
    result[2][0] = result20;
    std::thread th8(matrixelemmult, index21, matrixA, matrixB, std::ref(result21));
    th8.join();
    result[2][1] = result21;
    std::thread th9(matrixelemmult, index22, matrixA, matrixB, std::ref(result22));
    th9.join();
    result[2][2] = result22;
    clock_t end1 = clock();
    double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    printf("RunTime with threads : %f sec\n", seconds1);

    clock_t start2 = clock();
    multiplyMatrix(matrixA, matrixB, resultWithoutThreads);
    clock_t end2 = clock();
    double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("RunTime without threads : %f sec\n", seconds2);
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
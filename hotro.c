#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hotro.h"
#include "menu.h"

// ham dem nguoc chuyen huong
void stop(int t, const char *s) {
    while (t > 0) {
        printf("\rChuyen huong den %s sau %d giay !", s, t);
        sleep(1);
        t--;
    }
    printf("\nDang chuyen huong den %s ...\n", s);
    sleep(1);
}

// ham xoa man hinh
void xoaMH(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
// Ham doc tai khoan tu file
void docTaiKhoanTuFile(NguoiDungNode **head) {
    FILE *a;
    char *pass = (char*)malloc(15 * sizeof(char));
    NguoiDungNode *temp = (NguoiDungNode*)malloc(sizeof(NguoiDungNode));
    if (temp == NULL) {
        perror("Loi cap phat bo nho: ");
        exit(1);
    }
    a = fopen("nguoidung.txt", "r");
    if (a == NULL) {
        perror("Loi file: ");
        exit(1);
    }
    while (fscanf(a, "%[^|]|%[^|]|%d\n", temp->username, pass, &temp->type) == 3) {
        strcpy(temp->password, pass);
        temp->next = *head;
        *head = temp;
        temp = (NguoiDungNode*)malloc(sizeof(NguoiDungNode));
        if (temp == NULL) {
            perror("Loi cap phat bo nho: ");
            exit(1);
        }
    }
    free(temp);
    free(pass);
    fclose(a);
}

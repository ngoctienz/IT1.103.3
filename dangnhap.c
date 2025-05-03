#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dangnhap.h"
#include "hotro.h"

//Ham doc file user
int docTaiKhoan(char *user, char *pass) {
    FILE *a;
    char user_temp[15];
    char pass_temp[15];
    int type;
    a = fopen("nguoidung.txt", "r");
    if (a == NULL) {
        perror("Loi file: ");
        exit(1);
    }
    while (fscanf(a, "%[^|]|%[^|]|%d\n", user_temp, pass_temp, &type) == 3) {
        if ((strcmp(user, user_temp) == 0) && (strcmp(pass, pass_temp) == 0)) {
            fclose(a);
            return type; // Dung tai khoan thi tra ve luon
        }
    }
    fclose(a);
    return 0;
}

// ham dang nhap
int dangNhap(void) {
    char *user = (char*)malloc(15 * sizeof(char));
    char *pass = (char*)malloc(15 * sizeof(char));
    int c, check;
    printf("===== HE THONG DANG NHAP =====\n");

    do {
        printf("Nhap ten dang nhap: ");
        scanf("%s", user);
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Nhap mat khau: ");
        scanf("%s", pass);
        while ((c = getchar()) != '\n' && c != EOF);
        check = docTaiKhoan(user, pass);
        if (check != 0) {
            printf("Dang nhap thanh cong!\n");
            stop(3, (check == 1) ? "MENU QUAN TRI VIEN" : "MENU KHACH HANG");
        } else {
            xoaMH();
            printf("Tai khoan hoac mat khau chua chinh xac !\n");
        }
    } while (check == 0);
    free(user);
    free(pass);
    return check;
}
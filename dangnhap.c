#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dangnhap.h"
#include "hotro.h"

//Ham doc file user
int docTaiKhoan(char *user, char *pass) {
    FILE *a;
    char *user_temp = (char*)malloc(15 * sizeof(char));
    char *pass_temp = (char*)malloc(15 * sizeof(char));
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
int dangNhap(char *user) {
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
            printf("User: %s\n", user);
            stop(3, (check == 1) ? "MENU QUAN TRI VIEN" : "MENU KHACH HANG");
        } else {
            xoaMH();
            printf("Tai khoan hoac mat khau chua chinh xac !\n");
        }
    } while (check == 0);
    free(pass);
    return check;
}


// ham dang ky
int dangKy(char *user) {
    FILE *a;
    char *pass = (char*)malloc(15 * sizeof(char));
    char c;
    NguoiDungNode *head = NULL, *temp = NULL, *newNode = NULL;
    int check = 0;

    docTaiKhoanTuFile(&head);

    do {
        printf("Nhap ten dang nhap: ");
        scanf("%s", user);
        while ((c = getchar()) != '\n' && c != EOF);
        check = 0;
        for (temp = head; temp != NULL; temp = temp->next) {
            if (strcmp(user, temp->username) == 0) {
                check = 1;
                break;
            }
        }
        if (check == 1) {
            xoaMH();
            printf("Ten dang nhap da ton tai! Vui long chon ten khac.\n");
        } else {
            printf("Nhap mat khau: ");
            scanf("%s", pass);
            while ((c = getchar()) != '\n' && c != EOF);
            newNode = (NguoiDungNode*)malloc(sizeof(NguoiDungNode));
            if (newNode == NULL) {
                perror("Loi cap phat bo nho: ");
         
                return -1; 
            }
            strcpy(newNode->username, user);
            strcpy(newNode->password, pass);
            newNode->type = 2; // User
            newNode->next = head;
            head = newNode;
            a = fopen("nguoidung.txt", "a");
            if (a != NULL) {
                fprintf(a, "%s|%s|%d\n", user, pass, 2);
                fclose(a);
                xoaMH();
                printf("Dang ky thanh cong!\nVui long dang nhap lai!\n");
                break; 
            } else {
                perror("Loi mo file de ghi: ");
            }
            check = 0;
        }
    } while (check == 1);

    NguoiDungNode *current = head;
    NguoiDungNode *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(user);
    free(pass);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dangnhap.h"
#include "hotro.h"
#define RESET_COLOR   "\x1b[0m"
#define BOLD          "\x1b[1m"
#define GREEN         "\x1b[32m"
#define RED           "\x1b[31m"
#define YELLOW        "\x1b[33m"
#define CYAN          "\x1b[36m"
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
    int UserType = 0;
    xoaMH();
    printf(BOLD CYAN "===== HE THONG DANG NHAP =====\n" RESET_COLOR);
    do {
        printf(YELLOW "Nhap ten dang nhap: " RESET_COLOR);
        scanf("%s", user);
        while ((c = getchar()) != '\n' && c != EOF);
        printf(YELLOW "Nhap mat khau: " RESET_COLOR);
        scanf("%s", pass);
        while ((c = getchar()) != '\n' && c != EOF);
        UserType = docTaiKhoan(user, pass);
        if (UserType == 0) {
            xoaMH();
            printf(RED BOLD "Ten dang nhap hoac mat khau khong dung!\n" RESET_COLOR);
            printf(YELLOW "Nhan Enter de nhap lai hoac nhap 0 de quay lai menu chinh: " RESET_COLOR);
             char temp_choice[10];
             fgets(temp_choice, sizeof(temp_choice), stdin);
            if (strcmp(temp_choice, "0\n") == 0 || strcmp(temp_choice, "0\r\n") == 0) {
                 free(pass);
                 user[0] = '\0';
                 return 0;
            }
            xoaMH();
            printf(BOLD CYAN "===== HE THONG DANG NHAP =====\n" RESET_COLOR);
        } else {
            printf(GREEN BOLD "Dang nhap thanh cong!\n" RESET_COLOR);
            stop(2, "Menu");
            free(pass);
            return UserType;
        }
    } while (UserType == 0);
    free(pass);
    return 0;
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
        printf(YELLOW"Nhap ten dang nhap: "RESET_COLOR);
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
            printf(RED"Ten dang nhap da ton tai! Vui long chon ten khac.\n"RESET_COLOR);
        } else {
            printf(YELLOW"Nhap mat khau: "RESET_COLOR);
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

#include <stdio.h>
#include <stdlib.h>
#include "dangnhap.h"
#include "menu.h"
#include "hotro.h"

int main(void) {
    char c;
    int choice;
    int UserType = 0; // bien luu loai nguoi dung
                     // 0: khong tim thay, 1: admin, 2: user

    // Mang luu  ten nguoi dung
    char *user;
    user = (char*)malloc(15 * sizeof(char));


     do {
         menudangNhap();
         scanf("%d", &choice);
        while ((c = getchar()) != '\n' && c != EOF); // xoa bo dem
         switch (choice) {
             case 1:
                 xoaMH();
                 UserType = dangNhap(user);
                 break;
             case 2:
                 xoaMH();
                 UserType = dangKy(user);
                 break;
             case 3:
                 printf("Cam on ban da su dung he thong!\n");
                 exit(0);
             default:
                 xoaMH();
                 printf("Lua chon khong hop le!\n");
         }
     } while (UserType == 0);
    chonMenu(UserType,user);
    // Giai phap bo nho da cap phat cho user
    free(user);
    return 0;
}
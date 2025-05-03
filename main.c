#include <stdio.h>
#include <stdlib.h>
#include "dangnhap.h"
#include "menu.h"
#include "hotro.h"

int main(void) {
    int choice, UserType = 0;

    do {
        menudangNhap();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                xoaMH();
                UserType = dangNhap();
                break;
            case 2:
                xoaMH();
                UserType = dangKy();
                break;
            case 3:
                printf("Cam on ban da su dung he thong!\n");
                exit(0);
            default:
                xoaMH();
                printf("Lua chon khong hop le!\n");
        }
    } while (UserType == 0);

    chonMenu(UserType);
 
 
    return 0;
}
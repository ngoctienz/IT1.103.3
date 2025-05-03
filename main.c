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
                printf("Dang ky tai khoan moi thanh cong!\n");
                break;
            case 3:
                printf("Cam on ban da su dung he thong!\n");
                exit(0);
            default:
                xoaMH();
                printf("Lua chon khong hop le!\n");
        }
    } while (UserType == 0);

    if (UserType == 1) {
        xoaMH();
        menuQuanTriVien();
    } else if (UserType == 2) {
        xoaMH();
        menuKhachHang();
    } else {
        return 1;
    }

    return 0;
}
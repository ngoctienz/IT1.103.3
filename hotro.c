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

// ham chon menu
void chonMenu(int n) {
    if (n == 1) {
        xoaMH();
        menuQuanTriVien();
    } else if (n == 2) {
        xoaMH();
        menuKhachHang();
    } else {
        exit(0);
    }
}
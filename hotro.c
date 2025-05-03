#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hotro.h"

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
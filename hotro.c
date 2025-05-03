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
    int choice;
    if (n == 1) {
        do {
            xoaMH();
            menuQuanTriVien();
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    do {
                        xoaMH();
                        menuQuanLyPhim();
                        scanf("%d", &choice);
                        if (choice == 5) break;
                    } while (choice != 5);
                    break;
                case 2:
                    do {
                        xoaMH();
                        menuQuanLyLichChieu();
                        scanf("%d", &choice);
                         if (choice == 5) break;
                    } while (choice != 5);
                    break;
                case 3:
                    do {
                        xoaMH();
                        menuQuanLyVeVaThongKe();
                        scanf("%d", &choice);
                        if (choice == 5) break;
                    } while (choice != 5);
                    break;
                case 4:
                    do {
                        xoaMH();
                        menuQuanLyTaiKhoanNguoiDung();
                        scanf("%d", &choice);
                        if (choice == 3) break;
                    } while (choice != 3);
                    break;
                case 5:
                    xoaMH();
                    printf("Dang xuat thanh cong!\n");
                    return; // Sử dụng return để thoát khỏi hàm
                default:
                    xoaMH();
                    printf("Lua chon khong hop le!\n");
            }
        } while (1); 
    } else if (n == 2) {
        do {
            xoaMH();
            menuKhachHang();
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    xoaMH();
                    printf("Danh sach phim:\n");
                    // xem danh sach phim
                    break;
                case 2:
                    xoaMH();
                    printf("Dat ve xem phim:\n");
                    // dat ve xem phim
                    break;
                case 3:
                    xoaMH();
                    printf("Ve da dat:\n");
                    // xem ve da dat
                    break;
                case 4:
                    xoaMH();
                    printf("Huy ve da dat:\n");
                    // huy ve da dat
                    break;
                case 5:
                    xoaMH();
                    printf("Dang xuat thanh cong!\n");
                    return; // Sử dụng return để thoát khỏi hàm
                default:
                    xoaMH();
                    printf("Lua chon khong hop le!\n");
            }
        } while (1);
    } else {
        exit(0);
    }
}

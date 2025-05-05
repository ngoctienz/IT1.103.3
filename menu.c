#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "hotro.h"

// Ham menudangNhap
void menudangNhap(void) {
    printf("===== HE THONG DAT VE XEM PHIM =====\n");
    printf("Chao mung!\n");
    printf("1. Dang nhap\n");
    printf("2. Dang ky tai khoan moi\n");
    printf("3. Thoat\n");
    printf("------------------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuKhachHang
void menuKhachHang(char *user) {
    printf("===== MENU KHACH HANG =====\n");
    printf("Chao mung: %s\n", user);
    printf("1. Xem danh sach phim\n");
    printf("2. Dat ve xem phim\n");
    printf("3. Xem ve da dat\n");
    printf("4. Huy ve da dat\n");
    printf("5. Dang xuat\n");
    printf("--------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuQuanTriVien
void menuQuanTriVien(char *user) {
    printf("===== MENU QUAN TRI VIEN =====\n");
    printf("Admin: %s\n", user);
    printf("1. Quan ly Phim\n");
    printf("2. Quan ly Lich chieu\n");
    printf("3. Quan ly Du lieu Ve va Thong ke\n");
    printf("4. Quan ly Tai khoan Nguoi dung\n");
    printf("5. Dang xuat\n");
    printf("-----------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuQuanLyPhim
void menuQuanLyPhim(char *user) {
    printf("===== QUAN LY PHIM =====\n");
    printf("Admin: %s\n", user);
    printf("1. Them phim moi\n");
    printf("2. Sua thong tin phim\n");
    printf("3. Xoa phim\n");
    printf("4. Hien thi danh sach phim\n");
    printf("5. Quay lai Menu chinh\n");
    printf("------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuQuanLyLichChieu
void menuQuanLyLichChieu(char *user) {
    printf("===== QUAN LY LICH CHIEU =====\n");
    printf("Admin: %s\n", user);
    printf("1. Them lich chieu moi\n");
    printf("2. Sua thong tin lich chieu\n");
    printf("3. Hien thi danh sach lich chieu\n");
    printf("4. Cap nhat so do ghe ngoi (trang thai)\n");
    printf("5. Quay lai Menu chinh\n");
    printf("----------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuQuanLyVeVaThongKe
void menuQuanLyVeVaThongKe(char *user) {
    printf("===== QUAN LY VE & THONG KE =====\n");
    printf("Admin: %s\n", user);
    printf("1. Xem danh sach tat ca ve da dat\n");
    printf("2. Xu ly ve bi huy (cap nhat trang thai)\n");
    printf("3. Thong ke doanh thu\n");
    printf("4. Xuat bao cao thong ke\n");
    printf("5. Quay lai Menu chinh\n");
    printf("------------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuQuanLyTaiKhoanNguoiDung
void menuQuanLyTaiKhoanNguoiDung(char *user) {
    printf("===== QUAN LY TAI KHOAN NGUOI DUNG ======\n");
    printf("Admin: %s\n", user);
    printf("1. Xem danh sach nguoi dung\n");
    printf("2. Xoa tai khoan nguoi dung\n");
    printf("3. Quay lai Menu chinh\n");
    printf("------------------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// ham chon menu
void chonMenu(int n, char *user) {    
    int choice;
    if (n == 1) {
        do {
            xoaMH();
            menuQuanTriVien(user);
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    do {
                        xoaMH();
                        menuQuanLyPhim( user);
                        scanf("%d", &choice);
                        if (choice == 5) break;
                    } while (choice != 5);
                    break;
                case 2:
                    do {
                        xoaMH();
                        menuQuanLyLichChieu(user);
                        scanf("%d", &choice);
                         if (choice == 5) break;
                    } while (choice != 5);
                    break;
                case 3:
                    do {
                        xoaMH();
                        menuQuanLyVeVaThongKe(user);
                        scanf("%d", &choice);
                        if (choice == 5) break;
                    } while (choice != 5);
                    break;
                case 4:
                    do {
                        xoaMH();
                        menuQuanLyTaiKhoanNguoiDung(user);
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
            menuKhachHang(user);
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                do {
                    xoaMH();
                    inDanhSachPhim();
                    printf("Nhap  0 de quay lai: ");
                    scanf("%d", &choice);
                    if (choice == 0) 
                    break;
                } while (choice != 0);
                break;                              
                case 2:
                    do{
                        xoaMH();
                        datVe(user);
                        printf("Nhap 0 de quay lai: ");
                        scanf("%d", &choice);
                        if (choice == 0) 
                        break;
                    } while (choice != 0);
                    break;
                case 3:
                do{
                    xoaMH();
                    inVeDaDat(user);
                    printf("Nhap 0 de quay lai: ");
                    scanf("%d", &choice);
                    if (choice == 0) 
                    break;
                } while (choice != 0);
                break;
                case 4:
                do{
                    xoaMH();
                    huyVeDaDat(user);
                    printf("Nhap 0 de quay lai: ");
                    scanf("%d", &choice);
                    if (choice == 0) 
                    break;
                } while (choice != 0);
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

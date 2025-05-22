#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "hotro.h"
#include "dangnhap.h"
// Ham menudangNhap
void menudangNhap(void) {
    xoaMH();
    printf(BOLD BLUE"+----------------------------------+\n"RESET_COLOR);
    printf(BOLD BLUE"|"RESET_COLOR);
    printf(BOLD BLUE"====" RED" HE THONG DAT VE XEM PHIM"BOLD BLUE" ===="RESET_COLOR);
    printf(BOLD BLUE"|\n");
    printf("+----------------------------------+\n"RESET_COLOR);
    printf(BOLD BLUE"|"RESET_COLOR,RED"          Chao mung!              "RESET_COLOR"|\n");
    
    printf(BOLD YELLOW" 1. Dang nhap                     "RESET_COLOR);
    printf(BOLD BLUE"|\n");
    printf(BOLD BLUE"|");
    printf(BOLD YELLOW" 2. Dang ky tai khoan moi         "RESET_COLOR);
    printf(BOLD BLUE"|\n");
    printf("|");
    printf(BOLD YELLOW" 3. Thoat                         "RESET_COLOR);
    printf(BOLD BLUE"|\n");
    printf(BOLD BLUE"+----------------------------------+\n"RESET_COLOR);
    printf(BOLD GREEN);
    printf("Nhap lua chon cua ban: ");
    printf(RESET_COLOR);
}
// Ham menuKhachHang
void menuKhachHang(char *user) {
    xoaMH();
    printf(BOLD BLUE"+----------------------------------+\n");
    printf("|");
    printf(BOLD RED);
    printf("         MENU KHACH HANG          ");
    printf(RESET_COLOR);
    printf(BOLD BLUE"|\n");
    printf(BOLD BLUE"+----------------------------------+\n");
    printf("|" BOLD GREEN " Chao mung: %-21s " RESET_COLOR, user); printf(BOLD BLUE"|\n");
    printf("+----------------------------------+\n");
    printf("|"); 
    printf(BOLD YELLOW " 1. Xem danh sach phim            "); 
    printf(BOLD BLUE "|\n");
    printf("|"); 
    printf(BOLD YELLOW " 2. Dat ve xem phim               "); 
    printf(BOLD BLUE "|\n");
    printf("|"); 
    printf(BOLD YELLOW " 3. Xem ve da dat                 "); 
    printf( BOLD BLUE"|\n");
    printf("|"); 
    printf(BOLD YELLOW " 4. Huy ve da dat                 "); 
    printf(BOLD BLUE "|\n");
    printf("|"); 
    printf(BOLD YELLOW " 5. Doi mat khau                  ");
    printf(BOLD BLUE "|\n");
    printf("|"); 
    printf(BOLD YELLOW " 6. Dang xuat                     "); 
    printf(BOLD BLUE "|\n");
    printf("+----------------------------------+\n"RESET_COLOR);
    printf(YELLOW);
    printf("Nhap lua chon cua ban: ");
    printf(RESET_COLOR);
}
// Ham menuQuanTriVien
void menuQuanTriVien(char *user) {
    xoaMH();
    printf(BLUE"+--------------------------------------+\n");
    printf("|");
    printf(BOLD YELLOW);
    printf(RED"         MENU QUAN TRI VIEN           "RESET_COLOR);
    printf(BLUE"|\n");
    printf("+--------------------------------------+\n");
    printf("|" BOLD GREEN " Admin: %-28s  " RESET_COLOR , user);printf(BLUE "|\n");
    printf("+--------------------------------------+\n");
    printf("|");
    printf(BOLD YELLOW " 1. Quan ly Phim                      "); 
    printf(BLUE"|\n");
    printf("|"); 
    printf(BOLD YELLOW " 2. Quan ly Du lieu Ve va Thong ke    "); 
    printf( BLUE"|\n");
    printf("|"); 
    printf(BOLD YELLOW " 3. Quan ly Tai khoan Nguoi dung      ");
    printf( BLUE"|\n");
    printf("|"); 
    printf(BOLD YELLOW " 4. Doi mat khau                     ");
    printf( BLUE"|\n");
    printf("|"); 
    printf( BOLD YELLOW" 5. Dang xuat                         "); 
    printf( BLUE"|\n");
    printf("+--------------------------------------+\n");
    printf(GREEN);
    printf("Nhap lua chon cua ban: ");
    printf(RESET_COLOR);
}
// Ham menuQuanLyPhim
void menuQuanLyPhim(char *user) {
    xoaMH();
    printf(BOLD BLUE"+----------------------------------+\n");
    printf("|");
    printf(BOLD YELLOW);
    printf(RED"          QUAN LY PHIM            "RESET_COLOR);
    printf(RESET_COLOR);
    printf(BOLD BLUE"|\n");
    printf("+----------------------------------+\n"RESET_COLOR);
    printf("|"); 
    printf(BOLD YELLOW " 1. Them phim moi                  "); 
    printf(BOLD BLUE "|\n");
    printf("|"); 
    printf(BOLD YELLOW " 2. Sua thong tin phim             "); 
    printf(BOLD BLUE "|\n");
    printf("|"); 
    printf(BOLD YELLOW " 3. Xoa phim                       "); 
    printf(BOLD BLUE"|\n");
    printf("|"); 
    printf(BOLD YELLOW " 4. Hien thi danh sach phim        "); 
    printf(BOLD BLUE "|\n");
    printf("|"); 
    printf(BOLD YELLOW " 5. Quay lai Menu chinh            "); 
    printf(BOLD BLUE "|\n");
    printf("+----------------------------------+\n");
    printf(GREEN);
    printf("Nhap lua chon cua ban: ");
    printf(RESET_COLOR);
}
// Ham menuQuanLyVeVaThongKe
void menuQuanLyVeVaThongKe(char *user) {
    xoaMH();
    printf(BLUE"+--------------------------------------+\n");
    printf("|");
    printf(BOLD RED);
    printf("       QUAN LY VE & THONG KE          ");
    printf(RESET_COLOR);
    printf(BLUE"|\n");
    printf("+--------------------------------------+\n");
    printf("|"); 
    printf(BOLD YELLOW " 1. Xem danh sach tat ca ve da dat    "); 
    printf(BLUE "|\n");
    printf("|"); 
    printf(BOLD YELLOW " 2. Thong ke doanh thu                "); 
    printf( BLUE"|\n");
    printf("|"); 
    printf( BOLD YELLOW" 3. Quay lai Menu chinh               "); 
    printf( BLUE"|\n");
    printf("+--------------------------------------+\n");
    printf(GREEN);
    printf("Nhap lua chon cua ban: ");
    printf(RESET_COLOR);
}
// Ham menuQuanLyTaiKhoanNguoiDung
void menuQuanLyTaiKhoanNguoiDung(char *user) {
     xoaMH();
    printf(BOLD MAGENTA"+--------------------------------------+\n");
    printf("|");
    printf(BOLD YELLOW);
    printf("   QUAN LY TAI KHOAN NGUOI DUNG       ");
    printf(RESET_COLOR);
    printf(BOLD MAGENTA"|\n");
    printf("+--------------------------------------+\n");
    printf("|"); 
    printf(BOLD YELLOW " 1. Xem danh sach nguoi dung          "); 
    printf(BOLD MAGENTA "|\n");
    printf("|"); 
    printf(BOLD YELLOW  " 2. Xoa tai khoan nguoi dung          "); 
    printf(BOLD MAGENTA "|\n");
    printf("|"); 
    printf(BOLD YELLOW  " 3. Them tai khoan Admin              "); 
    printf(BOLD MAGENTA "|\n");
    printf("|"); 
    printf(BOLD YELLOW  " 4. Quay lai Menu chinh               "); 
    printf(BOLD MAGENTA "|\n");
    printf("+--------------------------------------+\n");
    printf(BOLD GREEN"Nhap lua chon cua ban: "RESET_COLOR);
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
                        menuQuanLyPhim(user);
                        scanf("%d", &choice);
                        switch (choice) {
                            case 1:
                            do {
                                xoaMH();
                                themPhim();
                                printf("Nhap  0 de quay lai: ");
                                scanf("%d", &choice);
                                if (choice == 0) 
                                break;
                            } while (choice != 0);
                            break;        
                            case 2:
                                xoaMH();
                                suaPhim();
                                break;        
                            case 3:
                                do {
                                    xoaMH();
                                    xoaPhim();
                                    printf("Nhap  0 de quay lai: ");
                                    scanf("%d", &choice);
                                    if (choice == 0) 
                                    break;
                                } while (choice != 0);
                                break;
                            case 4:
                                do {
                                    xoaMH();
                                    inDanhSachPhim();
                                    printf("Nhap  0 de quay lai: ");
                                    scanf("%d", &choice);
                                    if (choice == 0) 
                                    break;
                                } while (choice != 0);
                                break;                    ;
                            case 5:
                                break;
                            default:
                                xoaMH();
                                printf("Lua chon khong hop le!\n");
                        }
                        if (choice == 5) break;
                    } while (choice != 5);
                    break;
                case 2:
                    do {
                        xoaMH();
                        menuQuanLyVeVaThongKe(user);
                        scanf("%d", &choice);
                        switch (choice) {
                            case 1:
                                do {
                                    xoaMH();
                                    inDanhSachVe();
                                    printf("Nhap 0 de quay lai: ");
                                    scanf("%d", &choice);
                                    if (choice == 0) 
                                    break;
                                } while (choice != 0);
                                break;
                             case 2:
                                 do {
                                     xoaMH();
                                     thongKeDoanhThu();
                                     printf("Nhap 0 de quay lai: ");
                                     scanf("%d", &choice);
                                     if (choice == 0) 
                                     break;
                                 } while (choice != 0);
                                 break;
                            case 3:
                                break;
                            default:
                                xoaMH();
                                printf("Lua chon khong hop le!\n");
                        }
                        if (choice == 3) break;
                    } while (choice != 3);
                    break;
                case 3:
                    do {
                        xoaMH();
                        menuQuanLyTaiKhoanNguoiDung(user);
                        scanf("%d", &choice);
                        switch (choice) {
                         case 1: 
                        	do{
                        	xoaMH();
                        	inDanhSachNguoiDung();
                        	printf("Nhap 0 de quay lai: ");
                            scanf("%d", &choice);
                            if (choice == 0) 
                            break;					                                                	
                      	} while (choice != 0);
                      	break;
                      	 case 2:
                      	    do{
                      	    xoaMH();
							xoaTaiKhoanNguoiDung(user);  
							printf("Nhap 0 de quay lai: ");
                            scanf("%d", &choice);
                            if (choice == 0) 
                            break;  	
							  }while (choice != 0);
							  break;
                            
                        case 3:
                            do {
                                xoaMH();
                                themTaiKhoanAdmin();
                                printf("Nhap 0 de quay lai: ");
                                scanf("%d", &choice);
                                if (choice == 0) 
                                break;
                            } while (choice != 0);
                            break;
					}
                        if (choice == 4)
                        break;
                    } while (choice != 4);
                        break;
                
                case 4:
                    do {
                        xoaMH();
                        doiMatKhau(user);
                        printf("Nhap 0 de quay lai: ");
                        scanf("%d", &choice);
                        if (choice == 0) 
                        break;
                    } while (choice != 0);
                    break;
                
                case 5:
                    xoaMH();
                    printf("Dang xuat thanh cong!\n");
                    camOn();
                    return; 
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
                    do {
                        xoaMH();
                        doiMatKhau(user);
                        printf("Nhap 0 de quay lai: ");
                        scanf("%d", &choice);
                        if (choice == 0) 
                        break;
                    } while (choice != 0);
                    break;

                case 6:
                    xoaMH();
                    printf("Dang xuat thanh cong!\n");
                    camOn();
                    return; 
                default:
                    xoaMH();
                    printf("Lua chon khong hop le!\n");
            }
        } while (1);
    } else {
        exit(0);
    }
}

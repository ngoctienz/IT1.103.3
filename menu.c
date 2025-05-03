#include <stdio.h>
#include "menu.h"

// Ham menudangNhap
void menudangNhap() {
    printf("===== HE THONG DAT VE XEM PHIM =====\n");
    printf("Chao mung!\n");
    printf("1. Dang nhap\n");
    printf("2. Dang ky tai khoan moi\n");
    printf("3. Thoat\n");
    printf("------------------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuKhachHang
void menuKhachHang() {
    printf("===== MENU KHACH HANG =====\n");
    printf("Chao mung !\n");
    printf("1. Xem danh sach phim\n");
    printf("2. Dat ve xem phim\n");
    printf("3. Xem ve da dat\n");
    printf("4. Huy ve da dat\n");
    printf("5. Dang xuat\n");
    printf("--------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuQuanTriVien
void menuQuanTriVien() {
    printf("===== MENU QUAN TRI VIEN =====\n");
    printf("1. Quan ly Phim\n");
    printf("2. Quan ly Lich chieu\n");
    printf("3. Quan ly Du lieu Ve va Thong ke\n");
    printf("4. Quan ly Tai khoan Nguoi dung\n");
    printf("5. Dang xuat\n");
    printf("-----------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuQuanLyPhim
void menuQuanLyPhim() {
    printf("===== QUAN LY PHIM =====\n");
    printf("1. Them phim moi\n");
    printf("2. Sua thong tin phim\n");
    printf("3. Xoa phim\n");
    printf("4. Hien thi danh sach phim\n");
    printf("5. Quay lai Menu chinh\n");
    printf("------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuQuanLyLichChieu
void menuQuanLyLichChieu() {
    printf("===== QUAN LY LICH CHIEU =====\n");
    printf("1. Them lich chieu moi\n");
    printf("2. Sua thong tin lich chieu\n");
    printf("3. Hien thi danh sach lich chieu\n");
    printf("4. Cap nhat so do ghe ngoi (trang thai)\n");
    printf("5. Quay lai Menu chinh\n");
    printf("----------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuQuanLyVeVaThongKe
void menuQuanLyVeVaThongKe() {
    printf("===== QUAN LY VE & THONG KE =====\n");
    printf("1. Xem danh sach tat ca ve da dat\n");
    printf("2. Xu ly ve bi huy (cap nhat trang thai)\n");
    printf("3. Thong ke doanh thu\n");
    printf("4. Xuat bao cao thong ke\n");
    printf("5. Quay lai Menu chinh\n");
    printf("------------------------------\n");
    printf("Nhap lua chon cua ban: ");
}

// Ham menuQuanLyTaiKhoanNguoiDung
void menuQuanLyTaiKhoanNguoiDung() {
    printf("===== QUAN LY TAI KHOAN NGUOI DUNG ======\n");
    printf("1. Xem danh sach nguoi dung\n");
    printf("2. Xoa tai khoan nguoi dung\n");
    printf("3. Quay lai Menu chinh\n");
    printf("------------------------------------\n");
    printf("Nhap lua chon cua ban: ");
}
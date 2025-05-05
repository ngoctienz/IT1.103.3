#ifndef MENU_H
#define MENU_H
/*Menu dangNhap:
===== HE THONG DAT VE XEM PHIM =====
Chao mung!
1. Dang nhap
2. Dang ky tai khoan moi
3. Thoat
------------------------------------
Nhap lua chon cua ban: */
void menudangNhap(void);
/*===== MENU KHACH HANG =====
Chao mung !
1. Xem danh sach phim
2. Dat ve xem phim
3. Xem ve da dat
4. Huy ve da dat
5. Dang xuat
--------------------------
Nhap lua chon cua ban: */
void menuKhachHang(char *user);
/*===== MENU QUAN TRI VIEN =====

1. Quan ly Phim
2. Quan ly Lich chieu
3. Quan ly Du lieu Ve va Thong ke
4. Quan ly Tai khoan Nguoi dung
5. Dang xuat
-----------------------------
Nhap lua chon cua ban: */
void menuQuanTriVien(char *user);
/*===== QUAN LY PHIM =====

1. Them phim moi
2. Sua thong tin phim
3. Xoa phim
4. Hien thi danh sach phim
5. Quay lai Menu chinh

------------------------
Nhap lua chon cua ban: */
void menuQuanLyPhim(char *user);
/*===== QUAN LY LICH CHIEU =====

1. Them lich chieu moi
2. Sua thong tin lich chieu
3. Hien thi danh sach lich chieu
4. Cap nhat so do ghe ngoi (trang thai)
5. Quay lai Menu chinh

----------------------------
Nhap lua chon cua ban: */
void menuQuanLyLichChieu(char *user);
/*===== QUAN LY VE & THONG KE =====

1. Xem danh sach tat ca ve da dat
2. Xu ly ve bi huy (cap nhat trang thai)
3. Thong ke doanh thu
4. Xuat bao cao thong ke
5. Quay lai Menu chinh

------------------------------
Nhap lua chon cua ban: */
void menuQuanLyVeVaThongKe(char *user);
/*===== QUAN LY TAI KHOAN NGUOI DUNG ======

1. Xem danh sach nguoi dung
2. Xoa tai khoan nguoi dung
3. Quay lai Menu chinh

------------------------------------
Nhap lua chon cua ban: */
void menuQuanLyTaiKhoanNguoiDung(char *user);

/*Hàm chọn menu cho người dùng
 userType = 1: admin
 userType = 2: user*/
 void chonMenu(int userType, char *user);


#endif
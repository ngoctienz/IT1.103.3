#ifndef UTILS_H
#define UTILS_H

/*Hàm xóa màn hình*/
void xoaMH(void);
/*Hàm đếm ngược t giây sau đó chuyển hướng đến nhiệm vụ/ quá trình s*/
void stop(int t, const char *s);
/*Hàm chọn menu cho người dùng
 userType = 1: admin
 userType = 2: user*/
void chonMenu(int userType);

#endif
#ifndef UTILS_H
#define UTILS_H

/* danh sach lien ket nguoi dung */
typedef struct NguoiDungNode {
    char username[15];
    char password[15];
    int type;
    struct NguoiDungNode *next;
} NguoiDungNode;

/*Hàm xóa màn hình*/
void xoaMH(void);
/*Hàm đếm ngược t giây sau đó chuyển hướng đến nhiệm vụ/ quá trình s*/
void stop(int t, const char *s);

/*hàm sẽ đđọc toàn bộ nội dung của file nguoidung.txt một lần duy nhất và lưuưu vào danh sách liên kết NguoiDungNode*/ 
void docTaiKhoanTuFile(NguoiDungNode **head);

#endif
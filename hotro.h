#ifndef HOTRO_H
#define HOTRO_H

#define MAX_GHE 40
/* danh sach lien ket nguoi dung */
typedef struct NguoiDungNode {
    char username[15];
    char password[15];
    int type;
    struct NguoiDungNode *next;
} NguoiDungNode;

/* danh sách liên kết cho phim: MaPhim|TenPhim|TheLoai|NgayChieu|GioChieu|PhongChieu|GiaVe*/
typedef struct PhimNode {
    char MaPhim[15];
    char TenPhim[50];
    char TheLoai[20];
    char NgayChieu[11];
    char GioChieu[6]; 
    char PhongChieu[10];
    int GiaVe;
    struct PhimNode *next;
} PhimNode;

/* Danh sách liên kết vé: MaVe|MaPhim|TenNguoiDung|GheNgoi|TrangThai*/
typedef struct VeNode {
    char MaVe[15];
    char MaPhim[15];
    char TenNguoiDung[15];
    int GheNgoi[40]; // so ghe ngoi toi da 5 hang A,B, C, D, E danh so tu 1 den 8. VD: A1, A2 ... E8 duoc xep theo thu tu tuong ung
                     // 1: A1, 2: A2, ..., 8: A8, 9: B1, ..., 40: E8
    int TrangThai; // 0: chua dat, 1: da dat, 2: da huy
    struct VeNode *next;
} VeNode;

/*Hàm xóa màn hình*/
void xoaMH(void);
/*Hàm đếm ngược t giây sau đó chuyển hướng đến nhiệm vụ/ quá trình s*/
void stop(int t, const char *s);

/*HHàm sẽ đđọc toàn bộ nội dung của file nguoidung.txt một lần duy nhất và lưu vào danh sách liên kết NguoiDungNode*/ 
void docTaiKhoanTuFile(NguoiDungNode **head);

/*Hàm sẽ đọc toàn bộ nội dung của file phim.txt một lần duy nhất và lưu vào danh sách liên kết PhimNode*/
void docPhimTuFile(PhimNode **head);

/* Hàm in danh sách phim bằng cách đọc file phim.txt */
void inDanhSachPhim(void);

/*Hàm sẽ đọc toàn bộ nội dung của file ve.txt một lần duy nhất và lưu vào danh sách liên kết VeNode*/
void docVeTuFile(VeNode **head);

/* Hàm tạo mã vé duy nhất cho mỗi vé đặt*/
void taoMaVe(char *maVe);

/* Hàm đặt vé, thao tác trên danh sách liên kết VeNode */
void datVe(char *user);

/* Hàm ghi danh sách vé vào file ve.txt */
void ghiDanhSachVeVaoFile(VeNode *head);

/* Hàm in sơ đồ ghế ngồi cho một phim cụ thể */
void inSoDoGhe(VeNode *headVe, const char *maPhim);

/* Hàm in ra các vé đã đặt cho một phim cụ thể */
void inVeDaDat(char *user);

/* Hàm hủy vé đã đặt */
void huyVeDaDat(char *user);

/* Hàm thêm phim mới vào danh sách phim */
void themPhim(void);

/* Hàm sửa thông tin phim */
void suaPhim(void);

/* Hàm in thông tin phim */
void inThongTinPhim(PhimNode *p);

/* Hàm xóa phim */
void xoaPhim(void);

/* Hàm in danh sách vé đã đặt sap xếp theo mã phim */
void inDanhSachVe(void);

/* Hàm thống kê doanh thu theo phim*/
void thongKeDoanhThu(void);

/* Hàm ghi danh sách người dùng vào file nguoidung.txt */
void ghiDanhSachNguoiDungVaoFile(NguoiDungNode *head);

/* Hàm in danh sách tất cả người dùng (Admin only) */
void inDanhSachNguoiDung(void);

/* Hàm xóa tài khoản người dùng (Admin only) */
void xoaTaiKhoanNguoiDung(char *adminUser);
#endif
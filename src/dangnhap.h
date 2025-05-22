#ifndef DANGNHAP_H
#define DANGNHAP_H

/*Hàm đăng nhập
trả về trả về 1 nếu là admin; trả về 2 nếu là user*/
int dangNhap(char *user);
/*Hàm đọc file user và trả về ba giá trị uername, pass, usertype 
 File txt có dạng:
admin123|12345|1
user123|123456789|2
trả về 0 nếu sai user hoặc pass; trả về 1 nếu là admin; trả về 2 nếu là user*/
int docTaiKhoan(char *user, char *pass);

/*Hàm đăng kí tài khoản mới (áp dụng với người dùng)
Cho nhập tên người dùng sau đó kiểm tra với dslk nếu trùng cho nhập lại hoặc chuyển sang menu đăng nhập,
nếu chưa tồn tại sẽ cho nhập mật khẩu và lưu vào file nguoidung.txt trả về 2 nếu đăng kí hoàn tất*/
int dangKy(char *user);

/*Hàm thêm tài khoản admin
Cho nhập tên người dùng sau đó kiểm tra với dslk nếu trùng cho nhập lại hoặc chuyển sang menu đăng nhập,
nếu chưa tồn tại sẽ cho nhập mật khẩu và lưu vào file nguoidung.txt nếu đăng kí hoàn tất*/
void themTaiKhoanAdmin(void);

/* Hàm đổi mật khẩu
Cho nhập mật khẩu cũ và mới, nếu đúng sẽ đổi mật khẩu trong file nguoidung.txt*/
void doiMatKhau(char *user);

#endif
#ifndef DANGNHAP_H
#define DANGNHAP_H


/*Hàm đăng nhập
trả về trả về 1 nếu là admin; trả về 2 nếu là user
đồng trả về tên nguời dùng qua con trỏ user*/
int dangNhap(char *user);


/*Hàm đọc file user và trả về ba giá trị uername, pass, usertype 
File nguoidung.txt có dạng:
admin123|12345|1
user123|123456789|2
trả về 0 nếu sai user hoặc pass; trả về 1 nếu là admin; trả về 2 nếu là user*/
int kiemTraTaiKhoan(char *user, char *pass);


/*Hàm đăng kí tài khoản mới (áp dụng với người dùng)
Cho nhập tên người dùng sau đó kiểm tra với dslk nếu trùng cho nhập lại hoặc chuyển sang menu đăng nhập,
nếu chưa tồn tại sẽ cho nhập mật khẩu và lưu vào file nguoidung.txt trả về 2 nếu đăng kí hoàn tất*/
int dangKy(char *user);


#endif
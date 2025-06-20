# Bài tập lớn Kỹ thuật lập trình

## Thành Viên Nhóm

Tên|MSSV|Lớp
:---|:---|:---
Nguyễn Ngọc Tiên|6551071079|CQ.65.CNTT
Ngô Thanh Tiến|6551071082|CQ.65.CNTT

## Chú ý!

[Tài khoản test/demo](#53-d%E1%BB%AF-li%E1%BB%87u-m%E1%BA%ABu-v%C3%A0-t%C3%A0i-kho%E1%BA%A3n-test)

[Hướng Dẫn Biên Dịch và Chạy](#5-h%C6%B0%E1%BB%9Bng-d%E1%BA%ABn-bi%C3%AAn-d%E1%BB%8Bch-v%C3%A0-ch%E1%BA%A1y)

# Đề tài: Xây Dựng Ứng Dụng Quản Lý Rạp Chiếu Phim

Đây là dự án xây dựng ứng dụng quản lý rạp chiếu phim bằng ngôn ngữ lập trình C, tập trung vào các nghiệp vụ cơ bản của một rạp chiếu phim.

## 1. Giới Thiệu

Dự án nhằm xây dựng một ứng dụng quản lý toàn diện cho rạp chiếu phim, hỗ trợ chủ rạp và nhân viên trong việc vận hành các hoạt động hàng ngày một cách hiệu quả và chuyên nghiệp. Ứng dụng giải quyết các thách thức trong quản lý thủ công, giúp tối ưu hóa quy trình làm việc, tiết kiệm thời gian, giảm thiểu sai sót và nâng cao trải nghiệm cho cả nhân viên lẫn khách hàng. Hệ thống được xây dựng trên nền tảng ứng dụng máy tính (console application).

## 2. Công Nghệ Sử Dụng

* **Ngôn ngữ lập trình:** C
* **Cấu trúc dữ liệu:** Danh sách liên kết đơn (Singly Linked Lists)
* **Lưu trữ dữ liệu:** Tệp văn bản (.txt)
* **Quản lý phiên bản:** Git & GitHub

## 3. Tính Năng Chính

Ứng dụng cung cấp các chức năng cho hai loại người dùng chính: Người Dùng (Khách hàng) và Quản Trị Viên (Admin).

### 3.1. Chức năng chung

* Đăng nhập hệ thống
* Đăng ký tài khoản mới (dành cho Người Dùng)

![Giao diện đăng nhập](https://github.com/ngoctienz/IT1.103.3/blob/master/img/DangNhap.png)

### 3.2. Chức năng cho Người Dùng (User)

![Giao diện người dùng](https://github.com/ngoctienz/IT1.103.3/blob/master/img/User.png)

Sau khi đăng nhập, Người Dùng có thể:

* **Xem danh sách phim:** Hiển thị các phim đang chiếu cùng thông tin chi tiết (Mã phim, Tên phim, Thể loại, Ngày chiếu, Giờ chiếu, Phòng chiếu, Giá vé).
* **Đặt vé xem phim:**
    * Chọn phim muốn xem.
    * Xem sơ đồ ghế ngồi của phòng chiếu (ghế trống 'O', ghế đã đặt 'X').
    * Chọn ghế muốn đặt.
    * Hệ thống tạo mã vé và lưu thông tin vé.
* **Xem vé đã đặt:** Liệt kê các vé mà người dùng đã đặt, bao gồm thông tin Mã vé, Mã phim, Tên người đặt, Ghế ngồi, Trạng thái vé.
* **Hủy vé đã đặt:**
    * Chọn vé muốn hủy từ danh sách vé đã đặt.
    * Xác nhận hủy vé. Trạng thái vé được cập nhật và ghế ngồi được trả về trạng thái trống.
* **Đổi mật khẩu:** Cập nhật mật khẩu tài khoản.
* **Đăng xuất.**

### 3.3. Chức năng cho Quản Trị Viên (Admin)

![Giao diện quản trị viên](https://github.com/ngoctienz/IT1.103.3/blob/master/img/Admin.png)

Sau khi đăng nhập, Quản Trị Viên có các quyền quản lý sau:

* **Quản lý Phim:**
    * **Thêm phim mới:** Nhập thông tin chi tiết của phim mới và lưu vào hệ thống.
    * **Sửa thông tin phim:** Chọn phim và cập nhật các thông tin cần thiết.
    * **Xóa phim:** Xóa phim khỏi hệ thống.
    * **Hiển thị danh sách phim:** Xem toàn bộ danh sách phim.
* **Quản lý Dữ liệu Vé và Thống kê:**
    * **Xem danh sách tất cả vé đã đặt:** Hiển thị chi tiết tất cả các vé đã được đặt trong hệ thống, bao gồm thông tin người đặt, phim, ghế, trạng thái.
    * **Thống kê doanh thu:** Tính toán và hiển thị tổng doanh thu từ việc bán vé cho từng bộ phim (chỉ tính các vé đã đặt thành công).
* **Quản lý Tài khoản Người dùng:**
    * **Xem danh sách người dùng:** Liệt kê tất cả các tài khoản người dùng trong hệ thống (Tên đăng nhập, Loại tài khoản).
    * **Xóa tài khoản người dùng:** Xóa một tài khoản người dùng ra khỏi hệ thống (không thể xóa tài khoản admin đang đăng nhập).
    * **Thêm tài khoản Admin:** Chỉ Admin mới có thể thêm tài khoản Admin mới.
* **Đổi mật khẩu:** Cập nhật mật khẩu tài khoản.
* **Đăng xuất.**

## 4. Cấu Trúc Thư Mục và Tệp

Dự án bao gồm các tệp mã nguồn C (.c), tệp tiêu đề (.h) và các tệp dữ liệu (.txt):

* **Tệp mã nguồn chính:**

Tên File|Chức năng
:---|:---
`main.c`|Chứa hàm `main`, điều phối luồng chính của ứng dụng.
`dangnhap.c`|Chứa các hàm liên quan đến chức năng đăng nhập, đăng ký.
`menu.c`|Chứa các hàm hiển thị menu và điều hướng lựa chọn của người dùng.
`hotro.c`|Chứa các hàm hỗ trợ chung như quản lý dữ liệu phim, vé, người dùng, các tiện ích (xóa màn hình, dừng chương trình), đọc/ghi file.
* **Tệp tiêu đề:**

Tên File|Chức năng
:---|:---
`dangnhap.h`|Khai báo các hàm trong `dangnhap.c`.
`menu.h`|Khai báo các hàm trong `menu.c`.
`hotro.h`|Khai báo các cấu trúc dữ liệu (NguoiDungNode, PhimNode, VeNode) và các hàm trong `hotro.c`, cũng như các định nghĩa màu sắc cho console.
* **Tệp dữ liệu (lưu trữ ở cùng thư mục với file thực thi):**

Tên File|Chức năng
:---|:---
`nguoidung.txt`|Lưu thông tin tài khoản người dùng .
`phim.txt`|Lưu thông tin các bộ phim.
`ve.txt`|Lưu thông tin các vé đã đặt.

## 5. Hướng Dẫn Biên Dịch và Chạy

### 5.1. Sử dụng trình biên dịch (ví dụ: GCC)
[Xem video hướng dẫn tại YouTube](https://youtu.be/ZUw9MnbEMvs)
1.  **Môi trường:** Cần có một trình biên dịch C (ví dụ: GCC trên Linux/macOS, MinGW trên Windows).
2.  **Biên dịch:** Mở terminal hoặc command prompt, điều hướng đến thư mục chứa các tệp mã nguồn và thực hiện lệnh biên dịch. Ví dụ với GCC:
    ```bash
    gcc main.c dangnhap.c menu.c hotro.c -o QuanLyRapChieuPhim
    ```
3.  **Chạy chương trình:**
    * Sau khi biên dịch thành công, một tệp thực thi (ví dụ: `QuanLyRapChieuPhim.exe` trên Windows hoặc `QuanLyRapChieuPhim` trên Linux/macOS) sẽ được tạo.
    * Chạy tệp thực thi này từ terminal/command prompt:
        ```bash
        ./QuanLyRapChieuPhim
        ```

### 5.2. Sử dụng Dev-C++ IDE
[Xem video hướng dẫn tại YouTube](https://youtu.be/lJ-qn12VQHk)
1.  **Mở Project:**
    * Tại File Explorer > chọn vào file `.dev` > Open With > Dev-C++.
    * Hoặc: Khởi động phần mềm Dev-C++ > Chọn `File` > `Open Project or File...` (hoặc nhấn `Ctrl + O`). Điều hướng đến thư mục chứa tệp `.dev`.
2.  **Biên dịch và Chạy:**
    * Trong Dev-C++, biên dịch project bằng cách chọn `Execute` > `Compile` (hoặc nhấn `F9`).
    * Để chạy project, chọn `Execute` > `Run` (hoặc nhấn `F10`).
    * Để biên dịch và chạy cùng lúc, chọn `Execute` > `Compile & Run` (hoặc nhấn `F11`).

### 5.3. Dữ liệu mẫu và Tài khoản Test

Đảm bảo các tệp `nguoidung.txt`, `phim.txt`, và `ve.txt` được tạo (có thể để trống ban đầu) và đặt cùng thư mục với tệp thực thi (thường là thư mục chứa project `.dev` hoặc thư mục con nơi tệp `.exe` được tạo ra) để chương trình có thể đọc và ghi dữ liệu. Nếu các tệp này không tồn tại khi chương trình cố gắng đọc, sẽ xảy ra lỗi.

* **Dữ liệu mẫu `nguoidung.txt` (bao gồm tài khoản test):** (username|password|type)
    ```   
    tester|12345|1
    admin123|12345|1
    user|user123|2
    user123|123123|2
    ```
* **Dữ liệu mẫu `phim.txt`:** (MaPhim|TenPhim|TheLoai|NgayChieu|GioChieu|PhongChieu|GiaVe)
    ```
    P001|DAO MO KY SU|HANHDONG|15/05/2025|20:00|PHONG01|120000
    P002|LAT MAT 7|TAMLY|16/05/2025|19:30|PHONG02|110000
    ```
* **Dữ liệu mẫu `ve.txt`:** (MaVe|MaPhim|TenNguoiDung|GheNgoi_danh_sach_0_hoac_1_cach_nhau_boi_dau_phay_40_ghe|TrangThai)
    ```
    VE0001|P001|user1|0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0|1
    ```
    *(Lưu ý: Định dạng `GheNgoi` trong `ve.txt` là một chuỗi 40 số 0 hoặc 1, cách nhau bởi dấu phẩy, thể hiện trạng thái của 40 ghế. Số 1 nghĩa là ghế đó được chọn cho vé này)*

## 6. Giảng Viên Hướng Dẫn

* Trần Phong Nhã

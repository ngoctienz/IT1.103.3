# IT1.103.3 - Ứng dụng quản lý cơ bản

Đây là một ứng dụng console đơn giản được viết bằng ngôn ngữ C, nhằm mục đích minh họa các chức năng cơ bản như đăng nhập, hiển thị menu và hỗ trợ. Dự án này được xây dựng và chạy trên môi trường phát triển Dev-C++.

## Hướng dẫn chạy chương trình

Dưới đây là các bước chi tiết để bạn có thể biên dịch và chạy ứng dụng này trên máy tính của mình.

### Yêu cầu hệ thống

* **Hệ điều hành:** Windows (được phát triển và thử nghiệm trên Windows)
* **Phần mềm cần thiết:**
    * Dev-C++ 5.11 hoặc các phiên bản tương thích. Bạn có thể tải Dev-C++ miễn phí từ [https://sourceforge.net/projects/dev-cpp/](https://sourceforge.net/projects/dev-cpp/)

### Các bước chạy chương trình

1.  **Clone repository:**

    Nếu bạn chưa tải mã nguồn của dự án về máy, hãy sử dụng lệnh sau trong terminal hoặc command prompt để clone repository từ GitHub:

    ```bash
    git clone [https://github.com/ngoctienz/IT1.103.3.git](https://github.com/ngoctienz/IT1.103.3.git)
    cd IT1.103.3
    ```

2.  **Mở project bằng Dev-C++:**

    * Khởi động phần mềm **Dev-C++** trên máy tính của bạn.
    * Chọn **File** -> **Open Project...** (hoặc **Tệp** -> **Mở Project...** nếu giao diện của bạn là tiếng Việt).
    * Trong cửa sổ mở file, điều hướng đến thư mục bạn vừa clone repository `IT1.103.3`.
    * Chọn file có tên **`IT1.103.3.dev`** và nhấn **Open** (hoặc **Mở**).

3.  **Biên dịch và chạy chương trình:**

    * Sau khi project đã được mở trong Dev-C++, bạn có thể biên dịch và chạy chương trình bằng cách nhấn phím **F11** hoặc chọn menu **Execute** -> **Compile and Run** (hoặc **Thực thi** -> **Biên dịch và Chạy**).
    * Dev-C++ sẽ tự động biên dịch các file nguồn `.c` (`main.c`, `dangnhap.c`, `hotro.c`, `menu.c`) và liên kết chúng lại với các header file `.h` (`dangnhap.h`, `hotro.h`, `menu.h`).
    * Nếu quá trình biên dịch và liên kết thành công, một cửa sổ console sẽ xuất hiện và chương trình sẽ bắt đầu thực thi. Bạn sẽ thấy các thông báo và menu của ứng dụng hiển thị trong cửa sổ này.

```markdown
### Cấu trúc thư mục

IT1.103.3/
├── main.c
├── dangnhap.c
├── dangnhap.h
├── hotro.c
├── hotro.h
├── menu.c
├── menu.h


### Cách sử dụng

Sau khi chương trình chạy, bạn sẽ thấy một menu hoặc lời nhắc trong cửa sổ console. Hãy làm theo các hướng dẫn trên màn hình để tương tác với các chức năng của ứng dụng, bao gồm đăng nhập, truy cập menu và xem thông tin hỗ trợ.

### Đóng góp

Nếu bạn muốn đóng góp vào dự án này, vui lòng fork repository và tạo pull request với các thay đổi của bạn. Mọi đóng góp đều được hoan nghênh.

### Tác giả

[Tên của bạn hoặc tên nhóm phát triển]

### License

[Bạn có thể thêm thông tin về license của dự án tại đây nếu có. Ví dụ: MIT License]

---

Chúc bạn và những người khác có thể dễ dàng chạy và tìm hiểu dự án này! Hãy nhớ rằng bạn có thể tùy chỉnh thêm các phần như ảnh chụp màn hình, mô tả chi tiết về từng chức năng, hoặc bất kỳ thông tin nào khác mà bạn cho là hữu ích.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "dangnhap.h"
#include "hotro.h"


//Ham doc file user
int kiemTraTaiKhoan(char *user, char *pass) {
    FILE *a;
    char *user_temp;
    user_temp = (char*)malloc(15 * sizeof(char));

    char *pass_temp;
    pass_temp = (char*)malloc(15 * sizeof(char));

    if (user_temp == NULL || pass_temp == NULL) {
        perror("Loi cap phat bo nho: ");
        free(user_temp);
        free(pass_temp);
        exit(1);
    }
    
    int type;
    a = fopen("nguoidung.txt", "r");
    if (a == NULL) {
        perror("Loi file: ");
        exit(1);
    }
    while (fscanf(a, "%[^|]|%[^|]|%d\n", user_temp, pass_temp, &type) == 3) {
        if ((strcmp(user, user_temp) == 0) && (strcmp(pass, pass_temp) == 0)) {
            fclose(a);
            return type; // Dung tai khoan thi tra ve 1 hoac 2
        }
    }
    fclose(a);

    free(user_temp);
    free(pass_temp);
    return 0; // Sai tai khoan thi tra ve 0
}

// ham dang nhap
int dangNhap(char *user) {
    char *pass;
    pass = (char*)malloc(15 * sizeof(char));
    if (pass == NULL) {
        perror("Loi cap phat bo nho cho mat khau: ");
        // Trả về -1 nếu cấp phát lỗi
        exit(1);
    }
    int c; // Biến để đọc ký tự từ input
    int UserType = 0; // Biến để lưu loại người dùng (0: không tìm thấy/sai thông tin, 1: admin, 2: user)
    xoaMH();
    printf(BOLD CYAN "===== HE THONG DANG NHAP =====\n" RESET_COLOR);
    do {
        printf(YELLOW "Nhap ten dang nhap: " RESET_COLOR);
        scanf("%s", user);
        while ((c = getchar()) != '\n' && c != EOF);
        printf(YELLOW "Nhap mat khau: " RESET_COLOR);
        // --- Bắt đầu phần nhập mật khẩu ẩn (hiển thị ***) ---
        int i = 0; // Chỉ số cho mảng pass
        char input_char; // Biến tạm để đọc từng ký tự
        while ((input_char = getch()) != '\r' && input_char != '\n' && i < 14) {
            // getch() đọc một ký tự mà không hiển thị lên màn hình
            if (input_char != 8 && input_char != 127) {
                 // Nếu là ký tự thông thường, lưu vào mảng pass
                 pass[i] = input_char;
                 i++; // Tăng chỉ số
                 printf("*"); // In ký tự '*' ra màn hình
            } else if (i > 0) {
                 i--; // Giảm chỉ số
                 printf("\b \b"); // Xóa ký tự '*' cuối cùng trên màn hình (\b: lùi con trỏ, ' ': in khoảng trắng, \b: lùi con trỏ lại)
            }
        }
        pass[i] = '\0'; // Thêm ký tự null kết thúc chuỗi vào cuối mật khẩu
        printf("\n");

        // và trả về loại tài khoản (1: admin, 2: user) hoặc 0 nếu không tìm thấy/sai
        UserType = kiemTraTaiKhoan(user, pass); // Hàm kiemTraTaiKhoan cần được định nghĩa
       
        if (UserType == 0) { // Nếu UserType là 0 (đăng nhập thất bại)
            xoaMH();
            // In thông báo lỗi với màu đỏ đậm và in đậm
            printf(RED BOLD "Ten dang nhap hoac mat khau khong dung!\n" RESET_COLOR);
            // Yêu cầu người dùng nhập lại hoặc quay lại menu chính
            printf(YELLOW "Nhan Enter de nhap lai hoac nhap 0 de quay lai menu chinh: " RESET_COLOR);

            char *temp_choice;// Cấp phát bộ nhớ cho temp_choice
            temp_choice = (char*)malloc(10 * sizeof(char));
            if (temp_choice == NULL) {
                perror("Loi cap phat bo nho cho temp_choice: ");
                free(pass);
                exit(1) ; // Thoát nếu không cấp phát được
            }
            fgets(temp_choice, sizeof(temp_choice), stdin); // Sử dụng fgets an toàn hơn scanf cho chuỗi

            // So sánh lựa chọn với "0\n" (Enter sau khi nhập 0) hoặc "0\r\n" (trên một số hệ điều hành)
            if (strcmp(temp_choice, "0\n") == 0 || strcmp(temp_choice, "0\r\n") == 0) {
                 // Nếu người dùng nhập 0
                 free(pass);
                 user[0] = '\0'; // Đặt ký tự null vào đầu chuỗi user để làm rỗng tên đăng nhập
                 return 0; // Trả về 0 để báo hiệu quay lại menu chính
            }
            // Nếu người dùng nhấn Enter (không nhập 0), tiếp tục vòng lặp
            xoaMH(); 
          
            printf(BOLD CYAN "===== HE THONG DANG NHAP =====\n" RESET_COLOR);
            // Vòng lặp do-while tiếp tục vì UserType vẫn là 0
        } else { // Nếu UserType khác 0 (đăng nhập thành công)
      
            printf(GREEN BOLD "Dang nhap thanh cong!\n" RESET_COLOR);
            stop(2, UserType == 1 ? "Menu Admin" : "Menu nguoi dung"); 
            free(pass); 
            return UserType; // Trả về loại người dùng (1 hoặc 2) để báo hiệu đăng nhập thành công và loại tài khoản
        }
    } while (UserType == 0); // Vòng lặp tiếp tục nếu UserType là 0 (đăng nhập thất bại)
    free(pass); 
    return 0;
}
// ham dang ky
int dangKy(char *user) {
    FILE *a;
    char *pass;
    pass = (char*)malloc(15 * sizeof(char)); // Biến cho mật khẩu
    char *pass2;
    pass2 = (char*)malloc(15 * sizeof(char)); // Biến cho mật khẩu xác nhận

    char c; // Khai báo biến để đọc ký tự thừa trong bộ đệm nhập
    NguoiDungNode *head = NULL, *temp = NULL, *newNode = NULL;
    int check = 0; // Biến để kiểm tra tên đăng nhập có tồn tại hay không
    int kiemTraPass = 0; // Biến để kiểm tra mật khẩu có khớp không
                        // 0 không khớp, 1 khớp

    if (pass == NULL || pass2 == NULL) {
        perror("Loi cap phat bo nho: ");
        free(pass); 
        free(pass2); 
        exit(1);
    }

    docTaiKhoanTuFile(&head);

    do {
        printf(YELLOW"Nhap ten dang nhap: "RESET_COLOR);
        scanf("%14s", user); // Giới hạn đọc để tránh tràn bộ đệm
        while ((c = getchar()) != '\n' && c != EOF); // Xóa bộ đệm nhập

        check = 0;

        // Kiểm tra xem tên đăng nhập đã tồn tại trong danh sách liên kết chưa
        for (temp = head; temp != NULL; temp = temp->next) {
            if (strcmp(user, temp->username) == 0) {
                check = 1;
                break;
            }
        }

        if (check == 1) {
            xoaMH();
            printf(RED"Ten dang nhap da ton tai! Vui long chon ten khac.\n"RESET_COLOR);
        } else {
            // Vòng lặp để nhập và xác nhận mật khẩu
            do {
                printf(YELLOW"Nhap mat khau: "RESET_COLOR);
                scanf("%14s", pass); // Giới hạn đọc
                while ((c = getchar()) != '\n' && c != EOF); // Xóa bộ đệm nhập

                printf(YELLOW"Nhap lai mat khau de xac nhan: "RESET_COLOR);
                scanf("%14s", pass2); // Giới hạn đọc
                while ((c = getchar()) != '\n' && c != EOF); // Xóa bộ đệm nhập

                if (strcmp(pass, pass2) == 0) {
                    kiemTraPass = 1; // Mật khẩu khớp
                } else {
                    xoaMH();
                    printf(RED"Mat khau khong khop! Vui long nhap lai.\n"RESET_COLOR);
                    kiemTraPass = 0; // Mật khẩu không khớp, tiếp tục lặp
                }
            } while (kiemTraPass == 0); // Lặp cho đến khi mật khẩu khớp

            newNode = (NguoiDungNode*)malloc(sizeof(NguoiDungNode));
            if (newNode == NULL) {
                perror("Loi cap phat bo nho cho newNode: ");
                free(pass);
                free(pass2);
                // Giải phóng danh sách liên kết nếu có
                NguoiDungNode *current = head;
                NguoiDungNode *nextNode;
                while (current != NULL) {
                    nextNode = current->next;
                    free(current);
                    current = nextNode;
                }
                return -1;
            }

            // Sao chép tên đăng nhập và mật khẩu vào nút mới
            // Đảm bảo kích thước buffer đủ lớn trong NguoiDungNode
            strncpy(newNode->username, user, sizeof(newNode->username) - 1);
            newNode->username[sizeof(newNode->username) - 1] = '\0';

            strncpy(newNode->password, pass, sizeof(newNode->password) - 1);
            newNode->password[sizeof(newNode->password) - 1] = '\0';

            newNode->type = 2; // User
            newNode->next = head;
            head = newNode;

            a = fopen("nguoidung.txt", "a");
            if (a != NULL) {
                fprintf(a, "%s|%s|%d\n", user, pass, 2);
                fclose(a);
                xoaMH();
                printf(GREEN BOLD "Dang ky thanh cong!\n" RESET_COLOR);
                printf(YELLOW "Ten dang nhap: %s\n", user);
                // thong bao dang nhap lai
                printf(YELLOW "Vui long dang nhap lai: " RESET_COLOR);
                stop(2, "Dang nhap");
                check = 0; // Đặt check về 0 để thoát vòng lặp `do-while` chính
            } else {
                perror("Loi mo file de ghi: ");
                free(newNode);
                check = 1;
            }
        }
    } while (check == 1); // Tiếp tục lặp nếu tên đăng nhập đã tồn tại hoặc ghi file thất bại

    // Giải phóng danh sách liên kết
    NguoiDungNode *current = head;
    NguoiDungNode *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    // Giải phóng bộ nhớ đã cấp phát
    free(pass);
    free(pass2);

    return 0; // 
}

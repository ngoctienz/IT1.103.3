#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "hotro.h"

void xoaMH(void) {
#ifdef _WIN32 // Nếu đang chạy trên Windows
    system("cls");
#else
    system("clear"); // Nếu đang chạy trên Linux hoặc macOS
#endif
}

// Hàm void để giới hạn kích thước cửa sổ console (không kiểm tra lỗi chi tiết)

// Ham dem nguoc t giay va chuyen huong den noi dung s
void stop(int t, const char *s) {
    while (t > 0) {
        printf("\rChuyen huong den %s sau %d giay !", s, t);
        sleep(1);
        t--;
    }
    printf("\nDang chuyen huong den %s ...\n", s);
    sleep(1);
}


// Ham doc danh sach tai khoan tu file nguoidung.txt
// va luu vao danh sach lien ket
// tra ve qua con tro head
void docTaiKhoanTuFile(NguoiDungNode **head) {

    FILE *a = fopen("nguoidung.txt", "r");
    if ( a == NULL) {
        perror("Loi file: "); // Thông báo lỗi nếu không mở được file
        exit(1); 
    }

    while (!feof(a)) {
        NguoiDungNode *temp = (NguoiDungNode*)malloc(sizeof(NguoiDungNode));
        if ( temp == NULL) {
             perror("Loi cap phat bo nho");
              exit(1); 
            }
        char *pass;
        pass = (char*)malloc(15 * sizeof(char));
        if (fscanf(a, "%[^|]|%[^|]|%d\n", temp->username, pass, &temp->type) == 3) {
            strcpy(temp->password, pass);
            temp->next = *head;
            *head = temp;
        } else {
            free(temp);
        }
    }
    fclose(a);
}

// Ham doc danh sach phim tu file phim.txt
// va luu vao danh sach lien ket
// tra ve qua con tro head
void docPhimTuFile(PhimNode **head) {
    FILE *a = fopen("phim.txt", "r");
    if ( a == NULL) {
     perror("Loi file"); 
     exit(1); 
    }

    while (!feof(a)) {
        PhimNode *temp = (PhimNode*)malloc(sizeof(PhimNode));
        if (temp == NULL) {
            perror("Loi cap phat bo nho"); 
            exit(1); 
        }

        if (fscanf(a, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d\n", temp->MaPhim, temp->TenPhim, temp->TheLoai,
                   temp->NgayChieu, temp->GioChieu, temp->PhongChieu, &temp->GiaVe) == 7) {
            temp->next = *head;
            *head = temp;
        } else {
            free(temp);
        }
    }
    fclose(a);
}

// Ham in danh sach phim tu danh sach PhimNode
void inDanhSachPhim(void) {
    // Khoi tao danh sach lien ket phim
    PhimNode *temp = NULL; 

    // Doc danh sach phim tu file phim.txt
    // va luu vao danh sach lien ket temp
    docPhimTuFile(&temp);

    printf(BLUE"                                         DANH SACH PHIM                                   \n"RESET_COLOR);
    printf(RED"------------------------------------------------------------------------------------------\n"RESET_COLOR);
    printf(RED"%-10s %-15s %-15s %-10s %-10s %-10s %-10s\n", "Ma Phim", "Ten Phim", "The Loai", "Ngay", "Gio", "Phong", "Gia ve");
    printf("------------------------------------------------------------------------------------------\n"RESET_COLOR);
    while (temp != NULL) {
        printf(YELLOW"%-10s %-15s %-15s %-10s %-10s %-10s %-10d\n", temp->MaPhim, temp->TenPhim, temp->TheLoai, temp->NgayChieu, temp->GioChieu, temp->PhongChieu, temp->GiaVe);
        temp = temp->next;
    }
    printf(RESET_COLOR);
    printf(RED"------------------------------------------------------------------------------------------\n"RESET_COLOR);
    }

// Ham doc danh sach ve tu file ve.txt
// va luu vao danh sach lien ket
// tra ve qua con tro head
void docVeTuFile(VeNode **head) {
    FILE *a = fopen("ve.txt", "r");
    if (!a) { perror("Loi file"); exit(1); }
    while ( feof(a) == 0) {
        VeNode *temp;
        temp = (VeNode*)malloc(sizeof(VeNode));
        if (temp == NULL) {
            perror(RED"Loi cap phat bo nho"RESET_COLOR);
            exit(1);
            }

        char *ghe;
        ghe = (char*)malloc(100 * sizeof(char));
        if (fscanf(a, "%[^|]|%[^|]|%[^|]|%[^|]|%d\n", temp->MaVe, temp->MaPhim, temp->TenNguoiDung, ghe, &temp->TrangThai) == 5) {
            char *maGhe = strtok(ghe, ",");// Bắt đầu phân tích chuỗi ghế ngồi bằng dấu phẩy
            int i = 0;
            while (maGhe && i < 40) {// Lặp qua các maGhe (số ghế) và giới hạn 40 ghế
                temp->GheNgoi[i++] = atoi(maGhe);// Chuyển maGhe sang số nguyên và lưu vào mảng GheNgoi
                maGhe = strtok(NULL, ",");// Lấy maGhe tiếp theo
            }
            while (i < 40) temp->GheNgoi[i++] = 0;// Điền 0 cho các vị trí còn lại nếu ít hơn 40 ghế

            temp->next = *head;
            *head = temp;
        } else {
            free(temp);
        }
    }
    fclose(a);
}

// Ham ghi danh sach ve vao file ve.txt
// lay du lieu tu danh sach lien ket qua con tro head

void ghiDanhSachVeVaoFile(VeNode *head) {
    FILE *a = fopen("ve.txt", "w");
    if (a == NULL) {
        perror("Loi file"); 
        exit(1); 
    }

    VeNode *current = head;
    while (current) {   // Lặp qua từng vé trong danh sách liên kết cho đến khi gặp NULL.
        fprintf(a, "%s|%s|%s|", current->MaVe, current->MaPhim, current->TenNguoiDung);
        for (int i = 0; i < 40; i++) { // Lặp qua mảng GheNgoi (40 phần tử) để ghi trạng thái từng ghế
            fprintf(a, "%d", current->GheNgoi[i]);// Ghi trạng thái ghế (0 hoặc 1).
            if (i < 39) fprintf(a, ",");// Ghi dấu phẩy sau mỗi số ghế, trừ số cuối cùng.
        }
        fprintf(a, "|%d\n", current->TrangThai);
        current = current->next;
    }
    fclose(a);
}

// Ham tao ma ve ngau nhien
// Ma ve co dang "VE" + 4 chu so ngau nhien
void taoMaVe(char *maVe) {
    srand(time(NULL)); // khoi tao bo sinh ngau nhien
    sprintf(maVe, "VE%04d", rand() % 10000);// Tạo mã vé có dạng "VE" theo sau là 4 chữ số ngẫu nhiên
}

// Ham in so do ghe ngoi
// cho phim co ma phim la maPhim
// Duyet qua danh sach ve va kiem tra ghe ngoi da dat
// neu ghe ngoi da dat thi danh dau ghe do
// neu ghe ngoi chua dat thi khong danh dau
void inSoDoGhe(VeNode *headVe, const char *maPhim) {

    // Giả sử MAX_GHE là số lượng ghế tối đa, ví dụ 40
    int *ghe;
    ghe = (int*)malloc(MAX_GHE * sizeof(int));
    if (ghe == NULL) {
        perror("Loi cap phat bo nho: ");
        exit(1); // Thoát chương trình với mã lỗi
    }

    // Khởi tạo mảng ghe với tất cả các ghế đều chưa được đặt (0)
    for (int i = 0; i < MAX_GHE; i++) {
       *(ghe + i ) = 0;
    }

    for (VeNode *temp = headVe; temp; temp = temp->next) {// Duyệt qua danh sách liên kết các vé
        if (strcmp(temp->MaPhim, maPhim) == 0) {  // So sánh mã phim trong vé với mã phim đã chọn
            for (int i = 0; i < MAX_GHE; i++) {
                if (temp->GheNgoi[i])
                *(ghe + i) = 1;
            }
        }
    }

    printf(RED"\nSo do ghe (X: da dat, O: trong):\n"RESET_COLOR);
    printf("  ------------------------\n");

    for (char hang = 'A'; hang <= 'E'; hang++) {
        printf("%c |", hang); // In tên hàng (A, B, C, D, E) và ký tự phân cách
        for (int cot = 1; cot <= 8; cot++) {// Duyệt qua các cột ghế (từ 1 đến 8)
            int idx = (hang - 'A') * 8 + (cot - 1);
            printf(" %-2s", ghe[idx] ? RED"X"RESET_COLOR : GREEN"O"RESET_COLOR);
        }
       printf("\n");
    }

    printf("  ------------------------\n");
    printf("  ");
    for (int cot = 1; cot <= 8; cot++) {
        printf(" %-2d", cot);
    }
    printf("\n");
    free(ghe); // Lệnh free được di chuyển vào đúng vị trí
}

// Ham dat ve cho nguoi dung
void datVe(char *user) {
    PhimNode *headPhim = NULL;
    VeNode *headVe = NULL;
    docPhimTuFile(&headPhim);
    docVeTuFile(&headVe);

    VeNode *newVe = (VeNode*)malloc(sizeof(VeNode));
    if (newVe == NULL) { 
        perror(RED"Loi cap phat bo nho"RESET_COLOR); 
        exit(1); 
    }
    taoMaVe(newVe->MaVe);   // Tạo mã vé duy nhất cho vé mới

    char *maPhim;
    maPhim = (char*)malloc(15 * sizeof(char));
    char *gheNgoi;
    gheNgoi = (char*)malloc(3 * sizeof(char));
    if (maPhim == NULL || gheNgoi == NULL) { 
        perror(RED"Loi cap phat bo nho"RESET_COLOR); 
        exit(1); 
    }

    int gheINT;
    newVe->TrangThai = 1;  // Đặt trạng thái vé mới là 1 (đã đặt)
    inDanhSachPhim();      // Hiển thị danh sách phim để người dùng chọn
    PhimNode *tempPhim;    // Con trỏ tạm để duyệt danh sách phim
    do {
        printf(YELLOW"Nhap ma phim muon dat ve: "RESET_COLOR);
        scanf("%14s", maPhim);
        tempPhim = headPhim;
        while (tempPhim) {
            if (strcmp(tempPhim->MaPhim, maPhim) == 0) {   // So sánh mã phim nhập với mã phim trong danh sách
                strcpy(newVe->MaPhim, maPhim);             // Sao chép mã phim đã chọn vào nút vé mới
                break;
            }
            tempPhim = tempPhim->next; // Chuyển sang phim tiếp theo
        }
        if (tempPhim == NULL) { // Nếu không tìm thấy phim trong danh sách  
            printf(RED"Ma phim khong ton tai!\n"RESET_COLOR);
        } else {
            inSoDoGhe(headVe, maPhim);
            break;
        }
    } while (1);

    printf(GREEN"Nguoi dat ve: %s\n"RESET_COLOR, user);
    strcpy(newVe->TenNguoiDung, user);

    do {
        printf(GREEN"Nhap ghe ngoi (VD: A1): "RESET_COLOR);
        scanf("%2s", gheNgoi);
        if (strlen(gheNgoi) != 2 || *gheNgoi < 'A' || *gheNgoi > 'E' || *(gheNgoi + 1) < '1' || *(gheNgoi + 1) > '8') {// Kiểm tra định dạng nhập ghế ngồi (phải là 2 ký tự, hàng từ A-E, cột từ 1-8)
            printf("Dinh dang sai.\n");
            continue;
        }
        gheINT = (*gheNgoi - 'A') * 8 + (*(gheNgoi + 1) - '1');
        int daDat = 0;
        for (VeNode *temp = headVe; temp; temp = temp->next) {
        	// Kiểm tra nếu vé thuộc cùng phim và ghế đã chọn đã được đánh dấu là 1 trong vé này
            if (strcmp(temp->MaPhim, newVe->MaPhim) == 0 && temp->GheNgoi[gheINT]) {
                daDat = 1;
                break;
            }
        }
        if ( daDat == 0) { // Nếu ghế chưa được đặt
            for (int i = 0; i < 40; i++) newVe->GheNgoi[i] = 0;
            newVe->GheNgoi[gheINT] = 1;// Đánh dấu ghế đã chọn là 1 (đã đặt) trong vé mới
            newVe->next = headVe;
            headVe = newVe;
            ghiDanhSachVeVaoFile(headVe);
            printf(RED"Dat ve thanh cong!\n"RESET_COLOR);
            break;
        } else {
            printf(GREEN"Ghe da duoc dat!\n"RESET_COLOR);
        }
    } while (1);

    free(maPhim);
    free(gheNgoi);
}

void inVeDaDat(char *user) {
    VeNode *headVe = NULL;
    docVeTuFile(&headVe);
 
    printf(BLUE"                                    DANH SACH VE DA DAT                              \n");
    printf(MAGENTA"----------------------------------------------------------------------------------------");
    printf(RED"\n%-10s %-10s %-20s %-20s %-12s\n", "Ma Ve", "Ma Phim", "Ten Nguoi Dat", "Ghe Ngoi", "Trang Thai");
    printf(MAGENTA"----------------------------------------------------------------------------------------\n");
    for (VeNode *temp = headVe; temp; temp = temp->next) {
        if (strcmp(temp->TenNguoiDung, user) == 0) {
            // In dòng đầu với các trường cơ bản
            printf(BOLD YELLOW"%-10s %-10s %-20s ", temp->MaVe,
                temp->MaPhim,
                temp->TenNguoiDung);

            // In các ghế đã đặt
            int demGhe = 0;
            for (int i = 0; i < 40; i++) {
                if (temp->GheNgoi[i]) {
                    printf("%c%d ", 'A' + i / 8, i % 8 + 1);
                    demGhe++;
                }
            }
            if (demGhe == 0) {
                printf("XX ");
            }

            printf("%30s\n", temp->TrangThai == 1 ? GREEN"Da dat" : RED"Da huy"RESET_COLOR);
        }
    }

    printf(MAGENTA"----------------------------------------------------------------------------------------\n"RESET_COLOR);

    // Giải phóng bộ nhớ
    VeNode *tmp;
    while (headVe) {
        tmp = headVe;
        headVe = headVe->next;
        free(tmp);
    }
}

void huyVeDaDat(char *user) {
    VeNode *headVe = NULL;
    docVeTuFile(&headVe);

    char *maVe;
    maVe = (char*)malloc(15 * sizeof(char));
 
    if (maVe == NULL) { 
        perror("Loi cap phat bo nho"); 
        exit(1); 
    }

    inVeDaDat(user);
    printf(YELLOW"Nhap ma ve muon huy: "RESET_COLOR);
    scanf("%14s", maVe);

    int kiemTraVe = 0; // Biến để kiểm tra xem vé có tồn tại hay không
    VeNode *temp = headVe;
    while (temp) { // Lặp qua từng vé trong danh sách
                    // Kiểm tra nếu mã vé, tên người dùng trùng khớp và trạng thái vé là 1 (chưa hủy)
        if (strcmp(temp->MaVe, maVe) == 0 && strcmp(temp->TenNguoiDung, user) == 0 && temp->TrangThai == 1) {
            printf(YELLOW"Ban chac chan muon huy ve: "RESET_COLOR);
            for (int i = 0; i < 40; i++) {
                if (temp->GheNgoi[i]) {// Nếu ghế thứ i đã được đặt (giá trị là 1)
                    printf("%c%d ", 'A' + i / 8, i % 8 + 1);// In tên ghế (ví dụ: A1, B5)
                }
            }
            printf(BLUE"?\nNhap 1 de xac nhan, 0 de huy thao tac: "RESET_COLOR);

            int xacNhan; // Biến để xác nhận hủy vé

            scanf("%d", &xacNhan);
            if (xacNhan != 1) {
                printf(RED"Da huy thao tac huy ve.\n"RESET_COLOR);
                free(maVe);
                // Giải phóng danh sách
                VeNode *tmp;
                while (headVe) {
                    tmp = headVe;
                    headVe = headVe->next;
                    free(tmp);
                }
                return;
            }

            temp->TrangThai = 2;
            for (int i = 0; i < 40; i++) {
                temp->GheNgoi[i] = 0;
            } // Đánh dấu tất cả ghế trong vé là chưa đặt (0)
            }
            ghiDanhSachVeVaoFile(headVe);
            printf("Huy ve thanh cong!\n");
            kiemTraVe = 1;
            break;
        }
        temp = temp->next;
    

    if ( kiemTraVe == 0) {
        printf(RED"Ma ve khong ton tai, da bi huy, hoac khong phai cua ban!\n"RESET_COLOR);
    }

    // Giải phóng
    free(maVe);
    VeNode *tmp;
    while (headVe) {
        tmp = headVe;
        headVe = headVe->next;
        free(tmp);
    }
}


void themPhim(void) {
    PhimNode *headPhim = NULL;

    docPhimTuFile(&headPhim);

    PhimNode *newPhim;
    if (!newPhim) {
        perror("Loi cap phat bo nho");
        return;
    }
    xoaMH();
    printf("THEM PHIM MOI\n");
    printf("========================================\n");
    printf("Nhap ma phim: ");
    scanf("%s", newPhim->MaPhim);
    // Kiem tra trung ma phim
    for (PhimNode *temp = headPhim; temp != NULL; temp = temp->next) {
        if (strcmp(temp->MaPhim, newPhim->MaPhim) == 0) {
            printf("Ma phim da ton tai!\n");
            free(newPhim);
            return;
        }
    }

    printf(YELLOW"Nhap ten phim: "RESET_COLOR);
    getchar(); // Xoa bo nho dem
    fgets(newPhim->TenPhim, sizeof(newPhim->TenPhim), stdin);
    strtok(newPhim->TenPhim, "\n"); // Xoa ky tu newline
    printf(YELLOW"Nhap the loai: "RESET_COLOR);
    fgets(newPhim->TheLoai, sizeof(newPhim->TheLoai), stdin);
    strtok(newPhim->TheLoai, "\n");
    printf(YELLOW"Nhap ngay chieu (dd/mm/yyyy): "RESET_COLOR);
    scanf("%s", newPhim->NgayChieu);
    printf(YELLOW"Nhap gio chieu (hh:mm): "RESET_COLOR);
    scanf("%s", newPhim->GioChieu);
    printf(YELLOW"Nhap phong chieu: "RESET_COLOR);
    scanf("%s", newPhim->PhongChieu);
    printf(YELLOW"Nhap gia ve: "RESET_COLOR);
    scanf("%d", &newPhim->GiaVe);

    // Kiem tra trung lich (ngay + gio + phong)
    for (PhimNode *temp = headPhim; temp != NULL; temp = temp->next) {
        if (strcmp(temp->NgayChieu, newPhim->NgayChieu) == 0 &&
            strcmp(temp->GioChieu, newPhim->GioChieu) == 0 &&
            strcmp(temp->PhongChieu, newPhim->PhongChieu) == 0) {
            printf(RED"Da co phim duoc chieu vao thoi diem nay trong phong nay!\n"RESET_COLOR);
            free(newPhim);
            return;
        }
    }

    newPhim->next = NULL;

    // Ghi phim moi vao file
    FILE *a = fopen("phim.txt", "a");
    if ( a == NULL) {
        // Neu khong mo duoc file, thong bao loi va giai phong bo nho
        perror("Loi mo file phim.txt");
        free(newPhim);
        return;
    }

    fprintf(a, "%s|%s|%s|%s|%s|%s|%d\n",newPhim->MaPhim,
        newPhim->TenPhim,
        newPhim->TheLoai,
        newPhim->NgayChieu,
        newPhim->GioChieu,
        newPhim->PhongChieu,
        newPhim->GiaVe);

    fclose(a);

    xoaMH();
    printf("Them phim thanh cong!\n");
    printf("----------------------------------------------------------\n");
    inThongTinPhim(newPhim); 
    printf("----------------------------------------------------------\n");
    printf("Phim da duoc them vao danh sach phim.\n");
    // Giai phong danh sach phim da doc
    free(newPhim);
    PhimNode *tmp;
    while (headPhim) {
        tmp = headPhim;
        headPhim = headPhim->next;
        free(tmp);
    }
}

void inThongTinPhim(PhimNode *p) {
    if ( p != NULL) {
        printf("Ma phim: %s\n", p->MaPhim);
        printf("Ten phim: %s\n", p->TenPhim);
        printf("The loai: %s\n", p->TheLoai);
        printf("Ngay chieu: %s\n", p->NgayChieu);
        printf("Gio chieu: %s\n", p->GioChieu);
        printf("Phong chieu: %s\n", p->PhongChieu);
        printf("Gia ve: %d\n", p->GiaVe);
    }
}

void suaPhim() {
//   char c;

    char *maPhim;
    maPhim = malloc(10*sizeof(char));
    if (maPhim == NULL) {
        perror("Loi cap phat bo nho");
        return;
    }

    PhimNode *headPhim = NULL;
    docPhimTuFile(&headPhim);

    inDanhSachPhim();


    printf("Nhap ma phim muon sua: ");
    scanf("%s", maPhim);

    PhimNode *kiemTraVe = NULL;
    for (PhimNode *temp = headPhim; temp != NULL; temp = temp->next) {
        if (strcmp(temp->MaPhim, maPhim) == 0) {
            kiemTraVe = temp;
            break;
        }
    }

    if (!kiemTraVe) {
        printf("Khong tim thay phim voi ma da nhap!\n");
        return;
    }

    int choice;
    do {
        xoaMH();
        printf("\n---------------------THONG TIN PHIM---------------------\n");
        inThongTinPhim(kiemTraVe);
        printf("\n------------------------- MENU -------------------------\n");
        printf(MAGENTA"1. Sua ma phim\n"RESET_COLOR);
        printf(MAGENTA"2. Sua ten phim\n"RESET_COLOR);
        printf(MAGENTA"3. Sua the loai\n"RESET_COLOR);
        printf(MAGENTA"4. Sua ngay chieu\n"RESET_COLOR);
        printf(MAGENTA"5. Sua gio chieu\n"RESET_COLOR);
        printf(MAGENTA"6. Sua phong chieu\n"RESET_COLOR);
        printf(MAGENTA"7. Sua gia ve\n"RESET_COLOR);
        printf(MAGENTA"0. Thoat sua quay lai quan li phim\n"RESET_COLOR);
        printf("----------------------------------------------------------\n");
        printf(BLUE"Chon: "RESET_COLOR);
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf(BLUE"Nhap ma phim moi: "RESET_COLOR);
                scanf("%s", kiemTraVe->MaPhim);
                break;
            case 2:
                printf(BLUE"Nhap ten phim moi: "RESET_COLOR);
                fgets(kiemTraVe->TenPhim, sizeof(kiemTraVe->TenPhim), stdin);
                strtok(kiemTraVe->TenPhim, "\n");
                break;
            case 3:
                printf(BLUE"Nhap the loai moi: "RESET_COLOR);
                fgets(kiemTraVe->TheLoai, sizeof(kiemTraVe->TheLoai), stdin);
                strtok(kiemTraVe->TheLoai, "\n");
                break;
            case 4:
                printf(BLUE"Nhap ngay chieu moi: "RESET_COLOR);
                scanf("%s", kiemTraVe->NgayChieu);
                break;
            case 5:
                printf(BLUE"Nhap gio chieu moi: "RESET_COLOR);
                scanf("%s", kiemTraVe->GioChieu);
                break;
            case 6:
                printf(BLUE"Nhap phong chieu moi: "RESET_COLOR);
                scanf("%s", kiemTraVe->PhongChieu);
                break;
            case 7:
                printf(BLUE"Nhap gia ve moi: "RESET_COLOR);
                scanf("%d", &kiemTraVe->GiaVe);
                break;
            case 0:
                break;
            default:
                printf(RED"Lua chon khong hop le!\n"RESET_COLOR);
        }
    } while (choice != 0);

    FILE *a = fopen("phim.txt", "w");
    if (!a) {
        perror("Loi mo file phim.txt");
        return;
    }

    for (PhimNode *temp = headPhim; temp != NULL; temp = temp->next) {
        fprintf(a, "%s|%s|%s|%s|%s|%s|%d\n",
                temp->MaPhim,
                temp->TenPhim,
                temp->TheLoai,
                temp->NgayChieu,
                temp->GioChieu,
                temp->PhongChieu,
                temp->GiaVe);
    }

    fclose(a);

    PhimNode *tmp;
    while (headPhim) {
        tmp = headPhim;
        headPhim = headPhim->next;
        free(tmp);
    }
}

// Ham xoa phim
void xoaPhim() {
    char c;
    PhimNode *headPhim = NULL;
    docPhimTuFile(&headPhim);

    if (headPhim == NULL) {
        printf(RED"Danh sach phim rong, khong co gi de xoa!\n"RESET_COLOR);
        return;
    }

    // In danh sách phim
    inDanhSachPhim();  // Cần truyền headPhim nếu hàm yêu cầu

    // Cấp phát bộ nhớ cho mã phim cần xóa
    char *maPhim = (char*)malloc(15 * sizeof(char));
    if (maPhim == NULL) {
        perror("Loi cap phat bo nho");
        return;
    }

    // Xóa bộ đệm nhập
    while ((c = getchar()) != '\n' && c != EOF);

    printf(RED"Nhap ma phim muon xoa: "RESET_COLOR);
    scanf("%14s", maPhim); // giới hạn tránh tràn

    // Tìm phim cần xóa
    PhimNode *curr = headPhim, *prev = NULL;
    while (curr != NULL && strcmp(curr->MaPhim, maPhim) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        printf(RED"Khong tim thay phim co ma: %s\n"RESET_COLOR, maPhim);
        free(maPhim);
        return;
    }

    // Xác nhận xóa
    printf(RED"\nBan co chac chan muon xoa phim sau khong?\n"RESET_COLOR);
    printf(BLUE"----------------------------------------------------------\n"RESET_COLOR);
    inThongTinPhim(curr);
    printf(BLUE"----------------------------------------------------------\n"RESET_COLOR);
    printf(RED"Nhap 1 de xoa, 0 de huy: "RESET_COLOR);
    int confirm;
    scanf("%d", &confirm);

    if (confirm != 1) {
        printf(RED"Huy xoa phim.\n"RESET_COLOR);
        free(maPhim);
        return;
    }

    // Xóa node khỏi danh sách
    if (!prev) {
        headPhim = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);

    // Ghi danh sách mới vào file
    FILE *a = fopen("phim.txt", "w");
    if (!a) {
        perror("Loi mo file phim.txt");
        free(maPhim);
        return;
    }

    for (PhimNode *temp = headPhim; temp != NULL; temp = temp->next) {
        fprintf(a, "%s|%s|%s|%s|%s|%s|%d\n",
                temp->MaPhim,
                temp->TenPhim,
                temp->TheLoai,
                temp->NgayChieu,
                temp->GioChieu,
                temp->PhongChieu,
                temp->GiaVe);
    }

    fclose(a);
    printf(GREEN"Xoa phim thanh cong!\n"RESET_COLOR);

    // Giải phóng bộ nhớ
    PhimNode *tmp;
    while (headPhim) {
        tmp = headPhim;
        headPhim = headPhim->next;
        free(tmp);
    }

    free(maPhim);
}


// Ham in danh sach ve da dat sap xep theo ma phim
void inDanhSachVe() {
    VeNode *headVe = NULL;
    PhimNode *headPhim = NULL;
    docVeTuFile(&headVe);
    docPhimTuFile(&headPhim);
    printf(BOLD BLUE"                                 DANH SACH VE DA DAT                                   \n"RESET_COLOR);
    printf(BOLD MAGENTA"----------------------------------------------------------------------------------------\n");
    printf("%-10s %-10s %-20s %-10s %-10s %-10s\n", "Ma Ve", "Ma Phim", "Ten Nguoi Dat", "Ghe", "Trang Thai", "Ten phim");
    printf("----------------------------------------------------------------------------------------\n"RESET_COLOR);

    int *soLuongVe;
    soLuongVe = (int*)malloc(100 * sizeof(int));
    if (soLuongVe == NULL) {
        perror(RED"Loi cap phat bo nho"RESET_COLOR);
        exit(1);
    }
    for (int i = 0; i < 100; i++) {
        *(soLuongVe + i) = 0;
    }

    for (VeNode *tempVe = headVe; tempVe; tempVe = tempVe->next) {
        PhimNode *tempPhim = headPhim;
        
        char *tenPhim;
        tenPhim = (char *)malloc(50 * sizeof(char));

       // Kiểm tra xem cấp phát bộ nhớ có thành công không
    if (tenPhim == NULL) {
        perror(RED"Loi cap phat bo nho"RESET_COLOR);
        free(tenPhim); // Giải phóng bộ nhớ nếu không thành công
        exit(1);   // Báo lỗi và thoát chương trình
    }

    // Sao chép trực tiếp chuỗi vào vùng nhớ đã cấp phát
    strcpy(tenPhim, "Khong tim thay");

        while (tempPhim) {
            if (strcmp(tempPhim->MaPhim, tempVe->MaPhim) == 0) {
                strcpy(tenPhim, tempPhim->TenPhim);
                break;
            }
            tempPhim = tempPhim->next;
        }

        printf(BOLD YELLOW"%-10s %-10s %-20s ", 
            tempVe->MaVe, 
            tempVe->MaPhim, 
            tempVe->TenNguoiDung);
        
        int demGhe = 0;
         int doDai = 0; //
        for (int i = 0; i < 40; i++) {
            if (tempVe->GheNgoi[i]) {
                printf("%c%d ", 'A' + i / 8, i % 8 + 1);
                doDai += 3;
                demGhe++;
            }
        }
        if (demGhe == 0) {
            printf("XX ");
            doDai = 3;
        }
		int khoangCach;
        khoangCach = 10 - doDai; 
        if (khoangCach < 0) { // Đảm bảo không âm
            khoangCach = 0;
        }
        for (int k = 0; k < khoangCach; k++) { // In số khoảng trắng cần thiết
            printf(" ");
        }
        printf("%-12s %-35s\n", tempVe->TrangThai == 1 ? "Da dat" : "Da huy", tenPhim);
       printf(RESET_COLOR);

        for (tempPhim = headPhim; tempPhim; tempPhim = tempPhim->next) {
            if (strcmp(tempPhim->MaPhim, tempVe->MaPhim) == 0) {
                soLuongVe[atoi(tempVe->MaPhim + 2)]++;
                break;
            }
        }
    }
//    printf("----------------------------------------------------------------------------------------\n");
    printf(BOLD MAGENTA"----------------------------------------------------------------------------------------\n"RESET_COLOR);
    printf(BOLD BLUE"\n\n                                SO LUONG VE DA DAT THEO PHIM                             \n"RESET_COLOR);
    printf(BOLD MAGENTA"-----------------------------------------------------------------------------------------\n");
    printf("%-15s %-35s %-10s\n", "Ma Phim", "Ten Phim", "So Luong Ve");
    printf("-----------------------------------------------------------------------------------------\n"RESET_COLOR);
    for (PhimNode *tempPhim = headPhim; tempPhim; tempPhim = tempPhim->next) {
        int index = atoi(tempPhim->MaPhim + 2);
        printf(BOLD YELLOW"%-15s %-35s %-10d\n", 
            tempPhim->MaPhim, 
            tempPhim->TenPhim, 
            soLuongVe[index]);
    }
    printf(RESET_COLOR);
	printf(BOLD MAGENTA"-----------------------------------------------------------------------------------------\n"RESET_COLOR);
    
    VeNode *tmpVe;
    while (headVe) {
        tmpVe = headVe;
        headVe = headVe->next;
        free(tmpVe);
    }
    PhimNode *tmpPhim;
    while (headPhim) {
        tmpPhim = headPhim;
        headPhim = headPhim->next;
        free(tmpPhim);
    }
}
void thongKeDoanhThu() {
    VeNode *headVe = NULL;
    PhimNode *headPhim = NULL;
    docVeTuFile(&headVe);
    docPhimTuFile(&headPhim);

    printf(BOLD BLUE"                                 THONG KE DOANH THU                                     \n"RESET_COLOR);
    printf(BOLD MAGENTA"----------------------------------------------------------------------------------------\n");
    printf("%-15s %-35s %-10s\n", "Ma Phim", "Ten Phim", "Doanh Thu");
    printf("----------------------------------------------------------------------------------------\n"RESET_COLOR);

    for (PhimNode *tempPhim = headPhim; tempPhim; tempPhim = tempPhim->next) {
        int doanhThu = 0;
        for (VeNode *tempVe = headVe; tempVe; tempVe = tempVe->next) {
        	// Kiểm tra nếu MaPhim của vé trùng với MaPhim của phim hiện tại
            // VÀ trạng thái vé là 1 (nghĩa là vé đã được bán/thanh toán)
            if (strcmp(tempPhim->MaPhim, tempVe->MaPhim) == 0 && tempVe->TrangThai == 1) {
    // Cộng giá vé của phim vào tổng doanh thu của bộ phim đó
	            doanhThu += tempPhim->GiaVe;
            }
        }
        // In Mã Phim, Tên Phim và Doanh Thu với màu vàng đậm và định dạng căn lề
        printf(BOLD YELLOW"%-15s %-35s %-10d\n", 
            tempPhim->MaPhim, 
            tempPhim->TenPhim, 
            doanhThu);
    }
    printf(RESET_COLOR);
    printf(BOLD MAGENTA"----------------------------------------------------------------------------------------\n"RESET_COLOR);
// --- Giải phóng bộ nhớ của danh sách liên kết vé ---
    VeNode *tmpVe;
    while (headVe) {
        tmpVe = headVe;
        headVe = headVe->next;
        free(tmpVe);
    }
    // --- Giải phóng bộ nhớ của danh sách liên kết phim ---
    PhimNode *tmpPhim;
    while (headPhim) {
        tmpPhim = headPhim;
        headPhim = headPhim->next;
        free(tmpPhim);
    }
}

// Ham ghi danh sach nguoi dung vao file nguoidung.txt
void ghiDanhSachNguoiDungVaoFile(NguoiDungNode *head) {
    // Mở file nguoidung.txt để ghi
    // Nếu file không tồn tại, tạo mới
    FILE *a = fopen("nguoidung.txt", "w");
    if ( a == NULL) {
        // Nếu không mở được file, thông báo lỗi
        perror("Loi mo file nguoidung.txt de ghi");
        return;
    }

    NguoiDungNode *current = head;
    while (current) {
        fprintf(a, "%s|%s|%d\n", current->username,
            current->password, 
            current->type);
        current = current->next;
    }
    fclose(a);
}

// Ham in danh sach tat ca nguoi dung
void inDanhSachNguoiDung(void) {
    NguoiDungNode *head = NULL;
    docTaiKhoanTuFile(&head);

    printf(BOLD RED"                                 DANH SACH NGUOI DUNG                                  \n"RESET_COLOR);
    printf(BOLD BLUE"----------------------------------------------------------------------------------------\n");
    printf("%-20s %-10s\n", "Ten Dang Nhap", "Loai Tai Khoan");
    printf("----------------------------------------------------------------------------------------\n"RESET_COLOR);

    NguoiDungNode *current = head;
    while (current != NULL) {
        // In tên đăng nhập và loại tài khoản
        printf(BOLD YELLOW"%-20s %-10s\n", current->username, current->type == 1 ? "Admin" : "User");
        current = current->next;
    }
    printf(RESET_COLOR);
    printf(BOLD BLUE"----------------------------------------------------------------------------------------\n"RESET_COLOR);
    // Giai phong bo nho
    NguoiDungNode *tmp;
    while (head) {
        tmp = head;
        head = tmp->next;
        free(tmp);
    }
}

// Ham xoa tai khoan nguoi dung
void xoaTaiKhoanNguoiDung(char *adminUser) {
    NguoiDungNode *head = NULL;
    docTaiKhoanTuFile(&head);

    xoaMH();
    inDanhSachNguoiDung();

    char *tenCanXoa;
    tenCanXoa = (char*)malloc(15 * sizeof(char));
    if (tenCanXoa == NULL) {
        perror(RED"Loi cap phat bo nho"RESET_COLOR);
        return;
    }
    printf(RED"\nNhap ten dang nhap cua nguoi dung muon xoa: "RESET_COLOR);
    scanf("%14s", tenCanXoa);
 // Kiểm tra xem tên đăng nhập muốn xóa có trùng với tên đăng nhập của admin
    if (strcmp(tenCanXoa, adminUser) == 0) {
        printf(RED"Ban khong the xoa tai khoan admin dang su dung!\n"RESET_COLOR);
         // Giai phong bo nho
        NguoiDungNode *tmp;
        while (head) {
            tmp = head;
            head = tmp->next;
            free(tmp);
        }
        return;
    }

    NguoiDungNode *curr = head, *prev = NULL;
    // Duyệt danh sách để tìm nút có username trùng với tên đăng nhập người dùng nhập
    while (curr != NULL && strcmp(curr->username, tenCanXoa) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        printf("Khong tim thay nguoi dung voi ten dang nhap: %s\n", tenCanXoa);
         // Giai phong bo nho
        NguoiDungNode *tmp;
        while (head) {
            tmp = head;
            head = tmp->next;
            free(tmp);
        }
        return;
    }

    printf(RED"Ban co chac chan muon xoa tai khoan cua nguoi dung '%s' khong?\n", tenCanXoa);
    printf("Nhap 1 de xac nhan, 0 de huy: "RESET_COLOR);
    int confirm;
    scanf("%d", &confirm);

    if (confirm != 1) {
        printf(RED"Huy xoa tai khoan.\n"RESET_COLOR);
         // Giai phong bo nho
        NguoiDungNode *tmp;
        while (head) {
            tmp = head;
            head = tmp->next;
            free(tmp);
        }
        return;
    }

    // Xoa node
    if ( prev == NULL) {
        head = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);

    // Ghi lai danh sach moi vao file
    ghiDanhSachNguoiDungVaoFile(head);

    printf("Xoa tai khoan nguoi dung '%s' thanh cong!\n", tenCanXoa);

    // Giai phong bo nho
    NguoiDungNode *tmp;
    while (head) {
        tmp = head;
        head = tmp->next;
        free(tmp);
    }
}
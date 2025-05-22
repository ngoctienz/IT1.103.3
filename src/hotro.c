#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "hotro.h"

void xoaMH(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Dung chuong trinh trong t giay va thong bao chuyen huong
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
void docTaiKhoanTuFile(NguoiDungNode **head) {
    FILE *a = fopen("nguoidung.txt", "r");
    if (!a) { perror("Loi file"); exit(1); }

    while (!feof(a)) {
        NguoiDungNode *temp = (NguoiDungNode*)malloc(sizeof(NguoiDungNode));
        if (!temp) {
             perror("Loi cap phat bo nho");
             exit(1);
        }
        char pass[15];
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
void docPhimTuFile(PhimNode **head) {
    FILE *a = fopen("phim.txt", "r");
    if (a == NULL) {
        perror("Loi file"); 
        exit(1); 
    }

    while (!feof(a)) {
        PhimNode *temp = (PhimNode*)malloc(sizeof(PhimNode));
        if (temp == NULL) {
             // Cap phat bo nho that bai
             perror("Loi cap phat bo nho");
             exit(1);
        }

        if (fscanf(a, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d\n", temp->MaPhim, 
                    temp->TenPhim, 
                    temp->TheLoai,
                    temp->NgayChieu, 
                    temp->GioChieu, 
                    temp->PhongChieu, 
                    &temp->GiaVe) == 7) {
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
    PhimNode *temp = NULL;
    docPhimTuFile(&temp);
    printf(BLUE"                                         DANH SACH PHIM                                   \n"RESET_COLOR);
    printf(RED"------------------------------------------------------------------------------------------\n"RESET_COLOR);
    printf(RED"%-10s %-15s %-15s %-10s %-10s %-10s %-10s\n", "Ma Phim", "Ten Phim", "The Loai", "Ngay", "Gio", "Phong", "Gia ve");
    printf("------------------------------------------------------------------------------------------\n"RESET_COLOR);
    while (temp != NULL) {
        printf(YELLOW"%-10s %-15s %-15s %-10s %-10s %-10s %-10d\n", 
            temp->MaPhim, 
            temp->TenPhim, 
            temp->TheLoai, 
            temp->NgayChieu, 
            temp->GioChieu, 
            temp->PhongChieu, 
            temp->GiaVe);
        temp = temp->next;
    }
    printf(RESET_COLOR);
    printf(RED"------------------------------------------------------------------------------------------\n"RESET_COLOR);
    }
// Ham doc danh sach ve tu file ve.txt va luu vao danh sach lien ket
void docVeTuFile(VeNode **head) {
    FILE *a = fopen("ve.txt", "r");
    if (a == NULL) {
        perror("Loi file"); 
        exit(1); 
    }
    while (!feof(a)) {// Lap cho den khi dat cuoi tep
        VeNode *temp = (VeNode*)malloc(sizeof(VeNode));
        if (!temp) { perror(RED"Loi cap phat bo nho"RESET_COLOR); exit(1); }

        char gheChuoi[200];
        if (fscanf(a, "%[^|]|%[^|]|%[^|]|%[^|]|%d\n", 
            temp->MaVe, 
            temp->MaPhim, 
            temp->TenNguoiDung, 
            gheChuoi, 
            &temp->TrangThai) == 5) {
            char *token = strtok(gheChuoi, ",");// Bat dau phan tich chuoi ghe ngoi bang dau phay
            int i = 0;
            while (token && i < 40) {// Lap qua cac token (so ghe) va gioi han 40 ghe
                // Chuyen token sang so nguyen va luu vao mang GheNgoi
                temp->GheNgoi[i++] = atoi(token);
                token = strtok(NULL, ",");// Lay token tiep theo
            }
            // Dien 0 cho cac vi tri con lai neu it hon 40 ghe
            while (i < 40) temp->GheNgoi[i++] = 0;
            temp->next = *head;
            *head = temp;
        } else {
            free(temp);
        }
    }
    fclose(a);
}

// Ham ghi danh sach ve vao file ve.txt
void ghiDanhSachVeVaoFile(VeNode *head) {
    FILE *f = fopen("ve.txt", "w");
    if (!f) { 
        perror("Loi file");
        exit(1); 
    }

    VeNode *current = head;
    while (current) {// Lap qua tung ve trong danh sach lien ket cho den khi gap NULL.
        fprintf(f, "%s|%s|%s|", current->MaVe, 
            current->MaPhim, 
            current->TenNguoiDung);
        for (int i = 0; i < 40; i++) {
            // Lap qua mang GheNgoi (40 phan tu) de ghi trang thai tung ghe
            fprintf(f, "%d", current->GheNgoi[i]);
            // Ghi trang thai ghe (0 hoac 1).
            if (i < 39) fprintf(f, ",");
            // Ghi dau phay sau moi so ghe, tru so cuoi cung.
        }
        fprintf(f, "|%d\n", current->TrangThai);
        current = current->next;
    }
    fclose(f);
}
// Ham tao ma ve ngau nhien
void taoMaVe(char *maVe) {
    srand(time(NULL)); // Khoi tao bo sinh so ngau nhien dua tren thoi gian hien tai
    sprintf(maVe, "VE%04d", rand() % 10000);// Tao ma ve co dang "VE" theo sau la 4 chu so ngau nhien
}

// Ham in so do ghe cua mot phim
void inSoDoGhe(VeNode *headVe, const char *maPhim) {
    // Gia su MAX_GHE la so luong ghe toi da, vi du 40
    int ghe[MAX_GHE] = {0};
    for (VeNode *temp = headVe; temp; temp = temp->next) {// Duyet qua danh sach lien ket cac ve
        if (strcmp(temp->MaPhim, maPhim) == 0) {// Kiem tra neu ve hien tai thuoc ve phim co ma trung voi maPhim duoc truyen vao
            for (int i = 0; i < MAX_GHE; i++) {
                if (temp->GheNgoi[i]) ghe[i] = 1;
            }
        }
    }

    printf(RED"\nSo do ghe (X: da dat, O: trong):\n"RESET_COLOR);
    printf("  ------------------------\n");

    for (char hang = 'A'; hang <= 'E'; hang++) {
        printf("%c |", hang);// In ten hang (A, B, C, D, E) va ky tu phan cach
        for (int cot = 1; cot <= 8; cot++) {// Duyet qua cac cot ghe (tu 1 den 8)
            int idx = (hang - 'A') * 8 + (cot - 1);
            printf(" %-2s", ghe[idx] ? RED"X"RESET_COLOR : GREEN"O"RESET_COLOR);
            printf(" ");      // In trang thai ghe (X: da dat, O: trong) va ky tu phan cach
        }
        printf("\n");
    }

    printf("  ------------------------\n");
    printf("   ");
    for (int cot = 1; cot <= 8; cot++) {// In so thu tu cua cac cot (tu 1 den 8)
        printf(" %-2d", cot);
    }
    printf("\n");
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
    taoMaVe(newVe->MaVe);   // Tao ma ve duy nhat cho ve moi

    char *maPhim = (char*)malloc(15 * sizeof(char));
    char *gheNgoi = (char*)malloc(3 * sizeof(char));
    if (maPhim == NULL || gheNgoi == NULL) { 
        perror(RED"Loi cap phat bo nho"RESET_COLOR); 
        free(maPhim);
        free(gheNgoi);
        free(newVe);
        exit(1); 
    }
    int c;
    int gheINT;
    newVe->TrangThai = 1; // Dat trang thai ve moi la 1 (da dat)
    inDanhSachPhim(); // Hien thi danh sach phim de nguoi dung chon
    PhimNode *tempPhim = headPhim; // Khoi tao tempPhim truoc vong lap
    do {
        printf(YELLOW"Nhap ma phim muon dat ve (0 de huy): "RESET_COLOR);
        scanf("%14s", maPhim);
        while ((c = getchar()) != '\n' && c != EOF); // Xoa bo dem nhap
        if (strcmp(maPhim, "0") == 0) { // Kiem tra neu nguoi dung nhap 0
            printf(RED"Da huy thao tac dat ve.\n"RESET_COLOR);
            free(maPhim);
            free(gheNgoi);
            free(newVe);
            return; // Thoat ham
        }
        // Reset tempPhim de duyet lai
        tempPhim = headPhim; 
        while (tempPhim) {
            if (strcmp(tempPhim->MaPhim, maPhim) == 0) {
                 // So sanh ma phim nhap voi ma phim trong danh sach
                strcpy(newVe->MaPhim, maPhim); 
                // Sao chep ma phim da chon vao nut ve moi
                break;
            }
            tempPhim = tempPhim->next; // Chuyen sang phim tiep theo
        }
        if (!tempPhim) {
            printf(RED"Ma phim khong ton tai!\n"RESET_COLOR);
        } else {
            inSoDoGhe(headVe, maPhim);
            break;
        }
    } while (1);

    printf(GREEN"Nguoi dat ve: %s\n"RESET_COLOR, user);
    strcpy(newVe->TenNguoiDung, user);

    do {
        printf(GREEN"Nhap ghe ngoi (VD: A1, 0 de huy): "RESET_COLOR);
        scanf("%2s", gheNgoi);
        while ((c = getchar()) != '\n' && c != EOF); // Xoa bo dem nhap
        if (strcmp(gheNgoi, "0") == 0) { // Kiem tra neu nguoi dung nhap 0
            printf(RED"Da huy thao tac dat ve.\n"RESET_COLOR);
            free(maPhim);
            free(gheNgoi);
            free(newVe);
            return; // Thoat ham
        }
        if (strlen(gheNgoi) != 2 || *gheNgoi < 'A' || *gheNgoi > 'E' || *(gheNgoi + 1) < '1' || *(gheNgoi + 1) > '8') { // Kiem tra dinh dang nhap ghe ngoi
            printf(RED"Dinh dang sai.\n"RESET_COLOR);
            continue;
        }
        gheINT = (*gheNgoi - 'A') * 8 + (*(gheNgoi + 1) - '1');
        int daDat = 0;
        for (VeNode *temp = headVe; temp; temp = temp->next) {
            if (strcmp(temp->MaPhim, newVe->MaPhim) == 0 && temp->GheNgoi[gheINT]) {
                daDat = 1;
                break;
            }
        }
        if (!daDat) {
            for (int i = 0; i < 40; i++) newVe->GheNgoi[i] = 0;
            newVe->GheNgoi[gheINT] = 1; // Danh dau ghe da chon la 1 (da dat) trong ve moi
            newVe->next = headVe;
            headVe = newVe;
            ghiDanhSachVeVaoFile(headVe);
            printf(GREEN"Dat ve thanh cong!\n"RESET_COLOR);
            printf(YELLOW"Ma ve: %s\n", newVe->MaVe);
            printf(YELLOW"Ghe da dat: %s\n", gheNgoi);
            break;
        } else {
            printf(GREEN"Ghe da duoc dat!\n"RESET_COLOR);
            printf(YELLOW"Hay chon ghe khac.\n"RESET_COLOR); // Khuyen khich chon lai ghe
        }
    } while (1);

    free(maPhim);
    free(gheNgoi);
    // Khong giai phong headPhim va headVe vi chung duoc cap phat boi docPhimTuFile va docVeTuFile
}

// Ham in danh sach ve da dat cua nguoi dung
void inVeDaDat(char *user) {
    VeNode *headVe = NULL;
    docVeTuFile(&headVe);
 
    printf(BLUE"                                    DANH SACH VE DA DAT                              \n");
    printf(MAGENTA"----------------------------------------------------------------------------------------");
    printf(RED"\n%-10s %-10s %-20s %-20s %-12s\n", "Ma Ve", "Ma Phim", "Ten Nguoi Dat", "Ghe Ngoi", "Trang Thai");
    printf(MAGENTA"----------------------------------------------------------------------------------------\n");
    for (VeNode *temp = headVe; temp; temp = temp->next) {
        if (strcmp(temp->TenNguoiDung, user) == 0) {
            // In dong dau voi cac truong co ban
            printf(BOLD YELLOW"%-10s %-10s %-20s ", temp->MaVe, 
                temp->MaPhim, 
                temp->TenNguoiDung);

            // In cac ghe da dat
            int demGhe = 0;
            char gheStr[21]; // Bo dem de luu chuoi ghe, do dai toi da 20 + null terminator
            gheStr[0] = '\0'; // Khoi tao chuoi rong
            for (int i = 0; i < 40 && demGhe < 10; i++) { // Gioi han 10 ghe de tranh tran
                if (temp->GheNgoi[i]) {
                    char tempGhe[5];
                    snprintf(tempGhe, sizeof(tempGhe), "%c%d ", 'A' + i / 8, i % 8 + 1);
                    if (strlen(gheStr) + strlen(tempGhe) < 20) {
                        strcat(gheStr, tempGhe);
                        demGhe++;
                    } else {
                        break; // Dung neu vuot qua 20 ky tu
                    }
                }
            }
            if (demGhe == 0) {
                strncpy(gheStr, "XX", 3); // "XX" + null terminator
            }
            printf("%-20s", gheStr);

            // In trang thai voi do rong co dinh 12 ky tu, tach mau sac
            if (temp->TrangThai == 1) {
                printf(GREEN"%-12s"RESET_COLOR, "Da dat");
            } else {
                printf(RED"%-12s"RESET_COLOR, "Da huy");
            }
            printf("\n");
        }
    }

    printf(MAGENTA"----------------------------------------------------------------------------------------\n"RESET_COLOR);

    // Giai phong bo nho
    VeNode *tmp;
    while (headVe) {
        tmp = headVe;
        headVe = headVe->next;
        free(tmp);
    }
}

// Ham huy ve da dat cua nguoi dung
void huyVeDaDat(char *user) {
    VeNode *headVe = NULL;
    docVeTuFile(&headVe);

    char *maVe = (char*)malloc(15 * sizeof(char));
    if (maVe == NULL) { 
        perror("Loi cap phat bo nho"); 
        exit(1); 
    }

    inVeDaDat(user);
    printf(YELLOW"Nhap ma ve muon huy (0 de thoat): "RESET_COLOR);
    scanf("%14s", maVe);
    if (strcmp(maVe, "0") == 0) { // Kiem tra neu nguoi dung nhap 0
        printf(RED"Da huy thao tac huy ve.\n"RESET_COLOR);
        free(maVe);
        // Giai phong danh sach lien ket
        VeNode *tmp;
        while (headVe) {
            tmp = headVe;
            headVe = headVe->next;
            free(tmp);
        }
        return; // Thoat ham
    }
    int found = 0;
    VeNode *temp = headVe;
    while (temp) { // Lap qua tung ve trong danh sach
    // Kiem tra neu ma ve, ten nguoi dung trung khop va trang thai ve la 1 (chua huy)
        if (strcmp(temp->MaVe, maVe) == 0 && strcmp(temp->TenNguoiDung, user) == 0 && temp->TrangThai == 1) {
            printf(YELLOW"Ban chac chan muon huy ve: "RESET_COLOR);
            for (int i = 0; i < 40; i++) {
                if (temp->GheNgoi[i]) {// Neu ghe thu i da duoc dat (gia tri la 1)
                    printf("%c%d ", 'A' + i / 8, i % 8 + 1);// In ten ghe (vi du: A1, B5)
                }
            }
            printf(BLUE"?\nNhap 1 de xac nhan, 0 de huy thao tac: "RESET_COLOR);

            int xacNhan;
            scanf("%d", &xacNhan);
            if (xacNhan != 1) {
                printf(RED"Da huy thao tac huy ve.\n"RESET_COLOR);
                free(maVe);
                // Giai phong danh sach
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
            }
            ghiDanhSachVeVaoFile(headVe);
            printf("Huy ve thanh cong!\n");
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf(RED"Ma ve khong ton tai, da bi huy, hoac khong phai cua ban!\n"RESET_COLOR);
    }

    // Giai phong
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

    PhimNode *newPhim = (PhimNode *)malloc(sizeof(PhimNode));
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

    FILE *f = fopen("phim.txt", "a");
    if (!f) {
        perror("Loi mo file phim.txt");
        free(newPhim);
        return;
    }

    fprintf(f, "%s|%s|%s|%s|%s|%s|%d\n",newPhim->MaPhim,
        newPhim->TenPhim,
        newPhim->TheLoai,
        newPhim->NgayChieu,
        newPhim->GioChieu,
        newPhim->PhongChieu,
        newPhim->GiaVe);

    fclose(f);

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

// Ham in thong tin phim
void inThongTinPhim(PhimNode *p) {
    if (p) {
        printf("Ma phim: %s\n", p->MaPhim);
        printf("Ten phim: %s\n", p->TenPhim);
        printf("The loai: %s\n", p->TheLoai);
        printf("Ngay chieu: %s\n", p->NgayChieu);
        printf("Gio chieu: %s\n", p->GioChieu);
        printf("Phong chieu: %s\n", p->PhongChieu);
        printf("Gia ve: %d\n", p->GiaVe);
    }
}

// Ham sua thong tin phim
void suaPhim() {
    PhimNode *headPhim = NULL;
    docPhimTuFile(&headPhim);

    inDanhSachPhim();

    char maPhim[15];
    printf("Nhap ma phim muon sua: ");
    scanf("%s", maPhim);

    PhimNode *found = NULL;
    for (PhimNode *temp = headPhim; temp != NULL; temp = temp->next) {
        if (strcmp(temp->MaPhim, maPhim) == 0) {
            found = temp;
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay phim voi ma da nhap!\n");
        return;
    }

    int choice;
    do {
        xoaMH();
        printf("\n---------------------THONG TIN PHIM---------------------\n");
        inThongTinPhim(found);
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
                scanf("%s", found->MaPhim);
                break;
            case 2:
                printf(BLUE"Nhap ten phim moi: "RESET_COLOR);
                fgets(found->TenPhim, sizeof(found->TenPhim), stdin);
                strtok(found->TenPhim, "\n");
                break;
            case 3:
                printf(BLUE"Nhap the loai moi: "RESET_COLOR);
                fgets(found->TheLoai, sizeof(found->TheLoai), stdin);
                strtok(found->TheLoai, "\n");
                break;
            case 4:
                printf(BLUE"Nhap ngay chieu moi: "RESET_COLOR);
                scanf("%s", found->NgayChieu);
                break;
            case 5:
                printf(BLUE"Nhap gio chieu moi: "RESET_COLOR);
                scanf("%s", found->GioChieu);
                break;
            case 6:
                printf(BLUE"Nhap phong chieu moi: "RESET_COLOR);
                scanf("%s", found->PhongChieu);
                break;
            case 7:
                printf(BLUE"Nhap gia ve moi: "RESET_COLOR);
                scanf("%d", &found->GiaVe);
                break;
            case 0:
                break;
            default:
                printf(RED"Lua chon khong hop le!\n"RESET_COLOR);
        }
    } while (choice != 0);

    FILE *f = fopen("phim.txt", "w");
    if (!f) {
        perror("Loi mo file phim.txt");
        return;
    }

    for (PhimNode *temp = headPhim; temp != NULL; temp = temp->next) {
        fprintf(f, "%s|%s|%s|%s|%s|%s|%d\n",
                temp->MaPhim,
                temp->TenPhim,
                temp->TheLoai,
                temp->NgayChieu,
                temp->GioChieu,
                temp->PhongChieu,
                temp->GiaVe);
    }

    fclose(f);

    PhimNode *tmp;
    while (headPhim) {
        tmp = headPhim;
        headPhim = headPhim->next;
        free(tmp);
    }
}

// Ham xoa phim
void xoaPhim() {
    PhimNode *headPhim = NULL;
    docPhimTuFile(&headPhim);
    inDanhSachPhim();
    char maPhim[15];
    printf(RED"Nhap ma phim muon xoa (0 de thoat): "RESET_COLOR);
    scanf("%14s", maPhim);
    if (strcmp(maPhim, "0") == 0) { // Kiem tra neu nguoi dung nhap 0
        printf(RED"Da huy thao tac xoa phim.\n"RESET_COLOR);
        // Giai phong bo nho
        PhimNode *tmp;
        while (headPhim) {
            tmp = headPhim;
            headPhim = headPhim->next;
            free(tmp);
        }
        return; // Thoat ham
    }
    // Khoi tao con tro 'curr' tro den dau danh sach, 'prev' la NULL
    PhimNode *curr = headPhim, *prev = NULL;
    // Duyet danh sach de tim nut co MaPhim trung voi ma nguoi dung nhap
    while (curr != NULL && strcmp(curr->MaPhim, maPhim) != 0) {
        prev = curr;// Cap nhat 'prev' truoc khi 'curr' di chuyen
        curr = curr->next;
    }
    if (!curr) {
        printf("Khong tim thay phim co ma: %s\n", maPhim);
        return;
    }

    printf(RED"Ban co chac chan muon xoa phim sau khong?\n"RESET_COLOR);
    printf(BLUE"----------------------------------------------------------\n"RESET_COLOR);
    inThongTinPhim(curr);
    printf(BLUE"----------------------------------------------------------\n"RESET_COLOR);
    printf(RED"Nhap 1 de xoa, 0 de huy: "RESET_COLOR);
    int confirm;
    scanf("%d", &confirm);

    if (confirm != 1) {
        printf(RED"Huy xoa phim.\n"RESET_COLOR);
        return;
    }
    // Xoa node
    if (!prev) {
        headPhim = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);

    // Ghi lai danh sach moi vao file
    FILE *f = fopen("phim.txt", "w");
    if (!f) {
        perror("Loi mo file phim.txt");
        return;
    }

    for (PhimNode *temp = headPhim; temp != NULL; temp = temp->next) {
        fprintf(f, "%s|%s|%s|%s|%s|%s|%d\n",
                temp->MaPhim,
                temp->TenPhim,
                temp->TheLoai,
                temp->NgayChieu,
                temp->GioChieu,
                temp->PhongChieu,
                temp->GiaVe);
    }

    fclose(f);
    printf("Xoa phim thanh cong!\n");

    // Giai phong bo nho
    PhimNode *tmp;
    while (headPhim) {
        tmp = headPhim;
        headPhim = headPhim->next;
        free(tmp);
    }
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

    int soLuongVe[100]; 
    for (int i = 0; i < 100; i++) {
        soLuongVe[i] = 0;
    }

    for (VeNode *tempVe = headVe; tempVe; tempVe = tempVe->next) {
        PhimNode *tempPhim = headPhim;
        char tenPhim[50] = "Khong tim thay";
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
        int currentGheDisplayedLength = 0;
        for (int i = 0; i < 40; i++) {
            if (tempVe->GheNgoi[i]) {
                printf("%c%d ", 'A' + i / 8, i % 8 + 1);
                currentGheDisplayedLength += 3;
                demGhe++;
            }
        }
        if (demGhe == 0) {
            printf("XX ");
            currentGheDisplayedLength = 3;
        }
        int requiredPadding = 10 - currentGheDisplayedLength; // Tinh toan so khoang trang can them
        if (requiredPadding < 0) { // Dam bao khong am
            requiredPadding = 0;
        }
        for (int k = 0; k < requiredPadding; k++) { // In so khoang trang can thiet
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
    printf(BOLD MAGENTA"----------------------------------------------------------------------------------------\n"RESET_COLOR);
    printf(BOLD BLUE"\n\n                                SO LUONG VE DA DAT THEO PHIM                             \n"RESET_COLOR);
    printf(BOLD MAGENTA"-----------------------------------------------------------------------------------------\n");
    printf("%-15s %-35s %-10s\n", "Ma Phim", "Ten Phim", "So Luong Ve");
    printf("-----------------------------------------------------------------------------------------\n"RESET_COLOR);
    for (PhimNode *tempPhim = headPhim; tempPhim; tempPhim = tempPhim->next) {
        int index = atoi(tempPhim->MaPhim + 2);
        printf(BOLD YELLOW"%-15s %-35s %-10d\n", tempPhim->MaPhim, 
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
// Ham thong ke doanh thu theo phim
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
            // Kiem tra neu MaPhim cua ve trung voi MaPhim cua phim hien tai
            // VA trang thai ve la 1 (nghia la ve da duoc ban/thanh toan)
            if (strcmp(tempPhim->MaPhim, tempVe->MaPhim) == 0 && tempVe->TrangThai == 1) {
                // Cong gia ve cua phim vao tong doanh thu cua bo phim do
                doanhThu += tempPhim->GiaVe;
            }
        }
        // In Ma Phim, Ten Phim va Doanh Thu voi mau vang dam va dinh dang can le
        printf(BOLD YELLOW"%-15s %-35s %-10d\n", tempPhim->MaPhim, 
            tempPhim->TenPhim, 
            doanhThu);
    }
    printf(RESET_COLOR);
    printf(BOLD MAGENTA"----------------------------------------------------------------------------------------\n"RESET_COLOR);
    // Giai phong bo nho cua danh sach lien ket ve
    VeNode *tmpVe;
    while (headVe) {
        tmpVe = headVe;
        headVe = headVe->next;
        free(tmpVe);
    }
    // Giai phong bo nho cua danh sach lien ket phim
    PhimNode *tmpPhim;
    while (headPhim) {
        tmpPhim = headPhim;
        headPhim = headPhim->next;
        free(tmpPhim);
    }
}
// Ham ghi danh sach nguoi dung vao file nguoidung.txt
void ghiDanhSachNguoiDungVaoFile(NguoiDungNode *head) {
    FILE *f = fopen("nguoidung.txt", "w");
    if (!f) {
        perror("Loi mo file nguoidung.txt de ghi");
        return;
    }

    NguoiDungNode *current = head;
    while (current) {
        // CANH BAO: Ghi mat khau ra file. Nen ma hoa trong ung dung thuc te.
        fprintf(f, "%s|%s|%d\n", current->username, 
            current->password, 
            current->type);
        current = current->next;
    }
    fclose(f);
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
        // Khong hien thi mat khau truc tiep
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

    char usernameToDelete[15];// Bo dem de luu ten dang nhap can xoa
    printf(RED"\nNhap ten dang nhap cua nguoi dung muon xoa: "RESET_COLOR);
    scanf("%14s", usernameToDelete);
    // Kiem tra xem ten dang nhap muon xoa 
    // co trung voi ten dang nhap cua admin
    if (strcmp(usernameToDelete, adminUser) == 0) {
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
    // Duyet danh sach de tim nut co username trung voi ten dang nhap nguoi dung nhap
    while (curr != NULL && strcmp(curr->username, usernameToDelete) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        printf("Khong tim thay nguoi dung voi ten dang nhap: %s\n", usernameToDelete);
        // Giai phong bo nho
        NguoiDungNode *tmp;
        while (head) {
            tmp = head;
            head = tmp->next;
            free(tmp);
        }
        return;
    }

    printf(RED"Ban co chac chan muon xoa tai khoan cua nguoi dung '%s' khong?\n", usernameToDelete);
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
    if (!prev) {
        head = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);

    // Ghi lai danh sach moi vao file
    ghiDanhSachNguoiDungVaoFile(head);

    printf("Xoa tai khoan nguoi dung '%s' thanh cong!\n", usernameToDelete);

    // Giai phong bo nho
    NguoiDungNode *tmp;
    while (head) {
        tmp = head;
        head = tmp->next;
        free(tmp);
    }
}

// Ham cam on
void camOn() {
    xoaMH();
    printf(BOLD GREEN"CAM ON BAN DA SU DUNG CHUONG TRINH!\n"RESET_COLOR);
    printf(BOLD YELLOW"----------------------------------------------------------\n"RESET_COLOR);
    printf(BOLD YELLOW"|                  NHOM THUC HIEN                        |\n"RESET_COLOR);
    printf(BOLD YELLOW"----------------------------------------------------------\n"RESET_COLOR);
    printf(BOLD YELLOW"|             Nguyen Ngoc Tien - 6551071079              |\n"RESET_COLOR);
    printf(BOLD YELLOW"|             Ngo Thanh Tien - 6551071082                |\n"RESET_COLOR);
    printf(BOLD YELLOW"----------------------------------------------------------\n"RESET_COLOR);
    stop(3,"Exit");
    printf(BOLD YELLOW"----------------------------------------------------------\n"RESET_COLOR);
}
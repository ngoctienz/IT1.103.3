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
        if (!temp) { perror("Loi cap phat bo nho"); exit(1); }

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

void docPhimTuFile(PhimNode **head) {
    FILE *a = fopen("phim.txt", "r");
    if (!a) { perror("Loi file"); exit(1); }

    while (!feof(a)) {
        PhimNode *temp = (PhimNode*)malloc(sizeof(PhimNode));
        if (!temp) { perror("Loi cap phat bo nho"); exit(1); }

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
    PhimNode *temp = NULL;
    docPhimTuFile(&temp);
    printf("                                         DANH SACH PHIM                                   \n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-15s %-10s %-10s %-10s %-10s\n", "Ma Phim", "Ten Phim", "The Loai", "Ngay", "Gio", "Phong", "Gia ve");
    printf("------------------------------------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("%-10s %-15s %-15s %-10s %-10s %-10s %-10d\n", temp->MaPhim, temp->TenPhim, temp->TheLoai, temp->NgayChieu, temp->GioChieu, temp->PhongChieu, temp->GiaVe);
        temp = temp->next;
    }
    printf("------------------------------------------------------------------------------------------\n");
    }





// Ham doc danh sach ve tu file ve.txt
// va luu vao danh sach lien ket

void docVeTuFile(VeNode **head) {
    FILE *a = fopen("ve.txt", "r");
    if (!a) { perror("Loi file"); exit(1); }

    while (!feof(a)) {
        VeNode *temp = (VeNode*)malloc(sizeof(VeNode));
        if (!temp) { perror("Loi cap phat bo nho"); exit(1); }

        char gheChuoi[200];
        if (fscanf(a, "%[^|]|%[^|]|%[^|]|%[^|]|%d\n", temp->MaVe, temp->MaPhim, temp->TenNguoiDung, gheChuoi, &temp->TrangThai) == 5) {
            char *token = strtok(gheChuoi, ",");
            int i = 0;
            while (token && i < 40) {
                temp->GheNgoi[i++] = atoi(token);
                token = strtok(NULL, ",");
            }
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
    if (!f) { perror("Loi file"); exit(1); }

    VeNode *current = head;
    while (current) {
        fprintf(f, "%s|%s|%s|", current->MaVe, current->MaPhim, current->TenNguoiDung);
        for (int i = 0; i < 40; i++) {
            fprintf(f, "%d", current->GheNgoi[i]);
            if (i < 39) fprintf(f, ",");
        }
        fprintf(f, "|%d\n", current->TrangThai);
        current = current->next;
    }
    fclose(f);
}

void taoMaVe(char *maVe) {
    srand(time(NULL));
    sprintf(maVe, "VE%04d", rand() % 10000);
}

void inSoDoGhe(VeNode *headVe, const char *maPhim) {
    // Giả sử MAX_GHE là số lượng ghế tối đa, ví dụ 40
    int ghe[MAX_GHE] = {0};
    for (VeNode *temp = headVe; temp; temp = temp->next) {
        if (strcmp(temp->MaPhim, maPhim) == 0) {
            for (int i = 0; i < MAX_GHE; i++) {
                if (temp->GheNgoi[i]) ghe[i] = 1;
            }
        }
    }

    printf("\nSo do ghe (X: da dat, O: trong):\n");
    printf("  ------------------------\n");

    for (char hang = 'A'; hang <= 'E'; hang++) {
        printf("%c |", hang);
        for (int cot = 1; cot <= 8; cot++) {
            int idx = (hang - 'A') * 8 + (cot - 1);
            printf(" %-2s", ghe[idx] ? "X" : "O");
        }
        printf("\n");
    }

    printf("  ------------------------\n");
    printf("   ");
    for (int cot = 1; cot <= 8; cot++) {
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
        perror("Loi cap phat bo nho"); 
        exit(1); 
    }
    taoMaVe(newVe->MaVe);   

    char *maPhim = (char*)malloc(15 * sizeof(char));
    char *gheNgoi = (char*)malloc(3 * sizeof(char));
    if (maPhim == NULL || gheNgoi == NULL) { 
        perror("Loi cap phat bo nho"); 
        exit(1); 
    }

    int gheINT;
    newVe->TrangThai = 1;
    inDanhSachPhim();
    PhimNode *tempPhim;
    do {
        printf("Nhap ma phim muon dat ve: ");
        scanf("%14s", maPhim);
        tempPhim = headPhim;
        while (tempPhim) {
            if (strcmp(tempPhim->MaPhim, maPhim) == 0) {
                strcpy(newVe->MaPhim, maPhim);
                break;
            }
            tempPhim = tempPhim->next;
        }
        if (!tempPhim) {
            printf("Ma phim khong ton tai!\n");
        } else {
            inSoDoGhe(headVe, maPhim);
            break;
        }
    } while (1);

    printf("Nguoi dat ve: %s\n", user);
    strcpy(newVe->TenNguoiDung, user);

    do {
        printf("Nhap ghe ngoi (VD: A1): ");
        scanf("%2s", gheNgoi);
        if (strlen(gheNgoi) != 2 || *gheNgoi < 'A' || *gheNgoi > 'E' || *(gheNgoi + 1) < '1' || *(gheNgoi + 1) > '8') {
            printf("Dinh dang sai.\n");
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
            newVe->GheNgoi[gheINT] = 1;
            newVe->next = headVe;
            headVe = newVe;
            ghiDanhSachVeVaoFile(headVe);
            printf("Dat ve thanh cong!\n");
            break;
        } else {
            printf("Ghe da duoc dat!\n");
        }
    } while (1);

    free(maPhim);
    free(gheNgoi);
}

void inVeDaDat(char *user) {
    VeNode *headVe = NULL;
    docVeTuFile(&headVe);
 
    printf("                                      DANH SACH VE DA DAT                              \n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("\n%-10s %-10s %-20s %-20s %-12s\n", "Ma Ve", "Ma Phim", "Ten Nguoi Dat", "Ghe Ngoi", "Trang Thai");
    printf("----------------------------------------------------------------------------------------\n");

    for (VeNode *temp = headVe; temp; temp = temp->next) {
        if (strcmp(temp->TenNguoiDung, user) == 0) {
            // In dòng đầu với các trường cơ bản
            printf("%-10s %-10s %-20s ", temp->MaVe, temp->MaPhim, temp->TenNguoiDung);

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

            printf("%24s\n", temp->TrangThai == 1 ? "Da dat" : "Da huy");
        }
    }

    printf("----------------------------------------------------------------------------------------\n");

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

    char *maVe = (char*)malloc(15 * sizeof(char));
    if (maVe == NULL) { 
        perror("Loi cap phat bo nho"); 
        exit(1); 
    }

    inVeDaDat(user);
    printf("Nhap ma ve muon huy: ");
    scanf("%14s", maVe);

    int found = 0;
    VeNode *temp = headVe;
    while (temp) {
        if (strcmp(temp->MaVe, maVe) == 0 && strcmp(temp->TenNguoiDung, user) == 0 && temp->TrangThai == 1) {
            printf("Ban chac chan muon huy ve: ");
            for (int i = 0; i < 40; i++) {
                if (temp->GheNgoi[i]) {
                    printf("%c%d ", 'A' + i / 8, i % 8 + 1);
                }
            }
            printf("?\nNhap 1 de xac nhan, 0 de huy thao tac: ");

            int xacNhan;
            scanf("%d", &xacNhan);
            if (xacNhan != 1) {
                printf("Da huy thao tac huy ve.\n");
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
            }
            ghiDanhSachVeVaoFile(headVe);
            printf("Huy ve thanh cong!\n");
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Ma ve khong ton tai, da bi huy, hoac khong phai cua ban!\n");
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

    printf("Nhap ten phim: ");
    getchar(); // Xoa bo nho dem
    fgets(newPhim->TenPhim, sizeof(newPhim->TenPhim), stdin);
    strtok(newPhim->TenPhim, "\n"); // Xoa ky tu newline
    printf("Nhap the loai: ");
    fgets(newPhim->TheLoai, sizeof(newPhim->TheLoai), stdin);
    strtok(newPhim->TheLoai, "\n");
    printf("Nhap ngay chieu (dd/mm/yyyy): ");
    scanf("%s", newPhim->NgayChieu);
    printf("Nhap gio chieu (hh:mm): ");
    scanf("%s", newPhim->GioChieu);
    printf("Nhap phong chieu: ");
    scanf("%s", newPhim->PhongChieu);
    printf("Nhap gia ve: ");
    scanf("%d", &newPhim->GiaVe);

    // Kiem tra trung lich (ngay + gio + phong)
    for (PhimNode *temp = headPhim; temp != NULL; temp = temp->next) {
        if (strcmp(temp->NgayChieu, newPhim->NgayChieu) == 0 &&
            strcmp(temp->GioChieu, newPhim->GioChieu) == 0 &&
            strcmp(temp->PhongChieu, newPhim->PhongChieu) == 0) {
            printf("Da co phim duoc chieu vao thoi diem nay trong phong nay!\n");
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

    fprintf(f, "%s|%s|%s|%s|%s|%s|%d\n",newPhim->MaPhim,newPhim->TenPhim,newPhim->TheLoai,newPhim->NgayChieu,newPhim->GioChieu,newPhim->PhongChieu,newPhim->GiaVe);

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
        printf("1. Sua ma phim\n");
        printf("2. Sua ten phim\n");
        printf("3. Sua the loai\n");
        printf("4. Sua ngay chieu\n");
        printf("5. Sua gio chieu\n");
        printf("6. Sua phong chieu\n");
        printf("7. Sua gia ve\n");
        printf("0. Thoat sua quay lai quan li phim\n");
        printf("----------------------------------------------------------\n");
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Nhap ma phim moi: ");
                scanf("%s", found->MaPhim);
                break;
            case 2:
                printf("Nhap ten phim moi: ");
                fgets(found->TenPhim, sizeof(found->TenPhim), stdin);
                strtok(found->TenPhim, "\n");
                break;
            case 3:
                printf("Nhap the loai moi: ");
                fgets(found->TheLoai, sizeof(found->TheLoai), stdin);
                strtok(found->TheLoai, "\n");
                break;
            case 4:
                printf("Nhap ngay chieu moi: ");
                scanf("%s", found->NgayChieu);
                break;
            case 5:
                printf("Nhap gio chieu moi: ");
                scanf("%s", found->GioChieu);
                break;
            case 6:
                printf("Nhap phong chieu moi: ");
                scanf("%s", found->PhongChieu);
                break;
            case 7:
                printf("Nhap gia ve moi: ");
                scanf("%d", &found->GiaVe);
                break;
            case 0:
                break;
            default:
                printf("Lua chon khong hop le!\n");
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
    printf("Nhap ma phim muon xoa: ");
    scanf("%s", maPhim);

    PhimNode *curr = headPhim, *prev = NULL;
    while (curr != NULL && strcmp(curr->MaPhim, maPhim) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        printf("Khong tim thay phim co ma: %s\n", maPhim);
        return;
    }

    printf("Ban co chac chan muon xoa phim sau khong?\n");
    printf("----------------------------------------------------------\n");
    inThongTinPhim(curr);
    printf("----------------------------------------------------------\n");
    printf("Nhap 1 de xoa, 0 de huy: ");
    int confirm;
    scanf("%d", &confirm);

    if (confirm != 1) {
        printf("Huy xoa phim.\n");
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
    printf("                                 DANH SACH VE DA DAT                                   \n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("%-10s %-10s %-20s %-10s %-12s %-10s\n", "Ma Ve", "Ma Phim", "Ten Nguoi Dat", "Ghe", "Trang Thai", "Ten phim");
    printf("----------------------------------------------------------------------------------------\n");

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

        printf("%-10s %-10s %-20s ", tempVe->MaVe, tempVe->MaPhim, tempVe->TenNguoiDung);

        int demGhe = 0;
        for (int i = 0; i < 40; i++) {
            if (tempVe->GheNgoi[i]) {
                printf("%c%d ", 'A' + i / 8, i % 8 + 1);
                demGhe++;
            }
        }
        if (demGhe == 0) {
            printf("XX ");
        }
		printf("%s", "        ");
        printf("%-12s %-35s\n", tempVe->TrangThai == 1 ? "Da dat" : "Da huy", tenPhim);


        for (tempPhim = headPhim; tempPhim; tempPhim = tempPhim->next) {
            if (strcmp(tempPhim->MaPhim, tempVe->MaPhim) == 0) {
                soLuongVe[atoi(tempVe->MaPhim + 2)]++;
                break;
            }
        }
    }
//    printf("----------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("\n\n                                SO LUONG VE DA DAT THEO PHIM                             \n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-15s %-35s %-10s\n", "Ma Phim", "Ten Phim", "So Luong Ve");
    printf("-----------------------------------------------------------------------------------------\n");
    for (PhimNode *tempPhim = headPhim; tempPhim; tempPhim = tempPhim->next) {
        int index = atoi(tempPhim->MaPhim + 2);
        printf("%-15s %-35s %-10d\n", tempPhim->MaPhim, tempPhim->TenPhim, soLuongVe[index]);
    }
	printf("-----------------------------------------------------------------------------------------\n");
    
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

    printf("                                 THONG KE DOANH THU                                     \n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("%-15s %-35s %-10s\n", "Ma Phim", "Ten Phim", "Doanh Thu");
    printf("----------------------------------------------------------------------------------------\n");

    for (PhimNode *tempPhim = headPhim; tempPhim; tempPhim = tempPhim->next) {
        int doanhThu = 0;
        for (VeNode *tempVe = headVe; tempVe; tempVe = tempVe->next) {
            if (strcmp(tempPhim->MaPhim, tempVe->MaPhim) == 0 && tempVe->TrangThai == 1) {
                doanhThu += tempPhim->GiaVe;
            }
        }
        printf("%-15s %-35s %-10d\n", tempPhim->MaPhim, tempPhim->TenPhim, doanhThu);
    }
    printf("----------------------------------------------------------------------------------------\n");

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
// Ham ghi danh sach nguoi dung vao file nguoidung.txt
void ghiDanhSachNguoiDungVaoFile(NguoiDungNode *head) {
    FILE *f = fopen("nguoidung.txt", "w");
    if (!f) {
        perror("Loi mo file nguoidung.txt de ghi");
        return;
    }

    NguoiDungNode *current = head;
    while (current) {
        // WARNING: Writing password to file. Consider hashing in a real application.
        fprintf(f, "%s|%s|%d\n", current->username, current->password, current->type);
        current = current->next;
    }
    fclose(f);
}

// Ham in danh sach tat ca nguoi dung
void inDanhSachNguoiDung(void) {
    NguoiDungNode *head = NULL;
    docTaiKhoanTuFile(&head);

    printf("                                 DANH SACH NGUOI DUNG                                  \n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("%-20s %-10s\n", "Ten Dang Nhap", "Loai Tai Khoan");
    printf("----------------------------------------------------------------------------------------\n");

    NguoiDungNode *current = head;
    while (current != NULL) {
        // Do not display passwords directly
        printf("%-20s %-10s\n", current->username, current->type == 1 ? "Admin" : "User");
        current = current->next;
    }
    printf("----------------------------------------------------------------------------------------\n");

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

    char usernameToDelete[15];
    printf("\nNhap ten dang nhap cua nguoi dung muon xoa: ");
    scanf("%14s", usernameToDelete);

    if (strcmp(usernameToDelete, adminUser) == 0) {
        printf("Ban khong the xoa tai khoan admin dang su dung!\n");
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

    printf("Ban co chac chan muon xoa tai khoan cua nguoi dung '%s' khong?\n", usernameToDelete);
    printf("Nhap 1 de xac nhan, 0 de huy: ");
    int confirm;
    scanf("%d", &confirm);

    if (confirm != 1) {
        printf("Huy xoa tai khoan.\n");
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
    }}
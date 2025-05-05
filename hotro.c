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

// Ham ghi danh sach phim vao file phim.txt
void ghiDanhSachPhimVaoFile(PhimNode *head) {
    FILE *f = fopen("phim.txt", "w");
    if (!f) { perror("Loi file"); exit(1); }

    PhimNode *current = head;
    while (current) {
        fprintf(f, "%s|%s|%s|%s|%s|%s|%d\n", current->MaPhim, current->TenPhim, current->TheLoai, current->NgayChieu, current->GioChieu, current->PhongChieu, current->GiaVe);
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


// Ham huy ve da dat
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

// ham them phim vao danh sach phim
void themPhim(void) {
    PhimNode *headPhim = NULL;
    docPhimTuFile(&headPhim);

    PhimNode *newPhim = (PhimNode*)malloc(sizeof(PhimNode));
    if (newPhim == NULL) { 
        perror("Loi cap phat bo nho"); 
        exit(1); 
    }

    do {
        printf("Nhap ma phim: ");
        fgets(newPhim->MaPhim, sizeof(newPhim->MaPhim), stdin);
        newPhim->MaPhim[strcspn(newPhim->MaPhim, "\n")] = 0;

        int exists = 0;
        for (PhimNode *temp = headPhim; temp; temp = temp->next) {
            if (strcmp(temp->MaPhim, newPhim->MaPhim) == 0) {
                exists = 1;
                break;
            }
        }
        if (exists) {
            printf("Ma phim da ton tai! Vui long nhap ma phim khac.\n");
        } else {
            break;
        }
    } while (1);

    printf("Nhap ten phim: ");
    fgets(newPhim->TenPhim, sizeof(newPhim->TenPhim), stdin);
    newPhim->TenPhim[strcspn(newPhim->TenPhim, "\n")] = 0;

    printf("Nhap the loai: ");
    fgets(newPhim->TheLoai, sizeof(newPhim->TheLoai), stdin);
    newPhim->TheLoai[strcspn(newPhim->TheLoai, "\n")] = 0;

    printf("Nhap ngay chieu (dd/mm/yyyy): ");
    fgets(newPhim->NgayChieu, sizeof(newPhim->NgayChieu), stdin);
    newPhim->NgayChieu[strcspn(newPhim->NgayChieu, "\n")] = 0;

    printf("Nhap gio chieu (hh:mm): ");
    fgets(newPhim->GioChieu, sizeof(newPhim->GioChieu), stdin);
    newPhim->GioChieu[strcspn(newPhim->GioChieu, "\n")] = 0;

    do {
        printf("Nhap phong chieu: ");
        fgets(newPhim->PhongChieu, sizeof(newPhim->PhongChieu), stdin);
        newPhim->PhongChieu[strcspn(newPhim->PhongChieu, "\n")] = 0;

        int trungLich = 0;
        for (PhimNode *temp = headPhim; temp; temp = temp->next) {
            if (
                strcmp(temp->NgayChieu, newPhim->NgayChieu) == 0 &&
                strcmp(temp->GioChieu, newPhim->GioChieu) == 0 &&
                strcmp(temp->PhongChieu, newPhim->PhongChieu) == 0
            ) {
                trungLich = 1;
                break;
            }
        }

        if (trungLich) {
            printf("Phong da duoc dat cho suat chieu nay! Vui long chon phong hoac gio khac.\n");
        } else {
            break;
        }
    } while (1);

    printf("Nhap gia ve: ");
    scanf("%d", &newPhim->GiaVe);
    while (getchar() != '\n'); // Xóa newline trong bộ đệm

    newPhim->next = headPhim;
    headPhim = newPhim;

    ghiDanhSachPhimVaoFile(headPhim);
    printf("Them phim thanh cong!\n");
}

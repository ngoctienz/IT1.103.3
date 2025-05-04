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

void datVe(void) {
    PhimNode *headPhim = NULL;
    VeNode *headVe = NULL;
    docPhimTuFile(&headPhim);
    docVeTuFile(&headVe);

    VeNode *newVe = (VeNode*)malloc(sizeof(VeNode));
    if (!newVe) { perror("Loi cap phat bo nho"); exit(1); }
    taoMaVe(newVe->MaVe);

    char maPhim[15], tenNguoiDung[15], gheNgoi[3];
    int gheINT;
    newVe->TrangThai = 1;

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

    printf("Nhap ten nguoi dat ve: ");
    scanf("%14s", tenNguoiDung);
    strcpy(newVe->TenNguoiDung, tenNguoiDung);

    do {
        printf("Nhap ghe ngoi (VD: A1): ");
        scanf("%2s", gheNgoi);
        if (strlen(gheNgoi) != 2 || gheNgoi[0] < 'A' || gheNgoi[0] > 'E' || gheNgoi[1] < '1' || gheNgoi[1] > '8') {
            printf("Dinh dang sai.\n");
            continue;
        }
        gheINT = (gheNgoi[0] - 'A') * 8 + (gheNgoi[1] - '1');
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
}


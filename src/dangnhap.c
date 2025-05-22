#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h> // Thu vien cho getch()
#include "dangnhap.h"
#include "hotro.h"

// Ham doc file user
int docTaiKhoan(char *tenDangNhap, char *matKhau) {
    FILE *tepTin;
    char *tenDangNhapTam = (char*)malloc(15 * sizeof(char));
    char *matKhauTam = (char*)malloc(15 * sizeof(char));
    int loaiNguoiDung;
    tepTin = fopen("nguoidung.txt", "r");
    if (tepTin == NULL) {
        perror("Loi file: ");
        exit(1);
    }
    // Doc tung dong trong file va so sanh voi thong tin nhap vao
    while (fscanf(tepTin, "%[^|]|%[^|]|%d\n", tenDangNhapTam, matKhauTam, &loaiNguoiDung) == 3) {
        if ((strcmp(tenDangNhap, tenDangNhapTam) == 0) && (strcmp(matKhau, matKhauTam) == 0)) {
            fclose(tepTin);
            return loaiNguoiDung; // Dung tai khoan thi tra ve luon
        }
    }
    fclose(tepTin);
    return 0;
}

// Ham dang nhap
int dangNhap(char *tenDangNhap) {
    char *matKhau = (char*)malloc(15 * sizeof(char));
    if (matKhau == NULL) {
        perror("Loi cap phat bo nho cho mat khau: ");
        // Tra ve -1 neu cap phat loi
        return -1;
    }
    int kyTu; // Bien de doc ky tu tu input
    int loaiNguoiDung = 0; // Luu loai nguoi dung (0: khong tim thay/sai, 1: admin, 2: user)
    xoaMH();
    printf(BOLD CYAN "===== HE THONG DANG NHAP =====\n" RESET_COLOR);
    do {
        printf(YELLOW "Nhap ten dang nhap: " RESET_COLOR);
        scanf("%s", tenDangNhap);
        // Xoa bo dem nhap
        while ((kyTu = getchar()) != '\n' && kyTu != EOF);
        printf(YELLOW "Nhap mat khau: " RESET_COLOR);
        // Bat dau nhap mat khau an (hien thi ***)
        int i = 0; // Chi so cho mang matKhau
        char kyTuNhap; // Bien tam de doc tung ky tu
        while ((kyTuNhap = getch()) != '\r' && kyTuNhap != '\n' && i < 14) {
            // getch() doc mot ky tu ma khong hien thi len man hinh
            if (kyTuNhap != 8 && kyTuNhap != 127) {
                // Neu la ky tu thong thuong, luu vao mang matKhau
                matKhau[i] = kyTuNhap;
                i++; // Tang chi so
                printf("*"); // In ky tu '*' ra man hinh
            } else if (i > 0) {
                i--; // Giam chi so
                // Xoa ky tu '*' cuoi cung tren man hinh
                printf("\b \b");
            }
        }
        matKhau[i] = '\0'; // Them ky tu null ket thuc chuoi vao cuoi mat khau
        printf("\n");
        // Ket thuc nhap mat khau an
        // Tra ve loai tai khoan (1: admin, 2: user) hoac 0 neu khong dung
        loaiNguoiDung = docTaiKhoan(tenDangNhap, matKhau);

        if (loaiNguoiDung == 0) { // Dang nhap that bai
            xoaMH();
            printf(RED BOLD "Ten dang nhap hoac mat khau khong dung!\n" RESET_COLOR);
            printf(YELLOW "Nhan Enter de nhap lai hoac nhap 0 de quay lai menu chinh: " RESET_COLOR);

            char luaChonTam[10]; // Buffer tam de doc lua chon
            fgets(luaChonTam, sizeof(luaChonTam), stdin); // Dung fgets an toan hon scanf cho chuoi

            // So sanh lua chon voi "0\n" hoac "0\r\n"
            if (strcmp(luaChonTam, "0\n") == 0 || strcmp(luaChonTam, "0\r\n") == 0) {
                free(matKhau);
                tenDangNhap[0] = '\0'; // Dat ky tu null vao dau chuoi user de lam rong
                return 0; // Quay lai menu chinh
            }
            // Neu nhan Enter (khong nhap 0), tiep tuc vong lap
            xoaMH();
            printf(BOLD CYAN "===== HE THONG DANG NHAP =====\n" RESET_COLOR);
        } else { // Dang nhap thanh cong
            printf(GREEN BOLD "Dang nhap thanh cong!\n" RESET_COLOR);
            // Thong bao chuyen den menu chinh
            stop(2, loaiNguoiDung == 1 ? "Menu Admin" : "Menu Nguoi dung");
            free(matKhau);
            return loaiNguoiDung; // Tra ve loai nguoi dung (1 hoac 2)
        }
    } while (loaiNguoiDung == 0); // Lap lai neu dang nhap that bai
    free(matKhau);
    return 0;
}

// Ham dang ky
int dangKy(char *tenDangNhap) {
    FILE *tepTin;
    char *matKhau = (char*)malloc(50 * sizeof(char)); // Tang kich thuoc de phu hop voi NguoiDungNode
    char *xacNhanMatKhau = (char*)malloc(50 * sizeof(char)); // Bien cho mat khau xac nhan
    char kyTu;
    NguoiDungNode *dau = NULL, *tam = NULL, *nutMoi = NULL;
    int tonTai = 0; // Kiem tra ten dang nhap co ton tai khong
    int khopMatKhau = 0; // Kiem tra mat khau co khop khong

    if (matKhau == NULL || xacNhanMatKhau == NULL) {
        perror("Loi cap phat bo nho: ");
        free(matKhau);
        free(xacNhanMatKhau);
        return -1;
    }

    docTaiKhoanTuFile(&dau);
    xoaMH();
    do {
        printf(YELLOW"Nhap ten dang nhap: "RESET_COLOR);
        scanf("%49s", tenDangNhap); // Gioi han doc de tranh tran bo dem
        // Xoa bo dem nhap
        while ((kyTu = getchar()) != '\n' && kyTu != EOF);

        tonTai = 0;
        // Kiem tra ten dang nhap da ton tai chua
        for (tam = dau; tam != NULL; tam = tam->next) {
            if (strcmp(tenDangNhap, tam->username) == 0) {
                tonTai = 1;
                break;
            }
        }

        if (tonTai == 1) {
            xoaMH();
            printf(RED"Ten dang nhap da ton tai! Vui long chon ten khac.\n"RESET_COLOR);
        } else {
            // Vong lap nhap va xac nhan mat khau
            do {
                printf(YELLOW"Nhap mat khau: "RESET_COLOR);
                scanf("%49s", matKhau);
                while ((kyTu = getchar()) != '\n' && kyTu != EOF);

                printf(YELLOW"Nhap lai mat khau de xac nhan: "RESET_COLOR);
                scanf("%49s", xacNhanMatKhau);
                while ((kyTu = getchar()) != '\n' && kyTu != EOF);

                if (strcmp(matKhau, xacNhanMatKhau) == 0) {
                    khopMatKhau = 1; // Mat khau khop
                } else {
                    xoaMH();
                    printf(RED"Mat khau khong khop! Vui long nhap lai.\n"RESET_COLOR);
                    khopMatKhau = 0; // Mat khau khong khop, tiep tuc lap
                }
            } while (khopMatKhau == 0);

            nutMoi = (NguoiDungNode*)malloc(sizeof(NguoiDungNode));
            if (nutMoi == NULL) {
                perror("Loi cap phat bo nho cho nutMoi: ");
                free(matKhau);
                free(xacNhanMatKhau);
                // Giai phong danh sach lien ket neu co
                NguoiDungNode *hienTai = dau;
                NguoiDungNode *nutTiep;
                while (hienTai != NULL) {
                    nutTiep = hienTai->next;
                    free(hienTai);
                    hienTai = nutTiep;
                }
                return -1;
            }

            // Sao chep ten dang nhap va mat khau vao nut moi
            strncpy(nutMoi->username, tenDangNhap, sizeof(nutMoi->username) - 1);
            nutMoi->username[sizeof(nutMoi->username) - 1] = '\0';

            strncpy(nutMoi->password, matKhau, sizeof(nutMoi->password) - 1);
            nutMoi->password[sizeof(nutMoi->password) - 1] = '\0';

            nutMoi->type = 2; // User
            nutMoi->next = dau;
            dau = nutMoi;

            tepTin = fopen("nguoidung.txt", "a");
            if (tepTin != NULL) {
                fprintf(tepTin, "%s|%s|%d\n", tenDangNhap, matKhau, 2);
                fclose(tepTin);
                xoaMH();
                printf("Dang ky thanh cong!\nVui long dang nhap lai!\n");
                tonTai = 0; // Thoat vong lap chinh
            } else {
                perror("Loi mo file de ghi: ");
                free(nutMoi);
                tonTai = 1; // Lap lai quy trinh dang ky
            }
        }
    } while (tonTai == 1);

    // Giai phong danh sach lien ket
    NguoiDungNode *hienTai = dau;
    NguoiDungNode *nutTiep;
    while (hienTai != NULL) {
        nutTiep = hienTai->next;
        free(hienTai);
        hienTai = nutTiep;
    }

    // Giai phong bo nho da cap phat cho matKhau va xacNhanMatKhau
    free(matKhau);
    free(xacNhanMatKhau);
    return 0;
}

// Ham them tai khoan admin
void themTaiKhoanAdmin(void) {
    FILE *tepTin;
    char *tenDangNhap = (char*)malloc(50 * sizeof(char));
    char *matKhau = (char*)malloc(50 * sizeof(char));
    char *xacNhanMatKhau = (char*)malloc(50 * sizeof(char));
    char kyTu;
    NguoiDungNode *dau = NULL, *tam = NULL, *nutMoi = NULL;
    int tonTai = 0;
    int khopMatKhau = 0;

    if (matKhau == NULL || xacNhanMatKhau == NULL) {
        perror("Loi cap phat bo nho: ");
        free(matKhau);
        free(xacNhanMatKhau);
        exit(1);
    }

    docTaiKhoanTuFile(&dau);
    xoaMH();
    do {
        printf(YELLOW"Nhap ten Admin: "RESET_COLOR);
        scanf("%49s", tenDangNhap);
        while ((kyTu = getchar()) != '\n' && kyTu != EOF);

        tonTai = 0;
        // Kiem tra ten admin da ton tai chua
        for (tam = dau; tam != NULL; tam = tam->next) {
            if (strcmp(tenDangNhap, tam->username) == 0) {
                tonTai = 1;
                break;
            }
        }

        if (tonTai == 1) {
            xoaMH();
            printf(RED"Ten Admin da ton tai! Vui long chon ten khac.\n"RESET_COLOR);
        } else {
            // Vong lap nhap va xac nhan mat khau
            do {
                printf(YELLOW"Nhap mat khau: "RESET_COLOR);
                scanf("%49s", matKhau);
                while ((kyTu = getchar()) != '\n' && kyTu != EOF);

                printf(YELLOW"Nhap lai mat khau de xac nhan: "RESET_COLOR);
                scanf("%49s", xacNhanMatKhau);
                while ((kyTu = getchar()) != '\n' && kyTu != EOF);

                if (strcmp(matKhau, xacNhanMatKhau) == 0) {
                    khopMatKhau = 1;
                } else {
                    xoaMH();
                    printf(RED"Mat khau khong khop! Vui long nhap lai.\n"RESET_COLOR);
                    khopMatKhau = 0;
                }
            } while (khopMatKhau == 0);

            nutMoi = (NguoiDungNode*)malloc(sizeof(NguoiDungNode));
            if (nutMoi == NULL) {
                perror("Loi cap phat bo nho cho nutMoi: ");
                free(matKhau);
                free(xacNhanMatKhau);
                // Giai phong danh sach lien ket neu co
                NguoiDungNode *hienTai = dau;
                NguoiDungNode *nutTiep;
                while (hienTai != NULL) {
                    nutTiep = hienTai->next;
                    free(hienTai);
                    hienTai = nutTiep;
                }
            }

            // Sao chep ten dang nhap va mat khau vao nut moi
            strncpy(nutMoi->username, tenDangNhap, sizeof(nutMoi->username) - 1);
            nutMoi->username[sizeof(nutMoi->username) - 1] = '\0';

            strncpy(nutMoi->password, matKhau, sizeof(nutMoi->password) - 1);
            nutMoi->password[sizeof(nutMoi->password) - 1] = '\0';

            nutMoi->type = 1; // Admin
            nutMoi->next = dau;
            dau = nutMoi;

            tepTin = fopen("nguoidung.txt", "a");
            if (tepTin != NULL) {
                fprintf(tepTin, "%s|%s|%d\n", tenDangNhap, matKhau, 1);
                fclose(tepTin);
                xoaMH();
                printf("Dang ky thanh cong!\nVui long dang nhap lai!\n");
                tonTai = 0;
            } else {
                perror("Loi mo file de ghi: ");
                free(nutMoi);
                tonTai = 1;
            }
        }
    } while (tonTai == 1);

    // Giai phong danh sach lien ket
    NguoiDungNode *hienTai = dau;
    NguoiDungNode *nutTiep;
    while (hienTai != NULL) {
        nutTiep = hienTai->next;
        free(hienTai);
        hienTai = nutTiep;
    }

    // Giai phong bo nho da cap phat cho matKhau va xacNhanMatKhau
    free(matKhau);
    free(xacNhanMatKhau);
}

// Ham doi mat khau
void doiMatKhau(char *tenDangNhap) {
    FILE *tepTin;
    char *matKhauCu = (char*)malloc(50 * sizeof(char));
    char *matKhauMoi = (char*)malloc(50 * sizeof(char));
    char *xacNhanMatKhau = (char*)malloc(50 * sizeof(char));
    char kyTu;
    NguoiDungNode *dau = NULL, *tam = NULL, *nutMoi = NULL;
    int dungMatKhauCu = 0;
    int khopMatKhau = 0;

    if (matKhauCu == NULL || matKhauMoi == NULL || xacNhanMatKhau == NULL) {
        perror("Loi cap phat bo nho: ");
        free(matKhauCu);
        free(matKhauMoi);
        free(xacNhanMatKhau);
        exit(1);
    }

    docTaiKhoanTuFile(&dau);
    xoaMH();
    do {
        printf(YELLOW"Nhap mat khau cu: "RESET_COLOR);
        scanf("%49s", matKhauCu);
        while ((kyTu = getchar()) != '\n' && kyTu != EOF);

        dungMatKhauCu = 0;
        // Kiem tra mat khau cu co dung khong
        for (tam = dau; tam != NULL; tam = tam->next) {
            if ((strcmp(tenDangNhap, tam->username) == 0) && (strcmp(matKhauCu, tam->password) == 0)) {
                dungMatKhauCu = 1;
                break;
            }
        }

        if (dungMatKhauCu == 0) {
            xoaMH();
            printf(RED"Mat khau cu khong dung! Vui long chon mat khau khac.\n"RESET_COLOR);
        } else {
            // Vong lap nhap va xac nhan mat khau moi
            do {
                printf(YELLOW"Nhap mat khau moi: "RESET_COLOR);
                scanf("%49s", matKhauMoi);
                while ((kyTu = getchar()) != '\n' && kyTu != EOF);

                printf(YELLOW"Nhap lai mat khau moi de xac nhan: "RESET_COLOR);
                scanf("%49s", xacNhanMatKhau);
                while ((kyTu = getchar()) != '\n' && kyTu != EOF);
                if (strcmp(matKhauMoi, xacNhanMatKhau) == 0) {
                    khopMatKhau = 1;
                } else {
                    xoaMH();
                    printf(RED"Mat khau khong khop! Vui long nhap lai.\n"RESET_COLOR);
                    khopMatKhau = 0;
                }
            } while (khopMatKhau == 0);

            // Tim nut can cap nhat mat khau
            for (tam = dau; tam != NULL; tam = tam->next) {
                if (strcmp(tenDangNhap, tam->username) == 0) {
                    break;
                }
            }
            if (tam != NULL) {
                // Cap nhat mat khau
                strncpy(tam->password, matKhauMoi, sizeof(tam->password) - 1);
                tam->password[sizeof(tam->password) - 1] = '\0';
            }
            tepTin = fopen("nguoidung.txt", "w");
            if (tepTin != NULL) {
                // Ghi lai danh sach nguoi dung vao file
                for (tam = dau; tam != NULL; tam = tam->next) {
                    fprintf(tepTin, "%s|%s|%d\n", tam->username, tam->password, tam->type);
                }
                fclose(tepTin);
                xoaMH();
                printf("Doi mat khau thanh cong!\n");
                dungMatKhauCu = 0;
            } else {
                perror("Loi mo file de ghi: ");
                free(nutMoi);
                dungMatKhauCu = 1;
            }
        }
    } while (dungMatKhauCu == 1);

    // Giai phong danh sach lien ket
    NguoiDungNode *hienTai = dau;
    NguoiDungNode *nutTiep;
    while (hienTai != NULL) {
        nutTiep = hienTai->next;
        free(hienTai);
        hienTai = nutTiep;
    }
    // Giai phong bo nho da cap phat cho matKhauCu, matKhauMoi va xacNhanMatKhau
    free(matKhauCu);
    free(matKhauMoi);
    free(xacNhanMatKhau);
}

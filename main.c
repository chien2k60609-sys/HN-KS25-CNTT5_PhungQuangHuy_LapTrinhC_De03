#include <stdio.h>
#include <string.h>
#define MAX_SACH 50

typedef struct {
    char ma[20];
    char ten[100];
    int soLuong;
    long giaBan;
} DauSach;

void xoaEnter(char s[]) {
    s[strcspn(s, "\n")] = '\0';
}

void nhapChuoi(const char *thongBao, char s[], int n) {
    printf("%s", thongBao);
    fgets(s, n, stdin);
    xoaEnter(s);
}

int nhapSoNguyen(const char *thongBao) {
    char s[100];
    int x;
    char them;
    while (1) {
        printf("%s", thongBao);
        fgets(s, sizeof(s), stdin);
        if (sscanf(s, "%d %c", &x, &them) == 1)
            return x;
        printf("Du lieu khong hop le\n");
    }
}

long nhapGiaBan(const char *thongBao) {
    char s[100];
    long x;
    char them;
    while (1) {
        printf("%s", thongBao);
        fgets(s, sizeof(s), stdin);
        if (sscanf(s, "%ld %c", &x, &them) == 1 && x > 0)
            return x;
        printf("Gia ban phai lon hon 0\n");
    }
}

int timTheoMa(DauSach ds[], int soLuong, char ma[]) {
    int i;
    for (i = 0; i < soLuong; i++) {
        if (strcmp(ds[i].ma, ma) == 0)
            return i;
    }
    return -1;
}

void inTieuDe(void) {
    printf("\n%-10s %-15s %-10s %-10s %-10s\n",
           "Ma", "Ten dau sach", "So luong", "Gia ban", "Thanh tien");
    printf("-----------------------------------------------------------\n");
}

void inMotDauSach(DauSach s) {
    long thanhTien = (long)s.soLuong * s.giaBan;
    printf("%-10s %-15s %-10d %-10ld %-10ld\n",s.ma, s.ten, s.soLuong, s.giaBan, thanhTien);
}

void themDauSach(DauSach ds[], int *soLuong) {
    DauSach s;
    if (*soLuong == MAX_SACH) {
        printf("Danh sach da day\n");
        return;
    }
    nhapChuoi("Nhap ma: ", s.ma, sizeof(s.ma));
    if (timTheoMa(ds, *soLuong, s.ma) != -1) {
        printf("Ma dau sach da ton tai\n");
        return;
    }
    nhapChuoi("Nhap ten: ", s.ten, sizeof(s.ten));
    do {
        s.soLuong = nhapSoNguyen("Nhap so luong: ");
        if (s.soLuong < 0)
            printf("So luong khong hop le\n");
    } while (s.soLuong < 0);
    s.giaBan = nhapGiaBan("Nhap gia ban: ");
    ds[*soLuong] = s;
    (*soLuong)++;
    printf("Them dau sach thanh cong\n");
}

void hienThiDanhSach(DauSach ds[], int soLuong) {
    int i;
    if (soLuong == 0) {
        printf("Danh sach rong\n");
        return;
    }
    inTieuDe();
    for (i = 0; i < soLuong; i++)
        inMotDauSach(ds[i]);
}

void capNhatDauSach(DauSach ds[], int soLuong) {
    char ma[20];
    int viTri;
    if (soLuong == 0) {
        printf("Danh sach rong\n");
        return;
    }
    nhapChuoi("Nhap ma can sua: ", ma, sizeof(ma));
    viTri = timTheoMa(ds, soLuong, ma);
    if (viTri == -1) {
        printf("Khong tim thay dau sach\n");
        return;
    }
    nhapChuoi("Nhap ten moi: ", ds[viTri].ten, sizeof(ds[viTri].ten));
    do {
        ds[viTri].soLuong = nhapSoNguyen("Nhap so luong moi: ");
        if (ds[viTri].soLuong < 0)
            printf("So luong khong hop le\n");
    } while (ds[viTri].soLuong < 0);
    ds[viTri].giaBan = nhapGiaBan("Nhap gia ban moi: ");
    printf("Cap nhat thanh cong\n");
}

void xoaDauSach(DauSach ds[], int *soLuong) {
    char ma[20];
    int viTri, i;
    if (*soLuong == 0) {
        printf("Danh sach rong\n");
        return;
    }
    nhapChuoi("Nhap ma can xoa: ", ma, sizeof(ma));
    viTri = timTheoMa(ds, *soLuong, ma);
    if (viTri == -1) {
        printf("Khong tim thay dau sach\n");
        return;
    }
    for (i = viTri; i < *soLuong - 1; i++)
        ds[i] = ds[i + 1];
    (*soLuong)--;
    printf("Xoa thanh cong\n");
}

void timTheoTen(DauSach ds[], int soLuong) {
    char ten[100];
    int i, timThay = 0;
    nhapChuoi("Nhap ten can tim: ", ten, sizeof(ten));
    for (i = 0; i < soLuong; i++) {
        if (strcmp(ds[i].ten, ten) == 0) {
            if (timThay == 0)
                inTieuDe();
            inMotDauSach(ds[i]);
            timThay = 1;
        }
    }
    if (timThay == 0)
        printf("Khong tim thay dau sach\n");
}

void thongKeKhoHang(DauSach ds[], int soLuong) {
    int i, demSapHet = 0, viTriMax = 0;
    long tongGiaTri = 0;
    long thanhTienMax;
    if (soLuong == 0) {
        printf("Danh sach rong\n");
        return;
    }
    for (i = 0; i < soLuong; i++) {
        long thanhTien = (long)ds[i].soLuong * ds[i].giaBan;
        tongGiaTri += thanhTien;
        if (ds[i].soLuong < 5)
            demSapHet++;
        if (thanhTien > (long)ds[viTriMax].soLuong * ds[viTriMax].giaBan)
            viTriMax = i;
    }
    printf("Tong gia tri kho: %ld\n", tongGiaTri);
    printf("So dau sach sap het hang: %d\n", demSapHet);
    for (i = 0; i < soLuong; i++) {
        if (ds[i].soLuong < 5)
            inMotDauSach(ds[i]);
    }
    thanhTienMax = (long)ds[viTriMax].soLuong * ds[viTriMax].giaBan;
    printf("\nDau sach co thanh tien lon nhat (%ld):\n", thanhTienMax);
    inTieuDe();
    inMotDauSach(ds[viTriMax]);
}

void hienThiMenu(void) {
    printf("\n===== QUAN LY DAU SACH =====\n");
    printf("1. Them dau sach\n");
    printf("2. Hien thi danh sach dau sach\n");
    printf("3. Cap nhat dau sach theo ma\n");
    printf("4. Xoa dau sach theo ma\n");
    printf("5. Tim dau sach theo ten\n");
    printf("6. Thong ke kho hang\n");
    printf("0. Thoat\n");
}

int main(void) {
    DauSach ds[MAX_SACH];
    int soLuong = 0;
    int chon;
    do {
        hienThiMenu();
        chon = nhapSoNguyen("Chon chuc nang: ");
        switch (chon) {
            case 1:
                themDauSach(ds, &soLuong);
                break;
            case 2:
                hienThiDanhSach(ds, soLuong);
                break;
            case 3:
                capNhatDauSach(ds, soLuong);
                break;
            case 4:
                xoaDauSach(ds, &soLuong);
                break;
            case 5:
                timTheoTen(ds, soLuong);
                break;
            case 6:
                thongKeKhoHang(ds, soLuong);
                break;
            case 0:
                printf("Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
        }
    } while (chon != 0);
    return 0;
}

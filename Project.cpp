#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Material {
    char matId[10];
    char name[50];
    char unit[10];
    int qty;
    int status;
};

struct Transaction{
	char transId[20];
	char matId[10];
	char type[5];
	char date[15];
}; 

struct Material initList[13]= {
	    {"01", "Nuoc loc dong chai", "Chai", 20, 1},
	    {"02", "Sprite", "Chai", 30, 1},
	    {"03", "CoCa CoLa", "Lon", 50, 1},
	    {"04", "Snack", "Goi", 200, 0},
	    {"05", "Mirinda", "Lon", 10, 0},
	    {"06", "7UP", "Chai", 36, 1},
	    {"07", "SnacK khoai tay man", "Thung", 20, 0},
	    {"08", "SnacK khoai tay cay", "Bich", 80, 1},
	    {"09", "Keo mut", "Cay", 40, 1},
	    {"10", "Keo vien", "Cai", 40, 1},
	    {"11", "Sung do choi", "Cay", 40, 0},
	    {"12", "Bo lego xep hinh", "Hop", 30, 1},
	    {"13", "Set do choi oto", "Hop", 10, 1},
	};

int isNumber(char *s) {
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] < '0' || s[i] > '9') return 0;
    return 1;
}

int isEmpty(char *str) {
    if (str == NULL) return 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) return 0;
    }
    return 1;
}

int existId(struct Material *arr, int length, char *id) {
    for (int i = 0; i < length; i++)
        if (strcmp(arr[i].matId, id) == 0) return 1;
    return 0;
}

void deleteCharactor(char *string, int index){
	int length = strlen(string);
	for (int i = index ; i< length - 1;i++){
		string [i] = string[i+1];
	}
	string [length-1] = '\0';
}

void removeSpaces(char *str) {
    int len = strlen(str);
    int start = 0;
    if (len == 0) {
        str[0] = '\0';
        return;
    }
    while (start < len && isspace((unsigned char)str[start])) start++;
    if (start == len) {
        str[0] = '\0';
        return;
    }

    int end = len - 1;
    while (end >= start && isspace((unsigned char)str[end])) end--;
    int j = 0;
    for (int i = start; i <= end; i++) {
        str[j++] = str[i];
    }
    str[j] = '\0';
}

void strToLower(char *s) {
    for (int i = 0; s[i]; i++) {
        s[i] = tolower(s[i]);
    }
}

void inputMatIdStrict(char *matId, struct Material *arr, int length, int checkExist) {
    while (1) {
        fgets(matId, 10, stdin);
        matId[strcspn(matId, "\n")] = '\0';
        if (strlen(matId) == 0) { 
		printf("Ma vat tu khong duoc rong!\n");
		printf("Nhap ma vat tu: ");
		continue; }
        if (!isNumber(matId)) { 
		printf("Ma vat tu chi duoc nhap so!\n");
		printf("Nhap ma vat tu: ");
		continue; }
        if (checkExist && existId(arr, length, matId)) { 
		printf("Ma vat tu da ton tai!\n");
		printf("Nhap ma vat tu: ");
		continue; }
        break;
    }
}

void addMat(struct Material *arr, int *length) {
    int n;
    char tmp[20];
    while (1) {
        printf("Nhap so luong loai vat tu muon them: ");
        fgets(tmp, sizeof(tmp), stdin);
        tmp[strcspn(tmp, "\n")] = '\0';
        if (strlen(tmp) == 0) { 
            printf("So luong khong duoc rong!\n"); 
            continue; 
        }
        if (!isNumber(tmp)) { 
            printf("So luong chi duoc nhap so!\n"); 
            continue; 
        }
        n = atoi(tmp);
        if (n <= 0) { 
            printf("So luong phai > 0!\n"); 
            continue; 
        }
        break;
    }
    for (int k = 0; k < n; k++) {
        struct Material mat;
        printf("\n--- Nhap thong tin vat tu thu %d ---\n", *length + 1);
        printf("Nhap ma vat tu: ");
        inputMatIdStrict(mat.matId, arr, *length, 1);
        do {
            printf("Nhap ten vat tu: ");
            fgets(mat.name, sizeof(mat.name), stdin);
            mat.name[strcspn(mat.name, "\n")] = '\0';
            removeSpaces(mat.name);
            if (isEmpty(mat.name)) {
                printf("Ten vat tu khong duoc rong!\n"); 
            }
        } while (isEmpty(mat.name));
        do {
            printf("Nhap don vi tinh: ");
            fgets(mat.unit, sizeof(mat.unit), stdin);
            mat.unit[strcspn(mat.unit, "\n")] = '\0';
            removeSpaces(mat.unit);
            if (isEmpty(mat.unit)) {
                printf("Don vi tinh khong duoc rong!\n");
            }
        } while (isEmpty(mat.unit));
        while (1) {
            printf("Nhap so luong: ");
            fgets(tmp, sizeof(tmp), stdin);
            tmp[strcspn(tmp, "\n")] = '\0';
            if (strlen(tmp) == 0) { 
                printf("So luong khong duoc rong!\n"); 
                continue; 
            }
            if (!isNumber(tmp)) { 
                printf("So luong chi duoc nhap so!\n"); 
                continue; 
            }
            mat.qty = atoi(tmp);
            if (mat.qty < 0) { 
                printf("So luong phai >= 0!\n"); 
                continue; 
            }
            break;
        }
        mat.status = 1;
        arr[*length] = mat;
        (*length)++;
        printf("Them vat tu thanh cong!\n");
    }
}

void updateMat(struct Material *arr, int length) {
    if (length == 0) { 
        printf("Danh sach vat tu trong!\n"); 
        return; 
    }
    char id[10];
    printf("Nhap ma vat tu can cap nhat: ");
    inputMatIdStrict(id, arr, length, 0);
    int index = -1;
    for (int i = 0; i < length; i++)
        if (strcmp(arr[i].matId, id) == 0) { 
            index = i; 
            break; 
        }
    if (index == -1) { 
        printf("Khong tim thay vat tu voi ma %s\n", id); 
        return; 
    }
    while (1) {
        printf("Cap nhat ten vat tu: ");
        fgets(arr[index].name, sizeof(arr[index].name), stdin);
        arr[index].name[strcspn(arr[index].name, "\n")] = '\0';
        removeSpaces(arr[index].name);
        if (isEmpty(arr[index].name)) {
            printf("Ten vat tu khong duoc rong!\n");
            continue;
        }
        break;
    }
    while (1) {
        printf("Cap nhat don vi tinh: ");
        fgets(arr[index].unit, sizeof(arr[index].unit), stdin);
        arr[index].unit[strcspn(arr[index].unit, "\n")] = '\0';
        removeSpaces(arr[index].unit);
        if (isEmpty(arr[index].unit)) {
            printf("Don vi tinh khong duoc rong!\n");
            continue;
        }
        break;
    }
    char tmp[20];
    while (1) {
        printf("Cap nhat so luong: ");
        fgets(tmp, sizeof(tmp), stdin);
        tmp[strcspn(tmp, "\n")] = '\0';
        if (strlen(tmp) == 0) { 
            printf("So luong khong duoc rong!\n"); 
            continue; 
        }
        if (!isNumber(tmp)) { 
            printf("So luong chi duoc nhap so!\n"); 
            continue; 
        }
        arr[index].qty = atoi(tmp);
        if (arr[index].qty < 0) { 
            printf("So luong phai >= 0!\n"); 
            continue; 
        }
        break;
    }
    printf("Cap nhat thanh cong!\n");
}

void changeStatus(struct Material *arr, int *length) {
	char str[50];
    if (*length == 0) { 
		printf("Danh sach vat tu trong!\n"); 
		return; }
    int choice;
    char id[10];
    while (1) {
        printf("\n===== QUAN LY TRANG THAI VAT TU =====");
        printf("\n1. Khoa/Mo khoa vat tu \n2. Xoa vat tu \n3. Quay lai \nLua chon: ");
        scanf("%d", &choice); 
		getchar();
        switch (choice) {
            case 1: {
			    printf("Nhap ma vat tu: ");
			    inputMatIdStrict(id, arr, *length, 0);
			
			    int index1 = -1;
			    for (int i = 0; i < *length; i++)
			        if (strcmp(arr[i].matId, id) == 0) {
			            index1 = i;
			            break;
			        }
			
			    if (index1 == -1) {
			        printf("Khong tim thay vat tu!\n");
			        break;
			    }
			    printf("Trang thai hien tai: %s\n",
			           arr[index1].status == 1 ? "Con su dung (MO)" : "Het han su dung (KHOA)");
			
			    char choice;
			
			    if (arr[index1].status == 1) {
			        printf("Vat tu dang MO. \nBan co muon KHOA khong? (co(1)/khong(0)): ");
			        choice = getchar();
			        getchar();
			        if (choice == '1') {
			            arr[index1].status = 0;
			            printf("Da KHOA vat tu thanh cong!\n");
			        } else {
			            printf("Khong thuc hien thay doi!\n");
			        }
			    }
			    else {
			        printf("Vat tu dang KHOA. \nBan co muon MO khong? (co(1)/khong(0)): ");
			        choice = getchar();
			        getchar();
			        if (choice == '1') {
			            arr[index1].status = 1;
			            printf("Da MO vat tu thanh cong!\n");
			        } else {
			            printf("Khong thuc hien thay doi!\n");
			        }
			    }
			    break;
			}

            case 2: {
                printf("Nhap ma vat tu muon xoa: ");
                inputMatIdStrict(id, arr, *length, 0);
                int index2 = -1;
                for (int i = 0; i < *length; i++)
                    if (strcmp(arr[i].matId, id) == 0) { 
						index2 = i; 
						break; 
					}
                if (index2 == -1) { 
					printf("Khong tim thay vat tu!\n"); 
					break; 
				}
                for (int i = index2; i < *length - 1; i++) {
					arr[i] = arr[i + 1];
				}
                (*length)--;
                printf("Xoa vat tu thanh cong!\n");
                break;
            }
            case 3: 
	            printf("Dang thoat chuc nang...");
	            break;
            default: printf("Vui long chon 1 -> 3!\n");
        }
    }
}

void searchMat(struct Material *arr, int length) {
	char str[50];
    if (length == 0) { printf("Danh sach vat tu trong!\n"); return; }
    int choice;
    char key[50];
    int index = 0;
    while (1) {
        printf("\n1. Tim theo ma vat tu\n2. Tim theo ten vat tu\n3. Quay lai\nLua chon cua ban: ");
        scanf("%d", &choice); getchar();
        switch (choice) {
            case 1: {
                printf("Nhap ma vat tu: ");
                inputMatIdStrict(key, arr, length, 0);
                int found1 = 0;
                for (int i = 0; i < length; i++)
                    if (strcmp(arr[i].matId, key) == 0) { found1 = 1;
                        printf("\n|	Ma: %s |	Ten: %s |	Don vi: %s |	So luong: %d |	Trang thai: %s |\n", arr[i].matId, arr[i].name, arr[i].unit, arr[i].qty, arr[i].status == 1 ? "Con su dung" : "Het han su dung");
                        break;
                    }
                if (!found1) printf("Khong tim thay vat tu!\n");
                break;
            }
            case 2: {
                printf("Nhap ten vat tu muon tim: ");
                fgets(key, sizeof(key), stdin); key[strcspn(key, "\n")] = '\0';
                removeSpaces(key);
				if (isEmpty(key)) {
				    printf("Ten vat tu khong duoc rong!\n");
				    continue;
				}
                strToLower(key);

                int found2 = 0;
                for (int i = 0; i < length; i++) {
                    char nameLower[50];
                    strcpy(nameLower, arr[i].name);
                    strToLower(nameLower);
                    if (strstr(nameLower, key) != NULL) { 
                        found2 = 1;
                        printf("\n|	Ma: %s |	Ten: %s |	Don vi: %s |	So luong: %d |	Trang thai: %s |\n", 
                            arr[i].matId, arr[i].name, arr[i].unit, arr[i].qty, arr[i].status == 1 ? "Con su dung" : "Het han su dung");
                    }
                }
                if (!found2) printf("Khong tim thay vat tu!\n");
                break;
            }
            case 3: printf("Dang thoat chuong trinh..."); return;
            default: printf("Vui long chon 1 -> 3!\n");
        }
    }
}

void displayMat(struct Material *arr, int length) {
    if (length == 0) {
        printf("Danh sach vat tu trong!\n");
        return;
    }

    int page = 1;
    int perPage = 5;
    int totalPage = (length + perPage - 1) / perPage;

    while (1) {
        printf("\n======================== DANH SACH VAT TU (Trang %d/%d) =========================\n", page, totalPage);
        printf("| %-5s | %-25s | %-10s | %-8s | %-15s |\n",
               "Ma", "Ten", "Don vi", "So luong", "Trang thai");
        printf("-------------------------------------------------------------------------------\n");

        int start = (page - 1) * perPage;
        int end = start + perPage;
        if (end > length) end = length;

        for (int i = start; i < end; i++) {
            printf("| %-5s | %-25s | %-10s | %-8d | %-15s |\n",
                   arr[i].matId, arr[i].name, arr[i].unit, arr[i].qty,
                   arr[i].status == 1 ? "Con su dung" : "Het han su dung");
        }

        printf("-------------------------------------------------------------------------------\n");
        printf("1. Trang truoc\t2. Trang sau\t3. Den trang\t4. Thoat hien thi\nLua chon: ");

        int c;
        scanf("%d", &c);
        getchar();

        switch(c) {
            case 1:
                if (page == 1) {
                    printf("Ban dang o trang dau!\n");
                } else {
                    page--;
                }
                break;
            case 2:
                if (page == totalPage) {
                    printf("Ban dang o trang cuoi!\n");
                } else {
                    page++;
                }
                break;
            case 3: {
                int gotoPage;
                printf("Nhap trang muon den (1-%d): ", totalPage);
                scanf("%d", &gotoPage);
                getchar();
                if (gotoPage >= 1 && gotoPage <= totalPage) {
                    page = gotoPage;
                } else {
                    printf("Trang khong hop le!\n");
                }
                break;
            }
            case 4:
                printf("Dang thoat hien thi danh sach...\n");
                return;
            default:
                printf("Lua chon khong hop le!\n");
        }
    }
}

void sortMat(struct Material *arr, int length) {
    int choice;
    while (1) {
        printf("\n===== MENU SAP XEP =====\n");
        printf("1. Sap xep theo ten (A-Z, khong phan biet hoa thuong)\n");
        printf("2. Sap xep theo so luong (tang dan)\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                for (int i = 0; i < length - 1; i++) {
                    for (int j = 0; j < length - i - 1; j++) {
                        const char *a = arr[j].name;
                        const char *b = arr[j + 1].name;
                        while (*a && *b && tolower(*a) == tolower(*b)) { a++; b++; }
                        if (tolower(*a) > tolower(*b)) {
                            struct Material tmp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = tmp;
                        }
                    }
                }
                printf("Da sap xep theo ten!\n");
                break;
            }
            case 2: {
                for (int i = 0; i < length - 1; i++) {
                    for (int j = 0; j < length - i - 1; j++) {
                        if (arr[j].qty > arr[j + 1].qty) {
                            struct Material tmp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = tmp;
                        }
                    }
                }
                printf("Da sap xep theo so luong!\n");
                break;
            }
            case 3:
                printf("Da thoat chuc nang sap xep!\n");
                return;
            default:
                printf("Lua chon khong hop le, vui long chon 1->3!\n");
        }
    }
}
	
int main() {
    struct Material arr[100]; 
    int length = 13;
    for (int i = 0; i < 13; i++) {
        arr[i] = initList[i];
    }

    char str[50];
    while (1) {
        int choiceMain = 0;
        printf("\n======= MENU QUAN LY VAT TU =======");
        printf("\n|1. Menu quan ly tai khoan        |");
        printf("\n|2. Menu quan ly giao dich        |");
        printf("\n|3. Thoat                         |");
        printf("\n===================================");
        printf("\nChon chuc nang: ");
        scanf("%d", &choiceMain); 
        getchar();
        switch (choiceMain) {
            case 1: {
                int choice1 = 0;
                do {
                    printf("\n======= MENU QUAN LY TAI KHOAN =======");
                    printf("\n|1. Them vat tu moi                  |");
                    printf("\n|2. Cap nhat thong tin               |");
                    printf("\n|3. Quan ly trang thai               |");
                    printf("\n|4. Tim kiem vat tu                  |");
                    printf("\n|5. Hien thi danh sach               |");
                    printf("\n|6. Sap xep danh sach                |");
                    printf("\n|7. Quay lai menu quan ly tai khoan  |");
                    printf("\n======================================");
                    printf("\nLua chon: ");
                    scanf("%d", &choice1); getchar();
                    switch (choice1) {
                        case 1: addMat(arr, &length); break;
                        case 2: updateMat(arr, length); break;
                        case 3: changeStatus(arr, &length); break;
                        case 4: searchMat(arr, length); break;
                        case 5: displayMat(arr, length); break;
                        case 6: sortMat(arr, length); break;
                        case 7: printf("Dang thoat menu quan ly vat tu...\n"); break;
                        default: printf("Vui long chon tu 1->7!\n");
                    }
                } while (choice1 != 7);
                break;
            }
            case 2: {
                int choice2 = 0;
                do {
                    printf("\n======= MENU QUAN LY GIAO DICH =======");
                    printf("\n|1. Giao dich nhap/xuat vat tu       |");
                    printf("\n|2. Lich su nhap/xuat                |");
                    printf("\n|3. Quay lai menu quan ly vat tu     |");
                    printf("\n======================================");
                    printf("\nLua chon: ");
                    scanf("%d", &choice2); getchar();
                    switch (choice2) {
                        case 1: break;
                        case 2: break;
                        case 3: printf("Dang thoat menu giao dich...\n"); break;
                        default: printf("Vui long chon tu 1->3!\n");
                    }
                } while (choice2 != 3);
                break;
            }
            case 3: printf("Da thoat chuong trinh!\n"); return 0;
            default: printf("Vui long chon chuc nang tu 1->3!\n");
        }
    }
    return 0;
}

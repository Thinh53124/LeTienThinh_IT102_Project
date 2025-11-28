#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

void printError(char *msg) { 
	printf(RED "%s" RESET, msg); 
}
void printWarning(char *msg) { 
	printf(YELLOW "%s" RESET, msg); 
}
void printSuccess(char *msg) { 
	printf(GREEN "%s" RESET, msg); 
}

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
    int qty;
}; 

int autoTransId = 300;

void generateTransId(char *id) {
    sprintf(id, "T%04d", autoTransId++);
}

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
        if (!isdigit((unsigned char)s[i])) return 0;
    return 1;
}

int isEmpty(char *str) {
    if (str == NULL) return 1;
    for (int i = 0; str[i] != '\0'; i++)
        if (!isspace((unsigned char)str[i])) return 0;
    return 1;
}

int existId(struct Material *arr, int length, char *id) {
    for (int i = 0; i < length; i++)
        if (strcmp(arr[i].matId, id) == 0) return 1;
    return 0;
}

void removeSpaces(char *str) {
    int len = strlen(str);
    int start = 0;
    while (start < len && isspace((unsigned char)str[start])) start++;
    if (start == len) { str[0] = '\0'; return; }
    int end = len - 1;
    while (end >= start && isspace((unsigned char)str[end])) end--;
    int j = 0;
    for (int i = start; i <= end; i++) str[j++] = str[i];
    str[j] = '\0';
}

void strToLower(char *s) {
    for (int i = 0; s[i]; i++) s[i] = tolower(s[i]);
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inputMatIdStrict(char *matId, struct Material *arr, int length, int checkExist) {
    while (1) {
        fgets(matId, 10, stdin);
        if (matId[strlen(matId) - 1] != '\n')
            clearBuffer();
        else
            matId[strcspn(matId, "\n")] = '\0';

        if (strlen(matId) == 0) { 
            printError("Ma vat tu khong duoc rong!\n");
            printf("Nhap ma vat tu: ");
            continue; 
        }

        if (!isNumber(matId)) { 
            printError("Ma vat tu chi duoc nhap so!\n");
            printf("Nhap ma vat tu: ");
            continue; 
        }

        if (checkExist && existId(arr, length, matId)) { 
            printWarning("Ma vat tu da ton tai!\n");
            printf("Nhap ma vat tu: ");
            continue; 
        }

        break;
    }
}

int inputChoice(int min, int max) {
    char tmp[20];
    int choice;
    while (1) {
        fgets(tmp, sizeof(tmp), stdin);
        tmp[strcspn(tmp, "\n")] = '\0';
        removeSpaces(tmp);
        if (isEmpty(tmp)) {
            printError("Lua chon khong duoc rong!\n");
            printf("Lua chon cua ban: ");
            continue;
        }
        if (!isNumber(tmp)) {
            printError("Chi duoc nhap so!\n");
            printf("Lua chon cua ban: ");
            continue;
        }
        choice = atoi(tmp);
        if (choice < min || choice > max) {
            printError("Lua chon khong hop le!\n");
            printf("Lua chon cua ban: ");
            continue;
        }
        break;
    }
    return choice;
}

void addMat(struct Material *arr, int *length) {
    int n;
    char tmp[20];
    while (1) {
        printf("Nhap so luong loai vat tu muon them: ");
        fgets(tmp, sizeof(tmp), stdin);
        tmp[strcspn(tmp, "\n")] = '\0';
        if (strlen(tmp) == 0) { 
			printError("So luong khong duoc rong!\n"); 
			continue; 
		}
        if (!isNumber(tmp)) { 
			printError("So luong chi duoc nhap so!\n"); 
			continue; 
		}
        n = atoi(tmp);
        if (n <= 0) { 
			printError("So luong phai > 0!\n"); 
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
            if (isEmpty(mat.name)) printError("Ten vat tu khong duoc rong!\n");
        } while (isEmpty(mat.name));
        do {
            printf("Nhap don vi tinh: ");
            fgets(mat.unit, sizeof(mat.unit), stdin);
            mat.unit[strcspn(mat.unit, "\n")] = '\0';
            removeSpaces(mat.unit);
            if (isEmpty(mat.unit)) printError("Don vi tinh khong duoc rong!\n");
        } while (isEmpty(mat.unit));
        while (1) {
            printf("Nhap so luong: ");
            fgets(tmp, sizeof(tmp), stdin);
            tmp[strcspn(tmp, "\n")] = '\0';
            if (strlen(tmp) == 0) { 
				printError("So luong khong duoc rong!\n"); 
				continue; 
			}
            if (!isNumber(tmp)) { 
				printError("So luong chi duoc nhap so!\n"); 
				continue; 
			}
            mat.qty = atoi(tmp);
            if (mat.qty < 0) { 
				printError("So luong phai >= 0!\n"); 
				continue; 
			}
            break;
        }
        mat.status = 1;
        arr[*length] = mat;
        (*length)++;
        printSuccess("Them vat tu thanh cong!\n");
    }
}

void updateMat(struct Material *arr, int length) {
    if (length == 0) { 	
		printError("Danh sach vat tu trong!\n"); 
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
		printWarning("Khong tim thay vat tu!\n"); 
		return; 
	}
    while (1) {
        printf("Cap nhat ten vat tu: ");
        fgets(arr[index].name, sizeof(arr[index].name), stdin);
        arr[index].name[strcspn(arr[index].name, "\n")] = '\0';
        removeSpaces(arr[index].name);
        if (isEmpty(arr[index].name)) { 
			printError("Ten vat tu khong duoc rong!\n"); 
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
			printError("Don vi tinh khong duoc rong!\n"); 
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
			printError("So luong khong duoc rong!\n"); 
			continue; 
		}
        if (!isNumber(tmp)) { 
			printError("So luong chi duoc nhap so!\n");
			continue; 
		}
        arr[index].qty = atoi(tmp);
        if (arr[index].qty < 0) { 
			printError("So luong phai >= 0!\n"); 
			continue; 
		}
        break;
    }
    printSuccess("Cap nhat thanh cong!\n");
}

void changeStatus(struct Material *arr, int *length) {
    if (*length == 0) { printError("Danh sach vat tu trong!\n"); return; }
    int choice;
    char id[10];
    while (1) {
        printf("\n===== QUAN LY TRANG THAI VAT TU =====");
        printf("\n1. Khoa/Mo khoa vat tu \n2. Xoa vat tu \n3. Quay lai \nLua chon: ");
        scanf("%d", &choice); getchar();
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
				printWarning("Khong tim thay vat tu!\n"); 
				break; }
                printf("Trang thai hien tai: %s\n", arr[index1].status == 1 ? "Con su dung (MO)" : "Het han su dung (KHOA)");
                char choice;
                if (arr[index1].status == 1) {
                    printf("Vat tu dang MO. Ban co muon KHOA khong? (co(1)/khong(0)): ");
                    choice = getchar(); getchar();
                    if (choice == '1') { 
						arr[index1].status = 0; 
						printSuccess("Da KHOA vat tu thanh cong!\n"); 
					}else{
						printWarning("Khong thuc hien thay doi!\n");
					}
                } else {
                    printf("Vat tu dang KHOA. Ban co muon MO khong? (co(1)/khong(0)): ");
                    choice = getchar(); getchar();
                    if (choice == '1') { 
					arr[index1].status = 1; 
					printSuccess("Da MO vat tu thanh cong!\n"); 
					}else{
						printWarning("Khong thuc hien thay doi!\n");
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
					printWarning("Khong tim thay vat tu!\n"); 
					break; 
				}
                for (int i = index2; i < *length - 1; i++) arr[i] = arr[i + 1];
                (*length)--;
                printSuccess("Xoa vat tu thanh cong!\n");
                break;
            }
            case 3: 
				printSuccess("Dang thoat chuc nang...\n"); 
				return;
            default: 
				printError("Lua chon khong hop le! Vui long chon 1->3\n");
				break;
        }
    }
}

void searchMat(struct Material *arr, int length) {
    if (length == 0) { 
		printError("Danh sach vat tu trong!\n");
		return; 
	}
    int choice;
    char key[50];
    while (1) {
        printf("\n1. Tim theo ma vat tu\n2. Tim theo ten vat tu\n3. Quay lai\nLua chon cua ban: ");
        choice = inputChoice(1, 3);
        switch (choice) {
            case 1: {
                printf("Nhap ma vat tu: ");
                inputMatIdStrict(key, arr, length, 0);
                int found = 0;
                for (int i = 0; i < length; i++) {
                    if (strcmp(arr[i].matId, key) == 0) {
                        found = 1;
                        printf("\n| Ma: %s | Ten: %s | Don vi: %s | So luong: %d | Trang thai: %s |\n",
                               arr[i].matId, arr[i].name, arr[i].unit, arr[i].qty,
                               arr[i].status == 1 ? "Con su dung" : "Het han su dung");
                        break;
                    }
                }
                if (!found){
					printWarning("Khong tim thay vat tu!\n");
	                break;
	           	}
	           	break;
            }
            case 2: {
                printf("Nhap ten vat tu muon tim: ");
                fgets(key, sizeof(key), stdin); key[strcspn(key, "\n")] = '\0';
                removeSpaces(key);
                if (isEmpty(key)) { 
					printError("Ten vat tu khong duoc rong!\n"); 
					continue; 
				}
                strToLower(key);
                int found = 0;
                for (int i = 0; i < length; i++) {
                    char nameLower[50]; strcpy(nameLower, arr[i].name); strToLower(nameLower);
                    if (strstr(nameLower, key) != NULL) {
                        found = 1;
                        printf("\n| Ma: %s | Ten: %s | Don vi: %s | So luong: %d | Trang thai: %s |\n",
                               arr[i].matId, arr[i].name, arr[i].unit, arr[i].qty,
                               arr[i].status == 1 ? "Con su dung" : "Het han su dung");
                    }
                }
                if (!found) printWarning("Khong tim thay vat tu!\n");
                break;
            }
            case 3: 
	            printSuccess("Dang thoat chuc nang...");
				return;
            default: printError("Vui long chon 1 -> 3!\n");
        }
    }
}

void displayMat(struct Material *arr, int length) {
    if (length == 0) { 
        printError("Danh sach vat tu trong!\n"); 
        return; 
    }

    int page = 1, perPage = 5;
    int totalPage = (length + perPage - 1) / perPage;
    char tmp[20];

    while (1) {
        printf("\n======================== DANH SACH VAT TU (Trang %d/%d) =========================\n", page, totalPage);
        printf("| %-5s | %-25s | %-10s | %-8s | %-15s |\n", "Ma", "Ten", "Don vi", "So luong", "Trang thai");
        printf("-------------------------------------------------------------------------------\n");

        int start = (page - 1) * perPage;
        int end = start + perPage; if (end > length) end = length;
        for (int i = start; i < end; i++)
            printf("| %-5s | %-25s | %-10s | %-8d | %-15s |\n",
                   arr[i].matId, arr[i].name, arr[i].unit, arr[i].qty,
                   arr[i].status == 1 ? "Con su dung" : "Het han su dung");
        printf("-------------------------------------------------------------------------------\n");

        int c;
        while (1) {
            printf("1. Trang truoc\t2. Trang sau\t3. Den trang\t4. Thoat hien thi\nLua chon: ");
            fgets(tmp, sizeof(tmp), stdin);
            tmp[strcspn(tmp, "\n")] = '\0';
            removeSpaces(tmp);

            if (isEmpty(tmp)) { printError("Lua chon khong duoc rong!\n"); continue; }
            if (!isNumber(tmp)) { printError("Chi duoc nhap so!\n"); continue; }

            c = atoi(tmp);
            if (c < 1 || c > 4) { printError("Lua chon khong hop le!\n"); continue; }
            break;
        }

        switch (c) {
            case 1: 
                if (page > 1) page--;
                else printWarning("Ban dang o trang dau!\n");
                break;
            case 2: 
                if (page < totalPage) page++;
                else printWarning("Ban dang o trang cuoi!\n");
                break;
            case 3: {
                int gotoPage;
                while (1) {
                    printf("Nhap trang muon den (1-%d): ", totalPage);
                    fgets(tmp, sizeof(tmp), stdin);
                    tmp[strcspn(tmp, "\n")] = '\0';
                    removeSpaces(tmp);

                    if (isEmpty(tmp)) { printError("Khong duoc rong!\n"); continue; }
                    if (!isNumber(tmp)) { printError("Chi duoc nhap so!\n"); continue; }

                    gotoPage = atoi(tmp);
                    if (gotoPage < 1 || gotoPage > totalPage) { printError("Trang khong hop le!\n"); continue; }
                    break;
                }
                page = gotoPage;
                printSuccess("Dang den trang ban muon...");
                break;
            }
            case 4:
                printSuccess("Dang thoat chuc nang...");
                return;
        }
    }
}

void sortMat(struct Material *arr, int length) {
    int choice;
    while(1){
        printf("\n===== MENU SAP XEP =====\n1. Sap xep theo ten (A-Z, khong phan biet hoa thuong)\n2. Sap xep theo so luong (tang dan)\n3. Thoat\nLua chon cua ban: ");
        scanf("%d",&choice); getchar();
        switch(choice){
            case 1:{
                for(int i=0;i<length-1;i++){
                    for(int j=0;j<length-i-1;j++){
                        char name1[50], name2[50]; strcpy(name1,arr[j].name); strToLower(name1);
                        strcpy(name2,arr[j+1].name); strToLower(name2);
                        if(strcmp(name1,name2)>0){ struct Material tmp=arr[j]; arr[j]=arr[j+1]; arr[j+1]=tmp; }
                    }
                }
                printSuccess("Da sap xep theo ten!\n"); 
				break;
            }
            case 2:{
                for(int i=0;i<length-1;i++){
                    for(int j=0;j<length-i-1;j++){
                        if(arr[j].qty>arr[j+1].qty){ struct Material tmp=arr[j]; arr[j]=arr[j+1]; arr[j+1]=tmp; }
                    }
                }
                printSuccess("Da sap xep theo so luong!\n"); 
				break;
            }
            case 3:
            	printSuccess("Dang thoat chuc nang...");
				return; 
			default: 
				printError("Lua chon khong hop le, vui long chon 1->3!\n");
				break;
        }
    }
}

struct Transaction history[200];
int transCount = 0;

void tradeMat(struct Material *arr, int length) {
    char id[10];

    printf("Nhap ma vat tu: ");
    inputMatIdStrict(id, arr, length, 0);

    int index = -1;
    for (int i = 0; i < length; i++)
        if (strcmp(arr[i].matId, id) == 0) { index = i; break; }

    if (index == -1) { printWarning("Khong tim thay vat tu!\n"); return; }
    if (arr[index].status == 0) { printError("Vat tu dang KHOA, KHONG THE giao dich!\n"); return; }

    char tmp[20];
    int typeChoice;
    while (1) {
        printf("\n1. Nhap hang\n2. Xuat hang\nLua chon: ");
        fgets(tmp, sizeof(tmp), stdin);
        tmp[strcspn(tmp, "\n")] = '\0';
        removeSpaces(tmp);
        if (isEmpty(tmp)) { printError("Lua chon khong duoc rong!\n"); continue; }
        if (!isNumber(tmp)) { printError("Chi duoc nhap so!\n"); continue; }
        typeChoice = atoi(tmp);
        if (typeChoice != 1 && typeChoice != 2) { printError("Lua chon khong hop le!\n"); continue; }
        break;
    }

    int amount;
    while (1) {
        printf("Nhap so luong: ");
        fgets(tmp, sizeof(tmp), stdin);
        tmp[strcspn(tmp, "\n")] = '\0';
        removeSpaces(tmp);
        if (isEmpty(tmp)) { printError("So luong khong duoc rong!\n"); continue; }
        if (!isNumber(tmp)) { printError("Chi duoc nhap so!\n"); continue; }
        amount = atoi(tmp);
        if (amount <= 0) { printError("So luong phai > 0!\n"); continue; }
        if (typeChoice == 2 && amount > arr[index].qty) { 
            printError("So luong khong du de xuat!\n"); 
            continue; 
        }
        break;
    }

    if (typeChoice == 1) { arr[index].qty += amount; printSuccess("Nhap hang thanh cong!\n"); }
    else { arr[index].qty -= amount; printSuccess("Xuat hang thanh cong!\n"); }

    struct Transaction t;
    generateTransId(t.transId);
    strcpy(t.matId, id);
    strcpy(t.type, typeChoice == 1 ? "Nhap" : "Xuat");

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(t.date, 15, "%d/%m/%Y", tm_info);

    t.qty = amount;
    history[transCount++] = t;
}


void displayTransaction(struct Transaction *list, int total) {
    if (total == 0) { printWarning("Chua co giao dich nao!\n"); return; }
    int page = 1, perPage = 5;
    int totalPage = (total + perPage - 1) / perPage;
    char tmp[20];
    while (1) {
        printf("\n===================== LICH SU GIAO DICH (Trang %d/%d) =====================\n",
               page, totalPage);
        printf("| %-8s | %-6s | %-6s | %-12s | %-8s |\n", "Ma GD", "Ma VT", "Loai", "Ngay", "So luong");
        printf("-------------------------------------------------------------------------------\n");

        int start = (page - 1) * perPage;
        int end = start + perPage; if (end > total) end = total;

        for (int i = start; i < end; i++) {
            printf("| %-8s | %-6s | %-6s | %-12s | %-8d |\n",
                   list[i].transId, list[i].matId, list[i].type, list[i].date, list[i].qty);
        }
        printf("-------------------------------------------------------------------------------\n");

        int c;
        while (1) {
            printf("1. Trang truoc\t2. Trang sau\t3. Den trang\t4. Thoat\nLua chon: ");
            fgets(tmp, sizeof(tmp), stdin);
            tmp[strcspn(tmp, "\n")] = '\0';
            removeSpaces(tmp);
            if (isEmpty(tmp)) { printError("Lua chon khong duoc rong!\n"); continue; }
            if (!isNumber(tmp)) { printError("Chi duoc nhap so!\n"); continue; }
            c = atoi(tmp);
            if (c < 1 || c > 4) { printError("Lua chon khong hop le!\n"); continue; }
            break;
        }

        switch (c) {
            case 1: if (page > 1) page--; else printWarning("Ban dang o trang dau!\n"); break;
            case 2: if (page < totalPage) page++; else printWarning("Ban dang o trang cuoi!\n"); break;
            case 3: {
                int gotoP;
                while (1) {
                    printf("Nhap trang (1-%d): ", totalPage);
                    fgets(tmp, sizeof(tmp), stdin);
                    tmp[strcspn(tmp, "\n")] = '\0';
                    removeSpaces(tmp);
                    if (isEmpty(tmp)) { printError("Khong duoc rong!\n"); continue; }
                    if (!isNumber(tmp)) { printError("Chi duoc nhap so!\n"); continue; }
                    gotoP = atoi(tmp);
                    if (gotoP < 1 || gotoP > totalPage) { printError("Trang khong hop le!\n"); continue; }
                    break;
                }
                page = gotoP;
                break;
            }
            case 4: printSuccess("Dang thoat chuc nang..."); return;
            default: printError("Vui long nhap tu 1->4!!\n"); break;
        }
    }
}


int main() {
    struct Material arr[100];
    int length = 13;
    for(int i=0;i<length;i++) arr[i]=initList[i];

    while(1){
        int choiceMain;
        printf("\n======= MENU QUAN LY VAT TU =======");
        printf("\n|1. Menu quan ly tai khoan        |");
        printf("\n|2. Menu quan ly giao dich        |");
        printf("\n|3. Thoat                         |");
        printf("\n===================================");
        printf("\nChon chuc nang: ");
		choiceMain = inputChoice(1, 3);
        switch(choiceMain){
            case 1:{
                int choice1;
				do{
				    printf("\n======= MENU QUAN LY TAI KHOAN =======");
				    printf("\n|1. Them vat tu moi                  |");
				    printf("\n|2. Cap nhat thong tin               |");
				    printf("\n|3. Quan ly trang thai               |");
				    printf("\n|4. Tim kiem vat tu                  |");
				    printf("\n|5. Hien thi danh sach               |");
				    printf("\n|6. Sap xep danh sach                |");
				    printf("\n|7. Quay lai menu quan ly tai khoan  |");
				    printf("\n======================================");
				    printf("\nLua chon cua ban: ");
				    choice1 = inputChoice(1, 7);
				
				    switch(choice1){
				        case 1: addMat(arr,&length); break;
				        case 2: updateMat(arr,length); break;
				        case 3: changeStatus(arr,&length); break;
				        case 4: searchMat(arr,length); break;
				        case 5: displayMat(arr,length); break;
				        case 6: sortMat(arr,length); break;
				        case 7: printSuccess("Dang thoat menu quan ly vat tu...\n"); break;
				        default: printError("Vui long chon tu 1->7!\n");
				    }
				}while(choice1!=7);
                break;
            }
            case 2:{
			    int choice2;
			    do{
				    printf("\n======= MENU QUAN LY GIAO DICH =======");
				    printf("\n|1. Giao dich nhap/xuat vat tu       |");
				    printf("\n|2. Xem lich su giao dich            |");
				    printf("\n|3. Quay lai                         |");
				    printf("\n======================================");
				    printf("\nLua chon cua ban: ");
				    choice2 = inputChoice(1, 3);
				
				    switch(choice2){
				        case 1: tradeMat(arr, length); break;
				        case 2: displayTransaction(history, transCount); break;
				        case 3: printSuccess("Dang thoat menu giao dich...\n"); break;
				        default: printError("Lua chon khong hop le! Vui long chon 1->3!\n");
				    }
				}while(choice2 != 3);
			    break;
			}
            case 3: printSuccess("Da thoat chuong trinh!\n"); return 0;
            default: printError("Vui long chon chuc nang tu 1->3!\n");
        }
    }
    return 0;
}

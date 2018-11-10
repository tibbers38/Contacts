#include "Function.hpp"
#include <stdio.h>
#include <string.h>

static void PrintInfo(const Contact &contact, int *contact_number) {
    printf("%d: %s : %s : %s : %s\n", *contact_number, contact.name, contact.address, contact.home_number, contact.work_number);
    (*contact_number)++;
}


// Open File ---------------------------

void OpenFile(FILE *&file, char mode[]) {
    // change file location here.
    file = fopen("/Users/Nam/Documents/Xcode Documents/Contacts/Contacts/Data.dat", mode);
    if (file == NULL) {
        printf("Mo file khong thanh cong!!! Kiem tra duong dan file.\n");
    }
}

int TestOpen(FILE *&file) {
    char mode[] = "rb";
    
    OpenFile(file, mode); // test open.
    if (file == NULL) {
        return 0;
    }
    file = NULL;
    return 1;
}


// View Contact ------------------------

void ViewAllContacts(FILE *file) {
    Contact contact;
    int contact_number = 1;
    char mode[] = "rb";
    
    OpenFile(file, mode);
    printf("Ho va ten: Dia chi: So dien thoai nha rieng: So dien thoai cong viec.\n");

    fread(&contact, sizeof(contact), 1, file);
    while (!feof(file)) {
        PrintInfo(contact, &contact_number);
        fread(&contact, sizeof(contact), 1, file);
    }
    
//    do {
//        fread(&contact, sizeof(contact), 1, file);
//        printf("%s : %s : %s : %s\n", contact.name, contact.address, contact.home_number, contact.work_number);
//    } while (!feof(file)); sai
    
    fclose(file);
}


// Search Contact ------------------------

static void Compare(const Contact &contact, int sub_select, char info[], int* found, int* contact_number) {
    switch (sub_select) {
        case 1:
            if (strcmp(contact.name, info) == 0) {
                *found = 1;
                PrintInfo(contact, contact_number);
            }
            break;
        case 2:
            if (strcmp(contact.address, info) == 0) {
                *found = 1;
                PrintInfo(contact, contact_number);
            }
            break;
        case 3:
            if (strcmp(contact.home_number, info) == 0) {
                *found = 1;
                PrintInfo(contact, contact_number);
            }
            break;
        case 4:
            if (strcmp(contact.work_number, info) == 0) {
                *found = 1;
                PrintInfo(contact, contact_number);
            }
            break;
    }
}

void SearchContacts(FILE *&file, int sub_select, char info[]) {
    char mode[] = "rb";
    Contact contact;
    int found = 0;
    int contact_number = 1;
    
    OpenFile(file, mode);
    fread(&contact, sizeof(contact), 1, file);
    while (!feof(file)) {
        Compare(contact, sub_select, info, &found, &contact_number);
        fread(&contact, sizeof(contact), 1, file);
    }
    if (found == 0) {
        printf("Khong tim thay danh ba!!!.\n");
    }
    fclose(file);
}


// Sort Contact (use Quick Sort) -----------------------------

void swap(Contact* a, Contact* b) {
    Contact temp = *a;
    *a = *b;
    *b = temp;
}

int Partition (Contact arr[], int low, long high, int select) {
    Contact pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        switch (select) {
            case 1:
                if (strcmp(arr[j].name, pivot.name) < 0) {
                    i++;
                    swap(&arr[i], &arr[j]);
                }
                break;
            case 2:
                if (strcmp(arr[j].address, pivot.address) < 0) {
                    i++;
                    swap(&arr[i], &arr[j]);
                }
                break;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void QuickSort(Contact arr[], int low, long high, int select) {
    if (low < high) {
        int pi = Partition(arr, low, high, select);
        QuickSort(arr, low, pi - 1, select);
        QuickSort(arr, pi + 1, high, select);
    }
}

void GetFileSize(FILE *&file, long *size) {
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    rewind(file);
}

static void LoadContacts(Contact *&buffer, FILE *&file, long* file_size) {
    Contact temp;
    char mode[] = "rb";
    
    OpenFile(file, mode);
    GetFileSize(file, file_size); //480=2*240.
    buffer = new Contact[*file_size/sizeof(temp)];
    while (!feof(file)) {
        fread(buffer, sizeof(buffer), *file_size, file);
    }
}

void SortContacts(FILE *&file, int sub_select) {
    Contact* buffer;
    long contact_number = 0;
    long file_size = 0;
    char mode[] = "wb+";
    
    LoadContacts(buffer, file, &file_size); // load OK!!
    contact_number = file_size/long(sizeof(buffer[0]));
    QuickSort(buffer, 0, contact_number-1, sub_select); // ok
    OpenFile(file, mode);
    fwrite(buffer, sizeof(buffer[0]), contact_number, file);
    delete [] buffer;
    fclose(file);
    printf("Sap xep thanh cong!!!\n");
}


// Add New Contact ---------------------------

void AddNewContact(FILE *file) {
    Contact contact;
    // Open file and always write to end of file, expanding it.
    char mode[] = "ab";
    
    OpenFile(file, mode);
    fseek(stdin, 0, SEEK_END);
    
    printf("Nhap ten:\n");
    fgets(contact.name, sizeof(contact.name), stdin);
    printf("Nhap dia chi:\n");
    fgets(contact.address, sizeof(contact.address), stdin);
    printf("Nhap so dien thoai nha rieng:\n");
    fgets(contact.home_number, sizeof(contact.home_number), stdin);
    printf("Nhap so dien thoai cong viec:\n");
    fgets(contact.work_number, sizeof(contact.work_number), stdin);
    
    // Delete last character (\n) because of fgets
    contact.name[strlen(contact.name)-1] = '\0';
    contact.address[strlen(contact.address)-1] = '\0';
    contact.home_number[strlen(contact.home_number)-1] = '\0';
    contact.work_number[strlen(contact.work_number)-1] = '\0';
    
    fwrite(&contact, sizeof(contact), 1, file);
    printf("Da them danh ba.\n");
    fclose(file);
}


// Delete Contact -------------------------------

void DeleteContact(FILE *&file) {
    Contact* buffer;
    char mode[] = "wb+";
    int select = 0;
    long file_size = 0;
    long contact_number = 0;
    
    printf("Chon so thu tu danh ba muon xoa:\n\n");
    ViewAllContacts(file);
    scanf("%d", &select);
    
    LoadContacts(buffer, file, &file_size);
    contact_number = file_size/long(sizeof(buffer[0]));
    for (int i = select-1; i<contact_number-1; i++) {
        buffer[i]=buffer[i+1];
    }
    OpenFile(file, mode);
    fwrite(buffer, sizeof(buffer[0]), contact_number-1, file);
    delete [] buffer;
    fclose(file);
}

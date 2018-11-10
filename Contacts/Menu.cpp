#include "Menu.hpp"
#include <stdio.h>
#include <string.h>

void MainMenu(int* select) {
    printf("\nLựa chọn thao tác:\n");
    printf("1. Xem toàn bộ danh bạ.\n");
    printf("2. Tìm kiếm.\n");
    printf("3. Sắp xếp danh bạ.\n");
    printf("4. Thêm danh bạ mới.\n");
    printf("5. Xoá danh bạ.\n");
    printf("6. Kết thúc chương trình.\n");
    do {
        fflush(stdin);
        scanf("%d", select);
        if (*select<1 || *select>6) {
            printf("Lựa chọn sai!!! Vui lòng nhập lại. ");
        }
    } while (*select<1 || *select>6);
}

void Menu2(int* sub_select, char* info) {
    printf("Tìm kiếm theo:\n");
    printf("1. Họ và tên.\n");
    printf("2. Địa chỉ.\n");
    printf("3. Số điện thoại nhà riêng.\n");
    printf("4. Số điện thoại công việc.\n");
    do {
        fflush(stdin);
        scanf("%d", sub_select);
        if (*sub_select<1 ||*sub_select>4) {
            printf("Lựa chọn sai!!! Vui lòng nhập lại. ");
        }
    } while (*sub_select<1 ||*sub_select>4);
    switch (*sub_select) {
        case 1:
            printf("Nhập họ tên người cần tìm:\n");
            break;
        case 2:
            printf("Nhập địa chỉ người cần tìm:\n");
            break;
        case 3:
            printf("Nhập số điện thoại nhà riêng người cần tìm:\n");
            break;
        case 4:
            printf("Nhập số điện thoại công việc người cần tìm:\n");
            break;
    }
    fseek(stdin, 0, SEEK_END);
    // sizeof(info)*100 ???????? : info is pointer, size = 8. (64bit) not array.
    fgets(info, sizeof(info)*100, stdin);
    info[strlen(info)-1] = '\0';
}

void Menu3(int* sub_select, char* info) {
    printf("Sắp xếp theo:\n");
    printf("1. Họ và tên.\n");
    printf("2. Địa chỉ.\n");
    do {
        fflush(stdin);
        scanf("%d", sub_select);
        if (*sub_select<1 ||*sub_select>2) {
            printf("Lựa chọn sai!!! Vui lòng nhập lại. ");
        }
    } while (*sub_select<1 ||*sub_select>2);
}


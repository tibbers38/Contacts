
// Notes:
/*
    1. ALL WORKED!!!!!!!!
    2. Sửa đường dẫn file dữ liệu ở hàm OpenFile (Function.cpp)
    3. File dữ liệu là file nhị phân, có dạng *.dat
*/

#include "Menu.hpp"
#include "Function.hpp"

int main(int argc, const char * argv[]) {
    // Declaration
    typedef struct Contact Contact;
    
    int select = 0, sub_select = 0;
    char info[100];
    FILE* file;
    
    // Program
    if (TestOpen(file) == 0) return 0;
    do {
        MainMenu(&select);
        switch (select) {
            case 1:
                ViewAllContacts(file);
                break;
            case 2:
                Menu2(&sub_select, info);
                SearchContacts(file, sub_select, info);
                break;
            case 3:
                Menu3(&sub_select, info);
                SortContacts(file, sub_select);
                break;
            case 4:
                AddNewContact(file);
                break;
            case 5:
                DeleteContact(file);
                break;
            case 6:
                break;
        }
    } while (select != 6);
}

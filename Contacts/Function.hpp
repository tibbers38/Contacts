#ifndef Function_hpp
#define Function_hpp

#include <stdio.h>

struct Contact {
    char name[100];
    char address[100];
    char home_number[20];
    char work_number[20];
};

void OpenFile(FILE *&file, char mode[]);
int TestOpen(FILE *&file);
void ViewAllContacts(FILE *file);
void SearchContacts(FILE *&file, int select, char info[]);
void SortContacts(FILE *&file, int sub_select);
void AddNewContact(FILE *file);
void DeleteContact(FILE *&file);

#endif /* Function_hpp */

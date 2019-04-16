/*
Nama program 	: PhoneBook - Multi Linked List
Nama			: Ahmad Faaiz Al-auza'i
NPM				: 140810180023
Tanggal dibuat	: 16/04/2019
Deskripsi       : Program sederhana untuk mengelola buku telepon. Jika kita men-input contact, maka index akan terbentuk dengan sendirinya. Sebaliknya jika kita men-delete (semua)contact dalam suatu index maka index akan ter-delte dengan sendirinya. 
***********************************************/

#include <iostream>
using namespace std;

struct Contact {
    char name[10] ;
    char phone[12];
    Contact* next;
};

struct Index {
    char index;
    Index* next;
    Contact* firsContact;
};

typedef Contact* pointerContact;
typedef Index* pointerIndex;
typedef pointerIndex listIndex;

void createListIndex(listIndex& first){
    first = NULL;
}

void createElementContact(pointerContact& pBaru){
    pBaru = new Contact;
    cout << "Name : "; cin >> pBaru->name;
    cout << "Phone : "; cin >> pBaru->phone;
    pBaru->next = NULL;
}

void createElementIndex(pointerIndex& pBaruIndex, pointerContact pBaruContact){
    pBaruIndex = new Index;
    pBaruIndex->index = pBaruContact->name[0];          //buat index dengan mengambil huruf pertama nama contact, hanya jika index tidak ada saat insert contact
    pBaruIndex->next = NULL;
    pBaruIndex->firsContact = NULL;
}

bool cekIndex(listIndex firstIndex, pointerContact pCariContact, pointerIndex& pBantuIndex){
    pBantuIndex = firstIndex;
    while(pBantuIndex != NULL){
        if(pBantuIndex->index == pCariContact->name[0]){        //ketemu!!
            return true;
        }
        pBantuIndex = pBantuIndex->next;
    }
    return false;
}

void insertIndex(listIndex& first, pointerIndex pBaruIndex){    //sorting insertion
    pointerIndex pBantuIndex = first;
    pointerIndex pBeforeIndex;

    if (first == NULL) {                    //list kosong
        first = pBaruIndex;
    } else {
        while(pBaruIndex->index > pBantuIndex->index && pBantuIndex->next != NULL){
            pBeforeIndex = pBantuIndex;
            pBantuIndex = pBantuIndex->next;
        }

        if (pBantuIndex == first) {
            if (pBaruIndex->index > pBantuIndex->index) { //insertafter
                pBaruIndex->next = pBantuIndex->next;
                pBantuIndex->next = pBaruIndex;
            }
            else {                          //insertfirst
                pBaruIndex->next = first;
                first = pBaruIndex;
            } 
        } else if (pBantuIndex->next == NULL) { //insertlast
            if (pBaruIndex->index > pBantuIndex->index) { //insertlast
                pBantuIndex->next = pBaruIndex;
            }
            else {                          //insertbefore
                pBaruIndex->next = pBantuIndex;
                pBeforeIndex->next = pBaruIndex;
            } 
        } else {                                //insertbefore
            pBaruIndex->next = pBantuIndex;
            pBeforeIndex->next = pBaruIndex;
        }
    }
}

void insertContact(listIndex& firstIndex, pointerIndex pBaruIndex, pointerContact pBaruContact){
    pointerIndex pIndexCari;
    if (!cekIndex(firstIndex, pBaruContact, pIndexCari)) {                      //index tidak ada, maka buat index dahulu lalu insert ke list
        createElementIndex(pBaruIndex, pBaruContact);
        insertIndex(firstIndex, pBaruIndex);
        pIndexCari = pBaruIndex;
    } 

    //sorting insertion contact
    pointerContact pBantuContact = pIndexCari->firsContact;
    pointerContact pBeforeContact;

    if (pIndexCari->firsContact == NULL) {                    //list kosong
        pIndexCari->firsContact = pBaruContact;
    } else {
        while(pBaruContact->name[1] > pBantuContact->name[1] && pBantuContact->next != NULL){
            pBeforeContact = pBantuContact;
            pBantuContact = pBantuContact->next;
        }

        if (pBantuContact == pIndexCari->firsContact) {
            if (pBaruContact->name[1] > pBantuContact->name[1]) { //insertafter
                pBaruContact->next = pBantuContact->next;
                pBantuContact->next = pBaruContact;
            }
            else {                          //insertfirst
                pBaruContact->next = pIndexCari->firsContact;
                pIndexCari->firsContact = pBaruContact;
            } 
        } else if (pBantuContact->next == NULL) { //insertlast
            if (pBaruContact->name[1] > pBantuContact->name[1]) { //insertlast
                pBantuContact->next = pBaruContact;
            }
            else {                          //insertbefore
                pBaruContact->next = pBantuContact;
                pBeforeContact->next = pBaruContact;
            } 
        } else {                                //insertbefore
            pBaruContact->next = pBantuContact;
            pBeforeContact->next = pBaruContact;
        }
    }
}

void linearSearchContact(listIndex pBantuIndex, int& status, char keyContact[], pointerContact& pCariContact){
    pCariContact = pBantuIndex->firsContact;
    status = 0;
    while (pCariContact != NULL && status == 0){
        if (pCariContact->name == string(keyContact)){
            cout << "Data Ditemukan!" << endl;
            status = 1;
        }
        else
            pCariContact = pCariContact->next;
    }
}

void deleteContact(listIndex& firstIndex){
    char keyContact[10];
    int status;
    cout << "Masukkan nama : "; cin >> keyContact;

    //mencari index
    status = 0;
    pointerIndex pBantuIndex = firstIndex;
    pointerIndex pBeforeIndex;
    while(pBantuIndex != NULL){
        if(pBantuIndex->index == keyContact[0]){        //ketemu!!
            status = 1;
            break;
        }
        pBeforeIndex = pBantuIndex;
        pBantuIndex = pBantuIndex->next;
    }
    
    pointerContact pCariContact;
    pointerContact pBeforeContact;
    if (status == 1) {
        pCariContact = pBantuIndex->firsContact;
        //mencari contact dalam index yang sudah ditemukan
        status = 0;
        while (pCariContact != NULL && status == 0){
            if (pCariContact->name == string(keyContact)){
                cout << "Data Ditemukan!" << endl;
                status = 1;
            }
            else{
                pBeforeContact = pCariContact;
                pCariContact = pCariContact->next;
            }
        }
    }
    
    if (status == 1) {
        //delete data
        
        if (pBantuIndex->firsContact->next == NULL) { //index berisi satu contact -> delete index
            pointerIndex pDeleteIndex = pBantuIndex;
            if (pBantuIndex == firstIndex) {     //delete first
                if (pBantuIndex->next == NULL) { //index hanya satu di list 
                    pDeleteIndex = firstIndex;
                    firstIndex = NULL;
                } else {                        //lebih dari satu 
                    pDeleteIndex = firstIndex;
                    firstIndex = firstIndex->next;
                    pDeleteIndex->next = NULL;
                }
            }
            else if(pBantuIndex->next == NULL) { //delte last 
                pBeforeIndex->next = NULL;
            }
            else {  //delte tengah
                pBeforeIndex->next = pBantuIndex->next;
                pBantuIndex->next = NULL;
            }
        } else { //index berisi dari satu contact
            pointerContact pDeleteContact = pCariContact;
            if (pCariContact == pBantuIndex->firsContact) {     //delete first
                pDeleteContact = pBantuIndex->firsContact;
                pBantuIndex->firsContact = pBantuIndex->firsContact->next;
                pDeleteContact->next = NULL;
            }
            else if(pBantuIndex->next == NULL) { //delte last 
                pBeforeContact->next = NULL;
            }
            else {  //delte tengah
                pBeforeContact->next = pCariContact->next;
                pCariContact->next = NULL;
            }
        }
        cout << "Data berhasil di hapus!" << endl;
    }
    else {
        cout << "Data tidak ditemukan!" << endl;
    } 
}

void updateContact(listIndex& firstIndex){
    char keyContact[10];
    int status;
    pointerContact pCariContact;
    cout << "Masukkan nama : "; cin >> keyContact;

    //mencari index
    status = 0;
    pointerIndex pBantuIndex = firstIndex;
    while(pBantuIndex != NULL){
        if(pBantuIndex->index == keyContact[0]){        //ketemu!!
            break;
        }
        pBantuIndex = pBantuIndex->next;
    }
    

    if (status == 1) {
        //mencari contact dalam index yang sudah ditemukan
        linearSearchContact(pBantuIndex, status, keyContact, pCariContact);

        cout << "No Hp Baru : "; cin >> pCariContact->phone;
        cout << "Data berhasil di update!" << endl;
    }
    else {
        cout << "Data tidak ditemukan!" << endl;
    }
}

void traversal(pointerIndex firstIndex){
    pointerIndex pBantuIndex;
    pointerContact pBantuContact;

    pBantuIndex = firstIndex;

    while (pBantuIndex != NULL){ //loop index
        cout << "|- " << pBantuIndex->index << endl;
        pBantuContact = pBantuIndex->firsContact;
        while (pBantuContact != NULL){ //loop contact
            cout << "   |- " << pBantuContact->name << " / " << pBantuContact->phone << endl;
            pBantuContact = pBantuContact->next;
        }
        pBantuIndex = pBantuIndex->next;
    }
}

int main(){
    listIndex firstIndex;
    pointerContact pContact;
    pointerIndex pIndex;

    createListIndex(firstIndex);
    
    int menu;
    while(1){
        system("CLS");
        traversal(firstIndex);
        cout << "-----------------------------------" << endl;
        cout << "PHONE BOOK PROGRAM" << endl;
        cout << "-----------------------------------" << endl;
        cout << "MENU : " << endl;
        cout << "1. INSERT CONTACT" << endl;
        cout << "2. DELETE CONTACT" << endl;
        cout << "3. UPDATE CONTACT" << endl;
        cout << "4. EXIT " << endl;
        
        cout << "MASUKKAN MENU : "; cin >> menu;
        cout << endl;
        switch (menu){
            case 1:
                createElementContact(pContact);
                insertContact(firstIndex, pIndex, pContact);
                system("PAUSE");
                break;
            case 2:
                deleteContact(firstIndex);
                system("PAUSE");
                break;
            case 3:
                updateContact(firstIndex);
                system("PAUSE");
                break;
            case 4:
                return 0;
            default:
                cout << "MENU TIDAK TERSEDIA!" << endl << endl;
                system("PAUSE");
                break;
            }
    }
}
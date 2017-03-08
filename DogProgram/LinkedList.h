
#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <string.h>
using namespace std;

struct Entry {
    char Name[32];
    Entry * next;
    int index;
};

class LinkedList {
private:
    Entry * head;
    Entry * last;
    
    int length;
    
public:
    LinkedList();
    
    // Inserta un item al final de la lista
    void insertEntry( Entry * newEntry );
    
    // Removes an item from the list by item key.
    // Returns true if the operation is successful.
    bool removeEntry( char _name[32] );

    //Retorna un item de la lista, el primer nombre que encuentra.
    Entry * getEntry( char _name[32] );
    
    //Imprime todos los nombres que coinciden con el solicitado.
    void PrintAllEntries(char _name[32]);

    //Desplega el contenido de la lista
    void printList();
    
    int getLength();
    
    void Clear();

    ~LinkedList();

};

#endif
    string StringToUpper(string strToConvert) ;



#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <string.h>
using namespace std;

//*****************************************************************
// List items are keys with pointers to the next item.
//*****************************************************************
struct Entry {
    char Name[32];
    int index;
    Entry * next;
    // Entry(int i){ index = i;}
};

//*****************************************************************
// Linked lists store a variable number of items.
//*****************************************************************
class LinkedList {
private:
    // Head is a reference to a list of data nodes.
    Entry * head;
    Entry * last;
    
    // Length is the number of data nodes.
    int length;
    
public:
    // Constructs the empty linked list object.
    // Creates the head node and sets length to zero.
    LinkedList();
    
    // Inserts an item at the end of the list.
    void insertEntry( Entry * newEntry );
    
    // Removes an item from the list by item key.
    // Returns true if the operation is successful.
    bool removeEntry( char _name[32] );
    
    // Searches for an item by its key.
    // Returns a reference to first match.
    // Returns a NULL pointer if no match is found.
    Entry * getEntry( char _name[32] );
    
    // Displays list contents to the console window.
    void printList();
    
    // Returns the length of the list.
    int getLength();
    

    // De-allocates list memory when the program terminates.
    ~LinkedList();

};

#endif
    string StringToUpper(string strToConvert) ;

//*****************************************************************
// End of File
//*****************************************************************
#ifndef HashTable_h
#define HashTable_h

// #include "LinkedList.h"
#include "LinkedList.cpp"

class HashTable {
private:
    
    // Array is a reference to an array of Linked Lists.
    LinkedList * headsArray;
    
    // Length is the size of the Hash Table array.
    int tableLength;
    
    // Returns an array location for a given item key.
    int hash( char _name[32] );
    
public:
    
    HashTable( int _tableLength  );
    
    void Reset() ;
    
    // Adds an item to the Hash Table.
    void insertEntry( Entry * _newEntry , int _index);
    
    // Deletes an Item by key from the Hash Table.
    // Returns true if the operation is successful.
    bool removeEntry( char _name[32] );
    
    // Returns an item from the Hash Table by key.
    // If the item isn't found, a null pointer is returned.
    Entry * getEntryByName( char _name[32] );
    
    // Display the contents of the Hash Table to console window.
    double printTable();
    
    // Prints a histogram illustrating the Item distribution.
    double printHistogram();
    
    // Returns the number of locations in the Hash Table.
    int getLength();
    
    // Returns the number of Items in the Hash Table.
    int getNumberOfEntries();
    
    // De-allocates all memory used for the Hash Table.
    ~HashTable();
};

#endif

//*****************************************************************
// End of File
//*****************************************************************
//Contiene la definición clase HashTable .
//El arreglo de elementos consiste en una lista enlazada de objetos.
#include "HashTable.h"


//Constructor del objeto HashTable.
HashTable::HashTable( int _tableLength ) {
    if (_tableLength <= 0) 
        _tableLength = 4;
    headsArray = new LinkedList[ _tableLength ];
    tableLength = _tableLength;
}

void HashTable::Reset() {
    delete [] headsArray;
    headsArray = new LinkedList[ tableLength ];
}

// Returns an headsArray location for a given item key.
int HashTable::hash( char _name[32] ) {
    // unsigned long hash = 7; // =5
    // unsigned long hash = 13; // =6
    // unsigned long hash = 31; // =6
    // unsigned long hash = 37; // =5
    // unsigned long hash = 113; // =6
    // unsigned long hash = 127; // =3
    // unsigned long hash = 137; // =3
    // cout<<"SE PIDE HASH CON: "<<XX<<endl;
    // cout<<"SE PIDE HASH A: "<<_name<<endl;
    unsigned long hash = 196; // =3

    int result=0;
    int i = 0;
    while( _name[i] != '\0' ){
        hash = ((hash << 5) + hash) + toupper(_name[i] ); /* hash * 33 + c */
        i++;
    }
    // result = rand() % tableLength;
    // cout<<"-->: "<<tableLength<<endl;
    result = hash % tableLength;
    // cout<<"SE PIDE OBTIENE: "<<abs(result)<<endl;
    return abs(result);
}

// Adds an item to the Hash Table.
void HashTable::insertEntry( Entry * _newEntry , int _index) {
    // cout << " y "<<( _newEntry->Name)<<endl;
    int h = hash( _newEntry -> Name );
    // cout << " "<<h<<" "<<endl;
    Entry * newEntry = new Entry();
    memcpy(newEntry,_newEntry,sizeof(Entry));
    newEntry->index = _index;
    headsArray[ h ].insertEntry( newEntry );
    // headsArray[h].printList();

    /*
    */
}

// Deletes an Item by key from the Hash Table.
// Returns true if the operation is successful.
bool HashTable::removeEntry( char _name[32] ) {
    int index = hash( _name );
    return headsArray[ index ].removeEntry( _name );
}

// Returns an item from the Hash Table by key.
// If the item isn't found, a null pointer is returned.
Entry * HashTable::getEntryByName( char _name[32] ) {
    int index = hash( _name );
    cout << "--index: "<<index<<" "<<endl;

    return headsArray[ index ].getEntry( _name );
}

// Display the contents of the Hash Table to console window.
double HashTable::printTable() {
    double result =0;
    // cout << "\n\nHash Table:\n";
    for ( int i = 0; i < tableLength; i++ ) {
        // if (headsArray[i].getLength() >260) {
            cout << "------- [" << i  << "] --- ----";
            headsArray[i].printList();
            // result++;
        // }
    }
    return result;
}

// Prints a histogram illustrating the Item distribution.
double HashTable::printHistogram() {
    double empties =0;
    for ( int i = 0; i < tableLength; i++ ) {
        // if (headsArray[i].getLength() ==0) {
        //     empties ++;
        // }
        cout << i  << ":\t";
        for ( int j = 0; j < headsArray[i].getLength(); j++ )
            cout << " X";
        cout << "\n";
        /*
        */
    }
    // cout << "\n\nHash Table Contains ";
    cout << getNumberOfEntries() << " Items total\n";
    // cout <<empties << " Items vacios\n";
    return empties;
}

// Returns the number of locations in the Hash Table.
int HashTable::getLength() {
    return tableLength;
}

// Returns the number of Items in the Hash Table.
int HashTable::getNumberOfEntries() {
    int itemCount = 0;
    for ( int i = 0; i < tableLength; i++ ) {
        itemCount += headsArray[i].getLength();
    }
    return itemCount;
}

// De-allocates all memory used for the Hash Table.
HashTable::~HashTable() {
    delete [] headsArray;
}

//*****************************************************************
// End of File
//*****************************************************************
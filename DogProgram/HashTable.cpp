//Contiene la definición clase HashTable .
//El arreglo de elementos consiste en una lista enlazada de objetos.
#include "HashTable.h"


//Constructor del objeto HashTable.
HashTable::HashTable( int _tableLength ) {
    if (_tableLength <= 0) 
        _tableLength = 13;
    headsArray = new LinkedList[ _tableLength ];
    tableLength = _tableLength;
}


//Retorna una posición para un item dado.
int HashTable::hash( char _name[32] ) {
    unsigned long hash = 196; // =3
    int result=0;
    int i = 0;
    while( _name[i] != '\0' ){
        hash = ((hash << 5) + hash) + toupper(_name[i] ); /* hash * 33 + c */
        i++;
    }
    result = hash % tableLength;
    // cout<<"SE PIDE OBTIENE: "<<abs(result)<<endl;
    return abs(result);
}

//Limpia la tabla hash.
void HashTable::Reset() {
    delete [] headsArray;
    headsArray = new LinkedList[ tableLength ];
}

//Agrega un item a la tabla hash.
void HashTable::insertEntry( Entry * _newEntry , int _index) {
    int h = hash( _newEntry -> Name ); //Calcula la posición h a ubicarlo
    // cout << " "<<h<<" "<<endl;
    Entry * newEntry = new Entry();
    memcpy(newEntry,_newEntry,sizeof(Entry));
    newEntry->index = _index;
    headsArray[ h ].insertEntry( newEntry );// Lo agrega a la lista h.
}

bool HashTable::removeEntry( char _name[32] ) {
    int index = hash( _name );
    return headsArray[ index ].removeEntry( _name );
}

//Retorna un item de la tabla, el primer nombre que encuentra.
Entry * HashTable::getEntryByName( char _name[32] ) {
    int index = hash( _name );
    // cout << "--index: "<<index<<" "<<endl;
    return headsArray[ index ].getEntry( _name );
}

//Imprime todos los nombres que coinciden con el solicitado.
void HashTable::PrintAllEntriesByName( char _name[32]){
    int index = hash( _name ); //Calcula en que indice debería estar
    headsArray[ index ].PrintAllEntries( _name );   //Imprime los existentes en la lista correspondiente.
}

//Desplega el contenido de la tabla
double HashTable::printTable() {
    double result =0;
    for ( int i = 0; i < tableLength; i++ ) {
        // if (headsArray[i].getLength() >260) {
            cout << "------- [" << i  << "] --- ----";
            headsArray[i].printList();
            // result++;
        // }
    }
    return result;
}

//Imprime un histograma para ilustrar la distribución
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
    }
    // cout << "\n\nHash Table Contains ";
    // cout <<empties << " Items vacios\n";
    return empties;
}


int HashTable::getLength() {
    return tableLength;
}

// Retorna el número de items total que existen en la tabla
int HashTable::getNumberOfEntries() {
    int itemCount = 0;
    for ( int i = 0; i < tableLength; i++ ) {
        itemCount += headsArray[i].getLength();
    }
    return itemCount;
}

// Destructor
HashTable::~HashTable() {
    delete [] headsArray;
}


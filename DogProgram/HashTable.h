#ifndef HashTable_h
#define HashTable_h

#include "LinkedList.cpp"

class HashTable {
private:
    
    // La tabla es conformada por un arreglo de listas enlazadas
    LinkedList * headsArray;
    int tableLength;

    //Retorna una posición para un item dado.
    int hash( char _name[32] );
    
public:
    
    HashTable( int _tableLength  );
    
    //Limpia la tabla hash.
    void Reset() ;
    
    //Agrega un item a la tabla hash.
    void insertEntry( Entry * _newEntry , int _index);
    
    bool removeEntry( char _name[32] );
    
    //Retorna un item de la tabla, el primer nombre que encuentra.
    Entry * getEntryByName( char _name[32] );
    
    //Imprime todos los nombres que coinciden con el solicitado.
    void PrintAllEntriesByName( char _name[32]);

    //Desplega el contenido de la tabla
    double printTable();
    
    //Imprime un histograma para ilustrar la distribución
    double printHistogram();
    
    int getLength();
    
    // Retorna el número de items total que existen en la tabla
    int getNumberOfEntries();
    
    ~HashTable();
};

#endif


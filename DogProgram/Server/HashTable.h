#ifndef HashTable_h
#define HashTable_h

#include "LinkedList.cpp"
#define tableLength  1721
// #define tableLength  2

class HashTable {
private:
    
    // LinkedList * headsArray;
    // La tabla es conformada por un arreglo de listas enlazadas
    LinkedList headsArray[ tableLength ];

    //Retorna una posición para un item dado.
    int hash( char _name[32] );
    
public:
    
    HashTable( );
    
    //Limpia la tabla hash.
    void Reset() ;
    
    //Agrega un item a la tabla hash.
    void insertEntry( char _name[32] , int _index);
    
    bool removeEntry( char _name[32] );
    
    //Retorna un item de la tabla, el primer nombre que encuentra.
    Entry * getEntryByName( char _name[32] );
    
    //Imprime todos los nombres que coinciden con el solicitado.
    void PrintAllEntriesByName( char _name[32]);
    int SendAllEntriesByName( char _name[32] ,DataUser * _data );

    //Desplega el contenido de la tabla
    double printTable();
    
    //Imprime un histograma para ilustrar la distribución
    double printHistogram();
    
    int getLength();
    
    // Retorna el número de items total que existen en la tabla
    int getNumberOfEntries();
    
    void Clear() ;
    
    ~HashTable();


};

#endif


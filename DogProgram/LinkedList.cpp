
#include "LinkedList.h"

//Inicializa una lista vacía creando el espacio para el nodo principal, la "cabeza" de la lista 
LinkedList::LinkedList() {
    head = new Entry();
    last = new Entry();
    head -> next = NULL;
    last -> next = NULL;
    length = 0;
}

// Inserta un item al final de la lista
void LinkedList::insertEntry( Entry * newEntry ) {
    // cout<<"Insertado "<<newEntry->Name<<" con i : "<<newEntry->index<<endl;
    if (!head -> next) {
        head -> next = newEntry;
        last = newEntry;
        length++;
        return;
    }
    Entry * p = last;
    p -> next = newEntry;
    last =newEntry;
    newEntry -> next = NULL; 

    length++;
}

bool LinkedList::removeEntry( char _name[32] ) {
    return false;
}

//Retorna un item de la lista, el primer nombre que encuentra.
Entry * LinkedList::getEntry( char _name[32] ) {
    string _sName = _name;
    string pName ;
    Entry * p = head;
    Entry * q = head;
    while (q) {
        p = q;
        pName = p -> Name;
        // if ((p != head) && (p -> Name[0] == _name[0])){
        if ((p != head) && (StringToUpper( _sName) ==StringToUpper( pName)  )){
            return p;
        }
        q = p -> next;
    }
    return NULL;
}

 //Imprime todos los nombres que coinciden con el solicitado.
void LinkedList::PrintAllEntries(char _name[32]){
    string _sName = _name;
    string pName ;
    Entry * p = head;
    Entry * q = head;
    int matches =0;
    while (q) {
        p = q;
        pName = p -> Name;
        // if ((p != head) && (p -> Name[0] == _name[0])){
        if ((p != head) && (StringToUpper( _sName) ==StringToUpper( pName)  )){
            cout << 1+(p -> index)<<" : "<< p -> Name<<endl;
            matches ++;
        }
        q = p -> next;
    }
    printf("\nSe encontraron %i coincidencias. \n\n",matches );
}

//Desplega el contenido de la lista
void LinkedList::printList() {
    if (length == 0) {
        cout << "\n{ }\n";
        return;
    }
    Entry * p = head;
    Entry * q = head;
    cout << "\n{ ";
    while (q) {
        p = q;
        if (p != head) {
            cout << p -> index<<"-"<< p -> Name;
            // cout << p -> Name;
            if (p -> next) cout << ", ";
            else cout << " ";
        }
        q = p -> next;
    }
    cout << "}\n";
}

int LinkedList::getLength() {
    return length;
}

LinkedList::~LinkedList() {
    Entry * p = head;
    Entry * q = head;
    while (q) {
        p = q;
        q = p -> next;
        if (q) delete p;
    }
}

// Convierte un string a mayusculas
string StringToUpper(string strToConvert) {
    // cout<<" A CONVERTIR "<<strToConvert<<" en ";
    char result[32];
   for (int p = 0; p<strToConvert.length() ;p++)
        result[p] = toupper( strToConvert[p]);
    // cout<<result<<endl;
   return (string)result;
}



#include "LinkedList.h"
//Inicializa una lista vacía creando el espacio para el nodo principal, la "cabeza" de la lista 
LinkedList::LinkedList() {
    head = new Entry();
    last = new Entry();
    head -> next = NULL;
    last -> next = NULL;
    length = 0;
}

// Inserta un perro al final de la lista
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
    

    
    /*
    Entry * p = head;
    Entry * q = head;
    
    while (q) {
        p = q;
        q = p -> next;
    }
    p -> next = newEntry;
    newEntry -> next = NULL; 

    */
    length++;
}

// Removes an item from the list by item key.
// Returns true if the operation is successful.// MODIFICAR, NO SIRVE
bool LinkedList::removeEntry( char _name[32] ) {
    // if (!head -> next) return false;
    // Entry * p = head;
    // Entry * q = head;
    // while (q)
    // {
    //     if (q -> name == _name)
    //     {
    //         p -> next = q -> next;
    //         delete q;
    //         length--;
    //         return true;
    //     }
    //     p = q;
    //     q = p -> next;
    // }
    return false;
}

// Searches for an item by its key.
// Returns a reference to first match.
// Returns a NULL pointer if no match is found.
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

// Displays list contents to the console window.
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
            cout << p -> index;
            // cout << p -> Name;
            if (p -> next) cout << ", ";
            else cout << " ";
        }
        q = p -> next;
    }
    cout << "}\n";
}

// Returns the length of the list.
int LinkedList::getLength() {
    return length;
}

// De-allocates list memory when the program terminates.
LinkedList::~LinkedList() {
    Entry * p = head;
    Entry * q = head;
    while (q) {
        p = q;
        q = p -> next;
        if (q) delete p;
    }
}

string StringToUpper(string strToConvert) {
    cout<<" A CONVERTIR "<<strToConvert<<" en ";
    char result[32];
   for (int p = 0; p<strToConvert.length() ;p++)
        result[p] = toupper( strToConvert[p]);
    cout<<result<<endl;
   return (string)result;
}

//*****************************************************************
// End of File
//*****************************************************************
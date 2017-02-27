// #include <string.h>
// #include <iostream>
// using namespace std;

#include "HashTable.cpp"
#include "dogType.h"

int main() {
    // int mXX=127;
    int dSize = sizeof(dogType);
    dogType buffer;
    

    FILE * dataFile;
    dataFile = fopen("dataDogs.dat", "r");
    if (dataFile == NULL){
        perror("Error al leer el archivo dataDogs \n");
        exit(-1);
    }

    Entry *entry = new Entry;
    

         HashTable table =HashTable(13);
         // HashTable table =HashTable(1721);
         // HashTable table =HashTable(104729);

    /* 
    */
        int index = 0;
        while(fread((void*)&buffer,dSize,1,dataFile) ==1){
            memcpy(entry->  Name, buffer.Name,sizeof(char[32]));
            // cout<<"__Leido__: "<<buffer.Name<<" : "<<endl;
            table.insertEntry(entry,index);
            index++;
            if (index == 1000) {
                // break;
            }
        }
        fclose(dataFile);
        free(entry);

    /* 

        int movedP = fseek( dataFile, 3*sizeof(dogType), SEEK_SET);
    if (movedP != 0){
        perror("El reinicio del apuntador no se logró correctamente.");
        exit(-1);
    }


        // for (int index = 1; index < 1000000; ++index) {
        for (int index = 1; index < 80549; ++index) {
            fread((void*)&buffer,dSize,1,dataFile);
            // cout<<"__Leido__: "<<buffer.Name<<" : ";
            memcpy(entry->  Name, buffer.Name,sizeof(char[32]));
            table.insertEntry(entry,index);
        }
    */

        // table.printTable();
        // table.printHistogram();

        // double an= table.printTable();
        
        // // Remove one item from Hash Table.
        // // table.removeItem("Apple");
        // // table.printTable();
        
        // table.printTable();
        // table.printHistogram();
        
        // // Look up an item in the hash table
        char nameToSearch[32] = "Antonio'";
        // char nameToSearch[32] = "Antonio";
        Entry * result = table.getEntryByName(nameToSearch);
        cout << "AQUI RESULTA: "<<result -> Name << endl;
        // cout << "AQUI RESULTA: "<<nameToSearch << endl;
        int in;
        cin>>in;
        // return 0;
}
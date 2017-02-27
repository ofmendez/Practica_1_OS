#include "HashTable.cpp"
#include "view.cpp"
// #include "dogType.h"

int main(){
	LoadDataProgram();

	ShowMainMenu();


      char nameToSearch[32] = "Fabian";
      Entry * result = table.getEntryByName(nameToSearch);
      cout << "AQUI RESULTA: "<<result -> Name << endl;
}

void LoadDataProgram(){
	table.Reset();

	int dSize = sizeof(dogType);
	char m[20] = "Cargando...";
  	Entry *entry = new Entry();
	dogType buffer;
	FILE * dataFile = GetReadDataFile();

	ShowMessage(m);


	// HashTable table =HashTable(1721);

	int index = 0;
	while(fread((void*)&buffer,dSize,1,dataFile) ==1){
		memcpy(entry->  Name, buffer.Name,sizeof(char[32]));
		cout<<"__Leido__: "<<buffer.Name<<" : "<<endl;
		table.insertEntry(entry,index);
		index++;
		if (index == 1000) {/* break; */}
	}
      // table.printTable();
      // table.printHistogram();
	fclose(dataFile);
	free(entry);
}


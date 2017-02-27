#include "HashTable.cpp"
#include "view.cpp"

int main(){
	LoadDataProgram();
	ShowMainMenu();
}

//Carga los datos del .dat para crear la tabla hash.
void LoadDataProgram(){
	FILE * dataFile = GetReadDataFile();
  	Entry *entry = new Entry();
	int dSize = sizeof(dogType);
	dogType buffer;

	table.Reset(); //Asegura que la tabla hash esté vacía.

	char m[20] = "Cargando...";
	ShowMessage(m); //Despliega un mensaje mientras se inicializa la tabla

	int index = 0;//Se leen todos los campos del .dat y se llena la tabla.
	while(fread((void*)&buffer,dSize,1,dataFile) ==1){
		memcpy(entry->  Name, buffer.Name,sizeof(char[32]));
		table.insertEntry(entry,index);
		index++;
	}
	fclose(dataFile);
	free(entry);
}


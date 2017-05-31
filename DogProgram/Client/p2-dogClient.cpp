#include "HashTable.cpp"
#include "view.cpp"

#include <iostream>    
#include <strings.h>
#include <unistd.h>

#define PORT 3535

void ConnectToServer(){
	int  r;
	struct sockaddr_in   clientAddr;
	int sizeCli;
	
	if (clientSocketFd == -1) { perror("Error socket: ") ;}
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(PORT);
	clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //argv[1]  ./client 123.123.123.123
	bzero(clientAddr.sin_zero , 8);
	sizeCli = sizeof( clientAddr);

	r = connect(clientSocketFd, (struct sockaddr *)&clientAddr,  sizeCli  );
	if (r == -1) { perror("Error connecting to server: ") ;}
}



int main(){
	char m[20] = "Conectando...";
	ShowMessage(m);
	sleep(0.1);
	ConnectToServer();
	
	// r = send(clientSocketFd, "hola Fabian y Camilo 1",24,0    );
	// if (r != 11) { perror("Error sending all: ") ;}

	// sleep(4);

	// r = send(clientSocketFd, "hola Fabian y Camilo  2",24,0    );
	// if (r != 11) { perror("Error sending all: ") ;}

	// HashTable mtable =HashTable(); 
	// LoadDataProgram();
	ShowMainMenu();
	close(clientSocketFd);
	// table.FF();
}


//Carga los datos del .dat para crear la tabla hash.
void LoadDataProgram(){
	FILE * dataFile = GetReadDataFile();
  	// Entry *entry = new Entry();
	int dSize = sizeof(dogType);
	dogType buffer;

	table.Clear(); //Asegura que la tabla hash esté vacía.

	char m[20] = "Cargando...";
	ShowMessage(m); //Despliega un mensaje mientras se inicializa la tabla

	int index = 0;//Se leen todos los campos del .dat y se llena la tabla.
	while(fread((void*)&buffer,dSize,1,dataFile) ==1){
		// memcpy(entry->  Name, buffer.Name,sizeof(char[32]));
		table.insertEntry(buffer.Name,index);
		index++;
	}
	fclose(dataFile);
	// table.Clear(); //Asegura que la tabla hash esté vacía.
	// free(entry);
}


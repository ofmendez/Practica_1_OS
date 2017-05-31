#include "HashTable.cpp"
#include "view.cpp"

#include <netinet/in.h>    
#include <netdb.h>    
#include <sys/types.h>    
#include <sys/socket.h>    
#include <arpa/inet.h>    
#include <strings.h>
#include <iostream>    
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;
// #include "Util.h"


#define PORT 3535
#define BACKLOG 10
#define THREADS 32



int WaitState(DataUser *_data){
	int nextState = 0;
	packageInfo infoReceived ;
	int rc = recv (_data->clientFd , &infoReceived  , sizeof(packageInfo), 0);
      // printf("Recieve =%i\n",rc); 
     	if (rc<=0)
      	return -1;
      nextState = infoReceived.state;
	return nextState;
}

bool IngressState(DataUser * _data){
	dogType dogReceived ;
	int rc = recv (_data->clientFd , &dogReceived  , sizeof(dogType), 0);
     	if (rc<=0)
      	return false;
	printf(" TODO://  INGRESAR PERRO AL ARCHIVO \n"); 
	printf(" se puede ingresar a -> %s \n",dogReceived.Name); 
	return true;
}

bool SearchState(DataUser * _data){
	packageInfo infoReceived ;
	packageInfo infoToSend ;
	
	//Enviar el número de entradas.
	infoToSend.index =  table.getNumberOfEntries();
	int r = send( _data->clientFd, &infoToSend, sizeof(packageInfo), 0 );
	
	// Recive el nombre del registro a borrar
	int rc = recv (_data->clientFd , &infoReceived  , sizeof(packageInfo), 0);
     	if (rc<=0 )
      		return false;
      	int matches = table.SendAllEntriesByName( infoReceived.toSearch, _data ); 
	
	infoToSend.index =  0;
	infoToSend.state =  matches;
	r = send(_data->clientFd, &infoToSend, sizeof(packageInfo), 0 );
	//Recibe el nombre del perro a buscar
}

bool DeleteState(DataUser * _data){

	packageInfo infoReceived ;
	packageInfo infoToSend ;
	
	//Enviar el número de entradas.
	infoToSend.index =  table.getNumberOfEntries();
	int r = send( _data->clientFd, &infoToSend, sizeof(packageInfo), 0 );

	// Recive el indice del registro a borrar
	int rc = recv (_data->clientFd , &infoReceived  , sizeof(packageInfo), 0);
     	if (rc<=0 )
      		return false;

  	FILE * dataFile = GetReadDataFile();
	dogType buffer;

	SetPositionInEndFile(dataFile,-1); // Va a la ultima posición del archivo.
	fread((void*)&buffer,sizeof(dogType),1,dataFile) ;//Lee la última posición en un buffer.
	SetPositionInFile(dataFile, infoReceived.index);   //Va a la posición que el usuario desea borrar
	WriteDogToFile(buffer, dataFile); //Escribe el buffer en la posición para sobre-escribirla
      
      DeleteLastItem(dataFile);
	
	LoadDataProgram();
	infoToSend.index =  1;
	r = send(_data->clientFd, &infoToSend, sizeof(packageInfo), 0);
	// char msg[20] = "Hecho...";
	// ShowMessage(msg); 
	
}

bool ViewState(DataUser * _data){

	FILE * mrFile = GetMedicalRecordFile();

	packageInfo infoReceived ;
	packageInfo infoToSend ;
	dogType buffer;

	//Enviar el número de entradas.
	infoToSend.index =  table.getNumberOfEntries();
	int r = send( _data->clientFd, &infoToSend, sizeof(packageInfo), 0 );
	// printf("SE ENCONTRARON  %i PERROS EN LA BD.\n",  table.getNumberOfEntries() );

	// Recive el indice del registro a visualizar
	int rc = recv (_data->clientFd , &infoReceived  , sizeof(packageInfo), 0);
     	if (rc<=0 )
      		return false;
	if(infoReceived.index == -1 || infoReceived.state != 2){
		printf(" problemas recibiendo del cliente %i en estado 2 recibe estado: %s\n", _data->clientIndex, infoReceived.state );
   	   	return false;
	}

	FILE * dataFile = GetReadDataFile();
	//Lleva el puntero al registro solicitado dentro del .dat.
	SetPositionInFile(dataFile,infoReceived.index);
	fread((void*)&buffer,sizeof(dogType),1,dataFile) ;
      	
	fprintf(mrFile, "~~~~ HISTORIA CLINICA~~~~ \n \n Nombre: %s \n Tipo:   %s \n Edad:   %i \n Raza:   %s \n Altura: %i \n Peso:   %2.2f \n Sexo:   %c ",
	buffer.Name, buffer.Type, buffer.Age, buffer.Breed, buffer.Heigth, buffer.Weigth, buffer.Sex );

	rewind( mrFile );

	int sended ,bytesRead= 0;
	infoToSend.index =  1;
	while( !feof(mrFile)  )  {
		bytesRead = fread(infoToSend.toSearch , sizeof(char[32])-1, 1, mrFile);
		sended += send(_data->clientFd, &infoToSend, sizeof(packageInfo), 0);
		memcpy(infoToSend.toSearch, "",sizeof(char[32]));
	} 

	infoToSend.index =  0;
	r = send(_data->clientFd, &infoToSend, sizeof(packageInfo), 0 );
	fclose(mrFile);
	return true;
}

void * ProcessClient(void *_data){
	DataUser *data;
	data = (DataUser*)_data;
	int state = 0;

	printf("Cliente %i conectado desde ip: %s \n ",data->clientIndex, data->clientIP); 

	while( state >= 0){
		switch (state) {
		    case 0:
			printf("Cliente %i En estado: %i \n ",data->clientIndex, 0); 
		    	state = WaitState(data);
		      break;
		    case 1:
			printf("Cliente %i En estado: %i \n ",data->clientIndex, 1); 
		    	 state = IngressState(data) ? 0 : -1;
		      break;
    		    case 2:
			printf("Cliente %i En estado: %i \n ",data->clientIndex, 2); 
		    	 state = ViewState(data) ? 0 : -1;
		      break;
    		    case 3:
			printf("Cliente %i En estado: %i \n ",data->clientIndex, 3); 
		    	 state = DeleteState(data) ? 0 : -1;
		      break;
    		    case 4:
			printf("Cliente %i En estado: %i \n ",data->clientIndex, 4); 
		    	 state = SearchState(data)? 0 : -1;
		      break;
		    default:
		      break;
		}
		// int rc = recv (data->clientFd , &dogReceived  , sizeof(dogType), 0);
	}
	
	printf(" Cliente %i  desconectado.\n",data->clientIndex);
	close(data->clientFd); 

}

int serverSocketFd ;

void CreateConnection(){
	int r;
	int clientFds [THREADS];
	DataUser dataUser [THREADS];
	pthread_t dOfThread [THREADS];
	struct sockaddr_in  serverAddr, clientAddr;
	size_t sizeStAddr = sizeof( struct sockaddr_in);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY; //-> ip por donde se va a servir
	bzero(serverAddr.sin_zero , 8);   


	serverSocketFd =  socket(AF_INET , SOCK_STREAM, 0);
	if (serverSocketFd == -1) { perror("Error socket.") ;}

	r = bind(serverSocketFd, (struct sockaddr*)&serverAddr ,  sizeStAddr);
	if (r== -1) {perror("Error bind."); }

	r= listen (serverSocketFd, BACKLOG);
	if (r== -1) {perror("Error listen.");}
	
	int attempt =0;


	while(clientFds[attempt] = accept( serverSocketFd ,  (struct sockaddr*)&clientAddr,  (socklen_t *)&sizeStAddr )   ){
		printf("------------ Conexion cliente [%i] ------------ \n",  attempt  );

 		sprintf(dataUser[attempt].clientIP, "%d.%d.%d.%d", int( clientAddr.sin_addr.s_addr&0xFF), int((clientAddr.sin_addr.s_addr&0xFF00)>>8), int((clientAddr.sin_addr.s_addr&0xFF0000)>>16), int((clientAddr.sin_addr.s_addr&0xFF000000)>>24));
		dataUser[attempt].clientFd = clientFds[attempt];
		dataUser[attempt].clientIndex = attempt+1;
		
		r= pthread_create(&dOfThread[attempt], NULL, ProcessClient, (void*)&dataUser[attempt] );
		if (r!=0) {perror("Error create."); }
		attempt ++;
		if (attempt == THREADS) {
			printf("------------ Límite de conexiones alcanzado  ------------ \n"  );
			break;
		}
	}
}
int main(){
	LoadDataProgram();
	CreateConnection();
	// HashTable mtable =HashTable(); 
	// close(serverSocketFd);
	// ShowMainMenu();
	// table.FF();
}

//Carga los datos del .dat para crear la tabla hash.
void LoadDataProgram(){
	FILE * dataFile = GetReadDataFile();
  	// Entry *entry = new Entry();
	int dSize = sizeof(dogType);
	dogType buffer;

	table.Clear(); //Asegura que la tabla hash esté vacía.

	// char m[20] = "Cargando...";
	// ShowMessage(m); //Despliega un mensaje mientras se inicializa la tabla

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



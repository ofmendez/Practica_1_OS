#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <arpa/inet.h>    
#include "view.h"
#include "Util.h"
using namespace std;

// HashTable table =HashTable(13);
int clientSocketFd =  socket(AF_INET , SOCK_STREAM, 0);
HashTable table =HashTable();  // Crea la tabla hash con N numero de espacios.
// HashTable *table ;


//Elige qué  función desplegar dependiendo de la opción elegida por el uduario.
void LaunchDisplay( int _v){
	system("clear");
	switch (_v) {
		case 1: Display1Ingress(); break;
		case 2: Display2View(); break;
		case 3: Display3Delete(); break;
		case 4: Display4Search(); break;
		case 5: Display5Exit(); break;
	     default:
	     		printf("ERROR!\n");
	}
}

//Despliega el menú principal y solicita una entrada válida del usuario.
void ShowMainMenu(){
	char n=0;
	// cout<<"es: "<<sizeof(LinkedList);
	do{
		system("clear");
		printf("~~~~~~~VETERINARIA OFMENDEZ ~~~~~~~\n");
		printf(  "~   \t\t\t\t ~ \n");
		printf(  "~   1. Ingresar registro.\t ~ \n");
		printf(  "~   2. Ver registro.\t\t ~ \n");
		printf(  "~   3. Borrar registro.\t\t ~ \n");
		printf(  "~   4. Buscar registro.\t\t ~ \n");
		printf(  "~   5. Salir.\t\t\t ~ \n");
		printf(  "~   \t\t\t\t ~ \n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("Please enter # of menu: \n");
		scanf("%c",&n);
		while (getchar()!='\n');
	} while( !isdigit(n) || (n-'0')<1 || (n-'0') >5);
	LaunchDisplay((n-'0'));
}

//Espera a que oprima ENTER para continuar.
bool UserContinue(){
	printf("Operación finalizada...\n");
	printf("Presione ENTER para continuar.");
	while(getchar() != '\n');
	printf("\n");
	ShowMainMenu(); //Regresa al menú principal.
}

// *********************************************
// *******             DISPLAYS             *************
// *********************************************

//Función de ingresar un registro.
void Display1Ingress(){
	char name[32];
	char type[32];
	int age;
	char breed[16];
	int heigth;
	float weigth;
	char sex;
	printf("~~~~INGRESANDO HISTORIA CLINICA~~~\n");
	printf("Ingresa el nombre: \n"); scanf("%s", &name); while (getchar()!='\n');
	printf("Ingresa el tipo: \n"); scanf("%s", &type); while (getchar()!='\n');
	printf("Ingresa la edad: \n"); scanf("%i", &age); while (getchar()!='\n');
	printf("Ingresa la raza: \n"); scanf("%s", &breed); while (getchar()!='\n');
	printf("Ingresa la altura(cm): \n"); scanf("%i", &heigth); while (getchar()!='\n');
	printf("Ingresa la peso(Kg): \n"); scanf("%f", &weigth); while (getchar()!='\n');
	printf("Ingresa la sexo(F/M): \n"); scanf("%c", &sex); while (getchar()!='\n');
	sex = (sex =='F' || sex =='f')?'F' :'M';
	ConfirmDataToRegister(name, type, age, breed, heigth, weigth, sex);
	UserContinue();	
}


int GetNumberOfEntries(int _s){
	int result = 0;
	
	packageInfo infoToSend ;
	packageInfo infoToRecieve ;

	infoToSend.state = _s;
	infoToSend.index = 1;
	//Envia el estado en el que está
	int r = send(clientSocketFd, &infoToSend, sizeof(packageInfo), 0 );

	//Recibe el número de entradas en  la BD.
	int rc = recv (clientSocketFd , &infoToRecieve  , sizeof(packageInfo), 0);
	
	// printf("RECIBIDO UN TOTAL DE : %i\n", infoToRecieve.index );
	result = infoToRecieve.index;

	return result;
	// r = send(clientSocketFd, &infoToSend, sizeof(packageInfo), 0 );
}

//Función de visualizar un registro.
void Display2View(){
	int numberOfEntries = GetNumberOfEntries(2);
	int n=0;
	do{
		system("clear");
		printf("~~~~~~~VETERINARIA OFMENDEZ~~~~~~~\n");
		printf(  "~   \t\t\t\t ~ \n");
		printf(  "~    Registrados actualmente \t ~ \n");
		printf(  "~   \t  %i Animales.\t\t  \n",numberOfEntries);
		printf(  "~   \t\t\t\t ~ \n");
		printf(  "~   \t Digita el registro \t ~ \n");
		printf(  "~   \t  que deseas ver   \t ~ \n");
		printf(  "~   \t\t\t\t ~ \n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("Ver: \n");
		scanf("%i",&n);
		while (getchar()!='\n');
	} while(  n<1 || n >numberOfEntries );
	ViewRegister(n-1);
	UserContinue();
}

//Función de Borrar un registro.
void Display3Delete(){
	int numberOfEntries = GetNumberOfEntries(3);
	int n=0;
	do{
		system("clear");
		printf("~~~~~~~VETERINARIA OFMENDEZ~~~~~~~\n");
		printf(  "~   \t\t\t\t ~ \n");
		printf(  "~    Registrados actualmente \t ~ \n");
		printf(  "~   \t  %i Animales.\t\t  \n",numberOfEntries);
		printf(  "~   \t\t\t\t ~ \n");
		printf(  "~   \t Digita el registro \t ~ \n");
		printf(  "~   \tque deseas  BORRAR.\t ~ \n");
		printf(  "~   \t\t\t\t ~ \n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("Borrar: \n");
		scanf("%i",&n);
		while (getchar()!='\n');
	} while(  n<1 || n >numberOfEntries );
	DeleteRegisterInServer(n-1);
	UserContinue();
}

void PrintAllEntriesByNameFromServer(char _name[32]){
	packageInfo infoToSend ;
	packageInfo infoToRecieve  ;

	memcpy(infoToSend.toSearch, _name, sizeof(char[32]));
	//Envía el nombre que quiere buscar
	int r = send(clientSocketFd, &infoToSend, sizeof(packageInfo), 0 );


	while(true) {
		r = recv(clientSocketFd, &infoToRecieve, sizeof(packageInfo), 0);
		if(r == -1) {
			perror("ERROR EN RECEPCION DE RESULTADOS.\n");
			break;
		}
		if (!infoToRecieve.index )
			break;
		printf("%i : %s \n" , infoToRecieve.state , infoToRecieve.toSearch);
      }

    	printf("\nSe encontraron %i coincidencias. \n\n",infoToRecieve.state );

}

//Funcion de Buscar un registro.
void Display4Search(){
	int numberOfEntries = GetNumberOfEntries(4);
	char name[32];
	system("clear");
	printf("~~~~~~~VETERINARIA OFMENDEZ~~~~~~~\n");
	printf(  "~   \t\t\t\t ~ \n");
	printf(  "~    Registrados actualmente \t ~ \n");
	printf(  "~   \t  %i Animales.\t\t  \n",numberOfEntries);
	printf(  "~   \t\t\t\t ~ \n");
	printf(  "~   \t Digita el nombre \t ~ \n");
	printf(  "~   \tque deseas  BUSCAR.\t ~ \n");
	printf(  "~   \t\t\t\t ~ \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Buscar: \n");
	scanf("%s",&name);
	while (getchar()!='\n');
	system("clear");
	printf("RESULTADOS PARA \"%s \" : \n\n",name);
	PrintAllEntriesByNameFromServer( name );
       // table.PrintAllEntriesByName( name ); //Despliega todas las entradas que coinciden con el nombre
	UserContinue();
}



//Función salir del programa.
void Display5Exit(){
	char msg[20] = "      ADIOS!";
	ShowMessage(msg);
} 
// *********************************************
// *******             END DISPLAYS             ********
// *********************************************


//Borra el registro seleccionado.
void DeleteRegisterInServer(int _p1){
	packageInfo infoToSend ;
	packageInfo infoToRecieve ;

	infoToSend.index = _p1;
	//Envía el indice que quiere borrar
	int r = send(clientSocketFd, &infoToSend, sizeof(packageInfo), 0 );

	r = recv(clientSocketFd, &infoToRecieve, sizeof(packageInfo), 0);
	if (!infoToRecieve.index) 
		perror("Error en el borrado del registro. \n");

	char msg[20] = "Hecho...";
	ShowMessage(msg); 

}

//Borra el registro seleccionado.
void DeleteRegister(int _p1){
	FILE * dataFile = GetReadDataFile();
	dogType buffer;

	SetPositionInEndFile(dataFile,-1); // Va a la ultima posición del archivo.
	fread((void*)&buffer,sizeof(dogType),1,dataFile) ;//Lee la última posición en un buffer.
	SetPositionInFile(dataFile, _p1);   //Va a la posición que el usuario desea borrar
	WriteDogToFile(buffer, dataFile); //Escribe el buffer en la posición para sobre-escribirla
      
      DeleteLastItem(dataFile);
	
	LoadDataProgram();
	char msg[20] = "Hecho...";
	ShowMessage(msg); 
}

//Borra el último item de un archivo.
void DeleteLastItem(FILE * _file){
	int finalSize =table.getNumberOfEntries()-1  ; //Items del nuevo archivo
	printf("Es: %i\n", finalSize);
	char msg[20] = "Borrando...";
	ShowMessage(msg); 

	SetPositionInFile(_file,0);
	//Trunca el archivo eliminando el último registro
	if (ftruncate(fileno(_file), finalSize *sizeof(dogType) ) != 0){ 
		perror("Error en el borrado del registro. \n");
		exit(-1);
	}else{
		// cout <<"HRY";
		// cin>>r;
	}
	fclose(_file);
}


//Busca, Lee y despliega el registro solicitado en un .txt.
void ViewRegister(int _p1){
	packageInfo infoToSend ;
	packageInfo infoToRecieve ;

	FILE * mrFile = GetMedicalRecordFile();


	infoToSend.state = 2;
	infoToSend.index = _p1;

	//Envía el indice que quiere "VER"
	int r = send(clientSocketFd, &infoToSend, sizeof(packageInfo), 0 );
	int totalRecieve = 0;
	while(true) {
		r = recv(clientSocketFd, &infoToRecieve, sizeof(packageInfo), 0);
		if (!infoToRecieve.index) 
			break;
		fprintf(mrFile, "%s",infoToRecieve.toSearch );
		memcpy(infoToSend.toSearch, "",sizeof(char[32]));
      }

	fclose(mrFile);
	system("nano medicalRecord.txt");

	// printf("Presione ENTER para actualizar historia clinica.");
	// while(getchar() != '\n');
	// printf("\n");
}


//Busca, Lee y despliega el registro solicitado en un .txt.
void OLDViewRegister(int _p1){
	FILE * dataFile = GetReadDataFile();
	FILE * mrFile = GetMedicalRecordFile();
	dogType buffer;
	//Lleva el puntero al registro solicitado dentro del .dat.
	SetPositionInFile(dataFile,_p1);
	fread((void*)&buffer,sizeof(dogType),1,dataFile) ;

	//Escribe los datos de la historia clinica en el TXT, libera los archivos
	fprintf(mrFile, "~~~~ HISTORIA CLINICA~~~~ \n \n Nombre: %s \n Tipo:   %s \n Edad:   %i \n Raza:   %s \n Altura: %i \n Peso:   %2.2f \n Sexo:   %c ",
	buffer.Name, buffer.Type, buffer.Age, buffer.Breed, buffer.Heigth, buffer.Weigth, buffer.Sex );
	fclose(mrFile);
	fclose(dataFile);
	//Abre en editor el TXT
	system("nano medicalRecord.txt");
}


//Despliega los datos que se van a guardar y pide confirmación al usuario.
void ConfirmDataToRegister(char _n[32], char _t[32], int _a, char _b[16], int _h, float _w, char _s ){
	char op;
	system("clear");
	printf("~~~~~~ DATOS A INGRESAR ~~~~~\n");
	printf(" nombre: %s\n",  _n);
	printf(" tipo: \t %s\n",  _t);
	printf(" edad: \t %d\n",  _a);
	printf(" raza: \t %s\n",  _b);
	printf(" altura: %d\n",  _h);
	printf(" peso: \t %f\n",  _w);
	printf(" sexo: \t %c\n\n",  _s);
	printf(" Registrar estos datos? (S/N): \n");
	scanf("%c", &op); while (getchar()!='\n');

	if (op == 'Y' || op == 'y' || op == 'S' || op == 's' || op == 'N' || op == 'n' ) {
		if (op == 'N' || op == 'n') {
			char msg[20] = "Registro cancelado!";
			ShowMessage(msg);
		}else{
			// RegisterDog(_n, _t, _a, _b, _h, _w, _s); //Guarda el nuevo registro
			RegisterDogInServer(_n, _t, _a, _b, _h, _w, _s); //Guarda el nuevo registro
		}
	}else{
		ConfirmDataToRegister(_n, _t, _a, _b, _h, _w, _s); //Permanece hasta que exista una entrada válida.
	}
}

//Guarda el nuevo registro.
void RegisterDogInServer(char _n[32], char _t[32], int _a, char _b[16], int _h, float _w, char _s ){
	packageInfo infoToSend ;
	infoToSend.state = 1;
	infoToSend.index = 1;
	int r = send(clientSocketFd, &infoToSend, sizeof(packageInfo), 0 );
	dogType newDog;
	
  	// Entry *entry = new Entry();
 	// FILE * fData= GetDataFileAppend();
 	//Llena la nueva estructura con los datos que ingresó el usuario.
	memcpy( newDog.Name , _n, sizeof(char[32])  );
	// memcpy( entry->Name , _n, sizeof(char[32])  );
	memcpy( newDog.Type  ,  _t, sizeof(char[32]) );
	newDog.Age = _a;
	memcpy(newDog.Breed  , _b, sizeof(char[16]) );
	newDog.Heigth  = _h;
	newDog.Weigth = _w;
	newDog.Sex = _s;
	printf("ENVIO AL PERRO: %s\n", newDog.Name );
	r = send(clientSocketFd, &newDog,sizeof(dogType),0    );
	sleep(1);
	// table.insertEntry(_n,table.getNumberOfEntries());//Ingresa a la tabla hash
	// WriteDogToFile(newDog, fData);//Escribe al archivo .dat
	// fclose(fData);
	// char msg[20] = "  Registrado!!";
	// ShowMessage(msg);
}

//Despliega un mensaje al usuario
void ShowMessage(char _msg[16]){
	system("clear");
	printf("~~~~~~~VETERINARIA OFMENDEZ~~~~~~~\n");
	printf(  "~   \t\t\t\t ~ \n");
	printf(  "~   \t\t\t\t ~ \n");
	printf(  "~   \t\t\t\t ~ \n");
	printf(  "   \t%s\t  \n",_msg);
	printf(  "~   \t\t\t\t ~ \n");
	printf(  "~   \t\t\t\t ~ \n");
	printf(  "~   \t\t\t\t ~ \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
} 

//Establece el apuntador del archivo a la posiciń dada relativa al inicio del archivo.
void SetPositionInFile(FILE *_file ,int _p){
      int movedP = fseek( _file, _p*sizeof(dogType), SEEK_SET);
	if (movedP != 0){
		perror("El reinicio del apuntador no se logró correctamente.");
		exit(-1);
	}
}

//Establece el apuntador del archivo a la posiciń dada relativa al final del archivo.
void SetPositionInEndFile(FILE *_file ,int _p){
      int movedP = fseek( _file, _p*sizeof(dogType), SEEK_END);
	if (movedP != 0){
		perror("El reinicio del apuntador no se logró correctamente.");
		exit(-1);
	}
}
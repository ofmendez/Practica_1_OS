#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>

#include "view.h"
#include "Util.h"
using namespace std;
HashTable table =HashTable(13);

void LaunchDisplay( int _v){
	// system("clear");
	switch (_v) {
		case 1:
			Display1Ingress(); break;
		case 2:
			Display2View(); break;
		case 3:
			Display3Delete(); break;
		case 4:
			Display4Search(); break;
		case 5:
			Display5Exit(); break;
	     default:
	     		printf("ERROR!\n");
 			// ShowMainMenu();
	}

}

void ShowMainMenu(){
	char n=0;
	do{
		// system("clear");
		printf("~~~~~~~VETERINARIA OFMENDEZ~~~~~~~\n");
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

bool UserContinue(){
	printf("Operación finalizada...\n");
	printf("Presione ENTER para continuar.");
	while(getchar() != '\n');
	printf("\n");
	ShowMainMenu();
}


void Display1Ingress(){

	printf("~~~~INGRESANDO HISTORIA CLINICA~~~\n");
	char name[32];
	char type[32];
	int age;
	char breed[16];
	int heigth;
	float weigth;
	char sex;
	printf("Ingresa el nombre: \n");
	scanf("%s", &name); while (getchar()!='\n');
	printf("Ingresa el tipo: \n");
	scanf("%s", &type); while (getchar()!='\n');
	printf("Ingresa la edad: \n");
	scanf("%i", &age); while (getchar()!='\n');
	printf("Ingresa la raza: \n");
	scanf("%s", &breed); while (getchar()!='\n');
	printf("Ingresa la altura(cm): \n");
	scanf("%i", &heigth); while (getchar()!='\n');
	printf("Ingresa la peso(Kg): \n");
	scanf("%f", &weigth); while (getchar()!='\n');
	printf("Ingresa la sexo(F/M): \n");
	scanf("%c", &sex); while (getchar()!='\n');
	sex = (sex =='F' || sex =='f')?'F' :'M';
	ConfirmDataToRegister(name, type, age, breed, heigth, weigth, sex);
	UserContinue();	
}

void Display2View(){
	int n=0;
	do{
		// system("clear");
		printf("~~~~~~~VETERINARIA OFMENDEZ~~~~~~~\n");
		printf(  "~   \t\t\t\t ~ \n");
		printf(  "~    Registrados actualmente \t ~ \n");
		printf(  "~   \t  %i Animales.\t\t ~ \n",table.getNumberOfEntries());
		printf(  "~   \t\t\t\t ~ \n");
		printf(  "~   \t Digita el registro \t ~ \n");
		printf(  "~   \t  que deseas ver   \t ~ \n");
		printf(  "~   \t\t\t\t ~ \n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("Ver: \n");
		scanf("%i",&n);
		while (getchar()!='\n');
	} while(  n<1 || n >table.getNumberOfEntries() );
	ViewRegister(n-1);
	UserContinue();
}

void Display3Delete(){
	int n=0;
	do{
		// system("clear");
		printf("~~~~~~~VETERINARIA OFMENDEZ~~~~~~~\n");
		printf(  "~   \t\t\t\t ~ \n");
		printf(  "~    Registrados actualmente \t ~ \n");
		printf(  "~   \t  %i Animales.\t\t ~ \n",table.getNumberOfEntries());
		printf(  "~   \t\t\t\t ~ \n");
		printf(  "~   \t Digita el registro \t ~ \n");
		printf(  "~   \t  que deseas  BORRAR.\t ~ \n");
		printf(  "~   \t\t\t\t ~ \n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("Borrar: \n");
		scanf("%i",&n);
		while (getchar()!='\n');
	} while(  n<1 || n >table.getNumberOfEntries() );
	DeleteRegister(n-1);
	UserContinue();
}

void Display4Search(){
	
      table.printTable();
	UserContinue();
}

void Display5Exit(){
	char m[20] = "      ADIOS!";
	ShowMessage(m);
} 

void DeleteRegister(int _p1){
	FILE * dataFile = GetReadDataFile();
	dogType buffer;
	SetPositionInEndFile(dataFile,-1);
	fread((void*)&buffer,sizeof(dogType),1,dataFile) ;
	SetPositionInFile(dataFile, _p1);
      
	WriteDogToFile(buffer, dataFile);
	SetPositionInFile(dataFile, 0);

	FILE *dataFile_tmp;

	dataFile_tmp=fopen("tmp.dat", "wb");
	if (!dataFile_tmp) {
		printf("Unable to open file temp file.");
      		exit(-1);
	}
	int readed =1;
	while (fread((void*)&buffer,sizeof(dogType),1,dataFile) == 1 && readed< table.getNumberOfEntries()) {
		fwrite(&buffer, sizeof(dogType), 1, dataFile_tmp);
		readed ++;
	}

	fclose(dataFile);
	fclose(dataFile_tmp);

	remove("dataDogs.dat");
	rename("tmp.dat", "dataDogs.dat");
	// SetPositionInEndFile(dataFile,-1);
	// WriteDogToFile(NULL, dataFile);

	// FILE * mrFile = GetMedicalRecordFile();
	// BORRAR DE LA HASH
	LoadDataProgram();
}

void ViewRegister(int _p1){
	FILE * dataFile = GetReadDataFile();
	dogType buffer;
	SetPositionInFile(dataFile,_p1);


	fread((void*)&buffer,sizeof(dogType),1,dataFile) ;

	// FILE * mrFile = GetMedicalRecordFile();
	FILE * mrFile;
	mrFile = fopen("medicalRecord.txt", "w");
	if (mrFile == NULL){
		perror("Error en la creación/apertura del archivo. \n");
		exit(-1);
	}
	fprintf(mrFile, "~~~~ HISTORIA CLINICA~~~~ \n \n Nombre: %s \n Tipo:   %s \n Edad:   %i \n Raza:   %s \n Altura: %i \n Peso:   %2.2f \n Sexo:   %c ",
	buffer.Name, buffer.Type, buffer.Age, buffer.Breed, buffer.Heigth, buffer.Weigth, buffer.Sex );
	fclose(mrFile);
	system("nano medicalRecord.txt");
}

void ConfirmDataToRegister(char _n[32], char _t[32], int _a, char _b[16], int _h, float _w, char _s ){
// system("clear");
	char op;
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
			char m[20] = "Registro cancelado!";
			ShowMessage(m);
		}else{
			RegisterDog(_n, _t, _a, _b, _h, _w, _s);
		}
	}else{
		ConfirmDataToRegister(_n, _t, _a, _b, _h, _w, _s);
	}

}

void RegisterDog(char _n[32], char _t[32], int _a, char _b[16], int _h, float _w, char _s ){
	dogType newDog;
  	Entry *entry = new Entry();
 	FILE * fData= GetDataFileAppend();

	memcpy( newDog.Name , _n, sizeof(char[32])  );
	memcpy( entry->Name , _n, sizeof(char[32])  );
	memcpy( newDog.Type  ,  _t, sizeof(char[32]) );
	newDog.Age = _a;
	memcpy(newDog.Breed  , _b, sizeof(char[16]) );
	newDog.Heigth  = _h;
	newDog.Weigth = _w;
	newDog.Sex = _s;
	table.insertEntry(entry,table.getNumberOfEntries());
	WriteDogToFile(newDog, fData);
	fclose(fData);
	char m[20] = "Registrado!!";
	ShowMessage(m);
}


void ShowMessage(char _msg[16]){
	// system("clear");
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

void SetPositionInFile(FILE *_file ,int _p){
      int movedP = fseek( _file, _p*sizeof(dogType), SEEK_SET);
	if (movedP != 0){
		perror("El reinicio del apuntador no se logró correctamente.");
		exit(-1);
	}
}
void SetPositionInEndFile(FILE *_file ,int _p){
      int movedP = fseek( _file, _p*sizeof(dogType), SEEK_END);
	if (movedP != 0){
		perror("El reinicio del apuntador no se logró correctamente.");
		exit(-1);
	}
}
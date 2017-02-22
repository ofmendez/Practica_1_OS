// #include <stdio.h>
// #include <iostream>
// #include <stdlib.h>
#include "view.h"
#include "dogType.h"



int main(){
	// ShowMainMenu();
	// while(UserContinue()){
	// ListenAndGoToScreen( AskMenu() );
	// }

	FILE * dataFile;
	dataFile = fopen("dataDogs.dat", "r");
	if (dataFile == NULL){
		perror("Error al leer el archivo dataDogs \n");
		exit(-1);
	}

	int movedP = fseek( dataFile, 0, SEEK_SET);
	// int movedP = fseek( dataFile, 3*sizeof(dogType), SEEK_SET);
	if (movedP != 0){
		perror("El reinicio del apuntador no se logró correctamente.");
		exit(-1);
	}
	dogType newDog ;
	fread((void*)&newDog,sizeof(dogType),1,dataFile);
	DogToPrint(newDog);



}


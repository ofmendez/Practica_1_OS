#include "dogType.h"

FILE * GetDataFile(){
	FILE * result;
	result = fopen("dataDogs.dat", "wb+");
	if (result == NULL){
		perror("Error en la creación/apertura del archivo. \n");
		exit(-1);
	}
	
	return result;
}

FILE * GetDataFileAppend(){
	FILE * result;
	result = fopen("dataDogs.dat", "ab+");
	if (result == NULL){
		perror("Error en la creación/apertura del archivo. \n");
		exit(-1);
	}
	
	return result;
}

FILE * GetReadDataFile(){
  FILE * result;
  result = fopen("dataDogs.dat", "rb+");
  if (result == NULL){
      perror("Error al leer el archivo dataDogs \n");  exit(-1);
      exit(-1);
  }
  return result;
}


void WriteDogToFile(dogType _dog, FILE * _file){
	// DogToPrint(&_dog); //TEST
 	int dataWrited;
	dataWrited = fwrite( &_dog, sizeof( dogType), 1, _file);
    	if (dataWrited == 0){
    		perror("No se logró escribir la estructura al archivo \n");
      	exit(-1);
    }

}

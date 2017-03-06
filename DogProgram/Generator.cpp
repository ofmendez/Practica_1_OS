#include <string.h>
#include <iostream>
using namespace std;

#include "Util.h"
#include "generator.h"

int main(){
	Generate();
}

void Generate() {
      // int registers = 9;
	int registers = 10000000;
 	struct dogType tmpDog;
	char namesBase[1717][32];
	char breedsBase[32][16];
 	FILE * fData= GetDataFile();

	LoadNamesBase(namesBase);
	LoadBreedsBase(breedsBase);

  	for (int i = 0; i < registers; i++) {
		tmpDog = GetRandomDog(namesBase,breedsBase);
		WriteDogToFile(tmpDog,fData);
  	}

  	fclose(fData);

  	printf("Sucess!\n");
	// dogType *aux =malloc(sizeof(dogType));
}

dogType GetRandomDog(char  _namesBase[][32], char _breedsBase[][16]){
	dogType result;
	char type[32] = "Perro"; 

	memcpy(result.Name , _namesBase[rand()%1717] ,sizeof( _namesBase[0]));
	memcpy(result.Type , type ,sizeof( type ) );
	result.Age = RandomRange(0,16);
	memcpy(result.Breed , _breedsBase[rand()%32] ,sizeof( _breedsBase[0]));
	result.Heigth = RandomRange(12,70);
	result.Weigth = RandomRangeF(2.5,30.0);
	result.Sex = rand()%2 == 1?'F':'M';
	return result;
}

void LoadBreedsBase(char _breed[][16]){
  	// char  breeds[32][16];
	int sz = sizeof(_breed[0]);
  	strncpy (_breed[0] , "Affenpinscher", sz );
  	strncpy (_breed[1] , "Afgano", sz );
  	strncpy (_breed[2] , "Akita", sz );
  	strncpy (_breed[3] , "Alzawakh", sz );
  	strncpy (_breed[4] , "Barbet", sz );
  	strncpy (_breed[5] , "Bullmastiff", sz );
  	strncpy (_breed[6] , "Boxer", sz );
  	strncpy (_breed[7] , "Bulldog", sz );
  	strncpy (_breed[8] , "Cocker", sz );
  	strncpy (_breed[9] , "Chow Chow", sz );
  	strncpy (_breed[10] , "Collie", sz );
  	strncpy (_breed[11] , "Chihuahua", sz );
  	strncpy (_breed[12] , "Dalmata", sz );
  	strncpy (_breed[13] , "Doberman", sz );
  	strncpy (_breed[14] , "Dogo", sz );
  	strncpy (_breed[15] , "Fox Terrier", sz );
  	strncpy (_breed[16] , "Galgo", sz );
  	strncpy (_breed[17] , "Gran Danes", sz );
  	strncpy (_breed[18] , "Geyhound", sz );
  	strncpy (_breed[19] , "Husky", sz );
  	strncpy (_breed[20] , "Kai", sz );
  	strncpy (_breed[21] , "Komondor", sz );
  	strncpy (_breed[22] , "Labrador", sz );
  	strncpy (_breed[23] , "Mastin", sz );
  	strncpy (_breed[24] , "Pastor Aleman", sz );
  	strncpy (_breed[25] , "Ponter", sz );
  	strncpy (_breed[26] , "Rottweiler", sz );
  	strncpy (_breed[27] , "San Bernardo", sz );
  	strncpy (_breed[28] , "Schnauzer", sz );
  	strncpy (_breed[29] , "Samoyedo", sz );
  	strncpy (_breed[30] , "Teckel", sz );
  	strncpy (_breed[31] , "Yorkshire", sz );
}


void LoadNamesBase(char _names[][32]){
	char buffer[32];
	FILE *ap;
      ap = fopen("nombresMascotas.txt","r");

      if(ap == NULL ){
      	perror ("Error al abrir el archivo");  exit(-1);
      }	
    	for (int i = 0; i < 1717; ++i) {
	 	fgets(buffer , 32,  ap);
	 	buffer[strcspn(buffer, "\n")] = 0;
		memcpy (_names[i] , buffer, sizeof(buffer));
	}
	fclose(ap);
}

int RandomRange(int _min, int _max){
 	return(rand() % (_max + 1) + _min);
}

float RandomRangeF(float _min, float _max){
 	return _min + (rand() /     (  RAND_MAX /(_max -_min)       ) );
}




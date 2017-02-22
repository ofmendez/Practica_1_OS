#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
using namespace std;

void ShowMainMenu(){
	system("clear");
	cout << "MENU: "<< endl
	<< "1. Ingresar registro."<< endl
	<< "2. Ver registro."<< endl
	<< "3. Borrar registro."<< endl
	<< "4. Buscar registro."<< endl
	<< "5. Salir."<< endl;
}

int AskMenu(){
	int menuSelected;
	cin >> menuSelected;
	return menuSelected;
}

bool UserContinue(){
	printf("Operación finalizada...\n");
	printf("Presione ENTER para continuar.");
	while(getchar() != '\n');
	getchar();
	printf("\n");
}

void ListenAndGoToScreen(int _m){
	system("clear");
	cout << "ESTAMOS EN EL MENU "<<_m<<endl;
	
	UserContinue();
	
}

void DogToPrint(dogType _dog){
	cout<<_dog.Name<<endl;
	cout<<_dog.Type<<endl;
	cout<<_dog.Age<<endl;
	cout<<_dog.Breed<<endl;
	cout<<_dog.Heigth<<endl;
	cout<<_dog.Weigth<<endl;
	cout<<_dog.Sex<<endl<<endl;
}
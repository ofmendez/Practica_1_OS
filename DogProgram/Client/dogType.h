
#pragma pack(1)
 struct dogType{
	char Name[32];
	char Type[32];
	int Age;
	char Breed[16];
	int Heigth;
	float Weigth;
	char Sex;
};

void DogToPrint(dogType *_dog){
	cout<<"--------------------------------------"<<endl;
	cout<<_dog->Name<<endl;
	cout<<_dog->Type<<endl;
	cout<<_dog->Age<<endl;
	cout<<_dog->Breed<<endl;
	cout<<_dog->Heigth<<endl;
	cout<<_dog->Weigth<<endl;
	cout<<_dog->Sex<<endl;
	// cout<<"Apunta a: "<<((_dog->next == NULL)?"nulo!!!":_dog->next->Name)<<endl;
	cout<<"--------------------------------------"<<endl;
}
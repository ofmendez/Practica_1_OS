 struct dogType{
	char Name[32];
	char Type[32];
	int Age;
	char Breed[16];
	int Heigth;
	float Weigth;
	char Sex;
	struct dogType *next;
};
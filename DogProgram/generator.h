void LoadNamesBase(char _names[][32]);

void DogToPrint(dogType _dog);

void Generate() ;

dogType GetRandomDog(char  _namesBase[][32], char _breedsBase[][16]);


void WriteDogToFile(dogType _dog, FILE * _file);

int RandomRange(int _min, int _max);

void LoadBreedsBase(char _breed[][16]);

float RandomRangeF(float _min, float _max);

FILE * GetDataFile();








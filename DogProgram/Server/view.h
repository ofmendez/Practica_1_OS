// Carga los datos ńecesarios del .dat para crear la hash
void LoadDataProgram();

//Despliega el menú principal y solicita una entrada válida del usuario.
void ShowMainMenu();

//Espera a que oprima ENTER para continuar.
bool UserContinue();


//Función de ingresar un registro.
void Display1Ingress(); 

//Función de visualizar un registro.
void Display2View(); 

//Función de Borrar un registro.
void Display3Delete(); 

//Funcion de Buscar un registro.
void Display4Search(); 

//Función salir del programa.
void Display5Exit(); 

//Borra el registro seleccionado.
void DeleteRegister(int _p1);

//Borra el último item de un archivo.
void DeleteLastItem(FILE * _file);

//Busca, Lee y despliega el registro solicitado en un .txt.
void ViewRegister(int _p1);

//Guarda el nuevo registro.
void RegisterDog(char _n[32], char _t[32], int _a, char _b[16], int _h, float _w, char _s );

//Despliega los datos que se van a guardar y pide confirmación al usuario.
void ConfirmDataToRegister(char _n[32], char _t[32], int _a, char _b[16], int _h, float _w, char _s );

//Despliega un mensaje al usuario
void ShowMessage(char _msg[20]);

//Establece el apuntador del archivo a la posiciń dada relativa al inicio del archivo.
void SetPositionInFile(FILE *_file ,int _p);

//Establece el apuntador del archivo a la posiciń dada relativa al final del archivo.
void SetPositionInEndFile(FILE *_file ,int _p);

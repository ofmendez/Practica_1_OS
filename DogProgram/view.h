void ShowMainMenu();

bool UserContinue();

void LoadDataProgram();

void Display1Ingress(); 
void Display2View(); 
void Display3Delete(); 
void Display4Search(); 
void Display5Exit(); 
void ShowMessage(char _msg[20]);
void ViewRegister(int _p1);
void DeleteRegister(int _p1);

void RegisterDog(char _n[32], char _t[32], int _a, char _b[16], int _h, float _w, char _s );
void ConfirmDataToRegister(char _n[32], char _t[32], int _a, char _b[16], int _h, float _w, char _s );

void SetPositionInFile(FILE *_file ,int _p);
void SetPositionInEndFile(FILE *_file ,int _p);


#include"allWindows.h"

extern fstream openConfig();
extern string pwdEncode(string src_pwd);
extern fstream globalConfigFile;
//extern void drawMainWindow();


int main() {
	globalConfigFile=openConfig();
	
	
	//string o("我是");
	//cout<<(o[0]+o[1]);
	drawMainWindow();
	loginWindow();
	
	
	
	gotoXY(WWIDTH,WHEIGHT);
	return 0;
}

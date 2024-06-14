#ifndef ALLWINDOWS_H
#define ALLWINDOWS_H

#define WWIDTH 100
#define WHEIGHT 25

#include"conWindows.h"
#include"allValueType.h"
#include"allValues.h"

extern Users curUser;
extern bool userLogin(string username,string password);


void drawMainWindow(){
	string windowsLine[6]={"╔","╗","╚","╝","═","║"};
	drawWindow(0,0,WWIDTH,WHEIGHT,windowsLine);
}

void loginWindow(){
	int tempHang=4;
	TextCK tck(46,tempHang,5,1);
	tck.setText("登录界面");
	tck.draw();
	TextCK unTck(18,tempHang+4,10,1);
	unTck.setText("用户名:");
	unTck.draw();
	TextCK pwdTck(18,tempHang+9,10,1);
	pwdTck.setText("密码:");
	pwdTck.draw();
	
	EditCK unEck(28,tempHang+3,40,1);
	unEck.draw();
	EditCK pwdEck(28,tempHang+8,40,1);
	pwdEck.draw();
	ButtonCK loginBtn(44,tempHang+12,7,1);
	loginBtn.setText("  登录");
	loginBtn.draw();
	curUser.username=unEck.getEditFocus();
	curUser.password=pwdEck.getEditFocus();
	loginBtn.setFocusInfo(true);
	getch();
	loginBtn.setFocusInfo(false);
	
	
}




#endif

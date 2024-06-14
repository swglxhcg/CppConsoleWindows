#ifndef CONWINDOWS_H
#define CONWINDOWS_H

#include"globalHeader.h"

void gotoXY(short x, short y) {
	COORD coord = {x, y}; 
	//COORD是Windows API中定义的一种结构体类型，表示控制台屏幕上的坐标。
	//上面语句是定义了COORD类型的变量coord，并以形参x和y进行初始化。
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	//GetStdHandle(STD_OUTPUT_HANDLE); 获取控制台输出句柄
	//然后用SetConsoleCursorPosition设置控制台(cmd)光标位置
}

void clrScr() {    //清空屏幕
	HANDLE hdout = GetStdHandle(STD_OUTPUT_HANDLE);    //获取标准输出设备的句柄
	CONSOLE_SCREEN_BUFFER_INFO csbi;    //定义表示屏幕缓冲区属性的变量
	GetConsoleScreenBufferInfo(hdout, &csbi);  //获取标准输出设备的屏幕缓冲区属性
	DWORD size = csbi.dwSize.X * csbi.dwSize.Y, num = 0; //定义双字节变量
	COORD pos = {0, 0};    //表示坐标的变量（初始化为左上角(0, 0)点）
	//把窗口缓冲区全部填充为空格并填充为默认颜色（清屏）
	FillConsoleOutputCharacter(hdout, ' ', size, pos, &num);
	FillConsoleOutputAttribute (hdout, csbi.wAttributes, size, pos, &num );
	SetConsoleCursorPosition(hdout, pos);    //光标定位到窗口左上角
}

void drawLine(short x,short y,int len,bool horv,string c){
	int tx=x,ty=y;
	for(int i=0;i<len;i++){
		gotoXY(tx,ty);
		cout<<c;
		if(horv){	//0=h, 1=v
			ty=y+i;
		}else{
			tx=x+i;
		}
	}
}

void drawWindow(short x,short y,int width,int height,string cline[]){
	if(cline[0]==""){
		//cline={"╔","╗","╚","╝","═","║"};
		cline[0]="╔";
		cline[1]="╗";
		cline[2]="╚";
		cline[3]="╝";
		cline[4]="═";
		cline[5]="║";
	}
	drawLine(x,y,width,0,cline[4]);
	drawLine(x+width-1,y,height,1,cline[5]);
	drawLine(x,y,height,1,cline[5]);
	drawLine(x,y+height-1,width+1,0,cline[4]);
	gotoXY(x,y);
	cout<<cline[0];
	gotoXY(x+width-1,y);
	cout<<cline[1];
	gotoXY(x,y+height-1);
	cout<<cline[2];
	gotoXY(x+width-1,y+height-1);
	cout<<cline[3];
}

class ConKey{
public:
	short x;
	short y;
	int width;
	int height;
	//bool isFocus=false;
	//short fx,fy;
	string cline[6]={"╔","╗","╚","╝","═","║"};
	
	
	
	void drawRootCK(){
		drawWindow(x,y,width,height,cline);
	}
	
	ConKey(short x,short y,int width,int height){
		this->x=x;
		this->y=y;
		this->width=width;
		this->height=height;
	}
	
	
	void changeBoxLine(string tmpLine[]){
		//this->cline=tmpLine;
		//strcpy((this->cline),tmpLine);
		for(int i=0;i<6;i++){
			this->cline[i]=tmpLine[i];
		}
		
	}
	
};

class Window : ConKey{
public:
	int CKcount=0;
	
	//string layoutFile;
	Window(string layoutFilePath):ConKey(0,0,0,0){
		string lineText;
		ifstream layoutFile(layoutFilePath);
		if(layoutFile.good()){
			getline(layoutFile,lineText);
			sscanf(lineText.c_str(),"%hd,%hd,%d,%d",&this->x,&this->y,&this->width,&this->height);
		}
		while(getline(layoutFile,lineText)){
			short tempx,tempy,CKclass;
			int tempw,temph;
			sscanf(lineText.c_str(),"%hd %hd,%hd,%d,%d",&CKclass,&tempx,&tempy,&tempw,&temph);
		}
	}
};

class TextCK : ConKey
{
public:
	string text="";
	TextCK(short x,short y,int width,int height):ConKey(x,y,width,height){}
	void draw(){
		gotoXY(x,y);
		//int counth=0;
		//bool isFirst=true;
		//for(int i=0;i<(int)text.length()/4;i++){
		cout<<text;
		/*不支持utf16，弃用
		  if(i%(this->width)==0&&!isFirst){
		  counth++;
		  gotoXY(x,y+counth);
		  }
		  if(counth>=this->height)break;
		  cout<<text[i];
		  isFirst=false;
		 */
		//}
	}
	void setText(string c){
		this->text=c;
	}
	
};

class EditCK : ConKey
{
public:
	EditCK(short x,short y,int width,int height):ConKey(x,y,width,height){
		string cline[6]={"┌","┐","└","┘","─","│"};
		changeBoxLine(cline);
	}
	void draw(){
		drawWindow(x,y,width+2,height+2,this->cline);
		
	}
	string getEditFocus(){
		string text;
		gotoXY(x+1,y+1);
		//cin>>text;
		//cin.getline(text,width);
		getline(cin,text);
		return text;
	}
};

class ButtonCK : ConKey
{
public:
	string text="";
	bool isFocus=false;
	string noFocusCline[6]={"┌","┐","└","┘","─","│"};
	string yesFocusCline[6]={"┏","┓","┗","┛","━","┃"};
	ButtonCK(short x,short y,int width,int height):ConKey(x,y,width,height){
		//string cline[6]={"┏","┓","┗","┛","━","┃"};
		changeBoxLine(noFocusCline);
		
	}
	void draw(){
		drawWindow(x,y,width+2,height+2,this->cline);
		gotoXY(x+1,y+1);
		cout<<this->text;
	}
	
	
	void setFocusInfo(bool tb){
		isFocus=tb;
		if(isFocus){
			changeBoxLine(yesFocusCline);
		}else{
			changeBoxLine(noFocusCline);
		}
		//this->fx=x;
		//this->fy=y;
		this->draw();
		//gotoXY(x+1,y+1);
	}
	
	
	void setText(string c){
		this->text=c;
	}
};

#endif

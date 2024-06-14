#include"globalHeader.h"

//声明
fstream openConfig();
bool userLogin(string username,string password);
string pwdEncode(string src_pwd);
string addUser(Users user);
//------------

//ProgramDB
string configFileName="config.cdb";

fstream openConfig(){
	fstream configFile;
	configFile.open(configFileName, std::ios::in | std::ios::out | std::ios::app);
	
	if (!configFile.is_open()) {
		configFile.open(configFileName, std::ios::out);
		Users usrAdmin={"admin","admin","admin"};
		configFile<<addUser(usrAdmin);
		configFile.close();
		configFile.open(configFileName, std::ios::in | std::ios::out | std::ios::app);
		
	}
	return configFile;
}



//UserFunction
bool userLogin(string username,string password){
	bool isAuth=false;
	
	return isAuth;
}

string pwdEncode(string src_pwd){
	stringstream ss;
	int num;
	for(char a:src_pwd){
		if(a>='A'&&a<='Z'){
			num=a-'A';
		}else if(a>='a'&&a<='z'){
			num=a-'a'+26;
		}else if(a>='0'&&a<='9'){
			num=a-'0'+52;
		}
		ss << std::setw(2) << std::setfill('0') << num;
		
	}
	return ss.str();
}
string addUser(Users user){
	string rlt_str(user.username);
	rlt_str+=":";
	rlt_str+=pwdEncode(user.password);
	rlt_str+=".";
	rlt_str+=user.name;
	rlt_str+='\n';
	return rlt_str;
}

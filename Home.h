#ifndef HOME_H//³¯§»©x  U0933050 
#define HOME_H
class console_based{
	public:
		Home(int a=0,string b="",string c=""){
			account = a;
			setUserName(b);
			setPassword(c); 
		}
		void setAccount(int a){ account = a;
		}
		void setUserName(string b){
			int length = b.size();
			length = (length<17 ? length : 16);
			b.copy(userName, length);
			userName[length]='\0';
		} 
		void setPassword(string b){
			int length = b.size();
			length = (length<17 ? length : 16);
			b.copy(password, length);
			password[length]='\0';
		}
		int getAccount(){ return account;
		}
		string getUserName(){ return userName;
		}
		string getPassword(){ return password;
		} 
	private:
		int account;
		char userName[17];
		char password[17];
};
#endif

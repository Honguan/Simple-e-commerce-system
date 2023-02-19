#ifndef PRODUCT_H//³¯§»©x  U0933050 
#define PRODUCT_H
class Product{
	public:
		output(int a=0, string b="", string c="",int d=0){
			pid = a; price = d;
			setPname(b);
			setPdesc(c); 
		}
		void setPid(int a){ pid = a;
		}
		void setPname(string b){
			int length = b.size();
			length = (length<17 ? length : 16);
			b.copy(pname, length);
			pname[length]='\0';
		} 
		void setPdesc(string b){
			int length = b.size();
			length = (length<17 ? length : 16);
			b.copy(pdesc, length);
			pdesc[length]='\0';
		}
		void setPrice(int a){ price = a;
		}
		int getPid(){ return pid;
		}
		string getPname(){ return pname;
		}
		string getPdesc(){ return pdesc;
		} 
		int getPrice(){ return price;
		}
	private:
		int pid,price;
		char pname[17];
		char pdesc[17];		
};
#endif

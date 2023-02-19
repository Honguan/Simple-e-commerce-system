#ifndef TRANSACTION_H//³¯§»©x  U0933050 
#define TRANSACTION_H
class transaction{
	public:
		Record(int a=0, int b=0,int c=0,int d=0, int e=0,int f=0,string x="",int g=0,string w="",int h=0,int k=0){
			year=a;month=b;days=c;hour=d;minute=e;
			uesrId = f;
			setuser_name(x);
			productId = g;
			setgoods_name(w);
			munber = h;
			Kvlaue=k;
		}
		void setYear(int a){ year = a;}
		void setMonth(int a){ month = a;}
		void setDays(int a){ days = a;}
		void setHour(int a){ hour = a;}
		void setMinute(int a){ minute = a;}
		
		void setuesrId(int a){ uesrId = a;}
		void setuser_name(string b){
			int length = b.size();
			length = (length<17 ? length : 16);
			b.copy(user_name, length);
			user_name[length]='\0';
		} 
		
		void setproductId(int a){ productId = a;}
		void setgoods_name(string b){
			int length = b.size();
			length = (length<17 ? length : 16);
			b.copy(goods_name, length);
			goods_name[length]='\0';
		}
		void setmunber(int a){ munber = a;}
		void setKvlaue(int a){ Kvlaue = a;}
		
		int getyear(){ return year;}
		int getmonth(){ return month;}
		int getdays(){ return days;}
		int gethour(){ return hour;}
		int getminute(){ return minute;}
		
		int getUesrId(){ return uesrId;}
		string getuser_name(){ return user_name;} 
		
		int getProductId(){ return productId;}
		string getgoods_name(){ return goods_name;
		} 
		int getMunber(){ return munber;}
		int getKvlaue(){ return Kvlaue;
		}

	private:
	    char user_name[17];
		char goods_name[17];
		int year,month,days,hour,minute;
		int uesrId,productId,munber;
		int Kvlaue;	
};
#endif

#include <iostream>//陳宏官  U0933050 
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;
#include "Product.h"
#include "Home.h"
#include "Transaction.h"

void printClient(ostream &, console_based &);
int menu();
void registered(fstream &);
int  login(fstream &);

void printGoods();
int  produce();
void Add(fstream &f);
void deleteGoods(fstream &f);
void modify(fstream &f);
bool existed(fstream &f, int pid);
void information(fstream &f);

int buyer();
void tran(ostream &o, transaction &record);
void label(ostream &o, transaction &record);
void buy(int,fstream &,fstream &,fstream &);
void examine(int,fstream &);



void printClient(ostream &o, console_based &client){
	o << client.getAccount() << "\t";
	o << client.getUserName() << "\t";
	o << client.getPassword() << endl; 
}
int menu(){
	int s;
	cout << "作業選項： " << endl;
	cout << " (1) 註冊帳戶 " << endl;
	cout << " (2) 登陸帳戶 " << endl;
	cout << " (3) 離開" << endl;
	cout << "請輸入選項： ";
	cin >> s;
	return s;
}
void registered(fstream &f){
    int account=0;
    bool check=1;
    string userName, password;   
    console_based menu,menu_Account,menu_UserName;
    f.seekg(0*sizeof(console_based));
    while(!f.eof()){
	f.read( reinterpret_cast<char *>(&menu_Account), sizeof(console_based));
	if(menu_Account.getAccount()>=account&&menu_Account.getAccount()<=1100)account=menu_Account.getAccount();
	}
	f.clear();account++;cout<<account<<endl;
    cout << "請輸入帳戶名稱，密碼: ";
    cin >> userName >> password;
    menu.setAccount(account);
    menu.setUserName(userName);
	menu.setPassword(password);
	if(1){
	f.seekg(0*sizeof(console_based));
	while(!f.eof()){
	f.read( reinterpret_cast<char*>(&menu_UserName), sizeof(console_based));
	if(menu_UserName.getAccount()>=1001&&menu_UserName.getAccount()<=1100){
		if(menu_UserName.getUserName()==userName){cout<<"帳號名稱已經存在 "<<endl;check=0;} 
		}
	}f.clear();
	if(check){
	f.seekp((account-1001)*sizeof(console_based));   // 移動檔案寫入位置 
	f.write(reinterpret_cast<const char*>(&menu),sizeof(console_based));
	printClient(cout,menu);cout<<"註冊完成"<<endl;
		}
	}
}
int login(fstream &f){
	console_based menu,menu_1,menu_2;
	bool check=0,check_2=0;
	int id;
	string userName, password;
	f.seekg(0*sizeof(console_based));
	while(!f.eof()){	
	f.read( reinterpret_cast<char*>(&menu),sizeof(console_based));
	if(menu.getAccount()>=1001&&menu.getAccount()<=1100)printClient(cout,menu);
	}f.clear();
	cout<<"\t登入\t\n請輸入帳戶名稱，密碼:";
	cin>>userName>>password;
	if(true){
	f.seekg(0*sizeof(console_based));
	while(!f.eof()){
	f.read( reinterpret_cast<char*>(&menu_1), sizeof(console_based));
	if(menu_1.getAccount()>=1001&&menu_1.getAccount()<=1100){if(menu_1.getUserName()==userName)check++;} 
	}
	for(int i=0;i<2;i++){if(check==0){cout<<"帳號不存在"<<endl;break;}
	}
	f.clear();
	if(check){
	f.seekg(0*sizeof(console_based));
	while(!f.eof()){
	f.read( reinterpret_cast<char*>(&menu_2), sizeof(console_based));
	if(menu_2.getAccount()>=1001&&menu_2.getAccount()<=1100){
	if(menu_2.getUserName()==userName&&menu_2.getPassword()==password){
		check_2++;userName=menu_2.getUserName();id=menu_2.getAccount();
			}
		}
	}
	f.clear();
	if(check_2){
		cout<<"歡迎"<<userName<<"/你的帳戶編號是"<<id<<endl;
			return id;
	}	for(int i=0;i<2;i++){if(check_2==0) {cout<<"密碼不正確"<<endl;break;}}
		}
		
	}
}


void printGoods(ostream &o, Product &goods){
	o << goods.getPid() << "\t";
	o << goods.getPname() << "\t";
	o << goods.getPdesc() << "\t";
	o << goods.getPrice() << endl; 
}
int produce(){
	int s;
	cout << "  產品管理： " << endl;
	cout << " (1) 新增產品 " << endl;
	cout << " (2) 刪除產品 " << endl;
	cout << " (3) 修改產品" << endl;
	cout << " (4) 交易資料" << endl;
	cout << " (5) 離開" << endl;
	cout << "請輸入選項： ";
	cin >> s;
	return s;
}
bool existed(fstream &f, int pid){
	Product goods;
	if( pid < 101 || pid > 200) return false;
	f.seekg((pid-101)*sizeof(Product));
	f.read( reinterpret_cast<char *>(&goods), sizeof(Product));
    if (goods.getPid() >= 101&&goods.getPid()<=200) return true;
    return false;
}
void Add(fstream &f){
    int pid,price;
    string pname, pdesc;
    Product goods;
    cout << "請輸入帳號: (101 ~ 200) "; cin >> pid;
    if(pid >= 101 && pid <= 200 && !existed(f, pid)){
    	cout << "請輸入產品名稱,產品說明,產品單價: ";
    	cin >> pname >> pdesc >> price;
    	goods.setPid(pid);
    	goods.setPname(pname);
		goods.setPdesc(pdesc);
		goods.setPrice(price);
		f.seekp((pid-101)*sizeof(Product));   // 移動檔案寫入位置 
		f.write(reinterpret_cast<const char*>(&goods),sizeof(Product));
		printGoods(cout,goods);
    }
}
void deleteGoods(fstream &f){
	int pid;
	cout << "請輸入要刪除的產品編號: ";
	cin >> pid;
    if(existed(f, pid)){
    	f.seekp((pid-101)*sizeof(Product));
	    Product goods;
	    f.write(reinterpret_cast<const char *>(&goods), sizeof(Product));
    }
    
}
void modify(fstream &f){
	Product check,goods;
	int pid,price;
    string pname, pdesc;
    f.seekg(0*sizeof(Product));
	while(!f.eof()){	
	f.read( reinterpret_cast<char*>(&check),sizeof(Product));
	if(check.getPid()>=101&&check.getPid()<=200)
//	if(check.getPid()==pid)
	printGoods(cout,check);
	}f.clear();
	cout << "請輸入要修改的產品編號: ";
	cin >> pid;
    if(pid >= 101 && pid <= 200 && existed(f, pid)){
		cout << "請輸入要修改的產品名稱,產品說明,產品單價: ";
		cin >> pname >> pdesc >> price;
		goods.setPid(pid);
    	goods.setPname(pname);
		goods.setPdesc(pdesc);
		goods.setPrice(price);
		f.seekp((pid-101)*sizeof(Product));   // 移動檔案寫入位置 
		f.write(reinterpret_cast<const char*>(&goods),sizeof(Product)); 
    }
}
void information(fstream &f){
	transaction check;
	int id,only;
	cout<<"是否精確搜尋:"<<endl; 
	cin>>only;
	if(only){cout<<"請輸入使用者 id : "<<endl;cin>>id;}
	if(only){
	f.seekg(0*sizeof(transaction));
	while(!f.eof()){	
	f.read( reinterpret_cast<char*>(&check),sizeof(transaction));
	if(check.getUesrId()>=1001&&check.getUesrId()<=1100)if(check.getUesrId()==id)label(cout,check);
	}
} 
	else{
	f.seekg(0*sizeof(transaction));
	while(!f.eof()){	
	f.read( reinterpret_cast<char*>(&check),sizeof(transaction));
	if(check.getUesrId()>=1001&&check.getUesrId()<=1100)label(cout,check);
		}
	}
}

int buyer(){
	int s;
	cout << "  歡迎購買： " << endl;
	cout << " (1) 我要購買 " << endl;
	cout << " (2) 查看交易明細  " << endl;
	cout << " (3) 離開" << endl;
	cout << "請輸入選項： ";
	cin >> s;
	return s;
}
void tran(ostream &o, transaction &record){
	o << record.getyear() << "/"<< record.getmonth() << "/"<< record.getdays() << "  ";
	o << record.gethour() << ":"<< record.getminute() << "  ";
	
	o << record.getUesrId() << "  ";
	o << record.getProductId() << "  ";
	o << record.getMunber() << endl; 
}
void label(ostream &o, transaction &record){
	o << record.getyear() << "/"<< record.getmonth() << "/"<< record.getdays() << "\t";
	o << record.gethour() << ":"<< record.getminute() << "  ";
	
	o << record.getUesrId() << "  "<<"username: "<<record.getuser_name()<<" ";
	o << record.getProductId() << " "<<"productname: "<<record.getgoods_name()<<" ";
	o << record.getMunber() <<" "<<"vaule: "<<record.getKvlaue()<<endl; 
}
void buy(int id,fstream &ftran,fstream &fuser,fstream &fgood){
	Product check_g,check_p;
	fgood.seekg(0*sizeof(Product));
	while(!fgood.eof()){	
	fgood.read( reinterpret_cast<char*>(&check_g),sizeof(Product));
	if(check_g.getPid()>=101&&check_g.getPid()<=200)
	printGoods(cout,check_g);
	}fgood.clear();
	
	int pid,munber,Kvlaue;
	int year_,month_,days_,hour_,minute_;
	transaction line;
	string user_name,goods_name;
	cout << "請輸入要購買的產品編號,和產品數量: ";
	cin >> pid>>munber;
	
	time_t now = time(0);
   	tm *ltm = localtime(&now);
   	year_=(1900 + ltm->tm_year);month_=(1 + ltm->tm_mon);
	days_=(20+ltm->tm_wday);hour_=(ltm->tm_hour);minute_=(ltm->tm_min);
   	
   	
   	console_based check;
   	fuser.seekg(0*sizeof(console_based));
	while(!fuser.eof()){
	fuser.read( reinterpret_cast<char*>(&check), sizeof(console_based));
	if(check.getAccount()>=1001&&check.getAccount()<=1100){
	if(check.getAccount()==id)user_name=check.getUserName();}
	}fuser.clear();

	fgood.seekg(0*sizeof(Product));
	while(!fgood.eof()){	
	fgood.read( reinterpret_cast<char*>(&check_p),sizeof(Product));
	if(check_p.getPid()>=101&&check_p.getPid()<=200){
	if(check_p.getPid()==pid){goods_name=check_p.getPname(),Kvlaue=check_p.getPrice();}
		}
	}
	fgood.clear();
	int ok;
	cout<<"是否購買"<<endl; 
	cin>>ok;
	if(ok){
	line.setYear(year_);line.setMonth(month_);line.setDays(days_);
	line.setHour(hour_);line.setMinute(minute_);
	line.setuesrId(id);line.setuser_name(user_name);
	line.setproductId(pid);line.setgoods_name(goods_name);
	line.setmunber(munber);line.setKvlaue(munber*Kvlaue);
	ftran.write(reinterpret_cast<const char*>(&line),sizeof(transaction));
	cout<<"購買完成"<<endl;
	}
	else cout<<"購買失敗"<<endl;
	}
void examine(int id,fstream &f){
	transaction check;
	f.seekg(0*sizeof(transaction));
	while(!f.eof()){	
	f.read( reinterpret_cast<char*>(&check),sizeof(transaction));
	if(check.getUesrId()>=1001&&check.getUesrId()<=1100)if(check.getUesrId()==id)tran(cout,check);
	}
}

int main(int argc, char **argv){
	int number=0,human=0;
	
	fstream user;//第一題檔案 
	user.open("user.data", ios::in|ios::out|ios::binary);
	if( !user ) { cout << "檔案不存在1 ! " << endl;return 0;
	}
	fstream goods;//第二題檔案
	goods.open("product.data", ios::in | ios::out | ios::binary );
	if( !goods ) { cout << "檔案不存在2 ! " << endl;return 0;
	}
	fstream report;//第三題檔案 
	report.open("transData.data", ios::in | ios::out | ios::binary);
	if( !report ) { cout << "檔案不存在 3! " << endl;return 0;
	}
	cout<<" (1) 顧客 (2) 管理者"<<endl; 
	cin>>human;
	while(human==1){
		switch(menu()){
 		case 1: registered(user); break;  // 註冊帳戶
		case 2: number=login(user);	  break;  // 登陸帳戶 
		case 3: user.close(); exit(0);
		default:
			cerr << "選項不對 " << endl;
			    break; 
		}
		if(number>1000)break;
		user.clear();
	}
	while(number>1000){
		switch(buyer()){
 		case 1: buy(number,report,user,goods);break;  // 我要購買
		case 2: examine(number,report);break;  // 查看交易明細 
		case 3: report.close(); exit(0);
		default:
			cerr << "選項不對 " << endl;
				break; 
		}
		report.clear();
	}
	while(human==2){
		switch(produce()){
 		case 1: Add(goods); 		goods.clear(); break;  // 新增產品
		case 2: deleteGoods(goods);	goods.clear(); break;  // 刪除產品  
		case 3: modify(goods);		goods.clear(); break;  // 修改產品
		case 4: information(report);report.clear();break;  //交易資料
		case 5: goods.close();      exit(0);			  //離開
		default:
			cerr << "選項不對 " << endl;
			  	break; 
		}
		goods.clear();
	}
	
	return 0;
}



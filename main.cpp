#include <iostream>//�����x  U0933050 
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
	cout << "�@�~�ﶵ�G " << endl;
	cout << " (1) ���U�b�� " << endl;
	cout << " (2) �n���b�� " << endl;
	cout << " (3) ���}" << endl;
	cout << "�п�J�ﶵ�G ";
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
    cout << "�п�J�b��W�١A�K�X: ";
    cin >> userName >> password;
    menu.setAccount(account);
    menu.setUserName(userName);
	menu.setPassword(password);
	if(1){
	f.seekg(0*sizeof(console_based));
	while(!f.eof()){
	f.read( reinterpret_cast<char*>(&menu_UserName), sizeof(console_based));
	if(menu_UserName.getAccount()>=1001&&menu_UserName.getAccount()<=1100){
		if(menu_UserName.getUserName()==userName){cout<<"�b���W�٤w�g�s�b "<<endl;check=0;} 
		}
	}f.clear();
	if(check){
	f.seekp((account-1001)*sizeof(console_based));   // �����ɮ׼g�J��m 
	f.write(reinterpret_cast<const char*>(&menu),sizeof(console_based));
	printClient(cout,menu);cout<<"���U����"<<endl;
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
	cout<<"\t�n�J\t\n�п�J�b��W�١A�K�X:";
	cin>>userName>>password;
	if(true){
	f.seekg(0*sizeof(console_based));
	while(!f.eof()){
	f.read( reinterpret_cast<char*>(&menu_1), sizeof(console_based));
	if(menu_1.getAccount()>=1001&&menu_1.getAccount()<=1100){if(menu_1.getUserName()==userName)check++;} 
	}
	for(int i=0;i<2;i++){if(check==0){cout<<"�b�����s�b"<<endl;break;}
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
		cout<<"�w��"<<userName<<"/�A���b��s���O"<<id<<endl;
			return id;
	}	for(int i=0;i<2;i++){if(check_2==0) {cout<<"�K�X�����T"<<endl;break;}}
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
	cout << "  ���~�޲z�G " << endl;
	cout << " (1) �s�W���~ " << endl;
	cout << " (2) �R�����~ " << endl;
	cout << " (3) �קﲣ�~" << endl;
	cout << " (4) ������" << endl;
	cout << " (5) ���}" << endl;
	cout << "�п�J�ﶵ�G ";
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
    cout << "�п�J�b��: (101 ~ 200) "; cin >> pid;
    if(pid >= 101 && pid <= 200 && !existed(f, pid)){
    	cout << "�п�J���~�W��,���~����,���~���: ";
    	cin >> pname >> pdesc >> price;
    	goods.setPid(pid);
    	goods.setPname(pname);
		goods.setPdesc(pdesc);
		goods.setPrice(price);
		f.seekp((pid-101)*sizeof(Product));   // �����ɮ׼g�J��m 
		f.write(reinterpret_cast<const char*>(&goods),sizeof(Product));
		printGoods(cout,goods);
    }
}
void deleteGoods(fstream &f){
	int pid;
	cout << "�п�J�n�R�������~�s��: ";
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
	cout << "�п�J�n�ק諸���~�s��: ";
	cin >> pid;
    if(pid >= 101 && pid <= 200 && existed(f, pid)){
		cout << "�п�J�n�ק諸���~�W��,���~����,���~���: ";
		cin >> pname >> pdesc >> price;
		goods.setPid(pid);
    	goods.setPname(pname);
		goods.setPdesc(pdesc);
		goods.setPrice(price);
		f.seekp((pid-101)*sizeof(Product));   // �����ɮ׼g�J��m 
		f.write(reinterpret_cast<const char*>(&goods),sizeof(Product)); 
    }
}
void information(fstream &f){
	transaction check;
	int id,only;
	cout<<"�O�_��T�j�M:"<<endl; 
	cin>>only;
	if(only){cout<<"�п�J�ϥΪ� id : "<<endl;cin>>id;}
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
	cout << "  �w���ʶR�G " << endl;
	cout << " (1) �ڭn�ʶR " << endl;
	cout << " (2) �d�ݥ������  " << endl;
	cout << " (3) ���}" << endl;
	cout << "�п�J�ﶵ�G ";
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
	cout << "�п�J�n�ʶR�����~�s��,�M���~�ƶq: ";
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
	cout<<"�O�_�ʶR"<<endl; 
	cin>>ok;
	if(ok){
	line.setYear(year_);line.setMonth(month_);line.setDays(days_);
	line.setHour(hour_);line.setMinute(minute_);
	line.setuesrId(id);line.setuser_name(user_name);
	line.setproductId(pid);line.setgoods_name(goods_name);
	line.setmunber(munber);line.setKvlaue(munber*Kvlaue);
	ftran.write(reinterpret_cast<const char*>(&line),sizeof(transaction));
	cout<<"�ʶR����"<<endl;
	}
	else cout<<"�ʶR����"<<endl;
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
	
	fstream user;//�Ĥ@�D�ɮ� 
	user.open("user.data", ios::in|ios::out|ios::binary);
	if( !user ) { cout << "�ɮפ��s�b1 ! " << endl;return 0;
	}
	fstream goods;//�ĤG�D�ɮ�
	goods.open("product.data", ios::in | ios::out | ios::binary );
	if( !goods ) { cout << "�ɮפ��s�b2 ! " << endl;return 0;
	}
	fstream report;//�ĤT�D�ɮ� 
	report.open("transData.data", ios::in | ios::out | ios::binary);
	if( !report ) { cout << "�ɮפ��s�b 3! " << endl;return 0;
	}
	cout<<" (1) �U�� (2) �޲z��"<<endl; 
	cin>>human;
	while(human==1){
		switch(menu()){
 		case 1: registered(user); break;  // ���U�b��
		case 2: number=login(user);	  break;  // �n���b�� 
		case 3: user.close(); exit(0);
		default:
			cerr << "�ﶵ���� " << endl;
			    break; 
		}
		if(number>1000)break;
		user.clear();
	}
	while(number>1000){
		switch(buyer()){
 		case 1: buy(number,report,user,goods);break;  // �ڭn�ʶR
		case 2: examine(number,report);break;  // �d�ݥ������ 
		case 3: report.close(); exit(0);
		default:
			cerr << "�ﶵ���� " << endl;
				break; 
		}
		report.clear();
	}
	while(human==2){
		switch(produce()){
 		case 1: Add(goods); 		goods.clear(); break;  // �s�W���~
		case 2: deleteGoods(goods);	goods.clear(); break;  // �R�����~  
		case 3: modify(goods);		goods.clear(); break;  // �קﲣ�~
		case 4: information(report);report.clear();break;  //������
		case 5: goods.close();      exit(0);			  //���}
		default:
			cerr << "�ﶵ���� " << endl;
			  	break; 
		}
		goods.clear();
	}
	
	return 0;
}



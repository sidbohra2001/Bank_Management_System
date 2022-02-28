
/**                   HEADER FILE USED IN PROJECT               **/

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

/**                   CLASS USED IN PROJECT                     **/

class Bank
{
    private:
        int account_no;
        char name[50];
        int deposit;
        char type;
        char mobile[12];
        char aadhar[13];
        char pan[12];
    public:
        void create_account();	//declaration of function to get data from user
        void show_account() const;	//declaration of function to show data on screen
        void modify();	//declaration of function to add new data
        void dep(int);	//declaration of function to accept amount and add to balance amount
        void withdraw(int);	//declaration of function to accept amount and subtract from balance amount
        void report() const;	//declaration of function to show data in tabular format
        int return_account_no() const;	//declaration of function to return account number
        int return_deposit() const;	//declaration of function to return balance amount
        char rettype() const;	//declaration of function to return type of account
};         //class ends here

/**     definition of function to get data from user          **/

void Bank::create_account()
{
	cout << "\nEnter The account No. : ";
	cin >> account_no;
	cout << "\nEnter the Name of the Account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout << "\nEnter type of the Account (C/S) : ";
	cin >> type;
	type=toupper(type);
	cout << "\nEnter the Initial Amount(>=500 for Saving and >=1000 for Current ) : ";
	cin >> deposit;
	cout << "\nEnter Mobile No.(10 digits) : ";
	cin.ignore();
	cin.getline(mobile,12);
	cout << "\nEnter PAN No. (10 characters) : ";
	cin.getline(pan, 12);
	cout << "\nEnter Aadhar No. (12 digits) : ";
	cin.getline(aadhar, 13);
	cin.ignore();
}

/**     definition of function to show data on screen       **/

void Bank::show_account() const
{
	cout << "\nAccount No. : " << account_no;
	cout << "\nAccount Holder Name : " << name;
	cout << "\nType of Account : " << type;
	cout << "\nBalance Amount : " << deposit;
	cout << "\nMobile No. : " << mobile;
	cout << "\nPAN No. : " << pan;
	cout << "\nAadhar No. : " << aadhar;
}

/**     declaration of function to add new data     **/

void Bank::modify()
{
	cout << "\nAccount No. : " << account_no;
	cout << "\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModify Type of Account(C/S) : ";
	cin >> type;
	type=toupper(type);
	cout << "\nModify Mobile No.(10 digits) : ";
	cin.ignore();
	cin.getline(mobile, 12);
	cout << "\nModify PAN No.(10 characters) : ";
	cin.getline(pan, 12);
	cout << "\nModify Aadhar No.(12 digits) : ";
	cin.getline(aadhar, 13);
}

/**     definition of function to accept amount and add to balance amount      **/

void Bank::dep(int x)
{
	deposit+=x;
}

/**     definition of function to accept amount and subtract from balance amount       **/

void Bank::withdraw(int x)
{
	deposit-=x;
}

/**     definition of function to show data in tabular format      **/

void Bank::report() const
{
	cout << account_no << setw(10) << " " << name << setw(10) << " " << type << setw(9) << deposit << setw(22) << mobile << setw(22) << pan << setw(22) << aadhar << endl;
}

/**     definition of function to return account number       **/

int Bank::return_account_no() const
{
	return account_no;
}

/**     definition of function to return balance amount        **/

int Bank::return_deposit() const
{
	return deposit;
}

/**     definition of function to return type of account       **/

char Bank::rettype() const
{
	return type;
}

/**    	function declaration        **/

void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to deposit/withdraw amount for given account
void intro();	//introductory screen function

/**    	THE MAIN FUNCTION OF PROGRAM        **/

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("CLS");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t01. NEW ACCOUNT";
		cout << "\n\n\t02. DEPOSIT AMOUNT";
		cout << "\n\n\t03. WITHDRAW AMOUNT";
		cout << "\n\n\t04. BALANCE ENQUIRY";
		cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout << "\n\n\t06. CLOSE AN ACCOUNT";
		cout << "\n\n\t07. MODIFY AN ACCOUNT";
		cout << "\n\n\t08. EXIT";
		cout << "\n\n\tSelect Your Option (1-8) ";
		cin >> ch;
		system("CLS");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout << "\n\n\tEnter The Account No. : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "\n\n\tEnter The Account No. : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "\n\n\tEnter The Account No. : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n\n\tEnter The Account No. : "; cin >> num;
			delete_account(num);
			break;
		 case '7':
			cout << "\n\n\tEnter The Account No. : "; cin >> num;
			modify_account(num);
			break;
		 case '8':
			cout << "\n\n\tTHANKS FOR USING BANK MANAGEMENT SYSTEM !!!";
			break;
		 default :cout << "\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}

/**    	function to write in file       **/

void write_account()
{
	Bank ac;
	int x = 0;
	ofstream outFile;
	ac.create_account();
	outFile.open("bank.dat",ios::binary | ios::app);
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
	cout << "\n\nAccount Created..";
	outFile.close();
}

/**    	function to read specific record from file          **/

void display_sp(int n)
{
	Bank ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("bank.dat",ios::binary);
	if(!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\nBALANCE DETAILS\n";

    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
	{
		if(ac.return_account_no() == n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag == false)
		cout << "\n\nAccount number does not exist !!!";
}

/**    	function to modify record of file       **/

void modify_account(int n)
{
	bool found=false;
	Bank ac;
	fstream File;
	File.open("bank.dat",ios::binary | ios::in | ios::out);
	if(!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Bank));
		if(ac.return_account_no() == n)
		{
			ac.show_account();
			cout << "\n\nEnter The New Details of Account..." << endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(Bank));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
			cout << "\n\n\t Record Updated !!!";
			found=true;
		  }
	}
	File.close();
	if(found == false)
		cout << "\n\n Record Not Found !!!";
}

/**    	function to delete record of file       **/

void delete_account(int n)
{
	Bank ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("bank.dat",ios::binary);
	if(!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
	{
		if(ac.return_account_no()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
		}
	}
	inFile.close();
	outFile.close();
	remove("bank.dat");
	rename("Temp.dat","bank.dat");
	cout << "\n\n\tRecord Deleted ..";
}

/**    	function to display all accounts deposit list       **/

void display_all()
{
	Bank ac;
	ifstream inFile;
	inFile.open("bank.dat",ios::binary);
	if(!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << " ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  == \n";
	cout << "A/c no.        Name                Type  Balance          Mobile No.           PAN No.         Aadhar No.\n";
	cout << " ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  == \n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
	{
		ac.report();
	}
	inFile.close();
}

/**    	function to deposit and withdraw amounts        **/

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	Bank ac;
	fstream File;
	File.open("bank.dat", ios::binary | ios::in | ios::out);
	if(!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Bank));
		if(ac.return_account_no() == n)
		{
			ac.show_account();
			if(option == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				cout << "\n\nEnter The Amount to be Deposited : ";
				cin >> amt;
				ac.dep(amt);
			}
			if(option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The Amount to be Withdrawn : ";
				cin >> amt;
				int bal=ac.return_deposit()-amt;
				if((bal<500 && ac.rettype() == 'S')  ||  (bal<1000 && ac.rettype() == 'C'))
					cout << "Insufficient balance";
				else
					ac.withdraw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
			cout << "\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found == false)
		cout << "\n\n Record Not Found ";
}

/**    	INTRODUCTION FUNCTION       **/

void intro()
{
    cout << "\n\n\n\t\t   BANK";
	cout << "\n\n\t\tMANAGEMENT";
	cout << "\n\n\t\t  SYSTEM";
	cout << "\n\n\n\n\tMade By : Siddhant Bohra";
	cout << "\n\tUniversity Roll No. : 2014881";
	cout << "\n\tSection : A";
	cout << "\n\tBranch : CSE (Core)";
	cout << "\n\tUniversity : Graphic Era Deemed to be University";
	cin.get();
}

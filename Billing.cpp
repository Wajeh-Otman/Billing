// Billing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//login as Administrator:
//              username: admin
//              password: 123

#include <iostream>
#include<fstream>
#include<string>

using namespace std;


class shopping
{
private:
	int pcode;
	float price;
	float dis;
	string pname;

public:
	void menu();
	void administrator();
	void buyer();
	void add();
	void edit();
	void rem();
	void list();
	void receipt();

};

void shopping::menu()
{
	m:
	int choice;
	string username;
	string password;

	cout << "\t\t\t\t________________________________________" << endl;
	cout << "\t\t\t\t                                        " << endl;
	cout << "\t\t\t\t         Supermarket Main Menu          " << endl;
	cout << "\t\t\t\t                                        " << endl;
	cout << "\t\t\t\t________________________________________" << endl;
	cout << "\t\t\t\t                                        " << endl;
	
	cout << "\t1) Administrator" << endl;
	cout << "\t2) Buyer" << endl;
	cout << "\t3) Exit" << endl;
	cout << "Please select: ";
	cin >> choice;

	switch (choice)
	{
		case 1:
			cout << "\n\tLOGIN" << endl;
			cout << "Enter Username: ";
			cin >> username;
			cout << "Enter Password: ";
			cin >> password;

			if (username=="admin" && password=="123")
			{
				administrator();
			}
			else
			{
				cout << "Invalid email or password" << endl;
			}
			break;

		case 2:
			buyer();
			break;

		case 3:
			exit(0);
			break;

		default:
			cout << "Invalid choice" << endl;
			break;
	}

	goto m;

}

void shopping::administrator()
{
	m:
	int choice;
	cout << "\n\n\t\tADMINISTRATOR MENU" << endl;
	cout << "\t1) Add product" << endl;
	cout << "\t2) Modify product" << endl;
	cout << "\t3) Delete product" << endl;
	cout << "\t4) Back to main menu" << endl;
	cout << "Please select: ";
	cin >> choice;

	switch (choice)
	{
		case 1:
			add();
			break;

		case 2:
			edit();
			break;

		case 3:
			rem();
			break;

		case 4:
			menu();
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
	}
	goto m;
}

void shopping::buyer() 
{
	m:
	int choice;
	cout << "\n\n\t\tBUYER" << endl;
	cout << "\t1) Buy product" << endl;
	cout << "\t2) Back to main menu" << endl;
	cout << "Please select: ";
	cin >> choice;

	switch (choice)
	{
		case 1:
			receipt();
			break;

		case 2:
			menu();
			break;

		default:
			cout << "Invalid choice" << endl;
			break;
	}
	goto m;
}


void shopping::add()
{
	m:
	fstream data;
	int c, token = 0;
	float p, d;
	string n;
	cout << "\n\n\t\tAdd new product" << endl;
	cout << "Enter product code: ";
	cin >> pcode;
	cout << "Enter product name: ";
	cin >> pname;
	cout << "Enter product price: ";
	cin >> price;
	cout << "Enter product discount: ";
	cin >> dis;
	cout << "\n";
	data.open("database.txt", ios::in);
	if (!data)
	{
		data.open("database.txt", ios::app| ios::out);
		data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
		data.close();
	}
	else
	{
		data >> c >> n >> p >> d;
		while (!data.eof())
		{
			if (c == pcode)
				token++;
			data >> c >> n >> p >> d;
		}
		data.close();
	}

	if (token == 1)
		goto m;
	else {
		data.open("database.txt", ios::app | ios::out);
		data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
		data.close();
	}
	cout << "\t\tProduct inserted!" << endl;
}

void shopping::edit()
{
	fstream data, data1;
	int pkey, token = 0, c;
	float p, d;
	string n;
	cout << "\n\n\t\tModify product" << endl;
	cout << "\tEnter product code: ";
	cin >> pkey;

	data.open("database.txt", ios::in);
	if (!data)
	{
		cout << "File doesn't exist!" << endl;
	}
	else
	{
		data1.open("database1.txt", ios::app | ios::out);
		data >> pcode >> pname >> price >> dis;
		while (!data.eof())
		{
			if (pkey==pcode)
			{
				cout << "Enter product new code: ";
				cin >> c;
				cout << "Enter product new name: ";
				cin >> n;
				cout << "Enter product new price: ";
				cin >> p;
				cout << "Enter product new discount: ";
				cin >> d;
				data1<< " " << c << " " << n << " " << p << " " << d << "\n";
				cout << "\t\tProduct edited!" << endl;
				token++;
			}
			else
			{
				data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
			}
			data >> pcode >> pname >> price >> dis;
		}
		data.close();
		data1.close();

		remove("database.txt");
		rename("database1.txt","database.txt");

		if (token == 0) {
			cout << "Product not found!" << endl;
		}
	}
}

void shopping::rem()
{
	fstream data, data1;
	int pkey, token = 0;
	cout << "\n\n\t\tDelete product" << endl;
	cout << "Enter product code: ";
	cin >> pkey;
	data.open("database.txt", ios::in);
	if (!data)
	{
		cout << "File doesn't exist!" << endl;
	}
	else
	{
		data1.open("database1.txt", ios::app | ios::out);
		data >> pcode >> pname >> price >> dis;
		while (!data.eof())
		{
			if (pkey == pcode)
			{
				cout << "\tProduct deleted successfully" << endl;
				token++;
			}
			else
			{
				data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
			}
			data >> pcode >> pname >> price >> dis;
		}

		data.close();
		data1.close();
		remove("database.txt");
		rename("database1.txt", "database.txt");

		if (token == 0)
			cout << "\tProduct not found!" << endl;
	}
}

void shopping::list()
{
	fstream data;
	data.open("database.txt", ios::in);
	cout << "\n_____________________________________________________________________" << endl;
	cout << "ProNo\t\tName\t\tPrice" << endl;
	cout << "_____________________________________________________________________" << endl;
	data >> pcode >> pname >> price >> dis;
	while (!data.eof())
	{
		cout << pcode << "\t\t" << pname << "\t\t" << price << endl;
		data >> pcode >> pname >> price >> dis;
	}
	data.close();

}

void shopping::receipt()
{
	fstream data;
	int arrc[100];//array of codes
	int arrq[100];//array of quantity
	int c = 0;
	char choice;
	float amount = 0, dis = 0, total = 0;
	cout << "\n\n\t\tRECEIPT" << endl;

	data.open("database.txt", ios::in);
	if (!data)
	{
		cout << "\nEmpty database!" << endl;
	}
	else
	{
		data.close();
		list();
		cout << "\n\t\t_______________________________" << endl;
		cout << "\t\t        Place your order" << endl;
		cout << "\t\t_______________________________" << endl;


		do
		{
			m:
			cout << "Enter product code: ";
			cin >> arrc[c];
			cout << "Enter product quantity: ";
			cin >> arrq[c];
			for (int i = 0; i < c; i++)
			{
				if (arrc[c] == arrc[i])
				{
					cout << "Duplicate product code, please try again" << endl;
					goto m;
				}
			}
			c++;
			
			cout << "Do you want to but another product (y/n): ";
			cin >> choice;
			cout << endl;
		} while (choice=='y');
		cout << "\n\n\t\t___________________RECEIPT___________________" << endl;
		cout << "Product No\t Product Name\t Product quanitiy\t Price\t Amount\t Amount with dicount"
			<< endl;
		
		//cout << "***c = " << c << endl;
		for (int i = 0; i < c; i++)
		{
			
			
			data.open("database.txt", ios::in);
			data >> pcode >> pname >> price >> dis;
			
			while (!data.eof())
			{
				
				if (pcode == arrc[i]) {
				//	cout << "***i = " << i << endl;
					//cout << "***pcode = " << pcode << "  pname = " << pname << "  price = " << price
						//<< "  dis = " << dis << endl;
					amount = price * arrq[i];
					dis = amount - (amount * dis / 100);
					total = total + dis;
					cout << "\n" << pcode <<"\t\t " << pname << "\t\t " << arrq[i] << "\t\t\t " 
						<< price<< "\t " << amount << "\t\t" << dis;
				}
				data >> pcode >> pname >> price >> dis;
				
			}
			data.close();

		}
		
	}
	cout << "\n\n______________________________________" << endl;
	cout << "Total amount: "<<total << endl;
}

int main() 
{
	shopping s;
	s.menu();
}
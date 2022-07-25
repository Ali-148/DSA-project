#ifndef _FILEMANAGER_H
#define _FILEMANAGER_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <sstream>
#include <limits>
#include <string.h>
#include "SaleDLinkedList.h"
#include"ProductDLinkedList.h"
using namespace std;

class FileManager
{
private:

	ProductList P;
	SaleList S;
	int salescount;
	int productcount;
public:

	FileManager()
	{
		ifstream f1("Sales.txt");
		ifstream f2("Product.txt");
		if (!f2)
		{
			Create_ProductFile();
		}
		else
		{
			readProducts();
		}
		if (!f1)
		{
			Create_SalesFile();
		}
		else
		{
			readSales();
		}
	}
	void sortProductsID()

	{
		P.mergeSortID(P.head);
		//	P.viewList();
		fstream fin("Product.txt", ios::in | ios::out);
		remove("Product.txt");
		Create_ProductFile();
		ProductNode* t = P.head;
		for (; t != NULL; t = t->next)
			append_product(t);

	}
	void sortProductsPrice()

	{
		P.mergeSortPrice(P.head);
		//	P.viewList();
		fstream fin("Product.txt", ios::in | ios::out);
		remove("Product.txt");
		Create_ProductFile();
		ProductNode* t = P.head;
		for (; t != NULL; t = t->next)
			append_product(t);

	}
	void sortSales()
	{
		S.RadixSort();
		//P.viewList();
		fstream fin("Sales.txt", ios::in | ios::out);
		rename("Sales.txt", "sort.txt");
		remove("Sales.txt");
		Create_SalesFile();
	//	S.viewList();
		SalesNode* t1 = S.head;

		for (; t1 != NULL; t1 = t1->next) {

			int i = getSaleID(t1->data.get_amountSold(), t1->data.get_discount(), t1->data.get_listPrice());
			//cout << i << endl;
			ProductNode* t = P.searchID(i);
			double	p = t->data.get_costPrice();
			char * n = t->data.get_name();
			append_sale(t1, n, i);
		}
	}

	int getSaleID(int a, float d, double p)

	{
		int am, i;
		float dis;
		double pr;
		int counter = 0;

		ifstream fout("sort.txt");
		string data;
		while (getline(fout, data))
		{

		//	getline(fout, data);
			string d2 = data;

			for (char &c : d2)
			{
				if (!isdigit(c) && c != '.')
					c = ' ';
			}
			std::stringstream ss(d2);
			ss << std::setprecision(4);
			ss >> i;
			ss >> am;

			for (int i = 0; i < 4; i++)
			{
				ss >> dis;
			}
			ss >> pr;
			if (am == a && dis == d && pr == p)
			{
				return i;

			}

			counter++;

			data.clear();
		}
	}

	void removeProduct()
	{
		P.deleteNode();
		fstream fin("Product.txt", ios::in | ios::out);
		remove("Product.txt");
		Create_ProductFile();
		ProductNode* t = P.head;
		for (; t != NULL; t = t->next)
			append_product(t);
	}
	void removeProductbyID(int id)
	{
		P.deleteID(id);
		fstream fin("Product.txt", ios::in | ios::out);
		remove("Product.txt");
		Create_ProductFile();
		ProductNode* t = P.head;
		for (; t != NULL; t = t->next)
			append_product(t);
	}
	void removeProductbyName(char*name)
	{
		P.deleteName(name);
		fstream fin("Product.txt", ios::in | ios::out);
		remove("Product.txt");
		Create_ProductFile();
		ProductNode* t = P.head;
		for (; t != NULL; t = t->next)
			append_product(t);
	}
	void removeSale()
	{
		S.deleteNode();
		//P.viewList();
		fstream fin("Sales.txt", ios::in | ios::out);
		rename("Sales.txt", "sort.txt");
		remove("Sales.txt");
		Create_SalesFile();
	//	S.viewList();
		SalesNode* t1 = S.head;

		for (; t1 != NULL; t1 = t1->next) {

			int i = getSaleID(t1->data.get_amountSold(), t1->data.get_discount(), t1->data.get_listPrice());

			ProductNode* t = P.searchID(i);
			double	p = t->data.get_costPrice();
			char * n = t->data.get_name();
			append_sale(t1, n, i);
		}
	}
	void removeSalebyDate(char*n)
	{
		bool d = S.delete_datesold(n);
		if (!d)
			return;
		//P.viewList();
		fstream fin("Sales.txt", ios::in | ios::out);
		rename("Sales.txt", "sort.txt");
		remove("Sales.txt");
		Create_SalesFile();
	//	S.viewList();
		SalesNode* t1 = S.head;

		for (; t1 != NULL; t1 = t1->next) {

			int i = getSaleID(t1->data.get_amountSold(), t1->data.get_discount(), t1->data.get_listPrice());

			ProductNode* t = P.searchID(i);
			double	p = t->data.get_costPrice();
			char * n = t->data.get_name();
			append_sale(t1, n, i);
		}
	}
	void viewProduct()
	{
		ifstream fin("Product.txt");

		string data;
		while (getline(fin, data))
		{

			if (data[0] != ' ')
				cout << data << endl;
		}
		fin.close();
	}
	void viewSales()
	{
		ifstream fin("Sales.txt");

		string data;
		while (getline(fin,data))
		{
			
			if (data[0] != ' ')
				cout << data << endl;
		}
		fin.close();
	}
	void readProduct()
	{
		int i, q;
		double p;

		char s[1];
		s[0] = ' ';

		int counter = 0;
		int r = 0;
		fstream fin("Product.txt", ios::in | ios::out);
		char data[62];
		while (counter <= 20)
		{
			fin.getline(data, 62);

			if (strncmp(&data[0], "    ", 4) != 0 && counter != 0)
			{
				//std::string str;
				cout << data[7] << endl;
				cout << counter << endl;
				char *e = new char;
				char *n = new char;
				fin.seekp(62 * counter);
				fin >> i;


				cout << i;
				fin.seekg(62 * counter + 5);
				fin.get(n, 23);
				fin.seekg(62 * counter + 30);
				fin >> q;
				fin.seekg(62 * counter + 45);
				fin.get(e, 11);
				fin.seekg(62 * counter + 56);
				fin >> p;
			//	cout << "Reading Product in File...." << endl;

				P.append(i, n, q, e, p);
				//	delete e;
					//delete n;
					//P.viewList();
					//	memset(n, 0, 25);
					//memset(e, 0, 10);


			}
			counter++;
			memset(data, 0, sizeof(data));
			//	cout << counter << endl;
			//	fin.close();
		}
	}
	void readSales()
	{

		int a, i;
		float dis;
		double p;
		int counter = 0;
		ifstream fout("Sales.txt");
		string data;
	/*	while (counter <= 20)
		{*/

			while (getline(fout, data)){

			if (data[0] != ' ' && counter != 0)
			{
				string d2 = data;

				for (char &c : d2)
				{
					if (!isdigit(c) && c != '.')
						c = ' ';
				}
				std::stringstream ss(d2);
				ss << std::setprecision(4);
				//std::string str;
				//cout << data[7] << endl;
				//cout << s[0] << endl;
			/*	cout << counter << endl;*/
				char* d = new char;
				//fin.seekg(62 * counter);
			//	fin >> i;
				ss >> i;
				ss >> a;
				//fin.seekg(62 * counter + 5);
				for (int i = 40, j = 0; i <= 49; i++, j++)
				{
					d[j] = data[i];
				}
				//fin.get(n, 23);
				/*char * fd = new char;
				for (int i = 0; i < 10; i++)
				{
					fd[i] = d[i];
				}
				if (strlen(fd) > 10)
				{
					cout << "Date no" << endl;
				}*/


				for (int i = 0; i < 4; i++)
				{
					ss >> dis;
				}

				/*	fin2.seekg(62 * counter + 30);
					fin2 >> q;

					fin.seekg(62 * counter + 56);
					fin >> p;

					//fin.seekg(62 * counter + 45);*/


				ss >> p;

				S.append(p, dis, a, d);



			}

			counter++;

			data.clear();
		}
	}

	void readProducts()
	{
		int i, q;
		double p;
		int counter = 0;
		ifstream fout("Product.txt");
		string data;
	/*	while (counter <= 20)
		{*/

			while (getline(fout, data)){

			if (data[0] != ' ' && counter != 0)
			{
				string d2 = data;

				for (char &c : d2)
				{
					if (!isdigit(c))
						c = ' ';
				}
				std::stringstream ss(d2);
				//std::string str;
				//cout << data[7] << endl;
				//cout << s[0] << endl;
				/*cout << counter << endl;*/
				char* e = new char;
				char *n = new char;
				//fin.seekg(62 * counter);
			//	fin >> i;
				ss >> i;

				//fin.seekg(62 * counter + 5);
				int en = 5;
					for (int i = 5; i < 30; i++)
					{
						if (data[i] == ' ' && data[i + 1] == ' ')
						{
							en = i;
							break;
						}
				}
				
				for (int i = 5, j = 0; i < en; i++, j++)
				{
					n[j] = data[i];
				}
				//fin.get(n, 23);
				for (int i = 0; i < 1; i++)
				{
					ss >> q;
				}
				for (int i = 0; i < 4; i++)
				{
					ss >> p;
				}

				/*	fin2.seekg(62 * counter + 30);
					fin2 >> q;

					fin.seekg(62 * counter + 56);
					fin >> p;

					//fin.seekg(62 * counter + 45);*/
				for (int i = 45, j = 0; i <= 54; i++, j++)
				{
					e[j] = data[i];
				}



				P.append(i, n, q, e, p);



			}

			counter++;

			data.clear();
		}

	}
	void editProduct(int i)
	{
		P.editiD(i);
		fstream fin("Product.txt", ios::in | ios::out);
		remove("Product.txt");
		Create_ProductFile();
		ProductNode* t = P.head;
		for (; t != NULL; t = t->next)
			append_product(t);
	}

	void add_sale(int i) {


		double p;
		/*fstream f1("Product.txt", ios::in | ios::out);
		char data[65];*/
		char *n = new char;
		bool f = false;
		int count = 0;

		/*while (!f1.eof())
		{
			f1.getline(data, 62);
			if (strncmp(&data[0], i, strlen(i)) == 0)
			{
				f1.seekp(62 * count + 4);
				f1.ignore();
				f1.get(n, 20);
				f1.seekp(62 * count + 56);
				f1 >> p;
				cout << "Reading Product in File...." << endl;
				f = true;
				break;

			}
			count++;

		}
		f1.close();*/
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		/*if (!f)
		{
			cout << "Product not found!" << endl;
			return;
		}*/
		ProductNode* t = P.searchID(i);
		if (!t)
			return;
		int q = t->data.get_qty();
		p = t->data.get_costPrice();
		n = t->data.get_name();
		S.append(p);
		if (S.tail->data.get_amountSold() > q)
		{
			cout << "Amount sold can't be more than quantity!" << endl;
			return;
		}
		q = q - S.tail->data.get_amountSold();
		editQuantity(i, q);
		append_sale(S.tail, n, i);
//		salescount = S.count;
	}

	void add_product() {
		int c = P.count;
		P.append();
	
		//P.viewList();
		if (c == P.count)
			return;
		append_product(P.tail);
	}
	void editQuantity(int i, int q)
	{
		bool c = P.editQuantity(i, q);
		if (!c)
			return;
		fstream fin("Product.txt", ios::in | ios::out);
		remove("Product.txt");
		Create_ProductFile();
		ProductNode* t = P.head;
		for (; t != NULL; t = t->next)
			append_product(t);
	}
	void append_sale(SalesNode* n, char *name, int i)
	{
		int a = n->data.get_amountSold();
	/*	cout << a << endl;*/
		fstream fin("Sales.txt", ios::in | ios::out);
	/*	char data[72];*/
		string data;
		char * d = new char;
		d = n->data.get_dateSold();
		int count = 0;
		while (getline(fin, data)) {
		
			if (data[0] == ' ')
			{
				fin.seekp(70 * count + 30);
				fin << a;
				fin.seekp(70 * count);
				fin << i;
				fin.seekp(70 * count + 5);
				fin << name;
				fin.seekp(70 * count + 40);
				for (int i = 0; i <10;i++)
               fin << d[i];
				fin.seekp(70 * count + 51);
				fin << n->data.get_discount();
				fin.seekp(70 * count + 61);
				fin << n->data.get_listPrice();

			//	cout << "Adding Sale in File...." << endl;

				break;
			}
			count++;
		}
		fin.close();
	}
	void append_product(ProductNode* n)
	{
		fstream fin("Product.txt", ios::in | ios::out);
		string data;
		int count = 0;
		while (getline(fin, data)) {

			if (data[0] == ' ')
			{
				fin.seekp(62 * count);
				fin << n->data.get_id();
				fin.seekp(62 * count + 5);
				fin << n->data.get_name();
				fin.seekp(62 * count + 30);
				fin << n->data.get_qty();
				fin.seekp(62 * count + 45);
				fin << n->data.get_expiry();
				fin.seekp(62 * count + 56);
				fin << n->data.get_costPrice();

				fin.close();
				cout << "Adding Product in File...." << endl;

				break;
			}
			count++;
		}
		fin.close();
	}



	void Create_ProductFile()
	{
		ofstream fout("Product.txt");

		fout << left << setw(5) << "ID";
		fout << left << setw(25) << "Name";
		fout << left << setw(15) << "Quantity";
		fout << left << setw(11) << "Expiry";
		fout << left << setw(5) << "Price" << endl;
		for (int i = 1; i < 21; i++)
		{
			fout << left << setw(5) << " ";
			fout << left << setw(25) << " ";
			fout << left << setw(15) << " ";
			fout << left << setw(11) << " ";
			fout << left << setw(5) << 0 << endl;
		}
		fout.close();
		//62
	}

	void Create_SalesFile()
	{
		ofstream fout("Sales.txt");

		fout << left << setw(5) << "ID";
		fout << left << setw(25) << "Name";
		fout << left << setw(10) << "Amount";
		fout << left << setw(11) << "Date Sold";
		fout << left << setw(10) << "Discount%";
		fout << left << setw(8) << "Price" << endl;
		for (int i = 1; i < 21; i++)
		{
			fout << left << setw(5) << " ";
			fout << left << setw(25) << " ";
			fout << left << setw(10) << " ";
			fout << left << setw(11) << " ";
			fout << left << setw(10) << " ";
			fout << left << setw(8) << 0 << endl;
		}
		fout.close();
		//66
	}
	void menu_employee()
	{

		int op;
		int n;
		int data;

		cout << "" << endl;
		cout << "\n";
		int index;

		while (true)
		{
			cout << "Enter 1 to Remove the latest Sale\n";
			cout << "Enter 2 to Add a Sale\n";
			cout << "Enter 3 View Sales\n";
			cout << "Enter 4 to Remove Sale by Date\n";
			cout << "Enter 5 to Search Price\n";
			cout << "Enter 6 to Search Date Sold\n";
			cout << "Enter 7 to Search Amount Sold\n";
			cout << "Enter 8 to Sort Sales by Amount sold\n";
			cout << "Enter 0 ot Exit\n";
			cin >> op;
			switch (op) {
			case 1: {
				removeSale();

				break;
			}
			case 2: {
				int id;
				cout << "Enter the ID of the Product" << endl;
				cin >> id;
				add_sale(id);
				break;
			}
			case 3: {
				//cout << "Linked list: " << endl;
				viewSales();
				//cout << "" << endl;
				break;
			}

			case 4: {
				cin.ignore();
				char* n = new char;
				cout << "Enter the date: " << endl;
				cin.getline(n, 11);
				removeSalebyDate(n);
				break;

			}

			case 5: {
				double n;
				cin.ignore();
				cout << "Enter the Sale_price to Search: " << endl;
				cin >> n;
				S.search_bysaleprice(n);
				break;

			}
			case 6: {
				char* i = new char;
				cout << "Enter the Date_sold to Search: " << endl;
				cin >> i;
				S.search_datesold(i);
				break;

			}
			case 7: {
				int i;
				cout << "Enter the Amount_sold to Search: " << endl;
				cin >> i;
				S.search_amountsold(i);
				break;

			}
			case 8: {
				sortSales();
				break;
			}
			case 0: {
				return;
			}
			}
		}
	}
	void portal()
	{
		int i;
		cout << "Press 1 for the Employee Portal or 2 for the Manager Portal: " << endl;
		cin >> i;
		if (i == 1)
		{
			menu_employee();
		}
		else if (i == 2)
		{

			while (i != 123)
			{
				cout << "Enter the password to gain accesss: " << endl;
				cin >> i;

			}
			menu_manager();;
		}
		else
			cout << "Wrong input!" << endl;
	}
	void menu_manager()
	{
		int op;
		int n;
		int data;

		cout << "" << endl;
		cout << "\n";
		int index;

		while (true)
		{
			int op;
			int n;
			int data;

			cout << "" << endl;
			cout << "\n";
			int index;

			while (true)
			{
				cout << "Enter 1 to Remove the latest Sale\n";
				cout << "Enter 2 to Add a Sale\n";
				cout << "Enter 3 View Sales\n";
				cout << "Enter 4 to Remove Sale by Date\n";
				cout << "Enter 5 to Search Sale by Price Sold\n";
				cout << "Enter 6 to Search Sale by Date Sold\n";
				cout << "Enter 7 to Search Sale Amount Sold\n";
				cout << "Enter 8 to Sort Sales by Amount sold\n";
				cout << "Enter 9 to Add a Product\n";
				cout << "Enter 10 to Remove the latest Product\n";
				cout << "Enter 11 to Remove a Product by ID\n";
				cout << "Enter 12 to Remove a Product by Name\n";
				cout << "Enter 13 to sort Products by ID\n";
				cout << "Enter 14 to sort Products Price\n";
				cout << "Enter 15 to View Products\n";
				cout << "Enter 16 to Search by Name of Product\n";
				cout << "Enter 17 to Search by ID of Product\n";
				cout << "Enter 18 to Search by QTY of Product\n";
				cout << "Enter 19 to Edit a Product Name, Price and QTY\n";
				cout << "Enter 20 to Update QTY of a Product\n";
				cout << "Enter 0 ot Exit\n";
				cin >> op;
				switch (op) {
				case 1: {
					removeSale();

					break;
				}
				case 2: {
					int id;
					cout << "Enter the ID of the Product" << endl;
					cin >> id;
					add_sale(id);
					break;
				}
				case 3: {
					//cout << "Linked list: " << endl;
					viewSales();
					//cout << "" << endl;
					break;
				}

				case 4: {
					cin.ignore();
					char* n = new char;
					cout << "Enter the date: " << endl;
					cin.getline(n, 11);
					removeSalebyDate(n);
					break;

				}

				case 5: {
					double n;
					cin.ignore();
					cout << "Enter the Sale_price to Search: " << endl;
					cin >> n;
					S.search_bysaleprice(n);
					break;

				}
				case 6: {
					char* i = new char;
					cout << "Enter the Date_sold to Search: " << endl;
					cin.ignore();
					cin.getline(i, 11);
					S.search_datesold(i);
					break;

				}
				case 7: {
					int i;
					cout << "Enter the Amount_sold to Search: " << endl;
					cin >> i;
					S.search_amountsold(i);
					break;

				}
				case 8: {
					sortSales();
					break;
				}
				case 9: {
					add_product();
					break;
				}
				case 10: {
					removeProduct();
					break;
				}
				case 11: {
					int i;
					cout << "Enter the ID to delete: " << endl;
					cin >> i;
					removeProductbyID(i);
					break;
				}
				case 12: {
					char* i = new char;
					cout << "Enter the Name to Search: " << endl;
					cin.ignore();
					cin.getline(i, 25);
					removeProductbyName(i);
					break;
				}
				case 13: {
					sortProductsID();
					break;
				}
				case 14: {
					sortProductsPrice();
					break;
				}
				case 15: {
					viewProduct();
					break;
				}
				case 16: {
					char* i = new char;
					cout << "Enter the Name to Search: " << endl;
					cin.ignore();
					cin.getline(i, 25);
					P.searchName(i);
					break;
				}
				case 17: {
					int i;
					cout << "Enter the ID to Search: " << endl;
					cin >> i;
					P.viewID(i);
					break;
				}
				case 18: {
					int i;
					cout << "Enter the QTY to Search: " << endl;
					cin >> i;
					P.searchQTY(i);
					break;
				}
				case 19: {
					int i;
					cout << "Enter the ID of Product to Edit: " << endl;
					cin >> i;
					editProduct(i);
					break;
				}
				case 20: {
					int i,q;
					cout << "Enter the ID of Product to Edit: " << endl;
					cin >> i;
					cout << "Enter the updated QTY: " << endl;
					cin >> q;
					editQuantity(i,q);
					break;
				}
	
				case 0: {
					return;
				}
				}
			}
		}
	}
};

#endif 

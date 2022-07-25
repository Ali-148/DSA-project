#pragma once
#include <iostream>
#include <limits>
using namespace std;
#include <cstring>
#include <string.h>
class Product
{
private:
	char* name;
	double listPrice;
	char* expiry;
	int qty;
	int id;
public:
	Product()
	{
		name = new char;
		listPrice = 0;
		expiry = new char;
		qty = 0;
		id = 0;

	}
	void set_name(char* name)
	{
		this->name = name;
	}
	char* get_name()
	{
		return name;
	}
	void set_costPrice(double costPrice)
	{
		this->listPrice = costPrice;
	}
	double get_costPrice()
	{
		return listPrice;
	}
	void set_expiry(char* expiry)
	{
		this->expiry = expiry;
	}
	char* get_expiry()
	{
		return expiry;
	}
	void set_qty(int qty)
	{
		this->qty = qty;
	}
	int get_qty()
	{
		return qty;
	}
	void set_id(int id)
	{
		this->id = id;
	}
	int get_id()
	{
		return id;
	}


	void createProduct()
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
		cout << "Enter the product name: " << endl;
		cin.getline(name, 25);
	//	cin.ignore();
		cout << "Enter the Expiry Date: " << endl;
		while (!validateDate(expiry))
		{
			cin.getline(expiry, 11);
		}
		cout << "Enter the Quantity: " << endl;
		cin >> qty;
		
		cout << "Enter the ID: " << endl;
		while (!validateID(id))
		{
			cin >> id;
		}
		cout << "Enter the List Price: " << endl;
		cin >> listPrice;
	}

	void editProduct()
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Enter the new product name: " << endl;
		cin.getline(name, 25);
		//	cin.ignore();
		cout << "Enter the new Quantity: " << endl;
		cin >> qty;
		cout << "Enter the new List Price: " << endl;
		cin >> listPrice;
	}

	bool compareName(char* n)
	{
	/*	if (strlen(n) != strlen(name))
		{
			return false;
		}*/
	/*	for (int i = 0; i < strlen(name); i++)
		{
			if (n[i] != name[i])
				return false;
		}*/
		if (strncmp(n, name, strlen(name)) == 0)
			return true;
		else
			return false;
		return true;

	}
	bool validateDate(char* date)
	{
		if (strncmp(&date[2], "/", 1) == 0 && strncmp(date, "/", 5) && strlen(date) == 10)
		{
			return true;
		}
		return false;
	}
	bool validateID(int id)
	{
		if (id % 1000 != 0)
		{
			return true;
		}
		return false;
	}
	void display()
	{
		cout << "Name: " << name << endl;
		cout << "Exp: " << expiry << endl;
		cout << "ID: " << id << endl;
		cout << "QTY: " << qty << endl;
		cout << "Price: " << listPrice << endl;
		

	}
};

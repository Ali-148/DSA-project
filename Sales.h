#pragma once
#include <iostream>
using namespace std;
#include <cstring>
#include <string.h>

class Sale
{
private:
	double salePrice;
	float discount;
	int amountSold;
	char* dateSold;
	bool isDiscount;
public:
	Sale()
	{
		salePrice = 0;
		discount = 0;
	//	amountSold = 0;
		dateSold = new char;
		isDiscount = false;
	}
	void set_listPrice(double listPrice)
	{
		this->salePrice = listPrice;
	}
	double get_listPrice()
	{
		return salePrice;
	}
	void set_discount(float discount)
	{
		this->discount = discount;
	}
	float get_discount()
	{
		return discount;
	}
	void set_amountSold(int amountSold)
	{
		this->amountSold = amountSold;
	}
	int get_amountSold()
	{
		return amountSold;
	}
	void set_dateSold(char* dateSold)
	{
		this->dateSold = dateSold;
	}
	char* get_dateSold()
	{
		return dateSold;
	}
	void createSale(double p)
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter the Date Sold: " << endl;
		while (!validateDate(dateSold))
		{
			cin.getline(dateSold, 11);
		}
		cout << "Enter the Amount Sold: " << endl;
		cin >> amountSold;	
		cout << "Is there a discount? Y/N: ";
		char c;
		cin >> c;
		if (c == 'Y' || c == 'y')
		{
			cout << "Enter the Discount: " << endl;
			cin >> discount;
			isDiscount = true;
		}
		salePrice = (p)-(p*(discount/100.0));
		cout << "The Sale Price is: " << salePrice << endl;

	}
    bool compareDate(char* n)
    {
        /*if (strlen(n) != strlen(dateSold))
        {
            return false;
        }*/
       /* for (int i = 0; i < strlen(dateSold); i++)
        {
            if (n[i] != dateSold[i])
                return false;
        }*/
		if (strncmp(n, dateSold, 10) == 0)
			return true;
		else
			return false;
    }
    bool validateDate(char* date)
    {
        if (strncmp(&date[2], "/", 1) == 0 && strncmp(date, "/", 5) && strlen(date) == 10)
        {
            return true;
        }
        return false;
    }
	bool issDiscount()
	{
		return isDiscount;
	}
    void display()
    {
        cout << "DateSold: " << dateSold << endl;
        cout << "Discount%: " << discount << endl;
        cout << "Amount_Sold: " << amountSold << endl;
        cout << "SalePrice: " << salePrice << endl;
    }
};

#ifndef _PRODUCTDLINKEDLIST_H
#define _PRODUCTDLINKEDLIST_H
#include <iostream>
#include <limits>
#include"Product.h"
using namespace std;
class ProductNode {

private:
	Product data;
	ProductNode *next;
	ProductNode *prev;
public:

	ProductNode()
	{
		
		next = NULL;
		prev = NULL;

	}

	
	ProductNode* getNext()
	{
		return this->next;
	}
	ProductNode* getPrev()
	{
		return this->prev;
	}
	void setNext(ProductNode* N)
	{
		this->next = N;
	}
	void setPrev(ProductNode* N)
	{
		this->prev = N;
	}
	friend class ProductList;
    friend class FileManager;
};

class ProductList
{
private:
	ProductNode *head;
	ProductNode *tail;
	int count;
public:
	ProductList()
	{
		head = NULL;
		tail = NULL;
		count = 0;
	}



	void oldappend()
	{
		ProductNode *temp = new ProductNode;
	// temp->data.createProduct();
		//temp->data.set_name("A");
	
		temp->next = NULL;
		temp->prev = NULL;
		if (head == NULL)
		{
		
			head = temp;
			tail = temp;
			count = 1;
			return;
		}
		count++;
		tail->next = temp;
		temp->prev = tail;
		tail = tail->next;

	}
	bool editQuantity(int i, int q)
	{
		if (head == NULL)
		{
			cout << "Empty!" << endl;
			return 0;
		}
		ProductNode* temp = head;
		bool f = false;
		while (temp)
		{
			if (temp->data.get_id() == i)
			{
				f = true;
				temp->data.set_qty(q);
				return 1;
	
			}
			temp = temp->next;
		}
		if (!f)
		{
			cout << "Not found!" << endl;
			return 0;
		}
	}
	void append()
	{
		ProductNode* temp = new ProductNode;
		temp->data.createProduct();

		if (!isUnique(temp->data.get_id()))
		{
			cout << "The ID you entered already exists, try again!" << endl;
			return;
		}
		temp->next = NULL;
		if (head == NULL && count == 0)
		{
			head = temp;
			tail = temp;
			tail->next = NULL;
			count = 1;
			return;
		}
		count++;
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
	void append(int i, char *n, int q, char*e, double p )
	{
		ProductNode* temp = new ProductNode;
		temp->data.set_id(i);
		/*if (!isUnique(i))
		{
			cout << "ID exists already" << endl;
			return;;
		}*/
		temp->data.set_name(n);
		temp->data.set_expiry(e);
		temp->data.set_qty(q);
		temp->data.set_costPrice(p);
		/*	if (!isUnique(temp->data.get_id()))
			{
				cout << "The ID you entered already exists, try again!" << endl;
				return;
			}*/
		temp->next = NULL;
		if (head == NULL && count == 0)
		{
			head = temp;
			tail = temp;
			tail->next = NULL;
			count = 1;
			return;
		}
		count++;
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
	void addHead()
	{
		ProductNode *temp = new ProductNode;
		temp->data.createProduct();
		if (!isUnique(temp->data.get_id()))
		{
			cout << "The ID you entered already exists, try again!" << endl;
			return;
		}
		temp->prev = NULL;
		if (isEmpty() == true)
		{
			head = temp;
			tail = temp;
			tail->next = NULL;
			count = 1;
			return;
		}
		count++;
		temp->next = head;
		temp->prev = NULL;
		head = temp;
		head->next->prev = head;
		head->next->next = NULL;
		tail = head->next;

	}
	void viewList()
	{
		ProductNode* traverse = head;
		if (head == NULL)
		{
			cout << "No elements in list" << endl;
			return;
		}
		while (traverse != NULL)
		{
			traverse->data.display();
			cout << " " << endl;
			traverse = traverse->next;
		}
		cout << "" << endl;
		cout << "Index: " << count << endl;

	}
	void deleteNode()
	{
		if (isEmpty() == true)
		{
			cout << "No elements in list" << endl;
			return;
		}
		if (head->next == NULL)
		{
			head = NULL;
			tail = NULL;
			count = 0;
			cout << "Deleted! " << endl;
			return;
		}
		ProductNode *temp = tail;
		tail = tail->prev;
	//	delete temp;
		tail->next = NULL;
		count--;
	
		cout << "Deleted! " << endl;
	}
	void insertIndex(int i)
	{

		if (count == 0)
		{
			cout << "List is empty and data will be entered at first index" << endl;
			addHead();
			return;
		}
		if (i == 1)
		{
			cout << "Prepending!" << endl;
			addHead();
			return;
		}
		if (i < 1 || i > count + 1)
		{
			cout << "Invalid index" << endl;
			return;
		}
		if (i == count + 1)
		{
			cout << "Appending!" << endl;
			append();
			return;
		}// Corner cases dealt with
		ProductNode* temp = head;
		int counter = 1;
		while (temp != NULL)
		{
			if (counter == i)
			{
				ProductNode * t2 = new ProductNode;
				if (!isUnique(t2->data.get_id()))
				{
					cout << "The ID you entered already exists, try again!" << endl;
					return;
				}
				t2->data.createProduct();
				t2->next = temp;
				temp->prev->next = t2;
				t2->prev = temp->prev;
				temp->prev = t2;

			}
			counter++;
			temp = temp->next;
		}
		count++;
		cout << "Inserted!" << endl;
	}
	void deletehead()
	{
		if (isEmpty() == true)
		{
			cout << "No elements in list" << endl;
			return;
		}
		if (head->next == NULL)
		{
			head = NULL;
			tail = NULL;
			count = 0;
			cout << "Deleted!" << endl;
			return;
		}
		ProductNode* temp = head;
		head = head->next;
		head->prev = NULL;
		count--;
		delete temp;
	}
	void deleteIndex(int i)
	{
		if (isEmpty())
		{
			cout << "List is empty" << endl;
			return;
		}
		if (i == 1)
		{
			cout << "Deleting head!" << endl;
			deletehead();
			return;
		}
		if (i < 1 || i > count)
		{
			cout << "Invalid index" << endl;
			return;
		}
		if (i == count)
		{
			cout << "Deleting tail!" << endl;
			deleteNode();
			return;
		}// Corner cases dealt with
		ProductNode* temp = head;
		int counter = 1;
		while (temp != NULL)
		{
			if (counter == i)
			{
		
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
break;

			}
			counter++;
			temp = temp->next;
		}
		count--;
		cout << "Deleted!" << endl;
	}
	void deleteID(int n)
	{
		if (isEmpty())
		{
			cout << "List is empty" << endl;
			return;
		}
		ProductNode * temp = head;
		while (temp != NULL)
		{
			if (temp->data.get_id() == n)
			{
				if (temp->prev == NULL)
				{
					cout << "Deleting head!" << endl;
					deletehead();
					return;
				}
				if (temp->next == NULL)
				{
					cout << "Deleting tail!" << endl;
					deleteNode();
					return;
				}
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				count--;
				cout << "Deleted!" << endl;
				return;

			}
			temp = temp->next;
			
		}
		cout << "Not found!" << endl;
	}
	void deleteName(char* n)
	{
		if (isEmpty())
		{
			cout << "List is empty" << endl;
			return;
		}
		ProductNode* temp = head;
		while (temp != NULL)
		{
			if (temp->data.compareName(n))
			{
				if (temp->prev == NULL)
				{
					cout << "Deleting head!" << endl;
					deletehead();
					return;
				}
				if (temp->next == NULL)
				{
					cout << "Deleting tail!" << endl;
					deleteNode();
					return;
				}
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				count--;
				cout << "Deleted!" << endl;
				return;

			}
			temp = temp->next;

		}
		cout << "Not found!" << endl;
	}
	void searchName(char* N)
	{
		if( head == NULL)
	{
		cout << "Empty!" << endl;
		return;
	}
		ProductNode* temp = head;
		bool f = false;
		while (temp)
		{
			if (temp->data.compareName(N))
			{
				f = true;
				temp->data.display();
				cout << "" << endl;
			}
			temp = temp->next;
		}
		if (!f)
		{
			cout << "Not found!" << endl;
		}
	}

	ProductNode* searchID(int i)
	{
		if (head == NULL)
		{
			cout << "Empty!" << endl;
			return 0;
		}
		ProductNode* temp = head;
		bool f = false;
		while (temp)
		{
			if (temp->data.get_id()== i)
			{
				f = true;
				//temp->data.display();
				return temp;
				cout << "" << endl;
			}
			temp = temp->next;
		}
		if (!f)
		{
			cout << "Not found!" << endl;
			return NULL;;
		}
	}
	void viewID(int i)
	{
		if (head == NULL)
		{
			cout << "Empty!" << endl;
			return;
		}
		ProductNode* temp = head;
		bool f = false;
		while (temp)
		{
			if (temp->data.get_id() == i)
			{
				f = true;
				temp->data.display();
				//return temp;
				cout << "" << endl;
			}
			temp = temp->next;
		}
		if (!f)
		{
			cout << "Not found!" << endl;
			return;
		}
	}
	void editiD(int i)
	{
		if (head == NULL)
		{
			cout << "Empty!" << endl;
			return;
		}
		ProductNode* temp = head;
		bool f = false;
		while (temp)
		{
			if (temp->data.get_id() == i)
			{
				f = true;
				//temp->data.display();
				temp->data.editProduct();
				break;
			}
			temp = temp->next;
		}
		if (!f)
		{
			cout << "Not found!" << endl;
		}
	}

	void searchQTY(int i)
	{
		if (head == NULL)
		{
			cout << "Empty!" << endl;
			return;
		}
		ProductNode* temp = head;
		bool f = false;
		while (temp)
		{
			if (temp->data.get_qty() == i)
			{
				f = true;
				temp->data.display();
				cout << "" << endl;
			}
			temp = temp->next;
		}
		if (!f)
		{
			cout << "Not found!" << endl;
		}
	}
	void replace(ProductNode* n1, ProductNode* n2)
	{
		Product t = n1->data;
		n1->data = n2->data;
		n2->data = t;

	}
	bool isUnique(int id)
	{
		if (head)
		{
			ProductNode* temp = new ProductNode;
			temp = head;
			while (temp)
			{
				if (temp->data.get_id() == id) 
				{
					// cout << temp->data.get_id();
					return false;
				}
				temp = temp->next;
			}
		}
		return true;
	}
	ProductNode* mergeID(ProductNode*& head1, ProductNode*& head2) {
		ProductNode* newHead;

		if (head1 == NULL) return head2;
		else if (head2 == NULL) return head1;

		//compare the value
		if (head1->data.get_id() < head2->data.get_id()) {
			newHead = head1;
			newHead->next = mergeID(head1->next, head2);
		}
		else {
			newHead = head2;
			newHead->next = mergeID(head1, head2->next);
		}

		return newHead;
	}
	ProductNode* mergePrice(ProductNode*& head1, ProductNode*& head2) {
		ProductNode* newHead;

		if (head1 == NULL) return head2;
		else if (head2 == NULL) return head1;

		//compare the value
		if (head1->data.get_costPrice() < head2->data.get_costPrice()) {
			newHead = head1;
			newHead->next = mergePrice(head1->next, head2);
		}
		else {
			newHead = head2;
			newHead->next = mergePrice(head1, head2->next);
		}

		return newHead;
	}
	void mergeSortPrice(ProductNode*& start) {
		
		{
			if (start->next != NULL)
			{
				ProductNode* head1;
				ProductNode* head2 = start;
				int l = listSize(start);
				//cout 
				for (int i = 0; i < l / 2; i++)
				{
					head1 = head2;
					head2 = head2->next;
				}
				head1->next = NULL;
				head1 = start;
				//	cout << "test" << endl;
				mergeSortPrice(head1);
				mergeSortPrice(head2);
					start = mergePrice(head1, head2);
			}
		}
	}
	void mergeSortID(ProductNode*& start) {

		{
			if (start->next != NULL)
			{
				ProductNode* head1;
				ProductNode* head2 = start;
				int l = listSize(start);
				//cout 
				for (int i = 0; i < l / 2; i++)
				{
					head1 = head2;
					head2 = head2->next;
				}
				head1->next = NULL;
				head1 = start;
				//	cout << "test" << endl;
				mergeSortID(head1);
				mergeSortID(head2);
				start = mergeID(head1, head2);
			}
		}
	}
	int listSize(ProductNode* h)
	{
		ProductNode* temp = h;
		int i = 0;
		for (; temp != NULL; temp = temp->next) {
			i++;
		}
		return i;
	}
	bool isEmpty()
	{
		if (head == NULL)
		{
			return true;
		}
		return false;
	}
	~ProductList()
	{
		while (head != NULL)
		{
			deleteNode();
		}
	}

	void menu()
	{
		int op;
		int n;
		int data;
		ProductList l;
		cout << "" << endl;
		cout << "\n";
		int index;

		while (true)
		{


			cout << "Enter 1 to Delete Node at Tail\n";
			cout << "Enter 2 to Add Node at Tail\n";
			cout << "Enter 3 View The List\n";
			cout << "Enter 4 To Add Node at Head\n";
			cout << "Enter 5 To check if Empty\n";
			cout << "Enter 6 to Enter Data at Index\n";
			cout << "Enter 7 to Delete Data at Index\n";
			cout << "Enter 8 to Delete ID\n";
			cout << "Enter 9 to Delete Name\n";
			cout << "Enter 10 to Search Name\n";
			cout << "Enter 11 to Search ID\n";
			cout << "Enter 12 to Search QTY\n";
			cout << "Enter 13 to Merge Sort\n";
			cout << "Enter 0 ot Exit\n";
			cin >> op;
			switch (op) {
			case 1:
			{

				l.deleteNode();

				break;
			}
			case 2:
			{
				l.append();
				cout << "Added! " << endl;
				break;
			}
			case 3:
			{
				cout << "Linked list: " << endl;
				l.viewList();
				cout << "" << endl;
				break;
			}
			case 4:{
			
				l.addHead();
				cout << "Added! " << endl;
				break;
			}
			case 5:
			{
				if (l.isEmpty() == true)
				{
					cout << "Empty!" << endl;
					break;
				}
				cout << "Not empty!" << endl;
				break;
			}
			case 6:
			{
				int i;
				cout << "Enter the index: " << endl;
				cin >> i;
				l.insertIndex(i);
				break;

			}
			case 7:
			{	
				int i;
				cout << "Enter the index: " << endl;
			cin >> i;
			l.deleteIndex(i);
				break;

			}
			case 8:
			{
				int n;
				cout << "Enter the ID: " << endl;
				cin >> n;
				l.deleteID(n);
				break;

			}
			case 9:
			{
				char* n = new char;
				cin.ignore();
				cout << "Enter the Name: " << endl;
				cin.getline(n, 50);
				l.deleteName(n);
				break;

			}
			case 10:
			{
				char* n = new char;
				cin.ignore();
				cout << "Enter the Name to Search: " << endl;
				cin.getline(n, 50);
				l.searchName(n);
				break;

			}
			case 11:
			{
				int i;
				cout << "Enter the ID to Search: " << endl;
				cin >> i;
				l.searchID(i);
				break;

			}
			case 12:
			{
				int i;
				cout << "Enter the Qty to Search: " << endl;
				cin >> i;
				l.searchQTY( i);
				break;

			}
			case 13:
			{
				char i ;
				cout << "Enter 'P' to sort by Price and 'I' to sort by ID " << endl;
				cin >> i;
				if (i == 'P' || i == 'p')
				l.mergeSortPrice(l.head);
				if (i == 'I' || i == 'i')
				{
					l.mergeSortID(l.head);
				}
				break;

			}
		
			case 0:
			{
				return;
			}
			}
		}
	}
    friend class FileManager;
};
#endif
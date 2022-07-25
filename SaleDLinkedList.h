#include<iostream>
using namespace std;
#include"Sales.h"


#ifndef INC_2021_FALL_PROJECT_GROUP_B_IRTAZA_SALEDLINKEDLIST_H
#define INC_2021_FALL_PROJECT_GROUP_B_IRTAZA_SALEDLINKEDLIST_H

class SalesNode
{

private:
    Sale data;
    SalesNode *next;
    SalesNode *prev;
	friend class FileManager;

public:
    SalesNode()
    {
        next = NULL;
        prev = NULL;
    }

    SalesNode(int d)
    {
        this->next = NULL;
    }

    SalesNode* getNext()
    {
        return this->next;
    }
    SalesNode* getPrev()
    {
        return this->prev;
    }
    void setNext(SalesNode* N)
    {
        this->next = N;
    }
    void setPrev(SalesNode* N)
    {
        this->prev = N;
    }
    friend class SaleList;
};

class SaleList
{
private:

SalesNode *head;
SalesNode *tail;
int count;
friend class FileManager;
public:

SaleList()
{
    head = NULL;
    tail = NULL;
    count = 0;
}

void append(double price)
    {
        SalesNode* temp = new SalesNode;
        temp->data.createSale(price);
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
void append(double price, float dis, int a, char*d)
{
	SalesNode* temp = new SalesNode;
	temp->data.set_amountSold(a);
	temp->data.set_dateSold(d);
	temp->data.set_discount(dis);
	temp->data.set_listPrice(price);
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

 void addHead(double price)
    {
        SalesNode *temp = new SalesNode;
        temp->data.createSale(price);
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
        head = temp;
        head->next->prev = head;

    }

    void viewList()
    {
        SalesNode* traverse = head;
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
        SalesNode* temp = head;
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
       SalesNode *temp = tail;
        tail = tail->prev;
        //	delete temp;
        tail->next = NULL;
        count--;

        cout << "Deleted! " << endl;
    }

    bool delete_datesold(char* n)
    {
        if (isEmpty())
        {
            cout << "List is empty" << endl;
            return true;
        }
        SalesNode * temp = head;
        while (temp != NULL)
        {
            if (temp->data.compareDate(n))
            {
                if (temp->prev == NULL)
                {
                    cout << "Deleting head!" << endl;
                    deletehead();
                    return true;
                }
                if (temp->next == NULL)
                {
                    cout << "Deleting tail!" << endl;
                    deleteNode();
                    return true;
                }
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                count--;
                cout << "Deleted!" << endl;
                return true;

            }
            temp = temp->next;

        }
        cout << "Not found!" << endl;
		return false;
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
        SalesNode* temp = head;
        head = head->next;
        head->prev = NULL;
        count--;
        delete temp;
    }

    void insertIndex(int i,double price)
    {

        if (count == 0)
        {
            cout << "List is empty and data will be entered at first index" << endl;
            addHead(price);
            return;
        }
        if (i == 1)
        {
            cout << "Prepending!" << endl;
            addHead(price);
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
            append(price);
            return;
        }// Corner cases dealt with
        SalesNode* temp = head;
        int counter = 1;
        while (temp != NULL)
        {
            if (counter == i)
            {
                SalesNode * t2 = new SalesNode;
                t2->data.createSale(price);
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

   void search_datesold(char* sold)
    {
        if (head == NULL)
        {
            cout << "Empty!" << endl;
            return;
        }
        SalesNode* temp = head;
        bool f = false;
        while (temp)
        {
            if (temp->data.compareDate(sold))
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

    void search_bysaleprice(double price)
    {
        if( head == NULL)
        {
            cout << "Empty!" << endl;
            return;
        }
        SalesNode* temp = head;
        bool f = false;
        while (temp)
        {
            if (temp->data.get_listPrice()==price)
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

    void search_amountsold(int i)
    {
        if (head == NULL)
        {
            cout << "Empty!" << endl;
            return;
        }
        SalesNode* temp = head;
        bool f = false;
        while (temp)
        {
            if (temp->data.get_amountSold() == i)
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

    bool isEmpty()
    {
        if (head == NULL)
        {
            return true;
        }
        return false;
    }

    int returnVal(int i)
    {
        SalesNode* t = head;
        int c = 1;

        while (t)
        {
            if (c == i + 1)
            {
                return t->data.get_amountSold();
            }
            t = t->next;
            c++;
        }
    }
    Sale returnSale(int v, SalesNode* L)
    {
        SalesNode* t = L;
        while (t)
        {
            if (t->data.get_amountSold() == v)
            {
                return t->data;
            }
            t = t->next;
        }
    }
    void insertVal(int i, int v, SalesNode* L)
    {
        SalesNode* t = head;
        int c = 1;

        while (t)
        {
            if (c == i + 1)
            {
                t->data = returnSale(v,L);
            }
            t = t->next;
            c++;
        }
    }
    
	void deepCopy(SalesNode* L)
	{
		while (head != NULL)
		{
			deleteNode();
		}
			for (; L != NULL; L = L = L->next)
			{

				this->append(L->data.get_listPrice(), L->data.get_discount(), L->data.get_amountSold(), L->data.get_dateSold());
			}
			

	}
    void count_sort(int div)
    {
        int max = findMax();
        int capacity = count;
        int* countarr = new int[max + 1]();
        SaleList L;
		L.deepCopy(this->head);
	//	L.viewList();
     
        int* temp = new int[max * 2];
       

        for (int i = 0; i < capacity; i++)
        {
            countarr[(returnVal(i) / div) % 10]++;
        }

        for (int i = 1; i <= max; i++) {
            countarr[i] += countarr[i - 1];
        }
        for (int i = capacity - 1; i >= 0; i--) {
            L.insertVal(countarr[(returnVal(i) / div) % 10] - 1, returnVal(i), this->head);
            temp[countarr[(returnVal(i) / div) % 10] - 1] = returnVal(i);
       
            countarr[(returnVal(i) / div) % 10]--;
        }
        for (int i = 0; i < capacity; i++)
        {
            
            //insertVal(i, temp[i]);
        }
		deepCopy(L.head);
     //   delete[] temp;
        delete[] countarr;

        cout << "Sorted!" << endl;

    }
    void RadixSort()
    {
        int m = findMax();
        cout << "Max is: " << m;
        for (int div = 1; m / div > 0; div *= 10) {
            count_sort(div);
        }
    }
    int findMax()
    {
        SalesNode* t = head;
        int m = head->data.get_amountSold();
        while (t)
        {
            if (m < t->data.get_amountSold())
            {
                m = t->data.get_amountSold();
            }
            t = t->next;
        }
        return m;
    }
   /* void add()
    {
        count++;
    }
    void cloneList(SaleList L)
    {
        for int(i = 1; i <= count; i++)
        {

        }
     }*/
    ~SaleList()
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
            SaleList l;
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
                cout << "Enter 8 to Delete by Date\n";
                cout << "Enter 9 to Search Price\n";
                cout << "Enter 10 to Search Date Sold\n";
                cout << "Enter 11 to Search Amount Sold\n";
                cout << "Enter 12 to Radix Sort by Amount sold\n"; 
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
                        cout << "Enter List Price: " << endl;
                        double p;
                        cin >> p;
                        l.append(p);
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
                        cout << "Enter List Price: " << endl;
                        double p;
                        cin >> p;
                        l.addHead(p);
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
                        double price;
                        cout << "Enter the index: " << endl;
                        cin >> i;

                        cout<<"please enter the price"<<endl;
                        cin>>price;
                        l.insertIndex(i,price);
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
                        cin.ignore();
                         char * n = new char;
                        cout << "Enter the date: " << endl;
                        cin.getline(n,50);
                        l.delete_datesold(n);
                        break;

                    }

                    case 9:
                    {
                       double n;
                        cin.ignore();
                        cout << "Enter the Sale_price to Search: " << endl;
                        cin>> n;
                        l.search_bysaleprice(n);
                        break;

                    }
                    case 10:
                    {
                        char* i=new char;
                        cout << "Enter the Date_sold to Search: " << endl;
                        cin >> i;
                        l.search_datesold(i);
                        break;

                    }
                    case 11:
                    {
                        int i;
                        cout << "Enter the Amount_sold to Search: " << endl;
                        cin >> i;
                        l.search_amountsold(i);
                        break;

                    }
                    case 12:
                    {
                        l.RadixSort();
                        break;
                    }

                    case 0:
                    {
                        return;
                    }
                }
            }
        }
    };


#endif //INC_2021_FALL_PROJECT_GROUP_B_IRTAZA_SALEDLINKEDLIST_H

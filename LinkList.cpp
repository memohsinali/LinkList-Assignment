#include<iostream>
using namespace std;

template<class T>
struct node
{
	T data;
	node* next;
};

template<class T>
class SortedSet
{
private:
	node<T>* head;
	node<T>* tail;

public:
	//default constructor
	SortedSet()
	{
		head = NULL;
		tail = NULL;
	}

	//checking for duplicate data
	bool duplicate(T const data)
	{
		node<T>* temp = new node<T>();
		temp = head;
		while (temp != NULL)
		{
			if (temp->data == data)
			{
				return 1;
			}
			temp = temp->next;
		}
		return 0;
	}

	//function to insert data 
	void insert(T const data)
	{
		//when list is empty
		if (head == NULL)
		{
			node<T>* temp = new node<T>;
			temp->data = data;
			head = temp;
			tail = temp;
			tail->next = NULL;
			return;
		}

		//when data to be store is less than data at head then insert at start
		else if (head->data > data)
		{
			node<T>* temp = new node<T>;
			temp->data = data;
			temp->next = head;
			head = temp;
			return;
		}

		//when data to be stored is greater than data at tail then insert at end
		else if (tail->data < data)
		{
			node<T>* temp = new node<T>;
			temp->data = data;
			tail->next = temp;
			tail = temp;
			temp->next = NULL;
			return;
		}

		else
		{
			//check for duplicates
			if (!duplicate(data))
			{
				//now keeping track for ascedning order
				node<T>* temp = new node<T>;
				temp = head;
				while (temp->next != NULL && temp->next->data < data)
				{
					temp = temp->next;
				}
				node<T>* insert = new node<T>;
				insert->data = data;
				insert->next = temp->next;
				temp->next = insert;
			}
			return;
		}

	}

	//function to print contents of data
	void print() const
	{
		node<T>* temp = new node<T>;
		temp = head;
		while (temp != NULL)
		{
			cout << temp->data << "-->";
			temp = temp->next;
		}
		cout << endl;
	}


	//calculating the size of list
	int size_of()
	{
		node<T>* temp = new node<T>;
		temp = head;
		int count = 0;
		while (temp != NULL)
		{
			temp = temp->next;
			count++;
		}
		return count;
	}


	//function to delete node
	void deleting(int index)
	{
		if (head == NULL)
		{
			cout << "List is empty, there is nothing to delete\n";
			return;
		}

		//when index is zero delete head
		else if (index == 0)
		{
			node<T>* temp = new node<T>;
			temp = head;
			head = head->next;
			delete temp;
			temp = NULL;
			return;
		}

		//deleting tail
		else if (index == size_of() - 1)
		{
			node<T>* temp = new node<T>;
			temp = head;
			while (temp->next != tail)
			{
				temp = temp->next;
			}
			delete tail;
			tail = NULL;
			temp->next = NULL;
			tail = temp;
			return;
		}
		else if (index < 0)
		{
			cout << "\nEnter the index greater than 0\n";
			return;
		}

		else if (index >= size_of())
		{
			cout << "\nEnter the index with in the range of list\n";
			return;
		}

		else
		{
			node<T>* temp = new node<T>;
			temp = head;
			int count = 0;     //assuming that index of list starts from zero
			while (temp != NULL && count < index)
			{
				count++;
				if (count < index)
				{
					temp = temp->next;
				}
			}
			if (temp == NULL)
			{
				cout << "\nEnter the correct index\n";
				return;
			}
			else
			{
				node<T>* del = new node<T>;
				del = temp->next;
				temp->next = del->next;
				delete del;
				del = NULL;
			}
			return;
		}
	}

	



	void Union(SortedSet<T> const& otherSet)
	{
		node<T>* temp1 = new node<T>;
		temp1 = head;
		node<T>* temp2 = new node<T>;
		temp2 = otherSet.head;
		node<T>* prev1 = new node<T>;
		prev1 = temp1;
		node<T>* prev2 = new node<T>;
		prev2 = temp2;

		if (otherSet.head == NULL)
		{
			return;     //union would be the calling set
		}

		else if (head == NULL)
		{
			head = otherSet.head;      //union would be passing set
		}

	

		// handling the case when head of the calling set is greater than head of the pasing set
		else if (head->data > otherSet.head->data)
		{
			node<T>* ptr = new node<T>;
			ptr->data = temp2->data;
			ptr->next = head;
			head = ptr;
			temp1 = head;
			temp2 = temp2->next;  // cz we have already added that element in the calling set
		}


		else if (head->data == otherSet.head->data)  // when head of both sets are same
		{
			temp2 = temp2->next;
		}

    

		while (temp1 != NULL && temp2 != NULL && temp1->data < temp2->data)     //terminating condition
		{
			prev1 = temp1;
			temp1 = temp1->next;

			if (temp1 == NULL)  // important condition :- whenever the temp1 of calling set reaches to NULL then prev1 of calling set will directly point to temp2 of passing set
			{
				prev1->next = temp2;
			}


			// when temp1 data is greater than temp2 data

			else if (temp1->data > temp2->data)
			{
				node<T>* ptr = new node<T>;
				ptr->data = temp2->data;
				prev1->next = ptr;
				ptr->next = temp1;
				temp1 = ptr;      // move temp1 back ; point to newely added element
				temp2 = temp2->next;
			}

			// whenever same data is detected 
			else if (temp1->data == temp2->data)
			{
				temp2 = temp2->next;               // just move temp2 of passing set forward
			}
		}
	}

	//fucntion to rotate list
	void rotate()
	{
		int k;
		cout << "Enter the value of k for rotation\n";
		cin >> k;
		while (k<0 || k>size_of())
		{
			cout << "\nEnter the correct value of k\n";
			cin >> k;
		}

		if (k == 0 || k == size_of())
		{
			return;    //no need to rotate bcz list would remain same
		}
		else
		{
			int count = 0;  // keeping track
			node<T>* temp = new node<T>;
			temp = head;
			while (count < k)
			{
				count++;
				if (count < k)
				{
					temp = temp->next;       // temp will just point before the k
				}
			}
			node<T>* ptr = new node<T>;
			ptr = temp->next;                // ptr pointing on to the kth node
			node<T>* curr = new node<T>;
			curr = ptr;                     
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			if (ptr != NULL && temp != NULL)
			{
				ptr->next = head;
				temp->next = NULL;
				head = curr;       // now head is changed 
				tail = temp;       // now tail is changed
			}
		}
	}

	node<T>* get_head()
	{
		return head;
	}



	//following functions are written for the reverse function written outside the class

	node<T>* get_tail()
	{
		return tail;
	}

	void set_tail(node<T>* tail)
	{
		this->tail = tail;
	}

	void set_head(node<T>* head)
	{
		this->head = head;
	}


	//destructor

	~SortedSet()
	{
		node<T>* temp1;
		node<T>* temp2;
		temp1 = head;
		while (temp1 != NULL)
		{
			temp2 = temp1->next;
			delete temp1;
			temp1 = temp2;
		}
	}


};

template <class T>
void reverse(SortedSet<T>& list)
{
	node<T>* prev = new node<T>;   // prev node required to point curr node to prev
	prev = NULL;
	node<T>* curr = new node<T>;
	curr = list.get_head();
	node<T>* post = new node<T>;     
	post = curr;
	while (curr != NULL)
	{
		post = curr->next;
		curr->next = prev;
		prev = curr;            
		curr = post;
	}

	// remember to set head and tail according to reverse link list

	list.set_tail(list.get_head());    // pointing tail to head bcz it head would be last node 
	list.set_head(prev);              // pointing head to prev so that list starts from last
}




int main()
{
	SortedSet<int> s1;
	s1.insert(1);
	s1.insert(2);
	s1.insert(4);
	s1.insert(6);
	
	s1.deleting(3);
	s1.print();

	s1.rotate();

	s1.print();


	return 0;
}
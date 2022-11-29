#include <iostream>
#include <vector>
#include <string>
using namespace std;

string word = "aabbbcdddddfasdfadvdasewewrdfarewd";

class node
{
public:
	node* left;
	node* right;
	char data;
	int frequency;
	string code = "";
	node(char data, int frequency, node* left = NULL, node* right = NULL): data(data), frequency(frequency), left(left), right(right) {}
	node(): data('*'), frequency(0), left(NULL), right(NULL) {}
};

class queue
{
public:
	node** arr;
	int ending = 0;
	int starting = 0;
	int size;
	int elements = 0;
	queue(int size): size(size)
	{
		arr = new node*[size];
	}
	void sort()
	{

		for (int step = starting; step < ending - 1; ++step)
		{
			for (int i = starting; i < ending - 1; ++i)
			{
				if (arr[i]->frequency > arr[i + 1]->frequency) {
					node* temp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = temp;
				}
			}
		}
	}
	
		



	//push
	void push(node* n)
	{
		if (!full())
		{
			elements++;
			arr[ending++] = n;
			sort();
		}
	}
	node* pop()
	{
		if (!empty())
		{
			elements--;
			return arr[starting++];
		}
		return NULL;
	}

	bool empty()
	{
		if (ending == -1)
		{
			return true;
		}
		return false;
	}
	bool full()
	{
		if (ending == size)
		{
			return true;
		}
		return false;
	}

	string top()
	{
		return string(1, arr[starting]->data) + " " + to_string(arr[starting]->frequency);
	}

	bool oneLeft()
	{
		if (elements == 1)
			return true;
		return false;
	}

	void print()
	{
		cout << "------------" << endl;

		for (int i = starting; i < ending; i++)
		{
			cout << arr[i]->data << " " << arr[i]->frequency << endl;
		}
		cout << endl;

	}

	~queue()
	{
		delete[] arr;
	}
};


class Tree
{
public:
	node* head;
	vector<char> inorder;
	Tree(node* head) : head(head) {}
	
	void printLeaves(node* head, string code)
	{
		if (head->left == NULL && head->right == NULL)
		{
			cout << head->data << "    " << code << endl;
			head->code = code;
			return;
		}
		printLeaves(head->left, code + "1");
		printLeaves(head->right, code + "0");
	}

	//print tree
	void InorderTraversal(node* head)
	{
		if (head == NULL)
			return;
		InorderTraversal(head->left);
		inorder.push_back(head->data);
		InorderTraversal(head->right);
	}

	void printInorder()
	{
		for (int i=0;i<inorder.size();i++)
		{
			cout << inorder[i] << " ";
		}
	}

	int findHeight(node* head)
	{
		if (head == NULL)
			return -1;
		return 1 + findHeight(head->left);
		//cout << n << endl;
		
	}

	void printTree(node* head)
	{
		if (head == NULL)
			return;

		for (int i = 0; i < findHeight(head); i++)
		{
			cout << "  ";
		}
		if (head->left != NULL)
		cout << head->left->data << "  ";
		if (head->right != NULL)
			cout << head->right->data << endl;

		printTree(head->left);
	}
};



int main(void)
{

	queue list(word.size());

	//count occurences
	int arr[256] = { 0 };
	for (int i = 0; i < word.size(); i++)
	{
		arr[word[i]]++;
	}
	
	//build nodes
	for (int i = 0; i < 256; i++)
	{
		if (arr[i] == 0)
			continue;
		node* newNode = new node(char(i),arr[i]);
		list.push(newNode);
	}



	//build huffman tree
	while(!list.oneLeft())
	{

		list.print();
		node* two = list.pop();
		node* one = list.pop();
		int sum = one->frequency+two->frequency;
		node* newNode = new node('*',sum,one,two);
		list.push(newNode);



	}
		list.print();


	node* head = list.pop();
	Tree huffboi(head);

	huffboi.InorderTraversal(head);
	huffboi.printInorder();

	cout << endl <<  "_____________" << endl
		<< "Genrerated codes" << endl;
	cout << endl << endl;
	huffboi.printLeaves(head,"");


	//print tree logic is flawed for now
	//please ignore or fix

	




	return 0;
}


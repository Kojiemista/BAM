#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
using namespace std;

struct Priority
{
	char tableChar = NULL;
	int tableCount = 0;
	string code = "";
};

struct Node
{
	int count = 0;
	char value = NULL;
	Node* left = NULL;
	Node* right = NULL;
	Node() {};
	Node(Node* left, Node* right)
	{
		this->left = left;
		this->right = right;
		this->count = left->count + right->count;
	}
};

struct Compare
{
	bool operator()(Node* left, Node* right) const
	{
		return left->count < right->count;
	}
};

string code = "";
void binaryBuild(vector <Priority>& build, Node* tree)
{
	if (tree->left != NULL)
	{
		code += "0";
		binaryBuild(build, tree->left);
	}
	if (tree->right != NULL)
	{
		code += "1";
		binaryBuild(build, tree->right);
	}
	if (tree->value != NULL)
	{
		for (size_t i = 0; i < build.size(); ++i)
		{
			if (build.at(i).tableChar == tree->value)
			{
				if (code.size() == 0) code += "1";
				build.at(i).code = code;
			}
		}
	}
	if (!code.empty()) code.pop_back();
	return;
}

string coder(const vector <Priority>& build, const string& message)
{
	string coded = "";
	for (size_t i = 0; i < message.size(); ++i)
	{
		for (size_t b = 0; b < build.size(); ++b)
		{
			if (message.at(i) == build.at(b).tableChar)
			{
				coded += build.at(b).code;
				break;
			}
		}
	}
	return coded;
}

void treeSearcher(string coded, Node* tree, char& tmp, size_t i = 0)
{
	if (tree->left == NULL && tree->right == NULL && tmp == NULL)
	{
		tmp = tree->value;
		return;
	}
	if (coded.at(i) == 48 && tmp == NULL)
	{
		treeSearcher(coded, tree->left, tmp, ++i);
	}
	if (i != coded.size()) if (coded.at(i) == 49 && tmp == NULL)
	{
		treeSearcher(coded, tree->right, tmp, ++i);
	}
	return;
}

string decoder(const vector <Priority>& build, string coded, Node* tree)
{
	string decoded = "";
	while (coded.size() != 0)
	{
		char tmp = NULL;
		treeSearcher(coded, tree, tmp);
		decoded += tmp;
		for (size_t i = 0; i < build.size(); ++i)
		{
			if (build.at(i).tableChar == tmp)
			{
				coded.erase(0, build.at(i).code.size());
				break;
			}
		}
	}
	return decoded;
}

float coefOfUsefull(const vector <Priority>& build, const string& message, const string& coded)
{
	float tmp1 = message.size() * 8;
	size_t b = 0;
	for (size_t i = 0; i < build.size(); ++i) b += build.at(i).code.size();
	float tmp2 = coded.size() + build.size() * 8 + b;
	return tmp1 / tmp2;
}

void printStart()
{
	cout << "\t\t\t\t\t\t**Huffman Coder**\n\n";
	cout << "Сообщение для кодирования: ";
}

void print(const string& coded, const string& decoded, const float& coef, const string& message)
{
	cout
		<< "\n" << "Закодированное сообщение: " << coded
		<< "\n\n" << "Раскодированное сообщение: " << decoded
		<< "\n\n" << "Вес сообщения был сжат на: " << coef * 100 << " %"
		<< "\n\n";
	return;
}

Node* treeBuild(const vector <Priority>& build)
{
	list <Node*> tree;
	for (size_t i = 0; i < build.size(); ++i)
	{
		Node* tmp = new Node;
		tmp->count = build.at(i).tableCount;
		tmp->value = build.at(i).tableChar;
		tree.push_back(tmp);
	}
	while (tree.size() != 1)
	{
		tree.sort(Compare());
		Node* Left = tree.front();
		tree.pop_front();
		Node* Right = tree.front();
		tree.pop_front();
		Node* Front = new Node(Left, Right);
		tree.push_back(Front);
	}
	return tree.front();
}

bool checkKey(vector <Priority>& build, const string message, const int i, size_t& b)
{
	for (b = 0; b < build.size(); ++b)
	{
		if (message.at(i) == build.at(b).tableChar)
		{
			build.at(b).tableCount++;
			return false;
		}
	}
	return true;
}

string vectorPriority(vector <Priority>& build)
{
	string message;
	do {
		getline(cin, message);
	} while (message.size() == 0);
	for (size_t i = 0, b; i < message.length(); ++i)
	{
		if (checkKey(build, message, i, b))
		{
			build.push_back({ message.at(i) });
			build.at(b).tableCount++;
		}
	}
	return message;
}

void dialogHUF()
{
	printStart();
	vector <Priority> build;
	string message = vectorPriority(build);
	Node* root = treeBuild(build);
	binaryBuild(build, root);
	string coded = coder(build, message);
	string decoded = decoder(build, coded, root);
	float coef = coefOfUsefull(build, message, coded);
	print(coded, decoded, coef, message);
	system("pause");
	return;
}
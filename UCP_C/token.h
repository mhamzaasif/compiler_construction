#include <string>
#include<iostream>
using namespace std;
struct Token
{
	string lexeme;
	string type;
	int encode;
};

struct Rule 
{
	int value;
	int row;
};
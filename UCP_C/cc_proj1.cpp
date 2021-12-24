/* Header files */
#include"token.h"
#include"Lexer.h"
#include"Stack.h"
using namespace std;
int static parse_error_count=0;

/* Fuction Prototypes */
Token get_token(ifstream &);
void init_parser();
void parse_engine(Stack <Rule>&stack,Token token);
//void parse_engine(Stack <Rule>&stack, Token token, int &rule);
int parse_table[28][47] = { 0 };
int rule_book[55][10] = { 0 };
void read_parse_table(int parse_table[28][47]);
void read_rule_book(int rule_book[56][10]);
int main()
{
	cout << "Hello World" << endl;
	init_lexer();
	init_parser();
	system("pause");
	return 0;
}


void init_parser()
{
	read_parse_table(parse_table);
	read_rule_book(rule_book);
	ifstream inFile;
	Token token;
	Stack <Rule> stack;
	Rule rule;
	rule.value = 999;
	
	stack.push(rule);
	rule.value = -1;
	rule.row = 1;
	stack.push(rule);
	inFile.open("token.txt", ios::in);
	if (!inFile.is_open())
	{
		cout << "Failed to open token.txt" << endl;
		exit(1);
	}
	else
	{
		int rule = -1;

		while (!inFile.eof())
		{
			token = get_token(inFile);
			if (compare(token.lexeme, "\n")||compare(token.lexeme,""))
			{
				break;
			}
			parse_engine(stack, token);
			
		}
		cout << "After Execution::Stack Elements" << endl;
		while (!stack.is_empty())
		{
			cout << stack.top().value << endl;
			stack.pop();
		}
		inFile.close();
	}
}

void parse_engine(Stack <Rule>&stack,Token token) 
{
	cout << "Token:" << token.lexeme << endl;
	cout << "Stack:" << endl;
	stack.print();
	cout << "=================================" << endl;
	cin.get();
	if (stack.top().value == 999)
	{
		return;
	}
	if (stack.top().value == token.encode)
	{
		stack.pop();
		return;
	}
	else if (stack.top().value == 777)
	{
		stack.pop();
	}
	else if (stack.top().value < 0)
	{
		if (parse_table[stack.top().value*-1][token.encode] == 777)
		{
			stack.pop();
		}
		else if (parse_table[stack.top().value*-1][token.encode]==888)
		{
			return;
		}
		else
		{
			Stack <Rule>stack1;
			Rule rule;
			rule.row = stack.top().value*-1;
			for (int i = 0;; i++)
			{
				if (rule_book[parse_table[rule.row][token.encode]][i] != 999)
				{
					rule.value = rule_book[parse_table[rule.row][token.encode]][i];
					stack1.push(rule);
				}
				else
				{
					break;
				}
			}
			stack.pop();
			while (!stack1.is_empty())
			{
				stack.push(stack1.top());
				stack1.pop();
			}
		}
	}
	else
	{
		if (parse_table[stack.top().row][token.encode] == 777)
		{
			cout << "Skipping Rule :" << stack.top().value << endl;
			stack.pop();
		}
		else if (parse_table[stack.top().row][token.encode] == 888)
		{
			cout << "Skipping Token :" << token.lexeme << endl;
			return;
		}
		else
		{
			/*cout << parse_table[stack.top().row][token.encode] << endl;
			cout << "Undefined Error" << endl;*/
			/*Stack <Rule>stack1;
			Rule rule;
			rule.row = stack.top().row;
			for (int i = 0;; i++)
			{
				if (rule_book[parse_table[rule.row][token.encode]][i] != 999)
				{
					rule.value = rule_book[parse_table[rule.row][token.encode]][i];
					stack1.push(rule);
				}
				else
				{
					break;
				}
			}
			stack.pop();
			while (!stack1.is_empty())
			{
				stack.push(stack1.top());
				stack1.pop();
			}*/
			cout << "Force Skipping ::" << endl;
			return;
		}
	}


	/*
	if (stack.top().value < 0)
	{
		int row = stack.top().value*-1;
		stack.pop();
		Stack <Rule>stack1;
		Rule rule;
		rule.row = row;
		if (parse_table[row][token.encode] == 888)
		{
			cout << "Skipping token:" << token.lexeme << endl;
			lex_error_count++;
			return;
		}
		else if (parse_table[row][token.encode] == 777)
		{
			stack.pop();
		}
		else
		{
			for (int i = 0;; i++)
			{
				if (rule_book[parse_table[row][token.encode]][i] != 999)
				{
					rule.value = rule_book[parse_table[row][token.encode]][i];
					stack1.push(rule);
				}
				else
					break;
			}
			for (int i = 0;; i++)
			{
				if (!stack1.is_empty())
				{
					stack.push(stack1.top());
					stack1.pop();
				}
				else
				{
					break;
				}
			}
		}
	}
	else
	{
		if (stack.top().value == token.encode)
		{
			stack.pop();
			return;
		}
		else if (stack.top().value == 777)
		{
			stack.pop();
		}
		else
		{
			if (parse_table[stack.top().row][token.encode] == 777)
			{
				cout << "Stack Element:" << stack.top().value << endl;
				cout << "Token:" << token.encode << endl;
				cout << "Row:" << stack.top().row << endl;
				stack.pop();
				cout << "Token: " << token.lexeme << " is invalid" << endl;
				parse_error_count++;
			}
			else if (parse_table[stack.top().row][token.encode] == 888)
			{
				cout << "Token: " << token.lexeme << " is skipped" << endl;
				parse_error_count++;
				return;
			}
			else
			{
				parse_error_count++;
				cout << "Undefined Error" << endl;
			}
		}
	}
	*/
	parse_engine(stack, token);
	
	/*if (stack.top().value == 777)
	{
		cout << "777" << endl;
		stack.pop();
	}
	else if (stack.top().value == token.encode)
	{
		cout << "Stack.top():" << stack.top().value << " token.encode:" << token.encode << endl;
		return;
	}
	else if (stack.top().value < 0)
	{
		rule = stack.top().value*-1;
		stack.pop();
		Stack <Rule>stack1;
		for (int i = 0;; i++)
		{
			if (rule_book[parse_table[rule][token.encode]][i] != 999)
				stack1.push(rule_book[parse_table[rule][token.encode]][i]);
			else
				break;
		}
		while (!stack1.is_empty())
		{
			stack.push(stack1.top());
			stack1.pop();
		}
	}
	else
	{
		if (token.encode == stack.top())
		{
			return;
		}
		else if(parse_table[rule][token.encode]==777)
		{
			stack.pop();
		}
		else
		{
			return;
		}
	}
	parse_engine(stack, token, rule);*/
	/*if (stack.top() < 0)
	{
 		rule = parse_table[stack.top()*-1][token.encode];
		if (rule == 888)
		{
			cout << "888" << endl;
			return;
		}
		else if (rule == 777)
		{
			cout << "777" << endl;
			stack.pop();
		}
		else
		{
			stack.pop();
			Stack <int>stack1;
			for (int i = 0;; i++)
			{
				if (rule_book[rule][i] != 999)
					stack1.push(rule_book[rule][i]);
				else
					break;
			}
			while (!stack1.is_empty())
			{
				stack.push(stack1.top());
				stack1.pop();
			}
		}
	}
	else
	{
		if (stack.top() == token.encode )
		{
			cout << "stack.top:" << stack.top() << " Token.encode:" << token.encode << endl;
			stack.pop();
			return;
		} 
		else if (stack.top() == 777)
		{
			stack.pop();
		}
		else
		{
			if (parse_table[rule][token.encode] == 777)
			{
				stack.pop();
			}
			else
			{
				return;
			}
		}
	}
	parse_engine(stack, token, rule);*/
	/*if (stack.top == token.encode || stack.top == 777)
	{
		stack.pop();
		return;
	}
	else
	{
		if (stack.top() < 0)
		{
			int row = stack.top()*-1;
			int col = token.encode;
			rule = parse_table[row][col];
			stack.pop();
			Stack<int> stack1;
			for (int i = 0;; i++)
			{
				if (rule_book[rule][i] != 999)
					stack1.push(rule_book[rule][j]);
				else
					break;
			}
			while (!stack1.is_empty())
			{
				stack.push(stack1.top());
				stack1.pop();
			}
		}
		else if (parse_table[rule][token.encode] == 777)
		{
			stack.pop();
			return;
		}
		else
		{
			return;
		}
	}*/
	/*Stack <int>stack1;
	int row, col, rule = 0;
	row = stack.top();
	col = token.encode;
	if (row < 0)
	{
		stack.pop();
		row *= -1;
		rule = parse_table[row][col];
		for (int j = 0;; j++)
		{
			if (rule_book[rule][j] != 999)
				stack1.push(rule_book[rule][j]);
			else
				break;
		}
		while (!stack1.is_empty())
		{
			stack.push(stack1.top());
			stack.pop();
		}
	}
	else
	{
		if (stack.top() == token.encode)
		{
			stack.pop();
			return;
		}
	}
	parse_engine(stack, token);*/
}

void read_parse_table(int parse_table[28][47])
{
	ifstream inFile;
	inFile.open("parse_table.csv", ios::in);
	if (!inFile.is_open())
	{
		cout << "Failed to Open parse_table.csv" << endl;
		exit(0);
	}
	for (int i = 1; i <= 28; i++)
	{
		for (int j = 1; j <= 47; j++)
		{

			inFile >> parse_table[i][j];
		}
	}
	inFile.close();
	/*for (int i = 1; i <= 28; i++)
	{
		for (int j = 1; j <= 47; j++)
		{
			cout << parse_table[i][j] << "\t";
		}
		cout << endl;
	}*/
	
}

void read_rule_book(int rule_book[56][10])
{
	ifstream inFile;
	inFile.open("rule_table.csv", ios::in);
	if (!inFile.is_open())
	{
		cout << "Failed to open rule_book.csv" << endl;
		exit(1);
	}
	for (int i = 1; i <= 55; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			inFile >> rule_book[i][j];
			if (rule_book[i][j] == 999)
				break;
		}
	}
	/*
	for (int i = 0; i <= 55; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << rule_book[i][j] << "\t";
		}
		cout << endl;
	}
	*/
}

Token get_token(ifstream &inFile)
{
	Token token;
	inFile >> token.lexeme;
	inFile >> token.type;
	inFile >> token.encode;
	return token;
}

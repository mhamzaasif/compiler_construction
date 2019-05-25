/* Header files */

#include<iostream>
#include<string>
#include<stdlib.h>
#include<fstream>
#include"token.h"

using namespace std;


/* Fuction Prototypes */
void create_token(string,int);
void hash_mapping(int arr[256]);
void transition_table(int arr[32][32]);
void lexical_anal(string,string,int,int);
void read_keywords();
bool is_keyword(string);

void create_token();
void init_parser();

int state_table[32][32]={0};
int mapping[256]={0};
string keywords[10];


int main()
{
	hash_mapping(mapping);
	transition_table(state_table);
	read_keywords();
	init_parser();
	return 0;
}


void init_parser()
{
	//Token token = get_token();
	
}


void create_token()
{
	ifstream inFile;
	inFile.open("test.txt",ios::in);
	if(!inFile.is_open())
	{
		exit(0);
	}
	string instruction;
	/*int state = 1;
	instruction lexeme = "";*/
	while (!inFile.eof())
	{
		getline(inFile, instruction);
		lexical_anal(instruction, "", 1, 0);
	}
	
}

void hash_mapping(int arr[256])
{
	for (int i = 0;i < 255; i++)
	{
		if(char(i) == '_')
			arr[i] = 0;
		if(char(i) >= 'a' && char(i) <= 'z')
			arr[i] = 1;
		if(char(i) >= 'A' && char(i) <= 'Z')
			arr[i] = 1;
		if(char(i) >= '0' && char(i) <= '9')
			arr[i] = 2;
		if(char(i) == '+')
			arr[i] = 3;
		if(char(i) == '-')
			arr[i] = 4;
		if(char(i) == '.')
			arr[i] = 5;
		if(char(i) == '*')
			arr[i] = 6;
		if(char(i) == '/')
			arr[i] = 7;
		if(char(i) == '=')
			arr[i] = 8;
		if(char(i) == '>')
			arr[i] = 9;
		if(char(i) == '<')
			arr[i] = 10;
		if(char(i) == '!')
			arr[i] = 11;
		if(char(i) == ':')
			arr[i] = 12;
		if(char(i) == '{')
			arr[i] = 13;
		if(char(i) == '}')
			arr[i] = 14;
		if(char(i) == '(')
			arr[i] = 15;
		if(char(i) == ')')
			arr[i] = 16;
		if(char(i) == '[')
			arr[i] = 17;
		if(char(i) == ']')
			arr[i] = 18;
		if(char(i) == '#')
			arr[i] = 19;
		if(char(i) == ' ')
			arr[i] = 20;
		if(char(i) == ';')
			arr[i] = 21;
		if(char(i) == '&')
			arr[i] = 22;
		if(char(i) == '|')
			arr[i] = 23;
		if(char(i) == '^')
			arr[i] = 24;
		if(char(i) == '$')
			arr[i] = 25;
		if(char(i) == '%')
			arr[i] = 26;
		if(char(i) == '@')
			arr[i] = 27;
		if(char(i) == '?')
			arr[i] = 28;
		if(char(i) == ',')
			arr[i] = 29;
		if(char(i) == '\\')
			arr[i] = 30;
		if(char(i) == '\t')
			arr[i] = 31;
	}
}


void transition_table(int state_table[32][32])
{
	ifstream inFile;
	inFile.open("table1.csv",ios::in);
	if(!inFile.is_open())
	{
		exit(0);
	}
	int x;
	for(int i=0;i<32;i++)
	{
		for(int j=0;j<32;j++)
		{
			inFile>>x;
			state_table[i][j]=x;
		}
	}
	inFile.close();
	for(int i = 0;i<32;i++)
	{
		for(int j=0;j<32;j++)
		{
			cout<<state_table[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<int('\t')<<endl;
	cout<<mapping[9]<<endl;
	cin.get();
}


void lexical_anal(string instruction,string lexeme,int state,int i)
{
	if(instruction[i]=='\0')
	{
		create_token(lexeme,state);
		return;
	}
	switch(state)
	{
		case 0:
		//lexeme+=instruction[i];
		state = state_table[state][mapping[int(instruction[i])]];
		if(state != 0)
		{
			//create_token(lexeme,0);
			lexeme += instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 1:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state != 0)
			lexeme+=instruction[i];
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 2:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,2);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,2);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 3:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,3);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,3);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 4:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,4);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,4);
			lexeme="";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 5:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,5);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,5);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 6:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,6);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,6);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 7:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,7);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,7);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 8:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,8);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,8);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 9:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,9);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,9);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 10:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,10);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,10);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 11:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,11);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,11);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 12:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,12);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,12);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 13:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,13);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,13);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 14:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,14);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,14);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 15:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,15);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,15);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 16:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,16);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,16);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 17:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,17);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,17);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 18:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,18);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,18);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 19:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,19);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,19);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 20:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,20);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,20);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 21:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,21);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,21);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 22:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,22);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,22);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 23:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,23);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,23);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 24:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,24);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,24);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 25:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,25);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,25);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 26:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,26);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,26);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 27:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,27);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,27);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 28:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,27);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,27);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 29:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,29);
			lexeme = "";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,29);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
		case 30:
		state = state_table[state][mapping[int(instruction[i])]];
		if(state == 1)
		{
			create_token(lexeme,30);
			lexeme="";
			i--;
		}
		else if(state == 0)
		{
			create_token(lexeme,30);
			lexeme = "";
		}
		else
		{
			lexeme+=instruction[i];
		}
		lexical_anal(instruction,lexeme,state,i+1);
		break;
	}
}

void create_token(string lexeme,int state)
{
	if(state == 3)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Identifier>"<<endl;
			outFile.close();
		}
	}
	else if(state == 4)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Operator>"<<endl;
			outFile.close();
		}
	}
	else if(state == 5)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Number>"<<endl;
			outFile.close();
		}
	}
	else if(state == 7)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Number>"<<endl;
			outFile.close();
		}
	}
	else if(state == 8)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Operator>"<<endl;
			outFile.close();
		}
	}
	else if(state == 9)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Operator>"<<endl;
			outFile.close();
		}
	}
	else if(state == 10)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Operator>"<<endl;
			outFile.close();
		}
	}
	else if(state == 11)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Operator>"<<endl;
			outFile.close();
		}
	}
	else if(state == 12)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Operator>"<<endl;
			outFile.close();
		}
	}
	else if(state == 13)
	{
		/* Srearch for Keywords */
		string type = "";
		if(is_keyword(lexeme))
		{
			type = "Keyword";
		}
		else if(lexeme[0] == '<')
		{
			type = "Operator";
		}
		else
		{
			type = "invalid Token";
		}
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<","<<type<<">"<<endl;
			outFile.close();
		}
	}
	else if(state == 14)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Operator>"<<endl;
			outFile.close();
		}
	}
	else if(state == 15)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Operator>"<<endl;
			outFile.close();
		}
	}
	else if(state == 17)
	{
		/*Search for keywords*/
		string type = "";
		if(is_keyword(lexeme))
		{
			type = "Keyword";
		}
		else if(lexeme[0] = '<')
			type = "invalid token";
		else
		{
			type = "Operator";
		}
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<","<<type<<">"<<endl;
			outFile.close();
		}
	}
	else if(state == 19)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Operator>"<<endl;
			outFile.close();
		}
	}
	else if(state == 22)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Operator>"<<endl;
			outFile.close();
		}
	}
	else if(state == 23)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",{>"<<endl;
			outFile.close();
		}
	}
	else if(state == 24)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",}>"<<endl;
			outFile.close();
		}
	}
	else if(state == 25)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",(>"<<endl;
			outFile.close();
		}
	}
	else if(state == 26)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",)>"<<endl;
			outFile.close();
		}
	}
	else if(state == 27)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",]>"<<endl;
			outFile.close();
		}
	}
	else if(state == 28)
	{
		ofstream outFile;
		outFile.open("token.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",[>"<<endl;
			outFile.close();
		}
	}
	else if(state == 29)
	{
		/*Search for keyword*/
		if(is_keyword(lexeme))
		{
			ofstream outFile;
			outFile.open("token.txt",ios::app);
			if(!outFile.is_open())
			{
				cout<<"Error to open token.txt"<<endl;
				return;
			}
			else
			{
				outFile<<"<"<<lexeme<<",Keyword>"<<endl;
				outFile.close();
			}
		}
		else
		{
			ofstream outFile;
			outFile.open("error.txt",ios::app);
			if(!outFile.is_open())
			{
				cout<<"Error to open token.txt"<<endl;
				return;
			}
			else
			{
				outFile<<"<"<<lexeme<<",Invalid Token>"<<endl;
				outFile.close();
			}
		}
	}
	else
	{
		ofstream outFile;
		outFile.open("error.txt",ios::app);
		if(!outFile.is_open())
		{
			cout<<"Error to open token.txt"<<endl;
			return;
		}
		else
		{
			outFile<<"<"<<lexeme<<",Invalid Token>"<<endl;
			outFile.close();
		}
	}
}


void read_keywords()
{
	ifstream inFile;
	inFile.open("keywords",ios::in);
	if(!inFile.is_open())
	{
		cout<<"Failed To read keywords"<<endl;
		return;
	}
	else
	{
		int i=0;
		while(!inFile.eof())
		{
			getline(inFile,keywords[i]);
			i++;
		}
	}
}

bool compare(string a, string b)
{
	int i=0;
	while(a[i]!='\0' && b[i]!='\0')
	{
		if(a[i]!=b[i])
		{
			break;
		}
		i++;
	}
	if(a[i]=='\0' && b[i]=='\0')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool is_keyword(string a)
{
	for(int i = 0; i < 10; i++)
	{
		cout<<"Checking:: "<<keywords[i]<<endl;
		if(compare(a,keywords[i]))
		{
			return true;
		}
	}
	return false;
}
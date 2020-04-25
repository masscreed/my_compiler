#include <iostream> 
#include <fstream>
#include <string.h>
#include <cctype>
#include <regex>
#include "lexer.h"
//#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

using namespace std;

char options_compilier;


char equal_str(string s1, char s2[])
{
	string s2_1 = s2;

	if(s1 == s2_1)
		return 1;
	
	return 0;
}

int find_in_tokens(string token)
{
	int i = 0, result = 0;		
	for(i = 0; i < 150 && !result && (token_name[i][0] != '\0'); i++)
	{
		result = equal_str(token, token_name[i]);
		if(result)
			return i;
	}
	return -1;
}

bool is_letter(char c)
{
	if( c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'|| c == '_')
		return true;
	return false;
}

bool is_operator(char c)
{
	if( ('+' == c) || ('-' == c) ||
		('*' == c) || ('/' == c) ||
		('^' == c) || ('<' == c) ||
		('>' == c) || ('=' == c) ||
		(',' == c) || ('!' == c) ||
		('(' == c) || (')' == c) ||
		('[' == c) || (']' == c) ||
		('{' == c) || ('}' == c) ||
		('%' == c) || (':' == c) ||
		('?' == c) || ('&' == c) ||
		('|' == c) || (';' == c))
		return true;
	return false;
}
bool is_digit(char c)
{
	if(c >= '0' && c <= '9')
		return true;
	return false;
}

char type_char(const char c)
  {
	if( ('+' == c) || ('-' == c) ||
		('*' == c) || ('/' == c) ||
		('^' == c) || ('<' == c) ||
		('>' == c) || ('=' == c) ||
		(',' == c) || ('!' == c) ||
		('(' == c) || (')' == c) ||
		('[' == c) || (']' == c) ||
		('{' == c) || ('}' == c) ||
		('%' == c) || (':' == c) ||
		('?' == c) || ('&' == c) ||
		('|' == c) || (';' == c))
		return this_operator;
	else if( c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
		return this_letter;
	else if( c == '_')
		return this_literal;
	else if(c >= '0' && c <= '9')
		return this_digit;
	
	return this_composite_operator;
  }

int analysis_row(string source_string, int line_in_file)
{
	int str_length = source_string.length();
	int position_in_str = 1, i;
	int position_begin_word;
	int number_token;
	string buffer_str, buffer_str_2;
	char str_error, number_error;
	int type_date;
	
	for(i = 0; i < str_length; i++)
	{
		while((source_string[i] == ' ' || source_string[i] == '\t') && i < str_length)
		{
			if(source_string[i] == ' ')
			{
				position_in_str++;
			}
			else if(source_string[i] == '\t')
			{
				position_in_str += 4;
			}
			i++;
			
		}
		str_error = 0;
		number_error = 0;
		buffer_str = "";
		buffer_str_2 = "";
		position_begin_word = position_in_str;
		number_token = -1; 
		type_date = type_char(source_string[i]);
	//	cout<< "type date    "<< type_date<< endl;
		switch(type_date)
		{
			case this_composite_operator: 
			{
				if(source_string[i] == '"')
				{
					i++;
					position_in_str++;
					buffer_str = "\"\"";
					buffer_str_2 += '"';
					while(source_string[i] != '"' && i < str_length)
					{
						buffer_str_2 += source_string[i];
						i++;
						position_in_str++;
					}
					if(i>= str_length)
					{
						str_error = 1;
					}
					else
					{
						buffer_str_2 += '"';
					}
				}
				else if(source_string[i] == 39) // '''
				{
					buffer_str = "''";
					
					buffer_str_2 += 39;
					if(i + 2 < str_length && source_string[i + 2] == 39)
					{
						buffer_str_2 += source_string[i+1];
						buffer_str_2 += source_string[i+2];
						position_in_str += 2;
						i += 2;
						//cout<< "stringa ^"<< buffer_str_2<< endl;
					}
					else
					{
						str_error = 1;
					}
				}
				else if(i + 1 < str_length && source_string[i] == '.' && source_string[i+1] == '.')
				{
					buffer_str = "..";
					i++;
					position_in_str++;
				}
				else if(source_string[i] == '.' )
				{
					buffer_str = ".";
				}					
				break;
			}
			case this_operator: 
			{
				if(i + 1 < str_length && is_operator(source_string[i+1]))
				{
					char has_cange = 0;
					if(source_string[i] == ':' && source_string[i+1] == ':')
					{
						buffer_str = "::";
						has_cange = 1;
					}
					else if(source_string[i] == '>' && source_string[i+1] == '=')
					{
						has_cange = 1;
						buffer_str = ">=";
					}
					else if(source_string[i] == '<' && source_string[i+1] == '=')
					{
						has_cange = 1;
						buffer_str = "<=";
					}
					else if(source_string[i] == '=' && source_string[i+1] == '=')
					{
						has_cange = 1;
						buffer_str = "==";
					}
					else if(source_string[i] == '&' && source_string[i+1] == '&')
					{
						has_cange = 1;
						buffer_str = "&&";
					}
					else if(source_string[i] == '|' && source_string[i+1] == '|')
					{
						has_cange = 1;
						buffer_str = "||";
					}
					else if(source_string[i] == '<' && source_string[i+1] == '<')
					{
						has_cange = 1;
						buffer_str = "<<";
					}
					else if(source_string[i] == '>' && source_string[i+1] == '>')
					{
						has_cange = 1;
						buffer_str = ">>";
					}
					else if(source_string[i] == '/' && source_string[i+1] == '/')
					{
						has_cange = 2;
						buffer_str = "//";
						while(i < str_length)
						{
							buffer_str_2 += source_string[i];
							i++;
						}
					}
					else if(source_string[i] == '-' && source_string[i+1] == '>')
					{
						has_cange = 1;
						buffer_str = "->";
					}
					if(has_cange == 1)
					{
						i++;
						position_in_str++;
					}
					else if(has_cange != 2)
						buffer_str = source_string[i];	
				}
				else
				{
					if(i + 1 < str_length && source_string[i] == '-' && is_digit(source_string[i+1]))
					{
						i++;
						position_in_str++;
						buffer_str = "-";
						char has_point = 0;
						while(i < str_length && (is_digit(source_string[i]) || is_letter(source_string[i]) || source_string[i] == '.' ) && !number_error)
						{
							if(is_digit(source_string[i]))
							{
								buffer_str += source_string[i];
								i++;
								position_in_str++;
							}
							else if(is_letter(source_string[i]))
							{
								number_error = 1;
							}
							else if(source_string[i] == '.')
							{
								if(has_point)
								{
									buffer_str += source_string[i];
									i++;
									position_in_str++;
									number_error = 1;
								}
								else
								{
									
									buffer_str += source_string[i];
									i++;
									position_in_str++;
									
									has_point = 1;
								}
							}
						}
						i--;
						position_in_str--;
						type_date = this_digit;
					}
					else
						buffer_str = source_string[i];	
				}
				break;
			}
			case this_letter:
			{
				while(i < str_length && (is_digit(source_string[i]) || is_letter(source_string[i])))
				{
					buffer_str += source_string[i];
					i++;
					position_in_str++;
				}
				i--;
				position_in_str--;
				break;
			}
			case this_literal:
			{	
				buffer_str += source_string[i];
				i++;
				position_in_str++;
				while(i < str_length && (is_digit(source_string[i]) || is_letter(source_string[i])))
				{
					buffer_str += source_string[i];
					i++;
					position_in_str++;
				}
				i--;
				position_in_str--;
				break;
			}
			case this_digit:
			{	
				char has_point = 0;
				while(i < str_length && (is_digit(source_string[i]) || is_letter(source_string[i]) || source_string[i] == '.') && !number_error)
				{
					if(is_digit(source_string[i]))
					{
						buffer_str += source_string[i];
						i++;
						position_in_str++;
					}
					else if(is_letter(source_string[i]))
					{
						number_error = 1;
					}
					else if(source_string[i] == '.')
					{
						if(has_point)
						{
							buffer_str += source_string[i];
							i++;
							position_in_str++;
							number_error = 1;
						}
						else
						{
							buffer_str += source_string[i];
							i++;
							position_in_str++;
							has_point = 1;
						}
					}
				}
				i--;
				position_in_str--;
				break;
			}
		}
		
		//	cout<< buffer_str<< "     "<<find_in_tokens(buffer_str) <<endl;
		switch(type_date)
		{
			case this_composite_operator:
			{
				if(buffer_str[0] == '"' && buffer_str[1] == '"')
				{
					if(str_error)
						cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> ERROR \" string not closed: token -> '" <<buffer_str_2 <<"'" << endl;
					else if(options_compilier == 1)
						cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> string: token -> '" <<buffer_str_2 <<"'" << endl;
				}
				else if(buffer_str == "''")
				{
					if(str_error)
						cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> ' not closed: token -> '" <<buffer_str_2 <<"'" <<endl;
					else if(options_compilier == 1)
						cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> simbol: token -> '" <<buffer_str_2 <<"'" << endl;
				}
				else if(buffer_str[0] == '.')
				{
					number_token = find_in_tokens(buffer_str);
					if(number_token == -1)
						cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> unknown: token -> '" <<buffer_str<<"'" << endl;
					else if(options_compilier == 1)
					{
						cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> name token-> '"<< token_class[number_token] <<"' : token -> '" <<buffer_str<<"'" << endl;
					}
				}
					
				break;
			}
			case this_digit:
			{
				if(number_error)
					cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> error number: token -> '" <<buffer_str<<"'" << endl;
				else if(options_compilier == 1)
					cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> number: token -> '" <<buffer_str<<"'" << endl;
				break;
			}
			case this_letter:
			{
				if(options_compilier == 1)
				{
					number_token = find_in_tokens(buffer_str);
					if(number_token == -1)
						cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> literal: token -> '" <<buffer_str<<"'" << endl;
					else
					{
						cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> name token-> '"<< token_class[number_token] <<"' : token -> '" <<buffer_str<<"'" << endl;
					}
				}
				break;
			}
			case this_literal:
			{
				if(options_compilier == 1)
					cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> Literal: token -> '" <<buffer_str<<"'" << endl;
				break;
			}
			case this_operator: 
			{
				if(buffer_str == "//" )
				{
					if(options_compilier == 1)
						cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> comment: token -> '" <<buffer_str_2<<"'" << endl;
				}
				else
				{
					number_token = find_in_tokens(buffer_str);
					if(number_token == -1)
						cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> unknown: token -> '" <<buffer_str<<"'" << endl;
					else if(options_compilier == 1)
					{
						cout <<"Loc=<"<<line_in_file<< ":" << position_begin_word << "> name token-> '"<< token_class[number_token] <<"' : token -> '" <<buffer_str<<"'" << endl;
					}
				}
				break;
			}
		}
			
		
		position_in_str++;
	}

	return 0;
}
#ifndef CATCH_CONFIG_MAIN
int main(int argc, char *argv[]) 
{
	
	options_compilier = 0;
	if(argc == 2)
	{
		options_compilier = 0;
	}
	else if(argc == 3)
	{
		string source_opoptions = argv[2];
		if( source_opoptions == "--dump-tokens")
		{
			options_compilier = 1;
		}	
	}
	else
	{
		cout<< "invalid number of parameters "<< argc <<endl;
		return 0;
	}
	string source_string;
	ifstream in_file(argv[1]);
	if(!in_file)
	{
		cout<< "File cannot be opened : "<< argv[1] <<endl;
		return 0;
	}
	int line_in_file = 1;
	
	while(getline(in_file, source_string))
	{
		analysis_row(source_string, line_in_file);
		line_in_file++;
	}
	return 0;
}
#else

TEST_CASE("Gonna meet <public>", "First")
{
       
}
#endif


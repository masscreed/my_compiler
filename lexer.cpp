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

int find_in_exceptions(string token)
{
	int i = 0, result = 0;		
	for(i = 0; i < 4 && !result; i++)
	{
		result = equal_str(token, exceptions[i]);
		if(result)
			return i;
	}
	return -1;
}

bool is_letter(char c)
{
	if( c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
		return true;
	return false;
}

bool is_letter_or_underscores(char c)
{
	if( is_letter( c) || c == '_')
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

void prinf_in_consol(int line, int position, string str)
{
	cout <<"Loc=<"<<line<< ":" << position << "> "<< str << endl;
}



bool is_digit(char c)
{
	if(c >= '0' && c <= '9')
		return true;
	return false;
}

bool is_digit_or_letter(char c)
{
	return (is_digit(c) || is_letter(c));
}

bool is_hexadecimal(char c)
{
	if(is_digit(c) || c >= 'a' && c <= 'f')
		return true;
	return false;
}

bool is_octal(char c)
{
	if(c >= '0' && c <= '7')
		return true;
	return false;
}

char type_char(const char c)
  {
	if(is_operator(c))
		return this_operator;
	else if( is_letter(c))
		return this_letter;
	else if( c == '_')
		return this_literal;
	else if(is_digit(c))
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
	char error_comment = 0;
	
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
				else if(source_string[i] == '\'') // '''
				{
					buffer_str = "''";
					
					buffer_str_2 += '\'';
					if(i + 2 < str_length && source_string[i + 2] == '\'')
					{
						buffer_str_2 += source_string[i+1];
						buffer_str_2 += source_string[i+2];
						position_in_str += 2;
						i += 2;
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
					else if(source_string[i] == '/' && source_string[i+1] == '*')
					{
						error_comment = 0;
						char flag = 1;
						has_cange = 2;
						buffer_str = "/**/";
						while(i < str_length && flag)
						{
							if(source_string[i] == '*' && i + 1 < str_length  && source_string[i+1] == '/')
							{
								buffer_str_2 += "*/";
								flag = 0;
							}
							else
							{
								buffer_str_2 += source_string[i];
								
							}
							i++;
							position_in_str++;
						}
						if(flag == 1)
							error_comment = 1;
						
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
						while(i < str_length && (is_digit_or_letter(source_string[i]) || source_string[i] == '.' ) && !number_error)
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
				while(i < str_length && is_digit_or_letter(source_string[i]))
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
				while(i < str_length && is_digit_or_letter(source_string[i]))
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
				if(i + 1 < str_length && source_string[i] == '0' && is_digit_or_letter(source_string[i + 1]) )
				{
					buffer_str += source_string[i];
					i++;
					position_in_str++;
					if(source_string[i] == 'x')
					{
						buffer_str += source_string[i];
						i++;
						position_in_str++;
						while(i < str_length && is_digit_or_letter(source_string[i]) && !number_error)
						{
							if(is_hexadecimal(source_string[i]))
							{
								buffer_str += source_string[i];
								i++;
								position_in_str++;
							}
							else
							{
								buffer_str += source_string[i];
								number_error = 2;
							}
						}
					}
					else if(is_digit(source_string[i]))
					{
						while(i < str_length && is_digit_or_letter(source_string[i]) && !number_error)
						{
							if(is_octal(source_string[i]))
							{
								buffer_str += source_string[i];
								i++;
								position_in_str++;
							}
							else
							{
								buffer_str += source_string[i];
								number_error = 3;
							}
						}
					}
					else
					{
						buffer_str += source_string[i];
						number_error = 1;
					}
					
				}
				else
				{
					char has_point = 0;
					char ignored = 1;
					while(i < str_length && is_digit_or_letter(source_string[i]) || source_string[i] == '.' && !number_error && ignored)
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
							buffer_str += source_string[i];
						}
						else if(i + 1 < str_length && source_string[i] == '.' && source_string[i+1] == '.')
						{
							ignored = 0;
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
				}
				if(!number_error)
				{
					i--;
					position_in_str--;
				}
				break;
			}
		}
		
		switch(type_date)
		{
			case this_composite_operator:
			{
				if(buffer_str[0] == '"' && buffer_str[1] == '"')
				{
					if(str_error)
						prinf_in_consol(line_in_file, position_begin_word,"ERROR \" string not closed: Lexeme -> '" + buffer_str_2 + "'");
					else if(options_compilier == 1)
						prinf_in_consol(line_in_file, position_begin_word, " name token-> 'string' : Lexeme -> '" + buffer_str_2 + "'");
				}
				else if(buffer_str == "''")
				{
					if(str_error)
						prinf_in_consol(line_in_file, position_begin_word, " not closed: Lexeme -> '" + buffer_str_2 + "'");
					else if(options_compilier == 1)
						prinf_in_consol(line_in_file, position_begin_word, " name token-> 'simbol' : Lexeme -> '" + buffer_str_2 + "'");
				}
				else if(buffer_str[0] == '.')
				{
					number_token = find_in_tokens(buffer_str);
					if(number_token == -1)
						prinf_in_consol(line_in_file, position_begin_word, " name token-> 'unknown' : Lexeme -> '" + buffer_str + "'");
					else if(options_compilier == 1)
					{
						string buf =  token_class[number_token];
						prinf_in_consol(line_in_file, position_begin_word, " name token-> '" + buf + "' : Lexeme -> '" + buffer_str + "'");
					}
				}
					
				break;
			}
			case this_digit:
			{
				switch(number_error)
				{
					case 1:
					{
						prinf_in_consol(line_in_file, position_begin_word, " ERROR the number contains the letter: Lexeme -> '" + buffer_str + "'");
						break;
					}
					case 2:
					{
						prinf_in_consol(line_in_file, position_begin_word, " ERROR in hexadecimal number: Lexeme -> '" + buffer_str + "'");
						break;
					}
					case 3:
					{
						prinf_in_consol(line_in_file, position_begin_word, " ERROR in octal number: Lexeme -> '" + buffer_str + "'");
						break;
					}
					case 0:
					{
						if(options_compilier == 1)
							prinf_in_consol(line_in_file, position_begin_word, " name token-> 'number' : Lexeme -> '" + buffer_str + "'");
						break;
					}
				}
				break;
			}
			case this_letter:
			{
				int is_exceptions = -1;
				is_exceptions = find_in_exceptions(buffer_str);
				if(is_exceptions == -1)
				{
					if(options_compilier == 1)
					{
						number_token = find_in_tokens(buffer_str);
						if(number_token == -1)
							prinf_in_consol(line_in_file, position_begin_word, " name token-> 'literal' : Lexeme -> '" + buffer_str + "'");
						else
						{
							string buf = token_class[number_token];
							prinf_in_consol(line_in_file, position_begin_word, " name token-> '" + buf + "' : Lexeme -> '" + buffer_str + "'");
						}
					}
				}
				else
				{
					string buf;
					if(i + 1 < str_length && source_string[i + 1] == '!')
					{
						buffer_str += source_string[i + 1];
						i++;
						position_in_str++;
						number_token = find_in_tokens(buffer_str);
						buf = token_class[number_token];
						if(options_compilier == 1)
							prinf_in_consol(line_in_file, position_begin_word, " name token-> '" + buf + "' : Lexeme -> '" + buffer_str + "'");
					}
					else
					{
						buf = exceptions[is_exceptions];
						prinf_in_consol(line_in_file, position_begin_word, " ERROR not found ! in name token-> '" + buf + "' : Lexeme -> '" + buffer_str + "'");
					}
				}
				break;
			}
			case this_literal:
			{
				if(options_compilier == 1)
					prinf_in_consol(line_in_file, position_begin_word, " name token-> 'literal' : Lexeme -> '" + buffer_str + "'");
				break;
			}
			case this_operator: 
			{
				if(buffer_str == "//" )
				{
					if(options_compilier == 1)
						prinf_in_consol(line_in_file, position_begin_word, " name token-> 'comment' : Lexeme -> '" + buffer_str_2 + "'");
				}
				else if(buffer_str == "/**/")
				{
					if(error_comment == 1)
						prinf_in_consol(line_in_file, position_begin_word, " ERROR the comment is not finished: Lexeme -> '"  + buffer_str_2 + "'");
					else if(options_compilier == 1)
						prinf_in_consol(line_in_file, position_begin_word, " name token-> 'comment' : Lexeme -> '" + buffer_str_2 + "'");
				}
				else
				{
					number_token = find_in_tokens(buffer_str);
					if(number_token == -1)
						prinf_in_consol(line_in_file, position_begin_word, " name token-> 'unknown' : Lexeme -> '" + buffer_str + "'");
					else if(options_compilier == 1)
					{
						string buf = token_class[number_token];
						prinf_in_consol(line_in_file, position_begin_word, " name token-> '" + buf + "' : Lexeme -> '" + buffer_str + "'");
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
		if(source_string.length() > 1)
			analysis_row(source_string, line_in_file);
		else if(options_compilier == 1)
			prinf_in_consol(line_in_file, 1, "name token-> '\\n'");
		line_in_file++;
	}
	return 0;
}
#else

TEST_CASE("find_token", "1")
{
	string buffer;
	buffer = "fn";
	REQUIRE(find_in_tokens(buffer) == 0);
	buffer = "-";
	REQUIRE(find_in_tokens(buffer) == 22);
	buffer = "3213";
	REQUIRE(find_in_tokens(buffer) == -1);
}

TEST_CASE("equal_str", "2")
{
	string buffer, buffer_s;
	char a[100];
	buffer = "fn";
	buffer_s = "fn"; 
	strncpy(a, buffer_s.c_str(), sizeof(a) - 1);

	REQUIRE(equal_str(buffer, a) == 1);
	buffer = "-";
	buffer_s = "fn";
	strncpy(a, buffer_s.c_str(), sizeof(a) - 1);	
	REQUIRE(equal_str(buffer, a) == 0);
}

TEST_CASE("is_letter", "3")
{
	char a;
	a = '1';
	REQUIRE(is_letter(a) == false);
	a = 'a';
	REQUIRE(is_letter(a) == true);
}

TEST_CASE("is_operator", "4")
{
	char a;
	a = '1';
	REQUIRE(is_operator(a) == false);
	a = 'a';
	REQUIRE(is_operator(a) == false);
	a = '/';
	REQUIRE(is_operator(a) == true);
	a = ' ';
	REQUIRE(is_operator(a) == false);
}

TEST_CASE("is_digit", "5")
{
	char a;
	a = '1';
	REQUIRE(is_digit(a) == true);
	a = 'a';
	REQUIRE(is_digit(a) == false);
}

TEST_CASE("type_char", "6")
{
	char a;
	a = '+';
	REQUIRE(type_char(a) == this_operator);
	a = 'a';
	REQUIRE(type_char(a) == this_letter);
	a = '1';
	REQUIRE(type_char(a) == this_digit);
	a = '_';
	REQUIRE(type_char(a) == this_literal);
	a = '.';
	REQUIRE(type_char(a) == this_composite_operator);
}

TEST_CASE("is_hexadecimal", "7")
{
	char a;
	a = '0';
	REQUIRE(is_hexadecimal(a) == true);
	a = 'g';
	REQUIRE(is_hexadecimal(a) == false);
}

TEST_CASE("is_octal", "8")
{
	char a;
	a = '0';
	REQUIRE(is_octal(a) == true);
	a = '8';
	REQUIRE(is_octal(a) == false);
}
#endif

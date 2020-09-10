#ifndef LEXER
#define LEXER

#include <iostream> 
#include <fstream>
#include <string.h>
#include <cctype>
#include <regex>
//#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "token.hpp"
using namespace std;

char equal_str(string s1, char s2[]);
int find_in_exceptions(string token);
bool is_letter(char c);
bool is_letter_or_underscores(char c);
bool is_operator(char c);
bool is_digit(char c);
bool is_digit_or_letter(char c);
bool is_hexadecimal(char c);
bool is_octal(char c);
char get_type_char(const char c);

enum {
	this_composite_operator = -1,
	this_operator = 0,
	this_letter = 1,
	this_literal= 2,
	this_digit = 3
};

class token {
	string Lexeme;
	int line, position, TokenClass;
public:
	token(){
		TokenClass = -1;
		Lexeme = "";
		line = -1;
		position = -1;
	}

	void set_position(int pos){
		position = pos;
	}

	int get_position(){
		return position;
	}

	void set_line(int num){
		line = num;
	}

	int get_line(){
		return line;
	}

	void set_token_class(string tok_name){		
		for(int i = 0; token_name[i][0] != '\0'; i++)
		{
			if(equal_str(tok_name, token_name[i]))
			{
				TokenClass = i;
				break;
			}
				
		}
	}
	int get_token_class(){		
		return TokenClass;
	}



};

#endif

#ifndef TOKEN
#define TOKEN
char token_class[][150] = 
{
	"function",
	"int 8",
	"int 16",
	"int 32",
	"int 64",
	"int 128",
	"unsigned int 8",
	"unsigned int 16",
	"unsigned int 32",
	"unsigned int 64",
	"unsigned int 128",
	"literal",
	"print",
	"boolean",
	"char",
	"variable to change",
	"::",
	":",
	"''",
	"\"\"",
	"format",
	"plus",
	"minus",
	"multiply",
	"divide",
	"%",
	">",
	"<",
	">=",
	"<=",
	"==",
	"=",
	"&&",
	"&",
	"||",
	"|",
	"!",
	"^",
	"<<",
	">>",
	"keyword If",
	"keyword Else",
	"cycle For",
	"semi",
	"l_brace",
	"r_brace",
	"[",
	"]",
	"l_paren",
	"r_paren",
	"keyword match",
	"in",
	"..",
	"cycle while",
	"keyword break",
	"keyword Return",
	"float 64",
	"float 32",
	"float 128",
	"vec",
	"loop",
	"!",
	",",
	".",
	"struct",
	"Method in the structure",
	"->",
	"this structure",
	"print",
	"assert"
};
char token_name[][150] = 
{
	"fn",
	"i8",
	"i16",
	"i32",
	"i64",
	"i128",
	"u8",
	"u16",
	"u32",
	"u64",
	"u128",
	"let",
	"println!",
	"bool",
	"char",
	"mut",
	"::",
	":",
	"''",
	"\"\"",
	"format!",
	"+",
	"-",
	"*",
	"/",
	"%",
	">",
	"<",
	">=",
	"<=",
	"==",
	"=",
	"&&",
	"&",
	"||",
	"|",
	"!",
	"^",
	"<<",
	">>",
	"if",
	"else",
	"for",
	";",
	"{",
	"}",
	"[",
	"]",
	"(",
	")",
	"match",
	"in",
	"..",
	"while",
	"break",
	"return",
	"f64",
	"f32",
	"f128",
	"vec",
	"loop",
	"!",
	",",
	".",
	"struct",
	"impl",
	"->",
	"self",
	"print!",
	"assert!"
};

char exceptions[][10]
{
	"print",
	"assert",
	"println",
	"format"
};
#endif
#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "Header.h"

#define TOKEN_MAX_IDENTIFIER_LENGTH 256

typedef struct Token {
	char* _filePath;
	int _line;
	int _col;
	int _offset;
 
	int _len;
	char _value[TOKEN_MAX_IDENTIFIER_LENGTH];

	enum TokenType {
// invalid and EOF 
		Invalid,
		Eof,

// cap types
		LParen,         // (
		RParen,         // )
		LBrack,         // [
		RBrack,         // ]
		LBrace,         // {
		RBrace,         // }
    
// special chars types
		Comma,          // ,
		Colon,          // :
		SemiColon,      // ;
		Dot,            // .
    
		Plus,           // +
		Minus,          // -
		Star,           // *
		Slash,          // /
		Percent,        // %
		Ampersand,      // &
		Pipe,           // |
		Caret,          // ^
		Tilde,          // ~
		Exclam,         // !
		At,             // @
		Hash,           // #
		BSlash,         // "\"

// multi-char operators
		Shl,            // <<
		Shr,            // >>

// comparators
		Eq,             // ==
		Ne,             // !=
		Lt,             // <
		Gt,             // >
		Le,             // <=
		Ge,             // >=

// literal types
		Number,         // [0-9]+
		Char_literal,   // \'[ascii]*\'
		String,         // \"[ascii]*\"

// kept words
		If,             // if
		Else,           // else
		For,            // for
		// Do,             // do
		While,          // while
		// Extern,         // extern
		// Typedef,        // typedef
		// Signed,         // signed
		// Unsigned,       // unsigned
		Return,         // return

// kept type words
		Void,           // void
		Int,            // int
		Char,           // char
		Float,          // Float
		Double,         // Double
		Long,           // Long
		
// free words
		SymbolName,         // ( a-z | A-Z | _ )[ a-z | A-Z | 0-9 | _ ]*
	} _token_type;
} Token;

#endif 

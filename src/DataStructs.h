#ifndef _DATA_STRUCTS_H_
#define _DATA_STRUCTS_H_

#include "Header.h"

// typedef enum _node_t {
// 	_node_constant,   // constants
// 	_node_condition,  // condition statement
// 	_node_assignment, // assignment statement
// 	_node_code_block, // a code block {...}
// 	_node_if,         // an if entry
// 	_node_else_if,    // an else-if entry
// 	_node_else,       // an else entry
// 	_return,          // a return
// } _node_t;

typedef struct Token {
	// char* _file_path;
	// int _line;
	// int _col;
 
	int _len;
	char* _token;

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
		Do,             // do
		While,          // while
		Extern,         // extern
		Typedef,        // typedef
		Signed,         // signed
		Unsigned,       // unsigned
		Return,         // return

// kept type words
		Void,           // void
		Int,            // int
		Char,           // char
		Float,          // Float
		Double,         // Double
		Long,           // Long
		
// free words
		Symbol,         // ( a-z | A-Z | _ )[ a-z | A-Z | 0-9 | _ ]*
	} _token_type;

	struct Token* _prev;
	struct Token* _next;
} Token;

// typedef struct AST {
// 	_node_t _type;
// 	vector* _values;
// } AST;

#endif 
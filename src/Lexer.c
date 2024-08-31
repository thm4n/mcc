#include "Lexer.h"

Token* createToken(Lexer* lexedFile) {
	Token* token = (Token*)malloc(sizeof(Token));
	if(!token) {
		errlog("Failed to allocate memory");
		return NULL;
	}

	strcpy(token->_filePath, lexedFile->_filePath);

	token->_offset = lexedFile->_offset;
	token->_line = lexedFile->_line;
	token->_col = lexedFile->_col;

	token->_len = 0;

	return token;
}

void freeToken(Token* token) {
	if(token) {
		dbglog("Deallocating token");
		free(token);
	}
	else {
		dbglog("\"Deallocating\" NULL token");
	}
}

void addToken(Lexer* lexedFile, Token* token) {
	warlog("WIP");
}

void skipWhitespace(Lexer* lexedFile) {
	warlog("WIP");
}

char getNextChar(Lexer* lexedFile) {
	char ch = 0;
	
	if(feof(lexedFile->_fd)) {
		warlog("unexpected EOF");
		return EOF;
	}

	ch = fgetc(lexedFile->_fd);
	lexedFile->_offset++;

	return ch;
}

int readUntil(Lexer* lexedFile, Token* token, int (*cb)(char)) {
	int res = SUCCESS;
	warlog("WIP");
	return res;
}

char peekNextChar(Lexer* lexedFile) {
	char ch = 0;

	if(feof(lexedFile->_fd)) {
		warlog("unexpected EOF");
		return EOF;
	}

	ch = fgetc(lexedFile->_fd);
	fseek(lexedFile->_fd, -1, SEEK_CUR);

	return ch;
}

int getNextToken(Lexer* lexedFile) {
	Token* token = NULL;
	char ch = 0;
	int res = SUCCESS;
	
	token = createToken(lexedFile);

	skipWhitespace(lexedFile);
	if(isEndOfFile(lexedFile)) {
		if(!token) {
			res = ERRCODE_ALLOC;
			goto __getNextToken_end;
		}

		token->_tokenType = TokenTypeEOF;
		addToken(lexedFile, token);
		goto __getNextToken_end;
	}

	ch = getNextChar(lexedFile);
	switch(ch) {
	case ',':
		token->_tokenType = Comma;
		token->_value[token->_offset++] = ch;
		break;
	case ';':
		token->_tokenType = SemiColon;
		token->_value[token->_offset++] = ch;
		break;
	case '(':
		token->_tokenType = LParen;
		token->_value[token->_offset++] = ch;
		break;
	case ')':
		token->_tokenType = RParen;
		token->_value[token->_offset++] = ch;
		break;
	case '[':
		token->_tokenType = LBrack;
		token->_value[token->_offset++] = ch;
		break;
	case ']':
		token->_tokenType = RBrack;
		token->_value[token->_offset++] = ch;
		break;
	case '{':
		token->_tokenType = LBrace;
		token->_value[token->_offset++] = ch;
		break;
	case '}':
		token->_tokenType = RBrace;
		token->_value[token->_offset++] = ch;
		break;
	case '*':
		token->_tokenType = Star;
		token->_value[token->_offset++] = ch;
		break;
	case '/':
		token->_tokenType = Slash;
		token->_value[token->_offset++] = ch;
		break;
	case '%':
		token->_tokenType = Percent;
		token->_value[token->_offset++] = ch;
		break;
	case '+':
		token->_tokenType = Plus;
		token->_value[token->_offset++] = ch;
		break;
	case '-':
		token->_tokenType = Minus;
		token->_value[token->_offset++] = ch;
		break;


	case '<':
		token->_value[token->_offset++] = ch;
		switch(peekNextChar(lexedFile)) {
		case '<':
			token->_tokenType = Shl;
			token->_value[token->_offset++] = getNextChar(lexedFile);
			break;
		case '=':
			token->_tokenType = Le;
			token->_value[token->_offset++] = getNextChar(lexedFile);
			break;
		default:	
			token->_tokenType = Lt;
		}
		break;
	case '>':
		token->_value[token->_offset++] = ch;
		switch(peekNextChar(lexedFile)) {
		case '>':
			token->_tokenType = Shr;
			token->_value[token->_offset++] = getNextChar(lexedFile);
			break;
		case '=':
			token->_tokenType = Ge;
			token->_value[token->_offset++] = getNextChar(lexedFile);
			break;
		default:	
			token->_tokenType = Gt;
		}
		break;
	case '!':
		token->_tokenType = Exclam;
		token->_value[token->_offset++] = ch;
		if(peekNextChar(lexedFile) == '=') {
			token->_tokenType = Ne;
			token->_value[token->_offset++] = getNextChar(lexedFile);
		}
		break;
	case '=':
		token->_tokenType = Equal;
		token->_value[token->_offset++] = ch;
		if(peekNextChar(lexedFile) == '=') {
			token->_tokenType = Eq;
			token->_value[token->_offset++] = getNextChar(lexedFile);
		}
		break;
	
	default:
		if(IS_ALPHA(ch) || ch == '_') {
			res = readUntil(lexedFile, token, isAllowedInIdentifier);
			if(res != SUCCESS) {
				errlog("failed to read expected identifier: '%s'. failed with error: %d", token->_value, res);
				goto __getNextToken_end;
			}
			token->_tokenType = SymbolName;
		}
		else if(IS_DIGIT(ch)) {
			res = readUntil(lexedFile, token, isAllowedInNumber);
			if(res != SUCCESS) {
				errlog("failed to read expected number: '%s'. failed with error: %d", token->_value, res);
				goto __getNextToken_end;
			}
			token->_tokenType = Number;
		}
		else if(ch == '"') {
			res = readUntil(lexedFile, token, isDQuotes);
			if(res != SUCCESS) {
				errlog("failed to read string '%s'. failed with error: %d", token->_value, res);
				goto __getNextToken_end;
			}
			token->_tokenType = String;
		}
		else if(ch == '\'') {
			res = readUntil(lexedFile, token, isQuote);
			if(res != SUCCESS) {
				errlog("failed to read string '%s'. failed with error: %d", token->_value, res);
				goto __getNextToken_end;
			}
			token->_tokenType = Char_Literal;
		}
		else {
			warlog("failed to lex: '%c' - unknown character", ch);
		}
	}

	addToken(lexedFile, token);

__getNextToken_end:
	if(res != SUCCESS) {
		if(token) {
			freeToken(token);
		}
	}

	return res;
}

int lexer(Lexer** pLexedFile, const char* filePath) {
	int ret = SUCCESS;
	Lexer* lexedFile = *pLexedFile;

	if(lexedFile) {
		errlog("lexer recieved initialized Lexer*");
		ret = ERRCODE_USAGE;
		goto __lexer_end;
	}

	if(strlen(filePath) > 256) {
		errlog("file path to compile is too long - max 256 chars");
		ret = ERRCODE_IO;
		goto __lexer_end;
	}

	lexedFile = (Lexer*)malloc(sizeof(Lexer));
	if(!lexedFile) {
		errlog("Failed to allocate memory");
		ret = ERRCODE_ALLOC;
		goto __lexer_end;
	}
	memset(lexedFile, 0, sizeof(Lexer));
	
	strcpy(lexedFile->_filePath, filePath);
	lexedFile->_fd = fopen(lexedFile->_filePath, "r");

	lexedFile->_offset = 0;
	lexedFile->_col = 0;
	lexedFile->_line = 1;

	lexedFile->_tokensIndex = 0;

	lexedFile->_tokensArray = NULL;
	lexedFile->_tokensArrayLength = 0;

	do {

	} while(lexedFile->_tokens[lexedFile->_tokensIndex] && lexedFile->_tokens[lexedFile->_tokensIndex]->_tokenType != TokenTypeEOF);

__lexer_end:
	if(ret == SUCCESS) {
		dbglog("got to __lexer_end with SUCCESS");
		*pLexedFile = lexedFile;
	}
	else {
		dbglog("got to __lexer_end with errcode %d", ret);
		if(lexedFile) {
			dbglog("Deallocating 'lexedFile'");
			if(lexedFile->_filePath) {
				dbglog("Deallocating 'lexedFile->_filePath'");
				free(lexedFile->_filePath);
			}
			if(lexedFile->_fd) {
				dbglog("closing file 'lexedFile->_fd");
				fclose(lexedFile->_fd);
			}
			free(lexedFile);
			*pLexedFile = NULL;
		}
	}

	return ret;
}

#include "Lexer.h"

Token* createToken(Lexer* lexedFile) {
	Token* token = (Token*)malloc(sizeof(Token));
	if(!token) {
		errlog("Failed to allocate memory");
		return NULL;
	}

	strcpy(token->_filePath, lexedFile->_filePath);
	memset(token->_value, 0, IDENTIFIER_MAX_LENGTH);
	token->_offset = lexedFile->_offset;
	token->_line = lexedFile->_line;
	token->_col = lexedFile->_col;

	token->_len = 0;

	return token;
}

void freeToken(Token* token) {
	if(token) {
		dbglog("Deallocating token: '%s'", token->_value);
		free(token);
	}
	else {
		dbglog("\"Deallocating\" NULL token");
	}
}

int replaceTokensArrayCache(Lexer* lexedFile) {
	Token** tempTokensArray = NULL;
	int newTokensArrayLength = lexedFile->_tokensArrayLength;
	int res = SUCCESS;

	tempTokensArray = lexedFile->_tokensArray;
	newTokensArrayLength += lexedFile->_tokensIndex;
	lexedFile->_tokensArray = (Token**)malloc(newTokensArrayLength * sizeof(Token*));
	if(!lexedFile->_tokensArray) {
		errlog("Failed to allocate memory");
		res = ERRCODE_ALLOC;
		goto __replaceTokensArrayCache_end;
	}

	int i = 0, j = 0;
	for(i = 0; i < lexedFile->_tokensArrayLength; i++) {
		lexedFile->_tokensArray[i] = tempTokensArray[i];
	}
	for(; i < newTokensArrayLength && j < lexedFile->_tokensIndex; i++, j++) {
		lexedFile->_tokensArray[i] = lexedFile->_tokens[j];
	}
	free(tempTokensArray); // after memory was stashed in 'lexedFile'

	lexedFile->_tokensArrayLength = newTokensArrayLength;
	memset(lexedFile->_tokens, 0, TOKEN_CACHE_SIZE * sizeof(Token*));
	lexedFile->_tokensIndex = 0;

__replaceTokensArrayCache_end:
	if(res != SUCCESS) {
		if(lexedFile->_tokensArray) {
			free(lexedFile->_tokensArray);
			lexedFile->_tokensArray = tempTokensArray;
		}
	}
	return res;
}

int addToken(Lexer* lexedFile, Token* token) {
	int res = SUCCESS;

	if(lexedFile->_tokensIndex >= TOKEN_CACHE_SIZE) {
		dbglog("replacing tokens array cache");
		res = replaceTokensArrayCache(lexedFile);
	}

	lexedFile->_tokens[lexedFile->_tokensIndex++] = token;

	return res;
}

void skipWhitespace(Lexer* lexedFile) {
	readUntil(lexedFile, NULL, isWhitespace);
}

char getNextChar(Lexer* lexedFile) {
	char ch = 0;
	
	if(isEndOfFile(lexedFile)) {
		warlog("unexpected EOF");
		return EOF;
	}

	dbglog("lexedFile->_offset: %d", lexedFile->_offset);
	ch = fgetc(lexedFile->_fd);
	lexedFile->_offset++;
	dbglog("lexedFile->_offset: %d", lexedFile->_offset);

	return ch;
}

void readUntil(Lexer* lexedFile, Token* token, int (*cb)(char)) {
	char ch = 0;

	ch = peekNextChar(lexedFile);
	while(cb(ch) && ch != EOF) {
		ch = getNextChar(lexedFile);
		if(token)
			token->_value[token->_len++] = ch;
		ch = peekNextChar(lexedFile);
	}
}

char peekNextChar(Lexer* lexedFile) {
	char ch = 0;

	if(isEndOfFile(lexedFile)) {
		warlog("unexpected EOF");
		return EOF;
	}

	ch = fgetc(lexedFile->_fd);
	fseek(lexedFile->_fd, -1, SEEK_CUR);

	return ch;
}

int isEndOfFile(Lexer* lexedFile) {
	dbglog("lexedFile->_offset: %d", lexedFile->_offset);
	if(lexedFile->_offset < lexedFile->_file_length)
		return false;
	return true;
}

int getFileLength(Lexer* lexedFile) {
	int res = SUCCESS;
	int pos = 0;

	if(!lexedFile->_fd) {
		dbglog("lexedFile->_fd = NULL");
		res = ERRCODE_USAGE;
		goto __getFileLength_end;
	}

	dbglog("checking current position");
	pos = ftell(lexedFile->_fd);
	if(pos < 0) {
		res = pos;
		dbglog("ftell returned %d", res);
		goto __getFileLength_end;
	}
	
	dbglog("seeking to end of file");
	res = fseek(lexedFile->_fd, 0, SEEK_END);
	if(res != SUCCESS) {
		dbglog("fseek returned %d", res);
		goto __getFileLength_end;
	}

	dbglog("checking current position");
	lexedFile->_file_length = ftell(lexedFile->_fd);
	if(pos < 0) {
		res = pos;
		dbglog("ftell returned %d", res);
		goto __getFileLength_end;
	}

	dbglog("seeking to previous position");
	res = fseek(lexedFile->_fd, pos, SEEK_SET);
	if(res != SUCCESS) {
		dbglog("fseek returned %d", res);
		goto __getFileLength_end;
	}

__getFileLength_end:
	if(res != SUCCESS)
		warlog("failed to determine file length: %d", res);
	return res;
}

int getNextToken(Lexer* lexedFile) {
	Token* token = NULL;
	char ch = 0;
	int res = SUCCESS;
	
	dbglog("creating token");
	token = createToken(lexedFile);
	if(!token) {
		dbglog("failed to create token");
		res = ERRCODE_ALLOC;
		goto __getNextToken_end;
	}

	dbglog("skipping whitespace");
	skipWhitespace(lexedFile);
	dbglog("checking if EOF");
	if(isEndOfFile(lexedFile)) {
		dbglog("EOF: True");
		token->_tokenType = TokenTypeEOF;
		res = addToken(lexedFile, token);
		if(res != SUCCESS) {
			errlog("failed to add token of type EOF");
		}
		else {
			res = TokenTypeEOF;
		}
		goto __getNextToken_end;
	}

	dbglog("peeking at next char");
	ch = peekNextChar(lexedFile);
	switch(ch) {
	case '(':
		token->_tokenType = LParen;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case ')':
		token->_tokenType = RParen;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '[':
		token->_tokenType = LBrack;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case ']':
		token->_tokenType = RBrack;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '{':
		token->_tokenType = LBrace;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '}':
		token->_tokenType = RBrace;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	
	case ',':
		token->_tokenType = Comma;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case ':':
		token->_tokenType = Colon;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case ';':
		token->_tokenType = SemiColon;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '.':
		token->_tokenType = Dot;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;

	case '=':
		token->_tokenType = Equal;
		token->_value[token->_len++] = getNextChar(lexedFile);
		if(peekNextChar(lexedFile) == '=') {
			token->_tokenType = Eq;
			token->_value[token->_len++] = getNextChar(lexedFile);
		}
		break;
	case '+':
		token->_tokenType = Plus;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '-':
		token->_tokenType = Minus;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '*':
		token->_tokenType = Star;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '/':
		token->_tokenType = Slash;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '%':
		token->_tokenType = Percent;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '&':
		token->_tokenType = Ampersand;
		token->_value[token->_len++] = getNextChar(lexedFile);
		if(peekNextChar(lexedFile) == '&') {
			token->_tokenType = DAmp;
			token->_value[token->_len++] = getNextChar(lexedFile);
		}
		break;
	case '|':
		token->_tokenType = Pipe;
		token->_value[token->_len++] = getNextChar(lexedFile);
		if(peekNextChar(lexedFile) == '|') {
			token->_tokenType = DPipe;
			token->_value[token->_len++] = getNextChar(lexedFile);
		}
		break;
	case '^':
		token->_tokenType = Caret;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '~':
		token->_tokenType = Tilde;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '!':
		token->_tokenType = Exclam;
		token->_value[token->_len++] = getNextChar(lexedFile);
		if(peekNextChar(lexedFile) == '=') {
			token->_tokenType = Ne;
			token->_value[token->_len++] = getNextChar(lexedFile);
		}
		break;
	case '#':
		token->_tokenType = Hash;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;
	case '\\':
		token->_tokenType = BSlash;
		token->_value[token->_len++] = getNextChar(lexedFile);
		break;

	case '<':
		token->_value[token->_len++] = getNextChar(lexedFile);
		switch(peekNextChar(lexedFile)) {
		case '<':
			token->_tokenType = Shl;
			token->_value[token->_len++] = getNextChar(lexedFile);
			break;
		case '=':
			token->_tokenType = Le;
			token->_value[token->_len++] = getNextChar(lexedFile);
			break;
		default:	
			token->_tokenType = Lt;
		}
		break;
	case '>':
		token->_value[token->_len++] = getNextChar(lexedFile);
		switch(peekNextChar(lexedFile)) {
		case '>':
			token->_tokenType = Shr;
			token->_value[token->_len++] = getNextChar(lexedFile);
			break;
		case '=':
			token->_tokenType = Ge;
			token->_value[token->_len++] = getNextChar(lexedFile);
			break;
		default:	
			token->_tokenType = Gt;
		}
		break;


	
	default:
		dbglog("got to default in switch-case");

		if(IS_ALPHA(ch) || ch == '_') {
			dbglog("readUntil: isAllowedInIndentifier");
			readUntil(lexedFile, token, isAllowedInIdentifier);
			token->_tokenType = SymbolName;
		}
		else if(IS_DIGIT(ch)) {
			dbglog("readUntil: isAllowedInNumber");
			readUntil(lexedFile, token, isAllowedInNumber);
			token->_tokenType = Number;
		}
		else if(ch == '"') {
			getNextChar(lexedFile);
			dbglog("readUntil: isDQuotes");
			readUntil(lexedFile, token, isDQuotes);
			if(getNextChar(lexedFile) != ch) {
				errlog("failed to read string '%s'. failed with error: %d", token->_value, res);
				goto __getNextToken_end;
			}
			token->_tokenType = String;
		}
		else if(ch == '\'') {
			getNextChar(lexedFile);
			dbglog("readUntil: isQuote");
			readUntil(lexedFile, token, isQuote);
			if(getNextChar(lexedFile) != ch) {
				errlog("failed to read string '%s'. failed with error: %d", token->_value, res);
				goto __getNextToken_end;
			}
			token->_tokenType = Char_Literal;
		}
		else {
			warlog("failed to lex: '%c' - unknown character", ch);
		}
	}

	res = addToken(lexedFile, token);
	if(res != SUCCESS) {
		errlog("failed to add token '%s'. failed with error: %d", token->_value, res);
		goto __getNextToken_end;
	}
	
__getNextToken_end:
	if(res != SUCCESS) {
		if(token) {
			// freeToken(token);
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
	ret = getFileLength(lexedFile);
	if(ret != SUCCESS) {
		dbglog("error getting file length");
		goto __lexer_end;
	}
	dbglog("lexedFile->_file_length = %d", lexedFile->_file_length);

	lexedFile->_tokensIndex = 0;

	lexedFile->_tokensArray = NULL;
	lexedFile->_tokensArrayLength = 0;

	do {
		ret = getNextToken(lexedFile);
	} while(ret == SUCCESS);
	
	if(ret != TokenTypeEOF) {
		goto __lexer_end;
	}

	ret = replaceTokensArrayCache(lexedFile);
	if(ret != SUCCESS) {
		errlog("failed to replace tokens cache array. failed with error: %d", ret);
		goto __lexer_end;
	}

__lexer_end:
	if(ret == SUCCESS) {
		dbglog("got to __lexer_end with SUCCESS");
		*pLexedFile = lexedFile;
	}
	else {
		dbglog("got to __lexer_end with errcode %d", ret);
		if(lexedFile && ret != ERRCODE_USAGE) {
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

void freeLexer(Lexer* lexedFile) {
	if(!lexedFile) {
		warlog("lexedFile is NULL");
		goto __freeLexer_end;
	}

	if(lexedFile->_fd) {
		dbglog("closing lexedFile->_fd");
		fclose(lexedFile->_fd);
		lexedFile->_fd = NULL;
	}
	else {
		dbglog("lexedFile->_fd is NULL");
	}

	if(lexedFile->_tokensIndex > 0) {
		warlog("lexedFile->_tokens is not empty!!!");
		for(int i = 0; i < lexedFile->_tokensIndex; i++) {
			if(lexedFile->_tokens[i]) {
				dbglog("freeing: lexedFile->_tokens[%d]: '%s'", i, lexedFile->_tokens[i]->_value);
				freeToken(lexedFile->_tokens[i]);
				lexedFile->_tokens[i] = NULL;
			}
			else {
				errlog("lexedFile->_tokens[%d] is NULL - ERROR");
			}
		}
		lexedFile->_tokensIndex = 0;
	}

	dbglog("freeing lexedFile->_tokensArray contents");
	if(lexedFile->_tokensArray) {
		for(int i = 0; i < lexedFile->_tokensArrayLength; i++) {
			if(lexedFile->_tokensArray[i]) {
				dbglog("freeing: lexedFile->_tokensArray[%d]: '%s'", i, lexedFile->_tokensArray[i]->_value);
				freeToken(lexedFile->_tokensArray[i]);
				lexedFile->_tokensArray[i] = NULL;
			}
			else {
				errlog("lexedFile->_tokensArray[%d] is NULL - ERROR");
			}
		}
	}
	
	dbglog("freeing lexedFile->_tokensArray");
	free(lexedFile->_tokensArray);
	lexedFile->_tokensArray = NULL;

	dbglog("freeing lexedFile");
	free(lexedFile);
	
__freeLexer_end:
	lexedFile = NULL;
}

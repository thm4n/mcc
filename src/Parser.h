#ifndef _PARSER_H_
#define _PARSER_H_

#include "Header.h"
#include "Token.h"
#include "Lexer.h"

#include "AST.h"

#define AST_NODES_ARRAY_SIZE 16

int parseFile(AST** pRoot, Lexer* lexedFile) {
	int ret = SUCCESS;
	AST* root = *pRoot;
	
	if(root) {
		errlog("parser recieved initialized AST root node.");
		ret = ERRCODE_USAGE;
		goto __parseFile_end;
	}

	root = (AST*)malloc(sizeof(AST));
	if(root) {
		errlog("Failed to allocate memory");
		ret = ERRCODE_ALLOC;
		goto __parseFile_end;
	}

	strcpy(root->_file, lexedFile->_filePath);
	root->_statements = NULL;
	root->_statementsArraySize = 0;

	root->_tokens = lexedFile->_tokensArray;
	root->_currToken = 0;
	root->_tokensArraySize = lexedFile->_tokensArrayLength;

	lexedFile->_tokensArray = NULL;
	freeLexer(lexedFile); // should be lated moved to before calling the parseFile function.

	createAST(root);

__parseFile_end:
	if(ret == SUCCESS) {
		dbglog("got to __parseFile_end with SUCCESS");
		*pRoot = root;
	}
	else {
		dbglog("got to __parseFile_end with errcode %d", ret);
		if(root && ret != ERRCODE_USAGE) {
			dbglog("");
		}
	}
	return ret;
}

int createAST(AST* ast) {
	int res = SUCCESS;
	ASTNode* ASTNodesArray[AST_NODES_ARRAY_SIZE] = {0};
	int tokenArrayIndex = 0;

	if(!ast) {
		errlog("ast is NULL");
		return ERRCODE_USAGE;
	}
	
	res = getNextDeclarationStatement(ast, &ASTNodesArray[tokenArrayIndex]);
	
}

ASTNode* createASTNode() {
	ASTNode* astNode = NULL;
	astNode = (ASTNode*)malloc(sizeof(ASTNode));
	if(!astNode) {
		errlog("Failed to create ASTNode");
		return NULL;
	}
	memset(astNode, 0, sizeof(ASTNode));
	return astNode;
}

void freeASTNode(ASTNode* astNode) {
	if(!astNode) return;
	if(astNode->_statements) {
		for(int i = 0; i)
	}
}

int getNextDeclarationStatement(AST* ast, ASTNode** p_astNode) {
	// how does a declaration statement looks like in C?
	// 1. always a type identifier first: void, int , char
	// 2. name of identifier: some symbol name
	// at this point it cant be a variable or a function name, depends on the next token.
	// 3. if its either ; or =
	// 	    its a variable declaration.
	//    if its (
	//	    its a function declaration.

	int res = SUCCESS;
	Token* currToken = NULL;
	ASTNode* astNode = *p_astNode;

	if(!astNode) {
		astNode = createASTNode();
		if(!astNode) {
			res = ERRCODE_ALLOC;
			goto __getNextDeclarationStatement_end;
		}
	}
	else {
		warlog("ast node is not null - something went wrong!");
	}

	currToken = ast->_tokens[ast->_currToken];
	if(!isTypeIdentifier(currToken)) {
		inflog("expected a type identifier, got: %s", currToken->_value);
		return ERRCODE_PARSER;
	}

__getNextDeclarationStatement_end:
	if(res != SUCCESS) {
		if(astNode) {
			freeASTNode(astNode);
		}
	}

/*	
	int res = SUCCESS;
	int symTypeOffset = 0;
	int symNameOffset = 0;
	int symArgsOffset = 0; // holds the offset of the ( of the function arguments or the value of the variable declaration 

	symTypeOffset = ast->_currToken;
	res = getSymbolTypeIdentifier(ast);
	if(res == ERRCODE_PARSER) {
		// dbglog parser error
		return res;
	}
	else if (res != SUCCESS) {
		// dbglog something..
		return res;
	}

	symNameOffset = ast->_currToken;
	res = getSymbolNameIdentifier(ast);
	if(res == ERRCODE_PARSER) {
		// dbglog parser error
		return res;
	}
	else if(res != SUCCESS) {
		// dbglog something..
		return res;
	}

	symArgsOffset = ast->_currToken;
	res = getArgsIdentifiers(ast);
	if(res == ERRCODE_PARSER) {
		// dbglog parser error
		return res;
	}
	else if(res != SUCCESS) {
		// dbglog something..
		return res;
	}
*/


}

int getSymbolTypeIdentifier(AST* ast) {

}

int getSymbolNameIdentifier(AST* ast) {

}

#endif
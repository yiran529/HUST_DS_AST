#ifndef GET_TOKEN_H
#define GET_TOKEN_H

#include<stdio.h>
#include<stdlib.h>

bool is_num(char c);

enum TOKEN_KIND{
    ERROR_TOKEN, 
    IDENT, 
    INT_CONST, 
    FLOAT_CONST, 
    DOUBLE_CONST, 
    CHAR_CONST, 
    LONG_CONST, 
    STRING_CONST,
    INCLUDE, 
    STRUCT, 
    TYPEDEF,
    INT, 
    SHORT,
    FLOAT, 
    DOUBLE, 
    CHAR, 
    LONG, 
    VOID,
    IF, 
    ELSE, 
    EQ, 
    GREATER, 
    LESS, 
    GREATEREQ,// >=
    LESSEQ,// <=
    NOTEQ,
    ASSIGN, 
    SEMI, 
    COMMA, 
    BREAK, 
    CONTINUE, 
    RETURN, 
    FOR, 
    WHILE, 
    DO, 
    AND, 
    OR, 
    PLUS, 
    MINUS, 
    MULTIPLY, 
    DEVIDE, 
    MOD,
    LP, 
    RP,  
    LB, //'['
    RB, //']'
    LC, //'{'
    RC, //'}'
    HASH, //'#'
    DOUBLE_SLASH, // 单行注释的符号
    START_OF_MULTILINE_COMMENT, // namely "/*"
    END_OF_MULTILINE_COMMENT,    // namely "*/"
    COMMA_OR_RP // 要么是逗号要么是右括号，用以处理函数调用中形参的问题
};
//还差两个注释符号

/**
 * 读取*fp_pointer所指向的源文件的下一个单词
 * @param fp_pointer 指向源文件当前读取位置的双重指针
 * @return 识别出的单词的种类码
 */
int get_token(FILE** fp_pointer);

/**
 * 根据给定的单词编号返回对应的单词种类的字符串表示
 * @param kind 单词编号
 * @return 对应的单词种类字符串表示
 */
char* get_token_kind(int kind);

#endif
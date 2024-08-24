#include<string.h>
#include "syntax_analysis.h"

extern char token_text[300];

AST_NODE* root;

AST_NODE** AST;

int cur_kind; // 当前读到的单词的种类编号

/**
 * 判断一个种类编号是不是类型关键字
 * @param kind 将要进行判断的单词种类编号
 * @return 如果是，则返回true；否则返回false
 */
bool is_type_specifier(int kind) { //判断是不是类型关键字
    return kind == INT ||
           kind == SHORT ||
           kind == LONG ||
           kind == CHAR ||
           kind == FLOAT ||
           kind == DOUBLE;
}



/**
 * 根据所给的源文件构建定义序列代表的以cur_root为树根的AST（该源文件已经有一个单词被正确地读取了）
 * @param cur_node 当前所要构建的代表定义序列的AST的树根
 * @param fp_pointer 指向源文件当前读取位置的双重指针
 * @return 如果构建成功，没有错误，则返回true；否则返回false
 */
bool build_ext_def_seq(AST_NODE* &cur_node, FILE** fp_pointer) {
    if(cur_kind == EOF) {
        cur_node = NULL;
        return true;
    }
    cur_node = (AST_NODE*)malloc(sizeof(AST_NODE));
    cur_node-> type = (AST_NODE_TYPE)EXT_DEF_SEQ, cur_node-> first_child = NULL;
    bool ret_val;
    ret_val = build_ext_def_seq(cur_node-> first_child, fp_pointer);
    ret_val = ret_val && build_ext_def_seq(cur_node-> first_child-> next_sibling, fp_pointer);
    return ret_val;
}

/**
 * 以cur_node（引用指针类型）为根构建以表示定义序列的AST。该定义序列的第一个单词已经被正确地读取。
 * @param cur_node AST根的指针的引用
 * @param fp_pointer 文件当前读取位置的双重指针
 * @return 定义序列没有错误，则返回true；否则返回false
 */
bool build_ext_def(AST_NODE* &cur_node, FILE** fp_pointer) {
    cur_node = (AST_NODE*)malloc(sizeof(AST_NODE));
    cur_node-> type = (AST_NODE_TYPE)EXT_DEF;

    if(is_type_specifier(cur_kind)) {
        cur_node-> first_child = (AST_NODE*)malloc(sizeof(AST_NODE));
        cur_node-> first_child-> type = WORD;
        cur_node-> first_child-> word.kind = cur_kind;
        cur_node-> first_child-> word.data = (char*)malloc(sizeof(char) * (strlen(token_text) + 1));
        strcpy(cur_node-> first_child-> word.data, token_text);
        cur_node-> first_child-> first_child = cur_node-> first_child-> next_sibling = NULL;
        return true;
    } else return false;

    cur_kind = get_token(fp_pointer);
    if(cur_kind == IDENT) {
        AST_NODE* second_child = cur_node-> first_child-> next_sibling = (AST_NODE*)malloc(sizeof(AST_NODE));
        second_child-> type = WORD;
        second_child-> word.kind = (TOKEN_KIND)IDENT;
        second_child-> word.data = (char*)malloc(sizeof(char) * (strlen(token_text) + 1));
        strcpy(second_child-> word.data, token_text);
        second_child-> first_child = second_child-> next_sibling = NULL;
        return true;
    } else return false;

}

/**
 * 根据所给的源文件构建代表整个程序的AST
 * @param fp_pointer 指向源文件的双重指针
 * @return 如果构建成功，没有错误，则返回true；否则返回false
 */
bool build_program(FILE** fp_pointer) {
    cur_kind = get_token(fp_pointer);
    if(cur_kind == ERROR_TOKEN || cur_kind == EOF) return false;
    root = (AST_NODE*)malloc(sizeof(AST_NODE));
    *AST = root;
    return build_ext_def_seq(root -> first_child, fp_pointer);
}

int main() {
    char path[1000];
    scanf("%s", path);
    FILE *fp = fopen(path, "r");
    
    return 0;
}
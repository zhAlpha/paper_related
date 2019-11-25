#include <iostream>
#include "lsd.h"
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "../include/lsd.h"

#ifndef FALSE
#define FALSE 0
#endif /* !FALSE */

#ifndef TRUE
#define TRUE 1
#endif /* !TRUE */

/*----------------------------------------------------------------------------*/
/**
 ********************************错误输出**************************************
 * */
static void error (const char * msg)
{
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}

/*----------------------------------------------------------------------------*/
/*---------------------------    命令行接口定义    -----------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
#define FIELD_LENGTH 160
#define HELP_OPTION    "--help"
#define VERSION_OPTION "--version"
/**
 * 能够存储一个参数,并且读取其中的值的结构体
 */
struct argument
{
    char name[FIELD_LENGTH];              //内部标识参数的名称
    char desc[FIELD_LENGTH];              //描述
    char id;                              //字母用"-"连接时可选
    char type;                            //i=int, d=double, s=str, b=bool
    int required;
    int assigned;
    int def_value;                        //true 还是 false,默认的值是否被分配
    char d_value[FIELD_LENGTH];           //默认值
    char s_value[FIELD_LENGTH];           //找到字符串，也就是'str'的值
    int  i_value;
    double f_value;
    int    min_set;                       //true 还是 false,是最小的数集吗
    double min;
    int    max_set;                       //true 还是 false,是最大的数集吗
    double max;
};

/**
 * 能够存储多个参数,并且读取其中的值的结构体
 */

struct arguments
{
    char name[FIELD_LENGTH];
    char author[FIELD_LENGTH];
    char version[FIELD_LENGTH];
    char desc[FIELD_LENGTH];
    char compiled[FIELD_LENGTH];
    char year[FIELD_LENGTH];
    int arg_num;
    int arg_allocated;
    struct argument* args;
};


/**
 * 释放 arguments 结构体内存；
 */

static void free_arguments(struct arguments* arg)
{
    if (arg == NULL || arg->args == NULL)
        error("Error: NULL pointer at 'free_arguments'.");
    free((void *) arg->args);
    free((void *) arg);
}
/**
 * 允许字段中出现 数字 , 字母 , 以及 "_"
 */
static int is_id_char (int c)
{
    return c== '_' || isalpha(c) || isdigit(c) ;
}
/**
 * 读取下一个字段的参数定义
 */
static char* get_next_filed(char * p , char *id , char *value)
{
    int n;

    if (p == NULL || id  == NULL || value == NULL )        //检测输入是否正确
        error("Error: invalid input to 'get_next_field'.");

    while ( isspace(*p) ) ++p;
    if (*p != '#')
        error("Error： missing '#' in 'use description'.");

}






int main(int argc, char ** argv)
{
    std::cout <<  argc  << std::endl;
    std::cout << argv[0]<< std::endl;
    std::cout << argv[1]<< std::endl;
    std::cout << *argv[0]<< std::endl;
    std::cout << *argv[1]<< std::endl;
   if (is_id_char ( *argv[1]))
       std::cout << "输入是字母，数字 或 “_” ."<< std::endl;
   else
       std::cout << "输入不是是字母，数字 或 “_” ."<< std::endl;

    return EXIT_SUCCESS;
}
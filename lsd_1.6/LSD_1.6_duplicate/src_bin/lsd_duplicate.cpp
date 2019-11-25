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

int main(int argc, char ** argv)
{

    error("错误");

    return EXIT_SUCCESS;
}

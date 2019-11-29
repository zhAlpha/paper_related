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

    if (p == NULL || id  == NULL || value == NULL )               //检测输入是否正确
        error("Error: invalid input to 'get_next_field'.");

    while ( isspace(*p) ) ++p;                                    //跳过空格
    if (*p != '#')                                                //检测开头是否是#,并跳过
        error("Error： missing '#' in 'use description'.");
    ++p;
    for ( n=0; is_id_char(*p)&& n < FIELD_LENGTH; n++ )
    {
        id[n] = *(p++);                                           //
    }

}

static int get_num(FILE * f)
{
    int num,c;

    while(isspace(c=getc(f)));
    if(!isdigit(c)) error("Error: corrupted PGM file.");
    num = c - '0';
    while( isdigit(c=getc(f)) ) num = 10 * num + c - '0';
    if( c != EOF && ungetc(c,f) == EOF )
        error("Error: unable to 'ungetc' while reading PGM file.");

    return num;
}

static void skip_whites_and_comments(FILE * f)
{
    int c;
    do
    {
        while(isspace(c=getc(f))); /* skip spaces */
        if(c=='#') /* skip comments */
            while( c!='\n' && c!='\r' && c!=EOF )
                c=getc(f);
    }
    while( c == '#' || isspace(c) );
    if( c != EOF && ungetc(c,f) == EOF )
        error("Error: unable to 'ungetc' while reading PGM file.");
}

static double * read_pgm_image_double(int * X, int * Y, char * name)
{
    FILE * f;
    int c,bin;
    int xsize,ysize,depth,x,y;
    double * image;

    /* open file */
    if( strcmp(name,"-") == 0 ) f = stdin;
    else f = fopen(name,"rb");                                       //用给定的模式打开文件 模式"rb"  rb 读打开一个二进制文件，只允许读数据。
    if( f == NULL ) error("Error: unable to open input image file.");

    /* read header */
    if( getc(f) != 'P' ) error("Error: not a PGM file!");              //getc(FILE *stream)//从文件读取字符
    if( (c=getc(f)) == '2' ) bin = FALSE;
    else if( c == '5' ) bin = TRUE;
    else error("Error: not a PGM file!");
    skip_whites_and_comments(f);
    xsize = get_num(f);            /* X size */
    if(xsize<=0) error("Error: X size <=0, invalid PGM file\n");
    skip_whites_and_comments(f);
    ysize = get_num(f);            /* Y size */
    if(ysize<=0) error("Error: Y size <=0, invalid PGM file\n");
    skip_whites_and_comments(f);
    depth = get_num(f);            /* depth */
    if(depth<=0) fprintf(stderr,"Warning: depth<=0, probably invalid PGM file\n");
    /* white before data */
    if(!isspace(c=getc(f))) error("Error: corrupted PGM file.");

    /* get memory */
    image = (double *) calloc( (size_t) (xsize*ysize), sizeof(double) );
    if( image == NULL ) error("Error: not enough memory.");

    /* read data */
    for(y=0;y<ysize;y++)
        for(x=0;x<xsize;x++)
            image[ x + y * xsize ] = bin ? (double) getc(f)
                                         : (double) get_num(f);

    /* close file if needed */
    if( f != stdin && fclose(f) == EOF )
        error("Error: unable to close file while reading PGM file.");

    /* return image */
    *X = xsize;
    *Y = ysize;
    return image;
}





int main(int argc, char ** argv)
{

    FILE * f;
    int c,bin;
    int xsize,ysize,depth,x,y;
    double * image;

    /* open file */
    if( strcmp(argv[1],"-") == 0 ) f = stdin;
    else f = fopen(argv[1],"rb");                                       //用给定的模式打开文件 模式"rb"  rb 读打开一个二进制文件，只允许读数据。
    if( f == NULL ) error("Error: unable to open input image file.");



    return EXIT_SUCCESS;
}
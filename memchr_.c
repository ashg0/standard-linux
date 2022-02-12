#include        <stdio.h>
#include        <string.h>

int main(void)
{
        char str[] = "abchdef\0ghij";    /* 途中に空文字のある文字列 */
        char *p;
        
        p = memchr(str, 'h', 13);
        printf("検索文字は文字列の%d番目\n",p - str);
        
        return 0;
}

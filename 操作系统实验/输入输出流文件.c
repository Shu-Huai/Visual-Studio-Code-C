#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    char s[1024];
    FILE *filePointer = fopen(argv[1], "r");
    if (filePointer)
    {
        while (fgets(s, 1024, filePointer))
        {
            printf("%s", s);
        }
    }
    else
    {
        perror("文件错误");
        return 1;
    }
    return 0;
}
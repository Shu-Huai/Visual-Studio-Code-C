#include <stdio.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
int main(int argc, char *argv[])
{
    struct stat node;
    printf("文件：%s。\n", argv[1]);
    if (lstat(argv[1], &node) < 0)
    {
        perror("文件错误");
        return 1;
    }
    printf("设备驱动器号：%d。\n", major(node.st_dev));
    printf("设备号：%d。\n", minor(node.st_dev));
    if (S_ISCHR(node.st_mode) || S_ISBLK(node.st_mode))
    {
        printf("(%s)rdev = %d/%d。\n", S_ISCHR(node.st_mode) ? "字符设备" : "块设备", major(node.st_rdev), minor(node.st_rdev));
    }
    return 0;
}
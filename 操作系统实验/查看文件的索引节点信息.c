#include <stdio.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
char *DealTime(time_t tm, char *stringTime)
{
    struct tm *local = localtime(&tm);
    strftime(stringTime, 50, "%c", local);
    return stringTime;
}
int ShowFileInfo(char *fileName)
{
    struct stat node;
    if (lstat(fileName, &node))
    {
        perror("文件错误");
        return 1;
    }
    printf("文件名：%s。\n", fileName);
    printf("设备驱动器号：%d。\n", major(node.st_dev));
    printf("设备号：%d。\n", minor(node.st_dev));
    printf("索引节点号：%ld。\n", node.st_ino);
    printf("大小：%ld字节。\n", node.st_size);
    printf("类型：%07o。\n", node.st_mode & S_IFMT);
    printf("权限：%07o。\n", node.st_mode & 0777);
    printf("所有者：%d。\n", node.st_uid);
    printf("所有者组：%d。\n", node.st_gid);
    printf("硬链接数：%ld。\n", node.st_nlink);
    char time[50] = {0};
    printf("创建时间：%s。\n", DealTime(node.st_ctime, time));
    printf("最后访问时间：%s。\n", DealTime(node.st_atime, time));
    printf("最后修改时间：%s。\n", DealTime(node.st_mtime, time));
    printf("最后状态改变时间：%s。\n", DealTime(node.st_ctime, time));
    return 0;
}
int main(int argc, char *argv[])
{
    int result = ShowFileInfo(argv[0]);
    printf("\n");
    return result;
}
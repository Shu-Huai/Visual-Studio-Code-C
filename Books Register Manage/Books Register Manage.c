#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Book
{
    char *name_;
    char *author_;
    char *publisher_;
    char *ISBN_;
    struct Book *next_;
} Book;
Book *InitializeBooks(Book *books)
{
    books = (Book *)malloc(sizeof(Book));
    books->name_ = NULL;
    books->author_ = NULL;
    books->publisher_ = NULL;
    books->ISBN_ = NULL;
    books->next_ = NULL;
    return books;
}
void InsertBook(Book *books, char *name, char *author, char *publisher, char *ISBN)
{
    Book *newBook = (Book *)malloc(sizeof(Book));
    newBook->name_ = (char *)malloc(strlen(name) * sizeof(char));
    strcpy(newBook->name_, name);
    newBook->author_ = (char *)malloc(strlen(author) * sizeof(char));
    strcpy(newBook->author_, author);
    newBook->publisher_ = (char *)malloc(strlen(publisher) * sizeof(char));
    strcpy(newBook->publisher_, publisher);
    newBook->ISBN_ = (char *)malloc(strlen(ISBN) * sizeof(char));
    strcpy(newBook->ISBN_, ISBN);
    newBook->next_ = books->next_;
    books->next_ = newBook;
}
void ReadFromFile(Book *books, char *path)
{
    FILE *file = fopen(path, "r");
    if (!file)
    {
        printf("文件不存在。\n");
        return;
    }
    _Bool isEnd = 0;
    while (!isEnd)
    {
        char bookName[100] = {0};
        char bookAuthor[100] = {0};
        char bookPublisher[100] = {0};
        char bookISBN[14] = {0};
        fscanf(file, "%s%s%s%s", bookName, bookAuthor, bookPublisher, bookISBN);
        if (bookName[0] == 0)
        {
            isEnd = 1;
            break;
        }
        InsertBook(books, bookName, bookAuthor, bookPublisher, bookISBN);
    }
    fclose(file);
}
char *DeleteBook(Book *books, char *ISBN)
{
    Book *p = books;
    while (p && strcmp(p->next_->ISBN_, ISBN))
    {
        p = p->next_;
    }
    if (!p)
    {
        return "查无此书。";
    }
    Book *q = p->next_;
    p->next_ = q->next_;
    free(q);
    return "成功。";
}
char *SetBookName(Book *books, char *ISBN, char *name)
{
    Book *p = books->next_;
    while (p && strcmp(p->ISBN_, ISBN))
    {
        p = p->next_;
    }
    if (!p)
    {
        return "查无此书。";
    }
    strcpy(p->name_, name);
    return "成功。";
}
char *SetBookAuthor(Book *books, char *ISBN, char *author)
{
    Book *p = books->next_;
    while (p && strcmp(p->ISBN_, ISBN))
    {
        p = p->next_;
    }
    if (!p)
    {
        return "查无此书。";
    }
    strcpy(p->author_, author);
    return "成功。";
}
char *SetBookPublisher(Book *books, char *ISBN, char *publisher)
{
    Book *p = books->next_;
    while (p && strcmp(p->ISBN_, ISBN))
    {
        p = p->next_;
    }
    if (!p)
    {
        return "查无此书。";
    }
    strcpy(p->publisher_, publisher);
    return "成功。";
}
char *GetBookName(Book *books, char *ISBN)
{
    Book *p = books->next_;
    while (p && strcmp(p->ISBN_, ISBN))
    {
        p = p->next_;
    }
    return p ? p->name_ : "查无此书";
}
char *GetBookAuthor(Book *books, char *ISBN)
{
    Book *p = books->next_;
    while (p && strcmp(p->ISBN_, ISBN))
    {
        p = p->next_;
    }
    return p ? p->author_ : "查无此书";
}
char *GetBookPublisher(Book *books, char *ISBN)
{
    Book *p = books->next_;
    while (p && strcmp(p->ISBN_, ISBN))
    {
        p = p->next_;
    }
    return p ? p->publisher_ : "查无此书";
}
int main()
{
    Book *books = NULL;
    books = InitializeBooks(books);
    ReadFromFile(books, "Books.txt");
    char functionSelect = 0;
    char bookName[100] = {0};
    char bookAuthor[100] = {0};
    char bookPublisher[100] = {0};
    char bookISBN[14] = {0};
    while (functionSelect != '0')
    {
        printf("1. 录入图书信息。\n2. 显示图书名字。\n3. 显示图书作者。\n4. 显示图书出版社。\n5. 修改图书名字。\n6. 修改图书作者。\n7. 修改图书出版社。\n8. 删除图书。\n0. 保存并退出。");
        printf("选择功能（0~8）：");
        scanf("%c", &functionSelect);
        switch (functionSelect)
        {
        case '1':
            printf("输入图书名字：");
            scanf("%s", bookName);
            printf("输入图书作者：");
            scanf("%s", bookAuthor);
            printf("输入图书出版社：");
            scanf("%s", bookPublisher);
            printf("输入图书编号：");
            scanf("%s", bookISBN);
            InsertBook(books, bookName, bookAuthor, bookPublisher, bookISBN);
            printf("成功。\n");
            break;
        case '2':
            printf("输入图书编号：");
            scanf("%s", bookISBN);
            printf("图书名字是：%s。\n", GetBookName(books, bookISBN));
        case '3':
            printf("输入图书编号：");
            scanf("%s", bookISBN);
            printf("图书作者是：%s。\n", GetBookAuthor(books, bookISBN));
        case '4':
            printf("输入图书编号：");
            scanf("%s", bookISBN);
            printf("图书出版社是：%s。\n", GetBookPublisher(books, bookISBN));
        }
    }
    return 0;
}
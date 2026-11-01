
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree
{
    char key[100];
    int count;
    struct Tree *left;
    struct Tree *right;
} Tree;

typedef struct
{
    char author[100];
    char title[100];
    char publisher[100];
    int year;
} Book;

Tree* insert(Tree *root, char key[])
{
    if (root == NULL)
    {
        root = (Tree*)malloc(sizeof(Tree));
        strcpy(root->key, key);
        root->count = 1;
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    int cmp = strcmp(key, root->key);

    if (cmp == 0)
        root->count++;
    else if (cmp < 0)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

int search(Tree *root, char key[])
{
    if (root == NULL)
        return 0;

    int cmp = strcmp(key, root->key);

    if (cmp == 0)
        return root->count;
    else if (cmp < 0)
        return search(root->left, key);
    else
        return search(root->right, key);
}

void printTree(Tree *root)
{
    if (root != NULL)
    {
        printTree(root->left);
        printf("%s -> %d\n", root->key, root->count);
        printTree(root->right);
    }
}

int main()
{
    Tree *authors = NULL;
    Tree *publishers = NULL;
    Tree *years = NULL;

    Book books[] =
    {
        {"Шевченко", "Кобзар", "Освіта", 2020},
        {"Франко", "Захар Беркут", "Освіта", 2018},
        {"Шевченко", "Гайдамаки", "Світ", 2020},
        {"Костенко", "Маруся Чурай", "Світ", 2021},
        {"Франко", "Лис Микита", "Освіта", 2018},
        {"Стус", "Палімпсести", "Фоліо", 2022},
        {"Коцюбинський", "Тіні забутих предків", "Фоліо", 2021},
        {"Костенко", "Берестечко", "Світ", 2021}
    };

    int n = sizeof(books) / sizeof(books[0]);

    for (int i = 0; i < n; i++)
    {
        authors = insert(authors, books[i].author);
        publishers = insert(publishers, books[i].publisher);

        char year[20];
        sprintf(year, "%d", books[i].year);

        years = insert(years, year);
    }

    int choice;
    char key[100];

    do
    {
        printf("\nМЕНЮ \n");
        printf("1 - Частотний словник авторів\n");
        printf("2 - Частотний словник видавництв\n");
        printf("3 - Частотний словник років видання\n");
        printf("4 - Знайти кількість книг автора\n");
        printf("5 - Знайти кількість книг видавництва\n");
        printf("6 - Знайти кількість книг за роком видання\n");
        printf("0 - Вихід\n");
        printf("Ваш вибір: ");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                printf("\nЧастотний словник авторів:\n");
                printTree(authors);
                break;

            case 2:
                printf("\nЧастотний словник видавництв:\n");
                printTree(publishers);
                break;

            case 3:
                printf("\nЧастотний словник років видання:\n");
                printTree(years);
                break;

            case 4:
                printf("Введіть автора: ");
                fgets(key, 100, stdin);
                key[strcspn(key, "\n")] = 0;
                printf("Кількість книг: %d\n", search(authors, key));
                break;

            case 5:
                printf("Введіть видавництво: ");
                fgets(key, 100, stdin);
                key[strcspn(key, "\n")] = 0;
                printf("Кількість книг: %d\n", search(publishers, key));
                break;

            case 6:
                printf("Введіть рік видання: ");
                fgets(key, 100, stdin);
                key[strcspn(key, "\n")] = 0;
                printf("Кількість книг: %d\n", search(years, key));
                break;

            case 0:
                printf("Роботу завершено.\n");
                break;

            default:
                printf("Невірний вибір.\n");
        }

    } while (choice != 0);

    return 0;
}
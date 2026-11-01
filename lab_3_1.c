#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

struct Taxi
{
    int number;
    char brand[50];
    char driver[50];
    struct Taxi *next;
};

struct Taxi *hashTable[SIZE];

int hashFunction(int number)
{
    return number % SIZE;
}

void initTable()
{
    for(int i = 0; i < SIZE; i++)
        hashTable[i] = NULL;
}

void insertTaxi(int number, char brand[], char driver[])
{
    int index = hashFunction(number);

    struct Taxi *newTaxi = malloc(sizeof(struct Taxi));

    newTaxi->number = number;
    strcpy(newTaxi->brand, brand);
    strcpy(newTaxi->driver, driver);

    newTaxi->next = hashTable[index];
    hashTable[index] = newTaxi;
}

void deleteTaxi(int number)
{
    int index = hashFunction(number);

    struct Taxi *temp = hashTable[index];
    struct Taxi *prev = NULL;

    while(temp != NULL)
    {
        if(temp->number == number)
        {
            if(prev == NULL)
                hashTable[index] = temp->next;
            else
                prev->next = temp->next;

            free(temp);

            printf("Машину видалено.\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("Машину не знайдено.\n");
}

void printTable()
{
    printf("\nПоточний стан хеш-таблиці:\n");

    for(int i = 0; i < SIZE; i++)
    {
        printf("[%d] -> ", i);

        struct Taxi *temp = hashTable[i];

        while(temp != NULL)
        {
            printf("(№%d, %s, %s) -> ",
                   temp->number,
                   temp->brand,
                   temp->driver);

            temp = temp->next;
        }

        printf("NULL\n");
    }
}

void restructure()
{
    struct Taxi *oldTable[SIZE];

    for(int i = 0; i < SIZE; i++)
        oldTable[i] = hashTable[i];

    initTable();

    for(int i = 0; i < SIZE; i++)
    {
        struct Taxi *temp = oldTable[i];

        while(temp != NULL)
        {
            insertTaxi(temp->number,
                       temp->brand,
                       temp->driver);

            struct Taxi *del = temp;
            temp = temp->next;
            free(del);
        }
    }

    printf("Реструктуризацію виконано.\n");
}

int main()
{
    initTable();

    int choice;
    int number;
    char brand[50];
    char driver[50];

    do
    {
        printf("\n МЕНЮ \n");
        printf("1. Додати машину\n");
        printf("2. Видалити машину\n");
        printf("3. Вивести таблицю\n");
        printf("4. Реструктуризація\n");
        printf("0. Вихід\n");
        printf("Ваш вибір: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Номер машини: ");
                scanf("%d", &number);

                printf("Марка: ");
                scanf("%s", brand);

                printf("Прізвище водія: ");
                scanf("%s", driver);

                insertTaxi(number, brand, driver);
                break;

            case 2:
                printf("Введіть номер машини: ");
                scanf("%d", &number);

                deleteTaxi(number);
                break;

            case 3:
                printTable();
                break;

            case 4:
                restructure();
                break;

            case 0:
                printf("Завершення роботи.\n");
                break;

            default:
                printf("Невірний вибір.\n");
        }

    } while(choice != 0);

    return 0;
}
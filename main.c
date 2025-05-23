#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_PERSONS 10
#define NAME_LEN 20
#define FILE_NAME "text.txt"

typedef struct {
    char name[NAME_LEN];
    int  age;
    int  id;
} Person;

static int loadPersons(Person *persons) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) return 0;

    int count = 0;
    while (count < MAX_PERSONS &&
           fscanf(file, "%19s %d %d",
                  persons[count].name,
                  &persons[count].age,
                  &persons[count].id) == 3) {
        ++count;
    }
    fclose(file);
    return count;
}

static void savePersons(const Person *persons, int count) {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) return;

    for (int i = 0; i < count; ++i)
        fprintf(file, "%s %d %d\n",
                persons[i].name,
                persons[i].age,
                persons[i].id);

    fclose(file);
}

static void addPerson(Person *persons, int *count) {
    if (*count >= MAX_PERSONS) {
        puts("Brak miejsca na nowa osobe.");
        return;
    }
    printf("Podaj imie osoby: ");
    scanf("%19s", persons[*count].name);
    printf("Podaj wiek osoby: ");
    scanf("%d", &persons[*count].age);
    printf("Podaj id osoby: ");
    scanf("%d", &persons[*count].id);
    ++(*count);
}

static void showPersons(const Person *persons, int count) {
    for (int i = 0; i < count; ++i)
        printf("OSOBA %d\n%s %d lat ID:%d\n\n",
               i + 1,
               persons[i].name,
               persons[i].age,
               persons[i].id);
}

static void deletePerson(Person *persons, int *count, int id) {
    for (int i = 0; i < *count; ++i) {
        if (persons[i].id == id) {
            for (int j = i; j < *count - 1; ++j)
                persons[j] = persons[j + 1];
            --(*count);
            return;
        }
    }
    puts("Nie znaleziono osoby o podanym id.");
}

static void findPersonById(const Person *persons, int count, int id) {
    for (int i = 0; i < count; ++i) {
        if (persons[i].id == id) {
            printf("Znaleziono:\n%s %d lat ID:%d\n",
                   persons[i].name,
                   persons[i].age,
                   persons[i].id);
            return;
        }
    }
    puts("Nie znaleziono osoby o podanym id.");
}

int main(void) {
    Person persons[MAX_PERSONS];
    int count  = loadPersons(persons);
    int choice = 0;

    do {
        puts("--------------");
        puts("1. Pokaz uczniow");
        puts("2. Dodaj ucznia");
        puts("3. Usun ucznia");
        puts("4. Znajdz ucznia po ID");
        puts("5. Wyjdz");
        puts("--------------");
        printf("Wybierz: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showPersons(persons, count);
                break;
            case 2:
                addPerson(persons, &count);
                break;
            case 3: {
                int id;
                printf("Podaj id do usuniecia: ");
                scanf("%d", &id);
                deletePerson(persons, &count, id);
                break;
            }
            case 4: {
                int id;
                printf("Podaj id do wyszukania: ");
                scanf("%d", &id);
                findPersonById(persons, count, id);
                break;
            }
            case 5:
                puts("PROGRAM ZAKONCZONY");
                break;
            default:
                puts("Niepoprawny wybor.");
        }
        savePersons(persons, count);
    } while (choice != 5);

    return 0;
}
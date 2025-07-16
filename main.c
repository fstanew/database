#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERSONS 10
#define NAME_LEN 20
#define FILE_NAME "text.txt"

typedef struct {
    char name[NAME_LEN];
    int age;
    int id;
} Person;

static int loadPersons(Person *persons) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) return 0;

    int count = 0;
    while (count < MAX_PERSONS &&
           fscanf(file, "%19s %d %d", persons[count].name, &persons[count].age, &persons[count].id) == 3) {
        ++count;
    }
    fclose(file);
    return count;
}

static void savePersons(const Person *persons, int count) {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) return;

    for (int i = 0; i < count; ++i) {
        fprintf(file, "%s %d %d\n", persons[i].name, persons[i].age, persons[i].id);
    }

    fclose(file);
}

static void addPerson(Person *persons, int *count) {
    if (*count >= MAX_PERSONS) {
        printf("Brak miejsca na dodanie nowej osoby.\n");
        return;
    }

    printf("Imie: ");
    scanf("%19s", persons[*count].name);

    printf("Wiek: ");
    scanf("%d", &persons[*count].age);

    printf("ID: ");
    scanf("%d", &persons[*count].id);

    ++(*count);
    printf("Dodano osobe.\n");
}

static void showPersons(const Person *persons, int count) {
    if (count == 0) {
        printf("Brak zapisanych osob.\n");
        return;
    }

    printf("Lista osob:\n");
    for (int i = 0; i < count; ++i) {
        printf("[%d] %s, %d lat, ID: %d\n", i + 1, persons[i].name, persons[i].age, persons[i].id);
    }
}

static void deletePerson(Person *persons, int *count, int id) {
    for (int i = 0; i < *count; ++i) {
        if (persons[i].id == id) {
            for (int j = i; j < *count - 1; ++j) {
                persons[j] = persons[j + 1];
            }
            --(*count);
            printf("Usunieto osobe o ID: %d\n", id);
            return;
        }
    }
    printf("Nie znaleziono osoby o ID: %d\n", id);
}

static void findPersonById(const Person *persons, int count, int id) {
    for (int i = 0; i < count; ++i) {
        if (persons[i].id == id) {
            printf("Znaleziono: %s, %d lat, ID: %d\n", persons[i].name, persons[i].age, persons[i].id);
            return;
        }
    }
    printf("Nie znaleziono osoby o ID: %d\n", id);
}

static void editPersonById(Person *persons, int count, int id) {
    for (int i = 0; i < count; ++i) {
        if (persons[i].id == id) {
            printf("Nowe imie: ");
            scanf("%19s", persons[i].name);

            printf("Nowy wiek: ");
            scanf("%d", &persons[i].age);

            printf("Nowe ID: ");
            scanf("%d", &persons[i].id);

            printf("Dane zostaly zaktualizowane.\n");
            return;
        }
    }
    printf("Nie znaleziono osoby o ID: %d\n", id);
}

static void showMenu(void) {
    printf("\n--- MENU ---\n");
    printf("1. Wyswietl osoby\n");
    printf("2. Dodaj osobe\n");
    printf("3. Usun osobe\n");
    printf("4. Znajdz osobe po ID\n");
    printf("5. Edytuj osobe\n");
    printf("6. Zakoncz program\n");
    printf("Wybor: ");
}

int main(void) {
    Person persons[MAX_PERSONS];
    int count = loadPersons(persons);
    int choice = 0;

    while (1) {
        showMenu();
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
                printf("ID osoby do usuniecia: ");
                scanf("%d", &id);
                deletePerson(persons, &count, id);
                break;
            }
            case 4: {
                int id;
                printf("ID osoby do wyszukania: ");
                scanf("%d", &id);
                findPersonById(persons, count, id);
                break;
            }
            case 5: {
                int id;
                printf("ID osoby do edycji: ");
                scanf("%d", &id);
                editPersonById(persons, count, id);
                break;
            }
            case 6:
                printf("Program zakonczony.\n");
                savePersons(persons, count);
                return 0;
            default:
                printf("Niepoprawna opcja.\n");
        }

        savePersons(persons, count);
    }
}

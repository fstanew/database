#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

	char name[20];
	int age;
	int id;;

}osoba;

int loadPersons(osoba* osoby) {
	int count = 0;
	FILE* file = fopen("text.txt", "r");
	if (!file) return 0;

	while ((fscanf(file, "%s %d %d", osoby[count].name, &osoby[count].age, &osoby[count].id) == 3))
	{
		count++;
	}

	fclose(file);

	return count;

}

void savePersons(osoba osoby[], int licznik)
{
	FILE* file = fopen("text.txt", "w");

	for (int i = 0; i < licznik; i++)
	{
		fprintf(file, "%s %d %d\n", osoby[i].name, osoby[i].age, osoby[i].id);

	}
	fclose(file);


}

void addPerson(osoba osoby[], int* ptr) {
	printf("Podaj imie osoby: ");
	scanf("%s", osoby[*ptr].name);
	printf("Podaj wiek osoby: ");
	scanf("%d", &osoby[*ptr].age);
	printf("Podaj id osoby: ");
	scanf("%d", &osoby[*ptr].id);
	*ptr += 1;


}



void showPersons(osoba osoby[], int* ptr)
{
	for (int i = 0; i < *ptr; i++)
	{
		printf("OSOBA %d\n", i + 1);
		printf("%s ", osoby[i].name);
		printf("%d lat", osoby[i].age);
		printf("ID:%d ", osoby[i].id);
		printf("\n");
		printf("\n");
	}


}

void deletePerson(osoba osoby[], int id, int* ptr)
{
	for (int i = 0; i < *ptr; i++)
	{
		if (osoby[i].id == id)
		{
			for (int j = i; i < *ptr; i++)
			{
				osoby[j] = osoby[j + 1];
			}
		}

	}
	*ptr -= 1;
}




int main()
{
	osoba osoby[10];
	int licznik = loadPersons(osoby);
	int id = 0;

	int choice = 0;
	do {
		printf("--------------\n");
		printf("1.Pokaz uczniow\n");
		printf("2.Dodaj ucznia\n");
		printf("3.Usun ucznia\n");
		printf("4.Wyjdz\n");
		printf("--------------\n");
		printf("Wybierz:");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:showPersons(osoby, &licznik);
			break;
		case 2:addPerson(osoby, &licznik);
			break;
		case 3:

			printf("\nKogo chcesz usunac: ");
			scanf("%d", &id);
			deletePerson(osoby, id, &licznik);
			break;

		case 4:
			printf("PROGRAM ZAKONCZONY");
			break;
		case 7:
			system("cls"); break;
		}
		savePersons(osoby, licznik);






	} while (choice != 4);

}
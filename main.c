#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char CarBrand[50];
    char OwnerSurname[50];
    char SerialNumber[10];
    int YearOfManufacture;
} Cars;

int readDataFromFile(char* filename, Cars** cars, int* numCars) {
    // Відкриття файлу для читання
    FILE* inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("Помилка відкриття файлу %s\n", filename);
        return 0;
    }

  
    fscanf(inputFile, "%d", numCars);

   
    *cars = (Cars*)malloc(*numCars * sizeof(Cars));
    if (*cars == NULL) {
        printf("Помилка виділення пам'яті\n");
        fclose(inputFile);
        return 1;
    }

    
    for (int i = 0; i < *numCars; i++) {
        fscanf(inputFile, "%s %s %s %d", (*cars)[i].CarBrand, (*cars)[i].OwnerSurname, (*cars)[i].SerialNumber, &(*cars)[i].YearOfManufacture);
    }

    fclose(inputFile);
    return 0;
}


void printCarsWithDigits19(Cars* cars, int numCars) {
    int flag = 0;
    printf("Автомобілі з номерами, що містять цифри 1 і 9:\n");
    for (int i = 0; i < numCars; i++) {
        char* digit = strpbrk(cars[i].SerialNumber, "19");
        if (digit != NULL) {
            printf("Марка: %s, Власник: %s, Номер: %s, Рік випуску: %d\n",
                cars[i].CarBrand,
                cars[i].OwnerSurname,
                cars[i].SerialNumber,
                cars[i].YearOfManufacture);
            flag = 1;
        }
    }

    if (!flag) {
        printf("Не знайдено автомобілів з номерами, що містять цифри 1 і 9.\n");
    }
}

void printCarInfo(const Cars* car) {
    printf("Марка: %s, Власник: %s, Номер: %s, Рік випуску: %d\n",
        car->CarBrand,
        car->OwnerSurname,
        car->SerialNumber,
        car->YearOfManufacture);
}


void searchByOwnerSurname(Cars* cars, int numCars, char* ownerSurname) {
    int flag = 0;
    printf("Результати пошуку за прізвищем власника '%s':\n", ownerSurname);
    for (int i = 0; i < numCars; i++) {
        if (strcmp(cars[i].OwnerSurname, ownerSurname) == 0) {
            // Виведення інформації про автомобіль
            printCarInfo(&cars[i]);
            flag = 1;
        }
    }

    if (!flag) {
        printf("Автомобілі з власником '%s' не знайдено.\n", ownerSurname);
    }
}

void searchBySerialNumber(Cars* cars, int numCars, char* serialNumber) {
    int flag = 0;
    printf("Результати пошуку за номером автомобіля '%s':\n", serialNumber);
    for (int i = 0; i < numCars; i++) {
        if (strcmp(cars[i].SerialNumber, serialNumber) == 0) {
            printCarInfo(&cars[i]);
            flag = 1;
        }
    }

    if (!flag) {
        printf("Автомобіль з номером '%s' не знайдено.\n", serialNumber);
    }
}

void searchByCarBrand(Cars* cars, int numCars, char* carBrand) {
    int flag = 0;
    printf("Результати пошуку за маркою автомобіля '%s':\n", carBrand);
    for (int i = 0; i < numCars; i++) {
        if (strcmp(cars[i].CarBrand, carBrand) == 0) {
            printCarInfo(&cars[i]);
            flag = 1;
        }
    }

    if (!flag) {
        printf("Автомобілі марки '%s' не знайдено.\n", carBrand);
    }
}

void searchByYearOfManufacture(Cars* cars, int numCars, int yearOfManufacture) {
    int flag = 0;
    printf("Результати пошуку за роком випуску '%d':\n", yearOfManufacture);
    for (int i = 0; i < numCars; i++) {
        if (cars[i].YearOfManufacture == yearOfManufacture) {
            printCarInfo(&cars[i]);
            flag = 1;
        }
    }

    if (!flag) {
        printf("Автомобілі року випуску '%d' не знайдено.\n", yearOfManufacture);
    }
}

int main() {
    int numCars;
    Cars* cars;

    if (readDataFromFile("input.txt", &cars, &numCars) == 1) {
        return 1;
    }
    
    printCarsWithDigits19(cars, numCars);
    
    printf("\n----------------------------\n\n");

    printf("Оберіть критерій пошуку:\n");
    printf("1. Прізвище власника\n");
    printf("2. Номер автомобіля\n");
    printf("3. Марка автомобіля\n");
    printf("4. Рік випуску автомобіля\n");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        char ownerSurname[50];
        printf("Введіть прізвище власника: ");
        scanf("%s", ownerSurname);
        searchByOwnerSurname(cars, numCars, ownerSurname);
        break;
    }
    case 2: {
        char serialNumber[10];
        printf("Введіть номер автомобіля: ");
        scanf("%s", serialNumber);
        searchBySerialNumber(cars, numCars, serialNumber);
        break;
    }
    case 3: {
        char carBrand[50];
        printf("Введіть марку автомобіля: ");
        scanf("%s", carBrand);
        searchByCarBrand(cars, numCars, carBrand);
        break;
    }
    case 4: {
        int yearOfManufacture;
        printf("Введіть рік випуску автомобіля: ");
        scanf("%d", &yearOfManufacture);
        searchByYearOfManufacture(cars, numCars, yearOfManufacture);
        break;
    }
    default:
        printf("Неправильний вибір.\n");
        break;
    }

    free(cars);

    return 0;
}

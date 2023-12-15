#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_STRING_LENGTH 100
#define MAX_OPERATIONS 100

// structure for data
typedef struct {
    char county[MAX_STRING_LENGTH];
    char state[MAX_STRING_LENGTH];
    // education
    float education_bachelors_or_higher;
    float education_high_school_or_higher;
    // ethnicities fields
    float ethnicities_american_indian_and_alaska_native_alone;
    float ethnicities_asian_alone;
    float ethnicities_black_alone;
    float ethnicities_hispanic_or_latino;
    float ethnicities_native_hawaiian_and_other_pacific_islander_alone;
    float ethnicities_two_or_more_races;
    float ethnicities_white_alone;
    float ethnicities_white_alone_not_hispanic_or_latino;
    // income fields
    int income_median_household_income;
    int income_per_capita_income;
    float income_persons_below_poverty_level;
    // population field
    int population_2014_population;
} County;

// structure for operations
typedef struct {
    char operationType[MAX_STRING_LENGTH];
    char parameters[MAX_STRING_LENGTH];
} Operation;

void removeQuotes(char *str) {
    size_t len = strlen(str);
    if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
        memmove(str, str + 1, len - 2); // shifts string one char to the left
        str[len - 2] = '\0'; // add null terminator
    }
}

// read the demographics file and store data
int readDemographicsFile(char *filename, County **counties, int *countyCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int lineCount = 0;

    // count number of lines
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        lineCount++;
    }

    // allocate memory for counties
    *counties = (County *)malloc((lineCount - 1) * sizeof(County)); // -1 to exclude header
    if (*counties == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 0;
    }

    rewind(file); // Go to start of file
    fgets(line, MAX_LINE_LENGTH, file); // skip header line

    char *token;
    int index = 0;
    // get each line
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        int currentColumn = 0;
        token = strtok(line, ",\n");

        // if token it as specified index, store it accordingly in the structure
        while (token != NULL) {
            removeQuotes(token);
            switch (currentColumn) {
                case 0:
                    strncpy((*counties)[index].county, token, MAX_STRING_LENGTH - 1);
                    (*counties)[index].county[MAX_STRING_LENGTH - 1] = '\0';
                    break;
                case 1:
                    strncpy((*counties)[index].state, token, MAX_STRING_LENGTH - 1);
                    (*counties)[index].state[MAX_STRING_LENGTH - 1] = '\0';
                    break;
                case 5:
                    (*counties)[index].education_bachelors_or_higher = atof(token);
                    break;
                case 6:
                    (*counties)[index].education_high_school_or_higher = atof(token);
                    break;
                case 11:
                    (*counties)[index].ethnicities_american_indian_and_alaska_native_alone = atof(token);
                    break;
                case 12:
                    (*counties)[index].ethnicities_asian_alone = atof(token);
                    break;
                case 13:
                    (*counties)[index].ethnicities_black_alone = atof(token);
                    break;
                case 14:
                    (*counties)[index].ethnicities_hispanic_or_latino = atof(token);
                    break;
                case 15:
                    (*counties)[index].ethnicities_native_hawaiian_and_other_pacific_islander_alone = atof(token);
                    break;
                case 16:
                    (*counties)[index].ethnicities_two_or_more_races = atof(token);
                    break;
                case 17:
                    (*counties)[index].ethnicities_white_alone = atof(token);
                    break;
                case 18:
                    (*counties)[index].ethnicities_white_alone_not_hispanic_or_latino = atof(token);
                    break;
                case 25:
                    (*counties)[index].income_median_household_income = atoi(token);
                    break;
                case 26:
                    (*counties)[index].income_per_capita_income = atoi(token);
                    break;
                case 27:
                    (*counties)[index].income_persons_below_poverty_level = atof(token);
                    break;
                case 38:
                    (*counties)[index].population_2014_population = atoi(token);
                    break;
            }

            token = strtok(NULL, ",\n");
            currentColumn++;
        }

        index++;
    }

    *countyCount = lineCount - 2; // number of entries
    fclose(file);

    printf("%d entries loaded.\n", *countyCount);
    return 1;
}

// print data in an organized manner
void displayCountyData(const County *counties, int countyCount) {
    printf("County Data:\n");
    for (int i = 0; i < countyCount; i++) {
        printf("County: %s, State: %s\n", counties[i].county, counties[i].state);
        printf("\tEducation:\n");
        printf("\t\tBachelor's or Higher: %.2f%%\n", counties[i].education_bachelors_or_higher);
        printf("\t\tHigh School or Higher: %.2f%%\n", counties[i].education_high_school_or_higher);
        printf("\tEthnicities:\n");
        printf("\t\tAmerican Indian and Alaska Native Alone: %.2f%%\n", counties[i].ethnicities_american_indian_and_alaska_native_alone);
        printf("\t\tAsian Alone: %.2f%%\n", counties[i].ethnicities_asian_alone);
        printf("\t\tBlack Alone: %.2f%%\n", counties[i].ethnicities_black_alone);
        printf("\t\tHispanic or Latino: %.2f%%\n", counties[i].ethnicities_hispanic_or_latino);
        printf("\t\tNative Hawaiian and Other Pacific Islander Alone: %.2f%%\n", counties[i].ethnicities_native_hawaiian_and_other_pacific_islander_alone);
        printf("\t\tTwo or More Races: %.2f%%\n", counties[i].ethnicities_two_or_more_races);
        printf("\t\tWhite Alone: %.2f%%\n", counties[i].ethnicities_white_alone);
        printf("\t\tWhite Alone not Hispanic or Latino: %.2f%%\n", counties[i].ethnicities_white_alone_not_hispanic_or_latino);
        printf("\tIncome:\n");
        printf("\t\tMedian Household Income: $%d\n", counties[i].income_median_household_income);
        printf("\t\tPer Capita Income: $%d\n", counties[i].income_per_capita_income);
        printf("\t\tPersons Below Poverty Level: %.2f%%\n", counties[i].income_persons_below_poverty_level);
        printf("\tPopulation:\n");
        printf("\t\tPopulation 2014: %d\n", counties[i].population_2014_population);
        printf("\n");
    }
}

// filter by the state
void filterByState(County **counties, int *countyCount, const char *stateAbbrev) {
    int count = 0;

    for (int i = 0; i < *countyCount; i++) {
        if (strcmp((*counties)[i].state, stateAbbrev) == 0) {
            if (i != count) {
                (*counties)[count] = (*counties)[i]; // Move matching county to the new position
            }
            count++;
        }
    }

    *countyCount = count;
    County *temp = (County *)realloc(*counties, count * sizeof(County));
    if (temp == NULL) {
        perror("Memory reallocation failed");
        // Handle error, e.g., log error, clean up resources, etc.
        return;
    }
    *counties = temp;

    printf("Filter: state == %s (%d entries)\n", stateAbbrev, count);
}

// filter by a specific field
void filterByField(County **counties, int *countyCount, const char *field, const char *comparison, float number) {
    int count = 0;

    for (int i = 0; i < *countyCount; i++) {
        float value = 0.0;

        // Determine which field to compare
        if (strcmp(field, "education_bachelors_or_higher") == 0) {
            value = (*counties)[i].education_bachelors_or_higher;
        } else if (strcmp(field, "education_high_school_or_higher") == 0) {
            value = (*counties)[i].education_high_school_or_higher;
        } else if (strcmp(field, "ethnicities_american_indian_and_alaska_native_alone") == 0) {
            value = (*counties)[i].ethnicities_american_indian_and_alaska_native_alone;
        } else if (strcmp(field, "ethnicities_asian_alone") == 0) {
            value = (*counties)[i].ethnicities_asian_alone;
        } else if (strcmp(field, "ethnicities_black_alone") == 0) {
            value = (*counties)[i].ethnicities_black_alone;
        } else if (strcmp(field, "ethnicities_hispanic_or_latino") == 0) {
            value = (*counties)[i].ethnicities_hispanic_or_latino;
        } else if (strcmp(field, "ethnicities_native_hawaiian_and_other_pacific_islander_alone") == 0) {
            value = (*counties)[i].ethnicities_native_hawaiian_and_other_pacific_islander_alone;
        } else if (strcmp(field, "ethnicities_two_or_more_races") == 0) {
            value = (*counties)[i].ethnicities_two_or_more_races;
        } else if (strcmp(field, "ethnicities_white_alone") == 0) {
            value = (*counties)[i].ethnicities_white_alone;
        } else if (strcmp(field, "ethnicities_white_alone_not_hispanic_or_latino") == 0) {
            value = (*counties)[i].ethnicities_white_alone_not_hispanic_or_latino;
        } else if (strcmp(field, "income_median_household_income") == 0) {
            value = (float)(*counties)[i].income_median_household_income;
        } else if (strcmp(field, "income_per_capita_income") == 0) {
            value = (float)(*counties)[i].income_per_capita_income;
        } else if (strcmp(field, "income_persons_below_poverty_level") == 0) {
            value = (*counties)[i].income_persons_below_poverty_level;
        } else if (strcmp(field, "population_2014_population") == 0) {
            value = (float)(*counties)[i].population_2014_population;
        } else {
            printf("Invalid or non-numeric field: %s\n", field);
            free(*counties);
            *counties = NULL;
            *countyCount = 0;
            return;
        }

        // compare
        if ((strcmp(comparison, "ge") == 0 && value >= number) ||
            (strcmp(comparison, "le") == 0 && value <= number)) {
            if (i != count) {
                (*counties)[count] = (*counties)[i]; // Move matching county to the new position
            }
            count++;
        }
    }

    *countyCount = count;
    County *temp = (County *)realloc(*counties, count * sizeof(County));
    if (temp == NULL) {
        perror("Memory reallocation failed");
        // Handle error, e.g., log error, clean up resources, etc.
        return;
    }
    *counties = temp;

    printf("Filter: %s %s %.2f (%d entries)\n", field, comparison, number, count);
}

// calculate and print total population
void calculateTotalPopulation(County *counties, int countyCount) {
    int totalPopulation = 0;
    for (int i = 0; i < countyCount; i++) {
        totalPopulation += counties[i].population_2014_population;
    }
    printf("2014 population: %d\n", totalPopulation);
}

// helper func: gets the percentage value for a given field from a county
float getFieldPercentage(County county, const char *field) {
    if (strcmp(field, "education_bachelors_or_higher") == 0) {
        return county.education_bachelors_or_higher;
    } else if (strcmp(field, "education_high_school_or_higher") == 0) {
        return county.education_high_school_or_higher;
    } else if (strcmp(field, "ethnicities_american_indian_and_alaska_native_alone") == 0) {
        return county.ethnicities_american_indian_and_alaska_native_alone;
    } else if (strcmp(field, "ethnicities_asian_alone") == 0) {
        return county.ethnicities_asian_alone;
    } else if (strcmp(field, "ethnicities_black_alone") == 0) {
        return county.ethnicities_black_alone;
    } else if (strcmp(field, "ethnicities_hispanic_or_latino") == 0) {
        return county.ethnicities_hispanic_or_latino;
    } else if (strcmp(field, "ethnicities_native_hawaiian_and_other_pacific_islander_alone") == 0) {
        return county.ethnicities_native_hawaiian_and_other_pacific_islander_alone;
    } else if (strcmp(field, "ethnicities_two_or_more_races") == 0) {
        return county.ethnicities_two_or_more_races;
    } else if (strcmp(field, "ethnicities_white_alone") == 0) {
        return county.ethnicities_white_alone;
    } else if (strcmp(field, "ethnicities_white_alone_not_hispanic_or_latino") == 0) {
        return county.ethnicities_white_alone_not_hispanic_or_latino;
    } else if (strcmp(field, "income_persons_below_poverty_level") == 0) {
        return county.income_persons_below_poverty_level;
    }
    return 0.0;
}

// calculate and print sub-population for a given field
void calculateSubPopulation(County *counties, int countyCount, const char *field) {
    int totalPopulation = 0;
    float subPopulation = 0.0;

    for (int i = 0; i < countyCount; i++) {
        totalPopulation += counties[i].population_2014_population;
        float percentage = getFieldPercentage(counties[i], field);
        subPopulation += (percentage / 100.0) * counties[i].population_2014_population;
    }

    printf("2014 %s population: %.0f\n", field, subPopulation);
}

// calculate and print percentage for a given field
void calculatePercentage(County *counties, int countyCount, const char *field) {
    int totalPopulation = 0;
    float subPopulation = 0.0;

    for (int i = 0; i < countyCount; i++) {
        totalPopulation += counties[i].population_2014_population;
        float percentage = getFieldPercentage(counties[i], field);
        subPopulation += (percentage / 100.0) * counties[i].population_2014_population;
    }

    float resultPercentage = (subPopulation / totalPopulation) * 100.0;
    printf("2014 %s percentage: %.2f%%\n", field, resultPercentage);
}

// read operations from an operations file
int readOperationsFile(char *filename, Operation *operations, int *operationCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening operations file");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL && count < MAX_OPERATIONS) {
        char *token = strtok(line, " \n");
        if (token != NULL) {
            strcpy(operations[count].operationType, token);
            token = strtok(NULL, "\n");
            if (token != NULL) {
                strcpy(operations[count].parameters, token);
                count++;
            }
        }
    }

    *operationCount = count;
    fclose(file);
    return 1;
}

// execute operations
void executeOperations(Operation *operations, int operationCount, County *counties, int countyCount) {
    for (int i = 0; i < operationCount; i++) {
        if (strcmp(operations[i].operationType, "display") == 0) {
            displayCountyData(counties, countyCount);
        } else if (strcmp(operations[i].operationType, "filterState") == 0) {
            filterByState(&counties, &countyCount, operations[i].parameters);
        } else if (strcmp(operations[i].operationType, "filterField") == 0) {
            char field[MAX_STRING_LENGTH];
            char comparison[MAX_STRING_LENGTH];
            float number;
            sscanf(operations[i].parameters, "%s %s %f", field, comparison, &number);
            filterByField(&counties, &countyCount, field, comparison, number);
        } else if (strcmp(operations[i].operationType, "totalPopulation") == 0) {
            calculateTotalPopulation(counties, countyCount);
        } else if (strcmp(operations[i].operationType, "subPopulation") == 0) {
            calculateSubPopulation(counties, countyCount, operations[i].parameters);
        } else if (strcmp(operations[i].operationType, "percentage") == 0) {
            calculatePercentage(counties, countyCount, operations[i].parameters);
        } else {
            printf("Unknown operation: %s\n", operations[i].operationType);
        }
    }
}

int main(int argc, char *argv[]) {
    // make sure input contains three arguments
    if (argc != 3) {
        printf("Usage: %s <demographics_file.csv> <operations_file.txt>\n", argv[0]);
        return 1;
    }

    // read demographics file
    County *counties = NULL;
    int countyCount = 0;
    if (!readDemographicsFile(argv[1], &counties, &countyCount)) {
        printf("Error reading demographics file.\n");
        free(counties);
        return 1;
    }

    // read operations file
    Operation operations[MAX_OPERATIONS];
    int operationCount = 0;
    if (!readOperationsFile(argv[2], operations, &operationCount)) {
        printf("Error reading operations file.\n");
        free(counties);
        return 1;
    }

    // execute the operations
    executeOperations(operations, operationCount, counties, countyCount);

    free(counties);

    return 0;
}
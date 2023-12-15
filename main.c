#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_STRING_LENGTH 100

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

// Define a structure for operations
typedef struct {
    char operationType[MAX_STRING_LENGTH];
    char parameters[MAX_STRING_LENGTH];
} Operation;

void removeQuotes(char *str) {
    size_t len = strlen(str);
    if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
        memmove(str, str + 1, len - 2); // Shift the string one character to the left
        str[len - 2] = '\0'; // Null-terminate the string
    }
}

// read the demographics file and store it in an array
int readDemographicsFile(char *filename, County **counties, int *countyCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int lineCount = 0;

    // Count the number of lines to determine the size of the array
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        lineCount++;
    }

    // Allocate memory for counties
    *counties = (County *)malloc((lineCount - 1) * sizeof(County)); // -1 to exclude header
    if (*counties == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 0;
    }

    rewind(file); // Go back to the beginning of the file
    fgets(line, MAX_LINE_LENGTH, file); // Skip header line

    char *token;
    int index = 0;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        int currentColumn = 0;
        token = strtok(line, ",\n");

        while (token != NULL) {
            removeQuotes(token);
            switch (currentColumn) {
                case 0: // County
                    strcpy((*counties)[index].county, token);
                    break;
                case 1: // State
                    strcpy((*counties)[index].state, token);
                    break;
                case 5: // Education.Bachelor's Degree or Higher
                    (*counties)[index].education_bachelors_or_higher = atof(token);
                    break;
                case 6: // Education.High School or Higher
                    (*counties)[index].education_high_school_or_higher = atof(token);
                    break;
                case 11: // Ethnicities.American Indian and Alaska Native Alone
                    (*counties)[index].ethnicities_american_indian_and_alaska_native_alone = atof(token);
                    break;
                case 12: // Ethnicities.Asian Alone
                    (*counties)[index].ethnicities_asian_alone = atof(token);
                    break;
                case 13: // Ethnicities.Black Alone
                    (*counties)[index].ethnicities_black_alone = atof(token);
                    break;
                case 14: // Ethnicities.Hispanic or Latino
                    (*counties)[index].ethnicities_hispanic_or_latino = atof(token);
                    break;
                case 15: // Ethnicities.Native Hawaiian and Other Pacific Islander Alone
                    (*counties)[index].ethnicities_native_hawaiian_and_other_pacific_islander_alone = atof(token);
                    break;
                case 16: // Ethnicities.Two or More Races
                    (*counties)[index].ethnicities_two_or_more_races = atof(token);
                    break;
                case 17: // Ethnicities.White Alone
                    (*counties)[index].ethnicities_white_alone = atof(token);
                    break;
                case 18: // Ethnicities.White Alone not Hispanic or Latino
                    (*counties)[index].ethnicities_white_alone_not_hispanic_or_latino = atof(token);
                    break;
                case 25: // Income.Median Household Income
                    (*counties)[index].income_median_household_income = atoi(token);
                    break;
                case 26: // Income.Per Capita Income
                    (*counties)[index].income_per_capita_income = atoi(token);
                    break;
                case 27: // Income.Persons Below Poverty Level
                    (*counties)[index].income_persons_below_poverty_level = atof(token);
                    break;
                case 38: // Population.2014 Population
                    (*counties)[index].population_2014_population = atoi(token);
                    break;
            }

            token = strtok(NULL, ",\n");
            currentColumn++;
        }

        index++;
    }

    *countyCount = lineCount - 1; // Set the number of counties read
    fclose(file);
    return 1;
}

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

void filterByState(County **counties, int *countyCount, const char *stateAbbrev) {
    int count = 0;
    for (int i = 0; i < *countyCount; i++) {
        if (strcmp((*counties)[i].state, stateAbbrev) == 0) {
            (*counties)[count++] = (*counties)[i];
        }
    }
    *countyCount = count; // Update the number of counties after filtering
    printf("Filter: state == %s (%d entries)\n", stateAbbrev, count);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <demographics_file.csv>\n", argv[0]);
        return 1;
    }

    County *counties = NULL;
    int countyCount = 0;
    if (!readDemographicsFile(argv[1], &counties, &countyCount)) {
        printf("Error reading demographics file.\n");
        return 1;
    }

    filterByState(&counties, &countyCount, "RI");
    displayCountyData(counties, countyCount);

    free(counties);

    return 0;
}

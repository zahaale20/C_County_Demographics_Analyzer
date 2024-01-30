# C_County_Demographics_Analyzer

### Description:
The "C_County_Demographics_Analyzer" GitHub repository hosts a comprehensive C program designed to process and analyze real county demographics data from the CORGIS project's Census information. This project aims to enhance C programming skills while providing insights into data interpretation and its potential biases.

### Task 1 - Demographics Data Processing Program:

Program Name: county_demographics.
Functionality: The program takes two command-line arguments: a CSV file containing county demographics data and a file specifying a sequence of operations for data processing.
Data Loading and Validation:
Parses the CSV file, skipping the first line of column headers.
Converts numeric fields to appropriate data types and excludes extraneous data.
Handles malformed entries with error messages and skips them.
Supported Fields for Queries: County, State, Education, Ethnicities, Income, and Population for 2014.
Operations Supported:
display: Outputs county information.
filter-state: Filters entries by state abbreviation.
filter: Filters entries based on field values and comparison operators.
population-total: Computes total 2014 population across entries.
population and percent: Calculates sub-populations and their percentages based on specified fields.
Processing Operations: Executes operations in order, updating data state as per the operations file.

### Task 2 - Operations File Submission:
Submit operations files to analyze specific demographic metrics:
Percentage of population below poverty level in counties with high school completion <= 80%.
Percentage below poverty level in counties with bachelor's completion >= 40%.
Percentage below poverty level in counties based on a selected ethnicity >= 40%.
Percentage below poverty level in counties based on the same ethnicity <= 40%.

### Reflection on Data Interpretation:
Emphasis on cautious interpretation of the data, avoiding implicit biases.
Acknowledgment of the limitations in the data and the absence of causal information.

### Repository Contents:
Source code for the county_demographics program.
Example operations files for specific demographic analyses.
Documentation on the program's functionality, data processing techniques, and the usage of command-line arguments.
Additional notes on the potential misinterpretations and biases in data analysis.

/*
    Name: Yusuf Alperen Çelik
    Project Name: Histogram Generator
    Date: 10.04.2024
*/
/* 
Description: 
    This program allows the user to enter a range of numbers and display a histogram of the numbers.
    The user can also add new numbers to the histogram and see the average, median, and mode of the numbers.
*/
#include <stdio.h>
#define MAX_SIZE 1000 
#define LOWER_LIMIT 50
#define UPPER_LIMIT 200

/*Function prototypes*/
int find_size_of_array(int A[]);
void draw_histogram(int A, int B, int number_array[], int size);
void add_numbers_to_array(int number_array[], int *size);
void bubbleSort(int arr[], int size);
double calculate_average(int A, int B, int number_array[], int size);
void calculate_mode(int A, int B,int number_array[], int size);
float calculateMedian(int A, int B, int arr[], int size);

int main() 
{
    int A, B, flag = 1, menuFlag = 1;
    char addMore;
    int number_array[MAX_SIZE] = {
        93,  193, 95,   133,  85,  191,  55, 100, 101, 102, 76, 104, 105, 106, 107, 108,
        120, 110, 111, 112, 113, 114, 115, 116, 117, 118, 163, 120, 121, 122, 193, 124,
        125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140,
        141, 193, 133, 144, 145, 146, 147, 148, 149, 150, 151, 193, 153, 154, 155, 156,
        157, 158, 111, 160, 120, 162, 163, 128, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 176, 177, 111, 165, 180, 100, 111, 120, 184, 133, 186, 187, 188,
        125, 190, 191, 192, 193, 194, 195, 132, 197, 198, 199, 125, 201, 202, 203, 173,
        205,  61, 128, 173,  76, 111, 133, 45, -1};
    
    int size = find_size_of_array(number_array); 
    bubbleSort(number_array, size);
    while(menuFlag)
    {
        printf("Enter A and B values: ");
        scanf("%d %d", &A, &B);
        if(A >= LOWER_LIMIT && B <= UPPER_LIMIT) /*Check the validity of the entered interval*/
        {   
            draw_histogram(A, B, number_array, size);    
            while(flag)
            {
                printf("Would you like to add new numbers? (Press 1 for yes, press 0 for no): ");
                scanf(" %c", &addMore);
                if(addMore == '1') 
                {
                    add_numbers_to_array(number_array, &size); /*Add new numbers and update size*/
                    draw_histogram(A, B, number_array, size); /*Redraw histogram with updated data*/
                    bubbleSort(number_array, size);
                    double average = calculate_average(A, B, number_array, size);
                    double median = calculateMedian(A, B, number_array, size);
                    printf("Average: %.2f\n", average);
                    printf("Median: %.2f\n", median);
                    calculate_mode(A, B, number_array, size);
                    flag = 0;
                }
                else if(addMore == '0')
                {
                    double average = calculate_average(A, B, number_array, size);
                    double median = calculateMedian(A, B, number_array, size);
                    printf("Average: %.2f\n", average);
                    printf("Median: %.2f\n", median);
                    calculate_mode(A, B, number_array, size);
                    flag = 0;
                }
                else
                {
                    printf("\nInvalid input! Please enter 1 or 0.\n");
                }
            }
            menuFlag = 0;
        }
        else
        {
            printf("\nInvalid interval! Please enter an interval such that A >= 50 and B <= 200.\n");
        }
    }
    return 0;
}
double calculate_average(int A, int B, int number_array[], int size) 
{
    double sum = 0;
    int count = 0, i;
    for(i = 0; i < size; i++) 
    {
        if(A <= number_array[i] && number_array[i] <= B) /*Check if the number is within the interval*/
        {
            sum += number_array[i];
            count++;
        }
    }
    if(count == 0) /*If no valid numbers found*/
    {
        return 0;
    }
    return (sum / count);
}
void calculate_mode(int A, int B, int number_array[], int size) 
{
    int i;
    int frequency[MAX_SIZE] = {0}; /*Array to store frequency of each number*/
    int maxFrequency = 0;
    for(i = 0; i < size; i++) 
    {
        if(number_array[i] >= A && number_array[i] <= B) 
        {
            frequency[number_array[i]]++; /*Increment the frequency of the number*/
            if(frequency[number_array[i]] > maxFrequency)  /*Update max frequency*/
            {
                maxFrequency = frequency[number_array[i]];
            }
        }
    }
    printf("Mode: ");
    for(i = A; i <= B; i++) /*Print modes within the interval*/
    {
        if(frequency[i] == maxFrequency) /*If frequency equals max frequency, print the number*/
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}
float calculateMedian(int A, int B, int arr[], int size) 
{
    int temp[MAX_SIZE];
    int j = 0, i;
    for(i = 0; i < size; i++) 
    {
        if(arr[i] >= A && arr[i] <= B) 
        {
            temp[j] = arr[i]; /*Copy numbers within the interval to temporary array*/
            j++;
        }
    }
    if(j == 0) /*If no numbers within the interval*/
    { 
        return -1;
    }
    bubbleSort(temp, j); /*Sort the elements in the interval*/
    if(j % 2 != 0)
    {
        return (float)temp[j / 2]; /*Return middle element*/
    }
    else /*If even number of elements*/
    {
        return (float)(temp[(j - 1) / 2] + temp[j / 2]) / 2.0; /*Return average of middle elements*/
    }
}
void bubbleSort(int arr[], int size) 
{
    int i, j;
    for(i = 0; i < size-1; i++) 
    {
        for(j = 0; j < size-i-1; j++) 
        {
            if(arr[j] > arr[j+1]) /*Swap if the current element is greater than the next element*/
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
int find_size_of_array(int A[]) 
{
    int size = 0;
    while(A[size] != -1 && size < MAX_SIZE) /*Loop until -1 is found or maximum size is reached*/
    {
        size++;
    }
    return size;
}
void draw_histogram(int A, int B, int number_array[], int size) 
{
    int frequency[MAX_SIZE] = {0}; /*Array to store frequency of each number*/
    int i, row, col;
    for(i = 0; i < size; i++) 
    {
        if(number_array[i] >= A && number_array[i] <= B) 
        {
            frequency[number_array[i] - A]++; /*Increment the frequency of the number*/
        }
    }
    int max_freq = 0;
    for(i = 0; i <= B-A; i++) /*Find the maximum frequency*/
    {
        if(frequency[i] > max_freq) 
        {
            max_freq = frequency[i];
        }
    }
    for(row = max_freq; row > 0; row--) /* Loop  through rows*/
    {
        for(col = A; col <= B; col++)  /*Loop through colums*/
        {
            if(frequency[col - A] >= row) /*If the frequency is greater than or equal to the current row*/
            {
                printf("*");
            } 
            else 
            {
                printf(" ");
            }
        }
        printf("\n"); /*Move to the next line*/
    }
    printf("\n");
}
void add_numbers_to_array(int number_array[], int *size) 
{
    int num, count = 0;
    printf("Enter up to five numbers to add to the histogram (end with -1):\n");
    while(count < 5 && scanf("%d", &num) && num != -1)  /*Loop until five numbers are added or -1 is encountered*/
    {
        if(*size < MAX_SIZE - 1) /*Check if the array is not full*/
        {
            number_array[*size] = num;
            (*size)++;
            count++;
        }
        else 
        {
            printf("Maximum array size reached. Cannot add more numbers.\n");
            break;
        }
    }
    if(*size < MAX_SIZE) /*If the array is not full*/
    { 
        number_array[*size] = -1; /*Add -1 to mark the end of the array*/
    }
}
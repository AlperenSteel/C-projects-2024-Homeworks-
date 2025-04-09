#include <stdio.h>
/* 
TITLE: 
    Decision Tree Classifier
    Author: YUSUF ALPEREN ÇELİK
    Date: 13.03.2024
*/
/* 
DESCRIPTION:
    This program is a simple implementation of a decision tree classifier.
    It reads data from a file, calculates the minimum error count for a separator and regions,
    and then tests the model with a test set.
    It also provides a menu to explore the data, train the model, test the model, and exit the program.
*/
int main()
{
        FILE *file;
        char choice;
        int x, y;
        int class_label;
        int max_x_0 = -10000, min_x_0 = 10000, max_y_0 = -10000, min_y_0 = 10000;
        int max_x_1 = -10000, min_x_1 = 10000, max_y_1 = -10000, min_y_1 = 10000;
        int min_x = 10000, min_y = 10000, max_y = -10000, max_x = -10000;
        int min_error_count = 1000;
        int min_region_first, min_region_second, min_region_third, min_region_fourth, region_first, region_second, region_third, region_fourth;
        int separator_x, separator_y, min_separator_x, min_separator_y;
        int error_count = 0;
        float predict_count = 0, total_data_count = 0, success = 0;
        int flag = 0, menu_flag = 1, test;
        /* Open the file */
            file = fopen("data.txt", "r");
            if (file == NULL) 
            {
            printf("Error opening file.\n");
            }
            /* Read the data points */
            while (fscanf(file, "%d %d %d", &x, &y, &class_label) == 3) 
            {
            /* Update maximum and minimum X and Y coordinates for each class */
                if (class_label == 0) 
                {
                    if (x > max_x_0)
                        max_x_0 = x;
                    if (x < min_x_0)
                        min_x_0 = x;
                    if (y > max_y_0)
                        max_y_0 = y;
                    if (y < min_y_0)
                        min_y_0 = y;
                }
                else if (class_label == 1) 
                {
                    if (x > max_x_1)
                        max_x_1 = x;
                    if (x < min_x_1)
                        min_x_1 = x;
                    if (y > max_y_1)
                        max_y_1 = y;
                    if (y < min_y_1)
                        min_y_1 = y;
                }
                /* Update the overall maximum and minimum X and Y coordinates */
                if (x > max_x)
                    max_x = x;
                if (x < min_x)
                    min_x = x;
                if (y > max_y)
                    max_y = y;
                if (y < min_y)
                    min_y = y;
                }
                fclose(file);
            /* Loop through possible separator coordinates and regions*/
            for (separator_x = min_x; separator_x <= max_x; separator_x++) 
            {
                for (separator_y = min_y; separator_y <= max_y; separator_y++) 
                {
                    for (region_first = 0; region_first <= 1; region_first++) 
                    {
                        for (region_second = 0; region_second <= 1; region_second++) 
                        {
                            for (region_third = 0; region_third <= 1; region_third++) 
                            {
                                for (region_fourth = 0; region_fourth <= 1; region_fourth++)
                                {
                                    error_count = 0;
                                    file = fopen("data.txt", "r");
                                    /* Calculate error count for current separator and regions.*/
                                    while (fscanf(file, "%d %d %d", &x, &y, &class_label) == 3)
                                    {
                                        if (x <= separator_x && y > separator_y && region_first != class_label) 
                                        {
                                            error_count++;
                                        } 
                                        else if (x > separator_x && y > separator_y && region_second != class_label) 
                                        {
                                            error_count++;
                                        }
                                        else if (x <= separator_x && y <= separator_y && region_third != class_label) 
                                        {
                                            error_count++;
                                        }
                                        else if( x > separator_x && y <= separator_y && region_fourth != class_label)
                                        {
                                            error_count++;
                                        }
                                    }
                                    fclose(file);
                                    /* Update minimum error count and corresponding regions.*/
                                    if (error_count < min_error_count) 
                                    {
                                        min_error_count = error_count;
                                        min_region_first = region_first;
                                        min_region_second = region_second;
                                        min_region_third = region_third;
                                        min_region_fourth = region_fourth;
                                        min_separator_x = separator_x;
                                        min_separator_y = separator_y;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            file = fopen("test 1.txt", "r");
            if (file == NULL) 
            {
            printf("Error opening file.\n");
            return 0;
            }
            while (fscanf(file, "%d %d %d", &x, &y, &class_label) == 3) /* Test the model and calculate success rate.*/
            {
                if (x <= min_separator_x && y > min_separator_y && min_region_first == class_label) 
                {
                    predict_count++;
                } 
                else if (x > min_separator_x && y > min_separator_y && min_region_second == class_label) 
                {
                    predict_count++;
                }
                else if (x <= min_separator_x && y <= min_separator_y && min_region_third == class_label) 
                {
                    predict_count++;
                }
                else if( x > min_separator_x && y <= min_separator_y && min_region_fourth == class_label)
                {
                    predict_count++;
                }
                total_data_count++;
            }
            success = predict_count/total_data_count;
            fclose(file);
        while(menu_flag)
        {
        printf("\n## STUDENT NAME: YUSUF ALPEREN ÇELİK ##\n");
        printf("## PLEASE SELECT FROM THE FOLLOWING  ##\n");
        printf("## MENU :                            ##\n");
        printf("\t Enter (1) for EXPLORE DATA\n");
        printf("\t Enter (2) for TRAIN MODEL\n");
        printf("\t Enter (3) for TEST MODEL\n");
        printf("\t Enter (0) for EXIT\n");
        printf("\tPLEASE SELECT: ");
        scanf(" %c", &choice); /* Adding a space before %c to clear any unexpected newline character*/
            switch(choice)
                {
                    case '1':
                        printf("\nMinimum and Maximum X and Y values:\n");
                        printf("Class 0: X in [%d %d], Y in [%d %d]\n", min_x_0, max_x_0, min_y_0, max_y_0);
                        printf("Class 1: X in [%d %d], Y in [%d %d]\n", min_x_1, max_x_1, min_y_1, max_y_1);
                        break;
                    case '2':
                        printf("\nSeparator coordinates: X=%d, Y=%d\n", min_separator_x, min_separator_y);
                        printf("Training error of the model = %d\n", min_error_count);
                        printf("Labels of the regions: R1= %d, R2= %d, R3 = %d, R4= %d\n", min_region_first, min_region_second, min_region_third, min_region_fourth);
                        break;
                    case '3':
                        printf("\nAccuracy rate is: %f\n\n", success);
                        file = fopen("test 1.txt", "r");
                        if (file == NULL) 
                        {
                            printf("Error opening file.\n");
                            return 0;
                        }
                        while (fscanf(file, "%d %d", &x, &y) == 2) /* Print predicted classes for final test data.*/
                        {
                            if (x <= min_separator_x && y > min_separator_y) 
                            {
                                printf("X: %d, Y: %d, class: %d\n",x, y, min_region_first);
                            } 
                            else if (x > min_separator_x && y > min_separator_y) 
                            {
                                printf("X: %d, Y: %d, class: %d\n",x, y, min_region_second);
                            }
                            else if (x <= min_separator_x && y <= min_separator_y) 
                            {
                                printf("X: %d, Y: %d, class: %d\n",x, y, min_region_third);
                            }
                            else if( x > min_separator_x && y <= min_separator_y)
                            {
                                printf("X: %d, Y: %d, class: %d\n",x, y, min_region_fourth);
                            }
                        }
                        break;
                    case '0':
                        printf("Exiting...");
                        menu_flag = 0;
                        break;
                    default:
                        printf("\nInvalid option. Enter a valid character!\n");
                        break;
                }
        }
        return 0;
}
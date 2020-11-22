/***************************************************************
 *
 * Name:                 Form.c
 *
 * Last modification:    15/11/2020
 *
 * Description:          contain Page form and menu to select
 *                       actions of the program.
 *
 *Author:                Ahmed Eldakhly.
 *
 ***************************************************************/

/****************************************************************
 *                       Includes Files                         *
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Position_Color.h"
#include "MultiLine_editor.h"
#include "Form_config.h"

/****************************************************************
 *                       Global Variable                        *
 ***************************************************************/
 /* the color of the form. */
int color_g = RED;
/* last used line in the page. */
int Last_Line = 0;
/* array of pointer for each line in the page. */
char** Line_arr = NULL;
/* array of pointer to point into the End of each line. */
char** End_of_Line = NULL;
/* array of pointer to point into the cursor position of each line. */
char** Current_Position = NULL;

/****************************************************************
 * Function Name:	color
 *
 * Description: 	static function to change the color of the
 *                  highlighted lines.
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 ***************************************************************/
static void color(void)
{
    /* static to keep the current select. */
    static int curr = 0;
    char x;
    int exit = 0;
    /* Display color menu. */
    textattr(0x7D);
    gotoxy(48,3);
    printf("|               |");
    gotoxy(48,4);
    printf("|RED            |");
    gotoxy(48,5);
    printf("|               |");
    gotoxy(48,6);
    printf("|BLUE           |");
    gotoxy(48,7);
    printf("|               |");
    gotoxy(48,8);
    printf("|GREEN          |");
    gotoxy(48,9);
    printf("|_______________|");
    /* loop to get the color from the user. */
    do
    {
        /* display the page without go to insertion mode. */
        Multi_Line_editor(LINE_SIZE_HER, LINE_SIZE_VER , 5 , 5 , 1);
        for (int i = 0; i < 6; i += 2)
        {
            if(curr == i)
            {
                textattr(0x7D);
            }
            /* check witch the option is selected to make it highlighted. */
            switch(i)
            {
                case 0:
                    gotoxy(48, 3 + i);
                    _cprintf("|               |");
                    gotoxy(48, 4 + i);
                    _cprintf("|RED            |");
                    break;
                case 2:
                    gotoxy(48, 3 + i);
                    _cprintf("|               |");
                    gotoxy(48, 4 + i);
                    _cprintf("|BLUE           |");
                    break;
                case 4:
                    gotoxy(48, 3 + i);
                    _cprintf("|               |");
                    gotoxy(48, 4 + i);
                    _cprintf("|GREEN          |");
                    gotoxy(48,9);
                    printf("|_______________|");
                    break;
            }
            textattr(0x07);
        }
        x = getch();
        /* change the colors by arrows. */
        if(x == -32)
        {
            x = getch();
            switch(x)
            {
                case 71:
                    curr = 0;
                    break;
                case 79:
                    curr = 5;
                    break;
                case 72:
                    curr -= 2;
                    /* check if we get the first of the color list. */
                    if(curr < 0)
                        curr = 5;
                    break;
                case 80:
                    curr += 2;
                    /* check if we get the last of the color list. */
                    if(curr > 5)
                        curr = 0;
                    break;
            }
            switch(curr)
            {
                case 0:
                    color_g = RED;
                    break;
                case 2:
                    color_g = BLUE;
                    break;
                case 4:
                    color_g = GREEN;
                    break;
            }
        }
        else
        {
            /* check witch option is selected to change the form color to it. */
            if(x == 13)
            {
                textattr(0x07);
                system("cls");
                /* display the page without go to insertion mode. */
                Multi_Line_editor(LINE_SIZE_HER, LINE_SIZE_VER , 5 , 5 , 1);
                exit = 1;
            }
        }
    }while(exit != 1);
}

/****************************************************************
 * Function Name:	Form_Page
 *
 * Description: 	to move between options on the page.
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 ***************************************************************/
void Form_Page(void)
{
    char x[LINE_SIZE_VER];
    FILE* fptr;
    char ch;
    char c_file = 1;
    int exit = 0;
    int cur = 0;
    frame();
    /* loop to move on the form and get user choice. */
    do
    {
        frame_menu();
        /* display the page without go to insertion mode. */
        Multi_Line_editor(LINE_SIZE_HER, LINE_SIZE_VER , 5 , 5 , 1);
        /* loop to print the selected option highlighted. */
        for (int i = 0; i < 5; i++)
        {
            if(cur == i)
            {
                textattr(0x7D);
            }
            gotoxy(1 + i * 16, 1);
            switch(i)
            {
                case 0:
                    _cprintf("New");
                    break;
                case 1:
                    _cprintf("Save");
                    break;
                case 2:
                    _cprintf("Display");
                    break;
                case 3:
                    _cprintf("Color");
                    break;
                case 4:
                    _cprintf("Exit");
                    break;
            }
            textattr(0x07);
        }
        /* get user choice. */
        ch = getch();
        /* if the user press on arrows or tab or enter. */
        if(ch == -32)
        {
            ch = getch();
            switch(ch)
            {
                case 71:
                    cur = 0;
                    break;
                case 79:
                    cur = 5;
                    break;
                case 75:
                    cur--;
                    if(cur < 0)
                        cur = 5;
                    break;
                case 77:
                    cur++;
                    if(cur > 5)
                        cur = 0;
                    break;
            }
        }
        else
        {
            switch(ch)
            {
                /* if user press on enter. */
                case 13:
                    textattr(0x07);
                    switch(cur)
                    {
                        /* new option. */
                        case 0:
                            /* check to remove old data if it is exist. */
                            if(Line_arr != NULL)
                            {
                                free(End_of_Line);
                                free(Current_Position);
                                for(int i = 0; i < LINE_SIZE_HER; i++)
                                {
                                    free(Line_arr[i]);
                                }
                                Line_arr = NULL;

                                Last_Line = 0;
                            }
                            /* call to the function of highlighted lines in write mode. */
                            Multi_Line_editor(LINE_SIZE_HER, LINE_SIZE_VER , 5 , 5 , 0);
                            cur = 1;
                            break;
                        /* save option. */
                        case 1:
                            /* open saved file. */
                            fptr = fopen("SavedLines.txt","w");
                            /* check if the file opened correctly. */
                            if(fptr != NULL)
                            {
                                /* save every line in the function. */
                                for(int i = 0; i < LINE_SIZE_HER; i++)
                                {
                                    fprintf(fptr,"%s\n",Line_arr[i]);
                                }
                                gotoxy(20 , 20);
                                printf("file is saved, Thank you\n");
                            }
                            else
                            {
                                gotoxy(20 , 20);
                                printf("The file couldn't be created.\n");
                            }
                            /* close the file to complete saving of the data. */
                            fclose(fptr);
                            getch();
                            gotoxy(20 , 20);
                            printf("                               ");
                            break;
                        /* display option to load data from the file. */
                        case 2:
                            /* check if the lines arrays not allocated yet. */
                            if(Line_arr == NULL)
                            {
                                /* pointer to array for each line */
                                Line_arr = malloc(LINE_SIZE_HER * sizeof(char*));
                                for(int i = 0; i < LINE_SIZE_HER; i++)
                                {
                                    Line_arr[i] = malloc(sizeof(char) * LINE_SIZE_VER);
                                }
                                /* array of pointer to point into the end character in each line. */
                                End_of_Line = malloc(LINE_SIZE_HER * sizeof(char*));
                                /* array of pointer to point into the cursor position of each line. */
                                Current_Position = malloc(LINE_SIZE_HER * sizeof(char*));
                            }
                            /* open the file to load the data. */
                            fptr = fopen("SavedLines.txt","r");
                            /* check if the file opened correctly. */
                            if(fptr != NULL)
                            {
                                /* go to the first of the file. */
                                fseek(fptr, 0, SEEK_SET);
                                /* for each line and but it in the form. */
                                for(int i = 0; i < LINE_SIZE_HER; i++)
                                {
                                    fscanf(fptr,"%[^\n]",Line_arr[i]);
                                    fscanf(fptr,"%c",&c_file);
                                    /* loop to put cursor on the end of the line. */
                                    for(int j = 0; j < LINE_SIZE_VER - 1; j++)
                                    {
                                        if(Line_arr[i][j] != ' ' && Line_arr[i][j] != '\0')
                                        {
                                            /* check if the line didn't full to put the cursor in the last character on the line. */
                                            if(j != LINE_SIZE_VER - 2)
                                            {
                                                End_of_Line[i] = &Line_arr[i][j+1];
                                                Current_Position[i] = &Line_arr[i][j+1];
                                            }
                                            /* the line is full and the cursor should be on the last char. */
                                            else
                                            {
                                                End_of_Line[i] = &Line_arr[i][j];
                                                Current_Position[i] = &Line_arr[i][j];
                                            }
                                        }
                                        /* if the line terminator exist before the end of the line change it with space. */
                                        else if(Line_arr[i][j] == '\0')
                                        {
                                            Line_arr[i][j] = ' ';
                                        }
                                    }
                                }
                                fseek(fptr, 0, SEEK_SET);
                                /* get the last line number in the saved file. */
                                for(int i = 0; i < LINE_SIZE_HER; i++)
                                {
                                    if(End_of_Line[i] != Line_arr[i])
                                        Last_Line = i;
                                }
                            }
                            else
                            {
                                printf("The file couldn't be created.\n");
                            }
                            fclose(fptr);
                            /* call line editor to show lines. */
                            Multi_Line_editor(LINE_SIZE_HER, LINE_SIZE_VER , 5 , 5 , 0);
                            break;
                        /* color option. */
                        case 3:
                            color();
                            frame();
                            break;
                        /* close the program. */
                        case 4:
                            exit = 1;
                            break;
                    }
                    break;
                /* tab option to move between the options. */
                case 9:
                    cur++;
                    if(cur > 5)
                        cur = 0;
                    else if(cur == 5)
                    {
                        Multi_Line_editor(LINE_SIZE_HER, LINE_SIZE_VER , 5 , 5 , 0);
                        cur = 0;
                    }

                    break;

            }
        }
    }while(exit == 0);
    /* free allocated memory. */
    if(End_of_Line != NULL)
        free(End_of_Line);
    if(Current_Position != NULL)
        free(Current_Position);
    if(Line_arr != NULL)
    {
        for(int i = 0; i < LINE_SIZE_HER; i++)
        {
            if(Line_arr[i] != NULL)
                free(Line_arr[i]);
        }
        free(Line_arr);
    }
    system("cls");
    printf("\n\n\n\n\n\n\n\n                              thank you\n\n\n\n\n\n\n\n\n");
}

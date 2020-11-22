/***************************************************************
 *
 * Name:                 Line_editor.c
 *
 * Last modification:    13/11/2020
 *
 * Description:          problem 2 in Lab 7 Line Editor
 *                      (Delete - BackSpace).
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

/****************************************************************
 *                       Global Variable                        *
 ***************************************************************/
 /* the color of the form. */
extern char** Line_arr;
/* array of pointer to point into the End of each line. */
extern char** End_of_Line;
/* array of pointer to point into the cursor position of each line. */
extern char** Current_Position;
/* color of the form. */
extern int color_g;
    /* */
extern int Last_Line;
/****************************************************************
 *                           Functions                          *
 ***************************************************************/
/****************************************************************
 * Function Name:	frame
 *
 * Description: 	to print frame of the user interface page.
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 ***************************************************************/
void frame(void)
{
    textattr(0x07);
    gotoxy(0,0);
    printf(" _______________________________________________________________________________\n");
    printf("|New            |Save           |Display        |Color          |Exit           |\n");
    printf("|_______________|_______________|_______________|_______________|_______________|\n");
    for(int i = 3; i < 40; i++)
    {
        gotoxy(0,i);
        printf("|");
        gotoxy(80,i);
        printf("|");
    }
    printf("\n|_______________________________________________________________________________|\n");

}
void frame_menu(void)
{
    textattr(0x07);
    gotoxy(0,1);
    printf("|New            |Save           |Display        |Color          |Exit           |\n");

}
/****************************************************************
 * Function Name:	Line_Size
 *
 * Description: 	static function print the highlighted area in
 *                  specific position in the console with specific
 *                  color.
 *
 * Inputs:			position x
 *                  position y
 *                  color
 *                  array to initialize it with spaces.
 *                  size of the array.
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 ***************************************************************/
static void Line_Size(int x, int y, int color, char * arr, int size)
{
    int Counter;
    gotoxy(x,y);
    textattr(color);
    /* for loop to full the line array with spaces */
    for(Counter = 0; Counter < size - 1; Counter++)
    {
        arr[Counter] = ' ';
        printf(" ");
    }
    /* put Null terminator to end the string */
    arr[Counter] = '\0';
}

/****************************************************************
 * Function Name:	Multi_Line_editor
 *
 * Description: 	make highlighted area to write in highlighted
 *                  Multi lines.
 *
 * Inputs:			Number of Lines.
 *                  Number of characters in each line.
 *                  x position for first line.
 *                  y position for first line.
 *                  state to know if i am in the writing mode
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 ***************************************************************/
void Multi_Line_editor(int LINE_SIZE_HER, int LINE_SIZE_VER, int Xpos, int Ypos, int state)
{
    /* used to shift lines when the user print enter. */
    int shift_counter = 0;
    /* buffer to get inserted char by user. */
    char Inserted_Char;
    /* buffer to get inserted character. */
    int exit = 0;
    /* variable to check if the cursor in the limited number of line. */
    int line_number = 0;
    /* array of pointer to point into the start of each line. */
    char** Start_position = malloc(LINE_SIZE_HER * sizeof(char*));
    /* array of pointer to point into the End of each line. */
    char** End_position = malloc(LINE_SIZE_HER * sizeof(char*));
    /* array of pointer to point into the end of the array in each line. */
    char** Terminator_position = malloc(LINE_SIZE_HER * sizeof(char*));
    /* pointer to hold the current position in the Delete and Backspace operations. */
    char* buffer;
     /* pointer to shift line. */
    char* shift_Line_arr;
    /* pointer to hold the end position of the shifted line. */
    char* shift_End_of_Line;
    /* pointer to hold the current position of the shifted line. */
    char* shift_Current_Position;
    /* pointer to hold the start position of the shifted line. */
    char* shift_Start_position;
    /* pointer to point into the End of the shifted line. */
    char* shift_End_position;
    /* pointer to point into the end of the shifted line. */
    char* shift_Terminator_position;


    /* for loop to allocate every line element in the memory if it is not allocated yet. */
    if(Line_arr == NULL)
     {
        /* pointer to array for each line */
        Line_arr = malloc(LINE_SIZE_HER * sizeof(char*));

        /* array of pointer to point into the end character in each line. */
        End_of_Line = malloc(LINE_SIZE_HER * sizeof(char*));
        /* array of pointer to point into the cursor position of each line. */
        Current_Position = malloc(LINE_SIZE_HER * sizeof(char*));
        /* allocate the memory for every line ad initialize the addresses of used pointers. */
        for(int i = 0; i < LINE_SIZE_HER; i++)
        {
            Line_arr[i] = malloc(sizeof(char) * LINE_SIZE_VER);
            Line_Size(Xpos, Ypos + i, color_g, Line_arr[i], LINE_SIZE_VER);
            End_of_Line[i] = Line_arr[i];
            Line_arr[i][LINE_SIZE_VER - 1] = '\0';
            Start_position[i] = Line_arr[i];
            Terminator_position[i] = &Line_arr[i][LINE_SIZE_VER - 1];
            End_position[i] = &Line_arr[i][LINE_SIZE_VER - 2];
            Current_Position[i] = Line_arr[i];
        }


     }
     /* just print lines on screen. */
     else
     {
         for(int i = 0; i < LINE_SIZE_HER; i++)
        {
            textattr(color_g);
            gotoxy(Xpos , Ypos + i);
            _cprintf("%s", Line_arr[i]);
            Line_arr[i][LINE_SIZE_VER - 1] = '\0';
            Start_position[i] = Line_arr[i];
            Terminator_position[i] = &Line_arr[i][LINE_SIZE_VER - 1];
            End_position[i] = &Line_arr[i][LINE_SIZE_VER - 2];
        }
     }
    do
    {
        /* start to print the highlighted word in the specific Location. */
        textattr(color_g);
        gotoxy(Xpos , Ypos + line_number);
        _cprintf("%s", Line_arr[line_number]);
        frame_menu();
        /* condition to move cursor with the letters in the current line. */
        if(Current_Position[line_number] == Line_arr[line_number])
           gotoxy(Xpos , Ypos + line_number);
        else if(Current_Position[line_number] < Terminator_position[line_number])
            gotoxy(Xpos + Current_Position[line_number] - Start_position[line_number], Ypos + line_number);
        else
            gotoxy(Xpos + LINE_SIZE_VER - 2, Ypos + line_number);
        /* get insertion from the user. */
        if(state == 0)
        {
            /* enable the cursor. */
            printf("\e[?25h");
            /* get the user pressed key. */
            Inserted_Char = getch();
            /* disable the cursor. */
            printf("\e[?25l");
        }
        else
            Inserted_Char = 9;

        /* If condition to Inserted_Character if the user inserted special Inserted_Chararacter or normal letter to display it. */
        if(Inserted_Char == -32)
        {
            Inserted_Char = getch();
            switch(Inserted_Char)
            {
                /* Go to the start of the current Line */
                case 71:
                    Current_Position[line_number] = Line_arr[line_number];
                    break;
                /* Go to the above Line */
                case 72:
                    line_number--;
                    /* stop the cursor in the start of the first line. */
                    if(line_number < 0)
                        line_number = 0;
                    else
                        /* go to the end character in the above line. */
                        Current_Position[line_number] = End_of_Line[line_number];
                    break;
                /* Go to the first Line */
                case 73:
                    line_number = 0;
                    /* go to the end character in the first line. */
                    Current_Position[line_number] = End_of_Line[line_number];
                    break;
                /* Move backward in the current line. */
                case 75:
                    Current_Position[line_number]--;
                    /* stop the cursor in the start of the highlighted area of the current line. */
                    if(Current_Position[line_number] < Line_arr[line_number])
                        Current_Position[line_number] = Line_arr[line_number];
                    break;
                /* Move forward in the current line. */
                case 77:
                    /* stop cursor at the end of the highlighted area in the current line. */
                    if(Current_Position[line_number] < End_of_Line[line_number])
                    {
                        Current_Position[line_number]++;
                    }
                    break;
                /* Go to the end character of the current line. */
                case 79:
                    if(End_of_Line[line_number] <= Terminator_position[line_number])
                        Current_Position[line_number] = End_of_Line[line_number];
                    break;
                /* Go to the under Line */
                case 80:
                    line_number++;
                    /* stop the cursor in the end line. */
                    if(line_number > Last_Line)
                        line_number = Last_Line;
                    else
                        /* go to the end character in the under line. */
                        Current_Position[line_number] = End_of_Line[line_number];
                    break;
                /* Go to the last Line */
                case 81:
                    line_number = Last_Line;
                    /* go to the end character in the last line. */
                    Current_Position[line_number] = End_of_Line[line_number];
                    break;
                /* Delete current character from insertion area. */
                case 83:
                    /* check if we are in the range of the highlighted area. */
                    if(Current_Position[line_number] >= Line_arr[line_number] && Current_Position[line_number] < End_position[line_number])
                    {
                        /* save the location to return to it */
                        buffer = Current_Position[line_number];
                        /* shafted all the string after remove the char. */
                        while(Current_Position[line_number] < End_position[line_number])
                        {

                           *Current_Position[line_number] = *(Current_Position[line_number] + 1);
                            Current_Position[line_number]++;
                        }
                        /* return to the position */
                        Current_Position[line_number] = buffer;
                        if(End_of_Line[line_number] == End_position[line_number])
                            *End_of_Line[line_number] = ' ';
                        /* update the location of the end of the line. */
                        if(Current_Position[line_number] < End_of_Line[line_number])
                            End_of_Line[line_number]--;
                    }
                    /* if we are in the limit of the highlighted area. */
                    else if(Current_Position[line_number] == End_position[line_number])
                    {
                        if(*Current_Position[line_number] != ' ')
                        *Current_Position[line_number] = ' ';
                    }
                    break;
            }
        }
        else
        {
            switch(Inserted_Char)
            {
                /* backspace Inserted_Character */
                case 8:
                    /* check if we are in the range of the highlighted area. */
                    if(Current_Position[line_number] > Line_arr[line_number] && Current_Position[line_number] < End_position[line_number])
                    {
                        /* save the location to return to it */
                        buffer = Current_Position[line_number] - 1;
                        /* shafted all the string after remove the char. */
                        while(Current_Position[line_number] < Terminator_position[line_number])
                        {

                           *(Current_Position[line_number] - 1) = *Current_Position[line_number];
                            Current_Position[line_number]++;
                        }
                        /* return to the position */
                        Current_Position[line_number] = buffer;
                        if(End_of_Line[line_number] == End_position[line_number])
                            *End_of_Line[line_number] = ' ';
                        /* update the location of the end of the line. */
                        End_of_Line[line_number]--;
                    }
                    /* if we are in the limit of the highlighted area. */
                    else if(Current_Position[line_number] == End_position[line_number])
                    {
                        if(*Current_Position[line_number] != ' ')
                        *Current_Position[line_number] = ' ';
                        else
                        {
                            Current_Position[line_number] = End_position[line_number] - 1;
                            End_of_Line[line_number] = End_position[line_number] - 1;
                            *Current_Position[line_number] = ' ';
                        }

                    }
                    /* if the line is empty and the user press backspace. */
                    else if (End_of_Line[line_number] == Line_arr[line_number])
                    {
                        shift_counter = line_number;
                        while(shift_counter != Last_Line)
                        {
                             /* shitt the content of the lines. */
                            shift_Line_arr = Line_arr[shift_counter];
                            Line_arr[shift_counter] = Line_arr[shift_counter + 1];
                            Line_arr[shift_counter + 1] = shift_Line_arr;
                            /* shift the end of the lines. */
                            shift_End_of_Line = End_of_Line[shift_counter];
                            End_of_Line[shift_counter] = End_of_Line[shift_counter + 1];
                            End_of_Line[shift_counter + 1] = shift_End_of_Line;
                            /* shift the current position of the lines. */
                            shift_Current_Position = Current_Position[shift_counter];
                            Current_Position[shift_counter] = Current_Position[shift_counter + 1];
                            Current_Position[shift_counter + 1] = shift_Current_Position;
                            /* shift the start of the lines. */
                            shift_Start_position = Start_position[shift_counter];
                            Start_position[shift_counter] = Start_position[shift_counter + 1];
                            Start_position[shift_counter + 1] = shift_Start_position;
                            /* shift the end of the lines. */
                            shift_End_position = End_position[shift_counter];
                            End_position[shift_counter] = End_position[shift_counter + 1];
                            End_position[shift_counter + 1] = shift_End_position;
                            /* shift the terminator of the lines. */
                            shift_Terminator_position = Terminator_position[shift_counter];
                            Terminator_position[shift_counter] = Terminator_position[shift_counter + 1];
                            Terminator_position[shift_counter + 1] = shift_Terminator_position;

                            shift_counter++;
                        }
                        /* print all lines again. */
                        for(int i = 0; i < LINE_SIZE_HER; i++)
                        {
                            textattr(color_g);
                            gotoxy(Xpos , Ypos + i);
                            _cprintf("%s", Line_arr[i]);
                        }
                        Last_Line--;
                        line_number--;
                    }
                    /* if the current position is the start of the line and the line is not empty so shift the remind of the line to above line. */
                    else if (End_of_Line[line_number] != Line_arr[line_number] && Current_Position[line_number] == Line_arr[line_number])
                    {
                        /* if the remind of line is less than the remind empty space of the above line. */
                        if(End_of_Line[line_number] - Line_arr[line_number] <= End_position[line_number - 1] - End_of_Line[line_number - 1])
                        {
                            for(int i = 0; i < End_of_Line[line_number] - Line_arr[line_number]; i++)
                            {
                                *End_of_Line[line_number - 1] = Line_arr[line_number][i];
                                Line_arr[line_number][i] = ' ';
                                End_of_Line[line_number - 1]++;
                            }
                            shift_counter = line_number;
                            while(shift_counter != Last_Line)
                            {
                                 /* shitt the content of the lines. */
                                shift_Line_arr = Line_arr[shift_counter];
                                Line_arr[shift_counter] = Line_arr[shift_counter + 1];
                                Line_arr[shift_counter + 1] = shift_Line_arr;
                                /* shift the end of the lines. */
                                shift_End_of_Line = End_of_Line[shift_counter];
                                End_of_Line[shift_counter] = End_of_Line[shift_counter + 1];
                                End_of_Line[shift_counter + 1] = shift_End_of_Line;
                                /* shift the current position of the lines. */
                                shift_Current_Position = Current_Position[shift_counter];
                                Current_Position[shift_counter] = Current_Position[shift_counter + 1];
                                Current_Position[shift_counter + 1] = shift_Current_Position;
                                /* shift the start of the lines. */
                                shift_Start_position = Start_position[shift_counter];
                                Start_position[shift_counter] = Start_position[shift_counter + 1];
                                Start_position[shift_counter + 1] = shift_Start_position;
                                /* shift the end of the lines. */
                                shift_End_position = End_position[shift_counter];
                                End_position[shift_counter] = End_position[shift_counter + 1];
                                End_position[shift_counter + 1] = shift_End_position;
                                /* shift the terminator of the lines. */
                                shift_Terminator_position = Terminator_position[shift_counter];
                                Terminator_position[shift_counter] = Terminator_position[shift_counter + 1];
                                Terminator_position[shift_counter + 1] = shift_Terminator_position;

                                shift_counter++;
                            }
                            /* print all lines again. */
                            for(int i = 0; i < LINE_SIZE_HER; i++)
                            {
                                textattr(color_g);
                                gotoxy(Xpos , Ypos + i);
                                _cprintf("%s", Line_arr[i]);
                            }
                            Last_Line--;
                            line_number--;
                        }
                        /* if the remind of line is more than the remind empty space of the above line. */
                        else
                        {
                            int i = 0;
                            int j = 0;
                            int limit = End_position[line_number - 1] - End_of_Line[line_number - 1];
                            for(; i < limit; i++)
                            {
                                *End_of_Line[line_number - 1] = Line_arr[line_number][i];
                                Line_arr[line_number][i] = ' ';
                                End_of_Line[line_number - 1]++;
                            }
                            *End_of_Line[line_number - 1] = Line_arr[line_number][i];
                            Line_arr[line_number][i] = ' ';
                            limit = End_of_Line[line_number] - Line_arr[line_number] + 1;
                            i++;
                            for(; i < limit; i++ , j++)
                            {
                                Line_arr[line_number][j] = Line_arr[line_number][i];
                                Line_arr[line_number][i] = ' ';
                            }
                            if(End_of_Line[line_number] < End_position[line_number])
                                End_of_Line[line_number] = &Line_arr[line_number][j - 1];
                            else
                                End_of_Line[line_number] = &Line_arr[line_number][j];
                            /* print all lines again. */
                            for(int i = 0; i < LINE_SIZE_HER; i++)
                            {
                                textattr(color_g);
                                gotoxy(Xpos , Ypos + i);
                                _cprintf("%s", Line_arr[i]);
                            }
                        }
                    }
                    break;
                /* Escape button to end the program. */
                case 9:
                    exit = 1;
                    break;
                /* enter option to go to the next line. */
                case 13:
                    /* check if we didn't get the last line in the page. */
                    if(Last_Line < LINE_SIZE_HER - 1)
                    {
                        Last_Line++;
                        line_number++;
                        shift_counter = Last_Line;
                        /* shift all lines to the next line to make the current line ready to write on it. */
                        while(shift_counter != line_number)
                        {
                             /* shitt the content of the lines. */
                            shift_Line_arr = Line_arr[shift_counter];
                            Line_arr[shift_counter] = Line_arr[shift_counter - 1];
                            Line_arr[shift_counter - 1] = shift_Line_arr;
                            /* shift the end of the lines. */
                            shift_End_of_Line = End_of_Line[shift_counter];
                            End_of_Line[shift_counter] = End_of_Line[shift_counter - 1];
                            End_of_Line[shift_counter - 1] = shift_End_of_Line;
                            /* shift the current position of the lines. */
                            shift_Current_Position = Current_Position[shift_counter];
                            Current_Position[shift_counter] = Current_Position[shift_counter - 1];
                            Current_Position[shift_counter - 1] = shift_Current_Position;
                            /* shift the start of the lines. */
                            shift_Start_position = Start_position[shift_counter];
                            Start_position[shift_counter] = Start_position[shift_counter - 1];
                            Start_position[shift_counter - 1] = shift_Start_position;
                            /* shift the end of the lines. */
                            shift_End_position = End_position[shift_counter];
                            End_position[shift_counter] = End_position[shift_counter - 1];
                            End_position[shift_counter - 1] = shift_End_position;
                            /* shift the terminator of the lines. */
                            shift_Terminator_position = Terminator_position[shift_counter];
                            Terminator_position[shift_counter] = Terminator_position[shift_counter - 1];
                            Terminator_position[shift_counter - 1] = shift_Terminator_position;

                            shift_counter--;
                        }
                        /* shift the remind of th current line to the next line. */
                        if(End_of_Line[line_number - 1] != End_position[line_number - 1])
                        {
                            while(Current_Position[line_number - 1] != End_of_Line[line_number - 1])
                            {
                                *Current_Position[line_number] = *Current_Position[line_number - 1];
                                *Current_Position[line_number - 1] = ' ';
                                Current_Position[line_number]++;
                                Current_Position[line_number - 1]++;
                            }
                            /* update the end of current line. */
                            End_of_Line[line_number - 1] -= Current_Position[line_number] - Start_position[line_number];
                            Current_Position[line_number - 1] = End_of_Line[line_number - 1];
                        }
                        else if(End_of_Line[line_number - 1] == End_position[line_number - 1] && Current_Position[line_number - 1] != End_of_Line[line_number - 1])
                        {
                            while(Current_Position[line_number - 1] <= End_of_Line[line_number - 1])
                            {
                                *Current_Position[line_number] = *Current_Position[line_number - 1];
                                *Current_Position[line_number - 1] = ' ';
                                Current_Position[line_number]++;
                                Current_Position[line_number - 1]++;
                            }
                            /* update the end of current line. */
                            End_of_Line[line_number - 1] -= Current_Position[line_number] - Start_position[line_number] - 1;
                            Current_Position[line_number - 1] = End_of_Line[line_number - 1];
                        }
                        /* update the end of next line. */
                        for(int j = 0; j < LINE_SIZE_VER - 1; j++)
                        {
                            if(Line_arr[line_number][j] != ' ')
                            {
                                if(&Line_arr[line_number][j] != End_position[line_number])
                                    End_of_Line[line_number] = &Line_arr[line_number][j] + 1;
                                else
                                    End_of_Line[line_number] = &Line_arr[line_number][j];
                            }
                        }
                        Current_Position[line_number] = Start_position[line_number];
                        /* print all lines again. */
                        for(int i = 0; i < LINE_SIZE_HER; i++)
                        {
                            textattr(color_g);
                            gotoxy(Xpos , Ypos + i);
                            _cprintf("%s", Line_arr[i]);
                        }

                    }
                    break;
                /* new Inserted_Character in the line. */
                default:
                    /* check if we are in the limit of the highlighted area. */
                    if(Current_Position[line_number] < End_position[line_number])
                    {
                        *Current_Position[line_number] = Inserted_Char;
                        Current_Position[line_number]++;
                    }
                    else
                    {
                        *Current_Position[line_number] = Inserted_Char;
                    }
                    break;

            }
            /* update the end of the line position */
            if(Current_Position[line_number] > End_of_Line[line_number])
            {
                End_of_Line[line_number] = Current_Position[line_number];
            }
        }
    }while(exit == 0);
    textattr(0x07);
    /* free allocated memory. */
    free(Start_position);
    free(End_position);
    free(Terminator_position);
}



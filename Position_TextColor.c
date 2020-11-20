/***************************************************************
 *
 * Name:                 Position_TextColor.c
 *
 * Last modification:    13/11/2020
 *
 * Description:          have functions to go to specific position
 *                       in the console and change the color and
 *                       highlighted area for the font.
 *
 *Author:                Ahmed Eldakhly.
 *
 ***************************************************************/

/****************************************************************
 *                       Includes Files                         *
 ***************************************************************/
#include <windows.h>    //  header file for gotoxy

/****************************************************************
 *                       Global Variable                        *
 ***************************************************************/
COORD coord = {0 , 0};

/****************************************************************
 *                           Functions                          *
 ***************************************************************/

/****************************************************************
 * Function Name:	gotoxy
 *
 * Description: 	make the console write on specific position.
 *
 * Inputs:			position x
 *                  position y
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 ***************************************************************/
void gotoxy(int x , int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , coord);
}

/****************************************************************
 * Function Name:	textattr
 *
 * Description: 	make the console write with specific color.
 *
 * Inputs:			color
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 ***************************************************************/
void textattr(int i)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , i);
}

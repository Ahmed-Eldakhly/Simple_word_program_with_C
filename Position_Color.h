/***************************************************************
 *
 * Name:                 Position_Color.h
 *
 * Last modification:    13/11/2020
 *
 * Description:          have the declaration of gotoxy function
 *                       and textattr function.
 *
 *Author:                Ahmed Eldakhly.
 *
 ***************************************************************/

#ifndef POSITION_COLOR_H_INCLUDED
#define POSITION_COLOR_H_INCLUDED

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
extern void gotoxy(int x , int y);

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
extern void textattr(int i);

#endif // POSITION_COLOR_H_INCLUDED

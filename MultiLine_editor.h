/***************************************************************
 *
 * Name:                     Line_Editor.h
 *
 * Last modification:        13/11/2020
 *
 * Description:              Line Editor deceleration functions.
 *
 * Author:                   Ahmed Eldakhly.
 *
 ***************************************************************/

#ifndef LINE_EDITOR_H_INCLUDED
#define LINE_EDITOR_H_INCLUDED

/****************************************************************
 *                           Functions                          *
 ***************************************************************/

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
extern void Multi_Line_editor(int LINE_SIZE_HER, int LINE_SIZE_VER, int Xpos, int Ypos, int state);
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
extern void frame(void);
void frame_menu(void);
#endif // LINE_EDITOR_H_INCLUDED

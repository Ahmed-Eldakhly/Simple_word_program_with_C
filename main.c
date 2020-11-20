/***************************************************************
 *
 * Name:                 main.c
 *
 * Last modification:    15/11/2020
 *
 * Description:          Bonus Project - full form page.
 *
 *Author:                Ahmed Eldakhly.
 *
 ***************************************************************/

/****************************************************************
 *                       Includes Files                         *
 ***************************************************************/
#include "Form.h"
/* the entry point. */
int main(void)
{
    /* open console with specific dimensions. */
    system("MODE CON COLS=100 LINES=150");
    /* disable the cursor. */
    printf("\e[?25l");
    Form_Page();
}

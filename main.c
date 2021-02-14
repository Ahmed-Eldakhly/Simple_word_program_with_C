
/****************************************************************
 *                          Definitions                         *
 ***************************************************************/
#define _WIN32_WINNT 0x0500

/****************************************************************
 *                       Includes Files                         *
 ***************************************************************/
#include <windows.h>
#include "Form.h"

/* the entry point. */
int main(void)
{
    /* Prevent resizing of console */
   HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    /* open console with specific dimensions. */
    system("MODE CON COLS=85 LINES=42");
    /* disable the cursor. */
    printf("\e[?25l");
    Form_Page();
}

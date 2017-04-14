#include "./includeGUI.h"
#include "./GUIUtils.h"

//this function appends a character to a string s
void append(char* s, char c)
{
    s[strlen(s)] = c;
    s[strlen(s)+1] = '\0';
}

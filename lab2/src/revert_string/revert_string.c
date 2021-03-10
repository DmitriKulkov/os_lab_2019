#include "revert_string.h"
#include "string.h"

void RevertString(char *str)
{
	int left,right;
    char buf;
    for(left=0, right=strlen(str)-1; left<right; left++, right--)
    {
        buf = *(str+left);
        *(str+left) = *(str+right);
        *(str+right) = buf;
    }
}


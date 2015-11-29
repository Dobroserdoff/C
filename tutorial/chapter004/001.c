#include <stdio.h>
#include <string.h>

#define MAX 100

int findpattern(char l[], char p[]);
void cutstr(char str[], int position, int patternlength);

main()
{
    int i, c, add, pos[MAX];
    char line[] = "What if hat is just a hat? Drop that!";
    char pattern[] = "hat";
    i = add = 0;
    pos[0] = -1;

    while ((c = findpattern(line, pattern)) > 0)
    {
        pos[i++] = c + add;
        cutstr(line, c, (int)(strlen(pattern)));
        add += c + ((int)(strlen(pattern)));
        pos[i] = 0;
    }

    if (pos[0] == -1)
        printf("Error: No matches");
    else
        for (i = 0; pos[i] != 0; i++)
            printf("%d ", pos[i]);
}

int findpattern(char l[], char p[])
{
    int i, j, flag;
    char control[strlen(p)];
    j = flag = 0;

    for (i = 0; i < strlen(p); i++)
        control[i] = 0;

    for (i = 0; i < strlen(l); i++)
        if (l[i] == p[j])
        {
            control[j++] = l[i];
            flag = 1;
        }
        else if (l[i] != p[j] && flag == 1)
        {
            control[j] = '\0';
            break;
        }
    
    if (strcmp(control, p) == 0)
        return (i - (int)(strlen(control)));
    else
        return 0;
}

void cutstr(char s[], int p, int n)
{
    int i;
    char temp[strlen(s)];

    for (i = 0; s[i + p + n] != '\0'; i++)
        temp[i] = s[i + p + n];
    temp[i] = '\0';

    for (i = 0; temp[i] != '\0'; i++)
        s[i] = temp[i];
    s[i] = '\0';
}

#include <iostream>

void RemoveDups(char *str)
{
    if (str[0] == '\0')
        return;
    int64_t left = 0;
    int64_t right = 1;
    while (str[right] != '\0')
    {
        if (str[left] != str[right])
        {
            str[++left] = str[right];
        }
        right++;
    }
    str[++left] = '\0';
}

int main()
{
    char data[] = "AAA BBB   AAA";
    RemoveDups(data);
    printf("\'%s\'\n", data); // "A B A"
    return 0;
}
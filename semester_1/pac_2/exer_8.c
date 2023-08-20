#include <stdio.h>
int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int d, m, y, k;
    fscanf(in, "%d %d %d %d", &d, &m, &y, &k);
    int days_before = d + 365 * (y - 1);
    int visokosn = y / 4 - y / 100 + y / 400;
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
        visokosn = y / 4 - y / 100 + y / 400 - 1;

    days_before += visokosn;
    //----------
    const int MONTHS[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int i = 0; i < m - 1; i++)
    {
        if (((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) && i == 1)
            days_before += 29;
        else
            days_before += MONTHS[i];
    }
    //-------------

    int days_after = days_before + k;
    int cur_year = 1;
    while (1)
    {
        if ((cur_year % 4 == 0 && cur_year % 100 != 0) || (cur_year % 400 == 0))
        {
            if (days_after <= 366)
                break;
            cur_year++;
            days_after -= 366;
        }
        else
        {
            if (days_after <= 365)
                break;
            cur_year++;
            days_after -= 365;
        }
    }
    int mont = 1;
    for (int i = 0; i < 11; i++)
    {
        if ((((cur_year % 4 == 0 && cur_year % 100 != 0) || (cur_year % 400 == 0)) && i == 1) && days_after > 29)
        {
            days_after -= 29;
            mont += 1;
        }
        else if (((i == 0) || (i == 2) || (i == 4) || (i == 6) || (i == 7) || (i == 9) || (i == 11)) && days_after > 31)
        {
            days_after -= 31;
            mont += 1;
        }
        else if (days_after > 28 && i == 1)
        {
            days_after -= 28;
            mont += 1;
        }
        else if (days_after > 30)
        {
            days_after -= 30;
            mont += 1;
        }
    }
    fprintf(out, "%d %d %d", days_after, mont, cur_year);
    //-----------
    //-----------
    fclose(in);
    fclose(out);
    return 0;
}
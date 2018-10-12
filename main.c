#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define key_left 68;
#define key_right 67;

//leap year?
int isleapyear(int year)
{
    if((year%4 == 0 && year%100 != 0 ) || (year%400 == 0))
        return 1;
    else
        return 0;
}

//calculate number of days of a month
int HowmanyDay(int month_num, int year)
{
    switch(month_num)
    {
        case 0:
            return 31;
        case 3:
            if(isleapyear(year))
                return 29;
            else
                return 28;
        case 6:
            return 31;
        case 9:
            return 30;
        case 12:
            return 31;
        case 15:
            return 30;
        case 18:
            return 31;
        case 21:
            return 31;
        case 24:
            return 30;
        case 27:
            return 31;
        case 30:
            return 30;
        case 33:
            return 31;    
    }           
}

//calculate the lap between two different months in one year
int calculatelap(int tomonth, int toyear)
{
    int fromyear = 2018;
    int fromi = 27;
    int count = 0;
    //count year's lap
    if(toyear - fromyear > 0)
    {
        count+=93;//the days left by 2018
        for(int i = 0; i < toyear - fromyear - 1; ++i)
        {
            if(isleapyear(fromyear + i + 1))
                count+=366;
            else
                count+=365;
        }
        for(int j = 0; j < tomonth+3; j+=3)
        {
            count+=HowmanyDay(j,toyear);
        }
        return count;
    } else if (toyear - fromyear == 0){
        if(tomonth>fromi)
        {
            count+=32;//the day left by Oct
            for(int i = 0; i < tomonth - fromi; i+=3)
            {
                count+=HowmanyDay(fromi + i + 3,toyear);
            }
            return count;
        } else if(tomonth==fromi){
            return 6;
        }else{
            count+=6;//the day went through by Oct
            for(int i = 0; i < fromi - tomonth; i+=3)
            {
                count+=HowmanyDay(fromi - i - 3,toyear);
            }
            return count;
        }
    } else if (toyear - fromyear < 0){
        count+=279;//the days went through by 2018
        for(int i = 0; i < fromyear - toyear - 1; ++i)
        {
            if(isleapyear(fromyear - i - 1))
                count+=366;
            else
                count+=365;
        }
        for(int j = 0; j < 33-tomonth+3; j+=3)
        {
            count+=HowmanyDay(33 - j,toyear);
        }
        return count;
    }
}

//determine the first day is which week
//base a certain date(Oct/1/2018 Mon)
int WhichdaytoWhichweek(int month_num, int year)
{
    if ((year>2018)||(year==2018&&month_num>27)){

        int a = 7 - (HowmanyDay(month_num, year) - (calculatelap(month_num,year)%7))%7;//turn the last day be the first day
        if(a == 7)
        {
            return 0;
        } else {
            return a;
        }        
    } else {
        int a = 7-calculatelap(month_num,year)%7;
        if(a == 7)
        {
            return 0;
        } else {
            return a;
        }
    }
}

//generate calendar as array form
void generateCalendar(int month_num, int year, int month_array[6][7])
{
    int row = 0;
    int column= WhichdaytoWhichweek(month_num,year);
    int howmanyDay = HowmanyDay(month_num,year);
    int dec = -1;
    int dec_lv2;
    int row_lv2;
    int column_lv2;
    if((year==2018&&month_num == 27)) {
        month_array[0][0] = 0;
        for(int j = 0; j<howmanyDay; ++j)
        {
            ++dec;
            month_array[row][column + dec] = j+1;
            if(column + dec == 6)
            {
                column = 0;
                dec = -1;
                ++row;
            }
        }
        dec_lv2 = dec;
        row_lv2 = row;
        column_lv2 = column;
        for(int m = 0; m< (5-row_lv2)*7+(6-column_lv2+dec_lv2); ++m)
        {
            ++dec;
            month_array[row][column + dec] = 0;
            if(column + dec == 6)
            {
                if(row == 5)
                {
                    return;
                }
                column = 0;
                dec = -1;
                ++row;
            }       
        }
    } else {
        for(int i = 0; i<column; ++i)
        {
            ++dec;
            month_array[0][column-dec-1] = 0;
        }
        dec=-1;
        for(int j = 0; j<howmanyDay; ++j)
        {
            ++dec;
            month_array[row][column + dec] = j+1;
            if(column + dec == 6)
            {
                column = 0;
                dec = -1;
                ++row;
            }
        }
        dec_lv2 = dec;
        row_lv2 = row;
        column_lv2 = column;
        for(int m = 0; m< (5-row_lv2)*7+(6-column_lv2+dec_lv2); ++m)
        {
            ++dec;
            month_array[row][column + dec] = 0;
            if(column + dec == 6)
            {
                if(row == 5)
                {
                    return;
                }
                column = 0;
                dec = -1;
                ++row;
            }       
        }       
    } 
}

//
void drawCalendar(int month_num, int year, int month_1[6][7], int month_2[6][7], int month_3[6][7])
{
    int row = 6;
    int column = 7;
    char month_string[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    printf("%41c%d%c\n\n",'[', year, ']');
    printf("%11c%c%c%29c%c%c%29c%c%c\n", month_string[month_num], month_string[month_num+1], month_string[month_num+2], month_string[month_num+3], month_string[month_num+4], month_string[month_num+5], month_string[month_num+6], month_string[month_num+7], month_string[month_num+8]);
    printf("Su||Mo||Tu||We||Th||Fr||Sa     Su||Mo||Tu||We||Th||Fr||Sa     Su||Mo||Tu||We||Th||Fr||Sa\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    
    for (int j = 0; j<row; ++j)
    {
        for(int k = 0; k<column; ++k)
        {
            if(month_1[j][k] == 0)
            {
            printf("%-4c",' ');
            }else {
                printf("%-4d",month_1[j][k]);
            }
        }
        printf("   ");//3 space
        for(int k = 0; k<column; ++k)
        {
            if(month_2[j][k] == 0)
            {
            printf("%-4c",' ');
            }else {
                printf("%-4d",month_2[j][k]);
            }
        }
        printf("   ");
        for(int k = 0; k<column; ++k)
        {
            if(month_3[j][k] == 0)
            {
            printf("%-4c",' ');
            }else {
                printf("%-4d",month_3[j][k]);
            }
        }
        printf("\n");
    }
    printf("\npress key 'a' or key 'd' to change calendar\n");

}

//
void keyboardEvent(int month_num, int year, int month_1[6][7], int month_2[6][7], int month_3[6][7])
{
    while(1)
    {
	switch(getch())
	{
	    case 'key_right':
                if(month_num<27)
                {
                    month_num+=9;
                    generateCalendar(month_num,year,month_1);
                    generateCalendar(month_num+3,year,month_2);
                    generateCalendar(month_num+6,year,month_3);                    
                    system("cls");
                    drawCalendar(month_num, year, month_1, month_2, month_3);
                }else {
                    month_num = 0;
                    year+=1;
                    generateCalendar(month_num,year,month_1);
                    generateCalendar(month_num+3,year,month_2);
                    generateCalendar(month_num+6,year,month_3); 
                    system("cls");
                    drawCalendar(month_num, year, month_1, month_2, month_3);
                }
		break;
            case 'key_left':
                if(month_num>=9)
                {
                    month_num-=9;
                    generateCalendar(month_num,year,month_1);
                    generateCalendar(month_num+3,year,month_2);
                    generateCalendar(month_num+6,year,month_3); 
                    system("cls");
                    drawCalendar(month_num, year, month_1, month_2, month_3);
                }else {
                    month_num = 27;
                    year-=1;
                    generateCalendar(month_num,year,month_1);
                    generateCalendar(month_num+3,year,month_2);
                    generateCalendar(month_num+6,year,month_3); 
                    system("cls");
                    drawCalendar(month_num, year, month_1, month_2, month_3);
                }                
	}
    }
}

int main()
{
    //variable
    int row = 6;
    int column = 7;
    int year = 2018;
    int month_num = 27;
    int month_1[row][column];
    int month_2[row][column];
    int month_3[row][column];
    //generateCalendar
    generateCalendar(month_num,year,month_1);
    generateCalendar(month_num+3,year,month_2);
    generateCalendar(month_num+6,year,month_3);    
    //
    drawCalendar(month_num, year, month_1, month_2, month_3);
    //cant use define
    keyboardEvent(month_num, year, month_1, month_2, month_3);
    return 0;
}
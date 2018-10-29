#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define KNOWN_YEAR 2018
#define KNOWN_MONTH 10
#define KNOWN_DATE 1
#define KNOW_WEEK_DAY 1

int isleapyear(int year)
{
    if((year%4 == 0 && year%100 != 0 ) || (year%400 == 0))
        return 1;
    else
        return 0;
}

//calculate number of days of a month
int howManyDay(int month_num, int year)
{
    int month_array[] = {31,0,31,30,31,30,31,31,30,31,30,31};
    if(month_num == 2){
        if(isleapyear(year)){
            return 29;
        } else{
            return 28;
        }
    } else{
        return month_array[month_num-1];
    }
}

//calculate the lap between two different months in one year
//base on a certain date(Oct/1/2018 Mon)
int calculateDistance(int to_month, int to_year)
{
    int distance = 0;
    if(to_year - KNOWN_YEAR > 0)
    {
        for(int i = KNOWN_MONTH; i < 13; ++i){
            distance+=howManyDay(i,KNOWN_YEAR);
        }
        for(int i = 0; i < to_year - KNOWN_YEAR - 1; ++i)
        {
            if(isleapyear(KNOWN_YEAR + i + 1))
                distance+=366;
            else
                distance+=365;
        }
        for(int j = 1; j < to_month; ++j)
        {
            distance+=howManyDay(j,to_year);
        }
    } else if (to_year - KNOWN_YEAR == 0){
        if(to_month>KNOWN_MONTH)
        {
            distance+=(howManyDay(KNOWN_MONTH,KNOWN_YEAR));
            for(int i = 1; i < to_month - KNOWN_MONTH; ++i)
            {
                distance+=howManyDay(KNOWN_MONTH + i,to_year);
            }
        } else if(to_month==KNOWN_MONTH){
            distance = 0;
        }else{
            for(int i = 1; i < KNOWN_MONTH - to_month + 1; ++i)
            {
                distance-=howManyDay(KNOWN_MONTH - i,to_year);
            }
        }
    }  else if (to_year - KNOWN_YEAR < 0){
        for(int i = KNOWN_MONTH - 1; i > 0; --i){
            distance -= howManyDay(i,KNOWN_YEAR);
        }
        for(int i = 0; i < KNOWN_YEAR - to_year - 1; ++i)
        {
            if(isleapyear(KNOWN_YEAR - i - 1))
                distance-=366;
            else
                distance-=365;
        }
        for(int j = 0; j < 12-to_month+1; ++j)
        {
            distance-=howManyDay(12 - j,to_year);
        }
    }
    return distance; 
}

int determineTheFirstDayIsWhichWeekDay(int to_month, int to_year)
{
    int distance = calculateDistance(to_month, to_year) + KNOW_WEEK_DAY;
    while(distance<0){
        distance+=7;
    }
    return distance%7;
}

void printMonths(int how_many_months_on_a_row, int month_num, int year){
    char month_string[][4]={"NAN","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    char week_string[][3]={"Su","Mo","Tu","We","Th","Fr","Sa"};
    
    if(how_many_months_on_a_row == 3){
        //print year
        printf("%41c%d%c\n\n",'[', year, ']');

        //print months
        printf("%10c",' ');
        printf(month_string[month_num]);
        printf("%28c",' ');
        printf(month_string[month_num+1]);
        printf("%28c",' ');
        printf(month_string[month_num+2]);
        printf("\n");

        //print week days
        for(int i = 0;i<21;++i)//7 days for 3 months
        {
            if(i == 6||i == 13)//last day
            {
                printf(week_string[i%7]);
                printf("     ");
            } else if(i == 20){//last day
                printf(week_string[i%7]);
                printf("\n");
            }else {
            printf(week_string[i%7]);
            printf("--");
            }
        }

        //print spacer '~'
        for(int i = 0; i<88; ++i)
        {
            printf("~");
        }
        printf("\n");        
    } else if(how_many_months_on_a_row == 1){
        //print year
        printf("%9c",' ');
        printf("%c%d%c\n\n",'[', year, ']');

        //print month
        printf("%10c",' ');
        printf(month_string[month_num]);
        printf("\n");

        //print week days
        for(int i = 0;i<7;++i)
        {
            if(i == 6)
            {
                printf(week_string[i]);
            } else{
                printf(week_string[i]);
                printf("--"); 
            }  
        }
        printf("\n");

        //print spacer '~'
        for(int i = 0; i<26; ++i)
        {
            printf("~");
        }
        printf("\n");
    }
    int firstday_is_whichweek[3];//不可以直接花括号//c语言，栈必须确认分配大小
    firstday_is_whichweek[0] = determineTheFirstDayIsWhichWeekDay(month_num,year);
    firstday_is_whichweek[1] = determineTheFirstDayIsWhichWeekDay(month_num+1,year);
    firstday_is_whichweek[2] = determineTheFirstDayIsWhichWeekDay(month_num+2,year);
    int howmany_day[3];
    howmany_day[0] = howManyDay(month_num,year);
    howmany_day[1] = howManyDay(month_num+1,year);
    howmany_day[2] = howManyDay(month_num+2,year);
    int leftday[3];
    for(int row = 0; row<6; ++row){//6 rows
        for(int m = 0; m<how_many_months_on_a_row; ++m){
            for(int d = 0; d<7; ++d){//7 days
                if(row == 0){
                    if(d >= firstday_is_whichweek[m])
                        printf("%-4d",d - firstday_is_whichweek[m] + 1);
                    else
                        printf("%-4c",' ');  
                    leftday[m] = d - firstday_is_whichweek[m] + 1;
                } else{
                    if(leftday[m] <howmany_day[m])
                    {
                        ++leftday[m];
                        printf("%-4d",leftday[m]);
                    } else{
                        printf("%-4c",' ');     
                    }
                }
            }
            if (m < how_many_months_on_a_row-1)
                printf("   ");
        }
        printf("\n");
    }
    if(how_many_months_on_a_row == 3){
        printf("%s\n","press 'a' or 'd' to roll");
        printf("%s\n","press 'w' to change mode");        
    }else if(how_many_months_on_a_row == 1){
        printf("%s\n","press 's' to search");
        printf("%s\n","press 'w' to change mode");        
    }
}

void keyboardEvent_search();    
void keyboardEvent_roll(int month_num, int year)
{  
    while(1)
    {
	switch(getch())
	{
	    case 'd':
                if(month_num<10)
                {
                    month_num+=3;                  
                    system("cls");
                    printMonths(3,month_num, year);
                }else {
                    month_num = 1;
                    year+=1;
                    system("cls");
                    printMonths(3,month_num, year);
                }
		break;
            case 'a':
                if(month_num>=4)
                {
                    month_num-=3;
                    system("cls");
                    printMonths(3,month_num, year);
                }else {
                    month_num = 10;
                    year-=1;
                    system("cls");
                    printMonths(3,month_num, year);
                } 
                break;
            case 'w':
                keyboardEvent_search();
                break;
	}
    }
}

void keyboardEvent_search()
{
    int year_search;
    int month_search;    
    system("cls");
    printf("%s\n","press 's' to search");
    while(1)
    {
	switch(getch())
	{
	    case 's':
                system("cls");
                printf("please enter year: ");
                scanf("%d", &year_search);
                printf("please enter month: ");
                scanf("%d", &month_search);   
                system("cls");
                printMonths(1,month_search, year_search);
		break;
            case 'w':
                while((month_search-1)%3 != 0){
                    ++month_search;
                }
                if(month_search == 13)//override
                {
                    month_search = 10;
                }
                system("cls");
                printMonths(3,month_search, year_search);
                keyboardEvent_roll(month_search, year_search);
                break;                
	}
    }
}

int main()
{
    printMonths(3,KNOWN_MONTH, KNOWN_YEAR);
    keyboardEvent_roll(KNOWN_MONTH, KNOWN_YEAR);
    return 0;
}
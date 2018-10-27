#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define KNOWN_YEAR 2019
#define KNOWN_MONTH 10
#define KNOWN_DATE 1
#define KNOW_WEEK_DAY 2

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
int calculatelap(int to_month, int to_year)
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
        distance += KNOW_WEEK_DAY;
    } else if (to_year - KNOWN_YEAR == 0){
        if(to_month>KNOWN_MONTH)
        {
            distance+=(howManyDay(KNOWN_MONTH,KNOWN_YEAR));
            for(int i = 1; i < to_month - KNOWN_MONTH; ++i)
            {
                distance+=howManyDay(KNOWN_MONTH + i,to_year);
            }
            distance += KNOW_WEEK_DAY;
        } else if(to_month==KNOWN_MONTH){
            distance += KNOW_WEEK_DAY;
        }else{
            for(int i = 1; i < KNOWN_MONTH - to_month + 1; ++i)
            {
                distance-=howManyDay(KNOWN_MONTH - i,to_year);
            }
            distance += KNOW_WEEK_DAY;
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
        distance += KNOW_WEEK_DAY;
    }
    return distance; 
}

int determineTheFirstDayIsWhichWeekDay(int to_month, int to_year)
{
    int distance = calculatelap(to_month, to_year);
    if(distance>=0)
    {
        return distance%7;
    } else{
        while(distance<0){
            distance+=7;
        }
        return distance%7;
    }
}
//
void drawThreeMonths(int month_num, int year)
{
    int month_1_FirstDay_WhichWeek = determineTheFirstDayIsWhichWeekDay(month_num,year);
    int month_2_FirstDay_WhichWeek = determineTheFirstDayIsWhichWeekDay(month_num+1,year);
    int month_3_FirstDay_WhichWeek = determineTheFirstDayIsWhichWeekDay(month_num+2,year);
    int month_1_howManyDay = howManyDay(month_num,year);
    int month_2_howManyDay = howManyDay(month_num+1,year);
    int month_3_howManyDay = howManyDay(month_num+2,year);
    int month_1_left;
    int month_2_left;
    int month_3_left;
    
    char month_string[][4]={"NAN","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    char week_string[][3]={"Su","Mo","Tu","We","Th","Fr","Sa"};
    
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

    //print date
    for(int i = 0; i<23; ++i)//7 days for 3 weeks, and 2 spaces
    {
        if(i<=6)
        {
            if(i >= month_1_FirstDay_WhichWeek)
                printf("%-4d",i - month_1_FirstDay_WhichWeek + 1);
            else
                printf("%-4c",' ');
            month_1_left = i - month_1_FirstDay_WhichWeek + 1;
        } else if(i==7){
            printf("   ");//space
        } else if(i>=8&&i<=14){
            if(i - 8 >= month_2_FirstDay_WhichWeek)
                printf("%-4d",i - 8 - month_2_FirstDay_WhichWeek + 1);
            else
                printf("%-4c",' ');
            month_2_left = i - 8 - month_2_FirstDay_WhichWeek + 1;
        } else if(i==15){
            printf("   ");
        } else if(i>=16&&i<=22){
            if(i - 16 >= month_3_FirstDay_WhichWeek)
                printf("%-4d",i - 16 - month_3_FirstDay_WhichWeek + 1);
            else
                printf("%-4c",' ');
            month_3_left = i - 16 - month_3_FirstDay_WhichWeek + 1;
        }
    }
    
    printf("\n");
    
    for(int i = 0; i<23; ++i)
    {
        if(i<=6)
        {
            ++month_1_left;
            printf("%-4d",month_1_left);
        } else if(i==7){
            printf("   ");
        } else if(i>=8&&i<=14){
            ++month_2_left;
            printf("%-4d",month_2_left);
        } else if(i==15){
            printf("   ");
        } else if(i>=16&&i<=22){
            ++month_3_left;
            printf("%-4d",month_3_left);
        }
    }
  
    printf("\n");    
    
    for(int i = 0; i<23; ++i)
    {
        if(i<=6)
        {
            ++month_1_left;
            printf("%-4d",month_1_left);
        } else if(i==7){
            printf("   ");
        } else if(i>=8&&i<=14){
            ++month_2_left;
            printf("%-4d",month_2_left);
        } else if(i==15){
            printf("   ");
        } else if(i>=16&&i<=22){
            ++month_3_left;
            printf("%-4d",month_3_left);
        }
    }
    
    printf("\n");

    for(int i = 0; i<23; ++i)
    {
        if(i<=6)
        {
            ++month_1_left;
            printf("%-4d",month_1_left);
        } else if(i==7){
            printf("   ");
        } else if(i>=8&&i<=14){
            ++month_2_left;
            printf("%-4d",month_2_left);
        } else if(i==15){
            printf("   ");
        } else if(i>=16&&i<=22){
            ++month_3_left;
            printf("%-4d",month_3_left);
        }
    }
    
    printf("\n");
    
    for(int i = 0; i<23; ++i)
    {
        if(i<=6 && month_1_left <month_1_howManyDay)
        {
            ++month_1_left;
            printf("%-4d",month_1_left);
        } else if(i<=6 && month_1_left >= month_1_howManyDay){
            printf("%-4c",' ');
        }else if(i==7){
            printf("   ");
        } else if(i>=8&&i<=14 && month_2_left < month_2_howManyDay){
            ++month_2_left;
            printf("%-4d",month_2_left);
        } else if(i>=8&&i<=14 && month_2_left >= month_2_howManyDay){
            printf("%-4c",' ');
        } else if(i==15){
            printf("   ");
        } else if(i>=16&&i<=22 && month_3_left < month_3_howManyDay){
            ++month_3_left;
            printf("%-4d",month_3_left);
        } else if(i>=16&&i<=22 && month_3_left >= month_3_howManyDay){
            printf("%-4c",' ');
        }
    }

    printf("\n");

    for(int i = 0; i<23; ++i)
    {
        if(i<=6 && month_1_left <month_1_howManyDay)
        {
            ++month_1_left;
            printf("%-4d",month_1_left);
        } else if(i<=6 && month_1_left >= month_1_howManyDay){
            printf("%-4c",' ');
        }else if(i==7){
            printf("   ");
        } else if(i>=8&&i<=14 && month_2_left < month_2_howManyDay){
            ++month_2_left;
            printf("%-4d",month_2_left);
        } else if(i>=8&&i<=14 && month_2_left >= month_2_howManyDay){
            printf("%-4c",' ');
        } else if(i==15){
            printf("   ");
        } else if(i>=16&&i<=22 && month_3_left < month_3_howManyDay){
            ++month_3_left;
            printf("%-4d",month_3_left);
        } else if(i>=16&&i<=22 && month_3_left >= month_3_howManyDay){
            printf("%-4c",' ');
        }
    }
    
    printf("\n");
    
    printf("%s\n","press 'a' or 'd' to roll");
    printf("%s\n","press 'q' to change mode");      
}

void drawOneMonth(int month_num, int year)
{
    int month_1_FirstDay_WhichWeek = determineTheFirstDayIsWhichWeekDay(month_num,year);
    int month_1_howManyDay = howManyDay(month_num,year);
    int month_1_left;
    
    char month_string[][4]={"NAN","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    char week_string[][3]={"Su","Mo","Tu","We","Th","Fr","Sa"};
    
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

    //print date
    for(int i = 0; i<7; ++i)
    {
        if(i >= month_1_FirstDay_WhichWeek)
            printf("%-4d",i - month_1_FirstDay_WhichWeek + 1);
        else
            printf("%-4c",' ');
        month_1_left = i - month_1_FirstDay_WhichWeek + 1;
    }
    
    printf("\n");
    
    for(int i = 0; i<7; ++i)
    {
        ++month_1_left;
        printf("%-4d",month_1_left);
    }
  
    printf("\n");    
    
    for(int i = 0; i<7; ++i)
    {
        ++month_1_left;
        printf("%-4d",month_1_left);
    }
    
    printf("\n");

    for(int i = 0; i<7; ++i)
    {
        ++month_1_left;
        printf("%-4d",month_1_left);
    }
    
    printf("\n");
    
    for(int i = 0; i<7; ++i)
    {
        if(month_1_left <month_1_howManyDay)
        {
            ++month_1_left;
            printf("%-4d",month_1_left);
        } else if(month_1_left >= month_1_howManyDay){
            printf("%-4c",' ');
        }
    }

    printf("\n");

    for(int i = 0; i<7; ++i)
    {
        if(month_1_left <month_1_howManyDay)
        {
            ++month_1_left;
            printf("%-4d",month_1_left);
        } else if(month_1_left >= month_1_howManyDay){
            printf("%-4c",' ');
        }
    }
    
    printf("\n");
    
    printf("%s\n","press 's' to search");
    printf("%s\n","press 'q' to change mode");    
}
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
                    drawThreeMonths(month_num, year);
                }else {
                    month_num = 1;
                    year+=1;
                    system("cls");
                    drawThreeMonths(month_num, year);
                }
		break;
            case 'a':
                if(month_num>=4)
                {
                    month_num-=3;
                    system("cls");
                    drawThreeMonths(month_num, year);
                }else {
                    month_num = 10;
                    year-=1;
                    system("cls");
                    drawThreeMonths(month_num, year);
                } 
                break;
            case 'q':
                keyboardEvent_search();
                break;
	}
    }
}

void keyboardEvent_search(int month_num, int year)
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
                drawOneMonth(month_search, year_search);
		break;
            case 'q':
                while((month_search-1)%3 != 0){
                    ++month_search;
                }
                if(month_search == 13)//override
                {
                    month_search = 10;
                }
                system("cls");
                drawThreeMonths(month_search, year_search);
                keyboardEvent_roll(month_search, year_search);
                break;                
	}
    }
}

int main()
{
    drawThreeMonths(KNOWN_MONTH, KNOWN_YEAR);
    keyboardEvent_roll(KNOWN_MONTH, KNOWN_YEAR);
    return 0;
}
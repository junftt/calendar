#include <stdio.h>
#include <stdlib.h>

#include <termios.h>
#include <unistd.h>

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

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
        case 1:
            return 31;
        case 2:
            if(isleapyear(year))
                return 29;
            else
                return 28;
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;    
    }           
}

//calculate the lap between two different months in one year
int calculatelap(int to_month, int to_year)
{
    #define KNOWN_YEAR 2018
    #define KNOWN_MONTH 10
    #define KNOWN_DATE 1
    #define KNOW_WEEK_DAY 1
    int distance = 0;

    if(to_year - KNOWN_YEAR > 0)
    {
        distance+=(HowmanyDay(KNOWN_MONTH,KNOWN_YEAR)+HowmanyDay(KNOWN_MONTH+1,KNOWN_YEAR)+HowmanyDay(KNOWN_MONTH+2,KNOWN_YEAR)+1);//the days left by 2018
        for(int i = 0; i < to_year - KNOWN_YEAR - 1; ++i)
        {
            if(isleapyear(KNOWN_YEAR + i + 1))
                distance+=366;
            else
                distance+=365;
        }
        for(int j = 1; j < to_month; ++j)
        {
            distance+=HowmanyDay(j,to_year);
        }
        return distance; 
    } else if (to_year - KNOWN_YEAR == 0){
        if(to_month>KNOWN_MONTH)
        {
            distance+=(HowmanyDay(KNOWN_MONTH,KNOWN_YEAR)+1);//the day left by Oct
            for(int i = 1; i < to_month - KNOWN_MONTH; ++i)
            {
                    distance+=HowmanyDay(KNOWN_MONTH + i,to_year);
            }
            return distance;
        } else if(to_month==KNOWN_MONTH){
            return 6;
        }else{
            distance+=6;//the day went through by Oct
            for(int i = 1; i < KNOWN_MONTH - to_month + 1; ++i)
            {
                distance+=HowmanyDay(KNOWN_MONTH - i,to_year);
            }
            return distance;
        }
    }  else if (to_year - KNOWN_YEAR < 0){
        distance+=(HowmanyDay(KNOWN_MONTH-1,KNOWN_YEAR)+HowmanyDay(KNOWN_MONTH-2,KNOWN_YEAR)+HowmanyDay(KNOWN_MONTH-3,KNOWN_YEAR)+HowmanyDay(KNOWN_MONTH-4,KNOWN_YEAR)+HowmanyDay(KNOWN_MONTH-5,KNOWN_YEAR)+HowmanyDay(KNOWN_MONTH-6,KNOWN_YEAR)+HowmanyDay(KNOWN_MONTH-7,KNOWN_YEAR)+HowmanyDay(KNOWN_MONTH-8,KNOWN_YEAR)+HowmanyDay(KNOWN_MONTH-9,KNOWN_YEAR)+6);;//the days went through by 2018
        for(int i = 0; i < KNOWN_YEAR - to_year - 1; ++i)
        {
            if(isleapyear(KNOWN_YEAR - i - 1))
                distance+=366;
            else
                distance+=365;
        }
        for(int j = 0; j < 12-to_month+1; ++j)
        {
            distance+=HowmanyDay(12 - j,to_year);
        }
        return distance;
    }
}

//determine the first day is which week
//base a certain date(Oct/1/2018 Mon)
int determineTheFirstDayIsWhichWeek(int to_month, int to_year)
{
    int a;
    if((to_year  > KNOWN_YEAR) || (to_year == KNOWN_YEAR&&to_month > KNOWN_MONTH))
    {
        a = calculatelap(to_month,to_year)%7;
        return a;
    } else{
        a = 7-calculatelap(to_month,to_year)%7;
        return a;
    }
}

//
void drawCalendar(int month_num, int year)
{
    int month_1_FirstDay_WhichWeek = determineTheFirstDayIsWhichWeek(month_num,year);
    int month_2_FirstDay_WhichWeek = determineTheFirstDayIsWhichWeek(month_num+1,year);
    int month_3_FirstDay_WhichWeek = determineTheFirstDayIsWhichWeek(month_num+2,year);
    int month_1_HowmanyDay = HowmanyDay(month_num,year);
    int month_2_HowmanyDay = HowmanyDay(month_num+1,year);
    int month_3_HowmanyDay = HowmanyDay(month_num+2,year);
    int month_1_left;
    int month_2_left;
    int month_3_left;
    
    char month_string[][4]={"NAN","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    char week_string[][3]={"Su","Mo","Tu","We","Th","Fr","Sa"};
    
    printf("%41c%d%c\n\n",'[', year, ']');
    
    printf("%10c",' ');
    printf(month_string[month_num+1]);
    printf("%28c",' ');
    printf(month_string[month_num+2]);
    printf("%28c",' ');
    printf(month_string[month_num+3]);
    printf("\n");
    
    for(int i = 0;i<21;++i)
    {
        if(i == 6||i == 13)
        {
            printf(week_string[i%7]);
            printf("     ");
        } else if(i == 20){
            printf(week_string[i%7]);
            printf("\n");
        }else {
        printf(week_string[i%7]);
        printf("--");
        }
    }
    
    for(int i = 0; i<88; ++i)
    {
        printf("~");
    }
    printf("\n");

    for(int i = 0; i<23; ++i)
    {
        if(i<=6)
        {
            if(i >= month_1_FirstDay_WhichWeek)
                printf("%-4d",i - month_1_FirstDay_WhichWeek + 1);
            else
                printf("%-4c",' ');
            month_1_left = i - month_1_FirstDay_WhichWeek + 1;
        } else if(i==7){
            printf("   ");
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
        if(i<=6 && month_1_left <month_1_HowmanyDay)
        {
            ++month_1_left;
            printf("%-4d",month_1_left);
        } else if(i<=6 && month_1_left >= month_1_HowmanyDay){
            printf("%-4c",' ');
        }else if(i==7){
            printf("   ");
        } else if(i>=8&&i<=14 && month_2_left < month_2_HowmanyDay){
            ++month_2_left;
            printf("%-4d",month_2_left);
        } else if(i>=8&&i<=14 && month_2_left >= month_2_HowmanyDay){
            printf("%-4c",' ');
        } else if(i==15){
            printf("   ");
        } else if(i>=16&&i<=22 && month_3_left < month_3_HowmanyDay){
            ++month_3_left;
            printf("%-4d",month_3_left);
        } else if(i>=16&&i<=22 && month_3_left >= month_3_HowmanyDay){
            printf("%-4c",' ');
        }
    }

    printf("\n");

    for(int i = 0; i<23; ++i)
    {
        if(i<=6 && month_1_left <month_1_HowmanyDay)
        {
            ++month_1_left;
            printf("%-4d",month_1_left);
        } else if(i<=6 && month_1_left >= month_1_HowmanyDay){
            printf("%-4c",' ');
        }else if(i==7){
            printf("   ");
        } else if(i>=8&&i<=14 && month_2_left < month_2_HowmanyDay){
            ++month_2_left;
            printf("%-4d",month_2_left);
        } else if(i>=8&&i<=14 && month_2_left >= month_2_HowmanyDay){
            printf("%-4c",' ');
        } else if(i==15){
            printf("   ");
        } else if(i>=16&&i<=22 && month_3_left < month_3_HowmanyDay){
            ++month_3_left;
            printf("%-4d",month_3_left);
        } else if(i>=16&&i<=22 && month_3_left >= month_3_HowmanyDay){
            printf("%-4c",' ');
        }
    }
    
    printf("\n");
    
}

//
void keyboardEvent(int month_num, int year)
{
    while(1)
    {
	switch(getch())
	{
	    case 'd':
                if(month_num<10)
                {
                    month_num+=3;                  
                    system("clear");
                    drawCalendar(month_num, year);
                }else {
                    month_num = 1;
                    year+=1;
                    system("clear");
                    drawCalendar(month_num, year);
                }
		break;
            case 'a':
                if(month_num>=4)
                {
                    month_num-=3;
                    system("clear");
                    drawCalendar(month_num, year);
                }else {
                    month_num = 10;
                    year-=1;
                    system("clear");
                    drawCalendar(month_num, year);
                }                
	}
    }
}

int main()
{
    //variable
    int year = 2018;
    int month_num = 10;
    //
    drawCalendar(month_num, year);
    //cant use define
    keyboardEvent(month_num, year);
    return 0;
}
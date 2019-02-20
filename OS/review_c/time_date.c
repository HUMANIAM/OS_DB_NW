// Time and date in c

# include <stdio.h>
# include <stdlib.h>
#include  <stdbool.h>
#include <time.h>

void time_date(){
    time_t secs = time(NULL);
    printf(ctime(&secs));
}

void make_time(){
    struct tm str_time;

    str_time.tm_year = 2019-1900;
    str_time.tm_mon = 5;
    str_time.tm_mday = 0;
    str_time.tm_hour = 10;
    str_time.tm_min = 3;
    str_time.tm_sec = 5;
    str_time.tm_isdst = 1;

    time_t time_of_day = mktime(&str_time);
    printf(ctime(&time_of_day));
}

void measure_time(){
    time_t start = time(NULL);

    volatile long unsigned counter = 1;
    while(counter > 0 && counter < 10000000000){
        counter++;
    }

    time_t end = time(NULL);
    float exe_time = difftime(end, start);

    printf("execution time = %f\n", exe_time);

}


void time_zone(){
    time_t raw_time;
    #define PST 2

    time ( &raw_time );

    //convert calender time to UTC time
    struct tm *ptr_ts = gmtime ( &raw_time );

    printf ("Time Cairo: %2d:%02d\n",
         (ptr_ts->tm_hour+PST)%12, ptr_ts->tm_min);

}


void wait(long double ticks){
    ////returns the number of clock ticks elapsed since the program was launched.
    clock_t end_time = clock() + ticks;
    while(clock() < end_time);

    // ticks per second = CLOCKS_PER_SEC = 1000000

}

//main function
int main(){
//    time_date();
//    make_time();
//    measure_time();
//      time_zone();
       double w = 10000000;
//     printf("%d\n", CLOCKS_PER_SEC);
    printf("wait %ld secs\n",(int) w/CLOCKS_PER_SEC);
    wait(w);
        printf("hello");
   return 0;
}


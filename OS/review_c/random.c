// Time and date in c

# include <stdio.h>
# include <stdlib.h>
#include  <stdbool.h>
#include <time.h>

void create_random_numbers(int n, int from, int to){
    //seeding the random generator
    srand(time(NULL));

    int i = 0;
    int d = to - from + 1;
    while(i++ < n){
        printf("%d ", from + rand()%d);
    }
}

//main function
int main(){
    create_random_numbers(50, 1, 5);
   return 0;
}


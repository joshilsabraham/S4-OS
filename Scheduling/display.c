#include <stdio.h>
#include <time.h>
#include <unistd.h>
int main() {
    time_t now; //time_t is a data type used to represent calendar time.
    time(&now);  //Stores the current calendar time (seconds since the Unix Epoch) into the variable now.
    printf("Current system time: %s", ctime(&now));  // Converts the calendar time stored in now into a human-readable string.
sleep(30);
    return 0;
}

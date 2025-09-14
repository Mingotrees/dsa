/*
*
* An Exercise from Sir Gran Called Managing Flights with Dynamic Array
* This is version 3 of the array implementation
*
* Programmer: Jhanell R. Mingo 
* Created: 09/14/2025
* Last Updated: 09/14/2025 @ 10:26PM
*
*/

typedef struct{
    int hours;
    int minutes;
}Time;

typedef struct{
    int id;
    char origin[50];
    char destination[50];
    Time departure_time;
    Time arrival_time;
}Flight;

typedef struct{
    Flight *flights;
    int count;
    int max;
}Flights;


Flight createFlight(Flight);
void addFlight(Flights* flight_list); //return flight with id-1 if not found
Flight removeFlight(Flights* flight_list, int flight_id);
void showFlights(Flight fligh_list);
void displayFlightInfo(Flight f);
void display_time(Time t); // in format HH:MM:XX
Time createTime(int h, int m);
void initialize(Flights*);


int main(){

}
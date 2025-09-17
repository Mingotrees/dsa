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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


Flight createFlight(int id, Time departTime, Time arrivalTime, char destination[], char origin[]);
void addFlight(Flights* flight_list, Flight f);
Flight removeFlight(Flights* flight_list, int flight_id);
void showFlights(Flights fligh_list);
void displayFlightInfo(Flight f);
void display_time(Time t); // in format HH:MM:XX
Time createTime(int h, int m);
void initialize(Flights*);


int main(){
    Flights cebuPacific;
    initialize(&cebuPacific);
    Time depart = createTime(10, 2);
    Time arrival = createTime(5,2);
    Flight new = createFlight(1, depart, arrival, "PHIL", "USA");
    addFlight(&cebuPacific, new);
    addFlight(&cebuPacific, new);
    addFlight(&cebuPacific, new);
    addFlight(&cebuPacific, new);
    addFlight(&cebuPacific, new);
    addFlight(&cebuPacific, new);
    addFlight(&cebuPacific, new);
    showFlights(cebuPacific);
    Flight deletedFlight = removeFlight(&cebuPacific, 2);

}

void initialize(Flights* A){
    A->max = 5;
    A->count = 0;
    A->flights = (Flight*)malloc(sizeof(Flight)*A->max);    
}



Flight createFlight(int id, Time departTime, Time arrivalTime, char destination[], char origin[])
{
    Flight newTime = {id, .departure_time = {departTime.hours, departTime.minutes}, .arrival_time = {arrivalTime.hours, arrivalTime.minutes}};
    strcpy(newTime.origin, origin);
    strcpy(newTime.destination, destination);
    return newTime;
}


void addFlight(Flights* flight_list, Flight f){
    if(flight_list->count == flight_list->max){
        flight_list->max *= 2;
        flight_list->flights = realloc(flight_list->flights, sizeof(Flight)*flight_list->max);
    }
    flight_list->flights[flight_list->count++] = f;
}

Flight removeFlight(Flights* flight_list, int flight_id){
    Flight dummy = {-1, "not found", "not found", {-1, -1}, {-1, -1}};
    int ndx;
    for(ndx = 0; ndx < flight_list->count && flight_list->flights[ndx].id != flight_id; ndx++){}
    if(ndx < flight_list->count){
        flight_list->count--;
        dummy = flight_list->flights[ndx];
        for(;ndx < flight_list->count; ndx++){
            flight_list->flights[ndx] = flight_list->flights[ndx + 1]; 
        }
    }

    return dummy;
}

void showFlights(Flights flight_list){
    printf("=================FLIGHTS====================\n");
    for(int ndx = 0; ndx < flight_list.count; ndx++){
        displayFlightInfo(flight_list.flights[ndx]);
        printf("\n");
    }
}

void displayFlightInfo(Flight f){
    printf("FLIGHT ID: %d\n", f.id);
    printf("%s -> %s\n", f.origin, f.destination);
    printf("DEPARTURE TIME: ");
    display_time(f.departure_time);
    printf("ARRIVAL TIME: ");
    display_time(f.arrival_time);
}

void display_time(Time t){
    printf("%s%d:%s%d%s %s\n" , t.hours > 9 ? "" : "0", t.hours, t.minutes > 9 ? "" : "0", t.minutes, ":00" ,(t.hours > 12) ? "PM" : "AM");
} 

Time createTime(int h, int m){
    Time new = {h, m};
    return new;
}
#include <stdio.h>
#define ELECTRICITY_RATE 18


int main(){
    double water = 0, oldElectricity = 0, currentElectricity = 0, rent = 0, totalElectricity = 0;
    int input = 1;
    do{
        printf("Enter old: ");
        scanf("%lf", &oldElectricity);
        printf("Enter new: ");
        scanf("%lf", &currentElectricity);
        totalElectricity = currentElectricity - oldElectricity;
        printf("Electricity: %lf\n", totalElectricity);
        totalElectricity *= ELECTRICITY_RATE;
        printf("Electrcity Payment: %lf\n", totalElectricity);
        printf("Enter water: ");
        scanf("%lf", &water);
        printf("Enter rent: ");
        scanf("%lf", &rent);
        printf("Total Balance Due: %lf\n", totalElectricity + water + rent);
        printf("Calculate another one?: ");
        scanf("%d", &input);

    }while(input > 0);
}
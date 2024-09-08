#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_FLOORS 10
void shiftFloorUnit(int *floorUnit, bool goingUp) {
    if (goingUp) {
        *floorUnit <<= 1;
    } else {
        *floorUnit >>= 1;
    }
}
int performANDOperation(int floorUnit, int callUnit) {
    return floorUnit & callUnit;
}
int main() {
    int currentFloor, destinationFloor, elevatorPosition;
    char direction, continueChoice;
    int floorUnit = 1;
    int upCallUnit = 0, downCallUnit = 0;
    printf("Enter the initial elevator position (1-%d): ", MAX_FLOORS);
    scanf("%d", &elevatorPosition);
    while (1) {
        printf("Enter your current floor (1-%d): ", MAX_FLOORS);
        scanf("%d", &currentFloor);
        printf("Enter 'u' for up or 'd' for down: ");
        scanf(" %c", &direction);
        printf("Enter your destination floor (1-%d): ", MAX_FLOORS);
        scanf("%d", &destinationFloor);
        if (direction == 'u') {
            upCallUnit = 1 << (destinationFloor - 1);
        } else {
            downCallUnit = 1 << (destinationFloor - 1);
        }
        floorUnit = 1 << (elevatorPosition - 1);
        printf("\nElevator movement:\n");
        printf("Elevator is currently at floor: %d\n", elevatorPosition);
        printf("User is at floor: %d\n", currentFloor);
        while (elevatorPosition != currentFloor) {
            bool goingUp = currentFloor > elevatorPosition;
            if (goingUp) {
                printf("Elevator goes up\n");
                elevatorPosition++;
            } else {
                printf("Elevator goes down\n");
                elevatorPosition--;
            }
            shiftFloorUnit(&floorUnit, goingUp);
        }
        printf("Elevator arrives at user's floor: %d\n", currentFloor);
        while (currentFloor != destinationFloor) {
            bool goingUp = destinationFloor > currentFloor;
            if (goingUp) {
                printf("Elevator goes up\n");
                currentFloor++;
                elevatorPosition++;
                shiftFloorUnit(&floorUnit, true);
                if (performANDOperation(floorUnit, upCallUnit) > 0) {
                    printf("Elevator stops at floor %d\n", currentFloor);
                }
            } else {
                printf("Elevator goes down\n");
                currentFloor--;
                elevatorPosition--;
                shiftFloorUnit(&floorUnit, false);
                if (performANDOperation(floorUnit, downCallUnit) > 0) {
                    printf("Elevator stops at floor %d\n", currentFloor);
                }
            }
        }
        printf("Elevator stops and eliminates response signal\n");
        printf("You have reached your destination: Floor %d\n", destinationFloor);
        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &continueChoice);
        if (continueChoice != 'y' && continueChoice != 'Y') {
            break;
        }
    }
    printf("Elevator program terminated.\n");
    return 0;
}
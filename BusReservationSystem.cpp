#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 10
#define MAX_INPUT_LENGTH 100
#define MAX_NAME_LENGTH 50

typedef struct {
    int seatNumber;
    char passengerName[MAX_NAME_LENGTH];
    int isReserved;
} Seat;

typedef struct {
    int busNumber;
    int numSeats;
    Seat *seats;
} Bus;

void initializeBusSeats(Bus *bus) {
    bus->seats = (Seat *)malloc(bus->numSeats * sizeof(Seat));
    if (bus->seats == NULL) {
        printf("Memory allocation failed for bus %d.\n", bus->busNumber);
        exit(1);
    }
    for (int i = 0; i < bus->numSeats; i++) {
        bus->seats[i].seatNumber = i + 1;
        strcpy(bus->seats[i].passengerName, "");
        bus->seats[i].isReserved = 0;
    }
}

void displayAvailableSeats(Bus *bus) {
    printf("\nAvailable Seats for Bus %d:\n", bus->busNumber);
    int count = 0;
    int numColumns = 3;
    int seatsPerColumn = bus->numSeats / numColumns;

    for (int i = 0; i < bus->numSeats; i++) {
        if (bus->seats[i].isReserved == 0) {
            printf("%d ", bus->seats[i].seatNumber);
            count++;
            if (count % seatsPerColumn == 0) {
                printf("\n");
            }
        }
    }

    if (count % seatsPerColumn != 0) {
        printf("\n");
    }

    if (count == 0) {
        printf("No seats are available.\n");
    }
}

void reserveSeat(Bus *bus) {
    char input[MAX_INPUT_LENGTH];
    int seatNum;
    printf("\nEnter seat number to reserve (Bus %d): ", bus->busNumber);
    fgets(input, MAX_INPUT_LENGTH, stdin);
    if (sscanf(input, "%d", &seatNum) != 1 || seatNum < 1 || seatNum > bus->numSeats) {
        printf("Invalid seat number.\n");
        return;
    }
    if (bus->seats[seatNum - 1].isReserved == 1) {
        printf("Seat already reserved.\n");
        return;
    }
    printf("Enter passenger name: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    sscanf(input, "%[^\n]", bus->seats[seatNum - 1].passengerName);
    bus->seats[seatNum - 1].isReserved = 1;
    printf("Seat reserved successfully.\n");
}

void cancelReservation(Bus *bus) {
    char input[MAX_INPUT_LENGTH];
    int seatNum;
    printf("\nEnter seat number to cancel reservation (Bus %d): ", bus->busNumber);
    fgets(input, MAX_INPUT_LENGTH, stdin);
    if (sscanf(input, "%d", &seatNum) != 1 || seatNum < 1 || seatNum > bus->numSeats) {
        printf("Invalid seat number.\n");
        return;
    }
    if (bus->seats[seatNum - 1].isReserved == 0) {
        printf("Seat is not reserved.\n");
        return;
    }
    strcpy(bus->seats[seatNum - 1].passengerName, "");
    bus->seats[seatNum - 1].isReserved = 0;
    printf("Reservation cancelled successfully.\n");
}

void displayAllReservations(Bus *bus) {
    printf("\nAll Reservations for Bus %d:\n", bus->busNumber);
    int count = 0;
    for (int i = 0; i < bus->numSeats; i++) {
        if (bus->seats[i].isReserved == 1) {
            printf("Seat Number: %d, Passenger Name: %s\n", bus->seats[i].seatNumber, bus->seats[i].passengerName);
            count++;
        }
    }
    if (count == 0) {
        printf("No seats are reserved.\n");
    }
}

int main() {
    int numBuses = 10;
    int busChoice, choice;
    int numSeatsPerBus = 30;
    char input[MAX_INPUT_LENGTH];
    Bus buses[MAX_BUSES];

    // Initialize all buses
    for (int i = 0; i < numBuses; i++) {
        buses[i].busNumber = i + 1;
        buses[i].numSeats = numSeatsPerBus;
        initializeBusSeats(&buses[i]);
    }

    // Main menu loop
    do {
        printf("\nBus Reservation System Menu:\n");
        printf("1. Select a bus\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        fgets(input, MAX_INPUT_LENGTH, stdin);
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                // Bus selection loop
                do {
                    printf("\nEnter bus number (1-10) or 0 to exit: ");
                    fgets(input, MAX_INPUT_LENGTH, stdin);
                    if (sscanf(input, "%d", &busChoice) != 1) {
                        printf("Invalid bus number.\n");
                        continue;
                    }

                    // Exit bus selection if the user enters 0
                    if (busChoice == 0) {
                        printf("Returning to main menu...\n");
                        break;
                    }

                    // Check if the bus choice is valid
                    if (busChoice < 1 || busChoice > numBuses) {
                        printf("Invalid bus number.\n");
                        continue;
                    }

                    // Bus-specific menu loop
                    do {
                        printf("\nBus %d Menu:\n", busChoice);
                        printf("1. Display Available Seats\n");
                        printf("2. Reserve a Seat\n");
                        printf("3. Cancel Reservation\n");
                        printf("4. Display All Reservations\n");
                        printf("0. Back to Bus Selection\n");
                        printf("Enter your choice: ");
                        fgets(input, MAX_INPUT_LENGTH, stdin);
                        if (sscanf(input, "%d", &choice) != 1) {
                            printf("Invalid input. Please enter a number.\n");
                            continue;
                        }

                        switch (choice) {
                            case 1:
                                displayAvailableSeats(&buses[busChoice - 1]);
                                break;
                            case 2:
                                reserveSeat(&buses[busChoice - 1]);
                                break;
                            case 3:
                                cancelReservation(&buses[busChoice - 1]);
                                break;
                            case 4:
                                displayAllReservations(&buses[busChoice - 1]);
                                break;
                            case 0:
                                printf("Returning to bus selection...\n");
                                break;
                            default:
                                printf("Invalid choice. Please try again.\n");
                        }
                    } while (choice != 0);

                } while (busChoice != 0);

                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    // Free dynamically allocated memory for seats
    for (int i = 0; i < numBuses; i++) {
        free(buses[i].seats);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_BUSES 10          // Maximum number of buses in the system
#define MAX_INPUT_LENGTH 100   // Maximum length of user input strings
#define MAX_NAME_LENGTH 50    // Maximum length of a passenger's name

// Structure to represent a seat on a bus
typedef struct {
    int seatNumber;          // Seat number
    char passengerName[MAX_NAME_LENGTH];  // Passenger's name (empty if not reserved)
    int isReserved;          // 1 if reserved, 0 if not
} Seat;

// Structure to represent a bus
typedef struct {
    int busNumber;       // Bus number
    int numSeats;        // Total number of seats on the bus
    Seat *seats;         // Pointer to an array of Seat structures
} Bus;

// Function to initialize the seats of a bus
void initializeBusSeats(Bus *bus) {
    // Dynamically allocate memory for the seats array
    bus->seats = (Seat *)malloc(bus->numSeats * sizeof(Seat));
    // Check if memory allocation was successful
    if (bus->seats == NULL) {
	printf("Memory allocation failed for bus %d.\n", bus->busNumber);
	exit(1); // Exit the program if memory allocation fails
    }
    // Initialize each seat
    for (int i = 0; i < bus->numSeats; i++) {
	bus->seats[i].seatNumber = i + 1;       // Assign seat number
	strcpy(bus->seats[i].passengerName, ""); // Initialize passenger name to empty string
	bus->seats[i].isReserved = 0;            // Set initial reservation status to not reserved
    }
}

// Function to display available seats on a bus
void displayAvailableSeats(Bus *bus) {
    printf("\nAvailable Seats for Bus %d:\n", bus->busNumber);
    int count = 0; // Counter for available seats

    // Calculate the number of columns needed for better visualization
    int numColumns = 3; // Adjust this number as needed
    int seatsPerColumn = bus->numSeats / numColumns;

    for (int i = 0; i < bus->numSeats; i++) {
	// Check if the seat is not reserved
	if (bus->seats[i].isReserved == 0) {
	    printf("%d ", bus->seats[i].seatNumber);
	    count++;

	    // Print a newline after every 'seatsPerColumn' seats
	    if (count % seatsPerColumn == 0) {
		printf("\n");
	    }
	}
    }

    // Print any remaining seats on the last line
    if (count * seatsPerColumn != 0) {
	printf("\n");
    }

    if (count == 0) { // Handle case where no seats are available
	printf("No seats are available.\n");
    }
}
// Function to reserve a seat on a bus
void reserveSeat(Bus *bus) {
    char input[MAX_INPUT_LENGTH]; // Buffer to store user input
    int seatNum; // Variable to store the seat number
    printf("\nEnter seat number to reserve (Bus %d): ", bus->busNumber);
    fgets(input, MAX_INPUT_LENGTH, stdin); // Read input from user
    // Check for valid input and seat number
    if (sscanf(input, "%d", &seatNum) != 1 || seatNum < 1 || seatNum > bus->numSeats) {
	printf("Invalid seat number.\n");
	return; //Exit function if input is invalid
    }
    // Check if seat is already reserved
    if (bus->seats[seatNum - 1].isReserved == 1) {
	printf("Seat already reserved.\n");
	return; //Exit function if seat is already reserved
    }
    printf("Enter passenger name: ");
    fgets(input, MAX_INPUT_LENGTH, stdin); //Read passenger name
    sscanf(input, "%[^\n]", bus->seats[seatNum - 1].passengerName); //Store passenger name (remove trailing newline)
    bus->seats[seatNum - 1].isReserved = 1; // Mark the seat as reserved
    printf("Seat reserved successfully.\n");
}

// Function to cancel a seat reservation
void cancelReservation(Bus *bus) {
    char input[MAX_INPUT_LENGTH]; //Buffer to store user input
    int seatNum; //Variable to store seat number
    printf("\nEnter seat number to cancel reservation (Bus %d): ", bus->busNumber);
    fgets(input, MAX_INPUT_LENGTH, stdin); //Read user input
    //Check for valid input and seat number
    if (sscanf(input, "%d", &seatNum) != 1 || seatNum < 1 || seatNum > bus->numSeats) {
	printf("Invalid seat number.\n");
	return; //Exit if input is invalid
    }
    //Check if seat is already reserved
    if (bus->seats[seatNum - 1].isReserved == 0) {
	printf("Seat is not reserved.\n");
	return; //Exit if seat is not reserved
    }
    strcpy(bus->seats[seatNum - 1].passengerName, ""); // Clear passenger name
    bus->seats[seatNum - 1].isReserved = 0;           // Mark seat as not reserved
    printf("Reservation cancelled successfully.\n");
}


// Function to display all reservations on a bus
void displayAllReservations(Bus *bus) {
    printf("\nAll Reservations for Bus %d:\n", bus->busNumber);
    int count = 0; //Counter for reserved seats
    for (int i = 0; i < bus->numSeats; i++) {
	// Check if the seat is reserved
	if (bus->seats[i].isReserved == 1) {
	    printf("Seat Number: %d, Passenger Name: %s\n", bus->seats[i].seatNumber, bus->seats[i].passengerName);
	    count++; //Increment counter if seat is reserved
	}
    }
    if (count == 0) { //Handle case where no seats are reserved
	printf("No seats are reserved.\n");
    }
}

int main() {
    int numBuses = 10;          // Number of buses
    int busChoice, choice;     // Variables to store user choices
    int numSeatsPerBus = 30; // Number of seats per bus
    char input[MAX_INPUT_LENGTH]; // Buffer for user input
    Bus buses[MAX_BUSES];      // Array to store bus information

    //clrscr();//clears the screen

    // Initialize all buses
    for (int i = 0; i < numBuses; i++) {
	buses[i].busNumber = i + 1; // Assign bus number
	buses[i].numSeats = numSeatsPerBus;      // Set number of seats per bus
	initializeBusSeats(&buses[i]); // Initialize seats for each bus
    }

    // Main menu loop
    do {
	printf("\nBus Reservation System Menu:\n");
	printf("1. Select a bus\n");
	printf("0. Exit\n");
	printf("Enter your choice: ");

	fgets(input, MAX_INPUT_LENGTH, stdin); // Read user input
	// Check for valid integer input
	if (sscanf(input, "%d", &choice) != 1) {
	    printf("Invalid input. Please enter a number.\n");
	    continue; // Go to the next iteration of the loop
	}

	switch (choice) {
	    case 1:
		// Bus selection loop
		do {
		    printf("\nEnter bus number (1-10) or 0 to exit: ");
		    fgets(input, MAX_INPUT_LENGTH, stdin); // Read user input
		    // Check for valid bus number
		    if (sscanf(input, "%d", &busChoice) != 1) {
			printf("Invalid bus number.\n");
			continue; // Go to the next iteration
		    }

		    // Exit bus selection if the user enters 0
		    if (busChoice == 0) {
			printf("Returning to main menu...\n");
			break; // Exit the inner loop
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
			printf("0. Back to Bus Selection\n"); // Option to go back to bus selection
			printf("Enter your choice: ");
			fgets(input, MAX_INPUT_LENGTH, stdin); //Read user input
			//Check for valid integer input
			if (sscanf(input, "%d", &choice) != 1) {
			    printf("Invalid input. Please enter a number.\n");
			    continue; // Go to the next iteration
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
				break; // Go back to bus selection
			    default:
				printf("Invalid choice. Please try again.\n");
			}
		    } while (choice != 0);

		} while (busChoice != 0); // Continue bus selection loop if choice is 0 (back to bus selection)

		break;
	    case 0:
		printf("Exiting...\n");
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 0);

    // Free dynamically allocated memory for seats
    for (int j = 0; j < numBuses; j

    ++) {
	free(buses[j].seats);
    }
    getch();//shows the output
    return 0;
}
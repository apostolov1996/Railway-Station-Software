#include <stdio.h>
#include <string.h>
#include <math.h>
#define D_CHAR 50
#define N_STATIONS 10
#define N_USERS 100

/* Software with the next functions 
1) Nearest Station; with no considerations about the real path
2) Nearest Train;
3) Minimum waiting time; 
to calcolate it i have to consider the schedule, and make the differenze betwean the schedule time, the actual time, and eventualy i have to
sum the delay
4) Destinations included in my railway pass paiment;
5) Cost of the rail_pass according to the zone;
6) Schedule time of the trains on every single station, according to their final destination 
7) Delays;

*/



typedef struct {
	float x;
	float y;
	float z;
}Coordinates;

/* This type of information, has to be stored in a static database. From this database the software is going to obtain the
information needed. This database has to be structured on a way that considers the next data information
name, city, zone, coordinates, destinations (arrivals and departures),
also train schedule and time organisation */

/* Zone separation - this type of information is going to be used for the taxe calculations. We are going to devide the territory on this way:
1) Central Zone: 1
2) Periphery Zone: 2
3) Province Zone: 3
4) Ecc..
*/
typedef struct {
	char name[D_CHAR];
	char city[D_CHAR];         /* General information about the stations, this one has to be stored into the databes */
	int zone;
	Coordinates coord;
}Station;

typedef struct {
	Station your_station;
	Station destination[N_STATIONS];
	int departure_time[48][2];   /* If we have one train on every 30 mins */
	int arrival_time[48][2];
}Destination;

typedef struct {
	char name[D_CHAR];
	int id_number;
	Station destination;
	Coordinates coord;    /* I have to update them on real time, we need to track them with some type of GPS system */
	int arrival_time[1][1];
	int departure_time[1][1];
	int delay[1][1];
}Train;

typedef struct {
	int id_number;                     /* If the user id is 0, that means that the database is empty, and we have no information about this user */
	char name[D_CHAR];
	char password[D_CHAR];             /* I can use this empty database folder to insert new data */
	int rail_pass_payment;
	Coordinates position; /* I have to track them with the gps function of the phone */
}User;

int main () {
	/* GENERAL DECLARATIONS */
	char username[D_CHAR];
	char password [D_CHAR];
	int user_controll;
	int password_controll;
	int i;
	int choise;
	int k;
	int personal_id;
	int turn_back=0;
	int turn_back_menu;
	float distance;
	float min=1000000000000;
	int id_station;
	User user[N_USERS];
	Station station[N_STATIONS];
	
	printf("Your personal train application:");
	printf("\n__________________________________________________________\n");
	/*TEST*/
	for(i=0; i<N_USERS; i=i+1) {
		user[i].id_number=-1;
	}
	/* ACCESS FUNCTION */
	do {
	   /* REGISTER OR LOG IN */
	   printf("1) Log in\n");
	   printf("2) New registration\n");
	   printf("Operation requested: ");
	   scanf("%d", &choise);
	   printf("\n__________________________________________________________\n");
	   if (choise==2) {
		   printf("New registration form:");
		   /* Searching an empty database storage */
		   k=0;
		   for (i=0; i<N_USERS; i=i+1) {
			   if (user[i].id_number!=-1) {
			    	k=k+1;
			    } else {
				  i=N_USERS;
			    }
		    }
		    printf("\n__________________________________________________________\n");
		    printf("Empty storage number: %d\n", k);
		    printf("Initial id number: %d\n", user[k].id_number);
		    printf("Insert username: ");
		    scanf("%s", user[k].name);
		    printf("Insert password: ");
		    scanf("%s", user[k].password);
		    printf("Insert rail pass payment: ");
		    scanf("%d", &user[k].rail_pass_payment);
		    /* The software has to output the username personal id */
		    user[k].id_number=k;
	    } else {
		    printf("Insert username: ");
		    scanf("%s", username);
		    printf("Insert password: ");
		    scanf("%s", password);
		    printf("\n__________________________________________________________\n");
		    /* Controll of the user and password data */
		    for (i=0; i<N_USERS; i=i+1) {
			    user_controll=strcmp(username, user[i].name);
			    password_controll=strcmp(password, user[i].password);
			    if (user_controll==0 && password_controll==0) {
				   printf("The data inserted is correct\n");
				   printf("Your personal id is: %d\n", user[i].id_number);
				   personal_id=user[i].id_number;
				   i=N_USERS;
			    } else {
				}
		    }
			if (user_controll==0 && password_controll==0) {
				printf("Wait while we are elaborating your personal menu\n");
			} else {
				printf("The username or the password is not correct! Please try again.\n");
			} 
	    }
	    printf("\n__________________________________________________________\n");
	    printf("If you want to turn back, please press 0, \nif you want to exit press 1, \nif you want to continue press 2 (this one is available only if you are logged in)");
	    printf("\nOperation requested: ");
	    scanf("%d", &turn_back);
    } while (turn_back==0);
	
	/* After the successfull log in, the software can show out the menu interface */
	if (turn_back==2 && user_controll==0 && password_controll==0) {
		do {
	       printf("\n__________________________________________________________\n");
	       /* The user now have to choose from the general menu */
	       printf("                        MENU");
	       printf("\n__________________________________________________________\n\n");
	       printf("1) View your rail pass payments.\n");
	       printf("2) Insert new payment.\n");
	       printf("3) Find the nearest station.\n");
	       printf("4) Schedule time of the trains\n");
	       printf("5) EXIT");
	       printf("\nOperation requested: ");
	       scanf("%d", &choise);
	       printf("\n__________________________________________________________\n");
	       if (choise==1) {
	       	printf("Your rail pass payments are: %d\n", user[personal_id].rail_pass_payment);
		   } else if (choise==2) {
		   	printf("Insert your new rail pass payment: ");
		   	scanf("%d", &user[personal_id].rail_pass_payment);
		   	printf("\n__________________________________________________________\n");
		   	printf("Your updated rail pass payments are: %d", user[personal_id].rail_pass_payment);
		   } else if (choise==3) {
		   	/* FOR THIS FUNCTION I NEED INFORMATION ABOUT THE STATIONS AND THEIR COORDINATES
		   	SAME INFORMATION IS NEEDED ABOUT THE USER, I NEED TO LINK THE SOFTWARE WITH GPS SYSTEMS */
		   	 for (i=0; i<N_STATIONS; i=i+1) {
		   	 	distance=sqrt(pow((user[personal_id].position.x - station[i].coord.x), 2) + pow((user[personal_id].position.y - station[i].coord.y), 2) + pow((user[personal_id].position.z-station[i].coord.z), 2));
		   	 	if (min>distance) {
		   	 		min=distance;
		   	 		id_station=i;
					} else {
					}
				}
				printf("\n__________________________________________________________\n");
				printf("The nearest station is:");
				printf("Name: %s", station[id_station].name);
				printf("City: %s", station[id_station].city);
				printf("Zone: %d\n", station[id_station].zone);	 
				printf("Distance: %.2f", distance);
		   } else if (choise==4) {
		   	/* ON WORK */
		   } else if (choise==5) {
		   	turn_back_menu=1;
		   	turn_back=1;
		   } else {
		   }
		   printf("\n__________________________________________________________\n");
	       printf("If you want to turn back, please press 0, \nif you want to exit press 1.");
	       printf("\nOperation requested: ");
	       scanf("%d", &turn_back_menu);
		} while (turn_back_menu==0);
		printf("See you soon:");
	} else {
		printf("See you soon:");
	}
	getch();
	return 0;
	
}




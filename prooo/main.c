#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//  G00361128      @  GMIT.IE
//  AUTHOR         :  TOMAS O'MALLEY 
//  PROGRAM        :  ABC-DENTAL DATABASE
//  WEIGHTING      :  40%
//  DUE DATE       :  FRIDAY 26TH OF APRIL 2019

//users log Details 
typedef struct 
{
	char username[6];
	char password[6];
	struct login* NEXT;
};

struct node {
	//variable declaration for l8inked list 
	int PPSnum;
	char Fname[20];
	char Surname[20];
	int yearBorn;
	int gender;
	char emailAdd[40];
	char nextOfKinName[20];
	int lastAppointment;
	double weight;
	double height;
	char Allergies[1];
	int option;
	int result;
	int howManyCigarettesSmoked;
	int howManyDrinksPerWeek;
	int howOftenDoYouExcercise;

	struct node* NEXT;
};
//functions decalartiion
//---------------------

//linked list function 
void AddElementAtStart(struct node** top);

// display all patients in list
void DisplayList(struct node* top);

//Auhtenticates/validates  the users sign in information 
int verifyLogin();

//save the file after user entered all details
void saveFile(struct node* headptr);

//load data  saved from patientsFile
void loadfile(struct node** headptr);

//Update patient found in the
void updatePatient(struct node* top);

//allow the user to search for a specific patient in the file 
void SearchPatient(struct node* top);

//Ouputs the users data to a report  File 
void outputReport(struct node* headptr);

void main() {

	struct node* headPtr = NULL;
	FILE* filep;//initlize file
	int choice;
	int n = 0;
	int i;
	int numRead;

	char fileUser[10];
	char filePass[10];

	printf("================LOAD FILE===============\n");
	loadfile(&headPtr);
	printf("======================================\n");

	printf("======================================\n");
	printf("ABC Dental Practice Ltd\n");
	printf("======================================\nlogin details\n");

	//open and read file for read
	filep = fopen("log.txt", "r");

	//display all the users passwords/usernames for testing purposes 
	while (!feof(filep))
	{
		//read users input  from file
		numRead = fscanf(filep, "%s %s ", fileUser, filePass);
		//read only the two variables
		if (numRead == 2)
		{
			//display to the screen
			printf("The userName is %s, The password  is %s\n", fileUser, filePass);
		}
	}
	//close filep after reading
	fclose(filep);

	//begin function verifyLogin();
	verifyLogin();

	//login successful when =1
	if (verifyLogin() == 1) {
		printf("\nLogin succesfull!\n");

		//Menu Options	
		printf("MENU\n");
		printf("Press 1  To Add  a Patient \n");
		printf("Press 2 To Display all Patient  Details  \n");
		printf("Press 3	To Display Patient  Details \n");
		printf("Press 4  To Update a Patient  details\n");
		printf("press 5 To Delete a Patient  details  \n");
		printf("press 6 To Generate Statistics  \n");
		printf("press 7 To Print all patients  into a report file   \n");
		printf("press 8 To List all the  patients in order of their last appointments \n");

		printf("Or Press -1 to exit  \n");
		scanf("%d", &choice);

		//menu choices calling each function  in program
		while (choice != -1)
		{
			if (choice == 1)
			{
				printf("Adding element at the start\n");
				printf("\n");
				AddElementAtStart(&headPtr);
			}

			else if (choice == 2)
			{
				printf("Display the list\n");
				printf("\n");
				DisplayList(headPtr);
			}

			else if (choice == 3)
			{
				printf("To Display Patient  Details\n");
				printf("\n");
				SearchPatient(headPtr);
			}

			else if (choice == 4)
			{
				printf("Update a Patient  details\n");
				printf("\n");
				updatePatient(headPtr);
			}
			else if (choice == 5)
			{
				printf("Delete a Patient  details \n");
				
			}
			else if (choice == 6)
			{
				printf("Generate Statistics \n");
				printf("\n");
			}
			else if (choice == 7)
			{
				printf("Print all patients  into a report file  \n");
				printf("\n");
				outputReport(headPtr);
			}
			else if (choice == 8)
			{
				printf("List all the  patients in order of their last appointment \n");
				printf("\n");
			}

			printf("MENU\n");
			printf("Press 1  To Add  a Patient \n");
			printf("Press 2 To Display all Patient  Details  \n");
			printf("Press 3	To Display Patient  Details \n");
			printf("Press 4  To Update a Patient  details\n");
			printf("press 5 To Delete a Patient  details  \n");
			printf("press 6 To Generate Statistics  \n");
			printf("press 7 To Print all patients  into a report file   \n");
			printf("press 8 To List all the  patients in order of their last appointments \n");
			printf("/n");
			printf("Or Press -1 to exit  \n");
			scanf("%d", &choice);

			if (choice == -1) {
				//on exit by -1 the program will save to file report.txt via  saveFile  function call
				saveFile(headPtr);
				//alert user
				printf("You have chosen to exit the program.The database will now be updated \n");
			}
		}
	}
}
//Validate user function 
int verifyLogin()
{
	//variable declaration

	FILE* filep;//initlize file
	int input;
	int i;
	struct node* temp;
	char ch;
	int pCounter;
	char loginUser[10];
	char loginPass[10];
	char fileUser[10];
	char filePass[10];

	//enter username and password
	printf("Enter username:\n");
	scanf("%s", loginUser);
	printf("Enter 1 digit  password:\n");
	//scanf("%s", loginPass);

	//replace char with * for each char entered by user (HIDE PASSWORD ENTRY)
	for (i = 0; i < 6; i++)// loop through the number of characters in password
	{
		ch = getch();//get next char
		loginPass[i] = ch; //HOLD 
		ch = '*';  //REPLACE
		printf("%c", ch);//DISPLAY
	}//for

	loginPass[i] = '\0';//add null terminater

	filep = fopen("log.txt", "r");//open file for read

	//make sure file has contents
	if (filep == NULL) {
		printf("Error No File\n");
		return 0;
	}
	while (!feof(filep)) {
		//read file fileUser + filePassword
		input = fscanf(filep, "%s %s", fileUser, filePass);

		//compare the username + password 
		if (strcmp(loginUser, fileUser) == 0 && strcmp(loginPass, filePass) == 0) {
			printf("Credentials found \n ");
			printf("Welcome  back : %s", loginUser);
			return 1;
		}// if	

	}//while
	return 0;
	//close the file
	fclose(filep);
	//verifyLogin

}
// add patient to the linked list 
void AddElementAtStart(struct node** top)
{
	//inialize
	struct node* newNode;
	//malloc
	newNode = (struct node*)malloc(sizeof(struct node));


	//prompts ask patient to enter all his/her details into the program
	printf("Enter your PPS Number (int) \n");
	scanf("%d", &newNode->PPSnum);
	printf("Enter your First name (String)\n");
	scanf("%s", newNode->Fname);
	printf("Enter your second name (String) \n");
	scanf("%s", newNode->Surname);
	printf("Enter your year born (int)\n");
	scanf("%d", &newNode->yearBorn);
	printf("Enter your Gender  (int)\n");
	scanf("%d", &newNode->gender);
	printf("Enter your  Email Address (String) \n");
	scanf("%s", newNode->emailAdd);
	//Validate The @  
	printf("Enter your next of Kin Name  (String) \n");
	scanf("%s", newNode->nextOfKinName);
	printf("Enter your last Appointment (int) \n");
	scanf("%d", &newNode->lastAppointment);
	printf("Enter your Weight  (int)\n");
	scanf("%d", &newNode->weight);
	printf("Enter your Height (int) \n");
	scanf("%d", &newNode->height);
	printf("Does the patient have any allergies to any medications , enter:  y/n (char) \n");
	scanf("%s", newNode->Allergies);
	// validate the y or n
	printf("How many cigarettes would you smoke a day enter 1 for none \n enter 2 for less than 10 \n enter 3 for greater than 10 (int)\n");
	scanf("%d", &newNode->howManyCigarettesSmoked);
	// validate , options - none 
	// validate , options - LESS THAN 10, var<10 
	// validate , options - GREATER THAN 10 , var > 10
	printf("How much alcohol would you drink per week?  enter 1 for none \n enter 2 LESS THAN 10 units \n enter 3 for GREATER THAN 10 units (int)\n");
	scanf("%d", &newNode->howManyDrinksPerWeek);
	// validate , options - none 
	// validate , options - LESS THAN 10 units     , var < 10 units
	// validate , options - GREATER THAN 10 units  , var > 10 units 
	printf("How often do you exercise? (int)\n");
	scanf("%d", &newNode->howOftenDoYouExcercise);
	// validate , options - Never 
	// validate , options - LESS THAN  twice a week
	// validate , options - GREATER More than twice per week 
	newNode->NEXT = *top;
	*top = newNode;
}

//display all the users data stored in the list
void DisplayList(struct node* top)
{
	struct node* temp = top;
	if (temp == NULL)
	{
		printf("Nothing in file\n");
	}
	while (temp != NULL)
	{
		printf("======DisplayList=========\n");
		printf("PPSN:%d \n", temp->PPSnum);
		printf("FirstName::%s \n", temp->Fname);
		printf("SecondName:%s \n", temp->Surname);
		printf("yearBorn:%d \n", temp->yearBorn);
		printf("Gender:%d \n", temp->gender);
		printf("EmailAddress:%s \n", temp->emailAdd);
		printf("KinName::%s \n", temp->nextOfKinName);
		printf("lastAppointment:%d \n", temp->lastAppointment);
		printf("Weight:%d \n", temp->weight);
		printf("height:%d \n", temp->height);
		printf("Allergies:%s \n", temp->Allergies);
		printf("Ciggarettes Smoked:%d \n", temp->howManyCigarettesSmoked);
		printf("Drinks Drank Per Week:%d \n", temp->howManyDrinksPerWeek);
		printf("Exercise:%d \n", temp->howOftenDoYouExcercise);
		printf("++++++++++++++++++++++++++++\n");
		temp = temp->NEXT;
	}
}
//save the file to be reloaded
void saveFile(struct node* headptr) {//method to save to file

	FILE* outfile;//file pointer

	struct node *temp;//node pointer temp
	temp = (struct node*)malloc(sizeof(struct node));

	temp = headptr;
	outfile = fopen("patientsFile.txt", "w");//open patientsFile.txt

	while (outfile != NULL)
	{
		fprintf(outfile, "%d\n", temp->PPSnum);
		fprintf(outfile, "%s\n", temp->Fname);
		fprintf(outfile, "%s\n", temp->Surname);
		fprintf(outfile, "%d\n", temp->yearBorn);
		fprintf(outfile, "%d\n", temp->gender);
		fprintf(outfile, "%s\n", temp->emailAdd);
		fprintf(outfile, "%s\n", temp->nextOfKinName);
		fprintf(outfile, "%d\n", temp->lastAppointment);
		fprintf(outfile, "%d\n", temp->weight);
		fprintf(outfile, "%d\n", temp->height);
		fprintf(outfile, "%s\n", temp->Allergies);
		fprintf(outfile, "%d\n", temp->howManyCigarettesSmoked);
		fprintf(outfile, "%d\n", temp->howManyDrinksPerWeek);
		fprintf(outfile, "%d\n", temp->howOftenDoYouExcercise);

		temp = temp->NEXT;//move to next node
	}

	fclose(outfile);//close file
}//saveFile

void loadfile(struct node** headptr) {


	FILE* loadDetails;//file pointer
	struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));

	loadDetails = fopen("patientsFile.txt", "r");

	if (loadDetails == NULL) {//check if file is empty
		printf("Database Not found !\n");
		return;
	}// if NUll
	else {
			struct node* temp;
			temp = (struct node*)malloc(sizeof(struct node));

			fscanf(loadDetails,"%d", temp->PPSnum);
			fscanf(loadDetails, "%s", temp->Fname);
			fscanf(loadDetails, "%s", temp->Surname);
			fscanf(loadDetails, "%d",temp->yearBorn);
			fscanf(loadDetails, "%d", temp->gender);
			fscanf(loadDetails, "%s", temp->emailAdd);
			fscanf(loadDetails, "%s", temp->nextOfKinName);
			fscanf(loadDetails, "%d", temp->lastAppointment);
			fscanf(loadDetails, "%d", temp->weight);
			fscanf(loadDetails, "%d", temp->height);
			fscanf(loadDetails, "%s", temp->Allergies);
			fscanf(loadDetails, "%d", temp->howManyCigarettesSmoked);
			fscanf(loadDetails, "%d", temp->howManyDrinksPerWeek);
			fscanf(loadDetails, "%d", temp->howOftenDoYouExcercise);

			printf( "PPSN:%d \n", temp->PPSnum);
			printf( "Fname:%s \n", temp->Fname);
			printf( "Surname:%s \n", temp->Surname);
			printf( "yearBorn:%d \n", temp->yearBorn);
			printf( "gender:%d \n", temp->gender);
			printf( "emailAdd:%s \n", temp->emailAdd);
			printf( "nextOfKinName:%s \n", temp->nextOfKinName);
			printf( "lastAppointment:%d \n", temp->lastAppointment);
			printf( "weight:%d \n", temp->weight);
			printf( "height:%d \n", temp->height);
			printf( "Allergies:%s \n", temp->Allergies);
			printf( "howManyCigarettesSmoked:%d \n", temp->howManyCigarettesSmoked);
			printf( "howManyDrinksPerWeek:%d \n", temp->howManyDrinksPerWeek);
			printf( "howOftenDoYouExcercise:%d \n", temp->howOftenDoYouExcercise);

			temp->NEXT = *headptr;//next node is headptr
			*headptr = temp;//headpointer takes on temp value

	}//else
	fclose(loadDetails);
}//InputFromFile
void SearchPatient(struct node* top) {

	struct node* temp;
	int count = 0;
	int found = 0;
	
	char searchName[15];
	
	temp = (struct node*)malloc(sizeof(struct node));
	temp = top;

	//check how user would like to search
		printf("\t Enter Patient Name :");
		scanf("%s", searchName);
	
	while (temp != NULL) {
		if (strcmp(temp->Fname, searchName) == 0) {

			printf("PPSN:%d \n", temp->PPSnum);
			printf("FirstName::%s \n", temp->Fname);
			printf("SecondName:%s \n", temp->Surname);
			printf("yearBorn:%d \n", temp->yearBorn);
			printf("Gender:%d \n", temp->gender);
			printf("EmailAddress:%s \n", temp->emailAdd);
			printf("KinName::%s \n", temp->nextOfKinName);
			printf("lastAppointment:%d \n", temp->lastAppointment);
			printf("Weight:%d \n", temp->weight);
			printf("height:%d \n", temp->height);
			printf("Allergies:%s \n", temp->Allergies);
			printf("Ciggarettes Smoked:%d \n", temp->howManyCigarettesSmoked);
			printf("Drinks Drank Per Week:%d \n", temp->howManyDrinksPerWeek);
			printf("Exercise:%d \n", temp->howOftenDoYouExcercise);
			found = 1;
			break;
		}
		temp = temp->NEXT;
	}

	if (found == 0) {
		printf("No such Patient? Try again Please\n");
	}
}//displyPatient

void updatePatient(struct node* top) {

	struct node* temp;
	int count = 0;
	int found = 0;
	char searchName[15];

	temp = (struct node*)malloc(sizeof(struct node));
	temp = top;

	//check how user would like to search
	printf("Search Update by entering First Name\n");
	scanf("%s", searchName);
		
	while (temp != NULL) {
		//Search for irfu or name
		if (strcmp(temp->Fname, searchName) == 0) {

			//prompts ask patient to enter all his/her details
			printf("Enter your PPS Number \n");
			scanf("%d", &temp->PPSnum);

			printf("Enter your First name \n");
			scanf("%s", temp->Fname);

			printf("Enter your second name \n");
			scanf("%s", temp->Surname);

			printf("Enter your year born \n");
			scanf("%d", &temp->yearBorn);

			printf("Enter your Gender \n");
			scanf("%d", &temp->gender);

			printf("Enter your  Email Address \n");
			scanf("%s", temp->emailAdd);
			//Validate The @  

			printf("Enter your next of Kin Name \n");
			scanf("%s", temp->nextOfKinName);

			printf("Enter your last Appointment \n");
			scanf("%d", &temp->lastAppointment);

			printf("Enter your Weight \n");
			scanf("%d", &temp->weight);

			printf("Enter your Height \n");
			scanf("%d", &temp->height);

			printf("Does the patient have any allergies to any medications , enter:  y/n \n");
			scanf("%s", temp->Allergies);
			// validate the y or n

			printf("How many cigarettes would you smoke a day enter 1 for none \n enter 2 for less than 10 \n enter 3 for greater than 10 \n\n");
			scanf("%d", &temp->howManyCigarettesSmoked);
			// validate , options - none 
			// validate , options - LESS THAN 10, var<10 
			// validate , options - GREATER THAN 10 , var > 10

			printf("How much alcohol would you drink per week?  enter 1 for none \n enter 2 LESS THAN 10 units \n enter 3 for GREATER THAN 10 units \n\n");
			scanf("%d", &temp->howManyDrinksPerWeek);
			// validate , options - none 
			// validate , options - LESS THAN 10 units     , var < 10 units
			// validate , options - GREATER THAN 10 units  , var > 10 units 

			printf("How often do you exercise? \n");
			scanf("%d", &temp->howOftenDoYouExcercise);

			// validate , options - Never 
			// validate , options - LESS THAN  twice a week
			found = 1;
			break;
		}
		temp = temp->NEXT;
	}

	if (found == 0) {
		printf("Patient  is not in system\n");
	}
}
// output data and statistics to file named  patientsFile
void outputReport(struct node* headptr) {//method to ouput to file

	//variable declaration
	FILE* patientDetails;//file pointer
	struct node *temp;//node pointer temp
	temp = (struct node*)malloc(sizeof(struct node));
	temp = headptr;
	
	//open studentsFile.txt
	patientDetails = fopen("patientsFile.txt", "w");
	
	while (temp != NULL)
	{
		//print patients   to file
		fprintf(patientDetails, "PPSN:%d \n", temp->PPSnum);
		fprintf(patientDetails, "FirstName::%s \n", temp->Fname);
		fprintf(patientDetails, "SecondName:%s \n", temp->Surname);
		fprintf(patientDetails, "yearBorn:%d \n", temp->yearBorn);
		fprintf(patientDetails, "Gender:%d \n", temp->gender);
		fprintf(patientDetails, "EmailAddress:%s \n", temp->emailAdd);
		fprintf(patientDetails, "KinName::%s \n", temp->nextOfKinName);
		fprintf(patientDetails, "lastAppointment:%d \n", temp->lastAppointment);
		fprintf(patientDetails, "Weight:%d \n", temp->weight);
		fprintf(patientDetails, "height:%d \n", temp->height);
		fprintf(patientDetails, "Allergies:%s \n", temp->Allergies);
		fprintf(patientDetails, "Ciggarettes Smoked:%d \n", temp->howManyCigarettesSmoked);
		fprintf(patientDetails, "Drinks Drank Per Week:%d \n", temp->howManyDrinksPerWeek);
		fprintf(patientDetails, "Exercise:%d \n", temp->howOftenDoYouExcercise);

		temp = temp->NEXT;//move to next node

		//print  to file
	}
	//confirm to screeen
	printf("All Details recorded in patientsFile.txt\n");
	fprintf(patientDetails, "  \n");
	fclose(patientDetails);//close file
}//output Report
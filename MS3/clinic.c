
/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  :Ching Wei Lai
Student ID#:136893211
Email      :cwlai6@myseneca.ca
Section    :NHH

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu (hub) for application
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0;

    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != '\0')
        {
            displayPatientData(&patient[i], FMT_TABLE);
        }
    }
    printf("\n");
}


// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do
    {

        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            printf("\n");
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            printf("\n");
            break;
        }
    } while (selection);
}


// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int i = 0;
    int index = -1;

    while (i < max && index == -1)
    {
        if (patient[i].patientNumber == 0)
        {
            index = i; //  This is the index of the free spot in the array.
        }
        i++;
    }
    if (index != -1)
    {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}


// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int id = 0;
    int index = 0;

    printf("Enter the patient number: ");
    scanf("%d", &id);
    index = findPatientIndexByPatientNum(id, patient, max);
    if (index != -1)
    {
        printf("\n");
        menuPatientEdit(&patient[index]);
    }
    else
    {
        printf("\nERROR: Patient record not found!\n");
    }
}


// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int id = 0;
    int index = 0;
    char answer = 0;
    char newline = 0;

    printf("Enter the patient number: ");
    scanf("%d", &id);
    printf("\n");
    index = findPatientIndexByPatientNum(id, patient, max);

    if (index != -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        inputCharOption(answer);
        switch (answer)
        {
        case 'y':
            patient[index].name[NAME_LEN] = '\0';
            patient[index].patientNumber = 0;
            patient[index].phone.description[PHONE_DESC_LEN] = '\0';
            patient[index].phone.number[PHONE_LEN] = '\0';
            printf("Patient record has been removed!\n\n");
            break;
        case 'n':
            printf("Operation aborted.\n\n");
            break;
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int index, j, minIdx;
    struct Appointment temp;


    for (index = 0; index < data->maxAppointments; index++)
    {
        minIdx = index;

        for (j = index + 1; j < data->maxAppointments; j++)
        {
            if (data->appointments[j].date.year > data->appointments[j + 1].date.year) { minIdx = j; }
            else if (data->appointments[j].date.year == data->appointments[j + 1].date.year)
            {
                if (data->appointments[j].date.month > data->appointments[j + 1].date.month) { minIdx = j; }
                else if (data->appointments[j].date.month == data->appointments[j + 1].date.month)
                {
                    if (data->appointments[j].date.day > data->appointments[j + 1].date.day) { minIdx = j; }
                    else if (data->appointments[j].date.day == data->appointments[j + 1].date.day)
                    {
                        if (data->appointments[j].time.hour > data->appointments[j + 1].time.hour) { minIdx = j; }
                        else if (data->appointments[j].time.hour == data->appointments[j + 1].time.hour)
                        {
                            if (data->appointments[j].time.min > data->appointments[j + 1].time.min) { minIdx = j; }
                            else if (data->appointments[j].time.min == data->appointments[j + 1].time.min)
                            {
                                minIdx = j;
                            }
                        }
                    }
                }
            }
        }
        if (minIdx != index)
        {
            temp = data->appointments[index];
            data->appointments[index] = data->appointments[minIdx];
            data->appointments[minIdx] = temp;
        }
    }
    
    
    
    
    
    int i;
    int appointments = importAppointments("appointmentData.txt", data->appointments , data->maxAppointments);

    displayScheduleTableHeader(data,1);

        for (i = 0; i < appointments; i++)
        {  
            if (data->patients[i].patientNumber != 0 )
            {
                displayScheduleData(&data->patients[i], &data->appointments[i], 1);
            }
        }
    printf("\n");
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i;
    int year = 0;
    int month = 0;
    int day = 0;
    int appointments = importAppointments("appointmentData.txt", data->appointments, data->maxAppointments);


    printf("Year        :");
    year = inputIntRange(2022,3000);

    printf("Month (1-12):");
    month = inputIntRange(1,12);

    if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0) 
    {
        if (month == 2)
        {
            printf("Day (1-29)  :");
            day = inputIntRange(1, 29);
        }
    }
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 9 || month == 11)
    {
        printf("Day (1-31)  :");
        day = inputIntRange(1, 31);
    }
    else if (month == 4 || month == 6 || month == 8 || month == 10 || month == 12)
    {
        printf("Day (1-30)  :");
        day = inputIntRange(1, 30);
    }
    else if ((year % 400 != 0 && year % 4 != 0 || year % 100 == 0) && month == 2)
    {
        printf("Day (1-28)  :");
        day = inputIntRange(1, 28);
    }

    printf("\n");
    displayScheduleTableHeader(data, 0);

    for (i = 0; i < appointments; i++)
    {
        if (data->appointments[i].date.year == year && data->appointments[i].date.month == month && data->appointments[i].date.day == day)
        {
            displayScheduleData(&data->patients[i], &data->appointments[i], 1);
        }
    }
    printf("\n");
   
}


// Add an appointment record to the appointment array
void addAppointment(struct ClinicData* data)
{
    int i = 0;
    int index = -1;
    int id = 0;
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;


    printf("Patient Number:");
    scanf("%d", &id);
    index = findPatientIndexByPatientNum(id, data->patients, data->maxPatient);
    if (index != -1)
    {
        printf("\n");
    }
    else
    {
        printf("\n*** No records found ***\n\n");
    }



    printf("Year        :");
    year = inputIntRange(2022, 3000);

    printf("Month (1-12):");
    month = inputIntRange(1, 12);

    if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
    {
        if (month == 2)
        {
            printf("Day (1-29)  :");
            day = inputIntRange(1, 29);
        }
    }
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 9 || month == 11)
    {
        printf("Day (1-31)  :");
        day = inputIntRange(1, 31);
    }
    else if (month == 4 || month == 6 || month == 8 || month == 10 || month == 12)
    {
        printf("Day (1-30)  :");
        day = inputIntRange(1, 30);
    }
    else if ((year % 400 != 0 && year % 4 != 0 || year % 100 == 0) && month == 2)
    {
        printf("Day (1-28)  :");
        day = inputIntRange(1, 28);
    }






    /*while (i < max && index == -1)
    {
        if (patient[i].patientNumber == 0)
        {
            index = i; //  This is the index of the free spot in the array.
        }
        i++;
    }
    if (index != -1)
    {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
        printf("*** Appointment scheduled! ***\n\n");
    }
    else
    {
        printf("ERROR: Appointment listing is FULL!\n\n");
    }*/



}


// Remove an appointment record from the appointment array
void removeAppointment(struct ClinicData* data)
{
    int id = 0;
    int index = 0;
    char answer = 0;
    char newline = 0;

    printf("Enter the patient number: ");
    scanf("%d", &id);
    printf("\n");
    index = findPatientIndexByPatientNum(id, data->patients, data->maxPatient);

    if (index != -1)
    {
        //displayPatientData(&patient[index], FMT_FORM);
        printf("\nAre you sure you want to remove this appointment (y,n):");
        inputCharOption(answer);
        switch (answer)
        {
        case 'y':
            /*data[index].name[NAME_LEN] = '\0';
            data[index].patientNumber = 0;
            data[index].phone.description[PHONE_DESC_LEN] = '\0';
            data[index].phone.number[PHONE_LEN] = '\0';*/
            data[index].appointments->patientNumber = 0; 
            data[index].appointments->date.year = 0;
            data[index].appointments->date.month = 0;
            data[index].appointments->date.day = 0;
            data[index].appointments->time.hour = 0;
            data[index].appointments->time.min = 0;
            printf("Appointment record has been removed!\n\n");
            break;
        case 'n':
            printf("Operation aborted.\n\n");
            break;
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int index = 0;
    int id = 0;

    printf("Search by patient number: ");
    scanf("%d", &id);
    index = findPatientIndexByPatientNum(id, patient, max);
    if (index != -1)
    {
        printf("\n");
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
    }
    else
    {
        printf("\n*** No records found ***\n\n");
    }
}


// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int counter = 0;
    int i = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    char phoneNum[PHONE_LEN + 1] = { '\0' };

    printf("Search by phone number: ");
    scanf("%10s", phoneNum);
    while (y < max) // total patient number 
    {
        for (i = 0; i < PHONE_LEN; i++)
        {
            if (phoneNum[i] == patient[y].phone.number[i]) // compare input phone number with ten digits
            {
                counter++;
                z++;
            }
            else
            {
                counter = 0;
                x++;
                break;
            }
        }
        if (counter == 10)
        {
            if (z == 10)
            {
                printf("\n");
                displayPatientTableHeader();
                displayPatientData(&patient[y], FMT_TABLE);
            }
            else
            {
                displayPatientData(&patient[y], FMT_TABLE);
            }
        }
        y++;
        counter = 0;
    }
    printf("\n");
    if (x == max)
    {
        displayPatientTableHeader();
        printf("\n*** No records found ***\n\n");
    }
}



// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i = 0;
    int arrayMax = patient[0].patientNumber;

    for (i = 1; i < max; i++)
    {
        if (patient[i].patientNumber > arrayMax)
        {
            arrayMax = patient[i].patientNumber;
        }
    }
    return arrayMax + 1;
}


// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i = 0;
    int Index = -1;

    while (i < max && Index == -1)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            Index = i;
        }
        else
        {
            Index = -1;
            i++;
        }
    }
    return Index;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    char patient_name[NAME_LEN + 1] = { '\0' };

    printf("Patient Data Input\n"
        "------------------\n");
    printf("Number: 0");
    printf("%d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient_name, 1, 15);
    printf("\n");
    strcpy(patient->name, patient_name);
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{
    int selection;
    char numberinput[PHONE_LEN + 1] = { '\0' };

    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');
    switch (selection)
    {
    case 1:
        printf("Contact: CELL\n");
        printf("Number : ");
        inputCString(numberinput, 10, 10);
        strcpy(phone->number, numberinput); // store phone number. assign the entered value to the phone number member.
        strcpy(phone->description, "CELL");
        printf("\n");
        break;
    case 2:
        printf("Contact: HOME\n");
        printf("Number : ");
        inputCString(numberinput, 10, 10);
        strcpy(phone->number, numberinput);
        strcpy(phone->description, "HOME");
        printf("\n");
        break;
    case 3:
        printf("Contact: WORK\n");
        printf("Number : ");
        inputCString(numberinput, 10, 10);
        strcpy(phone->number, numberinput);
        strcpy(phone->description, "WORK");
        printf("\n");
        break;
    case 4:
        strcpy(phone->number, numberinput);
        strcpy(phone->description, "TBD");
        break;
    }
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE *fp = NULL;
    int i = 0;

    fp = fopen(datafile, "r");

    while (!feof(fp)) 
    {
        fscanf(fp, "%d|%[^|]|%[^|]|", &patients[i].patientNumber, patients[i].name, patients[i].phone.description);
        if (strcmp(patients[i].phone.description, "TAB"))
        {
            fscanf(fp, "%[^\n]", patients[i].phone.number);
        }
        i++;
    }
    i--;
    fclose(fp);
    return i;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    FILE* fp = NULL;
    int i = 0;

    fp = fopen(datafile, "r");

    while (fscanf(fp, "%d,%d,%d,%d,%d,%d",
        &appoints[i].patientNumber,
        &appoints[i].date.year,
        &appoints[i].date.month,
        &appoints[i].date.day,
        &appoints[i].time.hour,
        &appoints[i].time.min) == 6 && i < max)
    {
        i++;
    }
    fclose(fp);
    return i;


    /*int index, j, minIdx;
    struct Appointment temp;


    for (index = 0; index < data->maxAppointments; index++)
    {
        minIdx = index;

        for (j = index + 1; j < max; j++)
        {
            if (data->appoints[j].date.year > data->appoints[j + 1].date.year){ minIdx = j; }
            else if (data->appoints[j].date.year == data->appoints[j + 1].date.year)
            {
                if (data->appoints[j].date.month > data->appoints[j + 1].date.month){ minIdx = j; }
                else if (data->appoints[j].date.month == data->appoints[j + 1].date.month)
                {
                    if (data->appoints[j].date.day > data->appoints[j + 1].date.day) { minIdx = j; }
                    else if (data->appoints[j].date.day == data->appoints[j + 1].date.day)
                    {
                        if (data->appoints[j].time.hour > data->appoints[j + 1].time.hour) { minIdx = j; }
                        else if (data->appoints[j].time.hour == data->appoints[j + 1].time.hour)
                        {
                            if (data->appoints[j].time.min > data->appoints[j + 1].time.min) { minIdx = j; }
                            else if (data->appoints[j].time.min == data->appoints[j + 1].time.min)
                            {
                                minIdx = j;
                            }
                        }
                    }                 
                }           
            }  
        }
        if (minIdx != index)
        {
            temp = appoints[index];
            appoints[index] = appoints[minIdx];
            appoints[minIdx] = temp;
        }
    }*/
    


}


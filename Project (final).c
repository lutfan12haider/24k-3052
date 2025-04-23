#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

// Definitions of particular entities

#define MAX_STUDENTS 100
#define MAX_COURSES 8
#define MAX_ATTENDANCE 50 // Maximum number of attendance records per student
#define MAX_WIDTH 60 // Assuming a maximum console width of 60 characters
#define DATE_WIDTH 17 // Width for the date column
#define PRESENCE_WIDTH 10 // Width for the presence column


struct attendence
{
    char date[11]; // Date in DD/MM/YYYY format
    char presence; // 'P' for Present, 'A' for Absent
};

struct marking
{
    float a_marks[3];  // 3 assignments
    float a_weight[3]; // weights for assignments
    float q_marks[3];  // 3 quizzes
    float q_weight[3]; // weights for quizzes
    float m_marks[2];  // 2 midterms
    float m_weight[2]; // weights for midterms
    float f_marks;     // Final exam marks
    float f_weight;    // Final exam weight
    float gpa;         // GPA (calculated)
};

struct std_details
{
    char name[20];
    char rollnumber[10];
    struct attendence a[MAX_ATTENDANCE]; // Array to store multiple attendance records
    int attendanceCount;                 // Number of attendance records for the student
    struct marking mk;
};

struct subjects
{
    char courseName[50];
    struct std_details std[MAX_STUDENTS];
    int stdCount; // Current number of students in the course
};

// Function Prototypes
void initializeSubjects(struct subjects sub[]);
int validateRollNumber(char roll[]);
void addStudent(struct subjects sub[], int courseIndex);
void markAttendance(struct subjects sub[], int courseIndex);
void gradeAssessment(struct subjects sub[], int courseIndex);
void viewAttendance(struct subjects sub[], int courseIndex, int i);
void viewMarks(struct subjects sub[], int courseIndex, char rollNum[]);
void teacherPortal(struct subjects sub[]);
void studentPortal(struct subjects sub[]);
void saveDataToFile(struct subjects sub[]);
void loadDataFromFile(struct subjects sub[]);
void clearscreen();

// Function to clear the terminal screen
void clearscreen()
{
    system("cls");
}

// Function to center-align a string within a given width
void printCentered(const char *str, int width)
{
    int len = strlen(str);
    if (len < width)
    {
        int padding = (width - len) / 2; // Calculate left padding
        printf("%*s%s%*s", padding, "", str, width - len - padding, "");
    }
    else
    {
        printf("%s", str); // If the string is too wide, print as it is
    }
}

// Initializing all marking elements to -1 as a null identifier
void initializeMarking(struct marking *mk)
{
    // Initialize assignment marks and weights
    for (int i = 0; i < 3; i++)
    {
        mk->a_marks[i] = -1;
        mk->a_weight[i] = -1;
        mk->q_marks[i] = -1;
        mk->q_weight[i] = -1;
    }

    // Initialize midterm marks and weights
    for (int i = 0; i < 2; i++)
    {
        mk->m_marks[i] = -1;
        mk->m_weight[i] = -1;
    }

    // Initialize final exam marks and weight
    mk->f_marks = -1;
    mk->f_weight = -1;

    // Initialize GPA
    mk->gpa = -1;
}

// Initialize Subjects
void initializeSubjects(struct subjects sub[])
{
    const char *courseNames[MAX_COURSES] = {
        "Calculus", "Applied Physics", "Functional English Lab",
        "Functional English Theory", "Programming Fundamentals Lab",
        "Programming Fundamentals", "Islamic Studies", "ICT"};
    for (int i = 0; i < MAX_COURSES; i++)
    {
        strncpy(sub[i].courseName, courseNames[i], sizeof(sub[i].courseName) - 1);
        sub[i].courseName[sizeof(sub[i].courseName) - 1] = '\0';
        sub[i].stdCount = 0;

        for (int j = 0; j < MAX_STUDENTS; j++)
        {
            initializeMarking(&sub[i].std[j].mk);
            // Initialize attendance count to 0
            sub[i].std[j].attendanceCount = 0;
        }
    }
}

// Validate Roll Number
int validateRollNumber(char roll[])
{
    if (strlen(roll) != 8 ||
        !isdigit(roll[0]) || !isdigit(roll[1]) ||
        roll[2] != 'k' || roll[3] != '-' ||
        !isdigit(roll[4]) || !isdigit(roll[5]) ||
        !isdigit(roll[6]) || !isdigit(roll[7]))
    {
        return 0; // Invalid roll number
    }
    return 1; // Valid roll number
}

int isValidDate(char date[]) {
    // Check length is 10 characters (DD-MM-YYYY)
    if (strlen(date) != 10) {
        return 0;
    }

    // Check format DD-MM-YYYY (digits for day, month, year, with '-' in correct places)
    if (!isdigit(date[0]) || !isdigit(date[1]) || date[2] != '-' ||
        !isdigit(date[3]) || !isdigit(date[4]) || date[5] != '-' ||
        !isdigit(date[6]) || !isdigit(date[7]) || !isdigit(date[8]) || !isdigit(date[9])) {
        return 0;
    }

    // Extract day, month, and year
    int day = (date[0] - '0') * 10 + (date[1] - '0');  // Convert from char to int
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

    // Check if month is valid (1 to 12)
    if (month < 1 || month > 12) {
        return 0;
    }

    // Validate day based on month (simplified version)
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        if (day < 1 || day > 31) return 0; // 31 days months
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day < 1 || day > 30) return 0; // 30 days months
    } else if (month == 2) {
        // Check for February (leap year check is not included here for simplicity)
        if (day < 1 || day > 28) return 0; // Not considering leap years here, February has 28 days
    }

    return 1; // Date is valid
}

// Add Student
void addStudent(struct subjects sub[], int courseIndex)
{
    if (sub[courseIndex].stdCount >= MAX_STUDENTS)
    {
        printf("Maximum number of students reached for %s!\n", sub[courseIndex].courseName);
        return;
    }

    struct std_details *newStudent = &sub[courseIndex].std[sub[courseIndex].stdCount];
    printf("Enter Name: ");
    scanf(" %[^\n]", newStudent->name);

    printf("Enter Roll Number (format: 24k-XXXX): ");
    scanf("%s", newStudent->rollnumber);

    if (!validateRollNumber(newStudent->rollnumber))
    {
        printf("Invalid Roll Number! Try again.\n");
        return;
    }

    printf("Student %s (%s) added successfully to %s.\n",
           newStudent->name, newStudent->rollnumber, sub[courseIndex].courseName);

    sub[courseIndex].stdCount++;
    saveDataToFile(sub); // Save updated data to file
}

// Mark Attendance
void markAttendance(struct subjects sub[], int courseIndex)
{
    char roll[10],dateTemp[20];
    clearscreen();
    printf("Enter Roll Number of Student: ");
    scanf("%s", roll);

    if (!validateRollNumber(roll))
    {
        printf("Invalid Roll Number!\n");
        return;
    }

    for (int i = 0; i < sub[courseIndex].stdCount; i++)
    {
        if (strcmp(sub[courseIndex].std[i].rollnumber, roll) == 0)
        {
            if (sub[courseIndex].std[i].attendanceCount >= MAX_ATTENDANCE)
            {
                printf("Maximum attendance records reached for %s.\n", sub[courseIndex].std[i].name);
                return;
            }
			while(1)
			{
				printf("Enter Date (DD-MM-YYYY): ");
				scanf("%s",dateTemp);
				if(isValidDate(dateTemp))
				{
					strcpy(sub[courseIndex].std[i].a[sub[courseIndex].std[i].attendanceCount].date,dateTemp);
					break;
				}
				else
				{
					printf("Invalid Date Input!");
				}
			}
			printf("\nDate check : %s\n",sub[courseIndex].std[i].a[sub[courseIndex].std[i].attendanceCount].date);
            while(1)
            {
	            printf("Attendance (P for Present, A for Absent): ");
	            scanf(" %c", &sub[courseIndex].std[i].a[sub[courseIndex].std[i].attendanceCount].presence);
	
	            if (sub[courseIndex].std[i].a[sub[courseIndex].std[i].attendanceCount].presence != 'P' &&
	                sub[courseIndex].std[i].a[sub[courseIndex].std[i].attendanceCount].presence != 'A')
	            {
	                printf("Invalid Attendance Value! Use 'P' or 'A'.\n");
	                continue;
	            }
	            else
	            {
	            	break;
				}

			}
            // Increment attendance count after recording the attendance
            sub[courseIndex].std[i].attendanceCount++;

            printf("Attendance marked successfully for %s (%s).\n",
                   sub[courseIndex].std[i].name, sub[courseIndex].std[i].rollnumber);
            saveDataToFile(sub); // Save updated data to file
            return;
        }
    }

    printf("Student with Roll Number %s not found in %s.\n", roll, sub[courseIndex].courseName);
}

// View Attendance
void viewAttendance(struct subjects sub[], int courseIndex, int i)
{
    clearscreen();

    printf("\nAttendance Records for %s:\n", sub[courseIndex].std[i].name);

    // Check if there are any attendance records
    if (sub[courseIndex].std[i].attendanceCount == 0)
    {
        printf("No attendance records found.\n");
        printf("Attendance Percentage: 0.00%%\n");
        return;
    }

	 printf("\033[94m");
    // Print table header with light blue color
    printf("\033[94m");
    // Table Header
    printCentered("+-----------------+------------+", MAX_WIDTH);
    printf("\n");
    printCentered("| Date            | Presence   |", MAX_WIDTH);
    printf("\n");
    printCentered("+-----------------+------------+", MAX_WIDTH);
    printf("\n");
    printf("\033[0m");
    // Display attendance records in a table
    float presentCount = 0; // Count of 'P' entries
    int totalClasses = sub[courseIndex].std[i].attendanceCount;

    for (int j = 0; j < totalClasses; j++)
    {
        char presence = sub[courseIndex].std[i].a[j].presence;
        printf("| ");
        printCentered(sub[courseIndex].std[i].a[j].date, DATE_WIDTH); // Center Date
        printf(" | ");
        printCentered((presence == 'P' ? "P" : "A"), PRESENCE_WIDTH); // Center Presence (P/A)
        printf(" |");
        printf("\n");
        // Count 'P' entries
        if (presence == 'P')
        {
            presentCount++;
        }
    }

    // Print table footer
	printCentered("+-----------------+------------+", MAX_WIDTH);
    printf("\n");
    // Calculate and display attendance percentage
    double attendancePercentage = (presentCount / totalClasses) * 100;
    printf("\n");
    printCentered("Total Classes: ", MAX_WIDTH);
    printf("%d\n", totalClasses);
    printCentered("Present Count: ", MAX_WIDTH);
    printf("%.0f\n", presentCount);
    printCentered("Attendance Percentage: ", MAX_WIDTH);
    printf("%.2f%%\n", attendancePercentage);
}

// Save Data to File
void saveDataToFile(struct subjects sub[])
{
    FILE *file = fopen("student_data.bin", "wb");
    if (file == NULL)
    {
        printf("Error opening file for saving data!\n");
        return;
    }
    fwrite(sub, sizeof(struct subjects), MAX_COURSES, file);
    fclose(file);
}

// Load Data from File
void loadDataFromFile(struct subjects sub[])
{
    FILE *file = fopen("student_data.bin", "rb");
    if (file == NULL)
    {
        printf("No existing data file found. Starting fresh.\n");
        return;
    }
    fread(sub, sizeof(struct subjects), MAX_COURSES, file);
    fclose(file);
}

// Grade assessments
void gradeAssessment(struct subjects sub[], int courseIndex)
{
    char roll[10];
    clearscreen();
    printf("Enter Roll Number of Student: ");
    scanf("%s", roll);

    if (!validateRollNumber(roll))
    {
        printf("Invalid Roll Number!\n");
        return;
    }

    for (int i = 0; i < sub[courseIndex].stdCount; i++)
    {
        if (strcmp(sub[courseIndex].std[i].rollnumber, roll) == 0)
        {
            int assessmentType;
            while(1){
			printf("Enter Type of Assessment (1. Assignment, 2. Quiz, 3. Midterm, 4. Final): ");
            // Validate the assessment type
            if (scanf("%d", &assessmentType) != 1 || assessmentType < 1 || assessmentType > 4) {
	            // If input is invalid or not between 1 and 4
	            printf("Invalid action! Please enter a number between 1 and 4.\n");
	            while(getchar() != '\n'); // Clear the buffer to avoid infinite loop on invalid input
	            continue;
        	}
	        else
	        {
	        	break;
			}
    	}

            // Input for assignments
            if (assessmentType == 1)
            {
                int assignmentNo;
                while(1)
                {
	                printf("Enter Assignment Number (1-3): ");
	                // Validate the assignment number
		            if (scanf("%d", &assignmentNo) != 1 || assignmentNo < 1 || assignmentNo > 3) {
			            // If input is invalid or not between 1 and 3
			            printf("Invalid action! Please enter a number between 1 and 3.\n");
			            while(getchar() != '\n'); // Clear the buffer to avoid infinite loop on invalid input
			            continue;
		        	}
			        else
			        {
			        	break;
					}
    			}			
    			mark:
                printf("Enter Marks: ");
                scanf("%f", &sub[courseIndex].std[i].mk.a_marks[assignmentNo - 1]);
                if(sub[courseIndex].std[i].mk.a_marks[assignmentNo - 1]<0)
                {
                	printf("Invalid Marks Input!\n");
					goto mark;
				}
            }

            // Input for quizzes
            else if (assessmentType == 2)
            {
                int quizNo;
                printf("Enter Quiz Number (1-3): ");
                scanf("%d", &quizNo);

                if (quizNo < 1 || quizNo > 3)
                {
                    printf("Invalid Quiz Number!\n");
                    return;
                }

                printf("Current Marks for Quiz %d: %.2f\n", quizNo, sub[courseIndex].std[i].mk.q_marks[quizNo - 1]);
                printf("Enter Marks: ");
                scanf("%f", &sub[courseIndex].std[i].mk.q_marks[quizNo - 1]);
            }

            // Input for midterm exams
            else if (assessmentType == 3)
            {
                int midNo;
                printf("Enter Midterm Number (1-2): ");
                scanf("%d", &midNo);

                if (midNo < 1 || midNo > 2)
                {
                    printf("Invalid Midterm Number!\n");
                    return;
                }

                printf("Enter Marks for Midterm %d: ", midNo);
                scanf("%f", &sub[courseIndex].std[i].mk.m_marks[midNo - 1]);
            }

            // Input for final exam
            else if (assessmentType == 4)
            {
                printf("Enter Marks for Final Exam: ");
                scanf("%f", &sub[courseIndex].std[i].mk.f_marks);
            }

            return; // End once the grade is entered for the student
        }
    }

    printf("Student with Roll Number %s not found in %s.\n", roll, sub[courseIndex].courseName);
}

// view marks
void viewMarks(struct subjects sub[], int courseIndex, char rollNum[])
{
    char subjectsname[MAX_COURSES][35] = {"Calculus", "Applied Physics", "Functional English Lab",
                                          "Functional English Theory", "Programming Fundamentals Lab",
                                          "Programming Fundamentals", "Islamic Studies", "ICT"};
    int studentFound = 0;
    float assignConver = 0.5, quizConver = 0.33, midConver = 0.5, finConver = 0.5;

    clearscreen();
    // Search for the student in the course
    for (int i = 0; i < sub[courseIndex].stdCount; i++)
    {
        if (strcmp(sub[courseIndex].std[i].rollnumber, rollNum) == 0)
        {
            studentFound = 1;
            struct std_details *student = &sub[courseIndex].std[i];
            struct marking *marks = &student->mk;

            printf("\n+--------------------------------------------------------------+\n");
            printf("|                SUBJECT NAME: %-30s |\n", subjectsname[courseIndex]);
            printf("|                STUDENT NAME: %-19s (%s) |\n", student->name, student->rollnumber);
            printf("+--------------------------------------------------------------+\n");

            // Table for Assignments
            printf("| %-20s | %-15s |\n", "Assignment", "Marks");
            printf("+----------------------+-------------------------+\n");
            for (int j = 0; j < 3; j++)
            {
                if (marks->a_marks[j] == -1)
                {
                    printf("| %-18s%-3d   | %-17s |\n", "Assignment", j + 1, "-");
                }
                else
                {
                    printf("| %-18s%-3d   | %-17.2f |\n", "Assignment", j + 1, marks->a_marks[j]);
                }
            }
            printf("+----------------------+-------------------------+\n");

            // Table for Quizzes
            printf("| %-20s | %-15s |\n", "Quiz", "Marks");
            printf("+----------------------+-------------------------+\n");
            for (int j = 0; j < 3; j++)
            {
                if (marks->q_marks[j] == -1)
                {
                    printf("| %-18s%-3d   | %-17s |\n", "Quiz", j + 1, "-");
                }
                else
                {
                    printf("| %-18s%-3d   | %-17.2f |\n", "Quiz", j + 1, marks->q_marks[j]);
                }
            }
            printf("+----------------------+-------------------------+\n");

            // Table for Midterms
            printf("| %-20s | %-15s |\n", "Midterm", "Marks");
            printf("+----------------------+-------------------------+\n");
            for (int j = 0; j < 2; j++)
            {
                if (marks->m_marks[j] == -1)
                {
                    printf("| %-18s%-3d   | %-17s |\n", "Mid", j + 1, "-");
                }
                else
                {
                    printf("| %-18s%-3d   | %-17.2f |\n", "Mid", j + 1, marks->m_marks[j]);
                }
            }
            printf("+----------------------+-------------------------+\n");

            // Table for Final Exam
            printf("| %-20s | %-15s |\n", "Final Exam", "Marks");
            printf("+----------------------+-------------------------+\n");
            if (marks->f_marks == -1)
            {
                printf("| %-18s   | %-17s |\n", "Final Exam", "-");
            }
            else
            {
                printf("| %-18s%-9s   | %-17.2f |\n", "Final Exam", "", marks->f_marks);
            }
            printf("+----------------------+-------------------------+\n");

            // GPA calculation and display
            float totalWeightedMarks = 0, maxWeightedMarks = 0;

            // Add weighted contributions of assignments
            for (int j = 0; j < 3; j++)
            {
                if (marks->a_marks[j] != -1)
                {
                    totalWeightedMarks += marks->a_marks[j] * assignConver;
                    maxWeightedMarks += 100 * assignConver; // Maximum marks for this component
                }
            }

            // Add weighted contributions of quizzes
            for (int j = 0; j < 3; j++)
            {
                if (marks->q_marks[j] != -1)
                {
                    totalWeightedMarks += marks->q_marks[j] * quizConver;
                    maxWeightedMarks += 100 * quizConver; // Maximum marks for this component
                }
            }

            // Add weighted contributions of midterms
            for (int j = 0; j < 2; j++)
            {
                if (marks->m_marks[j] != -1)
                {
                    totalWeightedMarks += marks->m_marks[j] * midConver;
                    maxWeightedMarks += 100 * midConver; // Maximum marks for this component
                }
            }

            // Add weighted contributions of the final exam
            if (marks->f_marks != -1)
            {
                totalWeightedMarks += marks->f_marks * finConver;
                maxWeightedMarks += 100 * finConver; // Maximum marks for this component
            }

            // Calculate GPA (assume GPA is scaled to a maximum of 4.0)
            if (maxWeightedMarks > 0)
            {
                marks->gpa = (totalWeightedMarks / maxWeightedMarks) * 4.0f;
            }
            else
            {
                marks->gpa = 0.0f; // No valid marks entered
            }

            printf("\n+--------------------+-------------------------+\n");
            printf("| %-18s | %-17s |\n", "Total Weighted Score", "GPA");
            printf("+--------------------+-------------------------+\n");
            printf("| %.2f               | %.2f                  |\n", totalWeightedMarks, marks->gpa);
            printf("+--------------------+-------------------------+\n");

            return; // Exit function after displaying the marks
        }
    }

    if (!studentFound)
    {
        printf("Student with Roll Number %s not found in this course.\n", rollNum);
    }
}

// teacher portal
void teacherPortal(struct subjects sub[])
{
    while (1)
    {
        int courseIndex, action;
        clearscreen();
        printf("\n\tTeacher Portal\n");
        printf("Select Course:\n");
        for (int i = 0; i < MAX_COURSES; i++)
        {
            printf("%d. %s\n", i + 1, sub[i].courseName);
        }
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        if (scanf("%d", &courseIndex) != 1 || courseIndex < 0 || courseIndex > 8) {
            // If input is invalid or not between 0 and 8
            printf("Invalid action! Please enter a number between 1 and 4.\n");
            while(getchar() != '\n'); // Clear the buffer to avoid infinite loop on invalid input
            continue;
        }

        if (courseIndex == 0)
        {
            break; // Exit Teacher Portal to main menu
        }
        else if (courseIndex < 1 || courseIndex > MAX_COURSES)
        {
            printf("Invalid choice! Please select a valid course.\n");
            continue;
        }

        courseIndex--;		// decrement it to -1 for passing it as a index further

        while (1)
        {
            printf("\n1. Mark Attendance\n2. Grade Assessments\n3. Add Student\n4. Back to Course Selection\n");
            printf("Enter your action: ");
        	if (scanf("%d", &action) != 1 || action < 1 || action > 4) {
            // If input is invalid or not between 1 and 4
            printf("Invalid action! Please enter a number between 1 and 4.\n");
            while(getchar() != '\n'); // Clear the buffer to avoid infinite loop on invalid input
            continue;
        	}

            switch (action)
            {
            case 1:
                markAttendance(sub, courseIndex);
                break;
            case 2:
                gradeAssessment(sub, courseIndex);
                break;
            case 3:
                addStudent(sub, courseIndex);
                break;
            case 4:
                goto selectCourse; // Go back to course selection
            default:
                printf("Invalid action! Please try again.\n");
                break;
            }
        }
    selectCourse:; // Label for returning to course selection
    }
}

// student portal
void studentPortal(struct subjects sub[])
{
    while (1)
    {
        int courseIndex, action;
        char roll[10];
        clearscreen();
        printf("\n\tStudent Portal\n");
        printf("Select Course:\n");
        for (int i = 0; i < MAX_COURSES; i++)
        {
            printf("%d. %s\n", i + 1, sub[i].courseName);
        }
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        if (scanf("%d", &courseIndex) != 1 || courseIndex < 0 || courseIndex > 8) {
            // If input is invalid or not between 0 and 8
            printf("Invalid action! Please enter a number between 1 and 4.\n");
            while(getchar() != '\n'); // Clear the buffer to avoid infinite loop on invalid input
            continue;
        	}

        if (courseIndex == 0)
        {
            break; // Exit Student Portal to main menu
        }
        else if (courseIndex < 1 || courseIndex > MAX_COURSES)
        {
            printf("Invalid choice! Please select a valid course.\n");
            continue;
        }

        courseIndex--;

        // Start a loop to keep asking for roll number until it is valid or correct
        int rollNumberValid = 0;
        while (!rollNumberValid)
        {
            printf("Enter your Roll Number (format: 24k-XXXX): ");
            scanf("%s", roll);

            if (!validateRollNumber(roll))
            {
                printf("Invalid Roll Number! Please try again.\n");
                continue; // Go back to roll number input prompt
            }

            int studentFound = 0;
            for (int i = 0; i < sub[courseIndex].stdCount; i++)
            {
                if (strcmp(sub[courseIndex].std[i].rollnumber, roll) == 0)
                {
                    studentFound = 1;
                    rollNumberValid = 1; // Successfully found the student
                    while (1)
                    {
                        printf("\n1. View Attendance\n2. View Marks\n3. Back to Course Selection\n");
                        printf("Enter your action: ");
                        scanf("%d", &action);

                        switch (action)
                        {
                        case 1:
                            viewAttendance(sub, courseIndex, i);
                            break;
                        case 2:
                            viewMarks(sub, courseIndex, roll);
                            break;
                        case 3:
                            goto selectCourse; // Go back to course selection
                        default:
                            printf("Invalid action! Please try again.\n");
                            break;
                        }
                    }
                }
            }

            if (!studentFound)
            {
                printf("Student with Roll Number %s not found in %s.\n", roll, sub[courseIndex].courseName);
                rollNumberValid = 0; // Roll number is valid but student not found
            }
        }

    selectCourse:; // Label for returning to course selection
    }
}

// Main Function
int main()
{
    struct subjects sub[MAX_COURSES];
    initializeSubjects(sub);
    loadDataFromFile(sub);

    while (1)
    {
        int userType;
        clearscreen();
        printf("\nWelcome to the University Portal!\n");
        printf("Select User Type:\n");
        printf("1. Teacher\n2. Student\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userType);

        switch (userType)
        {
        case 1:
            teacherPortal(sub);
            break;
        case 2:
            studentPortal(sub);
            break;
        case 0:
            printf("Exiting...\n");
            saveDataToFile(sub);
            return 0;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
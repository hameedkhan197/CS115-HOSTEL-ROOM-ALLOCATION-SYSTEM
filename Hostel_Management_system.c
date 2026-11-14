#include <stdio.h>

// student structure
struct student {
    int id;
    char name[40];
    int age;
    char department[40];
    char phone[15];
    int room;
};

// room structure
struct room {
    int roomNumber;
    int capacity;
    int occupied;
};

// arrays
struct student students[40];  // total students are 40
struct room rooms[20];       // total rooms are 20

//Counters
int studentCount = 0;

// File Handling function declarations
void saveRecords();
void loadRecords();

//Initialize room
void initializeRoom() {
    for(int i = 0; i < 20; i++) {
        rooms[i].roomNumber = 101 + i;  //assign room starting from 101
        rooms[i].capacity = 2;          //each room can hold only two guest
        rooms[i].occupied = 0;          //initially no guests are in room
    }
}

// student function
void addStudent() {

    // checking max student capacity
    if(studentCount >= 40) {
        printf("Hostel is full !");
        return;
    }

    int id, found = 0;

    printf("Enter student ID: \n");
    scanf("%d", &id);

    //checking duplicate id
    for(int i = 0; i < studentCount; i++) {
        if(students[i].id == id) {
            found = 1;
            break;
        }
    }

    if(found == 1) {
        printf("Student id already exixts!!\n");
        return;
    }

    //Input student information
    students[studentCount].id = id;

    printf("Enter student name: \n");
    scanf(" %39[^\n]", students[studentCount].name);

    printf("Enter age: \n");
    scanf("%d", &students[studentCount].age);

    printf("Enter department: \n");
    scanf(" %39[^\n]", students[studentCount].department);

    printf("Enter phone number: \n");
    scanf("%14s", students[studentCount].phone);

    int allocate = 0; //Room is not allocated

    for(int i = 0; i < 20; i++) {

        if(rooms[i].occupied < rooms[i].capacity) {

            students[studentCount].room = rooms[i].roomNumber;
            rooms[i].occupied++;  //increase occupied students

            allocate = 1;  // room allocated
            break;
        }
    }

    if(allocate == 1) {
        printf("Student added successfully !!\n");

        // Printing student information
        printf(" Student ID:%d\n", students[studentCount].id);
        printf(" Student Name: %s\n", students[studentCount].name);
        printf(" Allocated room: %d\n", students[studentCount].room);

        studentCount++;

        // Save records in file
        saveRecords();
    }
    else {
        printf("sorry ! no room available\n");
    }
}

// Display student function
void displayStudent() {

    if(studentCount == 0) {
        printf("No student record found!\n");
        return;
    }

    for(int i = 0; i < studentCount; i++) {
        printf("\nStudent ID: %d\n", students[i].id);
        printf("Student Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("Department: %s\n", students[i].department);
        printf("Phone Number: %s\n", students[i].phone);
        printf("Room Number: %d\n", students[i].room);
        printf("-------------------------\n");
    }
}

// Search student function
void searchStudent() {

    int id, found = 0;

    printf("Enter student ID to search: ");
    scanf("%d", &id);

    for(int i = 0; i < studentCount; i++) {

        if(students[i].id == id) {
            printf("\nStudent Found!\n");
            printf("Student ID: %d\n", students[i].id);
            printf("Student Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("Department: %s\n", students[i].department);
            printf("Phone Number: %s\n", students[i].phone);
            printf("Room Number: %d\n", students[i].room);
            found = 1;
            break;
        }
    }

    if(found == 0) {
        printf("Student not found!\n");
    }
}

// Update student function
void updateStudent() {

    int id, found = 0;

    printf("Enter student ID to update: ");
    scanf("%d", &id);

    for(int i = 0; i < studentCount; i++) {

        if(students[i].id == id) {

            printf("Enter new student name: ");
            scanf(" %39[^\n]", students[i].name);

            printf("Enter new age: ");
            scanf("%d", &students[i].age);

            printf("Enter new department: ");
            scanf(" %39[^\n]", students[i].department);

            printf("Enter new phone number: ");
            scanf("%14s", students[i].phone);

            printf("Student record updated successfully!\n");

            found = 1;

            // Save updated records in file
            saveRecords();

            break;
        }
    }

    if(found == 0) {
        printf("Student not found!\n");
    }
}

// Delete student function
void deleteStudent() {

    int id, found = 0;

    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    for(int i = 0; i < studentCount; i++) {
        if(students[i].id == id) {

            // Release room
            for(int j = 0; j < 20; j++) {
                if(rooms[j].roomNumber == students[i].room) {
                    rooms[j].occupied--;
                    break;
                }
            }

            // Shift records
            for(int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }

            studentCount--;

            printf("Student deleted successfully!\n");

            found = 1;

            // Save updated records in file
            saveRecords();

            break;
        }
    }

    if(found == 0) {
        printf("Student not found!\n");
    }
}

// Room availability function
void viewRooms() {

    for(int i = 0; i < 20; i++) {

        printf("\nRoom Number: %d\n", rooms[i].roomNumber);
        printf("Capacity: %d\n", rooms[i].capacity);
        printf("Occupied: %d\n", rooms[i].occupied);
        printf("Available: %d\n",
               rooms[i].capacity - rooms[i].occupied);
    }
}

// Save student records
void saveRecords() {

    FILE *fp = fopen("hostel_records.txt", "w");

    if(fp == NULL) {
        printf("File could not be opened!\n");
        return;
    }

    for(int i = 0; i < studentCount; i++) {

        fprintf(fp, "%d|%s|%d|%s|%s|%d\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].department,
                students[i].phone,
                students[i].room);
    }

    fclose(fp);
}

// Load student records
void loadRecords() {

    FILE *fp = fopen("hostel_records.txt", "r");

    if(fp == NULL) {
        return;
    }

    while(studentCount < 40) {

        struct student temp;

        int result = fscanf(fp, "%d|%39[^|]|%d|%39[^|]|%14[^|]|%d\n",
                            &temp.id,
                            temp.name,
                            &temp.age,
                            temp.department,
                            temp.phone,
                            &temp.room);

        if(result != 6) {
            break;
        }

        // Check duplicate ID
        int found = 0;

        for(int i = 0; i < studentCount; i++) {
            if(students[i].id == temp.id) {
                found = 1;
                break;
            }
        }

        if(found == 1) {
            continue;
        }

        // Check room availability
        int roomFound = 0;

        for(int i = 0; i < 20; i++) {

            if(rooms[i].roomNumber == temp.room &&
               rooms[i].occupied < rooms[i].capacity) {

                rooms[i].occupied++;
                roomFound = 1;
                break;
            }
        }

        if(roomFound == 1) {
            students[studentCount] = temp;
            studentCount++;
        }
    }

    fclose(fp);
}

// main function
int main() {

    initializeRoom();

    // Load previous student records
    loadRecords();

    int choice;

    do {
        printf("\n");
        printf("=============================\n");
        printf("HOSTEL ROOM ALLOCATION SYSTEM\n");
        printf("=============================\n");

        printf("Total Rooms: 20\n");
        printf("Students per room: 2\n");
        printf("Total capacity: 40\n");
        printf("Current Students: %d\n", studentCount);

        printf("\n1. Add Student\n");
        printf("2. Display Student\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. View Room Availability\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudent();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                viewRooms();
                break;

            case 7:
                saveRecords();
                printf("Thank you for using Hostel System!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 7);

    return 0;
}

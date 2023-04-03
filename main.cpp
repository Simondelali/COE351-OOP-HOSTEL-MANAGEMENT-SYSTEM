#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
using namespace std;

// Class definitions

class Room {
    int roomNo;
    int price;
    bool isAvailable;
    char type[10];
    char occupant[50];
    int studentId;
public:
    Room() {}
    Room(int r, int p, bool a, char t[]) {
        roomNo = r;
        price = p;
        isAvailable = a;
        strcpy(type, t);
    }
    /*void display() {
        cout << "Room No.: " << roomNo << endl;
        cout << "Type: " << type << endl;
        cout << "Price: " << price << endl;
        cout << "Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
    }*/
    void book() {
        isAvailable = false;
    }
    void unbook() {
        isAvailable = true;
    }
    bool available() {
        return isAvailable;
    }
    int getRoomNo() {
        return roomNo;
    }
    // Funtion to get type of room
    char* getType() {
        return type;
    }
    // Function to get price of room
    int getPrice() {
        return price;
    }
    // set student name in room
    void setStudentName(char n[]) {
        strcpy(occupant, n);
    }
    // get student name in room
    char* getStudentName() {
        return occupant;
    }
    // set student id in room
    void setStudentId(int id) {
        studentId = id;
    }
    // get student id in room
    int getStudentId() {
        return studentId;
    }
};

class User {
    char username[20];
    char password[20];
public:
    User() {}
    User(char u[], char p[]) {
        strcpy(username, u);
        strcpy(password, p);
    }
    char* getUsername() {
        return username;
    }
    char* getPassword() {
        return password;
    }
    // virtual destructor
    virtual ~User() {}
};

class Student : public User {
    char name[50];

public:
    Student() {}
    Student(char n[], char u[], char p[]) : User(u, p) {
        strcpy(name, n);
    }
    char* getName() {
        return name;
    }
};

class Admin : public User {
public:
    Admin() {}
    Admin(char u[], char p[]) : User(u, p) {}
};

class Hostel {
    Room rooms[100];
    int numRooms;
public:
    Hostel() {
        numRooms = 0;
    }

    // Function to add a room
    void addRoom(char type[], int price) {
        rooms[numRooms++] = Room(numRooms + 1, price, true, type);
    }
    void removeRoom(int roomNo) {
        for (int i = 0; i < numRooms; i++) {
            if (rooms[i].getRoomNo() == roomNo) {
                rooms[i] = rooms[--numRooms];
                break;
            }
        }
    }
    // Function to display all rooms in table format with headers
    void displayRooms() {
        cout << "Room No.\tType\tPrice(GHC)\tAvailability" << endl;
        for (int i = 0; i < numRooms; i++) {
            cout << rooms[i].getRoomNo() << "\t\t" << rooms[i].getType() << "\t" << rooms[i].getPrice() << "\t\t" << (rooms[i].available() ? "Available" : "Not Available") << endl;
        }
    }
// Function to find a room by type and maxprice and display
Room* findRoom(char type[], int maxPrice) {
    cout << "Room No.\tType\tPrice\tAvailability" << endl;
    for (int i = 0; i < numRooms; i++) {
        if (strcmp(rooms[i].getType(), type) == 0 && rooms[i].getPrice() <= maxPrice) {
            cout << rooms[i].getRoomNo() << "\t\t" << rooms[i].getType() << "\t" << rooms[i].getPrice() << "\t" << (rooms[i].available() ? "Available" : "Not Available") << endl;
        }
    }

    return NULL;
}

Room* getRoom(int roomNo) {
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].getRoomNo() == roomNo) {
            return &rooms[i];
        }
    }
    return NULL;
}
void bookRoom(int roomNo, char studentName[], int studentId) {
    Room* room = getRoom(roomNo);
    if (room != NULL && room->available()) {
        room->book();
        room->setStudentName(studentName);
        room->setStudentId(studentId);

        cout << "Room " << roomNo << " booked successfully!" << endl;
    }
    else {
        cout << "Room not available." << endl;
    }
}
void unbookRoom(int roomNo, char studentName[], int studentId) {
    // check if input matches room occupant
    Room* room = getRoom(roomNo);
    if (room != NULL && !room->available() && strcmp(room->getStudentName(), studentName) == 0 && room->getStudentId() == studentId) {
        room->unbook();
        cout << "Room " << roomNo << " unbooked successfully!" << endl;
    }
    else {
        cout << "Room not booked or Details incorrect!" << endl;
    /*Room* room = getRoom(roomNo);
    if (room != NULL && !room->available()) {
        room->unbook();
        room->setStudentName("");// set student name to empty string
        room->setStudentId(0);// set student id to 0
        cout << "Room unbooked successfully!" << endl;
    }
    else {
        cout << "Room not found or already available." << endl;
    }*/
    }
}
void displayStudents() {
    cout << "Room No.\tStudent Name\tStudent ID" << endl;
    for (int i = 0; i < numRooms; i++) {
        if (!rooms[i].available()) {
            cout << rooms[i].getRoomNo() << "\t\t" << rooms[i].getStudentName() << "\t\t" << rooms[i].getStudentId() << endl;
        }
    }}
int getNumRooms() {
    cout << "Number of rooms: " << numRooms << endl;
}
};

// File handling functions

void saveRooms(Hostel h) {
ofstream file("rooms.dat", ios::binary);
file.write((char*)&h, sizeof(h));
file.close();
}

Hostel loadRooms() {
Hostel h;
ifstream file("rooms.dat", ios::binary);
if (file) {
file.read((char*)&h, sizeof(h));
file.close();
}
return h;
}
// file to store students in room and their details
void saveStudents(Hostel h) {
ofstream file("students.dat", ios::binary);
file.write((char*)&h, sizeof(h));
file.close();
}
Hostel loadStudents() {
Hostel h;
ifstream file("students.dat", ios::binary);
if (file) {
file.read((char*)&h, sizeof(h));
file.close();
}
return h;
}


int main() {// Main function
Hostel h = loadRooms();
Admin a;
// Menu as admin or student
int choice;
while (true) {
cout << "\nwelcome to hostel management system" << endl;
cout << "-----------------------------------" << endl;
cout << "login as:" << endl;
cout << "1. Admin" << endl;
cout << "2. Student" << endl;
cout << "3. Exit" << endl;
cout << "Enter choice: ";
cin >> choice;
// Admin login
if (choice == 1) {
    char inputusername, inputpassword;
    cout << "Enter username: ";
    cin >> inputusername;
    cout << "Enter password: ";
    cin >> inputpassword;
    //Admin a(username, password);
    //a.authenticate;
    cout << "Login successful!" << endl;
    // Menu for admin
    int choice;
    while (true){
    cout << "\n----------------" << endl;
    cout << " welcome, Admin " << endl;
    cout << "----------------" << endl;
    cout << "1. Add room" << endl;
    cout << "2. Remove room" << endl;
    cout << "3. Display rooms" << endl;
    cout << "4. Assign student to a room" << endl;
    cout << "5. Unbook student from room" << endl;
    cout << "6. Display students in a room" << endl;
    cout << "7. Logout" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    // Add room
    if (choice == 1) {
        char type[10];
        int price;
        int roomNo = h.getNumRooms() + 1;
        cout << "Enter type(1in1, 2in1, 3in1 or 4in1): ";
        cin >> type;
        cout << "Enter price in GHc: ";
        cin >> price;
        h.addRoom(type, price);
        saveRooms(h);
        cout << "Room added successfully!" << endl;
        cout << "Press any key to continue..." << endl;
        getch();

    }
    // Remove room
    else if (choice == 2) {
        int roomNo;
        cout << "Enter room no.: ";
        cin >> roomNo;
        h.removeRoom(roomNo);
        saveRooms(h);
        cout << "Room removed successfully!" << endl;
        cout << "Press any key to continue..." << endl;
        getch();
    }
    // Display rooms
    else if (choice == 3) {
        cout << "\nRooms:" << endl;
        cout << "-------------------------------------------------------" << endl;
        h.displayRooms();
        cout << "Press any key to continue..." << endl;
    }
    // Assign student to a room and saveStudent
    else if (choice == 4) {
        int roomNo;
        char studentName[20];
        int studentId;
        cout << "Enter room no.: ";
        cin >> roomNo;
        cout << "Enter student name: ";
        cin >> studentName;
        cout << "Enter student ID: ";
        cin >> studentId;
        h.bookRoom(roomNo, studentName, studentId);
        saveRooms(h);
        saveStudents(h);
        cout << "Press any key to continue..." << endl;
        getch();

    }
    // Unbook room with student details
    else if (choice == 5) {
        int roomNo;
        char studentName[20];
        int studentId;
        cout << "Enter room no.: ";
        cin >> roomNo;
        cout << "Enter student name: ";
        cin >> studentName;
        cout << "Enter student ID: ";
        cin >> studentId;
        h.unbookRoom(roomNo, studentName, studentId);
        saveRooms(h);
        cout << "Press any key to continue..." << endl;
        getch();
    }
    //displayStudents
    else if (choice == 6) {
        h.displayStudents();
        cout << "Press any key to continue..." << endl;
        getch();
    }

    // Logout
    else if (choice == 7) {
        cout << "Logging out..." << endl;
        cout << "Logged out successfully!" << endl;
        cout << "Press any key to continue..." << endl;
        getch();

        break;
    }
    // Invalid choice
    else {
        cout << "Invalid choice! Try again" << endl;
        cout << endl;
    }}
    }
    // menu for student
else if (choice == 2) {
        cout << "\nWelcome, Student!" << endl;
        cout << "-----------------" << endl;
        cout << "1. Find room" << endl;
        cout << "2. Book room" << endl;
        cout << "3. Unbook room" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        // Find room
        if (choice == 1) {
            char type[10];
            int maxPrice;
            int roomNo;
            cout << "Enter type(1in1, 2in1, 3in1 or 4in1): ";
            cin >> type;
            cout << "Enter max price: ";
            cin >> maxPrice;
            Room* room = h.findRoom(type, maxPrice);
            /*if (room != NULL) {
                room->display();
            }
            else {
                cout << "Room not found." << endl;
            }*/
        }
        // Book room
        else if (choice == 2) {
            int roomNo;
            char studentName[20];
            int studentId;
            cout << "Enter room no.: ";
            cin >> roomNo;
            cout << "Enter student name: ";
            cin >> studentName;
            cout << "Enter student ID: ";
            cin >> studentId;
            h.bookRoom(roomNo, studentName, studentId);
            saveRooms(h);
            saveStudents(h);
        }
        // Unbook room with student details
        else if (choice == 3) {
            int roomNo;
            char studentName[20];
            int studentId;
            cout << "Enter room no.: ";
            cin >> roomNo;
            cout << "Enter student name: ";
            cin >> studentName;
            cout << "Enter student ID: ";
            cin >> studentId;
            h.unbookRoom(roomNo, studentName, studentId);
            saveRooms(h);
            saveStudents(h);
        }
    }
else if (choice == 3) {
        break;
    }
    else {
        cout << "\nInvalid choice, Try again" << endl;
}
}
return 0;
}

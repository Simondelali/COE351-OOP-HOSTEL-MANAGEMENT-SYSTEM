#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <string>
using namespace std;

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
class User{
public:
    string username;
    string password;
};
class Admin : public User{
public:
    Admin(){
    username = "admin1";
    password = "pass1";
}
// function to authenticate admin
bool authenticate(string username, string password){
    if (this->username == username && this->password == password){
        return true;
    }else{return false;}
}
};

class Hostel {
    Room rooms[100]; /
    int numRooms;
public:
    Hostel() { // Constructor
        numRooms = 0;
    }

    // Function to add a room
    void addRoom(char type[], int price) {
        rooms[numRooms++] = Room(numRooms + 1, price, true, type);
    }
    // Function to remove a room
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
// Function to get a room by room number
Room* getRoom(int roomNo) {
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].getRoomNo() == roomNo) { // if room number is found
            return &rooms[i]; 
        }
    }
    return NULL; // room not found
}
// Function to book a room
void bookRoom(int roomNo, char studentName[], int studentId) {
    Room* room = getRoom(roomNo); // get room by room number
    if (room != NULL && room->available()) { // if room is available
        room->book(); // book room
        room->setStudentName(studentName); // set student name
        room->setStudentId(studentId); // set student id

        cout << "Room " << roomNo << " booked successfully!" << endl;
    }
    else {
        cout << "Room not available." << endl;
    }
}
// Function to unbook a room
void unbookRoom(int roomNo, char studentName[], int studentId) {
    Room* room = getRoom(roomNo); // get room by room number
    // if room is not available and student name and id match
    if (room != NULL && !room->available() && strcmp(room->getStudentName(), studentName) == 0 && room->getStudentId() == studentId) {
        room->unbook();
        cout << "Room " << roomNo << " unbooked successfully!" << endl;
    }
    else {
        cout << "Room not booked or Details incorrect!" << endl;
    }
}
// Function to display all booked rooms
void displayStudents() {
    cout << "Room No.\tStudent Name\tStudent ID" << endl;
    for (int i = 0; i < numRooms; i++) {
        if (!rooms[i].available()) { // if room is not available
            cout << rooms[i].getRoomNo() << "\t\t" << rooms[i].getStudentName() << "\t\t" << rooms[i].getStudentId() << endl;
        }
    }}
// Function to get number of rooms
int getNumRooms() { 
    cout << "Number of rooms: " << numRooms << endl;
}
};


// File handling functions

// file to store rooms and their details
void saveRooms(Hostel h) {
ofstream file("rooms.dat", ios::binary); // open file in binary mode
file.write((char*)&h, sizeof(h)); // write to file
file.close(); // close file
}

// load rooms from file
Hostel loadRooms() {
Hostel h; // create hostel object
ifstream file("rooms.dat", ios::binary); // open file in binary mode
if (file) { // if file exists
file.read((char*)&h, sizeof(h)); // read from file
file.close(); // close file
}
return h; // return hostel object
}

// file to store students in room and their details
void saveStudents(Hostel h) { 
ofstream file("students.dat", ios::binary); // open file in binary mode
file.write((char*)&h, sizeof(h)); // write to file
file.close(); // close file
}

// load students from file
Hostel loadStudents() {
Hostel h; // create hostel object
ifstream file("students.dat", ios::binary); // open file in binary mode
if (file) { // if file exists
file.read((char*)&h, sizeof(h)); // read from file
file.close(); // close file
}
return h; // return hostel object
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
    string username,password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    if (a.authenticate(username, password)){ // if username and password match
        cout << "Login successful!" << endl;

    }else{
        cout << "Login Failed!" <<endl;
        break;
        }

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
        int roomNo = h.getNumRooms() + 1; // get number of rooms and add 1
        cout << "Enter type(1in1, 2in1, 3in1 or 4in1): ";
        cin >> type;
        cout << "Enter price in GHc: ";
        cin >> price;
        h.addRoom(type, price); // add room
        saveRooms(h); // save rooms to file 
        cout << "Room added successfully!" << endl;
        cout << "Press any key to continue..." << endl;
        getch(); // wait for user input

    }
    // Remove room
    else if (choice == 2) {
        int roomNo;
        cout << "Enter room no.: ";
        cin >> roomNo;
        h.removeRoom(roomNo); // remove room
        saveRooms(h); // save rooms to file
        cout << "Room removed successfully!" << endl;
        cout << "Press any key to continue..." << endl;
        getch(); // wait for user input
    }
    // Display rooms
    else if (choice == 3) {
        cout << "\nRooms:" << endl;
        cout << "-------------------------------------------------------" << endl;
        h.displayRooms(); // display rooms
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
        h.bookRoom(roomNo, studentName, studentId); // book room
        saveRooms(h); // save rooms to file
        saveStudents(h); // save students to file
        cout << "Press any key to continue..." << endl;
        getch(); // wait for user input

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
        h.unbookRoom(roomNo, studentName, studentId); // unbook room
        saveRooms(h); // save rooms to file
        cout << "Press any key to continue..." << endl;
        getch(); // wait for user input
    }
    //displayStudents
    else if (choice == 6) {
        h.displayStudents(); // display students
        cout << "Press any key to continue..." << endl;
        getch(); // wait for user input
    }

    // Logout
    else if (choice == 7) {
        cout << "Logging out..." << endl;
        cout << "Logged out successfully!" << endl;
        cout << "Press any key to continue..." << endl;
        getch(); // wait for user input

        break; // break out of loop
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
            //if there are no rooms
            
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

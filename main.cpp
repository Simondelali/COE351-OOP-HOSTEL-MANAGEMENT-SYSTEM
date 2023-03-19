#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Class definitions

class Room {
    int roomNo;
    int price;
    bool isAvailable;
    char type[10];
    char occupant[50];
public:
    Room() {}
    Room(int r, int p, bool a, char t[]) {
        roomNo = r;
        price = p;
        isAvailable = a;
        strcpy(type, t);
    }
    void display() {
        cout << "Room No.: " << roomNo << endl;
        cout << "Type: " << type << endl;
        cout << "Price: " << price << endl;
        cout << "Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
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
    // Function to set occupant of room
    void setOccupant(char o[]) {
        strcpy(occupant, o);
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
    char username[20];
    char password[20];
public:
    Student() {}
    Student(char n[], char u[], char p[]) : User(u, p) {
        strcpy(name, n);
    }
    char* getName() {
        return name;
    }
    // authenticate function to check if username and password are correct
    bool authenticate(char u[], char p[]) {
        return strcmp(u, username) == 0 && strcmp(p, password) == 0;
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
    void displayRooms() {
        for (int i = 0; i < numRooms; i++)
            rooms[i].display();
            cout << endl;
    }

Room* findRoom(char type[], int maxPrice) {
    for (int i = 0; i < numRooms; i++) {
        if (strcmp(rooms[i].getType(), type) == 0 && rooms[i].getPrice() <= maxPrice && rooms[i].available()) {
            return &rooms[i];
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
void bookRoom(int roomNo) {
    Room* room = getRoom(roomNo);
    if (room != NULL && room->available()) {
        room->book();
        cout << "Room booked successfully!" << endl;
    }
    else {
        cout << "Room not available." << endl;
    }
}
void unbookRoom(int roomNo) {
    Room* room = getRoom(roomNo);
    if (room != NULL && !room->available()) {
        room->unbook();
        cout << "Room unbooked successfully!" << endl;
    }
    else {
        cout << "Room not found or already available." << endl;
    }
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

int main() {// Main function
Hostel h = loadRooms();
// Menu as admin or student
int choice;
cout << "welcome to hostel management system" << endl;
cout << "-----------------------------------" << endl;
cout << "login as:" << endl;
cout << "1. Admin" << endl;
cout << "2. Student" << endl;
cout << "Enter choice: ";
cin >> choice;
// Admin login
if (choice == 1) {
    char username[20], password[20];
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    Admin a(username, password);
    // Menu for admin
    int choice;
    cout << "1. Add room" << endl;
    cout << "2. Remove room" << endl;
    cout << "3. Display rooms" << endl;
    cout << "4. Book room" << endl;
    cout << "5. Unbook room" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    // Add room
    if (choice == 1) {
        char type[10];
        int price;
        cout << "Enter type: ";
        cin >> type;
        cout << "Enter price: ";
        cin >> price;
        h.addRoom(type, price);
        saveRooms(h);
    }
    // Remove room
    else if (choice == 2) {
        int roomNo;
        cout << "Enter room no.: ";
        cin >> roomNo;
        h.removeRoom(roomNo);
        saveRooms(h);
    }
    // Display rooms
    else if (choice == 3) {
        h.displayRooms();
    }
    // Book room
    else if (choice == 4) {
        int roomNo;
        cout << "Enter room no.: ";
        cin >> roomNo;
        h.bookRoom(roomNo);
        saveRooms(h);
    }
    // Unbook room
    else if (choice == 5) {
        int roomNo;
        cout << "Enter room no.: ";
        cin >> roomNo;
        h.unbookRoom(roomNo);
        saveRooms(h);
    }
}

    // menu for student
else if (choice == 2) {
       /* char username[20], password[20];
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        Student s(username, password);
        // Menu for student
        int choice;*/
        cout << "1. Find room" << endl;
        cout << "2. Book room" << endl;
        cout << "3. Unbook room" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        // Find room
        if (choice == 1) {
            char type[10];
            int maxPrice;
            cout << "Enter type: ";
            cin >> type;
            cout << "Enter max price: ";
            cin >> maxPrice;
            Room* room = h.findRoom(type, maxPrice);
            if (room != NULL) {
                room->display();
            }
            else {
                cout << "Room not found." << endl;
            }
        }
        // Book room
        else if (choice == 2) {
            int roomNo;
            cout << "Enter room no.: ";
            cin >> roomNo;
            h.bookRoom(roomNo);
            saveRooms(h);
        }
        // Unbook room
        else if (choice == 3) {
            int roomNo;
            cout << "Enter room no.: ";
            cin >> roomNo;
            h.unbookRoom(roomNo);
            saveRooms(h);
        }
    }
    return 0;

}


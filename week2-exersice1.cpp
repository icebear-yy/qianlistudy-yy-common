#include <iostream>
#include <string>
using namespace std;

class MotorController {
private:
    int speed;       
    bool key;        
    bool direction;  

public:
    MotorController() : speed(0), key(false), direction(false) {}
    void checkSpeed() {
        cout << "The speed of motor is: " << speed << endl;
    }

    
    void changeSpeed() {
        if (!key) {
            cout << "Motor is off. Please turn it on first.\n";
            return;
        }

        int newSpeed;
        cout << "Enter the speed you want to change to (0-100): ";
        cin >> newSpeed;

        if (newSpeed >= 0 && newSpeed <= 100) {
            speed = newSpeed;
            cout << "Speed updated to: " << speed << endl;
        } else {
            cout << "Invalid speed. Please enter a value between 0 and 100.\n";
        }
    }


    void checkDirection() {
        if (direction) {
            cout << "The motor is rotating counterclockwise.\n";
        } else {
            cout << "The motor is rotating clockwise.\n";
        }
    }

    
    void changeDirection() {
        if (!key) {
            cout << "Motor is off. Please turn it on first.\n";
            return;
        }

        direction = !direction;
        cout << "Direction changed.\n";
        checkDirection();
    }

    
    void toggleKey() {
        int choice;
        cout << "1. Turn on the motor\n";
        cout << "2. Turn off the motor\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            key = true;
            cout << "Motor is now ON.\n";
        } else if (choice == 2) {
            key = false;
            speed = 0;  
            cout << "Motor is now OFF. Speed reset to 0.\n";
        } else {
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }


    void checkKey() {
        if (key) {
            cout << "The motor is running.\n";
        } else {
            cout << "The motor is off.\n";
        }
    }
};

int main() {
    MotorController motor;  
    int choice;

    while (true) {
        
        cout << "\n--- Motor Controller Menu ---\n";
        cout << "1. Turn ON/OFF Motor\n";
        cout << "2. Check Motor Direction\n";
        cout << "3. Check Motor Speed\n";
        cout << "4. Change Motor Direction\n";
        cout << "5. Change Motor Speed\n";
        cout << "6. Exit Program\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                motor.toggleKey();
                break;
            case 2:
                motor.checkDirection();
                break;
            case 3:
                motor.checkSpeed();
                break;
            case 4:
                motor.changeDirection();
                break;
            case 5:
                motor.changeSpeed();
                break;
            case 6:
                cout << "Exiting program.\n";
                return 0;  
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

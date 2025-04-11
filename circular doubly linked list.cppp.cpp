#include <iostream>       // Include the iostream library for input and output operations.  
#include <string>         // Include the string library to use the std::string class.  
using namespace std;      // Use the standard namespace to avoid prefixing std::.

// Structure for employee node
struct EmployeeNode {                  // Define a new structure for an employee node.
	string name;                       // Variable to store the employee name.
	string jobTitle;                   // Variable to store the job title of the employee.
	double salary;                     // Variable to store the employee's salary.
	EmployeeNode *next;                // Pointer to the next node in the circular linked list.
	EmployeeNode *prev;                // Pointer to the previous node in the circular linked list.
};

// Circular Doubly Linked List class
class CircularDoublyLinkedList {       // Define class for the circular doubly linked list.
	private:
		EmployeeNode *head;             // Pointer to the head node of the list.
	public:
		// Constructor initializes head to nullptr
		CircularDoublyLinkedList() {    // Constructor for the CircularDoublyLinkedList class.
			head = nullptr;             // Initialize head to nullptr (empty list).
		}
		// Insert at beginning
		void insertAtBeginning(string name, string jobTitle, double salary) { // Method to insert a node at the beginning.
			EmployeeNode *newNode = new EmployeeNode{name, jobTitle, salary, nullptr, nullptr}; // Create a new employee node.
			if (!head) {                 // Check if the list is empty.
				// First node points to itself in both directions
				newNode->next = newNode; // Set next and prev to point to itself.
				newNode->prev = newNode; // Set prev to point to itself.
				head = newNode;          // Update the head to the new node.
			} else {
				EmployeeNode *tail = head->prev;  // Get the tail node (previous node of head).
				newNode->next = head;      // Point newNode's next to head.
				newNode->prev = tail;      // Point newNode's prev to tail.
				head->prev = tail->next = newNode; // Link the new node properly.
				head = newNode;            // Update head to newNode.
			}
			cout << "Inserted at beginning: " << name << endl; // Output the insertion result.
		}
		// Insert at end
		void insertAtEnd(string name, string jobTitle, double salary) { // Method to insert a node at the end.
			EmployeeNode *newNode = new EmployeeNode{name, jobTitle, salary, nullptr, nullptr}; // Create new employee node.
			if (!head) {                 // Check if the list is empty.
				newNode->next = newNode; // Set next and prev to point to itself.
				newNode->prev = newNode; // Set prev to point to itself.
				head = newNode;          // Update head to the new node.
			} else {
				EmployeeNode *tail = head->prev; // Get the tail node.
				tail->next = newNode;      // Link tail's next to the new node.
				newNode->prev = tail;      // Set newNode's prev to tail.
				newNode->next = head;      // Set newNode's next to head.
				head->prev = newNode;      // Update head's prev to newNode.
			}
			cout << "Inserted at end: " << name << endl; // Output the insertion result.
		}
		// Insert at a specific position
		void insertAtPosition(string name, string jobTitle, double salary,
		                      int pos) { // Method to insert at a specific position.
			if (pos <= 1 || !head) {  // If position is 1 or less, or the list is empty, insert at beginning.
				insertAtBeginning(name, jobTitle, salary); // Call method to insert at beginning.
				return;              // Exit the method.
			}
			EmployeeNode *newNode = new EmployeeNode{name, jobTitle, salary, nullptr, nullptr}; // Create new node.
			EmployeeNode *temp = head; // Start from head to find the position.
			for (int i = 1; i < pos - 1 && temp->next != head; ++i) { // Traverse to the position.
				temp = temp->next; // Move to the next node.
			}
			newNode->next = temp->next; // Link newNode's next to temp's next.
			newNode->prev = temp;        // Link newNode's prev to temp.
			temp->next->prev = newNode;  // Link the next node's prev to newNode.
			temp->next = newNode;        // Link temp's next to newNode.
			cout << "Inserted at position " << pos << ": " << name << endl; // Output the insertion result.
		}
		// Delete from beginning
		void deleteFromBeginning() {      // Method to delete a node from the beginning.
			if (!head) {                   // Check if the list is empty.
				cout << "List is empty." << endl; // Output message if the list is empty.
				return;                    // Exit the method.
			}
			if (head->next == head) {    // Check if there's only one node in the list.
				delete head;             // Delete the head node.
				head = nullptr;          // Set head to nullptr to indicate list is now empty.
			} else {
				EmployeeNode *tail = head->prev; // Get the tail node.
				EmployeeNode *toDelete = head;   // Node to delete is the current head.
				head = head->next;      // Move head to the next node.
				head->prev = tail;      // Update new head's previous pointer.
				tail->next = head;      // Update tail's next pointer.
				delete toDelete;        // Delete the old head node.
			}
			cout << "Deleted from beginning." << endl; // Output deletion result.
		}
		// Delete from end
		void deleteFromEnd() {             // Method to delete a node from the end.
			if (!head) {                   // Check if the list is empty.
				cout << "List is empty." << endl; // Output message if the list is empty.
				return;                    // Exit the method.
			}
			if (head->next == head) {    // Check if there's only one node in the list.
				delete head;             // Delete the head node.
				head = nullptr;          // Set head to nullptr to indicate the list is empty.
			} else {
				EmployeeNode *tail = head->prev; // Get the tail node.
				EmployeeNode *newTail = tail->prev; // Get the new tail node (previous node).
				newTail->next = head;   // Link new tail's next to head.
				head->prev = newTail;   // Link head's previous to new tail.
				delete tail;            // Delete the old tail node.
			}
			cout << "Deleted from end." << endl; // Output deletion result.
		}
		// Delete from specific position
		void deleteFromPosition(int pos) { // Method to delete a node from a specific position.
			if (!head) {                   // Check if the list is empty.
				cout << "List is empty." << endl; // Output message if the list is empty.
				return;                    // Exit the method.
			}
			if (pos <= 1) {                // If position is 1 or less, delete from beginning.
				deleteFromBeginning();     // Call method to delete from beginning.
				return;                    // Exit the method.
			}
			EmployeeNode *temp = head;      // Start from head to find the position.
			for (int i = 1; i < pos && temp->next != head; ++i) { // Traverse to the position.
				temp = temp->next;         // Move to the next node.
			}
			if (temp == head) {            // If the node to delete is at head.
				deleteFromBeginning();     // Call method to delete from beginning.
			} else {
				temp->prev->next = temp->next; // Link previous node’s next to the current node’s next.
				temp->next->prev = temp->prev; // Link next node's prev to the current node’s prev.
				delete temp;                // Delete the current node.
			}
			cout << "Deleted from position " << pos << endl; // Output deletion result.
		}
		// Search for employee by name
		void searchForElement(string name) { // Method to search for an employee by name.
			if (!head) {                   // Check if the list is empty.
				cout << "List is empty." << endl; // Output message if the list is empty.
				return;                    // Exit the method.
			}
			EmployeeNode *temp = head;      // Start from head to search.
			do {
				if (temp->name == name) {   // Check if the current node's name matches the search name.
					// Output found employee details
					cout << "Found: Name: " << temp->name << ", Job: " << temp->jobTitle << ", Salary: " << temp->salary << endl;
					return;                // Exit the method once found.
				}
				temp = temp->next;         // Move to the next node.
			} while (temp != head);        // Continue until we loop back to the head.
			cout << "Employee not found." << endl; // Output if employee was not found.
		}
		// Display list horizontally
		void displayList() {               // Method to display the entire list horizontally.
			if (!head) {                   // Check if the list is empty.
				cout << "List is empty." << endl; // Output message if the list is empty.
				return;                    // Exit the method.
			}
			EmployeeNode *temp = head;      // Start from head for display.
			do {
				// Output employee details from current node
				cout << "{Name: " << temp->name << ", Job: " << temp->jobTitle << ", Salary: " << temp->salary << "}";
				temp = temp->next;         // Move to the next node.
				if (temp != head)           // Check if it's not back to head.
					cout << " <=> ";        // Print separator if needed.
			} while (temp != head);        // Continue until we loop back to the head.
			cout << " <=> (head)" << endl; // Indicate the head node in the display.
		}

		// Destructor
		~CircularDoublyLinkedList() {      // Destructor for the class to free memory.
			while (head)                  // Keep deleting until the list is empty.
				deleteFromBeginning();     // Call method to delete from beginning.
		}
};

// Main function
int main() {
	CircularDoublyLinkedList list;       // Create an instance of CircularDoublyLinkedList.
	int choice;                         // Variable for menu choice.
	do {
		// Display menu options to the user
		cout << "\nCircular Doubly Linked List MENU\n";
		cout << "1. Insert at beginning\n2. Insert at end\n3. Insert at position\n4. Delete from beginning\n";
		cout << "5. Delete from end\n6. Delete from position\n7. Search for element\n8. Display list\n9. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;                   // Read user choice from input.
		if (cin.fail()) {                // Check for invalid input failure.
			cin.clear();                // Clear the error state.
			cin.ignore(10000, '\n');    // Ignore the rest of the line.
			cout << "Invalid input. Please enter a number between 1 and 9.\n"; // Output error message.
			continue;                    // Skip to the next iteration of the loop.
		}
		string name, jobTitle;   // Variables for inputting employee details.
		double salary;    // Variable for salary input.
		int pos;             // Variable for position input.
		switch (choice) {   // Switch statement to handle the menu choice.
			case 1:   // Case for inserting at the beginning.
				cout << "Enter Name: "; // Prompt for name input.
				cin >> name;   // Read name input.
				cout << "Enter Job Title: "; // Prompt for job title input.
				cin >> jobTitle;    // Read job title input.
				cout << "Enter Salary: "; // Prompt for salary input.
				cin >> salary;    // Read salary input.
				if (cin.fail()) {   // Check for invalid salary input.
					cin.clear();  // Clear the error state.
					cin.ignore(10000, '\n'); // Ignore the rest of the line.
					cout << "Invalid salary input.\n"; // Output error message.
					break;  // Break out of the switch case.
				}
				list.insertAtBeginning(name, jobTitle, salary); // Insert employee at beginning.
				break;  // Break out of the switch case.
			case 2:       // Case for inserting at the end.
				cout << "Enter Name: "; // Prompt for name input.
				cin >> name;     // Read name input.
				cout << "Enter Job Title: "; // Prompt for job title input.
				cin >> jobTitle;    // Read job title input.
				cout << "Enter Salary: "; // Prompt for salary input.
				cin >> salary;     // Read salary input.
				if (cin.fail()) {     // Check for invalid salary input.
					cin.clear();  // Clear the error state.
					cin.ignore(10000, '\n'); // Ignore the rest of the line.
					cout << "Invalid salary input.\n"; // Output error message.
					break;   // Break out of the switch case.
				}
				list.insertAtEnd(name, jobTitle, salary); // Insert employee at end.
				break;  // Break out of the switch case.
			case 3:    // Case for inserting at a specific position.
				cout << "Enter Name: "; // Prompt for name input.
				cin >> name;           // Read name input.
				cout << "Enter Job Title: "; // Prompt for job title input.
				cin >> jobTitle;       // Read job title input.
				cout << "Enter Salary: "; // Prompt for salary input.
				cin >> salary;         // Read salary input.
				cout << "Enter Position: "; // Prompt for position input.
				cin >> pos;       // Read position input.
				if (cin.fail()) {   // Check for invalid input.
					cin.clear();     // Clear the error state.
					cin.ignore(10000, '\n'); // Ignore the rest of the line.
					cout << "Invalid input.\n"; // Output error message.
					break;    // Break out of the switch case.
				}
				list.insertAtPosition(name, jobTitle, salary, pos); // Insert employee at position.
				break;   // Break out of the switch case.
			case 4:  // Case for deleting from the beginning.
				list.deleteFromBeginning(); // Call method to delete from beginning.
				break;    // Break out of the switch case.
			case 5:     // Case for deleting from the end.
				list.deleteFromEnd();   // Call method to delete from end.
				break;    // Break out of the switch case.
			case 6:    // Case for deleting from a specific position.
				cout << "Enter Position: "; //ask for position input.
				cin >> pos;   // Read position input.
				if (cin.fail()) {  // Check for invalid input.
					cin.clear();    // Clear the error state.
					cin.ignore(10000, '\n'); // Ignore the rest of the line.
					cout << "Invalid position input.\n"; // Output error message.
					break;   // Break out of the switch case.
				}
				list.deleteFromPosition(pos); // Call method to delete from position.
				break;   // Break out of the switch case.
			case 7:   // Case for searching for an employee by name.
				cout << "Enter Name to search: "; // Prompt for name to search.
				cin >> name; // Read name input.
				list.searchForElement(name); // Call method to search for employee.
				break;  // Break out of the switch case.
			case 8:   // Case for displaying the list.
				list.displayList(); // Call method to display the list.
				break; // Break out of the switch case.
			case 9:   // Case for exiting the program.
				cout << "Exiting..." << endl; // Output exit message.
				break;    // Break out of the switch case.
			default:  // Default case for invalid choice.
				cout << "Invalid choice. Please choose between 1 and 9." << endl; // Output error message.
		} // End of switch statement.
	} while (choice != 9); // Repeat the loop until user chooses to exit.
	return 0; // Return success exit code from main.
} // End of main function.
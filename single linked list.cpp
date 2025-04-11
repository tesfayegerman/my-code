#include <iostream>  // Include the input-output stream library for standard I/O operations  
#include <string>    // Include the string library to use std::string  
using namespace std; // Use the standard namespace to avoid prefixing std::

// Structure to define an EmployeeNode
struct EmployeeNode {
	string name;          // The name of the employee
	string jobTitle;      // The job title of the employee
	double salary;        // The salary of the employee
	EmployeeNode *next;   //means "declare a pointer named next that points to an EmployeeNode."
};
// Circular Singly Linked List class to manage EmployeeNode elements
class CircularLinkedList {
		/*The last node points back to the first node, forming a circle.
		                           There is no NULL at the end, unlike normal linked lists.*/
	private:
		EmployeeNode *head; // Pointer to the head node of the circular linked list
	public:
		// Constructor to initialize an empty linked list
		CircularLinkedList() {
			head = nullptr; // Initially, the head is set to nullptr, indicating the list is empty
		}
		// 1. Insert a new node at the beginning of the list
		void insertAtBeginning(string name, string jobTitle, double salary) {
			EmployeeNode *newNode = new EmployeeNode{name, jobTitle, salary, nullptr}; // Create a new EmployeeNode
			if (!head) { // Check if the list is empty
				head = newNode; // Set the head to the new node
				head->next = head; // Make the new node point to itself, forming a circular link
			} else { // If the list is not empty
				EmployeeNode *temp = head; // Temporary pointer to find the last node
				while (temp->next != head) // Loop to find the last node
					temp = temp->next; // Move to the next node
				temp->next = newNode; // The last node points to the new node
				newNode->next = head; // The new node points to the head
				head = newNode; // Update the head to the new node
			}
			cout << "Inserted at beginning: " << name << endl; // Confirmation message
		}
		// 2. Insert a new node at the end of the list
		void insertAtEnd(string name, string jobTitle, double salary) {
			EmployeeNode *newNode = new EmployeeNode{name, jobTitle, salary, nullptr}; // Create a new EmployeeNode
			if (!head) { // Check if the list is empty
				head = newNode; // Set the head to the new node
				head->next = head; // Make the new node point to itself
			} else { // If the list is not empty
				EmployeeNode *temp = head; // Temporary pointer to find the last node
				while (temp->next != head) // Loop to find the last node
					temp = temp->next; // Move to the next node
				temp->next = newNode; // The last node now points to the new node
				newNode->next = head; // The new node points back to the head
			}
			cout << "Inserted at end: " << name << endl; // Confirmation message
		}
		// 3. Insert a new node at a specific position in the list
		void insertAtPosition(string name, string jobTitle, double salary, int pos) {
			if (pos <= 1) { // If the position is less than or equal to 1
				insertAtBeginning(name, jobTitle, salary); // Call the method to insert at the beginning
				return; // Exit the function
			}
			EmployeeNode *newNode = new EmployeeNode{name, jobTitle, salary, nullptr}; // Create a new node
			EmployeeNode *temp = head; // Temporary pointer to traverse the list
			for (int i = 1; i < pos - 1 && temp->next != head; ++i) { // Traverse to the desired position
				temp = temp->next; // Move to the next node
			}
			newNode->next = temp->next; // Set the new node's next to the current node's next
			temp->next = newNode; // Make the current node point to the new node
			cout << "Inserted at position " << pos << ": " << name << endl; // Confirmation message
		}
		// 4. Delete the first node from the list
		void deleteFromBeginning() {
			if (!head) { // If the list is empty
				cout << "List is empty." << endl; // Print message and exit
				return; // Exit the function
			}
			if (head->next == head) { // If there's only one node in the list
				delete head; // Delete the head node
				head = nullptr; // Set head to null
			} else { // If there are multiple nodes
				EmployeeNode *temp = head; // Temporary pointer to find the last node
				while (temp->next != head) // Loop to find the last node
					temp = temp->next; // Move to the next node
				EmployeeNode *toDelete = head; // Node to be deleted
				head = head->next; // Move head to the next node
				temp->next = head; // Last node now points to the new head
				delete toDelete; // Free memory of the old head
			}
			cout << "Deleted from beginning." << endl; // Confirmation message
		}
		// 5. Delete the last node from the list
		void deleteFromEnd() {
			if (!head) { // If the list is empty
				cout << "List is empty." << endl; // Print message and exit
				return; // Exit the function
			}
			if (head->next == head) { // If there's only one node in the list
				delete head; // Delete the head node
				head = nullptr; // Set head to null
			} else { // If there are multiple nodes
				EmployeeNode *temp = head; // Temporary pointer to find the second-to-last node
				while (temp->next->next != head) // Loop until the second-to-last node
					temp = temp->next; // Move to the next node
				delete temp->next; // Delete the last node
				temp->next = head; // Update the second-to-last node to point to head
			}
			cout << "Deleted from end." << endl; // Confirmation message
		}
		// 6. Delete a node from a specific position in the list
		void deleteFromPosition(int pos) {
			if (!head) { // If the list is empty
				cout << "List is empty." << endl; // Print message and exit
				return; // Exit the function
			}
			if (pos <= 1) { // If the position is less than or equal to 1
				deleteFromBeginning(); // Call the function to delete from the beginning
				return; // Exit the function
			}
			EmployeeNode *temp = head; // Temporary pointer to traverse the list
			for (int i = 1; i < pos - 1 && temp->next != head; ++i) { // Traverse to the desired position
				temp = temp->next; // Move to the next node
			}
			EmployeeNode *toDelete = temp->next; // Node to be deleted
			if (toDelete == head) { // If the node to delete is the head
				head = head->next; // Move head to the next node
			}
			temp->next = toDelete->next; // Bypass the node to be deleted
			delete toDelete; // Free the memory of the deleted node
			cout << "Deleted from position " << pos << endl; // Confirmation message
		}
		// 7. Search for an employee by name in the list
		void searchForElement(string name) {
			if (!head) { // If the list is empty
				cout << "List is empty." << endl; // Print message and exit
				return; // Exit the function
			}
			EmployeeNode *temp = head; // Temporary pointer to traverse the list
			do {
				if (temp->name == name) { // Check if the current node's name matches the search name
					// Print the found employee's details
					cout << "Found: Name: " << temp->name << ", Job: " << temp->jobTitle << ", Salary: " << temp->salary << endl;
					return; // Exit the function
				}
				temp = temp->next; // Move to the next node
			} while (temp != head); // Loop until back at the head
			cout << "Employee not found." << endl; // Print if the employee is not found
		}
		// 8. Display all employee nodes in the list
		void displayList() {
			if (!head) { // If the list is empty
				cout << "List is empty." << endl; // Print message and exit
				return; // Exit the function
			}
			EmployeeNode *temp = head; // Temporary pointer to traverse the list
			do {
				// Print the current node's details
				cout << "{Name: " << temp->name << ", Job: " << temp->jobTitle << ", Salary: " << temp->salary << "}";
				temp = temp->next; // Move to the next node
				if (temp != head) // If it?s not back to the head
					cout << " -> "; // Print arrow for formatting
			} while (temp != head); // Loop until back at the head
			cout << " -> (head)" << endl; // Indicate the circular nature of the list
		}
		// Destructor to clean up memory when the list is destroyed
		~CircularLinkedList() { // In C++, the tilde (~) indicates this function is a destructor
			while (head) // While there are still nodes in the list
				deleteFromBeginning(); // Delete from the beginning
		}
};
int main() {
	CircularLinkedList list; // Create a new CircularLinkedList instance
	int choice; // Variable to store user choice
	do {
		// Display menu options
		cout << "\nCircular Singly Linked List MENU\n";
		cout << "1. Insert at beginning\n2. Insert at end\n3. Insert at position\n4. Delete from beginning\n";
		cout << "5. Delete from end\n6. Delete from position\n7. Search for element\n8. Display list\n9. Exit\n";
		cout << "Enter your choice: "; // Prompt user for input
		cin >> choice; // Read user choice
		// Check for invalid input
		if (cin.fail()) {//This checks if cin failed to read input correctly.
			cin.clear(); // Clear the error flag/This clears the error state of cin.
			cin.ignore(10000,
			           '\n'); /* Discard invalid input This discards up to 10,000 characters or until it finds a newline ('\n'), whichever comes first.
                                        It's used to remove the invalid input still left in the input buffer.
                                         Prevents the program from looping with the same bad input again.*/
			cout << "Invalid input. Please enter a number between 1 and 9.\n"; // Error message
			continue; // Skips the rest of the current loop and starts the next iteration
		}
		string name, jobTitle; // Variables to store employee details
		double salary; // Variable to store salary
		int pos; // Variable to store position
		// Handle user's menu choice
		switch (choice) {
			case 1: // Insert at beginning
				cout << "Enter Name: ";
				cin >> name; // Prompt for name
				cout << "Enter Job Title: ";
				cin >> jobTitle; // Prompt for job title
				cout << "Enter Salary: ";
				cin >> salary; // Prompt for salary
				if (cin.fail()) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Invalid salary input.\n"; // Error message
					break; // Exit the switch
				}
				list.insertAtBeginning(name, jobTitle, salary); // Call method to insert at beginning
				break; // Exit the switch
			case 2: // Insert at end
				cout << "Enter Name: ";
				cin >> name; // Prompt for name
				cout << "Enter Job Title: ";
				cin >> jobTitle; // Prompt for job title
				cout << "Enter Salary: ";
				cin >> salary; // Prompt for salary
				if (cin.fail()) { // Check for invalid salary input
					cin.clear();
					cin.ignore(10000, '\n'); // Clear the error flag and discard input
					cout << "Invalid salary input.\n"; // Error message
					break; // Exit the switch
				}
				list.insertAtEnd(name, jobTitle, salary); // Call method to insert at end
				break; // Exit the switch
			case 3: // Insert at position
				cout << "Enter Name: ";
				cin >> name; // Prompt for name
				cout << "Enter Job Title: ";
				cin >> jobTitle; // Prompt for job title
				cout << "Enter Salary: ";
				cin >> salary; // Prompt for salary
				cout << "Enter Position: ";
				cin >> pos; // Prompt for position
				if (cin.fail()) { // Check for invalid salary or position input
					cin.clear();
					cin.ignore(10000, '\n'); // Clear the error flag and discard input
					cout << "Invalid input for salary or position.\n"; // Error message
					break; // Exit the switch
				}
				list.insertAtPosition(name, jobTitle, salary, pos); // Call method to insert at specified position
				break; // Exit the switch

			case 4: // Delete from beginning
				list.deleteFromBeginning(); // Call method to delete from beginning
				break; // Exit the switch

			case 5: // Delete from end
				list.deleteFromEnd(); // Call method to delete from end
				break; // Exit the switch

			case 6: // Delete from position
				cout << "Enter Position: ";
				cin >> pos; // Prompt for position
				if (cin.fail()) { // Check for invalid position input
					cin.clear();
					cin.ignore(10000, '\n'); // Clear the error flag and discard input
					cout << "Invalid input for position.\n"; // Error message
					break; // Exit the switch
				}
				list.deleteFromPosition(pos); // Call method to delete from specified position
				break; // Exit the switch

			case 7: // Search for element
				cout << "Enter Name to search: ";
				cin >> name; // Prompt for name to search
				list.searchForElement(name); // Call method to search for the employee
				break; // Exit the switch

			case 8: // Display list
				list.displayList(); // Call method to display the entire list
				break; // Exit the switch

			case 9: // Exit
				cout << "Exiting..." << endl; // Exit message
				break; // Exit the switch

			default: // Handle invalid choice
				cout << "Invalid choice. Please select between 1 and 9.\n"; // Error message
		}
	} while (choice != 9); // Continue until user chooses to exit
	return 0; // Indicate that the program finished successfully
}
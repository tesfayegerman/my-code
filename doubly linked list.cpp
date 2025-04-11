#include <iostream>     // Include the standard I/O library  
#include <string>       // Include the string library  
#include <limits>       // Include limits for numeric limits  
using namespace std; // Use the standard namespace for convenience

// Class for the Node: Represents each element in the doubly linked list
class Node {
	public:
		string name;   // Name of the car
		string brand;  // Brand of the car
		string model;  // Model of the car
		Node *prev;    // Pointer to the previous node
		Node *next;    // Pointer to the next node

		// Constructor to initialize a node with given name, brand, and model
		Node(const string &n, const string &b, const string &m)
			: name(n), brand(b), model(m), prev(nullptr), next(nullptr) {}
};

// Class for the Doubly Linked List
class DoublyLinkedList {
	private:
		Node *head; // Pointer to the head (first node) of the list
	public:
		// Constructor initializes the list as empty
		DoublyLinkedList() : head(nullptr) {}
		//1. Function to insert a new node at the beginning of the list
		void insertAtBeginning(const string &name, const string &brand, const string &model) {
			Node *newNode = new Node(name, brand, model); // Create a new node
			newNode->next = head; // Link the new node to the current head
			if (head) { // If the list is not empty
				head->prev = newNode; // Set the previous of head to new node
			}
			head = newNode; // Update head to the new node
			cout << "Inserted at beginning: " << name << " " << brand << " " << model << endl;
		}
		//2. Function to insert a new node at the end of the list
		void insertAtEnd(const string &name, const string &brand, const string &model) {
			Node *newNode = new Node(name, brand, model); // Create a new node
			if (!head) { // If the list is empty
				head = newNode; // Set head to the new node
				cout << "Inserted at end: " << name << " " << brand << " " << model << endl;
				return; // Exit the function
			}
			Node *temp = head; // Start from the head
			while (temp->next) { // Traverse to the end of the list
				temp = temp->next;
			}
			temp->next = newNode; // Link the last node to the new node
			newNode->prev = temp; // Link the new node back to the last node
			cout << "Inserted at end: " << name << " " << brand << " " << model << endl;
		}
		//3. Function to insert a node at a specific position
		void insertAtPosition(int position, const string &name, const string &brand, const string &model) {
			if (position < 1) { // Check for a valid position
				cout << "Invalid position!" << endl; // Invalid position error
				return;
			}
			if (position == 1) { // Insert at the beginning if position is 1
				insertAtBeginning(name, brand, model);
				return;
			}
			Node *newNode = new Node(name, brand, model); // Create a new node
			Node *temp = head; // Start from the head
			for (int i = 1; temp && i < position - 1; i++) { // Traverse to the node before the desired position
				temp = temp->next;
			}
			if (!temp) { // If position is out of bounds
				cout << "Position out of bounds!" << endl; // Error message
				delete newNode; // Free the new node
				return;
			}
			newNode->next = temp->next; // Link new node to the next node
			newNode->prev = temp; // Link new node back to temp
			if (temp->next) { // If there is a next node
				temp->next->prev = newNode; // Update the previous link of the next node
			}
			temp->next = newNode; // Link temp to the new node
			cout << "Inserted at position " << position << ": " << name << " " << brand << " " << model << endl;
		}
		// 4. Function to delete a node from the beginning of the list
		void deleteFromBeginning() {
			if (!head) { // If the list is empty
				cout << "List is empty!" << endl; // Error message
				return;
			}
			Node *temp = head; // Store current head
			head = head->next; // Move head to the next node
			if (head) { // If the list is not empty after deletion
				head->prev = nullptr; // Update the previous link of the new head
			}
			delete temp; // Free memory of the old head node
			cout << "Deleted from beginning." << endl; // Confirm deletion
		}
		// 5. Function to delete a node from the end of the list
		void deleteFromEnd() {
			if (!head) { // If the list is empty
				cout << "List is empty!" << endl; // Error message
				return;
			}
			if (!head->next) { // If there is only one node in the list
				delete head; // Free the head node
				head = nullptr; // Set head to nullptr
				cout << "Deleted from end. List is now empty." << endl; // Confirm deletion
				return; // Exit the function
			}
			Node *temp = head; // Start from the head
			while (temp->next) { // Traverse to the last node
				temp = temp->next;
			}
			temp->prev->next = nullptr; // Unlink the last node
			delete temp; // Free memory of the last node
			cout << "Deleted from end." << endl; // Confirm deletion
		}
		//6. Function to delete a node from a specific position
		void deleteFromPosition(int position) {
			if (!head || position < 1) { // Check if list is empty or position is invalid
				cout << "Invalid position or list is empty!" << endl; // Error message
				return;
			}
			if (position == 1) { // If position is 1, delete from the beginning
				deleteFromBeginning();
				return;
			}
			Node *temp = head; // Start from the head
			for (int i = 1; temp && i < position; i++) { // Traverse to the desired position
				temp = temp->next;
			}
			if (!temp) { // If position is out of bounds
				cout << "Position out of bounds!" << endl; // Error message
				return;
			}
			// Adjusting the links to remove the node from the list
			if (temp->prev) {
				temp->prev->next = temp->next; // Link previous node to next node
			}
			if (temp->next) {
				temp->next->prev = temp->prev; // Link next node back to previous node
			}
			delete temp; // Free memory of the deleted node
			cout << "Deleted from position " << position << "." << endl; // Confirm deletion
		}
		//7. Function to search for an element by name
		void searchForElement(const string &name) const {
			Node *temp = head; // Start from the head
			while (temp) { // Traverse through the list
				if (temp->name == name) { // If the element is found
					cout << "Found: " << temp->name << ", " << temp->brand << ", " << temp->model << endl; // Display found element
					return; // Exit the function
				}
				temp = temp->next; // Move to the next node
			}
			cout << "Element not found!" << endl; // If the element is not found
		}
		//8. Function to display the elements of the list
		void displayList() const {
			if (!head) { // Check if the list is empty
				cout << "List is empty." << endl; // Error message
				return; // Exit the function
			}
			Node *temp = head; // Start from the head
			while (temp) { // Traverse through the list
				cout << temp->name << " " << temp->brand << " " << temp->model << " <-> "; // Display the current node
				temp = temp->next; // Move to the next node
			}
			cout << "nullptr" << endl; // Indicate the end of the list
		}
		// Destructor to free up memory when the list is no longer in use
		~DoublyLinkedList() {
			while (head) { // While the list is not empty
				deleteFromBeginning(); // Delete the first node
			}
		}
};

// Function to display menu options for user interaction
void displayMenu() {
	cout << "\nDOUBLY LINKED LIST MENU" << endl;
	cout << "1. Insert at beginning" << endl;
	cout << "2. Insert at end" << endl;
	cout << "3. Insert at position" << endl;
	cout << "4. Delete from beginning" << endl;
	cout << "5. Delete from end" << endl;
	cout << "6. Delete from position" << endl;
	cout << "7. Search for element" << endl;
	cout << "8. Display list" << endl;
	cout << "9. Exit" << endl;
}

int main() {
	DoublyLinkedList list; // Create an instance of the doubly linked list
	int choice, position; // Variables for menu choice and position input
	string name, brand, model; // Variables to store inputted name, brand, and model
	int invalidInputCount = 0; // Counter for invalid inputs
	while (true) { // Infinite loop for menu interaction
		displayMenu(); // Display the menu options
		cout << "Enter your choice: "; // Prompt for user input
		// Check for invalid input using cin
		if (!(cin >> choice)) {
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cout << "Invalid input! Please enter a number." << endl; // Notify user
			invalidInputCount++;
		} else {
			invalidInputCount = 0; // Reset counter on valid input
			switch (choice) { // Switch statement to handle user input
				case 1: // Insert at beginning case
					cout << "Enter car name, brand, and model: "; // Prompt for input
					cin >> name >> brand >> model; // Read name, brand, and model
					list.insertAtBeginning(name, brand, model); // Call insert function
					break; // Exit the case
				case 2: // Insert at end case
					cout << "Enter car name, brand, and model: "; // Prompt for input
					cin >> name >> brand >> model; // Read name, brand, and model
					list.insertAtEnd(name, brand, model); // Call insert function
					break; // Exit the case
				case 3: // Insert at specific position case
					cout << "Enter position, name, brand, and model: "; // Prompt for input
					cin >> position >> name >> brand >> model; // Read position and details
					list.insertAtPosition(position, name, brand, model); // Call insert function
					break; // Exit the case
				case 4: // Delete from beginning case
					list.deleteFromBeginning(); // Call delete function
					break; // Exit the case
				case 5: // Delete from end case
					list.deleteFromEnd(); // Call delete function
					break; // Exit the case
				case 6: // Delete from specific position case
					cout << "Enter position to delete: "; // Prompt for input
					cin >> position; // Read position
					list.deleteFromPosition(position); // Call delete function
					break; // Exit the case
				case 7: // Search for element case
					cout << "Enter car name to search: "; // Prompt for input
					cin >> name; // Read name
					list.searchForElement(name); // Call search function
					break; // Exit the case
				case 8: // Display list case
					list.displayList(); // Call display function
					break; // Exit the case
				case 9: // Exit case
					cout << "Exiting program." << endl; // Notify user of exit
					return 0; // Exit the program
				default: // Default case for invalid input
					cout << "Invalid choice! Please try again." << endl; // Error message
					invalidInputCount++;
			}
		}
		// Exit the loop after three consecutive invalid attempts
		if (invalidInputCount >= 3) {
			cout << "Too many invalid attempts. Exiting program." << endl;
			break;
		}
	}
	return 0;
}
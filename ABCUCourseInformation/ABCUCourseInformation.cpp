//============================================================================
// Name        : BSTABCU.cpp
// Author      : William Marshburn
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;



struct Course {		//Define structure to hold course information

	string courseNumber;
	string courseName;
	string prerequisite;

	Course(){		//default constructor setting each var to void.  Produces void in course search results if file was not loaded.

		courseNumber = "Void";
		courseName = "Void";
		prerequisite = "Void";
	}
};


struct Node {		// Internal structure for tree node

	Course course;

	Node* left;
	Node* right;

	Node() {		//Default Constructor
		left = nullptr;
		right = nullptr;
	}

	Node(Course aCourse) : Node() {		//Initialize Course
		this->course = aCourse;
	}
};

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {
private:
	Node* root;

	void addNode(Node* node, Course course);
	void inOrder(Node* node);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void inOrder();
	void Insert(Course course);
	Course Search(string courseNumber);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {

	root = nullptr;		//root is equal to nullptr, initializing housekeeping variables
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {			// recurse from root deleting every node

}

void BinarySearchTree::inOrder() {		//In order root
	this->inOrder(root);		// call inOrder fuction and pass root
}

void BinarySearchTree::Insert(Course course) {		//Implement inserting a course into the tree
	if (root == nullptr) {		// if root equal to null ptr
		root = new Node(course);
	}
	else {
		addNode(root, course);		// add Node root and course
	}
}

Course BinarySearchTree::Search(string courseNumber) {		//Implement searching the tree for a course

	Node* current = root;		// set current node equal to root

	while (current != nullptr) {
		if (current->course.courseNumber.compare(courseNumber) == 0) {
			return current->course;		// if match found, return current course
		}

		if (courseNumber.compare(current->course.courseNumber) < 0) {		// keep looping downwards until bottom reached or matching course is found
			current = current->left;		// if number is smaller than current node then traverse left
		}
		else {
			current = current->right;		// else larger so traverse right
		}
	}

	Course course;
	return course;
}

void BinarySearchTree::addNode(Node* node, Course course) {

	if (node->course.courseNumber.compare(course.courseNumber) > 0) {
		if (node->left == nullptr) {		// if no left node
			node->left = new Node(course);		// this node becomes left
		}
		else {
			addNode(node->left, course);		// else recurse down the left node
		}
	}
	else {
		if (node->right == nullptr) {		// if no right node
			node->right = new Node(course);		// this node becomes right
		}
		else {
			addNode(node->right, course);		// recurse down the right node
		}
	}
}

void BinarySearchTree::inOrder(Node* node) {
	if (root != nullptr) {		//if node is not equal to null ptr
		if (node->left != nullptr) {		//InOrder left
			inOrder(node->left);
		}

		cout << node->course.courseNumber << ", " << node->course.courseName << endl;		//output course, course num, prereqs

		if (node->right != nullptr) {
			inOrder(node->right);		//InOder right
		}
	}
}

void showMenu() {		//Function to print menu
	cout << "\n";
	cout << "Welcome to the course planner.\n\n";
	cout << "1. Load Data Structure.\n";
	cout << "2. Print Course List.\n";
	cout << "3. Print Course.\n";
	cout << "4. Exit\n\n";
	cout << "What would you like to do?\n";
}

int main() {
	BinarySearchTree* bst;		//Establishing variables
	bst = new BinarySearchTree();
	Course course;
	int selection;
	string searchCourse;
	string tempName;
	string fileName;
	string line;
	ifstream input;
	bool loop = true;
	fileName = "";

	while (loop) {

		showMenu();

		cin >> selection;


		if (selection < 1 || selection > 4) {		//Validating integer input.
			cout << selection << " is not a valid option.\n";
		}

		if (cin.fail()) {		//Exiting program if user enters text.
			throw runtime_error("Input Failed, please only use numbers 1-4.");
		}

		switch (selection) {
		case 1: {

			cout << "Please enter the name of the file you would like to open: \n";		//Ask for file to load
			cin >> fileName;
			cout << "Success. File " << fileName << " loaded.\n";

			input.open(fileName);

			if (!input.is_open()) {		//File validation
				cout << "File opening failed!\n";
				continue;
			}

			while (getline(input, line)) {

				string courseNumber;		//Parsing information from document and splitting into course object. 
				string courseName;
				string prerequisite;

				stringstream ss(line);		//creating string stream to split values seperated by commas.

				Course course;

				getline(ss, courseNumber, ',');
				course.courseNumber = courseNumber;

				getline(ss, courseName, ',');
				course.courseName = courseName;

				getline(ss, prerequisite);
				course.prerequisite = prerequisite;

				bst->Insert(course);		//Insert into search tree.
			}

			input.close();
			break;
		}

		case 2: {
			cout << "Here is a sample schedule:\n\n";

			bst->inOrder();        //Print courses in alphanumerical order

			break;
		}

		case 3: {

			cout << "What course would you like to know about?\n";

			cin >> searchCourse;

			for (unsigned int i = 0; i < searchCourse.size(); i++) {		//loop through searchCourse and uppercase to match documentation from the loaded file. 
				searchCourse[i] = toupper(searchCourse[i]);
			}

			Course temp = bst->Search(searchCourse);

			cout << temp.courseNumber << ", " << temp.courseName << "\n";		//print out the information requested. If nothing found "void" will print for all values
			cout << "Prerequisites: " << temp.prerequisite << "\n";

			break;
		}

		case 4:
			cout << "Goodbye";		//Exit Program
			loop = false;
		}
	}
}
#include <iostream>
#include <string>
using namespace std;

// Structure for each student
struct Student {
    int id;
    string name;
    string order;
    Student* left;
    Student* right;

    Student(int i, string n, string o) {
        id = i;
        name = n;
        order = o;
        left = right = nullptr;
    }
};

// Insertion function
Student* insert(Student* root, int id, string name, string order) {
    if (!root)
        return new Student(id, name, order);

    if (id < root->id)
        root->left = insert(root->left, id, name, order);
    else
        root->right = insert(root->right, id, name, order);

    return root;
}

// Inorder Traversal
void inorder(Student* root) {
    if (root) {
        inorder(root->left);
        cout << "ID: " << root->id << ", Name: " << root->name << ", Order: " << root->order << endl;
        inorder(root->right);
    }
}

// Preorder Traversal
void preorder(Student* root) {
    if (root) {
        cout << "ID: " << root->id << ", Name: " << root->name << ", Order: " << root->order << endl;
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal
void postorder(Student* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << "ID: " << root->id << ", Name: " << root->name << ", Order: " << root->order << endl;
    }
}

// Search function
Student* search(Student* root, int id) {
    if (!root || root->id == id)
        return root;

    if (id < root->id)
        return search(root->left, id);

    return search(root->right, id);
}

// Deletion function
Student* deleteStudent(Student* root, int id) {
    if (!root)
        return nullptr;

    if (id < root->id)
        root->left = deleteStudent(root->left, id);
    else if (id > root->id)
        root->right = deleteStudent(root->right, id);
    else {
        if (!root->left)
            return root->right;
        if (!root->right)
            return root->left;

        Student* temp = root->right;
        while (temp && temp->left)
            temp = temp->left;

        root->id = temp->id;
        root->name = temp->name;
        root->order = temp->order;
        root->right = deleteStudent(root->right, temp->id);
    }
    return root;
}

int main() {
    Student* root = nullptr;
    int choice, id;
    string name, order;

    while (true) {
        cout << "\n--- Canteen System Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Show Students by Wait Time (Inorder)\n";
        cout << "3. Show Students by Arrival Order (Preorder)\n";
        cout << "4. Show Students in Served Order (Postorder)\n";
        cout << "5. Search Student by ID\n";
        cout << "6. Serve Student (Delete)\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Student ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Student Name: ";
                getline(cin, name);
                cout << "Enter Student Order: ";
                getline(cin, order);
                root = insert(root, id, name, order);
                cout << "Student added successfully!\n";
                break;

            case 2:
                cout << "\nShow Students by Wait Time (Inorder Traversal):\n";
                inorder(root);
                break;

            case 3:
                cout << "\nShow Students by Arrival Order (Preorder Traversal):\n";
                preorder(root);
                break;

            case 4:
                cout << "\nShow Students in Served Order (Postorder Traversal):\n";
                postorder(root);
                break;

            case 5:
                cout << "Enter Student ID to Search: ";
                cin >> id;
                if (search(root, id))
                    cout << "Student Found!\n";
                else
                    cout << "Student Not Found!\n";
                break;

            case 6:
                cout << "Enter Student ID to Serve: ";
                cin >> id;
                root = deleteStudent(root, id);
                cout << "Student served and removed!\n";
                break;

            case 7:
                cout << "Exiting... Have a nice day!\n";
                return 0;

            default:
                cout << "Invalid Choice! Try again.\n";
        }
    }
}

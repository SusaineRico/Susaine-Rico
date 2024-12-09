#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Node structure for a Binary Search Tree (BST).  Each node holds a word type and the word itself.
// Think of this as a single record in a database table, but instead of rows and columns, we have a tree structure.
struct Node {
    string wordType;  // Type of word (e.g., "adjective", "noun")
    string word;      // The word itself
    Node *left;      // Pointer to the left subtree (smaller word types)
    Node *right;     // Pointer to the right subtree (larger word types)

    // Constructor to create a new Node.  Initializes left and right children to nullptr (empty).
    Node(string type, string w) : wordType(type), word(w), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node *root; // Root of the BST.  The starting point of the entire tree.

    // Recursive function to insert a new node into the BST.  This is a key part of a BST's functionality.
    //  A recursive function calls itself to solve smaller versions of the same problem.
    void insert(Node* &node, string wordType, string word) {
        // Base case: If the current node is nullptr (empty), create a new node here.
        if (node == nullptr) {
            node = new Node(wordType, word);
        }
        // Recursive case: If the wordType is less than the current node's wordType, insert into the left subtree.
        else if (wordType < node->wordType) {
            insert(node->left, wordType, word);
        }
        // Otherwise, insert into the right subtree.
        else {
            insert(node->right, wordType, word);
        }
    }

    // Recursive function for preorder traversal (Root, Left, Right).  A way to visit all nodes in the tree.
    void preorderTraversal(Node *node) {
        if (node != nullptr) {
            cout << node->wordType << ": " << node->word << "\n "; // Visit the current node (print its data)
            preorderTraversal(node->left); // Recursively traverse the left subtree
            preorderTraversal(node->right); // Recursively traverse the right subtree
        }
    }

    // Recursive function for inorder traversal (Left, Root, Right).  This will print the words in alphabetical order of word type.
    void inorderTraversal(Node *node) {
        if (node != nullptr) {
            inorderTraversal(node->left); // Recursively traverse the left subtree
            cout << node->wordType << ": " << node->word << "\n "; // Visit the current node
            inorderTraversal(node->right); // Recursively traverse the right subtree
        }
    }

    // Recursive function for postorder traversal (Left, Right, Root).  Another way to visit all nodes.
    void postorderTraversal(Node *node) {
        if (node != nullptr) {
            postorderTraversal(node->left); // Recursively traverse the left subtree
            postorderTraversal(node->right); // Recursively traverse the right subtree
            cout << node->wordType << ": " << node->word << "\n "; // Visit the current node
        }
    }

    // Recursive function to search for a node with a given wordType.
    Node* search(Node* node, string wordType) {
        // Base cases:  Node not found (nullptr) or node found.
        if (node == nullptr || node->wordType == wordType) return node;
        // Recursive cases: Search left or right subtree based on wordType comparison.
        if (wordType < node->wordType) return search(node->left, wordType);
        return search(node->right, wordType);
    }

    // Finds the node with the minimum wordType value in a subtree.  Used for deletion.
    Node* findMin(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    // Recursive function for deleting a node with a given wordType.  This is a complex BST operation.
    Node* deleteNode(Node* node, string wordType) {
        if (node == nullptr) return node; // Base case: Node not found

        // Recursive cases: Search left or right subtree.
        if (wordType < node->wordType) {
            node->left = deleteNode(node->left, wordType);
        } else if (wordType > node->wordType) {
            node->right = deleteNode(node->right, wordType);
        } else {
            // Node found. Handle cases based on the number of children.
            if (node->left == nullptr) { // Node has one or zero child
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node has two children: Find the inorder successor (smallest in right subtree)
            Node* temp = findMin(node->right);
            node->wordType = temp->wordType;
            node->word = temp->word;
            node->right = deleteNode(node->right, temp->wordType); // Delete the inorder successor
        }
        return node;
    }

public:
    BST() : root(nullptr) {} // Constructor: Initializes an empty BST

    void insert(string wordType, string word) {
        insert(root, wordType, word);
    }

    void preorderTraversal() {
        preorderTraversal(root);
        cout << endl;
    }

    void inorderTraversal() {
        inorderTraversal(root);
        cout << endl;
    }

    void postorderTraversal() {
        postorderTraversal(root);
        cout << endl;
    }

    // Returns the word associated with a given wordType, or an empty string if not found.
    string getWord(string wordType){
        Node* found = search(root, wordType);
        return (found != nullptr) ? found->word : "";
    }

    // Deletes the node with the given wordType from the BST.
    void deleteWord(string wordType){
        root = deleteNode(root, wordType);
    }
};

int main() {
    BST madLibs;

    cout << "Hello! Welcome to my Mad Libs game!\n";
    cout << "We're going to create a story based on your input.\n";
    cout << "Prepare your 3 words:\n";
    cout<< "NOTE:first word will be a name of person  \n";
    // Array to store the types of words needed for the Mad Libs story.
    string wordTypes[] = {"noun", "verb", "adverb"};
    string words[3];


    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << ") Enter a word (" << wordTypes[i] << "): ";
        getline(cin, words[i]); // Use getline to handle spaces in words
        madLibs.insert(wordTypes[i], words[i]); // Insert the word into the BST.
    }

    // Mad Libs story template.  Placeholders for the words will be replaced.
    string finalStory = "My cat,[noun], decided my laptop was a new scratching post.  The resulting chaos involved spilled coffee, a startled scream, a very guilty-looking feline  , and I [verb].  My deadline?  Completely and [adverb] missed, of course!!!!.";

    //Replaces the placeholders in the story with the words from the BST.
    for (int i = 0; i < 3; ++i) {
        size_t pos = finalStory.find("[" + wordTypes[i] + "]"); //Find the placeholder
        if (pos != string::npos) { //If placeholder is found
            finalStory.replace(pos, wordTypes[i].length() + 2, madLibs.getWord(wordTypes[i])); //Replace with word from BST
        }
    }

    cout << "\nHere's your Mad Libs story:\n" << finalStory << endl;

    cout << "\nInorder Traversal:\n ";
    madLibs.inorderTraversal();
    cout << "\nPreorder Traversal: \n ";
    madLibs.preorderTraversal();
    cout << "\nPostorder Traversal:\n ";
    madLibs.postorderTraversal();


    cout << "\nEnter a word type to delete: ";
    string wordToDelete;
    getline(cin, wordToDelete);
    madLibs.deleteWord(wordToDelete);
    cout << "Word deleted.\nNew Inorder Traversal: \n";
    madLibs.inorderTraversal();
    cout << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Added for std::swap

using namespace std;

// Structure to represent a band
struct Band {
    string name;
    int popularity;
};

// Function to heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(vector<Band>& arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (left < n && arr[left].popularity > arr[largest].popularity) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right].popularity > arr[largest].popularity) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]); // swap the root with the largest element

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Function to insert a new element into the heap
void insert(vector<Band>& heap, const Band& newBand) {
    heap.push_back(newBand); // Add the new band to the end of the heap
    int size = heap.size();
    // Heapify up from the bottom to maintain the max-heap property
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(heap, size, i);
    }
}


// Function to delete the root from the heap
void deleteRoot(vector<Band>& heap) {
    int size = heap.size();
    if (size == 0) {
        cout << "Heap is empty. Nothing to delete." << endl;
        return;
    }

    // Replace root with the last element
    heap[0] = heap[size - 1];
    heap.pop_back(); // Remove the last element

    // Heapify the root element to its correct position
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(heap, size - 1, i);
    }
}

// Function to print the heap
void printHeap(const vector<Band>& heap) {
    cout << "\tCURRENT LINEUP (heap)" << endl;
    for (int i = 0; i < heap.size(); i++) {
        cout << i + 1 << ") Band: " << heap[i].name << "\n Popularity:" << heap[i].popularity << endl;
    }
    cout << endl;
}

int main() {
    vector<Band> festivalLineup;

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Task 1: Insert bands with their popularity ratings into a Max-Heap and show the lineup after each addition
    Band band1 = {"The Rockers", 85};
    insert(festivalLineup, band1);
    cout << "HELLO!\n\nThis is the MUSIC FESTIVAL ORGANIZATION  \n\nThis is the band " << band1.name << " with popularity " << band1.popularity << " added to the lineup." << endl;
    printHeap(festivalLineup);

    Band band2 = {"The Melodies", 90};
    insert(festivalLineup, band2);
    cout << "This is the band " << band2.name << " with popularity " << band2.popularity << " added to the lineup." << endl;
    printHeap(festivalLineup);

    Band band3 = {"The Groovers", 78};
    insert(festivalLineup, band3);
    cout << "This is the band " << band3.name << " with popularity " << band3.popularity << " added to the lineup." << endl;
    printHeap(festivalLineup);

    // Task 2: If a band cancels, remove it from the heap and adjust the lineup accordingly
    cout << "one band has canceled. \nPlease choose the band to cancel (0 - " << festivalLineup.size() - 1 << "): ";
    int choice;
    cin >> choice;

    if (choice >= 0 && choice < festivalLineup.size()) {
        cout << " .\nThe band " << festivalLineup[choice].name << " with popularity " << festivalLineup[choice].popularity << " has canceled." << endl;

        // Swap the chosen band with the last band
        swap(festivalLineup[choice], festivalLineup[festivalLineup.size() - 1]); //Use std::swap for better performance

        // Remove the last band (which is now the swapped band)
        festivalLineup.pop_back();

        // Heapify the heap to maintain the max heap property
        for (int i = festivalLineup.size() / 2 - 1; i >= 0; i--) {
            heapify(festivalLineup, festivalLineup.size(), i);
        }

        printHeap(festivalLineup);
    } else {
        cout << "Invalid choice." << endl;
    }

    // Task 3: Heapify a list of bands and their ratings to create an optimized festival schedule
    vector<Band> randomBandRatings;
    for (int i = 0; i < 5; i++) {
        Band randomBand;
        randomBand.name = "Random Band " + to_string(i + 1);
        randomBand.popularity = rand() % 100;
        randomBandRatings.push_back(randomBand);
    }

    cout << "Random list of bands and their ratings:" << endl;
    for (int i = 0; i < randomBandRatings.size(); i++) {
        cout << "Band: " << randomBandRatings[i].name << ", Popularity: " << randomBandRatings[i].popularity << endl;
    }
    cout << endl;

    // Build max-heap for randomBandRatings
    for (int i = randomBandRatings.size() / 2 - 1; i >= 0; i--) {
        heapify(randomBandRatings, randomBandRatings.size(), i);
    }

    //Sort the heap to ensure output order from highest to lowest popularity.
    sort(randomBandRatings.begin(), randomBandRatings.end(), [](const Band& a, const Band& b) {
        return a.popularity > b.popularity;
    });

    cout << "Heapified lineup for optimized schedule:" << endl;
    for (int i = 0; i < randomBandRatings.size(); i++) {
        cout << "Band: " << randomBandRatings[i].name << ", Popularity: " << randomBandRatings[i].popularity << endl;
    }
    cout << endl;

    return 0;
}

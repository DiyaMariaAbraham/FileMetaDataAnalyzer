#include <iostream>
#include <vector>
#include <string>
using namespace std;


template <typename T, typename U>
struct element{
    T key;
    U value;
};


template <typename T, typename U>
class Map{
    private:
        vector<element<T, U>> elements;
        int len;
    public:
        void insert(T a, U b){
            element<T, U> new_element;
            new_element.key = a;
            new_element.value = b;
            
            int low = 0, high = elements.size() - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (elements[mid].key == a) {
                    // If key already exists, update the value
                    elements[mid].value = b;
                    return;
                } else if (elements[mid].key < a) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            elements.insert(elements.begin() + low, new_element);
            len = elements.size();
        }
        U& operator[](const T& key) {
        int low = 0, high = elements.size() - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (elements[mid].key == key) {
                // Key found, return the corresponding value
                return elements[mid].value;
            } else if (elements[mid].key < key) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        // Key not found, throw an error
        throw runtime_error("Key not found");
    }
        
        bool remove(T a){
           int low = 0, high = elements.size() - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (elements[mid].key == a) {
                    // Key found, erase the element from the vector
                    elements.erase(elements.begin() + mid);
                    len = elements.size();
                    return true;
                } else if (elements[mid].key < a) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            // Key not found
            return false; 
        }

        int size(){
            return len;
        }
};



/*
// main function for <int , string> map
int main() {
    Map<int, string> myMap;

    // Insert some elements
    myMap.insert(1, "One");
    myMap.insert(3, "Three");
    myMap.insert(5, "Five");
    myMap.insert(4, "Four");
    myMap.insert(2, "Two");

    // Display the size of the map
    cout << "Size of the map: " << myMap.size() << endl;

    // Display elements
    cout << "Elements in the map will be sorted:" << endl;
    for (int i = 1; i <= 5; ++i) {
        try {
            cout << "Key: " << i << ", Value: " << myMap[i] << endl;
        } catch (const runtime_error& e) {
            cout << "Key: " << i << ", " << e.what() << endl;
        }
    }

    // Accessing some elements using []
    try {
        cout << "Value at key 2: " << myMap[2] << endl;
        cout << "Value at key 4: " << myMap[4] << endl;
        // This line below throws an error
        cout << "Value at key 7: " << myMap[7] << endl;
    } catch (const runtime_error& e) {
        cout << "Accessing invalid key 7: " << e.what() << endl;
    }

    // Remove an element
    bool removed = myMap.remove(3);
    if (removed) {
        cout << "Element with key 3 removed successfully." << endl;
    } else {
        cout << "Element with key 3 not found." << endl;
    }

    // Display the size of the map after removal
    cout << "Size of the map after removal: " << myMap.size() << endl;

    // Try to access the removed element
    try {
        cout << "Value at key 3: " << myMap[3] << endl;
    } catch (const runtime_error& e) {
        cout << "Key 3 not found: " << e.what() << endl;
    }

    return 0;
}
*/

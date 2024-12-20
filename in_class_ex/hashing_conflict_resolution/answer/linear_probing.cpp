#include <iostream>
#include <vector>

const int TABLE_SIZE = 151;  // Increased size to a prime number to accommodate 50 entries and reduce collisions

class HashMap {
private:
    struct HashEntry {
        int key;
        std::string value;
        bool isOccupied = false;  // To check if a slot is occupied
    };

    std::vector<HashEntry> table;

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashMap() : table(TABLE_SIZE) {}  // Resize the table to the defined size

    void insert(int key, const std::string& value) {
        int index = hashFunction(key);

        // Linear probing for collision resolution
        while (table[index].isOccupied && table[index].key != key) {
            index = (index + 1) % TABLE_SIZE;  // wrap around if at end of table
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
    }

    bool find(int key, std::string& value) {
        int index = hashFunction(key);
        int start = index;

        do {
            if (table[index].key == key && table[index].isOccupied) {
                value = table[index].value;
                return true;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (index != start && table[index].isOccupied);

        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int start = index;

        do {
            if (table[index].key == key && table[index].isOccupied) {
                table[index].isOccupied = false;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (index != start && table[index].isOccupied);
    }
};

int main() {
    HashMap map;

    // Insert 50 entries
    map.insert(1, "John Doe");
    map.insert(2, "Jane Smith");
    map.insert(3, "James Brown");
    // ... continue until 50

    // Generating some names for demonstration purposes
    for (int i = 4; i <= 50; ++i) {
        map.insert(i, "Person " + std::to_string(i));
    }

    // Example of finding a value associated with a key
    std::string value;
    if (map.find(25, value)) {
        std::cout << "Value associated with key 25: " << value << std::endl;
    } else {
        std::cout << "Key 25 not found." << std::endl;
    }

    return 0;
}

#include <iostream>
#include <string>
#include <vector> // List data type
#include <fstream> // Read txt file
using namespace std;

class MailingAddress {
    public:
    string street, city, state; // Declare multiple variables as string
    int zipcode;

    // Constructors (initializer lists for variables)
    MailingAddress(string street_I, string city_I, string state_I, int zipcode_I)
    : street(street_I), city(city_I), state(state_I), zipcode(zipcode_I) {};
    MailingAddress()
    : street(""), city(""), state(""), zipcode(-1) {};

    string tostring() {
        return "{" + street + ", " + city + ", " + state + ", " + std::to_string(zipcode) + "}";
    }

    bool equals(MailingAddress addr) {
        if (addr.street == this->street)
            if (addr.city == this->city)
                if (addr.state == this->state)
                    if (addr.zipcode == this->zipcode)
                        return true;
        return false;
    };
};

class MAHashTable {
    public:
    int M;
    static int R;
    int N = 0; // Save total address count
    vector<vector<MailingAddress>> table;
    MAHashTable(int M_I) : M(M_I), table(M_I) {};

    long hashInt(int i) {
        return i % M;
    };
    long hashString(string s) {
        unsigned long hash = 0; // Remainder starts as 0
        for (int i = s.size()-1; i >= 0; i--) {
            // Adds remainder of each place value together
            hash = (R * hash + s[i]) % M;
        };
    return hash;
    };
    long hashAddress(MailingAddress addr) {
        return ((((( hashString(addr.street)*R + hashString(addr.city)) % M)*R
        + hashString(addr.state)) % M)*R + hashInt(addr.zipcode)) % M;
    };

    void insert(MailingAddress addr) {
        N++; // Number of addresses increases
        /* Go to the hashed index of outer vector
        -> then insert to the back of inner vector */
        table[hashAddress(addr)].push_back(addr);
    };
    bool contains(MailingAddress addr) {
        for(int i=0; i < table[hashAddress(addr)].size(); i++) {
            if(addr.equals(table[hashAddress(addr)][i])) return true;
        };
        return false;
    };
    float getLoadFactor() {
        return float(N) / M; // At least one variable must be float to prevent output from being int
    };
    void print() {
        for(int i=0; i<M; i++) {
            cout << std::to_string(i) << "->[";
            for(int j=0; j<table[i].size(); j++) {
                cout << table[i][j].tostring();
                if(j < table[i].size() - 1) cout << "; "; // Separate chained addresses
            };
            cout << "]" << endl;
        };
    };
};
int MAHashTable::R = 31;

MAHashTable read_and_hash(ifstream& addressFile, MAHashTable hashFile) {
    // Reset file for reading
    addressFile.clear(); // Clear error flags
    addressFile.seekg(0); // "seek get" (aka put pointer back to start of file)
    // Read and hash!!! :D
    string line;
    MailingAddress addr;
    string zipString;
    while(getline(addressFile, addr.street, ',')) { // getline(file, storage_variable, delimiter)
        getline(addressFile, addr.city, ',');
        getline(addressFile, addr.state, ',');
        getline(addressFile, zipString, '\n');
        /* Including this cout in the loop will print addresses.txt in its original state:
        cout << addr.street << "," << addr.city << "," << addr.state << "," << zipString << endl; */
        addr.zipcode = stoi(zipString);
        hashFile.insert(addr);
    };
    return hashFile;
};

int main() {
    ifstream addressFile("addresses.txt");
    MAHashTable hashFile97(97);
    MAHashTable hashFile127(127);
    // Check if file is open
    if (!addressFile.is_open()) {
    std::cerr << "Error: File could not be opened." << std::endl;
    return 1;
    };
    // Read file and insert into a hash table
    hashFile97 = read_and_hash(addressFile, hashFile97);
    hashFile127 = read_and_hash(addressFile, hashFile127);

    // Print the hash table and load factor
    hashFile97.print();
    cout << "\n\n"; // Provide viewing separation
    hashFile127.print();
    cout << "\n\n"; // Provide viewing separation
    cout << "M=97 Table Load Factor: " << to_string(hashFile97.getLoadFactor()) << endl;
    cout << "M=127 Table Load Factor: " << to_string(hashFile127.getLoadFactor()) << endl;
    
    // Search for the two given addresses
    MailingAddress checkAddr1, checkAddr2;
    checkAddr1.street = "450 Highland Ave", checkAddr1.city = "Salem", checkAddr1.state = "MA", checkAddr1.zipcode = 1970;
    checkAddr2.street = "450 Highland Avenue", checkAddr2.city = "Salem", checkAddr2.state = "MA", checkAddr2.zipcode = 1970;
    
    cout << "Address '450 Highland Ave,Salem,MA,1970'";
    if(hashFile97.contains(checkAddr1)) cout << " IS "; else cout << " is NOT ";
    cout << "in addresses.txt" << endl;
    
    cout << "Address '450 Highland Avenue,Salem,MA,1970'";
    if(hashFile97.contains(checkAddr2)) cout << " IS "; else cout << " is NOT ";
    cout << "in addresses.txt" << endl;

    return 0;
};
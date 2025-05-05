#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Record {
private:
    int id;
    float score;
    string name;
    bool isActive;

public:
    // Constructors
    Record() : id(0), score(0.0), name(""), isActive(false) {}
    Record(int i, float s, string n, bool a) : id(i), score(s), name(n), isActive(a) {}

    // String to bool converter
    static bool stringToBool(const string& str) {
        return (str == "1" || str == "true" || str == "True");
    }

    // Friend overloaded operator for writing object to file
    friend ofstream& operator<<(ofstream& ofs, const Record& r) {
        ofs << r.id << " " << r.score << " " << r.name << " " << r.isActive << "\n";
        return ofs;
    }

    // Friend overloaded operator for reading object from file
    friend ifstream& operator>>(ifstream& ifs, Record& r) {
        string line;
        if (getline(ifs, line)) {
            stringstream ss(line);
            string temp;

            // Read and convert each field
            getline(ss, temp, ' ');
            r.id = stoi(temp);

            getline(ss, temp, ' ');
            r.score = stof(temp);

            getline(ss, temp, ' ');
            r.name = temp;

            getline(ss, temp, ' ');
            r.isActive = stringToBool(temp);
        }
        return ifs;
    }

    void display() const {
        cout << "ID: " << id << "\n"
             << "Score: " << score << "\n"
             << "Name: " << name << "\n"
             << "Active: " << (isActive ? "Yes" : "No") << "\n";
    }
};

int main() {
    string filename = "record.txt";

    // Write object to file
    Record r1(101, 88.5, "Alice", true);
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << r1;
        outFile.close();
        cout << "Record written to file.\n\n";
    } else {
        cerr << "Failed to open file for writing.\n";
    }

    // Read object from file
    Record r2;
    ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> r2;
        inFile.close();
        cout << "Record read from file:\n";
        r2.display();
    } else {
        cerr << "Failed to open file for reading.\n";
    }

    return 0;
}

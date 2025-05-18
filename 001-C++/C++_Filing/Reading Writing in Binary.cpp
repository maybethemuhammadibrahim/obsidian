#include <iostream>
#include <cstring>  // Use <cstring> instead of <string.h> for C++
#include <fstream>
using namespace std;

class Student
{
private:
    int id;
    char name[50];
    float marks;

public:
    Student(int id = 0, const char *name = " ", float marks = 0.0f) : id(id), marks(marks)
    {
        strncpy(this->name, name, 49);
        this->name[49] = '\0'; // Ensure null-termination
    }

    friend ostream& operator<<(ostream& out, const Student& s) {
        out << s.id << s.name << s.marks;
        return out;
    }

    friend istream& operator>>(istream& in, Student& s) {
        in >> s.id >> s.name >> s.marks;
        return in;
    }
};

void writeToFile(const string& filename, Student* s, int noOfStudents) {
    ofstream ofile(filename.c_str(), ios::binary);
    if(!ofile) {
        cerr << "Error opening file for writing" << endl;
        return;
    }

    ofile.write(reinterpret_cast<const char*>(&noOfStudents), sizeof(noOfStudents));
    for(int i = 0; i < noOfStudents; i++) {
        ofile.write(reinterpret_cast<const char*>(&s[i]), sizeof(Student));
    }
}

void readFromFile(const string& filename, Student* s, int& no) {
    ifstream ifile(filename.c_str(), ios::binary);
    if(!ifile) {
        cerr << "Error opening file for reading" << endl;
        return;
    }

    ifile.read(reinterpret_cast<char*>(&no), sizeof(no));
    for(int i = 0; i < no; i++) {
        ifile.read(reinterpret_cast<char*>(&s[i]), sizeof(Student));
    }
}



int main() {
    const int MAX_STUDENTS = 10;
    Student students[MAX_STUDENTS] = {
        {1, "Alice", 85.5f},
        {2, "Bob", 76.0f},
        {3, "Charlie", 92.5f}
    };
    int count = 3;

    // Write to file
    writeToFile("students.bin", students, count);

    // Read from file
    Student readStudents[MAX_STUDENTS];
    int readCount = 0;
    readFromFile("students.bin", readStudents, readCount);

    for(int i = 0; i < readCount; i++) {
        cout << readStudents[i] << endl;
    }
    return 0;
}
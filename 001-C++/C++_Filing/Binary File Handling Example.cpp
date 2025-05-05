#include <iostream>
#include <cstring>
#include <fstream>
#include <exception>
using namespace std;

class Employee {
    private:
    int id;
    float salary;
    char name[50];
    public: 
    Employee(int id = -1, float salary = 0, const char* arr = "") : id(id), salary(salary){
        strncpy(name, arr, 49);
        name[50] = '\0';
    }

    friend ostream& operator<<(ostream& out, const Employee& e) {
        out << e.id << " " << e.salary << " " << e.name << endl;
        return out;  
    }

    friend class FileHandler;
};

class Errorthrower : public exception {
    private:
    string msg;
    public:
    Errorthrower(string msg = "Some Error Has Occured") : msg(msg) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class FileHandler
{
    fstream file;
    string fileName;

public:
    FileHandler(string fileName) : fileName(fileName)
    {
        file.open(fileName, ios::in | ios::out | ios::binary | ios::trunc);
        if (!file)
        {
            throw Errorthrower("File Not Opened In Constructor");
        }
    }

    void close()
    {
        if (file.is_open())
        {
            file.close();
        }
        else
        {
            throw Errorthrower("File Already Closed");
        }
    }

    void open() {
        if (!file.is_open())
        {
            file.open(fileName, ios::in | ios::out | ios::binary | ios::app);
        }
        else
        {
            throw Errorthrower("File Already Open");
        }
    }

    void resetInputPointer()
    {
        if (file.is_open())
        {
            file.seekg(0);
            file.clear();
        }
        else
        {
            throw Errorthrower("File Not Open");
        }
    }

    void resetOutputPointer()
    {
        if (file.is_open())
        {
            file.seekp(0);
            file.clear();
        }
        else
        {
            throw Errorthrower("File Not Open");
        }
    }

    void writeToFile(const Employee& e) {
        if(file.is_open())
            file.write((char*)&e, sizeof(e));
        else{
            throw Errorthrower("File Not Open");
        }    
        
    }

    void readFromFile(Employee& e){
        if(file.is_open())
            file.read((char*)&e, sizeof(e));
        else{
            throw Errorthrower("File Not Open");
        } 
    }
};

int main() {
    try {
        Employee e[3] = {
            {1, 100, "Ibrahim"},
            {2, 100, "Maybe"},
            {3, 100, "Again"}
        };
        FileHandler f("employee.bin");
        f.writeToFile(e[0]);
        f.writeToFile(e[1]);
        f.writeToFile(e[2]);
        f.resetInputPointer();
        f.resetOutputPointer();
        Employee r[3];
        f.readFromFile(r[0]);
        f.readFromFile(r[1]);
        f.readFromFile(r[2]);
        cout << r[0];
        cout << r[1];
        cout << r[2];
    }
    catch(exception& e) {
        cout << e.what() << endl;
    }
}
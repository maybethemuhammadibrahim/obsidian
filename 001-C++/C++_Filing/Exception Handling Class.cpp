#include <iostream>
#include <exception>
using namespace std;

class StackOverFlowException : public exception
{
private:
    string msg;

public:
    StackOverFlowException(string msg = "Stack is Full") : msg(msg) {}

    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

class StackUnderFlowException : public exception
{
private:
    string msg;

public:
    StackUnderFlowException(string msg = "Stack is Empty") : msg(msg) {}

    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

template <typename T>
class Stack
{
private:
    int size; // static size initialized once
    T *dataItem;
    int noOfDataItems;

public:
    Stack(int size) : size(size)
    {
        dataItem = new T[size];
        noOfDataItems = 0;
    }

    void push(const T &item)
    {
        try
        {
            if (noOfDataItems + 1 > size)
                throw StackOverFlowException();
            dataItem[noOfDataItems] = item;
            noOfDataItems++;
        }
        catch (exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
        catch (...)
        {
            cout << "error" << endl;
        }
    }

    T pop()//pops whatever is at the last index
    {
        try
        {
            if (noOfDataItems == 0)
                throw StackUnderFlowException();
            return dataItem[--noOfDataItems];
        }
        catch (exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
        catch (...)
        {
            cout << "error" << endl;
        }
    }

    void display() {
        cout << "=======================" << endl;
        cout << "size: " << size << endl;
        for(int i = 0; i < noOfDataItems; i++) {
            cout << "Data " << i + 1 << " :"<< dataItem[i] << endl;
        }
        cout << "=======================" << endl;
        
    }
};

int main()
{
    Stack<int> array(2);
    array.push(1);
    array.display();
    array.push(2);
    array.display();
    array.push(3);
    array.display();

    cout << array.pop();
    cout << array.pop();
    cout << array.pop();
    cout << array.pop();

    
}
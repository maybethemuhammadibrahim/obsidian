#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    ifstream ifs("file.txt");
    if (!ifs)
    {
        cout << "Error opening input file" << endl;
        return 1;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile)
    {
        cout << "Error opening temp file" << endl;
        ifs.close();
        return 1;
    }

    string stringToReplace, replacementWord, word;
    cout << "Enter the string to replace: ";
    cin >> stringToReplace;
    cout << "Enter the string to replace it with: ";
    cin >> replacementWord;

    // Process the input file word by word
    while (getline(ifs, word, ' '))
    {
        if (word == stringToReplace)
        {
            tempFile << replacementWord << " ";
        }
        else
        {
            tempFile << word << " ";
        }
    }

    ifs.close();
    tempFile.close();

    // Now copy the temp file back to original
    ifstream tempIn("temp.txt");
    ofstream ofs("file.txt");
    
    if (!tempIn || !ofs)
    {
        cout << "Error in final copy operation" << endl;
        return 1;
    }

    char ch;
    while (getline(tempIn, word, ' '))
    {
        ofs << word << " ";
    }

    tempIn.close();
    ofs.close();

    // Remove the temporary file (optional)
    // remove("temp.txt");

    return 0;
}
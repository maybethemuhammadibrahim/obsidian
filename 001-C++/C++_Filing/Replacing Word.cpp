/*1. Create and populate a file named data.txt with a few sentences. (e.g., AI is the
future. AI will transform the world. Embrace AI now.)
2. Prompt the user to enter:
○ A searchWord (e.g., "AI")
○ A replacementWord (e.g., "ML")
3. Open the file using fstream in ios::in | ios::out mode.
4. Search for the searchWord using seekg() and read sequentially.
5. When found:
○ Use tellg() to get the current read pointer location.
○ Use seekp() to position the write pointer.
○ Replace the word only if the replacement is of equal or smaller length to
avoid shifting content.

6. If the word is replaced, pad with spaces if needed (e.g., replacing "AI" with "ML" or
"XX").
7. After all replacements, display the updated file.*/
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    string search, replace, word, line;
    ofstream file("data.txt", ios::out);
    if (!file)
    {
        cout << "Error Opening Data.txt" << endl;
        return 1;
    }
    file << "AI is the future. AI will transform the world. Embrace AI now." << endl;
    file.close();



    cout << "Enter a Word to Search" << endl;
    cin >> search;
    cout << "Enter a Word to Replace" << endl;
    cin >> replace;
    if (!(search.size() == replace.size()))
    {
        cout << "Invalid Input! Both words should have same length" << endl;
    }
    fstream File("data.txt", ios::in | ios::out);
    if (File)
    {

        while (File >> word)
        {
            // cout<<File.tellg()<<endl;
            if (word == search)
            {
                streampos n = File.tellg();
                n -= static_cast<streamoff>(word.size());
                // n -= 1;
                File.seekp(n, ios::beg);
                File << replace;
                cout << word << "   Replaced with   " << replace << endl;
            }
            else {
                cout << "Word Does not Exists" << endl;
            }
        }
        

        
        

        File.clear();
        File.seekg(0);
        getline(File, line);
        cout << line << endl;
        File.close();
    }
    else
    {
        cout << "Error Opening Data.txt" << endl;
        return 1;
    }
    return 0;
}
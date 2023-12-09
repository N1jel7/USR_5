#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class replacement {
private:

public:
    int CountLinesInFile(string filename)
    {
        ifstream F(filename, ios::in);

        if (!F)
        {
            return -1;
        }

        int count = 0;
        char buffer[1000];

        while (!F.eof())
        {
            count++;
            F.getline(buffer, 1000);
        }
        F.close();
        return count;
    }

    void replace_rows(const string& PATH, const char& SYMBOL, const string& WORD) 
    {
        fstream data;
        ofstream tempFile;
        data.open("data.csv", ios::in);
        tempFile.open("temp.csv");
        if (data.is_open() || tempFile.is_open())
            {
                string str;
                int i = 0;
                while (!data.eof()) 
                {
                    if (i == 0) 
                    {
                        string str = "";
                        getline(data, str);
                        string tempString;
                        istringstream ist(str);
                        while (getline(ist, tempString, SYMBOL)) 
                        {
                            tempFile << tempString + ',';
                        }
                        tempFile << "\n";
                    }
                    i++;
                    string str = "";
                    getline(data, str);
                    string tempString;
                    istringstream ist(str);
                    while (getline(ist, tempString, SYMBOL)) 
                    {
                        tempFile << WORD + ",";
                    }
                    tempFile << "\n";
                }
                data.close();
                tempFile.close();
                remove(PATH.c_str()); // Удаление исходного файла
                rename("temp.csv", PATH.c_str()); // Переименование временного файла в исходное имя файла
            }

            else {
                cout << "Ошибка при открытии файла." << endl;
            }
            
        }

    void replace_columns(const string& PATH, const char& SYMBOL, const string& WORD)
    {
        fstream data;
        ofstream tempFile;
        data.open("data.csv", ios::in);
        tempFile.open("temp.csv");
        if (data.is_open() || tempFile.is_open())
        {
            string str;

            while (!data.eof())
            {
                string str = "";
                getline(data, str);
                string tempString;
                istringstream ist(str);
                int j = 0;
                while (getline(ist, tempString, SYMBOL))
                {
                    if (j == 0)
                    {
                        tempFile << tempString + ',';
                        j++;
                    }
                    else
                    {
                        tempFile << WORD + ',';
                    }
                    
                        
                }
                tempFile << "\n";
            }
            data.close();
            tempFile.close();
            remove(PATH.c_str()); // Удаление исходного файла
            rename("temp.csv", PATH.c_str()); // Переименование временного файла в исходное имя файла
        }

        else {
            cout << "Ошибка при открытии файла." << endl;
        }

    }

    void out(const string& PATH) {
        string line;

        ifstream out(PATH);
        if (out.is_open())
        {
            cout << "Результат выполнения программы: " << endl;
            while (getline(out, line))
            {
                cout << line << std::endl;
            }
            out.close();
        }
        else
        {
            cout << "Ошибка открытия файла!" << endl;
        }
        
    }
};



int main() {
    string PATH = "data.csv";
    string WORD = "Hello";
    char SYMBOL = ',';
    int choice = 0;
    replacement first;
    cout << "Введите путь к файлу (data.csv): ";
    getline(cin, PATH);
    cout << "Введите символ разделения: ";
    cin >> SYMBOL;
    cout << "Введите действие: " << endl;
    cout << "\t1 - замена строк. \n";
    cout << "\t2 - замена столбцов. \n";
    cin >> choice;
    switch (choice)
    {
    case 1: 
        system("cls");
        cout << "Замена строк.\n";
        cout << "Что ввести в качестве новой строки?: ";
        cin >> WORD;
        first.replace_rows(PATH, SYMBOL, WORD);
        first.out(PATH);
        break;
    case 2: 
        system("cls");
        cout << "Замена стоблцов.\n";
        cout << "Что ввести в качестве нового столбца?: ";
        cin >> WORD;
        first.replace_columns(PATH, SYMBOL, WORD);
        first.out(PATH);
        break;
    default:
        break;
    }
}
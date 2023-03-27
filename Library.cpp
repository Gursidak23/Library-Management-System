#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
class Books
{
    char name[25], author[25], publisher[25];
    float rate = 500.50;

public:
    int idno;
    void InputBook()
    {
        cout << "Enter the ID number of the book = ";
        cin >> idno;
    }
    void InputWriters()
    {
        cout << "Enter the name of the book = ";
        fflush(stdin);
        gets(name);
        cout << "Enter the name of author of the book = ";
        gets(author);
        cout << "Enter the name of publisher of the book = ";
        gets(publisher);
    }
    void UpdateData(char *nm, char *au, char *pub)
    {
        strcpy(name, nm);
        strcpy(author, au);
        strcpy(publisher, pub);
    }
    void ShowId()
    {
        cout << "\nID number of book = " << idno << endl;
    }
    void ShowDetails()
    {

        cout << "\nName of the book = " << name << endl;
        cout << "Name of the author = " << author << endl;
        cout << "Name of the publisher = " << publisher << endl;
        cout << "Cost of the Book = " << rate << endl;
    }
};
int main()
{
    Books obj;
    fstream F, fn, temp;
    int ch, arr[20], i;
    char choice, usr[20];
    char str_1[] = "user";
    long password = 123456;
    long pass;
    cout << "\t\t\t\tPlease enter your login details. " << endl;
    cout << "Enter your user-name : ";
    cin >> usr;
    int res = strcmp(str_1, usr);
    cout << "Enter your password = ";
    cin >> pass;
    if (res == 0 && pass == password)
    {
        cout << "\nLogin Successful" << endl;
        do
        {
            cout << "*****************Welcome to the Library Management System**********************" << endl;
            cout << "\nThe List of operations that can be performed in this system are as follows :" << endl;
            cout << "Press 1 for adding new book. " << endl;
            cout << "Press 2 for showing details. " << endl;
            cout << "Press 3 for deleting an entry. " << endl;
            cout << "Press 4 for finding an entry. " << endl;
            cout << "Press 5 for updating an entry. " << endl;
            cout << "Press 6 for exit. " << endl;
            cout << "Enter your choice = ";
            cin >> ch;
            if (ch == 1)
            {
                F.open("Book.txt", ios::in);
                for (i = 0; F.read((char *)&obj, sizeof(obj)); i++)
                {
                    arr[i] = obj.idno;
                }
                F.close();
                fn.open("Book.txt", ios::app | ios::binary | ios::in);
                temp.open("Bookcase.txt", ios::in | ios::out | ios::binary);
                obj.InputBook();
                temp.write((char *)&obj, sizeof(obj));
                temp.read((char *)&obj, sizeof(obj));
                int flag = 0;
                for (int j = 0; j < i; j++)
                {
                    if (arr[j] == obj.idno)
                    {
                        flag = 1;
                    }
                }
                if (flag == 1)
                {
                    cout << "\nID number for the book already exist" << endl;
                }
                if (flag == 0)
                {
                    obj.InputWriters();
                    cout << "\nYour book is added in the list successfully." << endl;
                    fn.write((char *)&obj, sizeof(obj));
                }
                temp.close();
                fn.close();
            }
            else if (ch == 2)
            {
                fstream fin;
                fin.open("Book.txt", ios::in | ios::binary);
                cout << "The details of the filled input are as follows:" << endl;
                while (fin.read((char *)&obj, sizeof(obj)))
                {
                    obj.ShowId();
                    obj.ShowDetails();
                }
                fin.close();
            }
            else if (ch == 3)

            {
                fstream f, temp;
                int num;
                f.open("Book.txt", ios::in | ios::binary);
                temp.open("rec.txt", ios::out | ios::binary);
                cout << "Enter the ID number you want to delete = ";
                cin >> num;
                cout << "\nThe details for the entered ID number deleted successfully." << endl;
                while (f.read((char *)&obj, sizeof(obj)))
                {
                    if (obj.idno != num)
                    {
                        temp.write((char *)&obj, sizeof(obj));
                    }
                }
                f.close();
                temp.close();
                remove("Book.txt");
                rename("rec.txt", "Book.txt");
            }
            else if (ch == 4)
            {
                int n;
                fstream find_id;
                find_id.open("Book.txt", ios::in | ios::binary);
                cout << "Enter the ID number for its details = ";
                cin >> n;
                cout << "\nThe details of the entered ID number are as follows :" << endl;
                while (find_id.read((char *)&obj, sizeof(obj)))
                {
                    if (obj.idno == n)
                    {
                        obj.ShowId();
                        obj.ShowDetails();
                    }
                    else
                        cout << "\nThe details of the particular ID number not found." << endl;
                }
                find_id.close();
            }
            else if (ch == 5)
            {
                int m;
                char nm[25], au[25], pub[25];
                fstream update, temp_file;
                int pos = update.tellg();
                update.open("Book.txt", ios::in | ios::binary);
                temp_file.open("record.txt", ios::out | ios::binary);
                cout << "Enter the ID number for updating its details = ";
                cin >> m;
                while (update.read((char *)&obj, sizeof(obj)))
                {
                    if (obj.idno != m)
                    {
                        temp_file.write((char *)&obj, sizeof(obj));
                    }
                    else
                    {
                        cout << "Enter the name of the new book = ";
                        fflush(stdin);
                        gets(nm);
                        cout << "Enter the name of author of the new book = ";
                        gets(au);
                        cout << "Enter the name of publisher of the new book = ";
                        gets(pub);
                        update.seekp(pos);
                        obj.UpdateData(nm, au, pub);
                        cout << "\nThe updated details for the entered ID number are as follows :" << endl;
                        obj.ShowId();
                        obj.ShowDetails();
                        temp_file.write((char *)&obj, sizeof(obj));
                    }
                }
                update.close();
                temp_file.close();
                remove("Book.txt");
                rename("record.txt", "Book.txt");
            }
            else if (ch == 6)
                exit(0);
            else
                cout << "Wrong Input";
            cout << "\nDo you want to continue? (Y/N) = ";
            cin >> choice;
        } while (choice == 'Y' || choice == 'y');
    }

    else
    {
        cout << "\nLogin Failed" << endl;
        exit(0);
    }
}
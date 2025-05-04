/*

Course: CSE Project 150
Title: Student Management System

*/
#include <bits/stdc++.h>
#include <conio.h>
#include <sys/stat.h>
#include <windows.h>

using namespace std;

void addnewStudent();
void ViewAllStudent();
void search();
void updateStudent();
void studentPanel(string id);

void studentlogin();
bool findstd(string id);

// to store stu info
struct Student
{
    string name;
    int rollNo;
    int age;
    int stdClass;
    int academicYr;
    string fathers_name;
    string mothers_name;
    string ID;
};


// global map to store all stu data using id as a key
map<string, Student> allStudentList;

// function to load all stu data from files into memory
void load_all_data()
{
    ifstream allfile("StudentInfo/AllStudent.data", ios::out);
    string id;
    while (getline(allfile, id))
    {
        allStudentList[id].ID = id;
        string f;
        f.append("StudentInfo/").append(id).append(".data");
        ifstream file(f, ios::out);
        string data, temp;
        int col, d = 1, n;
        while (getline(file, data))
        {
            col = data.find(':');
            temp = data.substr(col + 2);
            if (d >= 3 and d <= 6)
            {
                n = stoi(temp.c_str());
            }
            if (d == 1)
                allStudentList[id].ID = temp;
            else if (d == 2)
                allStudentList[id].name = temp;
            else if (d == 3)
                allStudentList[id].academicYr = n;
            else if (d == 4)
                allStudentList[id].stdClass = n;
            else if (d == 5)
                allStudentList[id].rollNo = n;
            else if (d == 6)
                allStudentList[id].age = n;
            else if (d == 7)
                allStudentList[id].fathers_name = temp;
            else if (d == 8)
                allStudentList[id].mothers_name = temp;
            temp.clear();
            d += 1;
        }
    }
}

// stu's data to the file system and map
bool addStudentFile(Student &std)
{
    string fileName;
    fileName.append("StudentInfo/").append(std.ID).append(".data");

    ofstream outFile(fileName);
    if (outFile.is_open())
    {
        outFile << "Student ID : " << std.ID << endl;
        outFile << "Name : " << std.name << endl;
        outFile << "Academic Year : " << std.academicYr << endl;
        outFile << "Class : " << std.stdClass << endl;
        outFile << "Roll : " << std.rollNo << endl;
        outFile << "Age : " << std.age << endl;
        outFile << "Father's Name : " << std.fathers_name << endl;
        outFile << "Mother's Name : " << std.mothers_name << endl;
    }
    else
    {
        cout << "Data write failed\n";
        return false;
    }
    outFile.close();
    //  Add stu's ID to the central record file
    ofstream alldata("StudentInfo/AllStudent.data", ios::app);
    if (alldata.is_open())
    {
        alldata << std.ID << endl;
    }
    alldata.close();
    return true;
}

// gather info from user
void addnewStudent()
{
    Student std;
    cout << "\n**************************************" << endl;
    cout << "Enter student's name    : ";
    cin.ignore();
    getline(cin, std.name);
    cout << "Enter Father's name     : ";
    // cin.ignore();
    getline(cin, std.fathers_name);
    cout << "Enter Mother's name     : ";
    // cin.ignore();
    getline(cin, std.mothers_name);
    cout << "Enter academic year     : ";
    cin >> std.academicYr;
    cout << "Enter Class             : ";
    cin >> std.stdClass;
    cout << "Enter student's roll no : ";
    cin >> std.rollNo;
    cout << "Enter student's age     : ";
    cin >> std.age;
    // ac year+class+roll
    std.ID = to_string(std.academicYr) + to_string(std.stdClass) +
             to_string(std.rollNo);

    addStudentFile(std);

    cout << endl;
    cout << "Student information added succesfully with ID : " << std.ID
         << endl
         << endl;
    allStudentList[std.ID] = std;
    return;
}

void ViewAllStudent()
{
    cout << "\n**************************************" << endl;
    cout << "List of all student :\n\n";
    ifstream allfile("StudentInfo/AllStudent.data", ios::out);
    string id, name, nam;
    for (int i = 1; getline(allfile, id); i++)
    {
        cout << i << ".\n";
        name.append("StudentInfo/").append(id).append(".data");
        ifstream nm(name, ios::out);
        getline(nm, nam);
        cout << nam << endl;
        getline(nm, nam);
        cout << nam << endl;
        nm.close();
        name.clear();
        cout << "\n";
    }
    return;
}

void search()
{
    cout << "\nEnter the student id : ";
    string inputId;
    cin >> inputId;
    cout << endl;

    ifstream allfile("StudentInfo/AllStudent.data", ios::out);
    string id;
    while (getline(allfile, id))
    {
        if (id == inputId)
        {
            string info, filename;
            filename.append("StudentInfo/").append(id).append(".data");
            ifstream studentFile(filename, ios::out);
            while (getline(studentFile, info))
            {
                cout << info << endl;
            }
            cout << endl;
            studentFile.close();
            return;
        }
    }
    cout << "Sorry no data found\n\n";

    cout << "Do you want to try again? yes/no :\n";
    string yn;
    cin >> yn;

    if (yn == "yes" or yn == "Yes")
    {
        search();
    }
    cout << endl;
    return;
}

// delete a stu record based on id
bool deleteStudentID(string idToDelete)
{
    if (findstd(idToDelete) == false)
    {
        cout << "Sorry no data found!!\n\n";
        return false;
    }
    string filename;
    filename.append("StudentInfo/").append(idToDelete).append(".data");

    ifstream inFile("StudentInfo/AllStudent.data");
    ofstream tempFile("StudentInfo/temp.data");

    string id;
    while (getline(inFile, id))
    {
        if (id != idToDelete)
        {
            tempFile << id << endl;
        }
    }

    inFile.close();
    tempFile.close();

    remove(filename.c_str());
    remove("StudentInfo/AllStudent.data");
    rename("StudentInfo/temp.data", "StudentInfo/AllStudent.data");

    allStudentList.clear();
    load_all_data();

    return true;
}


// update stu's info
void updateStudent()
{
    Student std;

    string id, f, info, temp;
    cout << "Enter Student ID : ";
    cin >> id;

    if (findstd(id) == false)
    {
        cout << "Sorry no data found!!\n\n";
        return;
    }
    std = allStudentList[id];

    f.append("StudentInfo/").append(id).append(".data");

    cout << "Enter student's name        : ";
    cin.ignore();
    getline(cin, temp);
    if (temp.size() != 0)
        std.name = temp;
    temp.clear();
    cout << "Enter student Father's name : ";
    // cin.ignore();
    getline(cin, temp);
    if (temp.size() != 0)
        std.fathers_name = temp;
    temp.clear();
    cout << "Enter student mother's name : ";
    // cin.ignore();
    getline(cin, temp);
    if (temp.size() != 0)
        std.mothers_name = temp;
    temp.clear();

    deleteStudentID(id);
    addStudentFile(std);

    cout << "Student information updated succesfully.\n";
    allStudentList[id] = std;
    return;
}


// Admin menu for all info
void adminmenu()
{
    cout << "\n**************************************" << endl;
    int ch2 = 0;
    string id;
    while (ch2 < 7)
    {
        cout << endl;
        cout << "1. Add New Student record." << "\n";
        cout << "2. View All Students record." << "\n";
        cout << "3. Search Student record." << "\n";
        cout << "4. Delete Student record." << "\n";
        cout << "5. Update Student record." << "\n";
        cout << "6. Back to main menu." << "\n\n";

        cin >> ch2;
        cout << endl;

        switch (ch2)
        {
        case 1:
            addnewStudent();
            cout << "Press any key...";
            getch();
            cout << endl;
            break;
        case 2:
            ViewAllStudent();
            cout << "Press any key...";
            getch();
            cout << endl;
            break;
        case 3:
            search();
            cout << "Press any key...";
            getch();
            cout << endl;
            break;
        case 4:
            cout << "Enter the student id to delete : ";
            cin >> id;
            cout << endl;
            if (deleteStudentID(id) == true)
                cout << "Succesfully removed.\n\n";
            cout << "Press any key...";
            getch();
            cout << endl;
            break;
        case 5:
            updateStudent();
            cout << "Press any key...";
            getch();
            cout << endl;
            break;
        case 6:
            cout << "Press any key...";
            getch();
            cout << endl;
            return;
        default:
            cout << "\nInvalid choice\nPress any key...";
            getch();
        }
    }
}


void myInfo(string inputId)
{
    ifstream allfile("StudentInfo/AllStudent.data", ios::out);
    string id;
    int line = 1;
    while (getline(allfile, id))
    {
        if (id == inputId)
        {
            string info, filename;
            filename.append("StudentInfo/").append(id).append(".data");
            ifstream studentFile(filename, ios::out);
            while (getline(studentFile, info))
            {
                if (line > 8)
                    return;
                cout << info << endl;
                line++;
            }
            cout << endl;
            studentFile.close();
            return;
        }
    }
    cout << "Sorry no data found\n";

    cout << "Do you want to try again? yes/no :\n";
    string yn;
    cin >> yn;

    if (yn == "yes")
    {
        search();
    }
    return;
}

// If any student wanna see their info, they will log in with their ID as a pass code
void studentPanel(string id)
{
    cout << "1: Show my information.\n";
    cout << "2: Back.\n";
    // . . .
    int choice;
    cin >> choice;
    cout<<endl;

    switch (choice)
    {
    case 1:
        myInfo(id);
        cout<<"\nPress any key...";
        getch();
        break;
    case 2:
        return;
    default :
        cout<<"Invalid chaoice.\n";
    }
    cout<<endl<<endl;
    studentPanel(id);
}

// Admin menu
void adminLogin()
{
    string pass;
    int warning = 0;
    while (warning <= 3)
    {
        cout << "Enter Pin : ";
        cin >> pass;
        if (pass == "sust")
        {
            cout << endl;
            adminmenu();
            return;
        }
        else
        {
            cout << "\nWrong Pin. Try again.\n\n";
        }
    }
    cout << "Sorry!!\n";
    return;
}

// Student panel
void studentlogin()
{
    cout << "\nEnter your student ID : ";
    string id;
    cin >> id;
    int k = 3;
    while (k--)
    {
        if (findstd(id))
        {
            cout << "\nLogin Succesfully\n\n";
            cout << "\n**************************************" << endl
                 << endl;
            studentPanel(id);

            return;
        }
        else
        {
            cout << "Wrong user name.\n";
            studentlogin();
        }
    }
    if (k == 0)
    {
        cout << "please try again later\n";
        return;
    }
}

bool findstd(string id)
{
    return allStudentList.find(id) != allStudentList.end();
}

// Driver code
int main()
{
    struct stat sb;
    if (stat("StudentInfo", &sb) != 0)
        mkdir("StudentInfo");
    if (stat("StudentInfo/AllStudent.data", &sb) != 0)
    {
        ofstream f("StudentInfo/AllStudent.data");
        f.close();
    }

    load_all_data();

    int loginChoice = 0;
    while (loginChoice < 3)
    {
        cout << "\n**************************************" << endl;
        cout << "           MAIN MENU\n";
        cout << endl;
        cout << "1: Admin login\n";
        cout << "2: Student login\n";
        cout << "3: Exit\n\n";
        cin >> loginChoice;
        if (loginChoice == 1)
        {
            adminLogin();
            system("cls");
        }
        else if (loginChoice == 2)
        {
            studentlogin();
            system("cls");
        }
    }
    cout << "\n\t Thank You For using This Application:";
    cout << "\n\t \tEnter Any Key To Exit:-";
    getch();
    allStudentList.clear();
    exit(0);
    return 0;
}

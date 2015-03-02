#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

/**************************************************************************
** class person
**************************************************************************/
// This class simply characterizes a person as collection of attributes,
// name, address, etc.
//
class person {
public:
    person(){}
    void setname (string n) {name = n;}
    void setaddr (string a) {address = a;}
    void setcity (string c) {city = c;}
    void setstate(string s) {state = s;}
    void setzip  (string z) {zip = z;}
    void setphone(string p) {phone = p;}
    void setcell (string c) {cell = c;}
    void setemail(string e) {email = e;}
    void setage  (int a) {age = a;}

    string getname() {return name;}
    string getaddr() {return address;}
    string getcity() {return city;}
    string getstate(){return state;}
    string getzip()  {return zip;}
    string getphone(){return phone;}
    string getcell() {return cell;}
    string getemail(){return email;}
    int getage()     {return age;}

    void show(string nom, string val) {cout << nom << val << endl;}
    void show(string nom, int val) {cout << nom << val << endl;}

    void showname () {show("name    : ", name);}
    void showaddr () {show("address : ", address);}
    void showcity () {show("city    : ", city);}
    void showstate() {show("state   : ", state);}
    void showzip  () {show("zip     : ", zip);}
    void showphone() {show("phone   : ", phone);}
    void showcell () {show("cell    : ", cell);}
    void showemail() {show("email   : ", email);}
    void showage  () {show("age     : ", age);}

    // Static type-safe functions for acquiring input from the user
    // after presenting a prompt for the input.
    //
    static string getstr(string prompt);
    static int getint(string prompt);

private:
    string name;
    string address;
    string city;
    string state;
    string zip;
    string phone;
    string cell;
    string email;
    int age;
};

string person::getstr(string prompt)
{
    string str;
    cout << prompt;
    getline(cin, str);
    return str;
}

int person::getint(string prompt)
{
    int num;
    string str;
    while (true) {
        cout << prompt;
        getline(cin, str);

        // If user simply pressed return key, return with a 0
        //
        if(str == "")
            return 0;

        // This code converts from string to number safely.
        //
        stringstream ss(str);
        if (ss >> num)
            break;
        cout << "Invalid number, please try again" << endl;
    }
    return num;
}

/**************************************************************************
** class addrbook
**************************************************************************/
// This class provides the container (vector) and methods for managing
// an Address Book as a collection of class person.
//
class addrbook {
public:
    addrbook(){}
    void addperson();
    void editperson();
    void showperson();
    void deleteperson();
    void savepeople();
    void loadpeople();
    void loadpeople(string fname);
    void viewpeople();
    void viewpeople(string fname);
    void getmenu(string fname);

private:
    vector<person> people;
    void showmenu();
    string& promptname(string &);
    bool findname(string name, person& p);
    bool findname(string name, int& index);
    bool isempty();
    string fgetstr(ifstream& f) {string s; f >> s; return s;}
    int    fgetint(ifstream& f) {   int i; f >> i; return i;}
};

string& addrbook::promptname(string& name)
{
    while(true) {
        name = person::getstr("Type a name: ");
        if(name == "")
            continue;
        else
            return name;
    }
}

////////////////////////////////////////////////////////////////////////////
//
// findname - find a name in the address book given a string for the name
// and a reference to an instance of class person.
// This version takes a reference to an index, instead of to an instance
// of class person.
//
bool addrbook::findname(string n, person& p)
{
    for(vector<person>::iterator i = people.begin(); i < people.end(); ++i) {
        if(i->getname() == n) {
            p = *i;
            return true;
        }
    }
    cout << "\tUnable to find person " << n << endl << endl;
    return false;
}

////////////////////////////////////////////////////////////////////////////
//
// findname - overloaded.
// This version takes a reference to an index, instead of to an instance
// of class person.
//
bool addrbook::findname(string n, int& index)
{
    for(unsigned i = 0; i < people.size(); ++i) {
        if(people[i].getname() == n) {
            index = i;
            return true;
        }
    }
    cout << "\tUnable to find person " << n << endl << endl;
    return false;
}

bool addrbook::isempty()
{
    if(people.size() == 0) {
        cout << "\tThe Address Book is empty\n"
             << "\tPlease add some entries.\n\n";
        return true;
    }
    return false;
}

void addrbook::addperson()
{
    int i = people.size();
    people.resize(i + 1);
    people[i].setname (person::getstr("   Name: "));
    people[i].setaddr (person::getstr("Address: "));
    people[i].setcity (person::getstr("   City: "));
    people[i].setstate(person::getstr("  State: "));
    people[i].setzip  (person::getstr("    Zip: "));
    people[i].setphone(person::getstr("  Phone: "));
    people[i].setcell (person::getstr("   Cell: "));
    people[i].setemail(person::getstr("  email: "));
    people[i].setage  (person::getint("    Age: "));
}

void addrbook::showperson()
{
    person p;
    string name;

    if(isempty())
        return;

    cout << "\tShow an existing address book entry" << endl;
    promptname(name);

    if(!findname(name, p))
        return;

    cout << "   Name: " << p.getname() << endl
         << "Address: " << p.getaddr() << endl
         << "   City: " << p.getcity() << endl
         << "  State: " << p.getstate() << endl
         << "    Zip: " << p.getzip() << endl
         << "  Phone: " << p.getphone() << endl
         << "   Cell: " << p.getcell() << endl
         << "  email: " << p.getemail() << endl
         << "    Age: " << p.getage() << endl;
}

void addrbook::editperson()
{
    person& p = people[0];
    string name;
    string str;
    int age;

    if(isempty())
        return;

    cout << "\tEdit an address book entry" << endl
         << "\tSimply press \"Return\" or \"Enter\" if you do not want \n"
         << "\tto change the field, else type the new value.\n\n";
    promptname(name);

    if(!findname(name, p))
        return;

    p.setname ((str = person::getstr("   Name: ")) == "" ? p.getname() : str);
    p.setaddr ((str = person::getstr("Address: ")) == "" ? p.getaddr() : str);
    p.setcity ((str = person::getstr("   City: ")) == "" ? p.getcity() : str);
    p.setstate((str = person::getstr("  State: ")) == "" ? p.getstate(): str);
    p.setzip  ((str = person::getstr("    Zip: ")) == "" ? p.getzip()  : str);
    p.setphone((str = person::getstr("  Phone: ")) == "" ? p.getphone(): str);
    p.setcell ((str = person::getstr("   Cell: ")) == "" ? p.getcell() : str);
    p.setemail((str = person::getstr("  email: ")) == "" ? p.getemail(): str);
    p.setage  ((age = person::getint("    Age: ")) == 0  ? p.getage()  : age);
}

void addrbook::deleteperson()
{
    string name;
    int i;
    int& index = i;

    if(isempty())
        return;

    cout << "Delete an address book entry" << endl;
    promptname(name);

    if(!findname(name, index))
        return;

    people.erase(people.begin() + index);
}

void addrbook::savepeople()
{
    string fname;
    ofstream file;

    cout << "\nSave the Address Book to a file.\n"
         << "\tYou can include the directory in the name."
         << "\tIf you do NOT want to do this, press the\n"
         << "\tENTER or RETURN key now\n\n";

    fname = person::getstr("Type a file name: ");
    if (fname == "")
        return;

    fname = fname + ".dat";
    cout << "Opening file: " << fname << endl;
    file.open(fname.c_str());

    if(!file.is_open()) {
        cout << "Cannot open file: " << fname << endl << endl;
        return;
    }

    file << people.size() << endl;

    for(vector<person>::iterator i = people.begin() ; i < people.end(); ++i) {
        person &p = *i;
        file << p.getname()  << endl
             << p.getaddr()  << endl
             << p.getcity()  << endl
             << p.getstate() << endl
             << p.getzip()   << endl
             << p.getphone() << endl
             << p.getcell()  << endl
             << p.getemail() << endl
             << p.getage()   << endl;
    }
}

void addrbook::loadpeople()
{
    string fname;
    ifstream file;

    cout << "\n\tName the Address Book file you want to open\n"
         << "\tYou can include the directory in the name.\n"
         << "\tYou can start a new Address Book by simply\n"
         << "\tpressing he RETURN or ENTER key now.\n\n";

    fname = person::getstr("Type a file name: ");
    if (fname == "")
        return;

    fname = fname + ".dat";
    loadpeople(fname);
}

void addrbook::loadpeople(string fname)
{
    int size;
    ifstream file;

    cout << "Opening Address Book from file: " << fname << endl;
    file.open(fname.c_str());

    if(!file.is_open()) {
        cout << "\n\tCannot open file: " << fname << endl
             << "\tYou can look for your Address Book file and press \"l\"\n"
             << "\tto load it when you find it, or you can start a new\n"
             << "\tAddress Book file by pressing \"a\" now.\n\n";
        return;
    }

    file >> size;
    cout << "Address Book " << fname << " contains " << size << " records.\n";

    for(int i = 0; i < size; i++) {
        people.resize(people.size() + 1);
        person& p = people[i];
        p.setname (fgetstr(file));
        p.setaddr (fgetstr(file));
        p.setcity (fgetstr(file));
        p.setstate(fgetstr(file));
        p.setzip  (fgetstr(file));
        p.setphone(fgetstr(file));
        p.setcell (fgetstr(file));
        p.setemail(fgetstr(file));
        p.setage  (fgetint(file));
    }
}

void addrbook::viewpeople()
{
    string fname;
    ifstream file;

    cout << "\n\tName the Address Book file you want to open\n"
         << "\tYou can include the directory in the name.\n"
         << "\tYou can start a new Address Book by simply\n"
         << "\tpressing he RETURN or ENTER key now.\n\n";

    fname = person::getstr("Type a file name: ");
    if (fname == "")
        return;

    fname = fname + ".dat";
    loadpeople(fname);
}

void addrbook::viewpeople(string fname)
{
    int size;
    ifstream file;

    cout << "Opening Address Book from file: " << fname << endl;
    file.open(fname.c_str());

    if(!file.is_open()) {
        cout << "\n\tCannot open file: " << fname << endl
             << "\tYou can look for your Address Book file and press \"l\"\n"
             << "\tto load it when you find it, or you can start a new\n"
             << "\tAddress Book file by pressing \"a\" now.\n\n";
        return;
    }

    file >> size;
    cout << "Address Book " << fname << " contains " << size << " records.\n";

    for(int i = 0; i < size; i++) {
        people.resize(people.size() + 1);
        person& p = people[i];
        p.showname  ();
        p.showaddr ();
        p.showcity ();
        p.showstate();
        p.showzip  ();
        p.showphone();
        p.showcell ();
        p.showemail();
        p.showage  ();
    }
}

void addrbook::showmenu()
{
    cout << endl << "Select a menu item by pressing a number." << endl;
    cout << "a - Add a new address book entry" << endl;
    cout << "f - Find and show an existing address book entry" << endl;
    cout << "e - Edit an address book entry" << endl;
    cout << "d - Delete an address book entry" << endl;
    cout << "l - Load the address book from a file" << endl;
    cout << "s - Save the address book to a file" << endl;
    cout << "v - View the contents of the address book" << endl;
    cout << "q - Quit the program" << endl << endl;
    cout << "Your choice: ";
}

void addrbook::getmenu(string fname)
{
    fname == "" ? loadpeople()
                : loadpeople(fname);

    char c;
    while(true) {
        showmenu();
        c = cin.get();
        cin.ignore();

        switch(c) {
        case 'a': addperson(); break;
        case 'f': showperson(); break;
        case 'e': editperson(); break;
        case 'd': deleteperson(); break;
        case 'l': loadpeople(); break;
        case 's': savepeople(); break;
	case 'v': viewpeople(); break;
        case 'q': return;
        default:
            cout << "\"" << c << "\" is not a valid selection. Try again.\n";
            break;
        }
    }
}

/************************************************
** main()
************************************************/
int main(int argc, char *argv[])
{
    string fname;
    addrbook ab;

    fname = argc > 1 ? argv[1] : "";
    ab.getmenu(fname);

    return 0;
}


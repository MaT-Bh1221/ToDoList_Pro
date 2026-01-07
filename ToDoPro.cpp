#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <conio.h>

using namespace std;

struct task {
    string task_name;
    int task_id;
    string deadline;
    string description;
    string task_creator;
    string assigned_user;
    bool isCompleted;
};

struct note {
    int note_id;
    string note_text;
    string note_writer;
};

struct users {
    string name;
    string Lname;
    string username;
    bool isAdmin;
    string password;
    vector <task> user_tasks;
    vector <note> user_notes;
};
//=====================================================================
bool whoisthis(vector<users>& userslist, string user_name, string password){ //------- user identify login
    for(users user: userslist){
        if(user_name == user.username && password == user.password)
            return true;
        else
            continue;
    }
    return false;
}
//---------------------------------------------------------------------
int user_index(vector<users>& userslist, string user_name){ // -------returns user index in userslist vector
    for(int i = 0; i < userslist.size(); i++){
        if(user_name == userslist[i].username)
            return i;
    }
    return -1;
}
//---------------------------------------------------------------------
int checknum(){ //------- check number of users in datafile

    ifstream dataf("data.txt");
    string temp;
    int lines = 0;
    while(getline(dataf, temp))
        lines++;
    dataf.close();
    return lines;
}
//---------------------------------------------------------------------
void save_data(vector<users>& userslist){ //------- save data to datafile

    int num = userslist.size();
    ofstream datafile("data.txt");
    if(num > 0){
        for(int i = 0; i < num; i++){
            datafile << userslist[i].name << " " << userslist[i].Lname << " " << userslist[i].username << " " << userslist[i].isAdmin << " " << userslist[i].password << endl;
        }
            datafile.close();
        cout << "\nsaved.\n";
    }
    else
        cout << "\nnot saved.\n";
}
//---------------------------------------------------------------------
void load_data(vector<users>& userslist){ //------- load data from datafile
    
    ifstream datafile("data.txt");
    int lines = checknum();
    for(int i = 0; i < lines; i++){
        userslist.push_back({});
        datafile >> userslist[i].name >> userslist[i].Lname >> userslist[i].username >> userslist[i].isAdmin >> userslist[i].password;
    }
    datafile.close();
}
//---------------------------------------------------------------------
void adduser(vector<users>& userslist){ //------- add new user
    system("cls");
    string temp0, temp1, temp2, temp3;
    bool temp4;
    cout << "\nenter first name : ";
    cin >> temp0;
    cout << "enter last name : ";
    cin >> temp1;
    cout << "enter username : ";
    cin >> temp2;
    cout << "enter password : ";
    cin >> temp3;
    cout << "is admin?";
    cin >> temp4;

    int index = user_index(userslist, temp2);

    if(index == -1){
        userslist.push_back({temp0,temp1,temp2,temp4,temp3});
        save_data(userslist);
        cout << "\nuser added. press any key to go back.";
    }
    else
        cout << "\nusername already exist.";
    
    cout << "\npress any key to go back.";
    char cmd0 = _getch();
}
//---------------------------------------------------------------------
void show_users(vector<users>& userslist){ /////////////////////////////////////////////////
    system("cls");
    for(users user: userslist){
        cout << "fullname : " << user.name << " " << user.Lname << "\nusername : " << user.username << "\nis admin : " << user.isAdmin << "\n\n";
    }
    cout << "\npress any key to go back.";
    char cmd0 = _getch();
}
//---------------------------------------------------------------------
void del_user(vector<users>& userslist, string username){ /////////////////////////////////////////////////////
    int index = user_index(userslist, username);
    if(index != -1){
        userslist.erase(userslist.begin() + index);
        save_data(userslist);
        cout << "\nuser deleted.";
    }
    else
        cout << "\nuser not found.";

    cout << "\npress any key to go back.";
    char cmd0 = _getch();
}
//---------------------------------------------------------------------
void edit_user(vector<users>& userslist, string username){
    int index = user_index(userslist, username);
    if(index != -1){
        system("cls");
        string temp0, temp1, temp2, temp3;
        bool temp4;
        cout << "\nenter first name : ";
        cin >> temp0;
        cout << "enter last name : ";
        cin >> temp1;
        cout << "enter username : ";
        cin >> temp2;
        cout << "enter password : ";
        cin >> temp3;
        cout << "is admin?";
        cin >> temp4;

        userslist[index] = {temp0,temp1,temp2,temp4,temp3};
        save_data(userslist);
        cout << "\nuser edited.";

    }
    else
        cout << "\nuser not found.";

    cout << "\npress any key to go back.";
    char cmd0 = _getch();
}
// ================================main program=====================================
int main(){

    vector<users> user_s;
    string user_name, password;

    load_data(user_s);

    while(true){

        system("cls");

        cout << "USERNAME : ";
        getline(cin, user_name);
        cout << "PASSWORD : ";
        getline(cin, password);

        if(whoisthis(user_s, user_name, password)){
            // ========================logged in=====================
            while(true){

                system("cls");
                if(user_name == user_s[user_index(user_s, user_name)].username && user_s[user_index(user_s, user_name)].isAdmin == true){
                    cout << "welcome Admin.\n2. show users\n3. users management\n4. logout";
                    char cmd = _getch();

                    if(cmd == '1')
                        break;

                    else if(cmd == '2')
                        show_users(user_s);

                    else if(cmd == '3'){
                        system("cls");

                        string func, user_to_func;
                        getline(cin, func);

                        if(func.substr(0,7) == "rm user"){
                            user_to_func = func.erase(0,8);
                            del_user(user_s, user_to_func);
                        }
                        else if(func.substr(0,8) == "add user")
                            adduser(user_s);

                        else if(func.substr(0,9) == "edit user"){
                            user_to_func = func.erase(0,10);
                            edit_user(user_s, user_to_func);
                            break;
                        }
                        else{
                            cout << "invalid command. press any key to go back.";
                            char cmd0 = _getch();
                        }
                    }
                    else if(cmd == '4')
                        break;
                }

                else{
                    cout << "welcome user.";
                    break;
                }
            }
            //=======================================================
        }
        else{
            system("cls");
            cout << "Wrong password or username. try again.\n\n";
            continue;
        }
    }
    
    return 0;
}
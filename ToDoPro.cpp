#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <conio.h>

using namespace std;

struct task {
    int task_id;
    string task_name;
    string deadline;
    string description;
    string task_creator;
    bool isCompleted;
    string assigned_to;
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
    int num_of_tasks = 0;
    vector <int> user_tasks = {};
    vector <int> user_notes = {};
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
            datafile << userslist[i].name << " " << userslist[i].Lname << " " << userslist[i].username << " " << userslist[i].isAdmin << " " << userslist[i].password << " " << userslist[i].num_of_tasks;
            if(userslist[i].num_of_tasks > 0){

                for(int j = 0; j < userslist[i].num_of_tasks; j++){
                    datafile << " " << userslist[i].user_tasks.at(j);
                }
            }
            datafile << endl;
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
        datafile >> userslist[i].name >> userslist[i].Lname >> userslist[i].username >> userslist[i].isAdmin >> userslist[i].password >> userslist[i].num_of_tasks;
        if(userslist[i].num_of_tasks > 0){
            for(int j = 0; j < userslist[i].num_of_tasks; j++){
                int task_id_load;
                datafile >> task_id_load;
                userslist[i].user_tasks.push_back(task_id_load);
            }
        }
    }
    datafile.close();
}
//---------------------------------------------------------------------
void adduser(vector<users>& userslist){ //------- add new user
    system("cls");
    string fname, lname, uname, passw;
    bool isA;
    cout << "\nenter first name : ";
    cin >> fname;
    cout << "enter last name : ";
    cin >> lname;
    cout << "enter username : ";
    cin >> uname;
    int username_checker = user_index(userslist, uname);
    if(username_checker != -1){
        cout << "this username is already exist.";
        return;
    }
    cout << "enter password : ";
    cin >> passw;
    cout << "is admin?";
    cin >> isA;

    userslist.push_back({fname,lname,uname,isA,passw});
    save_data(userslist);
    cout << "\nuser added.";
    
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
void edit_user(vector<users>& userslist, string username){ // --------edit user info 
    int index = user_index(userslist, username);
    if(index != -1){
        system("cls");
        string fname, lname, uname, passw;
        bool isA;
        cout << "\nenter first name : ";
        cin >> fname;
        cout << "enter last name : ";
        cin >> lname;
        cout << "enter username : ";
        cin >> uname;
        int username_checker = user_index(userslist, uname);
        if(username_checker != -1){
            cout << "this username is already exist.";
            return;
        }
        cout << "enter password : ";
        cin >> passw;
        cout << "is admin?";
        cin >> isA;

        userslist[index] = {fname,lname,uname,isA,passw};
        save_data(userslist);
        cout << "\nuser edited.";

    }
    else
        cout << "\nuser not found.";

    cout << "\npress any key to go back.";
    char cmd0 = _getch();
}
//-------------------------------------------------------------
void save_task(vector<users>& userslist,vector<task>& tasklist, string user_name){

    int index = user_index(userslist, user_name), num_tasks = userslist[index].num_of_tasks;
    ofstream taskfile("tasks.txt");
    for(int i = 0; i < num_tasks; i++){
        taskfile << tasklist[i].task_id << " " << tasklist[i].task_name << " " << tasklist[i].deadline << " " << tasklist[i].description << " " << tasklist[i].task_creator << " " << tasklist[i].isCompleted << " " << tasklist[i].assigned_to << "\n";
    }
    taskfile.close();
}
//-------------------------------------------------------------
void load_task(vector<users> userslist, vector<task>& tasklist, string user_name){

    int index = user_index(userslist, user_name), num_tasks = userslist[index].num_of_tasks;

    if(num_tasks > 0){
        ifstream taskfile("tasks.txt");
        for(int i = 0; i < num_tasks; i++){
            tasklist.push_back({});
            taskfile >> tasklist.at(i).task_id >> tasklist.at(i).task_name >> tasklist.at(i).deadline >> tasklist.at(i).description >> tasklist.at(i).task_creator >> tasklist.at(i).isCompleted >> tasklist[i].assigned_to;
        }
        taskfile.close();
    }   
}
//-------------------------------------------------------------
int add_task(vector<users>& userslist, vector<task>& tasklist, string user_name){ // ------add new task

    int task_id, index = user_index(userslist, user_name);
    string task_name, deadline, description ,assigned_to;;

    cout << "enter task id number: ";
    cin >> task_id;
    cin.ignore();
    cout << "enter task name: ";
    getline(cin, task_name);
    cout << "enter deadline: ";
    getline(cin, deadline);
    cout << "enter description: ";
    getline(cin, description);
    cout << "enter assigned to: ";
    getline(cin, assigned_to);  

    int assigned_index = user_index(userslist, assigned_to);

    for(task tsk : tasklist){
        if(tsk.task_id == task_id)
            return 2;
    }

    if(assigned_index == -1)
        return 1;

    userslist[assigned_index].num_of_tasks += 1;
    userslist[assigned_index].user_tasks.push_back(task_id);

    tasklist.push_back({task_id, task_name, deadline, description, user_name, false, assigned_to});

    save_task(userslist, tasklist, user_name);
    save_data(userslist);

    return 0;

}
//-------------------------------------------------------------
void show_tasks(vector<task>& tasklist, string user_name, int state, int idid = -1){ // -------show tasks for user

    system("cls");
    
    if(state == 1){
        cout << "your tasks:\n\n";
        for(task tsk: tasklist){
            if(tsk.task_creator == user_name){
                cout << "task id: " << tsk.task_id << "\ntask name: " << tsk.task_name << "\ndeadline: " << tsk.deadline << "\ndescription: " << tsk.description << "\ntask creator: " << tsk.task_creator << "\nis completed: " << tsk.isCompleted << "\n\n";
            }
        }
    }

    else if(state == 2){
        for(task tsk: tasklist){
            if(tsk.assigned_to == user_name){
                cout << "ID:" << tsk.task_id << "\t" << tsk.task_name << "\ndeadline: " << tsk.deadline << "\n\n";
            }
        }
    }

    else if(state == 3){
        cout << "task :" << idid << "\n\n";
        for(task tsk: tasklist){
            if(tsk.task_id == idid && tsk.assigned_to == user_name){
                cout << "\ntask name: " << tsk.task_name << "\ndeadline: " << tsk.deadline << "\ndescription: " << tsk.description << "\ntask creator: " << tsk.task_creator << "\nis completed: " << tsk.isCompleted << "\n\n";
            }
        }
    }
}
// ====================================================main program=========================================================
int main(){

    vector<users> user_s;
    vector<task> task_s;
    string user_name, password;

    load_data(user_s);

    while(true){

        task_s.clear(); // clear previous user tasks every login
        system("cls");

        cout << "USERNAME : ";
        getline(cin, user_name);
        cout << "PASSWORD : ";
        getline(cin, password);

        if(whoisthis(user_s, user_name, password)){
            load_task(user_s, task_s, user_name);
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
                        cout << "commands:\nremove user -> rm user [username]\nadd new user -> add user\nedit user -> edit user [username]\n\n";

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
                    else{
                        cout << "invalid command. press any key to go back.";
                        char cmd0 = _getch();
                    }
                }

                else{
                    cout << "welcome user.\n1. task & notes\n2. change password\n3. logout";
                    char cmd2 = _getch();
                    if(cmd2 == '1'){
                        show_tasks(task_s, user_name, 2);
                        cout << "commands : add task | show task [id] | ";

                        string func;
                        getline(cin, func);

                        if(func == "add task"){
                            int add_cheker = add_task(user_s, task_s, user_name);
                            if(add_cheker == 0)
                                cout << "task added.";
                            else if(add_cheker == 1)
                                cout << "user assigned to, not found.";
                            else if(add_cheker == 2)
                                cout << "task id already exist.";
                            cout << "\n\npress any key to go back.";
                            char cmd5 = _getch();
                        }

                        else if(func.substr(0,9) == "show task"){
                            int idid = stoi(func.erase(0,10));
                            show_tasks(task_s, user_name, 3, idid);
                            cout << "\n\npress any key to go back.";
                            char cmd5 = _getch();
                        }
                    }
                    
                    else if(cmd2 == '2'){
                        system("cls");
                        string newpass;
                        cout << "enter new password: ";
                        cin >> newpass;
                        int index = user_index(user_s, user_name);
                        user_s[index].password = newpass;
                        save_data(user_s);
                        cout << "password changed. press any key to go back.";
                        char cmd0 = _getch();
                    }
                    else if(cmd2 == '3')
                        break;
                }
            }
            //=======================================================
        }
        else{
            system("cls");
            cout << "Wrong password or username. press any key to try again.\n\n";
            char cmd0 = _getch();
            continue;
        }
    }
    
    return 0;
}

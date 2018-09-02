#include "AgendaUI.hpp"
#include <iostream>
#include <iomanip>
#include <signal.h>
using namespace std;


void catchCC(int n) {
    if (n == SIGINT) {
        cout<<endl<<endl<<endl<<"[You entered ctrl+c so the system shut down ~]"<<endl<<"Bye Bye ~~"<<endl<<endl<<endl;
    }
    exit(0);
}

AgendaUI::AgendaUI() {
    startAgenda();
}

void AgendaUI::OperationLoop(void) {
    signal(SIGINT, catchCC);
    while (executeOperation(getOperation())) {cout<<endl;startAgenda();}
}


    /**
     * constructor
     */
void AgendaUI::startAgenda(void) {
    cout<<"----------------------- Agenda ----------------------"<<endl;
    cout<<"Action :"<<endl;
    cout<<"l   - log in Agenda by user name and password"<<endl;
    cout<<"r   - register an Agenda account"<<endl;
    cout<<"q   - quit Agenda"<<endl;
    cout<<"-----------------------------------------------------"<<endl;
    cout<<endl<<"Agenda : ~$ ";
}

    /**
     * catch user's operation
     * @return the operation
     */
std::string AgendaUI::getOperation() {
    string getFromUser;
    cin>>getFromUser;
    return getFromUser;
}

    /**
     * execute the operation
     * @return if the operationloop continue
     */
bool AgendaUI::executeOperation(std::string t_operation) {
    if (t_operation == "l") {
        userLogIn();
    } else if (t_operation == "r") {
        userRegister();
    } else if (t_operation == "q") {
        return false;
    } else {
        cout<<"[error] invalid input!"<<endl;
    }
    return true;
}

    /**
     * user Login
     */
void AgendaUI::userLogIn(void) {
    cout<<endl;
    cout<<"[log in] [user name] [password]"<<endl;
    cout<<"[log in] ";
    string t_userName, t_password;
    cin>>t_userName>>t_password;
    cout<<"[log in] ";
    if (m_agendaService.userLogIn(t_userName, t_password)) {
        cout<<"[log in] succeed!"<<endl<<endl;
        m_userName = t_userName;
        m_userPassword = t_password;

        while (1) {
            cout<<"----------------------- Agenda ----------------------"<<endl;
            cout<<"Action :"<<endl;
            cout<<"o   - log out Agenda"<<endl;
            cout<<"dc  - delete Agenda account"<<endl;
            cout<<"lu  - list all Agenda user"<<endl;
            cout<<"cm  - create a meeting"<<endl;
            cout<<"la  - list all meetings"<<endl;
            cout<<"las - list all sponsor meetings"<<endl;
            cout<<"lap - list all participate meetings"<<endl;
            cout<<"qm  - query meeting by title"<<endl;
            cout<<"qt  - query meeting by time interval"<<endl;
            cout<<"dm  - delete meeting by title"<<endl;
            cout<<"da  - delete all meetings"<<endl;
            cout<<"cp  - change password"<<endl;
            cout<<"-----------------------------------------------------"<<endl;
            cout<<endl<<"Agenda@"<<m_userName<<" : # ";

            string userChoose = getOperation();
            cout<<endl;
            if (userChoose == "o") {
                userLogOut();
                break;
            } else if (userChoose == "dc") {
                deleteUser();
                break;
            } else if (userChoose == "lu") {
                listAllUsers();
            } else if (userChoose == "cm") {
                createMeeting();
            } else if (userChoose == "la") {
                listAllMeetings();
            } else if (userChoose == "las") {
                listAllSponsorMeetings();
            } else if (userChoose == "lap") {
                listAllParticipateMeetings();
            } else if (userChoose == "qm") {
                queryMeetingByTitle();
            } else if (userChoose == "qt") {
                queryMeetingByTimeInterval();
            } else if (userChoose == "dm") {
                deleteMeetingByTitle();
            } else if (userChoose == "da") {
                deleteAllMeetings();
            } else if (userChoose == "cp") {
                changePassword();
            } else {
                cout<<"[error] invalid input!"<<endl;
            }
            cout<<endl;
        }

    } else {
        cout<<"[error] log in fail!"<<endl;
        cout<<endl;
    }
}

    /**
     * user regist
     */
void AgendaUI::userRegister(void) {
    cout<<endl;
    cout<<"[register] [user name] [password] [email] [phone]"<<endl;
    cout<<"[register] ";
    string t_userName, t_password, t_email, t_phone;
    cin>>t_userName>>t_password>>t_email>>t_phone;
    cout<<"[register] ";
    if (m_agendaService.userRegister(t_userName, t_password, t_email, t_phone)) {       // success
        cout<<"[register] succeed!"<<endl<<endl;
    } else {                                                                            // fail
        cout<<"[error] register fail!"<<endl<<endl;
    }
}

    /**
     * quit the Agenda
     */
void AgendaUI::quitAgenda(void) {}

    /**
     * user logout
     */
void AgendaUI::userLogOut(void) {
    m_userName = "\0";
    m_userPassword = "\0";
}

    /**
     * delete a user from storage
     */
void AgendaUI::deleteUser(void) {
    if (m_agendaService.deleteUser(m_userName, m_userPassword)) {
        cout<<"[delete agenda account] succeed!"<<endl<<endl;
    } else {
        cout<<"[error] delete fail!"<<endl<<endl;
    }
}

    /**
     * list all users from storage
     */
void AgendaUI::listAllUsers(void) {
    cout<<"[list all users]"<<endl<<endl;
    list<User> allUsers = m_agendaService.listAllUsers();
    cout<<left<<setw(15)<<"name";
    cout<<left<<setw(20)<<"email";
    cout<<left<<setw(20)<<"phone"<<endl;
    for (auto i = allUsers.begin(); i != allUsers.end(); i++) {
        for (int p = 1; ; p++) {
            bool flag = true;
            if (i->getName().size() > 14*(p-1)) {
                flag = false;
                cout<<std::left<<setw(15)<<(i->getName().substr(14*(p-1),14));
            }
            if (i->getEmail().size() > 19*(p-1)) {
                flag = false;
                cout<<std::left<<setw(20)<<(i->getEmail().substr(19*(p-1),19));
            }
            if (i->getPhone().size() > 19*(p-1)) {
                flag = false;
                cout<<std::left<<setw(20)<<(i->getPhone().substr(19*(p-1),19));
            }
            if (flag) break;
            cout<<endl;
        }
    }
}

    /**
     * user create a meeting with someone else
     */
void AgendaUI::createMeeting(void) {
    cout<<"[create meeting] [the number of participators]"<<endl<<"[create meeting] ";
    string s_parCount;
    cin>>s_parCount;
    int f = 1;
    int parsCount = 0;
    for (int i = s_parCount.size() - 1; i >= 0; i--) {
        if (s_parCount[i] < '0' || s_parCount[i] > '9') {
            cout<<"[create meeting] error!"<<endl<<endl;
            return;
        }
        parsCount+=(s_parCount[i] - '0') * f;
        f *= 10;
    }
    std::vector<string> t_pars;
    list<User> t_userList = m_agendaService.listAllUsers();
    for (int i = 0; i < parsCount; i++) {
        cout<<"[create meeting] [please enter the participator "<<i+1<<" ]"<<endl<<"[create meeting] ";
        string par;
        cin>>par;
        t_pars.push_back(par);
    }
    cout<<"[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"<<endl;
    cout<<"[create meeting] ";
    string t_title, startDate, endDate;
    cin>>t_title>>startDate>>endDate;
    if (m_agendaService.createMeeting(m_userName, t_title, startDate, endDate, t_pars)) {
        cout<<"[create meeting] succeed!"<<endl<<endl;
    } else {
        cout<<"[create meeting] error!"<<endl<<endl;
    }
}

    /**
     * list all meetings from storage
     */
void AgendaUI::listAllMeetings(void) {
    cout<<"[list all meetings]"<<endl<<endl;
    list<Meeting> allMeetings = m_agendaService.listAllMeetings(m_userName);
    printMeetings(allMeetings);
}

    /**
     * list all meetings that this user sponsored
     */
void AgendaUI::listAllSponsorMeetings(void) {
    cout<<"[list all sponsor meetings]"<<endl<<endl;
    list<Meeting> allSponsorMeetings = m_agendaService.listAllSponsorMeetings(m_userName);
    printMeetings(allSponsorMeetings);
}

    /**
     * list all meetings that this user take part in
     */
void AgendaUI::listAllParticipateMeetings(void) {
    cout<<"[list all participate meetings]"<<endl<<endl;
    list<Meeting> allParMeetings = m_agendaService.listAllParticipateMeetings(m_userName);
    printMeetings(allParMeetings);
}

    /**
     * search meetings by title from storage
     */
void AgendaUI::queryMeetingByTitle(void) {
    cout<<"[query meeting] [title]"<<endl;
    cout<<"[query meeting] ";
    string t_title;
    cin>>t_title;
    list<Meeting> query = m_agendaService.meetingQuery(m_userName, t_title);
    printMeetings(query);
}

    /**
     * search meetings by timeinterval from storage
     */
void AgendaUI::queryMeetingByTimeInterval(void) {
    cout<<"[query meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"<<endl;
    cout<<"[query meeting] ";
    string t_startDate, t_endDate;
    cin>>t_startDate>>t_endDate;
    cout<<"[query meeting]"<<endl;
    list<Meeting> query = m_agendaService.meetingQuery(m_userName, t_startDate, t_endDate);
    printMeetings(query);
}

    /**
     * delete meetings by title from storage
     */
void AgendaUI::deleteMeetingByTitle(void) {
    cout<<"[delete meeting] [title]"<<endl<<"[delete meeting] ";
    string t_title;
    cin>>t_title;
    if (m_agendaService.deleteMeeting(m_userName, t_title)) {
        cout<<"[delete meeting by title] succeed!"<<endl<<endl;
    } else {
        cout<<"[error] delete meeting fail!"<<endl<<endl;
    }
}

    /**
     * delete all meetings that this user sponsored
     */
void AgendaUI::deleteAllMeetings(void) {
    if (m_agendaService.deleteAllMeetings(m_userName)) {
        cout<<"[delete meeting all meetings] succeed!"<<endl<<endl;
    } else {
        cout<<"[error] delete meeting fail!"<<endl<<endl;
    }
}

void AgendaUI::changePassword(void) {
    cout<<"[change password] [new password]"<<endl;
    cout<<"[change password] ";
    string newPassword;
    cin>>newPassword;
    m_agendaService.changePassword(m_userName, newPassword);
    m_userPassword = newPassword;
    cout<<"[change password] succeed!"<<endl<<endl;
}

    /**
     * show the meetings in the screen
     */
void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
    for (int i = 0; i < 105; i++) cout<<'-';
    cout<<endl;
    cout<<left<<setw(20)<<"title"<<"|";
    cout<<left<<setw(20)<<"sponsor"<<"|";
    cout<<left<<setw(20)<<"start time"<<"|";
    cout<<left<<setw(20)<<"end time"<<"|";
    cout<<left<<setw(20)<<"participators"<<"|"<<endl;
    for (int i = 0; i < 105; i++) cout<<'-';
    cout<<endl;
    for (auto i = t_meetings.begin(); i != t_meetings.end(); i++) {
        string participators;
        for (int j = 0; j < i->getParticipator().size(); j++) {
            if (j) participators+=",";
            participators+=i->getParticipator()[j];
        }
        for (int p = 1; ; p++) {
            bool printTitle = false;
            bool printSponsor = false;
            bool printPars = false;
            if (i->getTitle().size() > 19*(p-1)) {
                printTitle = true;
            }
            if (i->getSponsor().size() > 19*(p-1)) {
                printSponsor = true;
            }
            if (participators.size() > 19*(p-1)) {
                printPars = true;
            }
            if (!printTitle && !printSponsor && !printPars) break;
            if (printTitle) {
                cout<<std::left<<setw(20)<<(i->getTitle().substr(19*(p-1),19))<<'|';
            } else {
                cout<<std::left<<setw(20)<<" "<<'|';
            }
            if (printSponsor) {
                cout<<std::left<<setw(20)<<(i->getSponsor().substr(19*(p-1),19))<<'|';
            } else {
                cout<<std::left<<setw(20)<<" "<<'|';
            }
            if (p == 1) {
                cout<<std::left<<setw(20)<<Date::dateToString(i->getStartDate())<<'|';
                cout<<std::left<<setw(20)<<Date::dateToString(i->getEndDate())<<'|';
            } else {
                cout<<std::left<<setw(20)<<" "<<'|';
                cout<<std::left<<setw(20)<<" "<<'|';
            }
            if (printSponsor) {
                cout<<std::left<<setw(20)<<participators<<'|';
            } else {
                cout<<std::left<<setw(20)<<" "<<'|';
            }
            cout<<endl;
        }
        for (int i = 0; i < 105; i++) cout<<'-';
        cout<<endl;
    }
}

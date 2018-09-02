#include "AgendaService.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

AgendaService::AgendaService() {
    startAgenda();
}

    /**
     * destructor
     */
AgendaService::~AgendaService() {
    m_storage->sync();
    quitAgenda();
}

    /**
     * check if the userna  me match password
     * @param userName the username want to login
     * @param password the password user enter
     * @return if success, true will be returned
     */ 
bool AgendaService::userLogIn(const std::string userName, const std::string password) {
    list<User> t_userList = m_storage->queryUser([&](const User &t_user)->bool{return true;});
    list<User>::const_iterator i;
    for (i = t_userList.begin(); i != t_userList.end(); i++) {
        if ((*i).getName() == userName && (*i).getPassword() == password) return true;
    }
    return false;
}

    /**
     * regist a user
     * @param userName new user's username
     * @param password new user's password
     * @param email new user's email
     * @param phone new user's phone
     * @return if success, true will be returned
     */
bool AgendaService::userRegister(const std::string userName, const std::string password,
                      const std::string email, const std::string phone) {
    if (userName.find('&') != string::npos || userName.find('"') != string::npos || 
        userName.find(',') != string::npos || password.find('&') != string::npos ||
        password.find('"') != string::npos || password.find(',') != string::npos ||
        email.find('&') != string::npos || email.find('"') != string::npos ||
        email.find(',') != string::npos || phone.find('&') != string::npos ||
        phone.find('"') != string::npos || phone.find(',') != string::npos) return false;

    list<User> t_userList = m_storage->queryUser([&](const User &t_user)->bool{return true;});
    list<User>::const_iterator i;
    for (i = t_userList.begin(); i != t_userList.end(); i++) {
        if ((*i).getName() == userName) return false;
    }

    User tempUser(userName, password, email, phone);
    m_storage->createUser(tempUser);
    m_storage->sync();
    return true;
}

    /**
     * delete a user
     * @param userName user's username
     * @param password user's password
     * @return if success, true will be returned
     */
bool AgendaService::deleteUser(const std::string userName, const std::string password) {
    if (!userLogIn(userName, password)) return false;  
    m_storage->deleteMeeting([&](const Meeting &t_meeting)->bool{
        vector<string> pars = t_meeting.getParticipator();
        bool isPar = false;
        for (int i = 0; i < pars.size(); i++) {
            if (pars[i] == userName) {
                isPar = true;
                break;
            }
        }
        return (isPar || t_meeting.getSponsor() == userName);
    }); 
    m_storage->deleteUser([&](const User& t_user)->bool{
        return t_user.getName() == userName && t_user.getPassword() == password;
    });
    m_storage->sync();
    return true;
}

    /**
     * list all users from storage
     * @return a user list result
     */
std::list<User> AgendaService::listAllUsers(void) const {
    return m_storage->queryUser([&](const User &t_user)->bool{return true;});
}

    /**
     * create a meeting
     * @param userName the sponsor's userName
     * @param title the meeting's title
     * @param participator the meeting's participator
     * @param startDate the meeting's start date
     * @param endData the meeting's end date
     * @return if success, true will be returned
     */
bool AgendaService::createMeeting(const std::string userName, const std::string title,
                       const std::string startDate, const std::string endDate,
                       const std::vector<std::string> participator) {
    if (participator.size() == 0) return false;
    if (!m_storage->queryMeeting([&](const Meeting&t_meeting)->bool{return t_meeting.getTitle() == title;}).empty()) 
        return false;
    list<User> allUser = listAllUsers();
    for (int i = 0; i < participator.size(); i++) {
        bool hasPar = false;
        if (participator[i] == userName) return false;
        for (auto j = allUser.begin(); j != allUser.end(); j++) {
            if ((*j).getName() == participator[i]) {
                hasPar = true;
                break;
            }
        }
        if (!hasPar) return false;
    }
    for (int i = 0; i < participator.size(); i++) {
        for (int j = i+1; j < participator.size(); j++) {
            if (participator[i] == participator[j]) return false;
        }
    }
    Date t_startDate(startDate), t_endDate(endDate);
    if (!Date::isValid(t_startDate) || !Date::isValid(t_endDate)) return false;
    if (t_startDate >= t_endDate) return false;
    if (!m_storage->queryMeeting([&](const Meeting&t_meeting)->bool{
            bool parConflict = false;
            for (auto i = participator.begin(); i != participator.end(); i++) {
                if (t_meeting.isParticipator(*i) || t_meeting.getSponsor() == (*i)) {
                    parConflict = true;
                    break;
                }
            }
            if (!t_meeting.isParticipator(userName) && (!parConflict) && t_meeting.getSponsor() != userName) return false;
            return !(t_startDate >= t_meeting.getEndDate() ||
                    t_meeting.getStartDate() >= t_endDate);
            }).empty()) 
        return false;

    Meeting t_meeting(userName, participator, t_startDate, t_endDate, title);
    m_storage->createMeeting(t_meeting);
    m_storage->sync();
    return true;
}

    /**
     * search meetings by username and title (user as sponsor or participator)
     * @param uesrName the user's userName
     * @param title the meeting's title
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const {
    return m_storage->queryMeeting([&](const Meeting &t_meeting)->bool{
        vector<string> pars = t_meeting.getParticipator();
        bool isPar = false;
        for (int i = 0; i < pars.size(); i++) {
            if (pars[i] == userName) {
                isPar = true;
                break;
            }
        }
        return (isPar || t_meeting.getSponsor() == userName) && t_meeting.getTitle() == title;
    });
}
    /**
     * search a meeting by username, time interval (user as sponsor or participator)
     * @param uesrName the user's userName
     * @param startDate time interval's start date
     * @param endDate time interval's end date
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const {
    return m_storage->queryMeeting([&](const Meeting &t_meeting)->bool{
        vector<string> pars = t_meeting.getParticipator();
        bool isPar = false;
        for (int i = 0; i < pars.size(); i++) {
            if (pars[i] == userName) {
                isPar = true;
                break;
            }
        }
        Date t_startDate(startDate), t_endDate(endDate);
        return (isPar || t_meeting.getSponsor() == userName) && 
                !(t_startDate > t_meeting.getEndDate() ||
                    t_meeting.getStartDate() > t_endDate);
    });
}

    /**
     * list all meetings the user take part in
     * @param userName user's username
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const {
    return m_storage->queryMeeting([&](const Meeting &t_meeting)->bool{
        vector<string> pars = t_meeting.getParticipator();
        bool isPar = false;
        for (int i = 0; i < pars.size(); i++) {
            if (pars[i] == userName) {
                isPar = true;
                break;
            }
        }
        return (isPar || t_meeting.getSponsor() == userName);
    });
}

    /**
     * list all meetings the user sponsor
     * @param userName user's username
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const {
    return m_storage->queryMeeting([&](const Meeting &t_meeting)->bool{
        return (t_meeting.getSponsor() == userName);
    });
}

    /**
     * list all meetings the user take part in and sponsor by other
     * @param userName user's username
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::listAllParticipateMeetings(
        const std::string userName) const {
    return m_storage->queryMeeting([&](const Meeting &t_meeting)->bool{
        vector<string> pars = t_meeting.getParticipator();
        bool isPar = false;
        for (int i = 0; i < pars.size(); i++) {
            if (pars[i] == userName) {
                isPar = true;
                break;
            }
        }
        return isPar;
    });
}

    /**
     * delete a meeting by title and its sponsor
     * @param userName sponsor's username
     * @param title meeting's title
     * @return if success, true will be returned
     */
bool AgendaService::deleteMeeting(const std::string userName, const std::string title) {
    if (m_storage->queryMeeting([&](const Meeting&t_meeting)->bool{
            return t_meeting.getSponsor() == userName && t_meeting.getTitle() == title;}).empty()) 
        return false;
    m_storage->deleteMeeting([&](const Meeting &t_meeting)->bool{
        return (t_meeting.getSponsor() == userName && t_meeting.getTitle() == title);
    }); 
    return true;
}

    /**
     * delete all meetings by sponsor
     * @param userName sponsor's username
     * @return if success, true will be returned
     */
bool AgendaService::deleteAllMeetings(const std::string userName) {
    if (m_storage->queryMeeting([&](const Meeting&t_meeting)->bool{
            return t_meeting.getSponsor() == userName;}).empty()) 
        return false;
    m_storage->deleteMeeting([&](const Meeting &t_meeting)->bool{
        return (t_meeting.getSponsor() == userName);
    }); 
    return true;
}

    /**
     * start Agenda service and connect to storage
     */
void AgendaService::startAgenda(void) {
    m_storage = Storage::getInstance();
}

    /**
     * quit Agenda service
     */
void AgendaService::quitAgenda(void) {
    m_storage.reset();
}

void AgendaService::changePassword(const std::string userName, const std::string newPassword) {
    m_storage->updateUser([&](const User& t_user)->bool{return t_user.getName() == userName;},
                          [&](User& t_user)->void{t_user.setPassword(newPassword);} );
}

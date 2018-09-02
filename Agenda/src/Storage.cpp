#include "Storage.hpp"
#include "Path.hpp"
#include <iostream>
#include <fstream>
using namespace std;

shared_ptr<Storage> Storage::m_instance(new Storage);

Storage::Storage() {
 readFromFile();
  m_dirty = false;      // no need to write;
}

  /**
  *   read file content into memory
  *   @return if success, true will be returned
  */
bool Storage::readFromFile(void) {
  {ifstream in(Path::userPath);
    if (!in) return false;
    string tmp;
    while (1) {
      getline(in,tmp);
      if (!in) break;
      int pos1, pos2, pos3;
      pos1 = tmp.find(',');            // the pos of the 1st ','
      pos2 = tmp.find(',', pos1+1);    // the pos of the 2nd ','
      pos3 = tmp.find(',', pos2+1);    // the pos of the 3rd ','
      string t_name = tmp.substr(1, pos1-2);
      string t_password = tmp.substr(pos1+2, pos2-pos1-3);
      string t_email = tmp.substr(pos2+2, pos3-pos2-3);
      string t_phone = tmp.substr(pos3+2, tmp.size()-pos3-3);
      User tempUser(t_name,t_password,t_email,t_phone);
      m_userList.push_back(tempUser);
    }
    in.close();}

  {ifstream in(Path::meetingPath);
    if (!in) return false;
    string temp;
    while (1) {
      getline(in,temp);
      if (!in) break;
      int pos1, pos2, pos3, pos4;
      pos1 = temp.find(',');            // the pos of the 1st ','
      pos2 = temp.find(',', pos1+1);    // the pos of the 2nd ','
      pos3 = temp.find(',', pos2+1);    // the pos of the 3rd ','
      pos4 = temp.find(',', pos3+1);    // the pos of the 4th ','
      string t_sponsor = temp.substr(1, pos1-2);
  
      vector<string> t_participators;
      string s_participators = temp.substr(pos1+2, pos2-pos1-3);
      int p;
      while (s_participators.size()) {
        p = s_participators.find('&');
        if (p == string::npos) {
          t_participators.push_back(s_participators);
          break;
        }
        string a = s_participators.substr(0,p);
        t_participators.push_back(a);
        s_participators = s_participators.substr(p+1, s_participators.size()-p-1);
      }
  
      Date t_startDate(temp.substr(pos2+2, pos3-pos2-3));
      Date t_endDate(temp.substr(pos3+2, pos4-pos3-3));
      string t_title = temp.substr(pos4+2, temp.size()-pos4-3);
      Meeting tempMeeting(t_sponsor,t_participators,t_startDate,t_endDate,t_title);
      m_meetingList.push_back(tempMeeting);
    }
    in.close();}


  return true;
}

  /**
  *   write file content from memory
  *   @return if success, true will be returned
  */
bool Storage::writeToFile(void) {
  {
    ofstream out(Path::userPath);
    if (!out) return false;
    out.clear();
    list<User>::iterator i;
    for (i = m_userList.begin(); i != m_userList.end(); i++) {
      out<<"\""<<(*i).getName()<<"\",\""<<(*i).getPassword()<<"\",\"";
      out<<(*i).getEmail()<<"\",\""<<(*i).getPhone()<<'"';
      i++;
      if (i != m_userList.end()) out<<endl;
      i--;
    }
    out.close();}

  {
    ofstream out(Path::meetingPath);
    if (!out) return false;
    out.clear();
    list<Meeting>::iterator i;
    for (i = m_meetingList.begin(); i != m_meetingList.end(); i++) {
      out<<"\""<<(*i).getSponsor()<<"\",\"";
      vector<string> participators = (*i).getParticipator();
      vector<string>::iterator j;
      for (j = participators.begin(); j < participators.end(); j++) {
        if (j != participators.begin()) out<<"&";
        out<<(*j);
      }
      out<<"\",\"";
      out<<Date::dateToString((*i).getStartDate());
      out<<"\",\"";
      out<<Date::dateToString((*i).getEndDate());
      out<<"\",\""<<(*i).getTitle()<<'"';
      i++;
      if (i != m_meetingList.end()) out<<endl;
      i--;
    }
    out.close();}

  return true;
}

  /**
  * get Instance of storage
  * @return the pointer of the instance
  */
std::shared_ptr<Storage> Storage::getInstance(void) {
  return m_instance;
}

  /**
  *   destructor
  */
Storage::~Storage() {
  writeToFile();
}

  // CRUD for User & Meeting
  // using C++11 Function Template and Lambda Expressions

  /**
  * create a user
  * @param a user object
  */
void Storage::createUser(const User & t_user) {
  m_userList.push_back(t_user);
  m_dirty = true;           // need to write
}

  /**
  * query users
  * @param a lambda function as the filter
  * @return a list of fitted users
  */
std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
  list<User> re;
  list<User>::const_iterator i;
  for (i = m_userList.begin(); i != m_userList.end(); i++) {
    if (filter(*i)) re.push_back(*i);
  }
  return re;
}

  /**
  * update users
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the user
  * @return the number of updated users
  */
int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher) {
  int re = 0;
  list<User>::iterator i;
  for (i = m_userList.begin(); i != m_userList.end(); i++) {
    if (filter(*i)) {
      re++;
      switcher(*i);
    }
  }
  if (re) m_dirty = true;           // need to write
  return re;
}

  /**
  * delete users
  * @param a lambda function as the filter
  * @return the number of deleted users
  */
int Storage::deleteUser(std::function<bool(const User &)> filter) {
  int re = 0;
  for (list<User>::iterator i = m_userList.begin(); i != m_userList.end();) {
    if (filter(*i)) {
      re++;
      i = m_userList.erase(i);
    } else {
      i++;
    }
  }
  if (re) m_dirty = true;           // need to write
  return re;
}

  /**
  * create a meeting
  * @param a meeting object
  */
void Storage::createMeeting(const Meeting & t_meeting) {
  m_meetingList.push_back(t_meeting);
  m_dirty = true;           // need to write
}

  /**
  * query meetings
  * @param a lambda function as the filter
  * @return a list of fitted meetings
  */
list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
  list<Meeting> re;
  list<Meeting>::const_iterator i;
  for (i = m_meetingList.begin(); i != m_meetingList.end(); ++i) {
    if (filter(*i)) re.push_back(*i);
  }
  return re;
}

  /**
  * update meetings
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the meeting
  * @return the number of updated meetings
  */
int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher) {
  int re = 0;
  list<Meeting>::iterator i;
  for (i = m_meetingList.begin(); i != m_meetingList.end(); ++i) {
    if (filter(*i)) {
      re++;
      switcher(*i);
    }
  }
  if (re) m_dirty = true;           // need to write
  return re;
}

  /**
  * delete meetings
  * @param a lambda function as the filter
  * @return the number of deleted meetings
  */
int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
  int re = 0;
  for (list<Meeting>::iterator i = m_meetingList.begin(); i != m_meetingList.end();) {
    if (filter(*i)) {
      re++;
      i = m_meetingList.erase(i);
    } else {
      i++;
    }
  }
  if (re) m_dirty = true;           // need to write
  return re;
}

  /**
  * sync with the file
  */
bool Storage::sync(void) {
  return writeToFile();
}
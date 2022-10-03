//
// Created by 庞博 on 2018-12-16.
//

#pragma once
#ifndef BJFU_TOUR_GUIDE_USERMANAGEMENT_H
#define BJFU_TOUR_GUIDE_USERMANAGEMENT_H

#include <fstream>
#include "../Library/Vector.h"
#include "../DataModel/User.h"
#include "../Util/UWPHelper.h"
#include "../Util/StatusType.h"
#include "../Util/ReturnType.h"

class UserService
{
  private:
    Structure::Vector<User> users;
    UserServiceStatus CurrentStatus;

  public:
    UserService();

    virtual ~UserService();

    UserServiceReturnType login(const Structure::String &username, const Structure::String &password);

    void logout();

    UserServiceReturnType createUser(const Structure::String &username, const Structure::String &password);

    UserServiceReturnType deleteUser(const Structure::String &username, const Structure::String &password);

    UserServiceReturnType changePassWord(const Structure::String &username, const Structure::String &password,
                                         Structure::String &newPassword);

    UserServiceStatus getCurrentStatus() const;

  protected:
    void dataBaseUpdate();
};

#endif //BJFU_TOUR_GUIDE_USERMANAGEMENT_H

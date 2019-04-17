//
// Created by 庞博 on 2018-12-19.
//

#pragma once
#ifndef BJFU_TOUR_GUIDE_USER_H
#define BJFU_TOUR_GUIDE_USER_H

#include "../Library/String.h"
#include "../Library/MD5.h"
#include "../Util/ReturnType.h"

class User
{
  private:
    Structure::String _username;
    Structure::String _password;

  public:
    User();

    User(const Structure::String &username, const Structure::String &password);

    const Structure::String &getUsername() const;

    void setUsername(const Structure::String &_username);

    const Structure::String &getPassword() const;

    void setPassword(const Structure::String &_password);

    bool verify(const Structure::String &password);

    UserReturnType changePassword(const Structure::String &password, const Structure::String &newPassword);

    bool operator==(const User &rhs) const;

    bool operator!=(const User &rhs) const;

	friend std::istream &operator>>(std::istream &in, User &user);

    friend std::ostream &operator<<(std::ostream &os, const User &user);

  protected:
    static Structure::String ConvertToMD5(const Structure::String &str);
};

#endif //BJFU_TOUR_GUIDE_USER_H
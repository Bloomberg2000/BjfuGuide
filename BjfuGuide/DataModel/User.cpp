#include "pch.h"
#include "User.h"
#include <iostream>

User::User() = default;

User::User(const Structure::String &username, const Structure::String &password)
{
	_username = username;
	_password = User::ConvertToMD5(password);
}

const Structure::String &User::getUsername() const
{
	return _username;
}

void User::setUsername(const Structure::String &_username)
{
	User::_username = _username;
}

const Structure::String &User::getPassword() const
{
	return _password;
}

void User::setPassword(const Structure::String &_password)
{
	User::_password = _password;
}

bool User::verify(const Structure::String &password)
{
	return _password == User::ConvertToMD5(password);
}

UserReturnType User::changePassword(const Structure::String &password, const Structure::String &newPassword)
{
	if (verify(password))
	{
		_password = User::ConvertToMD5(newPassword);
		return UserReturnType::SUCCESS;
	}
	else
	{
		return UserReturnType::PASSWORD_WRONG;
	}
}

std::istream & operator>>(std::istream &in, User & user)
{
	in >> user._username >> user._password;
	return in;
}

std::ostream &operator<<(std::ostream &os, const User &user)
{
	os << user._username << "" << user._password;
	return os;
}

bool User::operator==(const User &rhs) const
{
	return _username == rhs._username;
}

bool User::operator!=(const User &rhs) const
{
	return !(rhs == *this);
}

Structure::String User::ConvertToMD5(const Structure::String &str)
{
	return Structure::String(Structure::MD5(str.cpp_str()).toStr());
}
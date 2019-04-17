#include "pch.h"
#include "UserService.h"
#include "ServiceController.h"

UserService::UserService()
{
	std::ifstream inFile;
	inFile.open(UWPHelper::getFilePath("users.db"), std::ios::in | std::ios::binary);
	if (!inFile)
	{
		CurrentStatus = UserServiceStatus::DB_ERROR;
	}
	while (!inFile.eof())
	{ //一直读到文件结束
		User user;
		inFile >> user;
		if (user.getUsername().length() == 0 &&
			user.getPassword().length() == 0)
		{
			break;
		}
		users.insert(user);
	}
	CurrentStatus = UserServiceStatus::DB_SUCCESS;
	inFile.close();
}

UserService::~UserService()
{
	dataBaseUpdate();
}

UserServiceReturnType UserService::login(const Structure::String &username, const Structure::String &password)
{
	int index = users.find(User(username, ""));
	if (index != -1)
	{
		if (users[index].verify(password))
		{
			ServiceController::IsLogin = true;
			return UserServiceReturnType::SUCCESS;
		}
		else
		{
			return UserServiceReturnType::PASSWORD_WRONG;
		}
	}
	else
	{
		return UserServiceReturnType::USER_NOT_EXIST;
	}
}

void UserService::logout()
{
	ServiceController::IsLogin = false;
}

UserServiceReturnType
UserService::createUser(const Structure::String &username, const Structure::String &password)
{
	if (users.find(User(username, "")) != -1)
	{
		return UserServiceReturnType::USER_HAS_EXISTED;
	}
	users.insert(User(username, password));
	dataBaseUpdate();
	return UserServiceReturnType::SUCCESS;
}

UserServiceReturnType
UserService::deleteUser(const Structure::String &username, const Structure::String &password)
{
	int index = users.find(User(username, ""));
	if (index != -1)
	{
		if (users[index].verify(password))
		{
			users.remove(index);
			dataBaseUpdate();
			return UserServiceReturnType::SUCCESS;
		}
		else
		{
			return UserServiceReturnType::PASSWORD_WRONG;
		}
	}
	else
	{
		return UserServiceReturnType::USER_NOT_EXIST;
	}
}

UserServiceReturnType
UserService::changePassWord(const Structure::String &username, const Structure::String &password,
							Structure::String &newPassword)
{
	int index = users.find(User(username, ""));
	if (index != -1)
	{
		UserReturnType status = users[index].changePassword(password, newPassword);
		if (status == UserReturnType::SUCCESS)
		{
			dataBaseUpdate();
			return UserServiceReturnType::SUCCESS;
		}
		else
		{
			// status == UserReturnType::PASSWORD_WRONG)
			return UserServiceReturnType::PASSWORD_WRONG;
		}
	}
	else
	{
		return UserServiceReturnType::USER_NOT_EXIST;
	}
}

UserServiceStatus UserService::getCurrentStatus() const
{
	return CurrentStatus;
}

void UserService::dataBaseUpdate()
{
	std::ofstream outFile;
	outFile.open(UWPHelper::getFilePath("users.db"), std::ios::out | std::ios::binary);
	if (!outFile)
	{
		CurrentStatus = UserServiceStatus::DB_ERROR;
	}
	for (int i = 0; i < users.size(); i++)
	{
		outFile << users[i] << std::endl;
	}
	CurrentStatus = UserServiceStatus::DB_SUCCESS;
	outFile.close();
}
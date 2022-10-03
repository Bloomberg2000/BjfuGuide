#pragma once
#include "Service/MapService.h"
#include "Service/UserService.h"

class ServiceController
{
public:
	static MapService mapService;
	static UserService userService;
	static bool IsLogin;
};

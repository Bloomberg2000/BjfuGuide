//
// Created by 庞博 on 2018-12-19.
//

#pragma once
#ifndef BJFU_TOUR_GUIDE_RETURNTYPE_H
#define BJFU_TOUR_GUIDE_RETURNTYPE_H

enum class UserReturnType
{
    SUCCESS,
    PASSWORD_WRONG
};

enum class UserServiceReturnType
{
    SUCCESS,
    USER_NOT_EXIST,
    USER_HAS_EXISTED,
    PASSWORD_WRONG
};

enum class MapServiceReturnType
{
    SUCCESS,
    SPOT_NOT_EXIST,
    SPOT_HAS_EXISTED,
    ROUTE_NOT_EXIST,
    ROUTE_HAS_EXIST
};

#endif //BJFU_TOUR_GUIDE_RETURNTYPE_H

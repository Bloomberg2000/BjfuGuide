#include "pch.h"
#include "TourRoute.h"
#include <iostream>

TourRoute::TourRoute(int _routeLength) : _routeLength(_routeLength) {}

int TourRoute::get_routeLength() const
{
	return _routeLength;
}

void TourRoute::set_routeLength(int _routeLength)
{
	TourRoute::_routeLength = _routeLength;
}

std::istream &operator>>(std::istream &is, TourRoute &route)
{
	is >> route._routeLength;
	return is;
}

std::ostream &operator<<(std::ostream &os, const TourRoute &route)
{
	os << route._routeLength;
	return os;
}

bool TourRoute::operator<(const TourRoute &rhs) const
{
	return _routeLength < rhs._routeLength;
}

bool TourRoute::operator>(const TourRoute &rhs) const
{
	return rhs < *this;
}

bool TourRoute::operator<=(const TourRoute &rhs) const
{
	return !(rhs < *this);
}

bool TourRoute::operator>=(const TourRoute &rhs) const
{
	return !(*this < rhs);
}

bool TourRoute::operator==(const TourRoute &rhs) const
{
	return _routeLength == rhs._routeLength;
}

bool TourRoute::operator!=(const TourRoute &rhs) const
{
	return !(rhs == *this);
}

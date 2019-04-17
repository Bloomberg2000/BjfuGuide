#include "pch.h"
#include "ScenicSpot.h"

ScenicSpot::ScenicSpot(const Structure::String &name, const Structure::String &info) : _name(name), _info(info)
{
	functionAnalysis(info);
}

const Structure::String &ScenicSpot::get_name() const
{
	return _name;
}

void ScenicSpot::set_name(const Structure::String &_name)
{
	ScenicSpot::_name = _name;
}

const Structure::String &ScenicSpot::get_info() const
{
	return _info;
}

void ScenicSpot::set_info(const Structure::String &_info)
{
	ScenicSpot::_info = _info;
}

const Structure::Vector<SpotFunction> &ScenicSpot::get_function() const
{
	return _function;
}

std::istream &operator>>(std::istream &is, ScenicSpot &scenicSpot)
{
	is >> scenicSpot._name >> scenicSpot._info;
	scenicSpot.functionAnalysis(scenicSpot._info);
	return is;
}

std::ostream &operator<<(std::ostream &os, const ScenicSpot &scenicSpot)
{
	os << scenicSpot._name << " " << scenicSpot._info;
	return os;
}

void ScenicSpot::functionAnalysis(const Structure::String &info)
{
	if (info.find("����") != info.length() || info.find("��ѧ") != info.length())
	{
		_function.insert(SpotFunction::TEACHING);
		_function.insert(SpotFunction::SELF_STUDY);
	}
	if (info.find("����") != info.length())
	{
		_function.insert(SpotFunction::ACCOMMODATION);
	}
	if (info.find("�칫") != info.length())
	{
		_function.insert(SpotFunction::OFFICE);
	}
	if (info.find("��") != info.length() ||
		info.find("��") != info.length() ||
		info.find("ʳ") != info.length())
	{
		_function.insert(SpotFunction::RESTAURANT);
	}
}

bool ScenicSpot::operator==(const ScenicSpot &rhs) const
{
	return _name == rhs._name;
}

bool ScenicSpot::operator!=(const ScenicSpot &rhs) const
{
	return !(rhs == *this);
}
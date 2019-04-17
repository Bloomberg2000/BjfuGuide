#pragma once


using namespace Platform;
using namespace Windows::Storage;

#include <string>
#include <vector>
class UWPHelper {
public:
	// 字符串分割
	static int StringSplit(std::vector<std::string>& dst, const std::string& src, const std::string& separator) {
		if (src.empty() || separator.empty())
			return 0;
		int nCount = 0;
		std::string temp;
		size_t pos = 0, offset = 0;
		// 分割第1~n-1个
		while ((pos = src.find_first_of(separator, offset)) != std::string::npos)
		{
			temp = src.substr(offset, pos - offset);
			if (temp.length() > 0) {
				dst.push_back(temp);
				nCount++;
			}
			offset = pos + 1;
		}
		// 分割第n个
		temp = src.substr(offset, src.length() - offset);
		if (temp.length() > 0) {
			dst.push_back(temp);
			nCount++;
		}
		return nCount;
	}

	static std::string ws2s(const std::wstring &ws)
	{
		size_t i;
		std::string curLocale = setlocale(LC_ALL, NULL);
		setlocale(LC_ALL, "chs");
		const wchar_t* _source = ws.c_str();
		size_t _dsize = 2 * ws.size() + 1;
		char* _dest = new char[_dsize];
		memset(_dest, 0x0, _dsize);
		wcstombs_s(&i, _dest, _dsize, _source, _dsize);
		std::string result = _dest;
		delete[] _dest;
		setlocale(LC_ALL, curLocale.c_str());
		return result;
	}

	static std::wstring s2ws(const std::string &s)
	{
		size_t i;
		std::string curLocale = setlocale(LC_ALL, NULL);
		setlocale(LC_ALL, "chs");
		const char* _source = s.c_str();
		size_t _dsize = s.size() + 1;
		wchar_t* _dest = new wchar_t[_dsize];
		wmemset(_dest, 0x0, _dsize);
		mbstowcs_s(&i, _dest, _dsize, _source, _dsize);
		std::wstring result = _dest;
		delete[] _dest;
		setlocale(LC_ALL, curLocale.c_str());
		return result;
	}

	static std::string Platform_str_to_std_str(Platform::String^ ms)
	{
		std::wstring ws1(ms->Data());
		return ws2s(ws1);
	}

	static Platform::String^ std_str_To_Platform_Str(const std::string & input)
	{
		//std::wstring w_str = std::wstring(input.begin(), input.end());
		std::wstring w_str = s2ws(input);
		const wchar_t* w_chars = w_str.c_str();
		return (ref new Platform::String(w_chars));
	}

	static const std::wstring getFilePath(const std::string & input) {
		// Get the app's installation folder
		StorageFolder^ appFolder = ApplicationData::Current->LocalFolder;
		String^ path = appFolder->Path + "\\" +std_str_To_Platform_Str(input);
		// Get the app's manifest file from the current folder
		return path->Data();
	}
};
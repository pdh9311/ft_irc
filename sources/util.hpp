#include <string>
#include <vector>

namespace irc
{
	std::vector<std::string>	split(const std::string& str, char delim = ',');
	int							stoi(const std::string& str);
	std::string					itos(const int& x);
	std::string					to_string(const int& x);
	bool						isLetterC(const char c);
	bool						isLetterStr(const std::string& str);
	bool						isDigitC(const char c);
	bool						isDigitStr(const std::string& str);
	bool						isUserC(const char c);
	bool						isUserStr(const std::string& str);
	bool						isHexDigitC(const char c);
	bool						isHexDigitStr(const std::string& str);
	bool						isSpecialC(const char c);
	bool						isSpecialStr(const std::string& str);
	bool						isNickStr(const std::string& str);
	bool						isChPrefix(const char c);
	bool						isChString(const char c);
}

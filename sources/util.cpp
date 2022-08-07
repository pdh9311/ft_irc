#include "util.hpp"

#include <sstream>
#include <iomanip>

namespace irc
{
	std::vector<std::string>	split(const std::string& str, char delim)
	{
		std::vector<std::string>	ret;
		size_t						cur = 0;
		size_t						fpos = cur;

		if (str.empty())
			return (ret);

		while (1)
		{
			fpos = str.find(delim, cur);
			std::string	tok = str.substr(cur, fpos - cur);
			if (tok.size())
				ret.push_back(tok);
			if (fpos == std::string::npos)
				break ;
			cur = fpos + 1;
		}
		return (ret);
	}

	int	stoi(const std::string& str)
	{
		int					ret;
		std::istringstream	ss(str);

		ss >> ret;
		return (ret);
	}

	std::string	itos(const int& x)
	{
		std::stringstream	ss;
		ss << x;
		return (ss.str());
	}

	std::string	to_string(const int& x)
	{
		std::stringstream	ss;
		ss << std::setfill('0');
		ss << std::setw(3);
		ss << x;
		return (ss.str());
	}


	bool	isLetterC(const char c)
	{
		return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
	}

	bool	isLetterStr(const std::string& str)
	{
		std::string::const_iterator	it = str.begin();

		while (it != str.end())
		{
			if (!isLetterC(*it))
				return (false);
			++it;
		}
		return (true);
	}

	bool	isDigitC(const char c)
	{
		return ('0' <= c && c <= '9');
	}

	bool	isDigitStr(const std::string& str)
	{
		std::string::const_iterator	it = str.begin();

		while (it != str.end())
		{
			if (!isDigitC(*it))
				return (false);
			++it;
		}
		return (true);
	}

	bool	isUserC(const char c)
	{
		return (c != 0 && c != '\r' && c != '\n' && c != ' ' && c != '@');
	}

	bool	isUserStr(const std::string& str)
	{
		std::string::const_iterator it = str.begin();

		while (it != str.end())
		{
			if (!isUserC(*it))
				return (false);
			++it;
		}
		return (true);
	}

	bool	isHexDigitC(const char c)
	{
		return (isDigitC(c) || ('A' <= c && c <= 'F'));
	}

	bool	isHexDigitStr(const std::string& str)
	{
		std::string::const_iterator	it = str.begin();

		while (it != str.end())
		{
			if (!isHexDigitC(*it))
				return (false);
			++it;
		}
		return (true);
	}

	bool	isSpecialC(const char c)
	{
		return ((0x5b <= c && c <= 0x60) || (0x7b <= c && c <= 0x7d));
	}

	bool	isSpecialStr(const std::string& str)
	{
		std::string::const_iterator	it = str.begin();

		while (it != str.end())
		{
			if (!isSpecialC(*it))
				return (false);
			++it;
		}
		return (true);
	}

	bool	isNickStr(const std::string& str)
	{
		if (!isLetterC(str[0]))
			return (false);
		for (size_t i = 1; i < str.size(); ++i)
		{
			const char&	c = str[i];
			if (!isLetterC(c) && !isDigitC(c) && !isSpecialC(c))
				return (false);
		}
		return (true);
	}

	bool	isChPrefix(const char c)
	{
		return (c == '#' || c == '&' || c == '!' || c == '+');
	}

	// <any 8bit code except SPACE, BELL, NUL, CR, LF and comma (',')>
	bool	isChString(const char c)
	{
		if (c == 0x20 || c == 0x07 || c == 0x00 || c == 0x0D || c == 0x0A || c == 0x2C)
			return (false);
		return (true);
	}
}

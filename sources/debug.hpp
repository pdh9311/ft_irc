#include <string>

#define DBGV(err,res,str)	(irc::x_void(err, res, str, __FILE__, __LINE__))
#define DBG(err,res,str)	(irc::x_int(err, res, str, __FILE__, __LINE__))

#define DBG_OFS(offset,str)	(irc::x_line(str, __FILE__, __LINE__ - offset))

#define PE(str)				(irc::perror(str, __FILE__, __LINE__));

namespace irc
{
	int	x_int(int err, int res, std::string str, std::string file, int line);

	void*	x_void(void* err, void* res, std::string str, std::string file,
																	int line);

	void	x_line(std::string str, std::string file, int line);

	void	perror(std::string err, std::string file, int line);
}

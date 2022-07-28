#ifndef __CONNECTIONCLASSES_HPP__
# define __CONNECTIONCLASSES_HPP__

# include <iostream>
# include <string>

// Y:<Class>:<Ping Frequency>:<Connect freq>:<Max Links>:<SendQ>:<Local Limit>:<Global Limit>
/*
#   1 class number
#   2 ping frequency (in seconds)
#   3 unused for client classes
#   4 maximum number of links in this class (per I line)
#   5 sendQ for each client
#   6 maximum number of links from this [user@]host on the server
#   7 maximum number of links from this [user@]host on the net
*/
namespace irc
{
	class ConnectionClasses
	{
		private:
			int	_clazz;           // 0
			int _ping_frequency;
			int _connect_freq;
			int _max_links;
			int _sendQ;
			int _local_limit;
			int _global_Limit;

		public:
			const int get_class();
			const int get_ping_frequency();
			const int get_connect_freq();
			const int get_max_links();
			const int get_sendQ();
			const int get_local_limit();
			const int get_global_Limit();

			void set_class(int clazz);
			void set_ping_frequency(int ping_frequency);
			void set_connect_freq(int connect_freq);
			void set_max_links(int max_links);
			void set_sendQ(int sendQ);
			void set_local_limit(int local_limit);
			void set_global_Limit(int global_Limit);

			void set_member(
				int	clazz,
				int ping_frequency,
				int connect_freq,
				int max_links,
				int sendQ,
				int local_limit,
				int global_Limit
			);
			void print();
	};
}
#endif


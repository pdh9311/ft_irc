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
			int getClazz() const;
			int getPingFrequency() const;
			int getConnectFreq() const;
			int getMaxLinks() const;
			int getSendQ() const;
			int getLocalLimit() const;
			int getGlobalLimit() const;

			void setClazz(int clazz);
			void setPingFrequency(int ping_frequency);
			void setConnectFreq(int connect_freq);
			void setMaxLinks(int max_links);
			void setSendQ(int sendQ);
			void setLocalLimit(int local_limit);
			void setGlobalLimit(int global_Limit);

			void setMember(
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


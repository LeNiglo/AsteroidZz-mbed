#ifndef	_SERIALREADER_HPP_
# define _SERIALREADER_HPP_

# include "variables.h"
# include "includes.h"

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>

class SerialReader
{
public:
	SerialReader();
	SerialReader(const std::string&);
	SerialReader(const SerialReader&);
	~SerialReader();
	bool						init();
	void						poke();
	std::string					getLine();
	std::string					getSerial() const;
private:
	std::string					serial;
	boost::asio::io_service		io;
	boost::asio::serial_port	sp;
};

#endif /* _SERIALREADER_HPP_ */

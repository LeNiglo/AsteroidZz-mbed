#ifndef	_SERIALREADER_HPP_
# define _SERIALREADER_HPP_

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

# include "variables.h"
# include "includes.h"

class SerialReader
{
public:
	SerialReader();
	~SerialReader();
	bool						init();
	void						poke();
	std::string					getLine();
	std::string					getSerial() const;
private:
	std::string					serial;
	boost::asio::io_service		io;
	boost::asio::serial_port	*sp;
};

#endif /* _SERIALREADER_HPP_ */

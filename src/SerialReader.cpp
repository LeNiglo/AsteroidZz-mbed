#include "SerialReader.hpp"

SerialReader::SerialReader()
: io(), sp(io, SERIAL_PORT)
{
	this->serial = SERIAL_PORT;
}

SerialReader::SerialReader(const std::string &serial)
: io(), sp(io, serial)
{
	this->serial = serial;
}

SerialReader::SerialReader(const SerialReader &sr)
: io(), sp(io, sr.getSerial())
{
	this->serial = sr.getSerial();
}

SerialReader::~SerialReader()
{
	this->sp.close();
}

bool					SerialReader::init()
{
	this->sp.set_option(boost::asio::serial_port_base::baud_rate(SERIAL_BAUD));
	return true;
}

void					SerialReader::poke()
{
	boost::asio::write(this->sp, boost::asio::buffer("m", 1));
}

std::string				SerialReader::getLine()
{
	char c;
	std::string result = "";
	for(;;) {
		boost::asio::read(this->sp, boost::asio::buffer(&c, 1));
		switch(c) {
			case '\r':
				break;
			case '\n':
				return result;
			default:
				result += c;
		}
	}
}

std::string				SerialReader::getSerial() const
{
	return this->serial;
}

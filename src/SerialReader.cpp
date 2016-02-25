#include "SerialReader.hpp"

SerialReader::SerialReader()
: io()
{
	if (boost::filesystem::exists(SERIAL_PORT1)) {
		this->sp = new boost::asio::serial_port(io, SERIAL_PORT1);
		this->serial = SERIAL_PORT1;
	} else if (boost::filesystem::exists(SERIAL_PORT2)) {
		this->sp = new boost::asio::serial_port(io, SERIAL_PORT2);
		this->serial = SERIAL_PORT2;
	} else {
		std::cerr << "No MBED Joypad found on port " << SERIAL_PORT1 << " nor port " << SERIAL_PORT2 << "." << std::endl;
	}
}

SerialReader::~SerialReader()
{
	this->sp->close();
	delete this->sp;
}

bool					SerialReader::init()
{
	if (!sp->is_open()) {
		return false;
	}
	this->sp->set_option(boost::asio::serial_port_base::baud_rate(SERIAL_BAUD));
	return true;
}

void					SerialReader::poke()
{
	if (sp->is_open()) {
		boost::asio::write(*this->sp, boost::asio::buffer("m", 1));
	}
}

std::string				SerialReader::getLine()
{
	if (sp->is_open()) {
		char c;
		std::string result = "";
		for(;;) {
			boost::asio::read(*this->sp, boost::asio::buffer(&c, 1));
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
	return NULL;
}

/**
*	GETTERS
*/

std::string				SerialReader::getSerial() const
{
	return this->serial;
}

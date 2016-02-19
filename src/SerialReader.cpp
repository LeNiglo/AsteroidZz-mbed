#include "SerialReader.hpp"

SerialReader::SerialReader()
{
	this->serial = SERIAL_PORT;
}

SerialReader::SerialReader(const std::string &serial)
{
	this->serial = serial;
}

SerialReader::SerialReader(const SerialReader &sr)
{
	this->serial = sr.getSerial();
}

SerialReader::~SerialReader()
{

}

bool					SerialReader::init()
{
	return true;
}

std::string				SerialReader::getLine()
{
	return "";
}

std::string				SerialReader::getSerial() const
{
	return this->serial;
}

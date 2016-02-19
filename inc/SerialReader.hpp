#ifndef	_SERIALREADER_HPP_
# define _SERIALREADER_HPP_

# include "variables.h"
# include "includes.h"

class SerialReader
{
public:
	SerialReader();
	SerialReader(const std::string&);
	SerialReader(const SerialReader&);
	~SerialReader();
	bool					init();
	std::string				getLine();
	std::string				getSerial() const;
private:
	std::string			serial;
};

#endif /* _SERIALREADER_HPP_ */

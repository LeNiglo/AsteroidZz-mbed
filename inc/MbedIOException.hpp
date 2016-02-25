#ifndef _MBEDIOEXCEPTION_HPP_
# define _MBEDIOEXCEPTION_HPP_

#include <exception>

struct MbedIOException : std::exception {
	const char* what() const noexcept {
		return "No MBED Joypad found.";
	}
};

#endif /* _MBEDIOEXCEPTION_HPP_ */

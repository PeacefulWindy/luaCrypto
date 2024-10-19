#include"util.hpp"

const char* hexDigits = "0123456789abcdef";

std::string toHex(const unsigned char* digest, size_t length)
{
	auto result = std::string();
	result.reserve(length * 2);

	for (auto i = 0; i < length; ++i)
	{
		result.push_back(hexDigits[(digest[i] >> 4) & 0x0F]);
		result.push_back(hexDigits[digest[i] & 0x0F]);
	}

	return result;
}

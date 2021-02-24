//Just if you don't have

//ENABLE_PREMIUM_PRIVATE_SHOP
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
void split_argument(const char *argument, std::vector<std::string> & vecArgs)
{
	std::string arg = argument;
	boost::split(vecArgs, arg, boost::is_any_of(" "), boost::token_compress_on);
}

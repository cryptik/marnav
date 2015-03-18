#include "message_03.hpp"
#include <utils/unique.hpp>

namespace ais
{

message_03::message_03()
	: message_01(ID)
{
}

std::unique_ptr<message> message_03::parse(const raw& bits) throw(std::invalid_argument)
{
	if (bits.size() != 168)
		throw std::invalid_argument{"invalid number of bits in message_03::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_03>();
	message_03& msg = static_cast<message_03&>(*result);

	msg.read_data(bits);

	return result;
}

}

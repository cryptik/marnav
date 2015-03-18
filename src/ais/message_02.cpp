#include "message_02.hpp"
#include <utils/unique.hpp>

namespace ais
{

message_02::message_02()
	: message_01(ID)
{
}

std::unique_ptr<message> message_02::parse(const raw& bits) throw(std::invalid_argument)
{
	if (bits.size() != 168)
		throw std::invalid_argument{"invalid number of bits in message_02::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_02>();
	message_02& msg = static_cast<message_02&>(*result);

	msg.read_data(bits);

	return result;
}

}

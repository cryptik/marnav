#include "hdm.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * hdm::TAG;

hdm::hdm()
	: sentence(ID, TAG, talker_id::magnetic_compass)
{
}

void hdm::set_heading(double t) noexcept
{
	heading = t;
	heading_mag = reference::MAGNETIC;
}

std::unique_ptr<sentence> hdm::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in hdm::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<hdm>();
	result->set_talker(talker);
	hdm & detail = static_cast<hdm &>(*result);

	read(*(first + 0), detail.heading);
	read(*(first + 1), detail.heading_mag);

	return result;
}

std::vector<std::string> hdm::get_data() const
{
	return {to_string(heading), to_string(heading_mag)};
}
}
}

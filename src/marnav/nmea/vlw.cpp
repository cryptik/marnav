#include "vlw.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * vlw::TAG;

vlw::vlw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

void vlw::set_distance_cum_nm(double t) noexcept
{
	distance_cum = t;
	distance_cum_unit = unit::distance::nm;
}

void vlw::set_distance_reset_nm(double t) noexcept
{
	distance_reset = t;
	distance_reset_unit = unit::distance::nm;
}

std::unique_ptr<sentence> vlw::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in vlw::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<vlw>();
	result->set_talker(talker);
	vlw & detail = static_cast<vlw &>(*result);

	read(*(first + 0), detail.distance_cum);
	read(*(first + 1), detail.distance_cum_unit);
	read(*(first + 2), detail.distance_reset);
	read(*(first + 3), detail.distance_reset_unit);

	return result;
}

std::vector<std::string> vlw::get_data() const
{
	return {to_string(distance_cum), to_string(distance_cum_unit), to_string(distance_reset),
		to_string(distance_reset_unit)};
}
}
}

#include "vhw.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * vhw::TAG;

vhw::vhw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
	, degrees_true(reference::TRUE)
{
}

void vhw::set_heading(double t) noexcept
{
	heading = t;
	degrees_mag = reference::MAGNETIC;
}

void vhw::set_speed_knots(double t) noexcept
{
	speed_knots = t;
	speed_knots_unit = unit::velocity::knot;
}

void vhw::set_speed_kmh(double t) noexcept
{
	speed_kmh = t;
	speed_kmh_unit = unit::velocity::kmh;
}

std::unique_ptr<sentence> vhw::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in vhw::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<vhw>();
	result->set_talker(talker);
	vhw & detail = static_cast<vhw &>(*result);

	read(*(first + 0), detail.heading_empty);
	read(*(first + 1), detail.degrees_true);
	read(*(first + 2), detail.heading);
	read(*(first + 3), detail.degrees_mag);
	read(*(first + 4), detail.speed_knots);
	read(*(first + 5), detail.speed_knots_unit);
	read(*(first + 6), detail.speed_kmh);
	read(*(first + 7), detail.speed_kmh_unit);

	return result;
}

std::vector<std::string> vhw::get_data() const
{
	return {to_string(heading_empty), to_string(degrees_true), to_string(heading),
		to_string(degrees_mag), to_string(speed_knots), to_string(speed_knots_unit),
		to_string(speed_kmh), to_string(speed_kmh_unit)};
}
}
}

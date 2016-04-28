#include "bwr.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * bwr::TAG;

bwr::bwr()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

void bwr::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void bwr::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

void bwr::set_bearing_true(double t) noexcept
{
	bearing_true = t;
	bearing_true_ref = reference::TRUE;
}

void bwr::set_bearing_mag(double t) noexcept
{
	bearing_mag = t;
	bearing_mag_ref = reference::MAGNETIC;
}

void bwr::set_distance(double t) noexcept
{
	distance = t;
	distance_unit = unit::distance::nm;
}

void bwr::set_waypoint(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_id = id;
}

std::unique_ptr<sentence> bwr::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 12)
		throw std::invalid_argument{"invalid number of fields in bwr::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<bwr>();
	result->set_talker(talker);
	bwr & detail = static_cast<bwr &>(*result);

	read(*(first + 0), detail.time_utc);
	read(*(first + 1), detail.lat);
	read(*(first + 2), detail.lat_hem);
	read(*(first + 3), detail.lon);
	read(*(first + 4), detail.lon_hem);
	read(*(first + 5), detail.bearing_true);
	read(*(first + 6), detail.bearing_true_ref);
	read(*(first + 7), detail.bearing_mag);
	read(*(first + 8), detail.bearing_mag_ref);
	read(*(first + 9), detail.distance);
	read(*(first + 10), detail.distance_unit);
	read(*(first + 11), detail.waypoint_id);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	detail.lat = correct_hemisphere(detail.lat, detail.lat_hem);
	detail.lon = correct_hemisphere(detail.lon, detail.lon_hem);

	return result;
}

std::vector<std::string> bwr::get_data() const
{
	return {to_string(time_utc), to_string(lat), to_string(lat_hem), to_string(lon),
		to_string(lon_hem), to_string(bearing_true), to_string(bearing_true_ref),
		to_string(bearing_mag), to_string(bearing_mag_ref), to_string(distance),
		to_string(distance_unit), to_string(waypoint_id)};
}
}
}

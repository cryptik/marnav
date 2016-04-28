#ifndef __NMEA__TDS__HPP__
#define __NMEA__TDS__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief TDS - Trawl Door Spread Distance
///
/// @code
///        1   2
///        |   |
/// $--TDS,x.x,M*hh<CR><LF>
/// @endcode
///
/// Field Number
/// 1. Distance between trawl doors in meters (0..300)
/// 2. Units
///    - M = Meters
///
class tds : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::TDS;
	constexpr static const char * TAG = "TDS";

	tds();
	tds(const tds &) = default;
	tds & operator=(const tds &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, fields::const_iterator first, fields::const_iterator last);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	double distance;
	nmea::unit::distance distance_unit;

public:
	NMEA_GETTER(distance)
	NMEA_GETTER(distance_unit)

	void set_distance(double t) noexcept
	{
		distance = t;
		distance_unit = nmea::unit::distance::meter;
	}
};
}
}

#endif

#include "mtw.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * mtw::TAG;

mtw::mtw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

void mtw::set_temperature(double t) noexcept
{
	temperature = t;
	temperature_unit = unit::temperature::celsius;
}

std::unique_ptr<sentence> mtw::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in mtw::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<mtw>();
	result->set_talker(talker);
	mtw & detail = static_cast<mtw &>(*result);

	read(*(first + 0), detail.temperature);
	read(*(first + 1), detail.temperature_unit);

	return result;
}

std::vector<std::string> mtw::get_data() const
{
	return {to_string(temperature), to_string(temperature_unit)};
}
}
}

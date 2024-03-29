#include "Goal.hpp"
#include <sstream>
#include "Logger.hpp"
#include "Shape2DUtils.hpp"

namespace Model
{
/**
 *
 */
Goal::Goal()
{
}
/**
 *
 */
Goal::Goal(const std::string& aName) :
		WayPoint(aName)
{
}
/**
 *
 */
Goal::Goal(const std::string& aName, const Point& aPosition) :
		WayPoint(aName, aPosition)
{
}
/**
 *
 */
Goal::~Goal()
{
}
/**
 *
 */
std::string Goal::asString() const
{
	std::ostringstream os;

	os << "Goal " << getName() << " at (" << getPosition().x << ","
			<< getPosition().y << ")";

	return os.str();
}
/**
 *
 */
std::string Goal::asDebugString() const
{
	std::ostringstream os;

	os << "Goal:\n";
	os << WayPoint::asDebugString();

	return os.str();
}
/*
 *
 */
std::string Goal::asCopyString() const
{
	std::ostringstream os;

	os << getName() << " " << getPosition().x << " " << getPosition().y;

	return os.str();

}
} // namespace Model

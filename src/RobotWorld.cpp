#include "RobotWorld.hpp"
#include "Logger.hpp"
#include "Robot.hpp"
#include "WayPoint.hpp"
#include "Goal.hpp"
#include "Wall.hpp"
#include <algorithm>

#include "CommunicationService.hpp"
#include "Client.hpp"
#include "Message.hpp"
#include "MainApplication.hpp"

#include <boost/algorithm/string.hpp>

namespace Model {
/**
 *
 */
/* static */RobotWorld& RobotWorld::RobotWorld::getRobotWorld() {
	static RobotWorld robotWorld;
	return robotWorld;
}
/**
 *
 */
RobotPtr RobotWorld::newRobot(const std::string& aName /*= "New Robot"*/,
		const Point& aPosition /*= Point(-1,-1)*/,
		bool aNotifyObservers /*= true*/) {
	RobotPtr robot(new Model::Robot(aName, aPosition));
	robots.push_back(robot);
	if (aNotifyObservers == true) {
		notifyObservers();
	}
	return robot;
}
/**
 *
 */
WayPointPtr RobotWorld::newWayPoint(
		const std::string& aName /*= "new WayPoint"*/,
		const Point& aPosition /*= Point(-1,-1)*/,
		bool aNotifyObservers /*= true*/) {
	WayPointPtr wayPoint(new Model::WayPoint(aName, aPosition));
	wayPoints.push_back(wayPoint);
	if (aNotifyObservers == true) {
		notifyObservers();
	}
	return wayPoint;
}
/**
 *
 */
GoalPtr RobotWorld::newGoal(const std::string& aName /*= "New Goal"*/,
		const Point& aPosition /*= Point(-1,-1)*/,
		bool aNotifyObservers /*= true*/) {
	GoalPtr goal(new Model::Goal(aName, aPosition));
	goals.push_back(goal);
	if (aNotifyObservers == true) {
		notifyObservers();
	}
	return goal;
}
/**
 *
 */
WallPtr RobotWorld::newWall(const Point& aPoint1, const Point& aPoint2,
		bool aNotifyObservers /*= true*/) {
	WallPtr wall(new Model::Wall(aPoint1, aPoint2));
	walls.push_back(wall);
	if (aNotifyObservers == true) {
		notifyObservers();
	}
	return wall;
}
/**
 *
 */
void RobotWorld::deleteRobot(RobotPtr aRobot,
		bool aNotifyObservers /*= true*/) {
	auto i = std::find_if(robots.begin(), robots.end(), [aRobot](RobotPtr r)
	{
		return aRobot->getName() == r->getName();
	});
	if (i != robots.end()) {
		robots.erase(i);
		if (aNotifyObservers == true) {
			notifyObservers();
		}
	}
}
/**
 *
 */
void RobotWorld::deleteWayPoint(WayPointPtr aWayPoint,
		bool aNotifyObservers /*= true*/) {
	auto i = std::find_if(wayPoints.begin(), wayPoints.end(),
			[aWayPoint]( WayPointPtr w)
			{
				return aWayPoint->getName() == w->getName();
			});
	if (i != wayPoints.end()) {
		wayPoints.erase(i);
		if (aNotifyObservers == true) {
			notifyObservers();
		}
	}
}
/**
 *
 */
bool RobotWorld::isChanged() {
	return changed;
}
;

void RobotWorld::setChanged() {
	changed = true;
}
;
void RobotWorld::unsetChanged() {
	changed = false;
}
;

void RobotWorld::deleteGoal(GoalPtr aGoal, bool aNotifyObservers /*= true*/) {
	auto i = std::find_if(goals.begin(), goals.end(), [aGoal]( GoalPtr g)
	{
		return aGoal->getName() == g->getName();
	});
	if (i != goals.end()) {
		goals.erase(i);

		if (aNotifyObservers == true) {
			notifyObservers();
		}
	}
}
/**
 *
 */
void RobotWorld::deleteWall(WallPtr aWall, bool aNotifyObservers /*= true*/) {
	auto i = std::find_if(walls.begin(), walls.end(), [aWall]( WallPtr w)
	{
		return
		aWall->getPoint1() == w->getPoint1() &&
		aWall->getPoint2() == w->getPoint2();
	});
	if (i != walls.end()) {
		walls.erase(i);

		if (aNotifyObservers == true) {
			notifyObservers();
		}
	}
}
/**
 *
 */
RobotPtr RobotWorld::getRobot(const std::string& aName) const {
	for (RobotPtr robot : robots) {
		if (robot->getName() == aName) {
			return robot;
		}
	}
	return nullptr;
}
/**
 *
 */
RobotPtr RobotWorld::getRobot(const Base::ObjectId& anObjectId) const {
	for (RobotPtr robot : robots) {
		if (robot->getObjectId() == anObjectId) {
			return robot;
		}
	}
	return nullptr;
}
/**
 *
 */
WayPointPtr RobotWorld::getWayPoint(const std::string& aName) const {
	for (WayPointPtr wayPoint : wayPoints) {
		if (wayPoint->getName() == aName) {
			return wayPoint;
		}
	}
	return nullptr;
}
/**
 *
 */
WayPointPtr RobotWorld::getWayPoint(const Base::ObjectId& anObjectId) const {
	for (WayPointPtr wayPoint : wayPoints) {
		if (wayPoint->getObjectId() == anObjectId) {
			return wayPoint;
		}
	}
	return nullptr;
}
/**
 *
 */
GoalPtr RobotWorld::getGoal(const std::string& aName) const {
	for (GoalPtr goal : goals) {
		if (goal->getName() == aName) {
			return goal;
		}
	}
	return nullptr;
}
/**
 *
 */
GoalPtr RobotWorld::getGoal(const Base::ObjectId& anObjectId) const {
	for (GoalPtr goal : goals) {
		if (goal->getObjectId() == anObjectId) {
			return goal;
		}
	}
	return nullptr;
}
/**
 *
 */
WallPtr RobotWorld::getWall(const Base::ObjectId& anObjectId) const {
	for (WallPtr wall : walls) {
		if (wall->getObjectId() == anObjectId) {
			return wall;
		}
	}
	return nullptr;
}

/**
 *
 */
const std::vector<RobotPtr>& RobotWorld::getRobots() const {
	return robots;
}
/**
 *
 */
const std::vector<WayPointPtr>& RobotWorld::getWayPoints() const {
	return wayPoints;
}
/**
 *
 */
const std::vector<GoalPtr>& RobotWorld::getGoals() const {
	return goals;
}
/**
 *
 */
const std::vector<WallPtr>& RobotWorld::getWalls() const {
	return walls;
}
/**
 *
 */
void RobotWorld::populate(int aNumberOfWalls /*= 2*/) {
	if (Application::MainApplication::isArgGiven("-worldname")) {
		if (Application::MainApplication::getArg("-worldname").value == "ONE") {
			RobotWorld::getRobotWorld().newGoal(
					std::string(
							Application::MainApplication::getArg("-worldname").value),
					Point(450, 450), false);
			//			RobotWorld::getRobotWorld().newWayPoint("WayPoint", Point(350, 350),
			//					false);
			RobotWorld::getRobotWorld().newRobot(
					std::string(
							Application::MainApplication::getArg("-worldname").value),
					Point(100, 50), false);
			RobotWorld::getRobotWorld().getRobot(
					std::string(
							Application::MainApplication::getArg("-worldname").value))->setGoal(
					std::string(
							Application::MainApplication::getArg("-worldname").value));
			//			RobotWorld::getRobotWorld().getRobot("Robot")->setWayPoint(
			//					"WayPoint");
			static Point coordinates[] = { Point(10, 200), Point(150, 200),
					Point(250, 200), Point(500, 200) };
			for (int i = 0; i < 2 * aNumberOfWalls; i += 2) {
				//				RobotWorld::getRobotWorld().getRobot("Robot")->setWayPoint(
				//						"WayPoint");
				for (int i = 0; i < 2 * aNumberOfWalls; i += 2) {
					RobotWorld::getRobotWorld().newWall(coordinates[i],
							coordinates[i + 1], false);
				}
				notifyObservers();
				return;
			}
		}
		if (Application::MainApplication::getArg("-worldname").value == "TWO") {
			RobotWorld::getRobotWorld().newGoal(
					std::string(
							Application::MainApplication::getArg("-worldname").value),
					Point(450, 50), false);
			RobotWorld::getRobotWorld().newRobot(
					std::string(
							Application::MainApplication::getArg("-worldname").value),
					Point(50, 450), false);
			RobotWorld::getRobotWorld().getRobot(
					std::string(
							Application::MainApplication::getArg("-worldname").value))->setGoal(
					std::string(
							Application::MainApplication::getArg("-worldname").value));
			notifyObservers();
			return;
		}
	} else {
		RobotWorld::getRobotWorld().newGoal("Goal", Point(300, 450), false);
		//RobotWorld::getRobotWorld().newGoal( "Goal2", Point( 350, 350),false);

		//		RobotWorld::getRobotWorld().newWayPoint("WayPoint", Point(350, 350),
		//				false);

		RobotWorld::getRobotWorld().newRobot("Robot", Point(50, 50), false);
		//RobotWorld::getRobotWorld().newRobot( "Robot2", Point( 150, 150),false);

		RobotWorld::getRobotWorld().getRobot("Robot")->setGoal("Goal");
		//RobotWorld::getRobotWorld().getRobot( "Robot2")->setGoal("Goal2");

		//		RobotWorld::getRobotWorld().getRobot("Robot")->setWayPoint("WayPoint");

		static Point coordinates[] = { Point(100, 400), Point(350, 300), Point(
				300, 100), Point(350, 200) };

		for (int i = 0; i < 2 * aNumberOfWalls; i += 2) {
			RobotWorld::getRobotWorld().newWall(coordinates[i],
					coordinates[i + 1], false);
		}
		notifyObservers();
	}
}
/**
 *
 */
void RobotWorld::unpopulate(bool aNotifyObservers /*= true*/) {
	robots.clear();
	wayPoints.clear();
	goals.clear();
	walls.clear();

	if (aNotifyObservers) {
		notifyObservers();
	}
}
/**
 *
 */
void RobotWorld::unpopulate(const std::vector<Base::ObjectId>& aKeepObjects,
		bool aNotifyObservers /*= true*/) {
	if (robots.size() > 0) {
		robots.erase(
				std::remove_if(robots.begin(), robots.end(),
						[&aKeepObjects](RobotPtr aRobot)
						{
							return std::find( aKeepObjects.begin(),
									aKeepObjects.end(),
									aRobot->getObjectId()) == aKeepObjects.end();
						}), robots.end());
	}
	if (wayPoints.size() > 0) {
		wayPoints.erase(
				std::remove_if(wayPoints.begin(), wayPoints.end(),
						[&aKeepObjects](WayPointPtr aWayPoint)
						{
							return std::find( aKeepObjects.begin(),
									aKeepObjects.end(),
									aWayPoint->getObjectId()) == aKeepObjects.end();
						}), wayPoints.end());
	}
	if (goals.size() > 0) {
		goals.erase(
				std::remove_if(goals.begin(), goals.end(),
						[&aKeepObjects](GoalPtr aGoal)
						{
							return std::find( aKeepObjects.begin(),
									aKeepObjects.end(),
									aGoal->getObjectId()) == aKeepObjects.end();
						}), goals.end());
	}
	if (walls.size() > 0) {
		walls.erase(
				std::remove_if(walls.begin(), walls.end(),
						[&aKeepObjects](WallPtr aWall)
						{
							return std::find( aKeepObjects.begin(),
									aKeepObjects.end(),
									aWall->getObjectId()) == aKeepObjects.end();
						}), walls.end());
	}

	if (aNotifyObservers) {
		notifyObservers();
	}
}
/**
 *
 */
std::string RobotWorld::asString() const {
	return ModelObject::asString();
}
/*
 *
 */
std::string RobotWorld::asCopyString() const {
	std::ostringstream os;

	for (RobotPtr ptr : robots) {
		os << Robot << " " << ptr->asCopyString() << '\n';
	}
	for (WayPointPtr ptr : wayPoints) {
		os << WayPoint << " " << ptr->asCopyString() << '\n';
	}
	for (GoalPtr ptr : goals) {
		os << Goal << " " << ptr->asCopyString() << '\n';
	}
	for (WallPtr ptr : walls) {
		os << Wall << " " << ptr->asCopyString() << '\n';
	}

	return os.str();
}
/**
 *
 */
std::string RobotWorld::asDebugString() const {
	std::ostringstream os;

	os << asString() << '\n';

	for (RobotPtr ptr : robots) {
		os << ptr->asDebugString() << '\n';
	}
	for (WayPointPtr ptr : wayPoints) {
		os << ptr->asDebugString() << '\n';
	}
	for (GoalPtr ptr : goals) {
		os << ptr->asDebugString() << '\n';
	}
	for (WallPtr ptr : walls) {
		os << ptr->asDebugString() << '\n';
	}

	return os.str();
}
/**
 *
 */
RobotWorld::RobotWorld() :
		communicating(false), robotWorldPtr(this) {
}
/**
 *
 */
RobotWorld::~RobotWorld() {
// No notification while I am in the destruction mode!
	disableNotification();
	unpopulate();
}
/**
 *
 */
void Model::RobotWorld::startCommunicating() {
	if (!communicating) {
		communicating = true;

		std::string localPort = "12345";
		if (Application::MainApplication::isArgGiven("-local_port")) {
			localPort =
					Application::MainApplication::getArg("-local_port").value;
		}

		Messaging::CommunicationService::getCommunicationService().runRequestHandler(
				toPtr<RobotWorld>(), std::stoi(localPort));
		Application::Logger::log("Started listening for world");

	}
}

void Model::RobotWorld::stopCommunicating() {
	if (communicating) {
		communicating = false;

		std::string localPort = "12345";
		if (Application::MainApplication::isArgGiven("-local_port")) {
			localPort =
					Application::MainApplication::getArg("-local_port").value;
		}

		Messaging::Client c1ient("localhost", localPort, toPtr<RobotWorld>());
		Messaging::Message message(1, "stop");
		c1ient.dispatchMessage(message);
		Application::Logger::log("Stopped listening for world");
	}
}

void Model::RobotWorld::handleRequest(Messaging::Message& aMessage) {
	switch (aMessage.getMessageType()) {
	case CopyWorldRequest: {
		Application::Logger::log(
				__PRETTY_FUNCTION__ + std::string(": CopyWorlds ")
						+ aMessage.getBody());
		//Read string and create objects.
		std::string myString = aMessage.getBody();
		aMessage.setMessageType(CopyWorldResponse);
		aMessage.setBody(this->asCopyString());
		fillWorld(myString);
		break;
	}
	case CopyRobots: {
		Application::Logger::log(
				__PRETTY_FUNCTION__ + std::string(": CopyRobots ")
						+ aMessage.getBody());

		std::stringstream ss;
		ss << aMessage.getBody();

		std::string aName;
		unsigned long x;
		unsigned long y;
		unsigned long lx;
		unsigned long ly;

		ss >> aName >> x >> y >> lx >> ly;

		Model::RobotPtr robot =
				(Model::RobotWorld::getRobotWorld().getRobots())[1];
		if (robot) {
			robot->setPosition(Point(x, y), true);
			robot->setFront(BoundedVector(lx, ly), true);
		};
		break;
	}

	case SyncWorlds: {
		Application::Logger::log(
				__PRETTY_FUNCTION__ + std::string(": SyncWorlds ")
						+ aMessage.getBody());
		std::string myString = aMessage.getBody();
		syncWorld(myString);
		aMessage.setMessageType(SyncWorlds);
		aMessage.setBody(asCopyString());

		break;
	}
	case StartRequest: {
		Application::Logger::log(
				__PRETTY_FUNCTION__ + std::string(": StartRequest"));
		Model::RobotPtr robot =
				(Model::RobotWorld::getRobotWorld().getRobots())[0];
		if (robot && !robot->isActing()) {
			robot->startActing();
		} else {
			robot->getRobotThread().join();
			std::thread newRobotThread([this, robot]
			{	robot->startDriving();});
			robot->getRobotThread().swap(newRobotThread);
		}
		aMessage.setMessageType(StartResponse);
		if (robot->isDriving()) {
			aMessage.setBody("Started remote robot.");
		} else {
			aMessage.setBody("Unable to start remote robot.");
		}
		break;
	}
	default:
		break;
	}
}
/**
 *
 */
void Model::RobotWorld::handleResponse(const Messaging::Message& aMessage) {
	switch (aMessage.getMessageType()) {
	case CopyWorldResponse: {
		Application::Logger::log(
				__PRETTY_FUNCTION__ + std::string(": CopyWorlds ")
						+ aMessage.getBody());
		//Read string and create objects.
		std::string myString = aMessage.getBody();
		fillWorld(myString);
		break;
	}
	case SyncWorlds: {
		Application::Logger::log(
				__PRETTY_FUNCTION__ + std::string(": SyncWorlds")
						+ aMessage.getBody());
		std::string myString = aMessage.getBody();
		syncWorld(myString);
		break;
	}
	case StartResponse:
		Application::Logger::log(
				__PRETTY_FUNCTION__ + std::string(": started remote robot")
						+ aMessage.asString());
		break;
	default: {
		Application::Logger::log(
				__PRETTY_FUNCTION__ + std::string(": Unknown response type")
						+ aMessage.getBody());
		break;
	}
	}
}
/**
 *
 */
void Model::RobotWorld::fillWorld(std::string& messageBody) {
	Application::Logger::log(
			__PRETTY_FUNCTION__ + std::string(": InputWorld") + messageBody);
	std::vector < std::string > lines;
	boost::split(lines, messageBody, boost::is_any_of("\n"));

	for (std::string line : lines) {
		if (!line.empty()) {
			std::stringstream ss;
			std::string aNewName;
			unsigned long aNewX;
			unsigned long aNewY;
			unsigned long aNewSecondX;
			unsigned long aNewSecondY;

			switch (std::stoi(&line.at(0))) {
			case Robot:
				line.erase(line.begin());
				ss << line;
				ss >> aNewName >> aNewX >> aNewY;
				newRobot((aNewName), Point(aNewX, aNewY));
				break;
			case WayPoint:
				line.erase(line.begin());
				ss << line;
				ss >> aNewName >> aNewX >> aNewY;
				newWayPoint(aNewName, Point(aNewX, aNewY), false);
				break;
			case Goal:
				line.erase(line.begin());
				ss << line;
				ss >> aNewName >> aNewX >> aNewY;
				newGoal(aNewName, Point(aNewX, aNewY), false);
				break;
			case Wall:
				line.erase(line.begin());
				ss << line;
				ss >> aNewX >> aNewY >> aNewSecondX >> aNewSecondY;
				newWall(Point(aNewX, aNewY), Point(aNewSecondX, aNewSecondY),
						false);
				break;
			default:
				Application::Logger::log("Unknown object");
				Application::Logger::log(line);
				break;
			}
		}
	}
	Application::Logger::log("Copied world");
	notifyObservers();
}

void Model::RobotWorld::syncWorld(std::string& messageBody) {
	Application::Logger::log(
			__PRETTY_FUNCTION__ + std::string(": SyncWorld") + messageBody);
	std::vector < std::string > lines;
	boost::split(lines, messageBody, boost::is_any_of("\n"));

	unsigned long waypointID = 0;
	unsigned long goalID = 0;
	unsigned long wallID = 0;

	for (std::string line : lines) {
		if (!line.empty()) {
			std::stringstream ss;
			std::string aNewName;
			unsigned long aNewX;
			unsigned long aNewY;
			signed long aNewLookX;
			signed long aNewLookY;
			unsigned long aNewSecondX;
			unsigned long aNewSecondY;

			RobotPtr robot;

			switch (std::stoi(&line.at(0))) {
			case Robot:
				line.erase(line.begin());
				ss << line;
				ss >> aNewName >> aNewX >> aNewY;
				robot = getRobot(aNewName);
				if (robot) {
					Application::Logger::log(robot->asString());
					robot->setPosition(Point(aNewX, aNewY), true);
					robot->setFront(BoundedVector(aNewLookX, aNewLookY), true);
					robot->notifyObservers();
				}
				break;
			case WayPoint:
				line.erase(line.begin());
				ss << line;
				ss >> aNewName >> aNewX >> aNewY;
				//getWayPoints().at(waypointID)->setPosition(Point(aNewX, aNewY), false);
				getWayPoint(aNewName)->setPosition(Point(aNewX, aNewY), false);
				getWayPoint(aNewName)->notifyObservers();
				++waypointID;
				break;
			case Goal:
				/*
				 line.erase(line.begin());
				 ss << line;
				 ss >> aNewName >> aNewX >> aNewY;
				 getGoals().at(goalID)->setPosition(Point(aNewX, aNewY), false);
				 getGoals().at(goalID)->notifyObservers();
				 ++goalID;
				 break;
				 */
				line.erase(line.begin());
				ss << line;
				ss >> aNewName >> aNewX >> aNewY;
				getGoal(aNewName)->setPosition(Point(aNewX, aNewY), false);
				getGoal(aNewName)->notifyObservers();
				break;
			case Wall:

				line.erase(line.begin());
				ss << line;
				ss >> aNewX >> aNewY >> aNewSecondX >> aNewSecondY;
				if (getWalls().at(wallID)) {
					getWalls().at(wallID)->setPoint1(Point(aNewX, aNewY),
							false);
					getWalls().at(wallID)->setPoint2(
							Point(aNewSecondX, aNewSecondY), false);
					getWalls().at(wallID)->notifyObservers();
				}
				++wallID;
				/*
				 line.erase(line.begin());
				 ss << line;
				 ss >> aNewX >> aNewY >> aNewSecondX >> aNewSecondY;
				 newWall(Point(aNewX, aNewY), Point(aNewSecondX, aNewSecondY),
				 false);
				 */
				break;
			default:
				Application::Logger::log("Unknown object");
				Application::Logger::log(line);
				break;
			}
		}
	}
	notifyObservers();
}

} // namespace Model

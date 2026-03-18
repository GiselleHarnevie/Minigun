#pragma once
#include "Sdbm.h"
#include <cstdint>

//struct EventArg {};
//using EventId = unsigned int;
//
//struct Event {
//	const EventId id;
//	static const uint8_t MAX_ARGS = 8;
//	uint8_t nbArgs;
//	EventArg args[MAX_ARGS];
//	explicit Event(EventId _id) : id{ _id } {}
//};

namespace EventsId
{
	constexpr unsigned int playerDied{ ::make_sdbm_hash("PlayerDied") };
	constexpr unsigned int pickUp{ ::make_sdbm_hash("PickUp") };
	/*Event playerDead(make_sdbm_hash("PlayerDied"));
	Event playerPickUp{ make_sdbm_hash("PlayerPickUp") };*/
	
}

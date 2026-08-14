#pragma once
#include "../Engine/Observer/Sdbm.h"
#include <cstdint>

namespace EventsId
{
	constexpr unsigned int playerDied{ ::make_sdbm_hash("PlayerDied") };
	
	constexpr unsigned int scoreLayerOne{ ::make_sdbm_hash("ScoreLayerOne") };
	constexpr unsigned int scoreLayerTwo{ ::make_sdbm_hash("ScoreLayerTwo") };
	constexpr unsigned int scoreLayerThree{ ::make_sdbm_hash("ScoreLayerThree") };
	constexpr unsigned int scoreLayerFour{ ::make_sdbm_hash("ScoreLayerFour") };
	constexpr unsigned int scoreUpdate{ ::make_sdbm_hash("ScoreLayerFour") };

	constexpr unsigned int enemyKilled{ ::make_sdbm_hash("EnemyKilled") };
}

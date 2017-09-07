#pragma once

#include "tinyxml_VS\stdafx.h"
#include "BBImporter.h"
#include "xmlfi\XMLFileImporter.h"

// ELEMNETS
static const string	MG_LEVEL_ELEMENT = "level";
static const string	MG_LEVEL_MAP_ELEMENT = "level_map";
static const string MG_LEVEL_SPRITE_TYPES_ELEMENT = "level_sprite_types";
static const string MG_BOTS_LIST_ELEMENT = "bots_list";
static const string MG_BOT_ELEMENT = "bot";
static const string MG_SPAWNING_POOLS_ELEMENT = "spawning_pools";
static const string MG_SPAWNING_POOL_ELEMENT = "spawning_pool";

// ATTRIBUTES
static const string MG_LEVEL_NAME_ATT = "level_name";
static const string	MG_MAP_DIR_ATT = "map_dir";
static const string MG_MAP_FILE_ATT = "map_file";
static const string MG_SPRITE_TYPES_DIR_ATT = "sprite_types_dir";
static const string MG_SPRITE_TYPES_FILE_ATT = "sprite_types_file";
static const string MG_SPRITE_TYPE_ATT = "sprite_type";
static const string MG_BOT_TYPE_ATT = "type";
static const string MG_INIT_X_ATT = "init_x";
static const string MG_INIT_Y_ATT = "init_y";
static const string MG_INIT_VX_ATT = "init_vx";
static const string MG_INIT_VY_ATT = "init_vy";
static const string MG_INIT_BOT_STATE_ATT = "init_bot_state";
static const string MG_INIT_SPRITE_STATE_ATT = "init_sprite_state";
static const string MG_X_ATT = "x";
static const string MG_Y_ATT = "y";
static const string MG_INTERVAL_TIME_ATT = "interval_time";
static const string MG_INTERVAL_TYPE_ATT = "interval_type";
static const string MG_MAX_VELOCITY = "max_velocity";

// VALUES
static const string MG_DETERMINISTIC_VALUE = "deterministic";
static const string MG_RANDOM_INTERVAL_VALUE = "random_interval";
static const string MG_SCHEDULED_VALUE = "scheduled";
static const string MG_WALKING_VALUE = "WALKING";
static const string MG_RECYCLE_VALUE = "recycle";
static const string MG_RESPAWN_VALUE = "respawn";

class BBLevelImporter : public BBImporter
{
private:
	XMLFileImporter xmlReader;

public:
	bool load(wstring levelFileDir, wstring levelFile);
	bool unload();
};
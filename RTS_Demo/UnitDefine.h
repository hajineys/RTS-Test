#pragma once

enum class PlayerType
{
	NONE,
	PLAYER,
	ENEMY
};

enum class UnitType
{
	RANGER,
	SHARPSHOOTER,
	SECTOID,
	VIPER
};

enum class UnitState
{
	STANDBY,
	MOVE,
	ATTACKREADY,
	ATTACK,
	DEAD
};
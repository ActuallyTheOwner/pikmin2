#ifndef _DROUGHT_GAME_NAVIGOHERE_H_
#define _DROUGHT_GAME_NAVIGOHERE_H_

#include "Game/Navi.h"
#include "Game/NaviState.h"
#include "Drought/Pathfinder.h"

namespace Game {

/* setting this to true will have the navi still
 * attempt to route through water if it
 * has non-blue pikmin */
const bool cTryRouteWater = false;

bool AreAllPikisBlue(Game::Navi* navi);

struct NaviGoHereStateArg : public StateArg {
	inline NaviGoHereStateArg(Vector3f pos, Drought::Path* path)
	    : mPosition(pos)
	    , mPath(path)
	{
	}

	Vector3f mPosition;
	Drought::Path* mPath;
};

struct NaviGoHereState : public NaviState {
	inline NaviGoHereState()
	    : NaviState(NSID_GoHere)
	    , mMoveSpeed(150.0f)
	    , mFinishDistanceThreshold(15.0f)
	{
	}

	virtual void init(Navi*, StateArg*); // _08
	virtual void exec(Navi*);            // _0C
	virtual void cleanup(Navi*);         // _10
	virtual bool callable() { return true; }

	void navigateToWayPoint(Navi*);
	bool navigateToFinalPoint(Navi*);

	const f32 mMoveSpeed;
	const f32 mFinishDistanceThreshold;

	f32 mTimeoutTimer; // The time in seconds before the navi gives up on the path
	Vector3f mLastPosition;

	Vector3f mTargetPosition;
	Drought::PathNode* mActiveRouteNode;
	Drought::Path* mPath;
};

} // namespace Game

#endif
#include "Game/Navi.h"
#include "Game/NaviState.h"
#include "PSM/Navi.h"
#include "Drought/Game/NaviGoHere.h"
#include "Game/MoviePlayer.h"
#include "Game/MapMgr.h"
#include "Drought/Pathfinder.h"
#include "Game/CPlate.h"

namespace Game {

bool AreAllPikisBlue(Navi* navi)
{
	Iterator<Creature> iterator(navi->mCPlateMgr);
	CI_LOOP(iterator)
	{
		Piki* piki = static_cast<Piki*>(*iterator);
		if (piki->getKind() != Game::Blue) {
			return false;
		}
	}
	return true;
}

void NaviFSM::init(Navi* navi)
{
	mBackupStateID = NSID_NULL;
	create(NSID_StateCount);

	registerState(new NaviWalkState);
	registerState(new NaviFollowState);
	registerState(new NaviPunchState);
	registerState(new NaviChangeState);
	registerState(new NaviGatherState);
	registerState(new NaviThrowState);
	registerState(new NaviThrowWaitState);
	registerState(new NaviDopeState);
	registerState(new NaviNukuState);
	registerState(new NaviNukuAdjustState);
	registerState(new NaviContainerState);
	registerState(new NaviAbsorbState);
	registerState(new NaviFlickState);
	registerState(new NaviDamagedState);
	registerState(new NaviPressedState);
	registerState(new NaviFallMeckState);
	registerState(new NaviKokeDamageState);
	registerState(new NaviSaraiState);
	registerState(new NaviSaraiExitState);
	registerState(new NaviDeadState);
	registerState(new NaviStuckState);
	registerState(new NaviDemo_UfoState);
	registerState(new NaviDemo_HoleInState);
	registerState(new NaviPelletState);
	registerState(new NaviCarryBombState);
	registerState(new NaviClimbState);
	registerState(new NaviPathMoveState);
	// added state
	registerState(new NaviGoHereState);
}

void NaviGoHereState::init(Navi* navi, StateArg* arg)
{
	P2ASSERT(arg);
	NaviGoHereStateArg* goHereArg = static_cast<NaviGoHereStateArg*>(arg);

	navi->startMotion(IPikiAnims::WALK, IPikiAnims::WALK, nullptr, nullptr);

	mTargetPosition  = goHereArg->mPosition;
	mPath            = goHereArg->mPath;
	mActiveRouteNode = goHereArg->mPath->mRoot;

	mTimeoutTimer = 0.0f;
}

// usually inlined, plays the navi's voice line when swapped
inline void NaviState::playChangeVoice(Navi* navi)
{
	if (navi->mNaviIndex == NAVIID_Olimar) { // OLIMAR
		PSSystem::spSysIF->playSystemSe(PSSE_SY_CHANGE_ORIMA, 0);

	} else if (playData->isStoryFlag(STORY_DebtPaid)) { // PRESIDENT
		PSSystem::spSysIF->playSystemSe(PSSE_SY_CHANGE_SHACHO, 0);

	} else { // LOUIE
		PSSystem::spSysIF->playSystemSe(PSSE_SY_CHANGE_LUI, 0);
	}

	if (navi->mNaviIndex == NAVIID_Olimar) { // OLIMAR
		navi->mSoundObj->startSound(PSSE_PL_PIKON_ORIMA, 0);

	} else if (playData->isStoryFlag(STORY_DebtPaid)) { // PRESIDENT
		navi->mSoundObj->startSound(PSSE_PL_PIKON_SHACHO, 0);

	} else { // LOUIE
		navi->mSoundObj->startSound(PSSE_PL_PIKON_LUI, 0);
	}
}

void NaviGoHereState::exec(Navi* navi)
{

	bool isFrozen = gameSystem && gameSystem->mIsFrozen;
	if (isFrozen || !navi->isAlive()) {
		navi->mVelocity = 0.0f;
		return;
	}

	bool navSuccess = false;
	if (mActiveRouteNode) {
		navigateToWayPoint(navi);
	} else {
		navSuccess = navigateToFinalPoint(navi);
	}

	// If we haven't moved in a while, start incrementing the giveup timer
	f32 distanceBetweenLast = (navi->getPosition() - mLastPosition).qLength2D();
	if (distanceBetweenLast <= 0.3f) {
		mTimeoutTimer += sys->mDeltaTime;

		// We've been trying for a little while, idk if we can do this
		if (mTimeoutTimer >= 3.5f) {
			navi->mFsm->transit(navi, NSID_Change, nullptr);
			PSSystem::spSysIF->playSystemSe(PSSE_PL_ORIMA_DAMAGE, 0);
			return;
		}
	}

	mLastPosition = navi->getPosition();

	if (navi->mController1) {
		navi->mWhistle->update(navi->mVelocity, false);

		if (!gameSystem->paused_soft() && moviePlayer->mDemoState == 0 && navi->mController1->isButtonDown(JUTGamePad::PRESS_B)) {
			navSuccess = true;
		}

		// swaps captains
		if (!gameSystem->paused_soft() && moviePlayer->mDemoState == 0 && !gameSystem->isMultiplayerMode()
		    && navi->mController1->isButtonDown(JUTGamePad::PRESS_Y) && playData->isDemoFlag(DEMO_Unlock_Captain_Switch)) {

			Navi* currNavi = naviMgr->getAt(GET_OTHER_NAVI(navi));
			int currID     = currNavi->getStateID();

			if (currNavi->isAlive() && currID != NSID_Nuku && currID != NSID_NukuAdjust && currID != NSID_Punch) {
				gameSystem->mSection->pmTogglePlayer();

				playChangeVoice(currNavi);

				if (currNavi->mCurrentState->needYChangeMotion()) {
					currNavi->mFsm->transit(currNavi, NSID_Change, nullptr);
				}
			}
		}
	}

	if (navSuccess) {
		navi->GoHereSuccess();
		transit(navi, NSID_Walk, nullptr);
	}
}

// moves the navi to the nearest waypoint
void NaviGoHereState::navigateToWayPoint(Navi* navi)
{
	WayPoint* currentWaypoint = mapMgr->mRouteMgr->getWayPoint(mActiveRouteNode->mWpIdx);

	Vector3f direction = currentWaypoint->mPosition;
	f32 distanceToNext = Vector3f::getFlatDirectionFromTo(navi->getPosition(), direction);

	// if the navi is close enough to the waypoint, move to the next one
	if (distanceToNext >= currentWaypoint->mRadius) {
		navi->makeCStick(true);

		// Look at the waypoint
		const f32 interp = 0.1f;
		navi->mFaceDir += interp * angDist(JMAAtan2Radian(direction.x, direction.z), navi->mFaceDir);
		navi->mFaceDir = roundAng(navi->mFaceDir);

		navi->mTargetVelocity.x = direction.x * mMoveSpeed;
		navi->mTargetVelocity.z = direction.z * mMoveSpeed;
		return;
	}

	mActiveRouteNode = mActiveRouteNode->mNext;
	if (!mActiveRouteNode) {
		return;
	}

	WayPoint* nextWp = mapMgr->mRouteMgr->getWayPoint(mActiveRouteNode->mWpIdx);

	// if the next waypoint isn't closed, don't stop
	bool stopAtClosed = nextWp->isFlag(WPF_Closed);
	if (!stopAtClosed) {
		return;
	}

	// If the waypoint is in water, and we don't have all blue pikmin, stop
	bool stopAtWater = nextWp->isFlag(WPF_Water) && !AreAllPikisBlue(navi);
	if (!stopAtWater) {
		return;
	}

	// We're either at a closed waypoint or a water waypoint, so stop
	mTargetPosition  = currentWaypoint->getPosition();
	mActiveRouteNode = nullptr;

	navi->GoHereInterupted();
	if (stopAtWater) {
		navi->GoHereInteruptWater();
	} else {
		navi->GoHereInteruptBlocked();
	}
}

// moves the navi to its final target destination
bool NaviGoHereState::navigateToFinalPoint(Navi* navi)
{
	Vector3f direction = mTargetPosition;
	f32 distance       = Vector3f::getFlatDirectionFromTo(navi->getPosition(), direction);
	if (distance < mFinishDistanceThreshold) {
		return true;
	}

	navi->makeCStick(true);

	navi->mFaceDir += 0.2f * angDist(JMAAtan2Radian(direction.x, direction.z), navi->mFaceDir);
	navi->mFaceDir = roundAng(navi->mFaceDir);

	navi->mTargetVelocity.x = direction.x * mMoveSpeed;
	navi->mTargetVelocity.z = direction.z * mMoveSpeed;
	return false;
}

void NaviGoHereState::cleanup(Navi* navi)
{
	if (mPath) {
		delete mPath;
		mPath = nullptr;
	}

	if (mActiveRouteNode) {
		delete mActiveRouteNode;
		mActiveRouteNode = nullptr;
	}
}

void Navi::GoHereSuccess()
{
	// your code here
}

void Navi::GoHereInterupted() { }

void Navi::GoHereInteruptBlocked() { }

void Navi::GoHereInteruptWater() { }

} // namespace Game
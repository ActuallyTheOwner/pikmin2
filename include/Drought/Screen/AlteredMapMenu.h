#ifndef _DROUGHT_SCREEN_ALTEREDMAPMENU_H
#define _DROUGHT_SCREEN_ALTEREDMAPMENU_H

#include "og/newScreen/SMenu.h"
#include "Game/routeMgr.h"
#include "Drought/Pathfinder.h"

namespace Drought {

namespace Screen {

struct AlteredMapMenu : public og::newScreen::ObjSMenuMap {
	AlteredMapMenu(const char* name)
	    : og::newScreen::ObjSMenuMap(name)
	{
		mStartWPIndex = -1;
	}

	virtual void doDraw(Graphics& gfx);
	virtual bool doUpdate();
	virtual bool doStart(const ::Screen::StartSceneArg*);
	virtual void doCreate(JKRArchive*);
	virtual void commonUpdate();
	virtual bool doEnd(const ::Screen::EndSceneArg*);

	void PathfindUpdate();
	void OnPathfindDone();
	void RenderPath(Graphics& gfx);

	bool HasMapInputChanged();

	Vector3f GetPositionFromTex(f32 x, f32 y);
	Vector2f GetPositionOnTex(Vector3f& pos);

	static bool IsPathfindingAllowed(Game::Navi* navi);

	void setupTextureDraw(Graphics& gfx);

	void drawArrow(Graphics& gfx);
	void drawButton(Graphics& gfx);

	void initPathfinding(bool);
	int execPathfinding();

	enum PathfindState {
		PATHFIND_INACTIVE    = -1,
		PATHFIND_IN_PROGRESS = 0,
		PATHFIND_FINISHED    = 1,
		PATHFIND_GOHERE      = 2,
	};

	bool mCanStartPathfind;
	bool mHasNoPath;
	bool mPathfindSuccess;
	bool mAllPikisBlue;
	s16 mStartWPIndex;
	s16 mGoalWPIndex;
	int mStartPathFindCounter;
	PathfindState mPathfindState;
	u32 mWayPointCount;
	Path* mPath;

	ResTIMG* mAButtonTex;
	ResTIMG* mArrowTex;
	ResTIMG* mArrowRedTex;

	JUTTexture* mArrowPicture;
	JUTTexture* mArrowRedPicture;
	JUTTexture* mAButton;
};

} // namespace Screen

} // namespace Drought

#endif
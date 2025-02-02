#ifndef _DROUGHT_PATHFINDER_H_
#define _DROUGHT_PATHFINDER_H_

#include "Game/pathfinder.h"

namespace Drought {

struct PathNode {
	PathNode(s16);
	PathNode* mNext;

	s16 mWpIdx;

	~PathNode()
	{
		if (mNext) {
			delete mNext;
		}
	}
};

struct Path {
	Path();

	~Path()
	{
		if (mRoot) {
			delete mRoot;
		}
	}

	void prepend(PathNode* node);

	f32 getDistance();

	PathNode* mRoot;
};

namespace Pathfinder {

u32 search_fast(s16 start, s16 end, Path&, u8);

} // namespace Pathfinder

} // namespace Drought

#endif
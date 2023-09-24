#ifndef _GAME_PIKIMGR_H
#define _GAME_PIKIMGR_H

#include "types.h"

#include "Condition.h"
#include "CNode.h"
#include "MonoObjectMgr.h"

#include "Game/Piki.h"
#include "Game/PikiParms.h"

struct J3DModelData;
struct UpdateMgr;
struct JKRArchive;

namespace SysShape {
struct ModelMgr;
} // namespace SysShape

namespace Game {
struct PikiContainer;

struct PikiMgr : public MonoObjectMgr<Piki> {
	PikiMgr();

	// vtable 1
	virtual ~PikiMgr() { } // _08 (weak)
	// vtable 2
	virtual void doAnimation();                      // _64 (weak)
	virtual void doEntry();                          // _68 (weak)
	virtual Piki* birth();                           // _7C
	virtual void resetMgr();                         // _80 (weak)
	virtual void onAlloc();                          // _88
	virtual void doSimpleDraw(Viewport* vp);         // _8C (weak)
	virtual u32 getMatrixLoadType() { return 1; }    // _90 (weak)
	virtual char* getMgrName() { return "PikiMgr"; } // _94 (weak)
	virtual void loadResources() { }                 // _98 (weak)
	virtual void loadResources(int modelFlag);       // _9C

	void init();
	void setupPiki(Piki* piki);
	void load(int modelFlag);
	void loadBmd(int id, char* name);
	void createModelCallback(SysShape::Model* model);
	SysShape::Model* createModel(int id, int num);
	SysShape::Model* createLeafModel(int id, int num);
	void setMovieDraw(bool drawOn);
	void debugShapeDL(char* text);
	void setVsXlu(int p1, bool p2);
	void setupSoundViewerAndBas();
	int getColorTransportScale(int color);
	void allocStorePikmins();
	void clearStorePikmins();
	void saveStorePikmins(Condition<Piki>* cond);
	void getStorePikmin(int, int);
	void moveAllPikmins(Vector3f& pos, f32 radius, Condition<Piki>* cond);
	void forceEnterPikmins(u8 check);
	void killDayEndPikmins(PikiContainer& container);
	void killAllPikmins();
	void caveSaveFormationPikmins(bool doKill);
	void caveSaveAllPikmins(bool check1, bool check2);
	void saveFormationPikmins(PikiContainer& container);
	void saveAllPikmins(PikiContainer& container);

	static int mBirthMode;
	static bool throwPikiDebug;

	s32 mDopedPikis;               // _30
	s32* mStoredPikis;             // _34
	u8 mFlags[2];                  // _38
	J3DModelData* mBluPikiModel;   // _3C, blue
	J3DModelData* mRedPikiModel;   // _40, red
	J3DModelData* mYelPikiModel;   // _44, yellow
	J3DModelData* mPrpPikiModel;   // _48, purple
	J3DModelData* mWtePikiModel;   // _4C, white
	J3DModelData* mBlbPikiModel;   // _50, bulbmin
	J3DModelData* mCrtPikiModel;   // _54, carrot
	J3DModelData* mLeafModel;      // _58
	J3DModelData* mBudModel;       // _5C
	J3DModelData* mFlowerModel;    // _60
	J3DModelData* mRedBudModel;    // _64
	J3DModelData* mRedFlowerModel; // _68
	PikiParms* mParms;             // _6C
	SysShape::ModelMgr* mModelMgr; // _70
	UpdateMgr* mUpdateMgr;         // _74
	UpdateMgr* mUpdateMgr2;        // _78, unsure of type
	JKRArchive* mModelArchive;     // _7C
};

extern PikiMgr* pikiMgr;
} // namespace Game

#endif

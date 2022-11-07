#ifndef _OG_NEWSCREEN_FINALMSG_H
#define _OG_NEWSCREEN_FINALMSG_H

#include "Screen/Bases.h"
#include "JSystem/J2D/J2DPane.h"

namespace P2DScreen {
struct Mgr_tuning;
} // namespace P2DScreen

namespace og {
namespace Screen {
struct DispMemberFinalMessage;
struct MenuMgr;
struct AnimText_Screen;
} // namespace Screen

namespace newScreen {
struct FinalMsg : public ::Screen::SceneBase {
	FinalMsg();

	virtual const char* getResName() const { return "res_final_message.szs"; } // _1C (weak)
	virtual SceneType getSceneType() { return SCENE_FINAL_MSG; }               // _08 (weak)
	virtual ScreenOwnerID getOwnerID() { return OWNER_OGA; }                   // _0C (weak)
	virtual ScreenMemberID getMemberID() { return MEMBER_FINAL_MSG; }          // _10 (weak)
	virtual bool isUseBackupSceneInfo() { return true; }                       // _14 (weak)
	virtual void doCreateObj(JKRArchive*);                                     // _20
	virtual void doUserCallBackFunc(Resource::MgrCommand*);                    // _24
	virtual int doGetFinishState();                                            // _4C

	// _00      = VTBL
	// _00-_220 = Screen::SceneBase
};

struct ObjFinalMsg : public ::Screen::ObjBase {
	ObjFinalMsg(const char*);

	virtual ~ObjFinalMsg();                               // _08 (weak)
	virtual bool doStart(const ::Screen::StartSceneArg*); // _44
	virtual bool doEnd(const ::Screen::EndSceneArg*);     // _48
	virtual void doCreate(JKRArchive*);                   // _4C
	virtual bool doUpdateFadein();                        // _50
	virtual void doUpdateFadeinFinish();                  // _54
	virtual bool doUpdate();                              // _58
	virtual void doUpdateFinish();                        // _5C
	virtual bool doUpdateFadeout();                       // _60
	virtual void doUpdateFadeoutFinish();                 // _64
	virtual void doDraw(Graphics& gfx);                   // _68

	void blink_Menu(int);
	void menu();
	void wait();

	// _00     = VTBL1
	// _18     = VTBL2
	// _00-_38 = Screen::ObjBase
	og::Screen::DispMemberFinalMessage* m_finalMessage; // _38
	u8 _3C[0x4];                                        // _3C, unknown
	P2DScreen::Mgr_tuning* _40;                         // _40
	og::Screen::MenuMgr* m_menuMgr;                     // _44
	og::Screen::AnimText_Screen* _48;                   // _48
	og::Screen::AnimText_Screen* _4C;                   // _4C
	og::Screen::AnimText_Screen* _50;                   // _50
	f32 _54;                                            // _54
	f32 _58;                                            // _58
};
} // namespace newScreen
} // namespace og

#endif

#ifndef _JAINTER_OBJECTBASE_H
#define _JAINTER_OBJECTBASE_H

#include "JSystem/JKR/JKRDisposer.h"
#include "Vector3.h"
#include "types.h"

struct JAISound;

namespace JAInter {
struct ObjectBase : public JKRDisposer {
	virtual ~ObjectBase();                         // _08
	virtual void startSound(u32, u32);             // _0C
	virtual void startSound(u8, u32, u32);         // _10
	virtual void startSound(JAISound**, u32, u32); // _14
	virtual void stopAllSound();                   // _18
	virtual void stopSound(u32, u32);              // _1C
	virtual void enable();                         // _20 (weak)
	virtual void disable();                        // _24
	virtual void dispose();                        // _28
	virtual void getFreeSoundHandlePointer();      // _2C
	virtual void getUseSoundHandlePointer(u32);    // _30
	virtual void handleStop(u8, u32);              // _34

	void getUseSoundHandleNo(u32);

	u8 _18;
	u8 m_handleCount;
	JAISound** m_sounds;
	u32 _20;
	Vector3f* _24;
};
} // namespace JAInter

#endif

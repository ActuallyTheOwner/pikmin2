#include "types.h"
#include "JSystem/JKR/JKRArchive.h"
#include "FogMgr.h"
#include "Camera.h"
#include "Dolphin/gx.h"
#include "System.h"
#include "BaseParm.h"
#include "nans.h"

/*
    Generated from dpostproc

    .section .ctors, "wa"  # 0x80472F00 - 0x804732C0
        .4byte __sinit_ebiP2TitleFog_cpp

    .section .data, "wa"  # 0x8049E220 - 0x804EFC20
    .global lbl_804E9FA8
    lbl_804E9FA8:
        .4byte 0x00000000
        .4byte 0x00000000
        .4byte 0x00000000
        .4byte 0x00000000

    .section .sbss # 0x80514D80 - 0x80516360
    .global lbl_80516110
    lbl_80516110:
        .skip 0x4
    .global lbl_80516114
    lbl_80516114:
        .skip 0x4

    .section .sdata2, "a"     # 0x80516360 - 0x80520E40
    .global lbl_8051FE30
    lbl_8051FE30:
        .float 0.0
*/

namespace ebi {

namespace title {

struct TTitleFogMgr : public FogMgr {
    virtual ~TTitleFogMgr() { }     // _08 (weak)
    
	void setGX(Camera& camera);
    void loadSettingFile(JKRArchive* archive, char* file);

    Parameters m_parameters;
    Parm<bool> fg10;
    Parm<float> fg00;
    Parm<float> fg01;
    Parm<int> fg02;
    Parm<int> fg03;
    Parm<int> fg04;
    Parm<int> fg05;
};

/*
 * --INFO--
 * Address:	803EB1A4
 * Size:	000118
 */
// TODO: non-matching!
void TTitleFogMgr::setGX(Camera& camera)
{
	if (_4C) {
		struct {
			s8 _00;
			s8 _01;
			s8 _02;
			s8 _03;
		} v16Obj;

		v16Obj._03 = _B8;
		v16Obj._01 = _E0;
		v16Obj._02 = _108;
		v16Obj._00 = _130;

		GXSetFog(GX_FOG_LINEAR, (void*)&v16Obj, _68, _90, camera.getNear(), camera.getFar());

		GXFogAdjTable table;
		GXInitFogAdjTable(&table, System::getRenderModeObj()->fbWidth, camera._B4);
		GXSetFogRangeAdj(TRUE, System::getRenderModeObj()->fbWidth >> 1, &table);
	} else {
		GXSetFog(GX_FOG_NONE, _24, 0.0f, 0.0f, 0.0f, 0.0f);
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	000040
 */
void TTitleFogMgr::offGX(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	803EB2BC
 * Size:	00007C
 */
void TTitleFogMgr::loadSettingFile(JKRArchive* archive, char* file)
{
	void* a = archive->getResource(file);
	if (a != nullptr) {
		RamStream stream(a, -1);
		stream.m_mode = 1;
		if (stream.m_mode == 1) {
			stream.m_tabCount = 0;
		};
		m_parameters.read(stream);
	}
}

} // namespace title

} // namespace ebi

/*
 * --INFO--
 * Address:	803EB338
 * Size:	000028
 */
void __sinit_ebiP2TitleFog_cpp(void)
{
	/*
	lis      r4, __float_nan@ha
	li       r0, -1
	lfs      f0, __float_nan@l(r4)
	lis      r3, lbl_804E9FA8@ha
	stw      r0, lbl_80516110@sda21(r13)
	stfsu    f0, lbl_804E9FA8@l(r3)
	stfs     f0, lbl_80516114@sda21(r13)
	stfs     f0, 4(r3)
	stfs     f0, 8(r3)
	blr
	*/
}

#include "Dolphin/os.h"
#include "Dolphin/vi.h"
#include "JSystem/JGadget/linklist.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "types.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTVideo.h"
#include "JSystem/J2D/J2DGrafContext.h"
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "string.h"

JUTConsoleManager* JUTConsoleManager::sManager;
static JUTConsole* sReportConsole;
static JUTConsole* sWarningConsole;

/*
 * --INFO--
 * Address:	800280DC
 * Size:	000088
 */
JUTConsole* JUTConsole::create(uint param_0, uint param_1, JKRHeap* param_2)
{
	JUTConsoleManager* mgr = JUTConsoleManager::sManager;
	u32 byteCount          = getObjectSizeFromBufferSize(param_0, param_1);
	void* buf              = JKRHeap::alloc(byteCount, 0, param_2);
	u8* mem                = (u8*)buf;
	JUTConsole* console    = new (mem) JUTConsole(param_0, param_1, true);
	console->mBuf          = mem + sizeof(JUTConsole);
	console->clear();

	mgr->appendConsole(console);
	return console;
}

/*
 * --INFO--
 * Address:	80028164
 * Size:	000098
 */
JUTConsole* JUTConsole::create(uint param_0, void* param_1, u32 param_2)
{
	JUTConsoleManager* mgr = JUTConsoleManager::sManager;
	u32 byteCount          = getLineFromObjectSize(param_2, param_0);
	u8* mem                = (u8*)param_1;
	JUTConsole* console    = new (mem) JUTConsole(param_0, byteCount, false);
	console->mBuf          = mem + sizeof(JUTConsole);
	console->clear();

	mgr->appendConsole(console);
	return console;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00005C
 */
// void JUTConsole::destroy(JUTConsole*)
// {
// 	// UNUSED FUNCTION
// }

/*
 * --INFO--
 * Address:	800281FC
 * Size:	000100
 */
JUTConsole::JUTConsole(uint param_0, uint param_1, bool param_2)
{
	_2C       = param_2;
	_20       = param_0;
	mMaxLines = param_1;

	mPositionX = 30;
	mPositionY = 50;
	mHeight    = 20;

	if (mHeight > mMaxLines) {
		mHeight = mMaxLines;
	}

	mFont      = nullptr;
	mIsVisible = true;
	_69        = false;
	_6A        = false;
	_6B        = false;
	mOutput    = 1;

	_5C.set(0, 0, 0, 100);
	_60.set(0, 0, 0, 230);
	_64 = 8;
}

/*
 * --INFO--
 * Address:	800282FC
 * Size:	000070
 */
JUTConsole::~JUTConsole() { JUTConsoleManager::sManager->JUTConsoleManager::removeConsole(this); };

/*
 * --INFO--
 * Address:	8002836C
 * Size:	000010
 */
size_t JUTConsole::getObjectSizeFromBufferSize(uint b1, uint b2) { return (b1 + 2) * b2 + sizeof(JUTConsole); }

/*
 * --INFO--
 * Address:	8002837C
 * Size:	000010
 */
size_t JUTConsole::getLineFromObjectSize(u32 param_1, uint param_2) { return (param_1 - sizeof(JUTConsole)) / (param_2 + 2); }

/*
 * --INFO--
 * Address:	8002838C
 * Size:	00005C
 */
void JUTConsole::clear()
{
	_30 = 0;
	_34 = 0;
	_38 = 0;
	_3C = 0;

	for (int i = 0; i < (u32)mMaxLines; i++) {
		setLineAttr(i, 0);
	}
	mBuf[0] = 0xFF;
	mBuf[1] = 0;
}

/*
 * --INFO--
 * Address:	800283E8
 * Size:	00055C
 */
void JUTConsole::doDraw(JUTConsole::EConsoleType inputType) const
{
	f32 fontYOffset;
	s32 changeLine_1;
	s32 changeLine_2;

	if (mIsVisible && (mFont || (inputType == CONSOLETYPE_Unk2))) {
		if (mHeight != 0) {
			bool testVal = (inputType == CONSOLETYPE_Active);
			fontYOffset  = 2.0f + mFontSizeY;

			if (inputType != CONSOLETYPE_Unk2) {
				if (JUTVideo::getManager() == nullptr) {
					J2DOrthoGraph ortho(0.0f, 0.0f, 640.0f, 480.0f, -1.0f, 1.0f);
					ortho.setPort();

				} else {
					J2DOrthoGraph ortho(0.0f, 0.0f, (f32)JUTVideo::getManager()->getFbWidth(), (f32)JUTVideo::getManager()->getEfbHeight(),
					                    -1.0f, 1.0f);
					ortho.setPort();
				}
				const JUtility::TColor* TColorChoice;

				if (testVal) {
					TColorChoice = &this->_60;
				} else {
					TColorChoice = &this->_5C;
				}

				J2DFillBox((f32)(mPositionX - 2), (f32)(s32)((f32)mPositionY - fontYOffset), (f32)(s32)((mFontSizeX * (f32)_20) + 4.0f),
				           (f32)(s32)(fontYOffset * (f32)mHeight), (JUtility::TColor)*TColorChoice);

				mFont->setGX();
				if (testVal) {
					int colordiff = _38;
					int colorf30  = _30;

					s32 s = colorCheck(diffIndex(colorf30, colordiff), mHeight);
					if (s <= 0) {
						mFont->setCharColor(JUtility::TColor(0xFF, 0xFF, 0xFF, 0xFF));

					} else if (colorf30 == (s32)_34) {
						mFont->setCharColor(JUtility::TColor(0xFF, 0xE6, 0xE6, 0xFF));

					} else {
						mFont->setCharColor(JUtility::TColor(0xE6, 0xE6, 0xFF, 0xFF));
					}
				} else {
					mFont->setCharColor(JUtility::TColor(0xE6, 0xE6, 0xE6, 0xFF));
				}
			} else {
				JUTDirectPrint::sDirectPrint->erase(mPositionX - 3, mPositionY - 2, (_20 * 6) + 6, (s32)(fontYOffset * (f32)mHeight) + 4);
				JUTDirectPrint::sDirectPrint->setCharColor(JUtility::TColor(0xFF, 0xFF, 0xFF, 0xFF));
			}

			char* linePtr;
			s32 currLine = _30;
			s32 yFactor  = 0;

			do {
				linePtr = (char*)getLinePtr(currLine); // getLinePtr was fixed, it was adding to the array index not to the address
				if ((u8)linePtr[-1] != 0) {            // necessary explicit comparison

					if (inputType != 2) {
						f32 f1, f2, f3, f4;
						f2             = (((f32)yFactor * fontYOffset) + (f32)mPositionY);
						f4             = mFontSizeY;
						f1             = mPositionX;
						f3             = mFontSizeX;
						JUTFont* pFont = mFont;
						u32 lineLength = strlen((char*)linePtr);
						bool inputBool = true;

						pFont->drawString_size_scale(f1, f2, f3, f4, linePtr, lineLength, inputBool);

					} else {

						JUTDirectPrint::sDirectPrint->drawString((u16)mPositionX, (((f32)yFactor * fontYOffset) + (f32)mPositionY),
						                                         linePtr);
					}

					changeLine_1 = currLine + 1;
					yFactor += 1;
					changeLine_2 = changeLine_1 & ~(-((s32)mMaxLines <= (s32)changeLine_1));
					currLine     = changeLine_2;
				} else {
					break;
				}
			} while ((yFactor < mHeight) && (changeLine_2 != _34));
		}
	}
}

/*
 * --INFO--
 * Address:	800289A0
 * Size:	00008C
 */
extern "C" {
void JUTConsole_print_f_va_(JUTConsole* console, const char* fmt, va_list args);
}

void JUTConsole::print_f(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	JUTConsole_print_f_va_(this, format, args);
	va_end(args);
}

/*
 * --INFO--
 * Address:	80028A2C
 * Size:	000300
 */
void JUTConsole::print(const char* str)
{
	if (mOutput & 1) {
		const u8* r29 = (const u8*)str;
		u8* r28       = getLinePtr(_38) + _3C;
		while (*r29) {
			if (_6A && _34 == nextIndex(_38)) {
				break;
			}
			if (*r29 == '\n') {
				r29++;
				_3C = _20;
			} else if (*r29 == '\t') {
				r29++;
				while (_3C < _20) {
					*(r28++) = ' ';
					_3C++;
					if (_3C % _64 == 0) {
						break;
					}
				}
			} else if (mFont && mFont->isLeadByte(*r29)) {
				if (_3C + 1 < _20) {
					*(r28++) = *(r29++);
					*(r28++) = *(r29++);
					_3C++;
					_3C++;
				} else {
					*(r28++) = 0;
					_3C++;
				}
			} else {
				*(r28++) = *(r29++);
				_3C++;
			}

			if (_3C < _20) {
				continue;
			}
			*r28 = 0;
			_38  = nextIndex(_38);
			_3C  = 0;
			setLineAttr(_38, 0xff);
			r28          = getLinePtr(_38);
			*r28         = 0;
			int local_28 = diffIndex(_30, _38);
			if (local_28 == mHeight) {
				_30 = nextIndex(_30);
			}
			if (_38 == _34) {
				_34 = nextIndex(_34);
			}
			if (_38 == _30) {
				_30 = nextIndex(_30);
			}

			if (_6B) {
				break;
			}
		}
		*r28 = 0;
	}
}

/*
 * --INFO--
 * Address:	80028D2C
 * Size:	000048
 */
extern "C" void JUTConsole_print_f_va_(JUTConsole* console, const char* format, va_list args)
{
	char buffer[0x400];
	vsnprintf(buffer, sizeof(buffer), format, args);
	console->print(buffer);
}

/*
 * --INFO--
 * Address:	........
 * Size:	00012C
 */
void JUTConsole::dumpToTerminal(uint)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000154
 */
void JUTConsole::dumpToConsole(JUTConsole*, uint)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80028D74
 * Size:	0000DC
 */
void JUTConsole::scroll(int amount)
{
	if (amount < 0) {
		int var = _30 - _34;
		var     = _30 - _34 >= 0 ? var : var + mMaxLines;

		if (amount < -var) {
			amount = -var;
		}
	} else if (amount > 0) {
		int var2 = _38 - _34;
		var2     = var2 >= 0 ? var2 : var2 + mMaxLines;

		if (var2 + 1 <= mHeight) {
			amount = 0;
		} else {
			int var3 = _38 - _30;
			var3     = _38 - _30 >= 0 ? var3 : var3 + mMaxLines;

			if (amount > (s32)(var3 - mHeight + 1)) {
				amount = var3 - mHeight + 1;
			}
		}
	}

	_30 += amount;
	if (_30 < 0) {
		_30 += mMaxLines;
	}
	if (_30 >= (u32)mMaxLines) {
		_30 -= mMaxLines;
	}
}

/*
 * --INFO--
 * Address:	80028E50
 * Size:	000024
 */
int JUTConsole::getUsedLine() const
{
	int line = _38 - _34;
	if (line >= 0) {
		return line;
	}
	return line + mMaxLines;
}

/*
 * --INFO--
 * Address:	80028E74
 * Size:	000024
 */
int JUTConsole::getLineOffset() const
{
	int line = _30 - _34;
	if (line >= 0) {
		return line;
	}
	return line + mMaxLines;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000028
 */
JUTConsoleManager::JUTConsoleManager()
{
	mActiveConsole = nullptr;
	mDirectConsole = nullptr;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000054
 */
// void __dt__Q27JGadget27TLinkList<JUTConsole, -24> Fv()
// {
// 	// UNUSED FUNCTION
// }

/*
 * --INFO--
 * Address:	........
 * Size:	000058
 */
JUTConsoleManager::~JUTConsoleManager()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80028E98
 * Size:	000068
 */
JUTConsoleManager* JUTConsoleManager::createManager(JKRHeap* heap)
{
	if (heap == nullptr) {
		heap = JKRHeap::sCurrentHeap;
	}
	JUTConsoleManager* manager = new (heap, 0) JUTConsoleManager();
	sManager                   = manager;
	return manager;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000060
 */
void JUTConsoleManager::destroyManager(JUTConsoleManager*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80028F00
 * Size:	000070
 */
void JUTConsoleManager::appendConsole(JUTConsole* console)
{
	mLinkList.Push_back(console);

	if (mActiveConsole == nullptr) {
		mActiveConsole = console;
	}
	/*
	stwu     r1, -0x30(r1)
	mflr     r0
	stw      r0, 0x34(r1)
	addi     r5, r1, 0x14
	stw      r31, 0x2c(r1)
	mr       r31, r4
	addi     r6, r31, 0x18
	stw      r30, 0x28(r1)
	mr       r30, r3
	addi     r0, r30, 4
	addi     r3, r1, 0x10
	stw      r0, 0xc(r1)
	mr       r4, r30
	stw      r0, 8(r1)
	stw      r0, 0x1c(r1)
	stw      r0, 0x18(r1)
	stw      r0, 0x14(r1)
	bl
Insert__Q27JGadget13TNodeLinkListFQ37JGadget13TNodeLinkList8iteratorPQ27JGadget13TLinkListNode
	lwz      r0, 0xc(r30)
	cmplwi   r0, 0
	bne      lbl_80028F58
	stw      r31, 0xc(r30)

lbl_80028F58:
	lwz      r0, 0x34(r1)
	lwz      r31, 0x2c(r1)
	lwz      r30, 0x28(r1)
	mtlr     r0
	addi     r1, r1, 0x30
	blr
	*/
}

/*
 * --INFO--
 * Address:	80028F70
 * Size:	0000C8
 */
void JUTConsoleManager::removeConsole(JUTConsole* console)
{
	if (mActiveConsole == console) {
		if (mLinkList.size() <= 1) {
			mActiveConsole = nullptr;
		} else {
			mActiveConsole = console != &mLinkList.back() ? mLinkList.Element_toValue(console->mListNode.getNext()) : &mLinkList.front();
		}
	}

	if (JUTGetWarningConsole() == console)
		JUTSetWarningConsole(nullptr);
	if (JUTGetReportConsole() == console)
		JUTSetReportConsole(nullptr);

	mLinkList.Remove(console);
	/*
	stwu     r1, -0x20(r1)
	mflr     r0
	stw      r0, 0x24(r1)
	stw      r31, 0x1c(r1)
	mr       r31, r4
	stw      r30, 0x18(r1)
	mr       r30, r3
	lwz      r0, 0xc(r3)
	cmplw    r0, r31
	bne      lbl_80028FEC
	lwz      r0, 0(r30)
	cmplwi   r0, 1
	bgt      lbl_80028FB0
	li       r0, 0
	stw      r0, 0xc(r30)
	b        lbl_80028FEC

lbl_80028FB0:
	addi     r3, r30, 4
	lwz      r4, 8(r30)
	stw      r3, 0x14(r1)
	addi     r0, r4, -24
	cmplw    r31, r0
	stw      r3, 0x10(r1)
	beq      lbl_80028FD8
	lwz      r3, 0x18(r31)
	addi     r0, r3, -24
	b        lbl_80028FE8

lbl_80028FD8:
	lwz      r3, 4(r30)
	stw      r3, 0xc(r1)
	addi     r0, r3, -24
	stw      r3, 8(r1)

lbl_80028FE8:
	stw      r0, 0xc(r30)

lbl_80028FEC:
	bl       JUTGetWarningConsole
	cmplw    r3, r31
	bne      lbl_80029000
	li       r3, 0
	bl       JUTSetWarningConsole

lbl_80029000:
	bl       JUTGetReportConsole
	cmplw    r3, r31
	bne      lbl_80029014
	li       r3, 0
	bl       JUTSetReportConsole

lbl_80029014:
	mr       r3, r30
	addi     r4, r31, 0x18
	bl       Remove__Q27JGadget13TNodeLinkListFPQ27JGadget13TLinkListNode
	lwz      r0, 0x24(r1)
	lwz      r31, 0x1c(r1)
	lwz      r30, 0x18(r1)
	mtlr     r0
	addi     r1, r1, 0x20
	blr
	*/
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void JUTConsoleManager::getConsoleNumber() const
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80029038
 * Size:	0000CC
 */
void JUTConsoleManager::draw() const
{
	ConsoleList::const_iterator iter = mLinkList.begin();
	ConsoleList::const_iterator end  = mLinkList.end();

	for (; iter != end; ++iter) {
		const JUTConsole* const console = &(*iter);
		if (console != mActiveConsole)
			console->doDraw(JUTConsole::CONSOLETYPE_Inactive);
	}

	if (mActiveConsole != nullptr)
		mActiveConsole->doDraw(JUTConsole::CONSOLETYPE_Active);
	/*
	stwu     r1, -0x60(r1)
	mflr     r0
	stw      r0, 0x64(r1)
	lwz      r0, 4(r3)
	stw      r31, 0x5c(r1)
	lwz      r31, 0xc(r3)
	stw      r30, 0x58(r1)
	stw      r29, 0x54(r1)
	mr       r29, r3
	addi     r30, r29, 4
	stw      r30, 0xc(r1)
	stw      r0, 0x14(r1)
	stw      r0, 0x10(r1)
	stw      r0, 0x34(r1)
	stw      r0, 0x30(r1)
	stw      r0, 0x1c(r1)
	stw      r0, 0x44(r1)
	stw      r30, 8(r1)
	stw      r30, 0x2c(r1)
	stw      r30, 0x28(r1)
	stw      r30, 0x18(r1)
	stw      r30, 0x40(r1)
	stw      r30, 0x3c(r1)
	stw      r30, 0x24(r1)
	b        lbl_800290C0

lbl_8002909C:
	lwz      r3, 0x44(r1)
	addi     r3, r3, -24
	cmplw    r3, r31
	beq      lbl_800290B4
	li       r4, 1
	bl       doDraw__10JUTConsoleCFQ210JUTConsole12EConsoleType

lbl_800290B4:
	lwz      r3, 0x44(r1)
	lwz      r0, 0(r3)
	stw      r0, 0x44(r1)

lbl_800290C0:
	lwz      r0, 0x44(r1)
	cmplw    r0, r30
	stw      r0, 0x38(r1)
	stw      r0, 0x20(r1)
	bne      lbl_8002909C
	lwz      r3, 0xc(r29)
	cmplwi   r3, 0
	beq      lbl_800290E8
	li       r4, 0
	bl       doDraw__10JUTConsoleCFQ210JUTConsole12EConsoleType

lbl_800290E8:
	lwz      r0, 0x64(r1)
	lwz      r31, 0x5c(r1)
	lwz      r30, 0x58(r1)
	lwz      r29, 0x54(r1)
	mtlr     r0
	addi     r1, r1, 0x60
	blr
	*/
}

/*
 * --INFO--
 * Address:	80029104
 * Size:	00007C
 */
void JUTConsoleManager::drawDirect(bool doRetrace) const
{
	if (!mDirectConsole) {
		return;
	}
	if (doRetrace) {
		int interrupts = OSEnableInterrupts();
		u32 count      = VIGetRetraceCount();
		do {
		} while (count == VIGetRetraceCount());
		OSRestoreInterrupts(interrupts);
	}
	mDirectConsole->doDraw(JUTConsole::CONSOLETYPE_Unk2);
}

/*
 * --INFO--
 * Address:	80029180
 * Size:	000124
 */
void JUTConsoleManager::setDirectConsole(JUTConsole* console)
{
	if (mDirectConsole) {
		appendConsole(mDirectConsole);
	}

	if (console) {
		removeConsole(console);
	}
	mDirectConsole = console;
	/*
	stwu     r1, -0x40(r1)
	mflr     r0
	stw      r0, 0x44(r1)
	stw      r31, 0x3c(r1)
	stw      r30, 0x38(r1)
	mr       r30, r4
	stw      r29, 0x34(r1)
	mr       r29, r3
	lwz      r31, 0x10(r3)
	cmplwi   r31, 0
	beq      lbl_800291E8
	addi     r0, r29, 4
	mr       r4, r29
	stw      r0, 0xc(r1)
	addi     r3, r1, 0x20
	addi     r5, r1, 0x24
	addi     r6, r31, 0x18
	stw      r0, 8(r1)
	stw      r0, 0x2c(r1)
	stw      r0, 0x28(r1)
	stw      r0, 0x24(r1)
	bl
Insert__Q27JGadget13TNodeLinkListFQ37JGadget13TNodeLinkList8iteratorPQ27JGadget13TLinkListNode
	lwz      r0, 0xc(r29)
	cmplwi   r0, 0
	bne      lbl_800291E8
	stw      r31, 0xc(r29)

lbl_800291E8:
	cmplwi   r30, 0
	beq      lbl_80029284
	lwz      r0, 0xc(r29)
	cmplw    r0, r30
	bne      lbl_80029250
	lwz      r0, 0(r29)
	cmplwi   r0, 1
	bgt      lbl_80029214
	li       r0, 0
	stw      r0, 0xc(r29)
	b        lbl_80029250

lbl_80029214:
	addi     r3, r29, 4
	lwz      r4, 8(r29)
	stw      r3, 0x1c(r1)
	addi     r0, r4, -24
	cmplw    r30, r0
	stw      r3, 0x18(r1)
	beq      lbl_8002923C
	lwz      r3, 0x18(r30)
	addi     r0, r3, -24
	b        lbl_8002924C

lbl_8002923C:
	lwz      r3, 4(r29)
	stw      r3, 0x14(r1)
	addi     r0, r3, -24
	stw      r3, 0x10(r1)

lbl_8002924C:
	stw      r0, 0xc(r29)

lbl_80029250:
	bl       JUTGetWarningConsole
	cmplw    r3, r30
	bne      lbl_80029264
	li       r3, 0
	bl       JUTSetWarningConsole

lbl_80029264:
	bl       JUTGetReportConsole
	cmplw    r3, r30
	bne      lbl_80029278
	li       r3, 0
	bl       JUTSetReportConsole

lbl_80029278:
	mr       r3, r29
	addi     r4, r30, 0x18
	bl       Remove__Q27JGadget13TNodeLinkListFPQ27JGadget13TLinkListNode

lbl_80029284:
	stw      r30, 0x10(r29)
	lwz      r0, 0x44(r1)
	lwz      r31, 0x3c(r1)
	lwz      r30, 0x38(r1)
	lwz      r29, 0x34(r1)
	mtlr     r0
	addi     r1, r1, 0x40
	blr
	*/
}

/*
 * --INFO--
 * Address:	800292A4
 * Size:	000008
 */
void JUTSetReportConsole(JUTConsole* console) { sReportConsole = console; }

/*
 * --INFO--
 * Address:	800292AC
 * Size:	000008
 */
JUTConsole* JUTGetReportConsole() { return sReportConsole; }

/*
 * --INFO--
 * Address:	800292B4
 * Size:	000008
 */
void JUTSetWarningConsole(JUTConsole* console) { sWarningConsole = console; }

/*
 * --INFO--
 * Address:	800292BC
 * Size:	000008
 */
JUTConsole* JUTGetWarningConsole() { return sWarningConsole; }

/*
 * --INFO--
 * Address:	........
 * Size:	00006C
 */
void JUTReportConsole_f_va(const char* fmt, va_list args)
{
	char buf[256];

	if (JUTGetReportConsole() == nullptr) {
		vsnprintf(buf, sizeof(buf), fmt, args);

	} else if (JUTGetReportConsole()->isAnyOutput()) {
		vsnprintf(buf, sizeof(buf), fmt, args);
		JUTGetReportConsole()->print(buf);
	}
}

/*
 * --INFO--
 * Address:	800292C4
 * Size:	0000DC
 */
void JUTReportConsole_f(char const* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	JUTReportConsole_f_va(fmt, args);
	va_end(args);
}

/*
 * --INFO--
 * Address:	800293A0
 * Size:	00002C
 */
void JUTReportConsole(char const* str) { JUTReportConsole_f("%s", str); }

/**
 * --INFO--
 * Address:	800293CC
 * Size:	0000DC
 * @warning This does not actually use the warning console.
 */
void JUTWarningConsole_f(char const* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	JUTReportConsole_f_va(fmt, args);
	va_end(args);
}

/**
 * --INFO--
 * Address:	800294A8
 * Size:	00002C
 * @warning This does not actually use the warning console.
 */
void JUTWarningConsole(char const* str) { JUTReportConsole_f("%s", str); }

.include "macros.inc"
.section .ctors, "wa"  # 0x80472F00 - 0x804732C0
.4byte __sinit_JMATrigonometric_cpp

.section .sdata2, "a"     # 0x80516360 - 0x80520E40
.balign 0x8
.global lbl_80516738
lbl_80516738:
	.4byte 0x00000000
.global lbl_8051673C
lbl_8051673C:
	.4byte 0x3FC90FDB
.global lbl_80516740
lbl_80516740:
	.float 0.5
.global lbl_80516744
lbl_80516744:
	.4byte 0x44800000
.global lbl_80516748
lbl_80516748:
	.4byte 0xBFC90FDB
.global lbl_8051674C
lbl_8051674C:
	.4byte 0x40490FDB
.global lbl_80516750
lbl_80516750:
	.4byte 0xC0490FDB
	.4byte 0x00000000
.global lbl_80516758
lbl_80516758:
	.4byte 0x401921FB
	.4byte 0x60000000
.global lbl_80516760
lbl_80516760:
	.4byte 0x40A00000
	.4byte 0x00000000
.global lbl_80516768
lbl_80516768:
	.4byte 0x3F500000
	.4byte 0x00000000
.global lbl_80516770
lbl_80516770:
	.4byte 0x3F490FDB
	.4byte 0x00000000
.global lbl_80516778
lbl_80516778:
	.4byte 0x43300000
	.4byte 0x80000000

.section .text, "ax"  # 0x800056C0 - 0x80472F00
.global "atan2___Q25JMath18TAtanTable<1024,f>CFff"
"atan2___Q25JMath18TAtanTable<1024,f>CFff":
/* 80035108 00032048  C0 02 83 D8 */	lfs f0, lbl_80516738@sda21(r2)
/* 8003510C 0003204C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80035110 00032050  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80035114 00032054  4C 41 13 82 */	cror 2, 1, 2
/* 80035118 00032058  40 82 01 20 */	bne lbl_80035238
/* 8003511C 0003205C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80035120 00032060  4C 41 13 82 */	cror 2, 1, 2
/* 80035124 00032064  40 82 00 88 */	bne lbl_800351AC
/* 80035128 00032068  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8003512C 0003206C  4C 41 13 82 */	cror 2, 1, 2
/* 80035130 00032070  40 82 00 3C */	bne lbl_8003516C
/* 80035134 00032074  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 80035138 00032078  40 82 00 08 */	bne lbl_80035140
/* 8003513C 0003207C  48 00 02 18 */	b lbl_80035354
lbl_80035140:
/* 80035140 00032080  C0 02 83 E4 */	lfs f0, lbl_80516744@sda21(r2)
/* 80035144 00032084  C0 62 83 E0 */	lfs f3, lbl_80516740@sda21(r2)
/* 80035148 00032088  EC 00 00 72 */	fmuls f0, f0, f1
/* 8003514C 0003208C  EC 00 10 24 */	fdivs f0, f0, f2
/* 80035150 00032090  EC 03 00 2A */	fadds f0, f3, f0
/* 80035154 00032094  FC 00 00 1E */	fctiwz f0, f0
/* 80035158 00032098  D8 01 00 08 */	stfd f0, 8(r1)
/* 8003515C 0003209C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80035160 000320A0  54 00 10 3A */	slwi r0, r0, 2
/* 80035164 000320A4  7C 03 04 2E */	lfsx f0, r3, r0
/* 80035168 000320A8  48 00 01 EC */	b lbl_80035354
lbl_8003516C:
/* 8003516C 000320AC  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 80035170 000320B0  C0 82 83 DC */	lfs f4, lbl_8051673C@sda21(r2)
/* 80035174 000320B4  40 82 00 08 */	bne lbl_8003517C
/* 80035178 000320B8  48 00 00 2C */	b lbl_800351A4
lbl_8003517C:
/* 8003517C 000320BC  C0 02 83 E4 */	lfs f0, lbl_80516744@sda21(r2)
/* 80035180 000320C0  C0 62 83 E0 */	lfs f3, lbl_80516740@sda21(r2)
/* 80035184 000320C4  EC 00 00 B2 */	fmuls f0, f0, f2
/* 80035188 000320C8  EC 00 08 24 */	fdivs f0, f0, f1
/* 8003518C 000320CC  EC 03 00 2A */	fadds f0, f3, f0
/* 80035190 000320D0  FC 00 00 1E */	fctiwz f0, f0
/* 80035194 000320D4  D8 01 00 08 */	stfd f0, 8(r1)
/* 80035198 000320D8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8003519C 000320DC  54 00 10 3A */	slwi r0, r0, 2
/* 800351A0 000320E0  7C 03 04 2E */	lfsx f0, r3, r0
lbl_800351A4:
/* 800351A4 000320E4  EC 04 00 28 */	fsubs f0, f4, f0
/* 800351A8 000320E8  48 00 01 AC */	b lbl_80035354
lbl_800351AC:
/* 800351AC 000320EC  FC 80 10 50 */	fneg f4, f2
/* 800351B0 000320F0  FC 04 08 40 */	fcmpo cr0, f4, f1
/* 800351B4 000320F4  40 80 00 44 */	bge lbl_800351F8
/* 800351B8 000320F8  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800351BC 000320FC  C0 62 83 DC */	lfs f3, lbl_8051673C@sda21(r2)
/* 800351C0 00032100  40 82 00 08 */	bne lbl_800351C8
/* 800351C4 00032104  48 00 00 2C */	b lbl_800351F0
lbl_800351C8:
/* 800351C8 00032108  C0 02 83 E4 */	lfs f0, lbl_80516744@sda21(r2)
/* 800351CC 0003210C  C0 42 83 E0 */	lfs f2, lbl_80516740@sda21(r2)
/* 800351D0 00032110  EC 00 01 32 */	fmuls f0, f0, f4
/* 800351D4 00032114  EC 00 08 24 */	fdivs f0, f0, f1
/* 800351D8 00032118  EC 02 00 2A */	fadds f0, f2, f0
/* 800351DC 0003211C  FC 00 00 1E */	fctiwz f0, f0
/* 800351E0 00032120  D8 01 00 08 */	stfd f0, 8(r1)
/* 800351E4 00032124  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800351E8 00032128  54 00 10 3A */	slwi r0, r0, 2
/* 800351EC 0003212C  7C 03 04 2E */	lfsx f0, r3, r0
lbl_800351F0:
/* 800351F0 00032130  EC 03 00 2A */	fadds f0, f3, f0
/* 800351F4 00032134  48 00 01 60 */	b lbl_80035354
lbl_800351F8:
/* 800351F8 00032138  FC 00 20 00 */	fcmpu cr0, f0, f4
/* 800351FC 0003213C  C0 62 83 EC */	lfs f3, lbl_8051674C@sda21(r2)
/* 80035200 00032140  40 82 00 08 */	bne lbl_80035208
/* 80035204 00032144  48 00 00 2C */	b lbl_80035230
lbl_80035208:
/* 80035208 00032148  C0 02 83 E4 */	lfs f0, lbl_80516744@sda21(r2)
/* 8003520C 0003214C  C0 42 83 E0 */	lfs f2, lbl_80516740@sda21(r2)
/* 80035210 00032150  EC 00 00 72 */	fmuls f0, f0, f1
/* 80035214 00032154  EC 00 20 24 */	fdivs f0, f0, f4
/* 80035218 00032158  EC 02 00 2A */	fadds f0, f2, f0
/* 8003521C 0003215C  FC 00 00 1E */	fctiwz f0, f0
/* 80035220 00032160  D8 01 00 08 */	stfd f0, 8(r1)
/* 80035224 00032164  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80035228 00032168  54 00 10 3A */	slwi r0, r0, 2
/* 8003522C 0003216C  7C 03 04 2E */	lfsx f0, r3, r0
lbl_80035230:
/* 80035230 00032170  EC 03 00 28 */	fsubs f0, f3, f0
/* 80035234 00032174  48 00 01 20 */	b lbl_80035354
lbl_80035238:
/* 80035238 00032178  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8003523C 0003217C  FC 80 08 50 */	fneg f4, f1
/* 80035240 00032180  40 80 00 94 */	bge lbl_800352D4
/* 80035244 00032184  FC 60 10 50 */	fneg f3, f2
/* 80035248 00032188  FC 03 20 40 */	fcmpo cr0, f3, f4
/* 8003524C 0003218C  4C 41 13 82 */	cror 2, 1, 2
/* 80035250 00032190  40 82 00 44 */	bne lbl_80035294
/* 80035254 00032194  FC 00 18 00 */	fcmpu cr0, f0, f3
/* 80035258 00032198  C0 42 83 F0 */	lfs f2, lbl_80516750@sda21(r2)
/* 8003525C 0003219C  40 82 00 08 */	bne lbl_80035264
/* 80035260 000321A0  48 00 00 2C */	b lbl_8003528C
lbl_80035264:
/* 80035264 000321A4  C0 02 83 E4 */	lfs f0, lbl_80516744@sda21(r2)
/* 80035268 000321A8  C0 22 83 E0 */	lfs f1, lbl_80516740@sda21(r2)
/* 8003526C 000321AC  EC 00 01 32 */	fmuls f0, f0, f4
/* 80035270 000321B0  EC 00 18 24 */	fdivs f0, f0, f3
/* 80035274 000321B4  EC 01 00 2A */	fadds f0, f1, f0
/* 80035278 000321B8  FC 00 00 1E */	fctiwz f0, f0
/* 8003527C 000321BC  D8 01 00 08 */	stfd f0, 8(r1)
/* 80035280 000321C0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80035284 000321C4  54 00 10 3A */	slwi r0, r0, 2
/* 80035288 000321C8  7C 03 04 2E */	lfsx f0, r3, r0
lbl_8003528C:
/* 8003528C 000321CC  EC 02 00 2A */	fadds f0, f2, f0
/* 80035290 000321D0  48 00 00 C4 */	b lbl_80035354
lbl_80035294:
/* 80035294 000321D4  FC 00 20 00 */	fcmpu cr0, f0, f4
/* 80035298 000321D8  C0 42 83 E8 */	lfs f2, lbl_80516748@sda21(r2)
/* 8003529C 000321DC  40 82 00 08 */	bne lbl_800352A4
/* 800352A0 000321E0  48 00 00 2C */	b lbl_800352CC
lbl_800352A4:
/* 800352A4 000321E4  C0 02 83 E4 */	lfs f0, lbl_80516744@sda21(r2)
/* 800352A8 000321E8  C0 22 83 E0 */	lfs f1, lbl_80516740@sda21(r2)
/* 800352AC 000321EC  EC 00 00 F2 */	fmuls f0, f0, f3
/* 800352B0 000321F0  EC 00 20 24 */	fdivs f0, f0, f4
/* 800352B4 000321F4  EC 01 00 2A */	fadds f0, f1, f0
/* 800352B8 000321F8  FC 00 00 1E */	fctiwz f0, f0
/* 800352BC 000321FC  D8 01 00 08 */	stfd f0, 8(r1)
/* 800352C0 00032200  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800352C4 00032204  54 00 10 3A */	slwi r0, r0, 2
/* 800352C8 00032208  7C 03 04 2E */	lfsx f0, r3, r0
lbl_800352CC:
/* 800352CC 0003220C  EC 02 00 28 */	fsubs f0, f2, f0
/* 800352D0 00032210  48 00 00 84 */	b lbl_80035354
lbl_800352D4:
/* 800352D4 00032214  FC 02 20 40 */	fcmpo cr0, f2, f4
/* 800352D8 00032218  40 80 00 44 */	bge lbl_8003531C
/* 800352DC 0003221C  FC 00 20 00 */	fcmpu cr0, f0, f4
/* 800352E0 00032220  C0 62 83 E8 */	lfs f3, lbl_80516748@sda21(r2)
/* 800352E4 00032224  40 82 00 08 */	bne lbl_800352EC
/* 800352E8 00032228  48 00 00 2C */	b lbl_80035314
lbl_800352EC:
/* 800352EC 0003222C  C0 02 83 E4 */	lfs f0, lbl_80516744@sda21(r2)
/* 800352F0 00032230  C0 22 83 E0 */	lfs f1, lbl_80516740@sda21(r2)
/* 800352F4 00032234  EC 00 00 B2 */	fmuls f0, f0, f2
/* 800352F8 00032238  EC 00 20 24 */	fdivs f0, f0, f4
/* 800352FC 0003223C  EC 01 00 2A */	fadds f0, f1, f0
/* 80035300 00032240  FC 00 00 1E */	fctiwz f0, f0
/* 80035304 00032244  D8 01 00 08 */	stfd f0, 8(r1)
/* 80035308 00032248  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8003530C 0003224C  54 00 10 3A */	slwi r0, r0, 2
/* 80035310 00032250  7C 03 04 2E */	lfsx f0, r3, r0
lbl_80035314:
/* 80035314 00032254  EC 03 00 2A */	fadds f0, f3, f0
/* 80035318 00032258  48 00 00 3C */	b lbl_80035354
lbl_8003531C:
/* 8003531C 0003225C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 80035320 00032260  40 82 00 08 */	bne lbl_80035328
/* 80035324 00032264  48 00 00 2C */	b lbl_80035350
lbl_80035328:
/* 80035328 00032268  C0 02 83 E4 */	lfs f0, lbl_80516744@sda21(r2)
/* 8003532C 0003226C  C0 22 83 E0 */	lfs f1, lbl_80516740@sda21(r2)
/* 80035330 00032270  EC 00 01 32 */	fmuls f0, f0, f4
/* 80035334 00032274  EC 00 10 24 */	fdivs f0, f0, f2
/* 80035338 00032278  EC 01 00 2A */	fadds f0, f1, f0
/* 8003533C 0003227C  FC 00 00 1E */	fctiwz f0, f0
/* 80035340 00032280  D8 01 00 08 */	stfd f0, 8(r1)
/* 80035344 00032284  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80035348 00032288  54 00 10 3A */	slwi r0, r0, 2
/* 8003534C 0003228C  7C 03 04 2E */	lfsx f0, r3, r0
lbl_80035350:
/* 80035350 00032290  FC 00 00 50 */	fneg f0, f0
lbl_80035354:
/* 80035354 00032294  FC 20 00 90 */	fmr f1, f0
/* 80035358 00032298  38 21 00 10 */	addi r1, r1, 0x10
/* 8003535C 0003229C  4E 80 00 20 */	blr 

.global __sinit_JMATrigonometric_cpp
__sinit_JMATrigonometric_cpp:
/* 80035360 000322A0  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 80035364 000322A4  7C 08 02 A6 */	mflr r0
/* 80035368 000322A8  90 01 00 64 */	stw r0, 0x64(r1)
/* 8003536C 000322AC  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 80035370 000322B0  F3 E1 00 58 */	psq_st f31, 88(r1), 0, qr0
/* 80035374 000322B4  DB C1 00 40 */	stfd f30, 0x40(r1)
/* 80035378 000322B8  F3 C1 00 48 */	psq_st f30, 72(r1), 0, qr0
/* 8003537C 000322BC  DB A1 00 30 */	stfd f29, 0x30(r1)
/* 80035380 000322C0  F3 A1 00 38 */	psq_st f29, 56(r1), 0, qr0
/* 80035384 000322C4  DB 81 00 20 */	stfd f28, 0x20(r1)
/* 80035388 000322C8  F3 81 00 28 */	psq_st f28, 40(r1), 0, qr0
/* 8003538C 000322CC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80035390 000322D0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80035394 000322D4  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80035398 000322D8  3C 60 80 50 */	lis r3, sincosTable___5JMath@ha
/* 8003539C 000322DC  3C 80 80 03 */	lis r4, "__ct__Q23std9pair<f,f>Fv"@ha
/* 800353A0 000322E0  38 63 71 A0 */	addi r3, r3, sincosTable___5JMath@l
/* 800353A4 000322E4  38 A0 00 00 */	li r5, 0
/* 800353A8 000322E8  38 84 55 20 */	addi r4, r4, "__ct__Q23std9pair<f,f>Fv"@l
/* 800353AC 000322EC  38 C0 00 08 */	li r6, 8
/* 800353B0 000322F0  38 E0 08 00 */	li r7, 0x800
/* 800353B4 000322F4  48 08 C4 89 */	bl __construct_array
/* 800353B8 000322F8  3C 60 80 50 */	lis r3, sincosTable___5JMath@ha
/* 800353BC 000322FC  CB A2 84 18 */	lfd f29, lbl_80516778@sda21(r2)
/* 800353C0 00032300  CB E2 83 F8 */	lfd f31, lbl_80516758@sda21(r2)
/* 800353C4 00032304  3B A3 71 A0 */	addi r29, r3, sincosTable___5JMath@l
/* 800353C8 00032308  CB C2 84 00 */	lfd f30, lbl_80516760@sda21(r2)
/* 800353CC 0003230C  3B C0 00 00 */	li r30, 0
/* 800353D0 00032310  3F E0 43 30 */	lis r31, 0x4330
lbl_800353D4:
/* 800353D4 00032314  6F C0 80 00 */	xoris r0, r30, 0x8000
/* 800353D8 00032318  93 E1 00 08 */	stw r31, 8(r1)
/* 800353DC 0003231C  90 01 00 0C */	stw r0, 0xc(r1)
/* 800353E0 00032320  C8 01 00 08 */	lfd f0, 8(r1)
/* 800353E4 00032324  FC 00 E8 28 */	fsub f0, f0, f29
/* 800353E8 00032328  FC 00 07 F2 */	fmul f0, f0, f31
/* 800353EC 0003232C  FF 80 F0 24 */	fdiv f28, f0, f30
/* 800353F0 00032330  FC 20 E0 90 */	fmr f1, f28
/* 800353F4 00032334  48 09 A4 29 */	bl sin
/* 800353F8 00032338  FC 00 08 18 */	frsp f0, f1
/* 800353FC 0003233C  FC 20 E0 90 */	fmr f1, f28
/* 80035400 00032340  D0 1D 00 00 */	stfs f0, 0(r29)
/* 80035404 00032344  48 09 9E B1 */	bl cos
/* 80035408 00032348  FC 00 08 18 */	frsp f0, f1
/* 8003540C 0003234C  3B DE 00 01 */	addi r30, r30, 1
/* 80035410 00032350  2C 1E 08 00 */	cmpwi r30, 0x800
/* 80035414 00032354  D0 1D 00 04 */	stfs f0, 4(r29)
/* 80035418 00032358  3B BD 00 08 */	addi r29, r29, 8
/* 8003541C 0003235C  41 80 FF B8 */	blt lbl_800353D4
/* 80035420 00032360  3C 60 80 51 */	lis r3, atanTable___5JMath@ha
/* 80035424 00032364  CB E2 84 18 */	lfd f31, lbl_80516778@sda21(r2)
/* 80035428 00032368  CB C2 84 08 */	lfd f30, lbl_80516768@sda21(r2)
/* 8003542C 0003236C  3B A3 D1 E0 */	addi r29, r3, atanTable___5JMath@l
/* 80035430 00032370  3B C0 00 00 */	li r30, 0
/* 80035434 00032374  3F E0 43 30 */	lis r31, 0x4330
lbl_80035438:
/* 80035438 00032378  6F C0 80 00 */	xoris r0, r30, 0x8000
/* 8003543C 0003237C  93 E1 00 08 */	stw r31, 8(r1)
/* 80035440 00032380  90 01 00 0C */	stw r0, 0xc(r1)
/* 80035444 00032384  C8 01 00 08 */	lfd f0, 8(r1)
/* 80035448 00032388  FC 00 F8 28 */	fsub f0, f0, f31
/* 8003544C 0003238C  FC 20 07 B2 */	fmul f1, f0, f30
/* 80035450 00032390  48 09 9A E1 */	bl atan
/* 80035454 00032394  FC 00 08 18 */	frsp f0, f1
/* 80035458 00032398  3B DE 00 01 */	addi r30, r30, 1
/* 8003545C 0003239C  28 1E 04 00 */	cmplwi r30, 0x400
/* 80035460 000323A0  D0 1D 00 00 */	stfs f0, 0(r29)
/* 80035464 000323A4  3B BD 00 04 */	addi r29, r29, 4
/* 80035468 000323A8  41 80 FF D0 */	blt lbl_80035438
/* 8003546C 000323AC  3C 60 80 51 */	lis r3, atanTable___5JMath@ha
/* 80035470 000323B0  C0 22 83 D8 */	lfs f1, lbl_80516738@sda21(r2)
/* 80035474 000323B4  38 83 D1 E0 */	addi r4, r3, atanTable___5JMath@l
/* 80035478 000323B8  C0 02 84 10 */	lfs f0, lbl_80516770@sda21(r2)
/* 8003547C 000323BC  3C 60 80 51 */	lis r3, asinAcosTable___5JMath@ha
/* 80035480 000323C0  D0 24 00 00 */	stfs f1, 0(r4)
/* 80035484 000323C4  CB C2 84 18 */	lfd f30, lbl_80516778@sda21(r2)
/* 80035488 000323C8  3B A3 E2 00 */	addi r29, r3, asinAcosTable___5JMath@l
/* 8003548C 000323CC  D0 04 10 00 */	stfs f0, 0x1000(r4)
/* 80035490 000323D0  3B C0 00 00 */	li r30, 0
/* 80035494 000323D4  CB E2 84 08 */	lfd f31, lbl_80516768@sda21(r2)
/* 80035498 000323D8  3F E0 43 30 */	lis r31, 0x4330
lbl_8003549C:
/* 8003549C 000323DC  6F C0 80 00 */	xoris r0, r30, 0x8000
/* 800354A0 000323E0  93 E1 00 08 */	stw r31, 8(r1)
/* 800354A4 000323E4  90 01 00 0C */	stw r0, 0xc(r1)
/* 800354A8 000323E8  C8 01 00 08 */	lfd f0, 8(r1)
/* 800354AC 000323EC  FC 00 F0 28 */	fsub f0, f0, f30
/* 800354B0 000323F0  FC 20 07 F2 */	fmul f1, f0, f31
/* 800354B4 000323F4  48 09 A4 B9 */	bl asin
/* 800354B8 000323F8  FC 00 08 18 */	frsp f0, f1
/* 800354BC 000323FC  3B DE 00 01 */	addi r30, r30, 1
/* 800354C0 00032400  2C 1E 04 00 */	cmpwi r30, 0x400
/* 800354C4 00032404  D0 1D 00 00 */	stfs f0, 0(r29)
/* 800354C8 00032408  3B BD 00 04 */	addi r29, r29, 4
/* 800354CC 0003240C  41 80 FF D0 */	blt lbl_8003549C
/* 800354D0 00032410  C0 22 83 D8 */	lfs f1, lbl_80516738@sda21(r2)
/* 800354D4 00032414  3C 60 80 51 */	lis r3, asinAcosTable___5JMath@ha
/* 800354D8 00032418  C0 02 84 10 */	lfs f0, lbl_80516770@sda21(r2)
/* 800354DC 0003241C  D4 23 E2 00 */	stfsu f1, asinAcosTable___5JMath@l(r3)
/* 800354E0 00032420  D0 03 10 00 */	stfs f0, 0x1000(r3)
/* 800354E4 00032424  E3 E1 00 58 */	psq_l f31, 88(r1), 0, qr0
/* 800354E8 00032428  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 800354EC 0003242C  E3 C1 00 48 */	psq_l f30, 72(r1), 0, qr0
/* 800354F0 00032430  CB C1 00 40 */	lfd f30, 0x40(r1)
/* 800354F4 00032434  E3 A1 00 38 */	psq_l f29, 56(r1), 0, qr0
/* 800354F8 00032438  CB A1 00 30 */	lfd f29, 0x30(r1)
/* 800354FC 0003243C  E3 81 00 28 */	psq_l f28, 40(r1), 0, qr0
/* 80035500 00032440  CB 81 00 20 */	lfd f28, 0x20(r1)
/* 80035504 00032444  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80035508 00032448  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8003550C 0003244C  80 01 00 64 */	lwz r0, 0x64(r1)
/* 80035510 00032450  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80035514 00032454  7C 08 03 A6 */	mtlr r0
/* 80035518 00032458  38 21 00 60 */	addi r1, r1, 0x60
/* 8003551C 0003245C  4E 80 00 20 */	blr 

.global "__ct__Q23std9pair<f,f>Fv"
"__ct__Q23std9pair<f,f>Fv":
/* 80035520 00032460  C0 02 83 D8 */	lfs f0, lbl_80516738@sda21(r2)
/* 80035524 00032464  D0 03 00 00 */	stfs f0, 0(r3)
/* 80035528 00032468  D0 03 00 04 */	stfs f0, 4(r3)
/* 8003552C 0003246C  4E 80 00 20 */	blr 

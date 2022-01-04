.include "macros.inc"
.section .rodata  # 0x804732E0 - 0x8049E220
.balign 0x8
.global lbl_8047F048
lbl_8047F048:
	.4byte 0x75706461
	.4byte 0x74654D67
	.4byte 0x722E6370
	.4byte 0x70000000
.global lbl_8047F058
lbl_8047F058:
	.4byte 0x6D61696C
	.4byte 0x20746F20
	.4byte 0x5B25642D
	.4byte 0x25645D20
	.4byte 0x25640A00
	.4byte 0x00000000

.section .sbss # 0x80514D80 - 0x80516360
.balign 0x8
.global collisionUpdateMgr__4Game
collisionUpdateMgr__4Game:
	.skip 0x8

.section .text, "ax"  # 0x800056C0 - 0x80472F00

.global updatable__Q24Game9UpdateMgrFPQ24Game13UpdateContext
updatable__Q24Game9UpdateMgrFPQ24Game13UpdateContext:
/* 801967B8 001936F8  28 04 00 00 */	cmplwi r4, 0
/* 801967BC 001936FC  40 82 00 0C */	bne lbl_801967C8
/* 801967C0 00193700  38 60 00 00 */	li r3, 0
/* 801967C4 00193704  4E 80 00 20 */	blr 
lbl_801967C8:
/* 801967C8 00193708  80 84 00 04 */	lwz r4, 4(r4)
/* 801967CC 0019370C  80 03 00 10 */	lwz r0, 0x10(r3)
/* 801967D0 00193710  7C 04 00 50 */	subf r0, r4, r0
/* 801967D4 00193714  7C 00 00 34 */	cntlzw r0, r0
/* 801967D8 00193718  54 03 DE 3E */	rlwinm r3, r0, 0x1b, 0x18, 0x1f
/* 801967DC 0019371C  4E 80 00 20 */	blr 

.global create__Q24Game9UpdateMgrFi
create__Q24Game9UpdateMgrFi:
/* 801967E0 00193720  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 801967E4 00193724  7C 08 02 A6 */	mflr r0
/* 801967E8 00193728  2C 04 00 00 */	cmpwi r4, 0
/* 801967EC 0019372C  90 01 00 14 */	stw r0, 0x14(r1)
/* 801967F0 00193730  93 E1 00 0C */	stw r31, 0xc(r1)
/* 801967F4 00193734  93 C1 00 08 */	stw r30, 8(r1)
/* 801967F8 00193738  7C 7E 1B 78 */	mr r30, r3
/* 801967FC 0019373C  41 81 00 08 */	bgt lbl_80196804
/* 80196800 00193740  38 80 00 01 */	li r4, 1
lbl_80196804:
/* 80196804 00193744  54 9F 10 3A */	slwi r31, r4, 2
/* 80196808 00193748  90 9E 00 00 */	stw r4, 0(r30)
/* 8019680C 0019374C  7F E3 FB 78 */	mr r3, r31
/* 80196810 00193750  4B E8 D7 9D */	bl __nwa__FUl
/* 80196814 00193754  90 7E 00 08 */	stw r3, 8(r30)
/* 80196818 00193758  7F E3 FB 78 */	mr r3, r31
/* 8019681C 0019375C  4B E8 D7 91 */	bl __nwa__FUl
/* 80196820 00193760  90 7E 00 0C */	stw r3, 0xc(r30)
/* 80196824 00193764  38 80 00 00 */	li r4, 0
/* 80196828 00193768  7C 85 23 78 */	mr r5, r4
/* 8019682C 0019376C  38 C0 00 00 */	li r6, 0
/* 80196830 00193770  90 9E 00 04 */	stw r4, 4(r30)
/* 80196834 00193774  90 9E 00 10 */	stw r4, 0x10(r30)
/* 80196838 00193778  48 00 00 1C */	b lbl_80196854
lbl_8019683C:
/* 8019683C 0019377C  80 7E 00 08 */	lwz r3, 8(r30)
/* 80196840 00193780  38 C6 00 01 */	addi r6, r6, 1
/* 80196844 00193784  7C 83 29 2E */	stwx r4, r3, r5
/* 80196848 00193788  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 8019684C 0019378C  7C 83 29 2E */	stwx r4, r3, r5
/* 80196850 00193790  38 A5 00 04 */	addi r5, r5, 4
lbl_80196854:
/* 80196854 00193794  80 1E 00 00 */	lwz r0, 0(r30)
/* 80196858 00193798  7C 06 00 00 */	cmpw r6, r0
/* 8019685C 0019379C  41 80 FF E0 */	blt lbl_8019683C
/* 80196860 001937A0  38 00 00 00 */	li r0, 0
/* 80196864 001937A4  90 1E 00 14 */	stw r0, 0x14(r30)
/* 80196868 001937A8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8019686C 001937AC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80196870 001937B0  83 C1 00 08 */	lwz r30, 8(r1)
/* 80196874 001937B4  7C 08 03 A6 */	mtlr r0
/* 80196878 001937B8  38 21 00 10 */	addi r1, r1, 0x10
/* 8019687C 001937BC  4E 80 00 20 */	blr 

.global addClient__Q24Game9UpdateMgrFPQ24Game13UpdateContext
addClient__Q24Game9UpdateMgrFPQ24Game13UpdateContext:
/* 80196880 001937C0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80196884 001937C4  7C 08 02 A6 */	mflr r0
/* 80196888 001937C8  90 01 00 14 */	stw r0, 0x14(r1)
/* 8019688C 001937CC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80196890 001937D0  7C 7F 1B 78 */	mr r31, r3
/* 80196894 001937D4  93 C1 00 08 */	stw r30, 8(r1)
/* 80196898 001937D8  7C 9E 23 78 */	mr r30, r4
/* 8019689C 001937DC  80 04 00 04 */	lwz r0, 4(r4)
/* 801968A0 001937E0  2C 00 FF FF */	cmpwi r0, -1
/* 801968A4 001937E4  41 82 00 08 */	beq lbl_801968AC
/* 801968A8 001937E8  48 00 00 A9 */	bl removeClient__Q24Game9UpdateMgrFPQ24Game13UpdateContext
lbl_801968AC:
/* 801968AC 001937EC  80 1F 00 00 */	lwz r0, 0(r31)
/* 801968B0 001937F0  38 A0 FF FF */	li r5, -1
/* 801968B4 001937F4  38 C0 27 10 */	li r6, 0x2710
/* 801968B8 001937F8  38 E0 00 00 */	li r7, 0
/* 801968BC 001937FC  38 80 00 00 */	li r4, 0
/* 801968C0 00193800  7C 09 03 A6 */	mtctr r0
/* 801968C4 00193804  2C 00 00 00 */	cmpwi r0, 0
/* 801968C8 00193808  40 81 00 28 */	ble lbl_801968F0
lbl_801968CC:
/* 801968CC 0019380C  80 7F 00 08 */	lwz r3, 8(r31)
/* 801968D0 00193810  7C 03 20 2E */	lwzx r0, r3, r4
/* 801968D4 00193814  7C 00 30 00 */	cmpw r0, r6
/* 801968D8 00193818  40 80 00 0C */	bge lbl_801968E4
/* 801968DC 0019381C  7C E5 3B 78 */	mr r5, r7
/* 801968E0 00193820  7C 06 03 78 */	mr r6, r0
lbl_801968E4:
/* 801968E4 00193824  38 84 00 04 */	addi r4, r4, 4
/* 801968E8 00193828  38 E7 00 01 */	addi r7, r7, 1
/* 801968EC 0019382C  42 00 FF E0 */	bdnz lbl_801968CC
lbl_801968F0:
/* 801968F0 00193830  2C 05 FF FF */	cmpwi r5, -1
/* 801968F4 00193834  41 82 00 44 */	beq lbl_80196938
/* 801968F8 00193838  90 BE 00 04 */	stw r5, 4(r30)
/* 801968FC 0019383C  54 A5 10 3A */	slwi r5, r5, 2
/* 80196900 00193840  80 9F 00 08 */	lwz r4, 8(r31)
/* 80196904 00193844  7C 64 28 2E */	lwzx r3, r4, r5
/* 80196908 00193848  38 03 00 01 */	addi r0, r3, 1
/* 8019690C 0019384C  7C 04 29 2E */	stwx r0, r4, r5
/* 80196910 00193850  88 1E 00 08 */	lbz r0, 8(r30)
/* 80196914 00193854  28 00 00 00 */	cmplwi r0, 0
/* 80196918 00193858  41 82 00 14 */	beq lbl_8019692C
/* 8019691C 0019385C  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 80196920 00193860  7C 64 28 2E */	lwzx r3, r4, r5
/* 80196924 00193864  38 03 00 01 */	addi r0, r3, 1
/* 80196928 00193868  7C 04 29 2E */	stwx r0, r4, r5
lbl_8019692C:
/* 8019692C 0019386C  80 7F 00 04 */	lwz r3, 4(r31)
/* 80196930 00193870  38 03 00 01 */	addi r0, r3, 1
/* 80196934 00193874  90 1F 00 04 */	stw r0, 4(r31)
lbl_80196938:
/* 80196938 00193878  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8019693C 0019387C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80196940 00193880  83 C1 00 08 */	lwz r30, 8(r1)
/* 80196944 00193884  7C 08 03 A6 */	mtlr r0
/* 80196948 00193888  38 21 00 10 */	addi r1, r1, 0x10
/* 8019694C 0019388C  4E 80 00 20 */	blr 

.global removeClient__Q24Game9UpdateMgrFPQ24Game13UpdateContext
removeClient__Q24Game9UpdateMgrFPQ24Game13UpdateContext:
/* 80196950 00193890  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80196954 00193894  7C 08 02 A6 */	mflr r0
/* 80196958 00193898  90 01 00 14 */	stw r0, 0x14(r1)
/* 8019695C 0019389C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80196960 001938A0  7C 9F 23 78 */	mr r31, r4
/* 80196964 001938A4  93 C1 00 08 */	stw r30, 8(r1)
/* 80196968 001938A8  7C 7E 1B 78 */	mr r30, r3
/* 8019696C 001938AC  81 04 00 04 */	lwz r8, 4(r4)
/* 80196970 001938B0  2C 08 FF FF */	cmpwi r8, -1
/* 80196974 001938B4  41 82 00 8C */	beq lbl_80196A00
/* 80196978 001938B8  2C 08 00 00 */	cmpwi r8, 0
/* 8019697C 001938BC  41 80 00 10 */	blt lbl_8019698C
/* 80196980 001938C0  80 1E 00 00 */	lwz r0, 0(r30)
/* 80196984 001938C4  7C 08 00 00 */	cmpw r8, r0
/* 80196988 001938C8  41 80 00 28 */	blt lbl_801969B0
lbl_8019698C:
/* 8019698C 001938CC  3C 60 80 48 */	lis r3, lbl_8047F048@ha
/* 80196990 001938D0  3C 80 80 48 */	lis r4, lbl_8047F058@ha
/* 80196994 001938D4  38 A4 F0 58 */	addi r5, r4, lbl_8047F058@l
/* 80196998 001938D8  80 FE 00 00 */	lwz r7, 0(r30)
/* 8019699C 001938DC  38 63 F0 48 */	addi r3, r3, lbl_8047F048@l
/* 801969A0 001938E0  38 80 00 9B */	li r4, 0x9b
/* 801969A4 001938E4  38 C0 00 00 */	li r6, 0
/* 801969A8 001938E8  4C C6 31 82 */	crclr 6
/* 801969AC 001938EC  4B E9 3C 95 */	bl panic_f__12JUTExceptionFPCciPCce
lbl_801969B0:
/* 801969B0 001938F0  80 1F 00 04 */	lwz r0, 4(r31)
/* 801969B4 001938F4  80 BE 00 08 */	lwz r5, 8(r30)
/* 801969B8 001938F8  54 04 10 3A */	slwi r4, r0, 2
/* 801969BC 001938FC  7C 65 20 2E */	lwzx r3, r5, r4
/* 801969C0 00193900  38 03 FF FF */	addi r0, r3, -1
/* 801969C4 00193904  7C 05 21 2E */	stwx r0, r5, r4
/* 801969C8 00193908  88 1F 00 08 */	lbz r0, 8(r31)
/* 801969CC 0019390C  28 00 00 00 */	cmplwi r0, 0
/* 801969D0 00193910  41 82 00 1C */	beq lbl_801969EC
/* 801969D4 00193914  80 1F 00 04 */	lwz r0, 4(r31)
/* 801969D8 00193918  80 BE 00 0C */	lwz r5, 0xc(r30)
/* 801969DC 0019391C  54 04 10 3A */	slwi r4, r0, 2
/* 801969E0 00193920  7C 65 20 2E */	lwzx r3, r5, r4
/* 801969E4 00193924  38 03 FF FF */	addi r0, r3, -1
/* 801969E8 00193928  7C 05 21 2E */	stwx r0, r5, r4
lbl_801969EC:
/* 801969EC 0019392C  80 7E 00 04 */	lwz r3, 4(r30)
/* 801969F0 00193930  38 00 FF FF */	li r0, -1
/* 801969F4 00193934  38 63 FF FF */	addi r3, r3, -1
/* 801969F8 00193938  90 7E 00 04 */	stw r3, 4(r30)
/* 801969FC 0019393C  90 1F 00 04 */	stw r0, 4(r31)
lbl_80196A00:
/* 80196A00 00193940  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80196A04 00193944  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80196A08 00193948  83 C1 00 08 */	lwz r30, 8(r1)
/* 80196A0C 0019394C  7C 08 03 A6 */	mtlr r0
/* 80196A10 00193950  38 21 00 10 */	addi r1, r1, 0x10
/* 80196A14 00193954  4E 80 00 20 */	blr 

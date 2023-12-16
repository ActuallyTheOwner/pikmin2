#ifndef _GAME_ENTITIES_BIGTREASURE_H
#define _GAME_ENTITIES_BIGTREASURE_H

#include "Game/EnemyStateMachine.h"
#include "Game/EnemyAnimatorBase.h"
#include "Game/EnemyParmsBase.h"
#include "Game/EnemyMgrBase.h"
#include "Game/JointFuncs.h"
#include "Game/EnemyBase.h"
#include "efx/TOoota.h"
#include "efx/TDama.h"
#include "JSystem/J3D/J3DGXColor.h"
#include "Sys/MatBaseAnimation.h"
#include "Sys/MatBaseAnimator.h"
#include "Collinfo.h"

/**
 * --Header for Titan Dweevil (BigTreasure)--
 */

namespace Game {
struct IKSystemMgr;
struct IKSystemParms;

namespace BigTreasure {
struct BigTreasureGroundCallBack;
struct BigTreasureShadowMgr;
struct BigTreasureAttackMgr;
struct FSM;

struct EyeColor {
	inline void set(f32 _r, f32 _g, f32 _b)
	{
		mRgb[0] = _r;
		mRgb[1] = _g;
		mRgb[2] = _b;
	}

	inline EyeColor& operator=(const EyeColor& other)
	{
		mRgb[0] = other.mRgb[0];
		mRgb[1] = other.mRgb[1];
		mRgb[2] = other.mRgb[2];
		return *this;
	}

	inline void operator=(EyeColor& other)
	{
		mRgb[0] = other.mRgb[0];
		mRgb[1] = other.mRgb[1];
		mRgb[2] = other.mRgb[2];
	}

	f32 mRgb[3]; // _00, r=0, g=1, b=2
};

enum StateID {
	BIGTREASURE_NULL      = -1,
	BIGTREASURE_Dead      = 0,
	BIGTREASURE_Stay      = 1,
	BIGTREASURE_Land      = 2,
	BIGTREASURE_Wait      = 3,
	BIGTREASURE_ItemWait  = 4,
	BIGTREASURE_Flick     = 5,
	BIGTREASURE_PreAttack = 6,
	BIGTREASURE_Attack    = 7,
	BIGTREASURE_PutItem   = 8,
	BIGTREASURE_DropItem  = 9,
	BIGTREASURE_Walk      = 10,
	BIGTREASURE_ItemWalk  = 11,
	BIGTREASURE_Count,
};

enum AttackID {
	BIGATTACK_NULL  = -1,
	BIGATTACK_Elec  = 0,
	BIGATTACK_Fire  = 1,
	BIGATTACK_Gas   = 2,
	BIGATTACK_Water = 3,
	BIGATTACK_AttackCount, // 4
};

enum EyeColorTargetID {
	EYECOLOR_Dark  = 0,
	EYECOLOR_Light = 1,
};

struct Obj : public EnemyBase {
	Obj();

	//////////////// VTABLE
	virtual void onInit(CreatureInitArg* settings);                             // _30
	virtual void onKill(CreatureKillArg* settings);                             // _34
	virtual void doDirectDraw(Graphics& gfx);                                   // _50
	virtual void getShadowParam(ShadowParam& settings);                         // _134
	virtual ~Obj() { }                                                          // _1BC (weak)
	virtual void setInitialSetting(EnemyInitialParamBase* params);              // _1C4
	virtual void doUpdate();                                                    // _1CC
	virtual void doUpdateCommon();                                              // _1D0
	virtual void doAnimationUpdateAnimator();                                   // _1D8
	virtual void doAnimationCullingOff();                                       // _1DC
	virtual void doDebugDraw(Graphics& gfx);                                    // _1EC
	virtual void changeMaterial();                                              // _200
	virtual void getThrowupItemPosition(Vector3f* position);                    // _268
	virtual void getThrowupItemVelocity(Vector3f* velocity);                    // _26C
	virtual bool damageCallBack(Creature* source, f32 damage, CollPart* part);  // _278
	virtual bool hipdropCallBack(Creature* source, f32 damage, CollPart* part); // _284
	virtual void doStartStoneState();                                           // _2A4
	virtual void doFinishStoneState();                                          // _2A8
	virtual void doStartMovie();                                                // _2F0
	virtual void doEndMovie();                                                  // _2F4
	virtual void setFSM(FSM* fsm);                                              // _2F8
	virtual void inWaterCallback(WaterBox* wb) { }                              // _84 (weak)
	virtual void outWaterCallback() { }                                         // _88 (weak)
	virtual f32 getDamageCoeStoneState() { return 0.5f; }                       // _2AC (weak)
	virtual void throwupItemInDeathProcedure() { }                              // _270 (weak)
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID()                          // _258 (weak)
	{
		return EnemyTypeID::EnemyID_BigTreasure;
	}
	//////////////// VTABLE END

	void resetAttackLimitTimer();
	bool isAttackLimitTime();
	void getTargetPosition();
	void createIKSystem();
	void setupIKSystem();
	void setIKParameter();
	void setIKSystemTargetPosition(Vector3f& targetPos);
	void updateIKSystem();
	void doAnimationIKSystem();
	void finishAnimationIKSystem();
	void startProgramedIK();
	void startIKMotion();
	void finishIKMotion();
	void forceFinishIKMotion();
	bool isFinishIKMotion();
	void startBlendMotion();
	void finishBlendMotion();
	void checkJointScaleOn();
	Vector3f getTraceCentrePosition();
	Vector3f* getJointPositionPtr(int jointIndex, int positionIndex);
	void createShadowSystem();
	void setupShadowSystem();
	void doAnimationShadowSystem();
	void setupCollision();
	void setupTreasure();
	void updateTreasure();
	void dropTreasure();
	bool dropTreasure(int treasureIndex);
	bool isCapturedTreasure();
	bool isCapturedTreasure(int treasureIndex);
	int getCapturedTreasureNum();
	bool addTreasureDamage(int treasureIndex, f32 damage);
	void flickStickCollPartPikmin(CollPart* part);
	void releaseItemLoozy();
	void createAttack();
	void setupAttack();
	void updateAttack();
	void startAttack();
	void finishAttack();
	void setTreasureAttack();
	int getPreAttackAnimIndex();
	int getAttackAnimIndex();
	int getPutItemAnimIndex();
	int getFireAttackAnimIndex();
	f32 getPreAttackTimeMax();
	f32 getAttackTimeMax();
	bool isNormalAttack(int treasureIndex);
	void resetMaterialColor();
	void resetTargetMatBodyColor(bool isVisible);
	void resetCurrentMatBodyColor();
	void resetTargetEyeMatColor();
	void resetCurrentMatEyeColor();
	void setMatEyeAnimSpeed();
	void setAttackMaterialColor(bool isFast);
	void updateMaterialColor();
	void startBlendAnimation(int animIdx, bool blendAnimation);
	void endBlendAnimation();
	int getCurrAnimationIndex();
	void startBossChargeBGM();
	void startBossAttackBGM();
	void finishBossAttackBGM();
	void startBossFlickBGM();
	void startBossItemDropBGM();
	void updateBossBGM();
	void resetBossAppearBGM();
	void setBossAppearBGM();
	void createEffect();
	void setupEffect();
	void createOnGroundEffect(int footIdx, WaterBox* wb);
	void createOffGroundEffect(int footIdx, WaterBox* wb);
	void startTreasurePinchSmoke(int treasureIndex);
	void finishTreasurePinchSmoke(int treasureIndex);
	void createDropTreasureEffect(int treasureIndex);
	void createAppearBodyEffect();
	void createAppearLegEffect(int legIdx);
	void createDeadBombLegEffect(int legIdx);
	void createDeadBombBodyEffect();
	void startDeadBubbleLegEffect(int legIdx);
	void finishDeadBubbleLegEffect(int legIdx);
	void startDeadBubbleBodyEffect();
	void finishDeadBubbleBodyEffect();
	void startDeadBubbleMouthEffect();
	void finishDeadBubbleMouthEffect();
	void createChangeMaterialEffect();
	void createDeadBombFootEffect();
	void startShineParticleEffect();
	void finishShineParticleEffect();
	void effectDrawOn();
	void effectDrawOff();
	void subShadowScale();
	bool startBigTreasureBootUpDemo();

	void setupBigTreasureCollision();

	inline int getCurrentBodyRed() { return mCurrMatBodyColor.r; }

	inline int getTargetBodyRed() { return mTargetMatBodyColor.r; }

	inline int getCurrentBodyGreen() { return mCurrMatBodyColor.g; }

	inline int getTargetBodyGreen() { return mTargetMatBodyColor.g; }

	inline int getCurrentBodyBlue() { return mCurrMatBodyColor.b; }

	inline int getTargetBodyBlue() { return mTargetMatBodyColor.b; }

	inline int getCurrentBodyAlpha() { return mCurrMatBodyColor.a; }

	inline int getTargetBodyAlpha() { return mTargetMatBodyColor.a; }

	// _00 		= VTBL
	// _00-_2BC	= EnemyBase
	FSM* mFsm;                                  // _2BC
	f32 mStateTimer;                            // _2C0
	f32 mAttackLimitTimer;                      // _2C4
	StateID mNextState;                         // _2C8
	Vector3f mTargetPosition;                   // _2CC
	f32 mShadowScale;                           // _2D8
	bool mIsFastMatAnim;                        // _2DC
	bool mIsWeaponAttacked[0x4];                // _2DD, used to determine if the weapon should shake
	IKSystemMgr* mIkSystemMgr;                  // _2E4
	IKSystemParms* mIkSystemParms;              // _2E8
	BigTreasureGroundCallBack* mGroundCallBack; // _2EC
	BigTreasureShadowMgr* mShadowMgr;           // _2F0
	BigTreasureAttackMgr* mAttackMgr;           // _2F4
	Vector3f mKosiJointPos;                     // _2F8
	Vector3f mJointPositions[4][4];             // _304
	Pellet* mTreasures[4];                      // _3C4, elec / fire / gas / water
	Pellet* mLouie;                             // _3D4, King of Bugs
	f32 mTreasureHealth[4];                     // _3D8, elec / fire / gas / water
	f32 mTreasureShakeAngle[4];                 // _3E8, used to make treasures shake while being attacked
	CollPart* mTreasureCollParts[4];            // _3F8, elec / fire / gas / water
	int mAttackIndex;                           // _408, see AttackID enum
	J3DGXColorS10 mTargetMatBodyColor;          // _40C
	J3DGXColorS10 mCurrMatBodyColor;            // _414
	int mTargetEyeColorIdx;                     // _41C, 0 = going to dark, 1 = going to light (indexes _438, _45C)
	f32 mClusterEyeAnimSpeeds[3];               // _420, r=0, g=1, b=2
	f32 mSideEyeAnimSpeeds[3];                  // _42C, r=0, g=1, b=2
	EyeColor mTargetClusterEyeColor[2];         // _438, 0 = dark, 1 = light, bounces between
	EyeColor mCurrClusterEyeColor;              // _450
	EyeColor mTargetSideEyeColor[2];            // _45C, 0 = dark, 1 = light, bounces between
	EyeColor mCurrSideEyeColor;                 // _474
	efx::TOootaFoot* mFootFX[4];                // _480
	efx::TDamaFootw* mFootWFX[4];               // _490
	efx::TDamaSmoke* mTreasureSmokeFX[4];       // _4A0
	efx::TOootaStartBody* mStartBodyFX;         // _4B0
	efx::TOootaStartOta* mStartTreasureFX[4];   // _4B4
	efx::TOootaStartLeg* mStartLegFX[4][3];     // _4C4
	efx::TOootaDeadLeg* mDeadLegFX[4][4];       // _4F4, leg bubble effect on death
	efx::TOootaDeadBody* mDeadBodyFX;           // _534, body bubble effect on death
	efx::TOootaDeadAwa* mDeadAwaFX;             // _538, mouth bubble effect on death
	efx::TOootaChangeLeg* mChangeLegFX[4][4];   // _53C
	efx::TOootaChangeBody* mChangeBodyFX;       // _57C
	efx::TOootaParticle* mShineParticleFX;      // _580
	                                            // _584 = PelletView
};

struct Mgr : public EnemyMgrBase {
	Mgr(int objLimit, u8 modelType);

	//////////////// VTABLE
	// virtual ~Mgr();                                     // _58 (weak)
	virtual void createObj(int count);                 // _A0
	virtual EnemyBase* getEnemy(int idx);              // _A4
	virtual void doAlloc();                            // _A8
	virtual SysShape::Model* createModel();            // _B0
	virtual void loadModelData();                      // _C8
	virtual EnemyTypeID::EEnemyTypeID getEnemyTypeID() // _AC (weak)
	{
		return EnemyTypeID::EnemyID_BigTreasure;
	}
	virtual J3DModelData* doLoadBmd(void* filename) // _D4 (weak)
	{
		return J3DModelLoaderDataBase::load(filename, 0x01240030);
	}
	//////////////// VTABLE END

	// _00 		= VTBL
	// _00-_44	= EnemyMgrBase
	Obj* mObj; // _48
};

struct Parms : public EnemyParmsBase {
	struct ProperParms : public Parameters {
		ProperParms()
		    : Parameters(nullptr, "EnemyParmsBase")
		    , mBaseFactor(this, 'fp01', "�x�[�X�W��", 3.0f, 0.0f, 10.0f)                   // 'base factor'
		    , mRaiseDecelFactor(this, 'fp02', "�グ�����W��", -0.2f, -5.0f, 5.0f)          // 'raising deceleration factor'
		    , mDownwardDecelFactor(this, 'fp03', "���������W��", 0.5f, -5.0f, 5.0f)        // 'downward acceleration factor'
		    , mMinReducedAccelFactor(this, 'fp04', "�Œጸ�����W��", -2.0f, -10.0f, 10.0f) // 'min reduced acceleration factor'
		    , mMaxDecelAccelFactor(this, 'fp05', "�ō��������W��", 10.0f, -10.0f, 10.0f)   // 'max deceleration acceleration factor'
		    , mLegSwing(this, 'fp06', "���̐U��グ", 120.0f, 0.0f, 200.0f)                // 'leg swing'
		    , mElectricityWaitTime(this, 'fp10', "�\\������(�d�C)", 2.5f, 0.0f, 10.0f)     // 'wait time (electricity)'
		    , mFireWaitTime1(this, 'fp11', "�\\������(��:1)", 2.8f, 0.0f, 10.0f)           // 'wait time (fire:1)'
		    , mFireWaitTime2(this, 'fp31', "�\\������(��:2)", 2.5f, 0.0f, 10.0f)           // 'wait time (fire:2)'
		    , mGasWaitTime(this, 'fp12', "�\\������(�K�X)", 2.5f, 0.0f, 10.0f)             // 'wait time (gas)'
		    , mWaterWaitTime(this, 'fp13', "�\\������(��)", 2.5f, 0.0f, 10.0f)             // 'wait time (water)'
		    , mElecAttackTimeMax(this, 'fp20', "�U������(�d�C)", 5.0f, 0.0f, 10.0f)        // 'attack time (electricity)'
		    , mFireAttackTimeMax(this, 'fp21', "�U������(��)", 5.0f, 0.0f, 10.0f)          // 'attack time (fire)'
		    , mGasAttackTimeMax(this, 'fp22', "�U������(�K�X)", 5.0f, 0.0f, 10.0f)         // 'attack time (gas)'
		    , mWaterAttackTimeMax(this, 'fp23', "�U������(��)", 5.0f, 0.0f, 10.0f)         // 'attack time (water)'

		    , mBounceCoefficient1_1(this, 'fe00', "���ԌW��(1-1)", 0.75f, 0.0f, 1.0f)         // 'bounce coefficient (1-1)'
		    , mFrictionCoefficient1_1(this, 'fe01', "���C�W��(1-1)", 0.65f, 0.0f, 1.0f)       // 'friction coefficient (1-1)'
		    , mBaseMuzzleVelocityXZ1_1(this, 'fe02', "XZ����Base(1-1)", 100.0f, 0.0f, 500.0f) // 'XZ muzzle velocity Base (1-1)'
		    , mRandMuzzleVelocityXZ1_1(this, 'fe03', "XZ����Rand(1-1)", 220.0f, 0.0f, 500.0f) // 'XZ muzzle velocity Rand (1-1)'
		    , mBaseMuzzleVelocityY1_1(this, 'fe04', "Y����Base(1-1)", 170.0f, 0.0f, 500.0f)   // 'Y muzzle velocity Base (1-1)'
		    , mRandMuzzleVelocityY1_1(this, 'fe05', "Y����Rand(1-1)", 200.0f, 0.0f, 500.0f)   // 'Y muzzle velocity Rand (1-1)'
		    , mDischargeStart1_1(this, 'fe06', "���d�J�n(1-1)", 2.7f, 0.0f, 5.0f)             // 'discharge start (1-1)'
		    , mChainInterval1_1(this, 'fe08', "�A���Ԋu(1-1)", 0.02f, 0.0f, 1.0f)             // 'chain interval (1-1)'
		    , mDischargeCount1_1(this, 'fe07', "���d��(1-1)", 10, 0, 16)                      // 'number of discharges (1-1)'

		    , mBounceCoefficient1_2(this, 'fe10', "���ԌW��(1-2)", 0.7f, 0.0f, 1.0f)          // 'bounce coefficient (1-2)'
		    , mFrictionCoefficient1_2(this, 'fe11', "���C�W��(1-2)", 0.65f, 0.0f, 1.0f)       // 'friction coefficient (1-2)'
		    , mBaseMuzzleVelocityXZ1_2(this, 'fe12', "XZ����Base(1-2)", 80.0f, 0.0f, 500.0f)  // 'XZ muzzle velocity Base (1-2)'
		    , mRandMuzzleVelocityXZ1_2(this, 'fe13', "XZ����Rand(1-2)", 250.0f, 0.0f, 500.0f) // 'XZ muzzle velocity Rand (1-2)'
		    , mBaseMuzzleVelocityY1_2(this, 'fe14', "Y����Base(1-2)", 350.0f, 0.0f, 500.0f)   // 'Y muzzle velocity Base (1-2)'
		    , mRandMuzzleVelocityY1_2(this, 'fe15', "Y����Rand(1-2)", 100.0f, 0.0f, 500.0f)   // 'Y muzzle velocity Rand (1-2)'
		    , mDischargeStart1_2(this, 'fe16', "���d�J�n(1-2)", 4.5f, 0.0f, 5.0f)             // 'discharge start (1-2)'
		    , mChainInterval1_2(this, 'fe18', "�A���Ԋu(1-2)", 0.02f, 0.0f, 1.0f)             // 'chain interval (1-2)'
		    , mDischargeCount1_2(this, 'fe17', "���d��(1-2)", 12, 0, 16)                      // 'number of discharges (1-2)'

		    , mBounceCoefficient2_1(this, 'fe20', "���ԌW��(2-1)", 0.97f, 0.0f, 1.0f)        // 'bounce coefficient (2-1)'
		    , mFrictionCoefficient2_1(this, 'fe21', "���C�W��(2-1)", 0.75f, 0.0f, 1.0f)      // 'friction coefficient (2-1)'
		    , mBaseMuzzleVelocityXZ2_1(this, 'fe22', "XZ����Base(2-1)", 60.0f, 0.0f, 500.0f) // 'XZ muzzle velocity Base (2-1)'
		    , mRandMuzzleVelocityXZ2_1(this, 'fe23', "XZ����Rand(2-1)", 70.0f, 0.0f, 500.0f) // 'XZ muzzle velocity Rand (2-1)'
		    , mBaseMuzzleVelocityY2_1(this, 'fe24', "Y����Base(2-1)", 350.0f, 0.0f, 500.0f)  // 'Y muzzle velocity Base (2-1)'
		    , mRandMuzzleVelocityY2_1(this, 'fe25', "Y����Rand(2-1)", 100.0f, 0.0f, 500.0f)  // 'Y muzzle velocity Rand (2-1)'
		    , mDischargeStart2_1(this, 'fe26', "���d�J�n(2-1)", 0.5f, 0.0f, 5.0f)            // 'discharge start (2-1)'
		    , mChainInterval2_1(this, 'fe28', "�A���Ԋu(2-1)", 0.25f, 0.0f, 1.0f)            // 'chain interval (2-1)'
		    , mDischargeCount2_1(this, 'fe27', "���d��(2-1)", 8, 0, 16)                      // 'number of discharges (2-1)'

		    , mBounceCoefficient2_2(this, 'fe30', "���ԌW��(2-2)", 0.2f, 0.0f, 1.0f)          // 'bounce coefficient (2-2)'
		    , mFrictionCoefficient2_2(this, 'fe31', "���C�W��(2-2)", 0.985f, 0.0f, 1.0f)      // 'friction coefficient (2-2)'
		    , mBaseMuzzleVelocityXZ2_2(this, 'fe32', "XZ����Base(2-2)", 100.0f, 0.0f, 500.0f) // 'XZ muzzle velocity Base (2-2)'
		    , mRandMuzzleVelocityXZ2_2(this, 'fe33', "XZ����Rand(2-2)", 90.0f, 0.0f, 500.0f)  // 'XZ muzzle velocity Rand (2-2)'
		    , mBaseMuzzleVelocityY2_2(this, 'fe34', "Y����Base(2-2)", 70.0f, 0.0f, 500.0f)    // 'Y muzzle velocity Base (2-2)'
		    , mRandMuzzleVelocityY2_2(this, 'fe35', "Y����Rand(2-2)", 20.0f, 0.0f, 500.0f)    // 'Y muzzle velocity Rand (2-2)'
		    , mDischargeStart2_2(this, 'fe36', "���d�J�n(2-2)", 0.2f, 0.0f, 5.0f)             // 'discharge start (2-2)'
		    , mChainInterval2_2(this, 'fe38', "�A���Ԋu(2-2)", 0.15f, 0.0f, 1.0f)             // 'chain interval (2-2)'
		    , mDischargeCount2_2(this, 'fe37', "���d��(2-2)", 14, 0, 16)                      // 'number of discharges (2-2)'

		    , mPatternCheckFlame(this, 'fe99', "�p�^�[���`�F�b�N", 0, 0, 4)    // 'pattern check'
		    , mFlameScale1(this, 'ff00', "�Ή��X�P�[��(1)", 1.0f, 0.5f, 5.0f)  // 'flame scale (1)'
		    , mFlameScale2(this, 'ff10', "�Ή��X�P�[��(2)", 1.25f, 0.5f, 5.0f) // 'flame scale (2)'

		    , mPatternCheckRotation(this, 'fg99', "�p�^�[���`�F�b�N", 0, 0, 2)       // 'pattern check'
		    , mRotationSpeed1(this, 'fg00', "��]�X�s�[�h(1)", 0.015f, 0.01f, 0.03f) // 'rotation speed (1)'
		    , mRotationSpeed2(this, 'fg10', "��]�X�s�[�h(2)", 0.02f, 0.01f, 0.03f)  // 'rotation speed (2)'
		    , mReversalTime2_1(this, 'fg30', "���]����(2-1)", 30.0f, 0.0f, 30.0f)    // 'reversal time (2-1)'
		    , mReversalTime2_2(this, 'fg40', "���]����(2-2)", 2.0f, 0.0f, 30.0f)     // 'reversal time (2-2)'

		    , mPatternCheckWater(this, 'fg99', "�p�^�[���`�F�b�N", 0, 0, 3)            // 'pattern check'
		    , mWaterDischargeInterval1(this, 'fw00', "�����Ԋu(1)", 0.5f, 0.1f, 1.0f)  // 'water discharge interval (1)'
		    , mRandomAngle1(this, 'fw01', "�����_���p�x(1)", 0.5f, 0.0f, 1.0f)         // 'random angle (1)'
		    , mRandomDistance1(this, 'fw02', "�����_������(1)", 100.0f, 0.0f, 500.0f)  // 'random distance (1)'
		    , mWaterDischargeInterval2(this, 'fw10', "�����Ԋu(2)", 0.25f, 0.1f, 1.0f) // 'water discharge interval (2)
		    , mRandomAngle2(this, 'fw11', "�����_���p�x(2)", 0.4f, 0.0f, 1.0f)         // 'random angle (2)'
		    , mRandomDistance2(this, 'fw12', "�����_������(2)", 50.0f, 0.0f, 500.0f)   // 'random distance (2)'
		    , mPatternCheck4(this, 'fw99', "�p�^�[���`�F�b�N", 0, 0, 2)                // 'pattern check'
		{
		}

		Parm<f32> mBaseFactor;              // _804
		Parm<f32> mRaiseDecelFactor;        // _82C
		Parm<f32> mDownwardDecelFactor;     // _854
		Parm<f32> mMinReducedAccelFactor;   // _87C
		Parm<f32> mMaxDecelAccelFactor;     // _8A4
		Parm<f32> mLegSwing;                // _8CC
		Parm<f32> mElectricityWaitTime;     // _8F4
		Parm<f32> mFireWaitTime1;           // _91C
		Parm<f32> mFireWaitTime2;           // _944
		Parm<f32> mGasWaitTime;             // _96C
		Parm<f32> mWaterWaitTime;           // _994
		Parm<f32> mElecAttackTimeMax;       // _9BC, fp20
		Parm<f32> mFireAttackTimeMax;       // _9E4, fp21
		Parm<f32> mGasAttackTimeMax;        // _A0C, fp22
		Parm<f32> mWaterAttackTimeMax;      // _A34, fp23
		Parm<f32> mBounceCoefficient1_1;    // _A5C
		Parm<f32> mFrictionCoefficient1_1;  // _A84
		Parm<f32> mBaseMuzzleVelocityXZ1_1; // _AAC
		Parm<f32> mRandMuzzleVelocityXZ1_1; // _AD4
		Parm<f32> mBaseMuzzleVelocityY1_1;  // _AFC
		Parm<f32> mRandMuzzleVelocityY1_1;  // _B24
		Parm<f32> mDischargeStart1_1;       // _B4C
		Parm<f32> mChainInterval1_1;        // _B74
		Parm<int> mDischargeCount1_1;       // _B9C
		Parm<f32> mBounceCoefficient1_2;    // _BC4
		Parm<f32> mFrictionCoefficient1_2;  // _BEC
		Parm<f32> mBaseMuzzleVelocityXZ1_2; // _C14
		Parm<f32> mRandMuzzleVelocityXZ1_2; // _C3C
		Parm<f32> mBaseMuzzleVelocityY1_2;  // _C64
		Parm<f32> mRandMuzzleVelocityY1_2;  // _C8C
		Parm<f32> mDischargeStart1_2;       // _CB4
		Parm<f32> mChainInterval1_2;        // _CDC
		Parm<int> mDischargeCount1_2;       // _D04
		Parm<f32> mBounceCoefficient2_1;    // _D2C
		Parm<f32> mFrictionCoefficient2_1;  // _D54
		Parm<f32> mBaseMuzzleVelocityXZ2_1; // _D7C
		Parm<f32> mRandMuzzleVelocityXZ2_1; // _DA4
		Parm<f32> mBaseMuzzleVelocityY2_1;  // _DCC
		Parm<f32> mRandMuzzleVelocityY2_1;  // _DF4
		Parm<f32> mDischargeStart2_1;       // _E1C
		Parm<f32> mChainInterval2_1;        // _E44
		Parm<int> mDischargeCount2_1;       // _E6C
		Parm<f32> mBounceCoefficient2_2;    // _E94
		Parm<f32> mFrictionCoefficient2_2;  // _EBC
		Parm<f32> mBaseMuzzleVelocityXZ2_2; // _EE4
		Parm<f32> mRandMuzzleVelocityXZ2_2; // _F0C
		Parm<f32> mBaseMuzzleVelocityY2_2;  // _F34
		Parm<f32> mRandMuzzleVelocityY2_2;  // _F5C
		Parm<f32> mDischargeStart2_2;       // _F84
		Parm<f32> mChainInterval2_2;        // _FAC
		Parm<int> mDischargeCount2_2;       // _FD4
		Parm<int> mPatternCheckFlame;       // _FFC
		Parm<f32> mFlameScale1;             // _1024
		Parm<f32> mFlameScale2;             // _104C
		Parm<int> mPatternCheckRotation;    // _1074
		Parm<f32> mRotationSpeed1;          // _109C
		Parm<f32> mRotationSpeed2;          // _10C4
		Parm<f32> mReversalTime2_1;         // _10EC
		Parm<f32> mReversalTime2_2;         // _1114
		Parm<int> mPatternCheckWater;       // _113C
		Parm<f32> mWaterDischargeInterval1; // _1164
		Parm<f32> mRandomAngle1;            // _118C
		Parm<f32> mRandomDistance1;         // _11B4
		Parm<f32> mWaterDischargeInterval2; // _11DC
		Parm<f32> mRandomAngle2;            // _1204
		Parm<f32> mRandomDistance2;         // _122C
		Parm<int> mPatternCheck4;           // _1254
	};

	Parms() { }

	virtual void read(Stream& stream) // _08 (weak)
	{
		CreatureParms::read(stream);
		mGeneral.read(stream);
		mProperParms.read(stream);
	}

	// _00-_7F8	= EnemyParmsBase
	ProperParms mProperParms; // _7F8
};

enum AnimID {
	BIGTREASUREANIM_NULL    = -1,
	BIGTREASUREANIM_Appear  = 0,
	BIGTREASUREANIM_Appear2 = 1,
	BIGTREASUREANIM_Wait1   = 2,

	// Fire attacks (forward, right, left, back)
	BIGTREASUREANIM_PreAttackF = 3,
	BIGTREASUREANIM_AttackF    = 4,
	BIGTREASUREANIM_AttackEndF = 5,

	BIGTREASUREANIM_PreAttackFR = 6,
	BIGTREASUREANIM_AttackFR    = 7,
	BIGTREASUREANIM_AttackEndFR = 8,

	BIGTREASUREANIM_PreAttackFL = 9,
	BIGTREASUREANIM_AttackFL    = 10,
	BIGTREASUREANIM_AttackEndFL = 11,

	BIGTREASUREANIM_PreAttackFB = 12,
	BIGTREASUREANIM_AttackFB    = 13,
	BIGTREASUREANIM_AttackEndFB = 14,

	// Water attack
	BIGTREASUREANIM_PreAttackW = 15,
	BIGTREASUREANIM_AttackW    = 16,
	BIGTREASUREANIM_AttackEndW = 17,

	// Gas attack
	BIGTREASUREANIM_PreAttackG = 18,
	BIGTREASUREANIM_AttackG    = 19,
	BIGTREASUREANIM_AttackEndG = 20,

	// Elec attack
	BIGTREASUREANIM_PreAttackE = 21,
	BIGTREASUREANIM_AttackE    = 22,
	BIGTREASUREANIM_AttackEndE = 23,

	BIGTREASUREANIM_DropItem = 24,
	BIGTREASUREANIM_Wait2    = 25,
	BIGTREASUREANIM_Flick    = 26,
	BIGTREASUREANIM_Dead     = 27,
	BIGTREASUREANIM_Move1    = 28,
	BIGTREASUREANIM_Wait2_2  = 29, // repeat of Wait2?
	BIGTREASUREANIM_AnimCount,     // 30
};

struct ProperAnimator : public EnemyBlendAnimatorBase {
	virtual ~ProperAnimator() { } // _08 (weak)

	// _00 		= VTBL
	// _00-_60	= EnemyBlendAnimatorBase
};

struct BigTreasureShadowMgr {
	BigTreasureShadowMgr(Obj*);

	void init();
	void setJointPosPtr(int jointIndex, int positionIndex, Vector3f* position);
	void setKosiJointPosPtr(Vector3f* position);
	void update();
	void updateTreasureShadow(JointShadowParm& settings);
	void updateHandShadow(JointShadowParm& settings);
	void updateAntennaShadow(JointShadowParm& settings);

	Matrixf* mBodyMatrix;            // _00
	Matrixf* mElecMatrix;            // _04
	Matrixf* mFireMatrix;            // _08
	Matrixf* mGasMatrix;             // _0C
	Matrixf* mWaterMatrix;           // _10
	Matrixf* mLeftArmMatrix[3];      // _14
	Matrixf* mRightArmMatrix[3];     // _20
	Matrixf* mLeftAntennaMatrix[2];  // _2C
	Matrixf* mRightAntennaMatrix[2]; // _34
	Obj* mObj;                       // _3C
	Vector3f* mKosiPosition;         // _40
	Vector3f* mJointPositions[4][4]; // _44
	JointShadowRootNode* mRootNode;  // _84
	SphereShadowNode* _88;           // _88
	SphereShadowNode* _8C;           // _8C
	TubeShadowSetNode* _90[4];       // _90
	TubeShadowSetNode* _A0[4];       // _A0
	TubeShadowSetNode* _B0[4];       // _B0
	TubeShadowSetNode* _C0[4];       // _C0
	SphereShadowNode* _D0[4];        // _D0
	SphereShadowNode* _E0[4];        // _E0
	SphereShadowNode* _F0[4];        // _F0
	SphereShadowNode* _100[4];       // _100
	TubeShadowPosNode* _110[2][4];   // _110
	SphereShadowNode* _130[2][2];    // _130
	TubeShadowPosNode* _140[2][5];   // _140
	SphereShadowNode* _168[2];       // _168
};

struct BigTreasureGroundCallBack : public JointGroundCallBack {
	inline BigTreasureGroundCallBack(Obj* obj)
	    : mObj(obj)
	{
	}

	virtual void invokeOnGround(int footIdx, WaterBox* wb);  // _08
	virtual void invokeOffGround(int footIdx, WaterBox* wb); // _0C

	// _00	= VTBL
	Obj* mObj; // _04
};

/////////////////////////////////////////////////////////////////
// ATTACK DEFINITIONS
struct AttackShadowNode : public JointShadowNode {
	AttackShadowNode(int nodeCount);

	virtual ~AttackShadowNode() { } // _08 (weak)

	void makeShadowSRT();

	// _00      = VTBL
	// _00-_24  = JointShadowNode
	Vector3f* _24; // _24
	f32 _28;       // _28
};

struct BigTreasureAttackData {
	inline BigTreasureAttackData()
	{
		_00 = 0.75f;
		_04 = 0.65f;
		_08 = 100.0f;
		_0C = 220.0f;
		_10 = 170.0f;
		_14 = 200.0f;
		_18 = 2.7f;
		_1C = 0.1f;
		_20 = 15;
		_24 = 0;
		_28 = 1.0f;
		_2C = 1;
		_30 = 3;
		_34 = 0.02f;
		_38 = 30.0f;
		_3C = 0.5f;
		_40 = 0.25f;
		_44 = 50.0f;
	}

	f32 _00; // _00
	f32 _04; // _04
	f32 _08; // _08
	f32 _0C; // _0C
	f32 _10; // _10
	f32 _14; // _14
	f32 _18; // _18
	f32 _1C; // _1C
	int _20; // _20
	int _24; // _24
	f32 _28; // _28
	u8 _2C;  // _2C
	int _30; // _30
	f32 _34; // _34
	f32 _38; // _38
	f32 _3C; // _3C
	f32 _40; // _40
	f32 _44; // _44
};

struct BigTreasureAttackParameter : public BigTreasureAttackData {
	// just a wrapper as far as I can tell, might've been differentiated based on type?
};

struct BigTreasureElecAttack : public CNode {
	BigTreasureElecAttack(Obj*, BigTreasureAttackParameter*);

	virtual ~BigTreasureElecAttack() { } // _08 (weak)

	bool update();

	void init();
	void start(Vector3f&, Vector3f&, bool);
	void startInteract(BigTreasureElecAttack*);
	void finish();

	// _00      = VTBL
	// _00-_18  = CNode
	Obj* mOwner;                         // _18
	BigTreasureAttackData* mAttackData;  // _1C
	u8 _20;                              // _20
	Sys::Triangle* _24;                  // _24
	Vector3f _28;                        // _28
	Vector3f _34;                        // _34
	u32 _40;                             // _40, unknown
	efx::TOootaElec* mEfxElec;           // _44
	efx::TOootaElecparts* mEfxElecParts; // _48
	efx::TOootaPhouden* mEfxPhouden;     // _4C
};

struct BigTreasureFireAttack : public CNode {
	BigTreasureFireAttack(Obj*, BigTreasureAttackParameter*);

	virtual ~BigTreasureFireAttack() { } // _08 (weak)

	bool update();

	void init();
	void start(Vector3f&, Vector3f&);
	void finish();

	// _00      = VTBL
	// _00-_18  = CNode
	Obj* mOwner;                        // _18
	BigTreasureAttackData* mAttackData; // _1C
	f32 _20;                            // _20
	Vector3f _24;                       // _24
	Vector3f _30;                       // _30
};

struct BigTreasureGasAttack : public CNode {
	BigTreasureGasAttack(Obj*, BigTreasureAttackParameter*);

	virtual ~BigTreasureGasAttack() { } // _08 (weak)

	bool update();

	void init();
	void start(Vector3f&, f32);

	// _00      = VTBL
	// _00-_18  = CNode
	Obj* mOwner;                        // _18
	BigTreasureAttackData* mAttackData; // _1C
	f32 _20;                            // _20
	Vector3f _24;                       // _24
	Vector3f _30;                       // _30, gas emit position?
};

struct BigTreasureWaterAttack : public CNode {
	BigTreasureWaterAttack(Obj*, BigTreasureAttackParameter*);

	virtual ~BigTreasureWaterAttack() { } // _08 (weak)

	bool update();

	void init();
	void start(Vector3f&, Vector3f&);
	void finish();

	// _00      = VTBL
	// _00-_18  = CNode
	Obj* mOwner;                        // _18
	BigTreasureAttackData* mAttackData; // _1C
	Vector3f _20;                       // _24
	Vector3f _2C;                       // _30
	efx::TOootaWbomb* mEfxWaterBomb;    // _38
};

struct BigTreasureAttackMgr {
	BigTreasureAttackMgr(Obj*);

	void init();
	void update();

	void startFireAttack();
	void startNewFireList();
	void updateFireAttack();
	void updateFireEmitPosition();
	void updateFireSePosition(BigTreasureFireAttack* attack, int nodeType);

	void startGasAttack();
	void startNewGasList();
	void updateGasAttack();
	void updateGasEmitPosition();
	void updateGasSePosition(BigTreasureGasAttack* attack, int nodeType);

	void startWaterAttack();
	void startNewWaterList();
	void updateWaterAttack();
	void updateWaterEmitPosition();
	void getWaterTargetCreature();

	void setElecAttackParameter();
	void startElecAttack();
	void updateElecAttack();
	void finishAttack();

	void addAttackShadow(BigTreasureWaterAttack* attack);
	void addAttackShadow(BigTreasureElecAttack* attack);
	void delAttackShadow(BigTreasureWaterAttack* attack);
	void delAttackShadow(BigTreasureElecAttack* attack);
	void updateAttackShadow();

	// unused/inlined:
	void setFireAttackParameter();
	void finishFireAttack();
	void setGasAttackParameter();
	void finishGasAttack();
	void setWaterAttackParameter();
	void finishWaterAttack();
	void startNewElecList();
	void finishElecAttack();

	u8 _00[4];                               // _00
	Obj* mObj;                               // _04
	f32 _08;                                 // _08
	f32 _0C;                                 // _0C
	CNode* _10;                              // _10
	CNode* mFireAttackNodes;                 // _14
	efx::TOootaFire* mEfxFire;               // _18
	Vector3f _1C;                            // _1C
	Vector3f _28[3];                         // _28
	CNode* _4C;                              // _4C
	CNode* mGasAttackNodes;                  // _50
	f32 _54[4];                              // _54
	Vector3f mGasEmitPosition;               // _64
	Vector3f _70[4];                         // _70
	efx::TOootaGas* mEfxGas[4];              // _A0
	CNode* _B0;                              // _B0
	CNode* mWaterAttackNodes;                // _B4
	efx::TOootaWbomb* mEfxWaterBomb;         // _B8
	Vector3f mWaterEmitPosition;             // _BC
	CNode* _C8;                              // _C8
	CNode* mElecAttackNodes;                 // _CC
	efx::TOootaElecLeg* mEfxElecLeg[4][3];   // _D0
	efx::TOootaElecAttack1* mEfxElecAttack1; // _100
	efx::TOootaElecAttack2* mEfxElecAttack2; // _104
	u8 _108[0xC];                            // _108, unknown
	JointShadowRootNode* mShadowRootNode;    // _114
	AttackShadowNode** mAttackShadowNodes;   // _118, array of 16 ptrs
	BigTreasureAttackData* mAttackData;      // _11C
};
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// STATE MACHINE DEFINITIONS
struct FSM : public EnemyStateMachine {
	virtual void init(EnemyBase* enemy); // _08

	// _00		= VTBL
	// _00-_1C	= EnemyStateMachine
};

struct State : public EnemyFSMState {
	inline State(int stateID, const char* name)
	    : EnemyFSMState(stateID)
	{
		mName = name;
	}

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateAttack : public State {
	inline StateAttack()
	    : State(BIGTREASURE_Attack, "attack")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateDead : public State {
	inline StateDead()
	    : State(BIGTREASURE_Dead, "dead")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateDropItem : public State {
	inline StateDropItem()
	    : State(BIGTREASURE_DropItem, "dropitem")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateFlick : public State {
	inline StateFlick()
	    : State(BIGTREASURE_Flick, "flick")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateItemWait : public State {
	inline StateItemWait()
	    : State(BIGTREASURE_ItemWait, "itemwait")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateItemWalk : public State {
	inline StateItemWalk()
	    : State(BIGTREASURE_ItemWalk, "itemwalk")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateLand : public State {
	inline StateLand()
	    : State(BIGTREASURE_Land, "land")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StatePreAttack : public State {
	inline StatePreAttack()
	    : State(BIGTREASURE_PreAttack, "preattack")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StatePutItem : public State {
	inline StatePutItem()
	    : State(BIGTREASURE_PutItem, "putitem")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateStay : public State {
	inline StateStay()
	    : State(BIGTREASURE_Stay, "stay")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateWait : public State {
	inline StateWait()
	    : State(BIGTREASURE_Wait, "wait")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};

struct StateWalk : public State {
	inline StateWalk()
	    : State(BIGTREASURE_Walk, "walk")
	{
	}

	virtual void init(EnemyBase* enemy, StateArg* settings); // _08
	virtual void exec(EnemyBase* enemy);                     // _0C
	virtual void cleanup(EnemyBase* enemy);                  // _10

	// _00		= VTBL
	// _00-_10 	= EnemyFSMState
};
/////////////////////////////////////////////////////////////////
} // namespace BigTreasure
} // namespace Game

#endif

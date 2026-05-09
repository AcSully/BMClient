#ifndef _INC_GAMEOTHERPLAYER_
#define _INC_GAMEOTHERPLAYER_
//////////////////////////////////////////////////////////////////////////
#include "../Common/GameRenderObject.h"
#include "../Net/GamePacketHandler.h"
#include "../GameScene/MagicEffect.h"
#include "../../CommonModule/ShareDefine.h"
//////////////////////////////////////////////////////////////////////////
class GameOtherPlayer : public GameObject
{
public:
	GameOtherPlayer();
	virtual ~GameOtherPlayer();

public:
	virtual void Update(float _dt);
	virtual void Render();
	virtual bool ProcUserCmd(const POINT& _mp);
	virtual bool IsLastFrame();
	virtual void TransparentRender();
	//	��������
	virtual void RenderName();
	virtual void RenderSaying();

	virtual void ResetTimerCounter()
	{
		m_fMoveOffsetXTotal = m_fMoveOffsetYTotal = 0.0f;
	}

	virtual void OnSetStatus(PLAYER_STATUS _ps);
	virtual void OnObjectAction(const PkgObjectActionNot& not);

public:
	int CalTextureIndex(int* _ptexsum = NULL, int* _pResIndex = NULL);
	int CalHairTexIndex(int* _ptexsum = NULL);
	int CalHairResIndex();
	int CalWingIndex(int* _ptexsum = NULL);
	int CalWeaponTexIndex(int* _ptexsum = NULL, int* _pResIndex = NULL);
	DWORD CalCustomWingIndexAndRes();

	virtual void UpdateMove();

	ItemAttrib* GetPlayerItem()
	{
		return m_equip;
	}
	ItemAttrib* GetPlayerItem(PLAYER_ITEM_TYPE _type)
	{
		return &m_equip[_type];
	}

	//	For magic
	void SetMagicEffect(MAGICEFFECT_TYPE _mgc);
	void ResetMagicEffect(MAGICEFFECT_TYPE _mgc);
	void RenderMagic();

	bool PlayMagic(int _nMgcID, GameObject* _pTarget, short _sDestX, short _sDestY, DWORD _dwAniTime);
	void RenderHumEffect();

	int GetMinEquipGrade();

	inline const char* GetHeroJobName()
	{
		switch(m_bJob)
		{
		case 0:
			{
				return "սʿ";
			}break;
		case 1:
			{
				return "��ʦ";
			}break;
		case 2:
			{
				return "��ʿ";
			}break;
		default:
			{
				return "δ����";
			}break;
		}
	}
	inline int GetHeroJob()
	{
		return m_bJob;
	}
	inline void SetHeroJob(int _bJob)
	{
		m_bJob = _bJob;
	}
	inline void UpdateLastAttackTime()
	{
		m_dwLastAttackTime = GetTickCount();
	}
	inline int GetHeroLevel()
	{
		return m_attrib.level;
	}
	inline void SetVipLevel(int _nLevel)
	{
		m_nVipLevel = _nLevel;
	}
	inline int GetVipLevel()
	{
		return m_nVipLevel;
	}
	inline ExtendHeroAttrib* GetExtendAttrib()
	{
		return &m_stExtAttrib;
	}

//protected:
	void RenderSelfEffect();
	//void SetHumEffect(DWORD _dwMask, DWORD _dwTime);
	void RenderHitEffect();
	void ClearHitEffect();

	void SetSelfEffect(MagicElement* _pEle);
	void SelfEffectUpdate();
	void SelfEffectRender();


	void PlayAttackSound();

	//	����Ч��
	void RefleashHumState();
	void ClearHumState();
	void UpdateHumState();
	void RenderHumState();
	bool InsertHumState(MagicElement* _pMgc);

	void RenderSkillEffect();

	//	����������������
	void RenderHum();
	void RenderHair();
	void RenderWeapon();
	void RenderWing();


	virtual int GetSkillLevel(DWORD _dwMgcID);
	void AddSkillLevelInfo(DWORD _dwMgcID, DWORD _dwLevel);
	void ClearSkillLevel();

//////////////////////////////////////////////////////////////////////////
	//	���ݰ�����
public:
	virtual void OnPacket(const PacketHeader* _pPkt);

	void DoPacket(const PkgChatNot& not);
	//void DoPacket(const PkgObjectActionNot& not);
	void DoPacket(const PkgPlayerChangeEquipNot& not);
	void DoPacket(const PkgPlayerGainItemNtf& ntf);
	void DoPacket(const PkgPlayerDropItemNot& not);
	void DoPacket(const PkgPlayerLostItemAck& ack);
	//void DoPacket(const PkgPlayerClearItemNtf& ntf);
	void DoPacket(const PkgPlayerSyncAttribNtf& ntf);
	void DoPacket(const PkgPlayerUndressItemAck& ack);
	void DoPacket(const PkgPlayerDressItemAck& ack);
	void DoPacket(const PkgPlayerUseItemAck& ack);
	void DoPacket(const PkgPlayerUpdateAttribNtf& ntf);
	void DoPacket(const PkgPlayerStruckAck& ack);
	void DoPacket(const PkgPlayerForceActionAck& ack);
	void DoPacket(const PkgPlayerClearBagNtf& ntf);
	void DoPacket(const PkgPlayerChangeMapAck& ack);
	void DoPacket(const PkgPlayerShowDoorAniAck& ack);
	void DoPacket(const PkgPlayerHideQuestDlgAck& ack);
	void DoPacket(const PkgPlayerGetBaleItemAck& ack);
	void DoPacket(const PkgPlayerSetEffectAck& ack);
	void DoPacket(const PkgPlayerReviveNot& not);
	void DoPacket(const PkgPlayerStoreDataAck& ack);
	void DoPacket(const PkgPlayerStoreSyncAck& ack);
	void DoPacket(const PkgPlayerShowHelpAck& ack);
	void DoPacket(const PkgPlayerShowDlgAck& ack);
	void DoPacket(const PkgPlayerUpdateCostNtf& ntf);
	void DoPacket(const PkgPlayerNetDelayAck& ack);
	void DoPacket(const PkgPlayerClearAllItemAck& ack);
	void DoPacket(const PkgPlayerUpdateItemNtf& ntf);
	void DoPacket(const PkgPlayerQuickMsgNtf& ntf);
	void DoPacket(const PkgPlayerVersionVerifyNtf& ntf);
	void DoPacket(const PkgPlayerQuestDataNtf& ntf);
	void DoPacket(const PkgPlayerSyncQuestNtf& ntf);
	void DoPacket(const PkgPlayerOtherPlayerEquipNtf& ntf);
	void DoPacket(const PkgPlayerGStatusNtf& ntf);
	void DoPacket(const PkgPlayerPlaySoundNtf& ntf);
	void DoPacket(const PkgPlayerOffSellListNtf& ntf);
	void DoPacket(const PkgPlayerOffSoldItemAck& ack);
	void DoPacket(const PkgPlayerUIDNtf& ntf);
	void DoPacket(const PkgPlayerUpdateWeaponGrowNtf& ntf);
	void DoPacket(const PkgPlayerPrivateChatAck& ack);
	void DoPacket(const PkgPlayerPrivateChatNtf& ntf);
	void DoPacket(const PkgPlayerServerDelayReq& req);
	void DoPacket(const PkgPlayerUpdateRandSeedNot& not);
	void DoPacket(const PkgPlayerRankListNot& not);
	void DoPacket(const PkgPlayerBuyOlShopItemAck& ack);
	void DoPacket(const PkgPlayerGetOlShopListAck& ack);
	void DoPacket(const PkgPlayerExtendAttribNot& not);
	void DoPacket(const PkgPlayerSmeltMaterialsRsp& rsp);
	void DoPacket(const PkgPlayerOpenPotentialRsp& rsp);
	void DoPacket(const PkgPlayerSayNot& not);
	void DoPacket(const PkgPlayerWorldSayNot& not);
	void DoPacket(const PkgPlayerEnableSkillNot& not);
	void DoPacket(const PkgPlayerPlayAniAck& ack);
	void DoPacket(const PkgPlayerDialogDataAck& ack);
	void DoPacket(const PkgPlayerDifficultyLevelRsp& rsp);
	void DoPacket(const PkgPlayerQuitSelChrRsp& rsp);
	void DoPacket(const PkgGameSyncDataNot& not);
	void DoPacket(const PkgGameObjectActionsNot& not);
	void DoPacket(const PkgGamePlayerSuitIgnoreNot& not);
	//void DoPacket(const PkgPlayerQuickMsgNtf& ntf);

	//bool MoveToDestination(WORD _wCoordX, WORD _wCoordY, BYTE _bWay);

protected:
	ItemAttrib m_equip[PLAYER_ITEM_TOTAL];
	float m_fDetect;
	float m_fMoveOffsetXTotal;
	float m_fMoveOffsetYTotal;
	float m_fLastUpdateSkill;
	float m_fLastUpdateAttack;
	float m_fLastUpdateDeath;
	float m_fLastUpdateAttackNoWeapon;
	float m_fLastUpdateAttackStop;
	float m_fLastUpdateAttacked;
	float m_fLastUpdateMove;

	//	Magic effect
	MAGICEFFECT_TYPE m_eEffect[MAGICEFFECT_TOTAL];
	/*DWORD m_dwHumEffectFlag;
	DWORD m_dwHumEffectTime[MMASK_TOTAL];*/
	MagicElement* m_pMagicEffect;
	hgeSprite* m_pEffectRender;

	bool m_bPlayOneStep;
	bool m_bPlayTwoStep;

	BYTE m_bJob;

	//	�ϴι���ʱ��
	DWORD m_dwLastAttackTime;
	DWORD m_dwLastAttackStopTime;

	//	�ϴι���ģʽ 0:�������� 1:ħ������
	DWORD m_dwLastAttackMode;

	//	ħ��Ч��
	MagicElementList m_xHumStates;

	//	
	DWORD m_dwJinGangExpireTime;

	//	�һ𽣷��ĵȼ� ������Ⱦ����Ч��
	int m_nLieHuoSkillLevel;

	//DWORD m_dwLastMoveTime;
	int m_nVipLevel;
	DWORD m_dwLastNameColorChangeTime;
	int m_nLastNameColorIndex;

	//	���ܵȼ���Ϣ
	map<DWORD, DWORD> m_xSkillInfo;

	//	��չ��������
	ExtendHeroAttrib m_stExtAttrib;

	// ����
	bool m_bInRider;
};
//////////////////////////////////////////////////////////////////////////
#endif
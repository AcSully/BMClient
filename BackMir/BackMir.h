#ifndef _BACKMIR_H_
#define _BACKMIR_H_
#include "SGameBase.h"
#include <Windows.h>
#include "../Common/MirMap.h"
#include "../GameScene/GameTextureManager.h"
#include "../GameScene/GameMapManager.h"
#include "../GameScene/GameScene.h"
#include "../LoginScene/LoginScene.h"
//#include "../LoginScene/SelChrScene.h"
//#include "../Net/PacketQueue.h"
//#include "../../CommonModule/ScriptEngine.h"
#include "LuaClientEngine.h"
#include "../../CommonModule/SaveFile.h"
#include "../../CommonModule/SettingLoader.h"
#include "../../CommonModule/ShareDefine.h"
#include "../../CommonModule/DataParser.h"
#include "../DuiWnd/AssistPaneWnd.h"
#include "../Common/SelectedTextureManager.h"
#include <google/protobuf/message.h>
//#include "BMDonateWnd.h"
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class MirGame;
class BMDonateValueWnd;
class AssistPaneWnd;
class BMDonateWnd;

extern MirGame* pTheGame;

extern ByteBuffer g_xBuffer;
//////////////////////////////////////////////////////////////////////////
#define DO_LOGIN_PACKET(op, pkg) case op:{pkg p;g_xBuffer >> p;DoLoginPacket(p);}break;

#define MAP_LAYER_NUM 3
#define MAP_WIDTH_PIX 48
#define MAP_HEIGHT_PIX 32
//
#define SMSG_ERROR(str); ::MessageBox(NULL, str, "Error!", MB_OK | MB_ICONERROR);
#define INC_ELE(e, n) (e += n)

unsigned int SendBufferToGS(ByteBuffer* _pBuf);
unsigned int SendBufferToLS(ByteBuffer* _pBuf);
unsigned int SendBufferToGS(ByteBuffer& _xBuf);
unsigned int SendBufferToLS(ByteBuffer& _xBuf);

unsigned int SendProto(int _nOpcode, google::protobuf::Message& _refMsg);
unsigned int SendProto2(int _nOpcode, google::protobuf::Message& _refMsg);
//////////////////////////////////////////////////////////////////////////
class MirGame : public SGameBase
{
public:
	MirGame();
	~MirGame();
	static MirGame* GetInstance();

public:
	virtual bool UserInitial();
	virtual void UserUninitial();
	virtual void UserFrameFunc();
	virtual void UserRenderFunc();
	virtual void UserGfxRestore();

	virtual LRESULT                 WinEventFilter(HWND h, UINT u, WPARAM w, LPARAM l); 

	virtual bool IsWindowMode();

public:
	inline GameScene* GetGameScene()
	{
		return m_pGameScene;
	}
	inline BYTE GetCurStage()
	{
		return m_bScene;
	}
	inline void SetCurState(BYTE _bStage)
	{
		m_bScene = _bStage;
	}
	inline LoginScene* GetLoginScene()
	{
		return m_pxLoginScene;
	}
	inline lua_State* GetLuaState()
	{
		return m_xScript.GetVM();
	}
	inline LuaClientEngine* GetScriptEngine()
	{
		return &m_xScript;
	}
	/*inline ScriptEngine* GetQuestScript()
	{
		return &m_xQuestScript;
	}*/
	/*inline lua_State* GetQuestLuaState()
	{
		return m_xQuestScript.GetVM();
	}*/
	inline std::map<int, int>& GetClothTable()
	{
		return m_xClothTable;
	}
	inline std::map<int, int>& GetWeaponTable()
	{
		return m_xWeaponTable;
	}
	inline bool IsSoundEnabled()
	{
		return m_bSoundEnable;
	}
	inline void SetSoundEnabled(bool _b)
	{
		m_bSoundEnable = _b;
	}
	inline bool IsSoundForbid()
	{
		return false;
		return m_bSoundForbid;
	}
	inline bool CanPlaySound()
	{
		return Config_EnableSound();
		return (m_xSettings.GetIntValue("SOUNDENABLE") != 0);
		return (m_bSoundEnable && !m_bSoundForbid);
	}
	inline hgeResourceManager* GetGameRes()
	{
		return m_pxGameRes;
	}
	inline hgeResourceManager* GetLoginRes()
	{
		return m_pxResMgr;
	}
	inline SettingLoader* GetGameSettings()
	{
		return &m_xSettings;
	}
	inline void ReleaseLoginRes()
	{
		delete m_pxLoginScene;
		m_pxLoginScene = NULL;
	}
	inline bool IsConnect()
	{
		return m_bConnect;
	}
	inline void SetConnect()
	{
		m_bConnect = true;
	}
	inline AssistPaneWnd* GetAssistPaneWnd()
	{
		return m_pAssistPaneWnd;
	}
	inline BMDonateWnd* GetDonateWnd() {
		return m_pDonateWnd;
	}
	inline BMDonateValueWnd* GetDonateValueWnd() {
		return m_pDonateValueWnd;
	}

	bool SetGameCursor(int _nResourceId);

	inline int GetDarkMode()						{return m_nDarkMode;}
	inline void SetDarkMode(int _nMode)				{m_nDarkMode = _nMode;}
	HTEXTURE GetDarkModeTexture();

	inline int GetShowMapSnap()						{return m_bShowMapSnap;}
	inline void SetShowMapSnap(bool _bShow)			{m_bShowMapSnap = _bShow;}

	inline GAME_MODE GetGameMode()					{return m_eGameMode;}
	inline void SetGameMode(GAME_MODE _eMode)		{m_eGameMode = _eMode;}
	void GetSnapshotFile(std::string& _file);
	bool CheckItemValid(const ItemAttrib* _pChecked);
	bool IsPassiveSkill(int _nMgcID);
	static bool IsEquipItem(const ItemAttrib& _item)
	{
		if(_item.type == ITEM_WEAPON ||
			_item.type == ITEM_CLOTH ||
			_item.type == ITEM_NECKLACE ||
			_item.type == ITEM_RING ||
			_item.type == ITEM_BRACELAT ||
			_item.type == ITEM_HELMET ||
			_item.type == ITEM_MEDAL ||
			_item.type == ITEM_SHOE ||
			_item.type == ITEM_BELT ||
			_item.type == ITEM_GEM ||
			_item.type == ITEM_CHARM)
		{
			return true;
		}

		return false;
	}
	void PlayItemPutDownSound(const ItemAttrib* _pItem);
	void PlayItemClickUpSound(const ItemAttrib* _pItem);

	bool IsInPlayerViewRange(int _nCoordX, int _nCoordY);

	const char* GetDifficultyLevelName(int _nDifficultyLevel);
	void UpdateWindowTitle(int _nDifficultyLevel);

	void RequestSmallQuit();

	inline void SetLoginAccount(std::string& _refAccount) {
		m_xLoginAccount = _refAccount;
	}

	//////////////////////////////////////////////////////////////////////////
	//	Quick config helper
	void LoadGameSetting();
	void WriteDefaultSetting();
	void WriteSettingsToFile();
	void UpdateConfigCache();
	bool Config_RenderHPBar();
	bool Config_ItemFlash();
	bool Config_EnableSound();
	bool Config_WindowMode();
	bool Config_SelfName();
	bool Config_EnhanceSel();
	int  Config_GetFPS();
	bool Config_JpgSnap();
	bool Config_HPAnimation();
	bool Config_TileSurface();
	bool Config_MousePickUp();
	bool Config_DisableRenderNameFrame();
	bool Config_DisableRenderChatFrame();

	void MessageLoop();

public:
	void Log(const char* _plog);
	bool LoadScript(int _nMapID);
	bool LoadQuestScript();
	//	�Ƿ����˱��پ���
	bool IsTimerFunctionRepalaced();
	//	��õ�ͼ����
	bool GetMapName(int _id, std::string& _xName);

private:
	void InitLogfile();
	bool CheckParam();
	void OnSocketMessage(SOCKET _s, LPARAM lParam);
	void OnGameSvrMsg(SOCKET _s, LPARAM lParam);
	void OnLoginSvrMsg(SOCKET _s, LPARAM lParam);
	void LoadIndexInfo();

	static void STDCALL _HandleLoginMsg(const void* _pData, unsigned int _len);
	void HandleLoginMsg(const void* _pData, unsigned int _len);
	void LoginAddGameRoleAck(const char* _pData, unsigned int _len);
	void LoginDelGameRoleAck(const char* _pData, unsigned int _len);
	void DoLoginPacket(const PkgLoginQuickMsgNot& not);
	void LoginCreateHumRsp(const char* _pData, unsigned int _len);
	void LoginDelHumRsp(const char* _pData, unsigned int _len);
	void LoginQuickMessage(const char* _pData, unsigned int _len);

	void RenderCursor(float _fx, float _fy);

	static BOOL WINAPI MyPeekMessage(
		__out LPMSG lpMsg,
		__in_opt HWND hWnd,
		__in UINT wMsgFilterMin,
		__in UINT wMsgFilterMax,
		__in UINT wRemoveMsg);
	void HookPeekMessage();
	// Vars of old PeekMessage proc
	typedef BOOL (WINAPI *PeekMessageFunc) (
		__out LPMSG lpMsg,
		__in_opt HWND hWnd,
		__in UINT wMsgFilterMin,
		__in UINT wMsgFilterMax,
		__in UINT wRemoveMsg);
	PeekMessageFunc m_pOldPeekMessage;

	// Pump all message with PeekMessage, if get WM_QUIT, return false
	static bool PumpMessage();

private:
	//	��Ϸ����
	GameScene* m_pGameScene;
	//	��½����
	LoginScene* m_pxLoginScene;
	//	��������
	BYTE m_bScene;
	//	�Ƿ��ʼ�����
	bool m_bInitialized;

	hgeResourceManager* m_pxResMgr;
	hgeResourceManager* m_pxGameRes;

	char m_szIP[4 * 3 + 3 + 1];
	WORD m_wPort;
	char m_szHero[20];

	//	�ű�����(�Ի��ű�)
	LuaClientEngine m_xScript;
	//	�ű�����(������ʾ�ű�)
	//LuaClientEngine m_xQuestScript;

	//	��װ ���� ��������
	std::map<int, int> m_xClothTable;
	std::map<int, int> m_xWeaponTable;

	bool m_bSoundForbid;
	bool m_bSoundEnable;

	//	�Ƿ�������
	bool m_bConnect;
	//	��Ϸ����
	SettingLoader m_xSettings;
	bool m_bConfigCache[12];
	int m_nFps;
	//	��Ϸ ģʽ
	GAME_MODE m_eGameMode;

	DataParser m_xLoginMsgParser;

	//	��������
	AssistPaneWnd* m_pAssistPaneWnd;
	// ��������
	BMDonateWnd* m_pDonateWnd;
	BMDonateValueWnd* m_pDonateValueWnd;

	//	�ڴ����ͷż�ʱ
	DWORD m_dwLastCheckMemoryStatus;

	//	��ҹЧ��
	int m_nDarkMode;
	HTEXTURE m_texDarkMode;

	//	�Ƿ���ʾС��ͼ�ʹ��ͼ
	bool m_bShowMapSnap;

	//	���
	int m_nCursorResourceId;

	// ��½���
	std::string m_xLoginAccount;
};

//////////////////////////////////////////////////////////////////////////
#endif
//---------------------------------------------------------
//
//サウンド
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

//--------------------------------------
//インクルードファイル
//--------------------------------------
#include"d3dx9.h"

//----------------------------------------
//前方宣言
//----------------------------------------
//class CSound;
class CSoundWave;
//class CSoundMp3;

//--------------------------------------
//クラス定義
//サウンド関連
//--------------------------------------
class CSoundManager
{
public:
	CSoundManager();												// コンストラクタ
	~CSoundManager();												// デストラクタ

	void InitAll();
	void UninitAll();
	void UpdateAll();

private:
	void ChangeSound();											//サウンドの種類
	void Select();
	void Play();

private:
	static CSoundWave* m_pSound_wave;										//サウンドのポインター
	//static CSoundMp3* m_pSound_Mp3;
	int m_Switch;
	int m_nSoundCount;
};

#endif // !_SOUNDMANAGER_H_

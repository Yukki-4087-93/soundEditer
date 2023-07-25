//---------------------------------------------------------
//
//�T�E���h
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include"d3dx9.h"

//----------------------------------------
//�O���錾
//----------------------------------------
//class CSound;
class CSoundWave;
//class CSoundMp3;

//--------------------------------------
//�N���X��`
//�T�E���h�֘A
//--------------------------------------
class CSoundManager
{
public:
	CSoundManager();												// �R���X�g���N�^
	~CSoundManager();												// �f�X�g���N�^

	void InitAll();
	void UninitAll();
	void UpdateAll();

private:
	void ChangeSound();											//�T�E���h�̎��
	void Select();
	void Play();

private:
	static CSoundWave* m_pSound_wave;										//�T�E���h�̃|�C���^�[
	//static CSoundMp3* m_pSound_Mp3;
	int m_Switch;
	int m_nSoundCount;
};

#endif // !_SOUNDMANAGER_H_

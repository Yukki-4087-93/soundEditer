//---------------------------------------------------------
//
//�T�E���h
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include"d3dx9.h"
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include"xaudio2.h"

//--------------------------------------
//�N���X��`
//�T�E���h�֘A
//--------------------------------------
class CSound
{
public:
	CSound();												// �R���X�g���N�^
	~CSound();												// �f�X�g���N�^
	virtual void Init() = 0;								// ������
	virtual void Uninit() = 0;								// �I��
	virtual void Update() = 0;								// �X�V
	void DestroyXAudioObject();								// XAudioObject�̉��

public:
	void SetVolume(float fvol) { m_fVol = fvol; }			// ���ʂ̐ݒ�
	float GetVolume() { return m_fVol; }					// ���ʂ̏��擾
	void SetPitch(float fpit) { m_fPitch = fpit; }			// ���ʂ̐ݒ�
	float GetPitch() { return m_fPitch; }					// �����̏��擾
	IXAudio2 *GetXAudioObject() { return m_pXAudio2; }
	IXAudio2MasteringVoice *GetMasteringVoice() { return m_pMasteringVoice; }

private:
	IXAudio2 *m_pXAudio2;												// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;							// �}�X�^�[�{�C�X
	int m_nCountFade;													// �t�F�[�h�p�J�E���^�[
	float m_fVol;														// �T�E���h�̉��ʂ�ω�������ϐ�
	float m_fPitch;														// �T�E���h�̉�����ω�������ϐ�
	
};

#endif // !_SOUND_H_

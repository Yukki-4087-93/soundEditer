//-----------------------------------------------------------------------------
//
//�T�E���h
//Author::TAKANO
//
//-----------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "sound.h"
#include <assert.h>

//--------------------------------------
//�萔��`
//--------------------------------------
const float SOUND_VOLUME = 1.0f;						//�萔�̍ő�l
const float SOUND_PITCH = 1.0f;							//�����̏����l

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CSound::CSound()
{
	m_pXAudio2 = nullptr;				// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X�̃N���A
	m_pMasteringVoice = nullptr;		// �}�X�^�[�{�C�X�̃N���A
	
	m_fVol = SOUND_VOLUME;				//���ʂ̏�����
	m_fPitch = SOUND_PITCH;				//�����̏�����
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CSound::~CSound()
{
}

//--------------------------------------
//XAudioObject�̉��
//--------------------------------------
void CSound::DestroyXAudioObject()
{
	if (m_pMasteringVoice != nullptr)
	{
		// �}�X�^�[�{�C�X�̔j��
		m_pMasteringVoice->DestroyVoice();
		m_pMasteringVoice = nullptr;
	}

	if (m_pXAudio2 != nullptr)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
		m_pXAudio2 = nullptr;
	}
}

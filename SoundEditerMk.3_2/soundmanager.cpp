//-----------------------------------------------------------------------------
//
//�T�E���h�}�l�[�W���[
//Author::TAKANO
//
//-----------------------------------------------------------------------------
#include "application.h"
#include "input.h"
#include "soundmanager.h"
#include "SoundWAVE.h"
//#include "SoundMp3.h"
#include <assert.h>

//--------------------------------------
//�O���[�o���ϐ�
//--------------------------------------
CSoundWave *CSoundManager::m_pSound_wave;
//CSoundMp3 *CSoundManager::m_pSound_Mp3;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CSoundManager::CSoundManager()
{
	m_pSound_wave = nullptr;		//�T�E���h�|�C���^�̏�����
	//m_pSound_Mp3 = nullptr;
	
	m_Switch = 0;
	m_nSoundCount = 0;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CSoundManager::~CSoundManager()
{
}

//--------------------------------------
//������
//--------------------------------------
void CSoundManager::InitAll()
{
	m_Switch = 0;
	m_nSoundCount = 0;

	//�|�C���^�̓��I�m��
	m_pSound_wave = new CSoundWave;

	//m_pSound_Mp3 = new CSoundMp3;

	if (m_pSound_wave != nullptr)
	{//�|�C���^�ɒl�������Ă����Ƃ�
		m_pSound_wave->Init();		//������
	}

	//if (m_pSound_Mp3 != nullptr)
	//{//�|�C���^�ɒl�������Ă����Ƃ�
	//	m_pSound_Mp3->Init();		//������
	//}
}

//--------------------------------------
//�I��
//--------------------------------------
void CSoundManager::UninitAll()
{
	//�I��
	m_pSound_wave->Uninit();

	if (m_pSound_wave != nullptr)
	{
		delete m_pSound_wave;
		m_pSound_wave = nullptr;
	}
}

//--------------------------------------
//�X�V
//--------------------------------------
void CSoundManager::UpdateAll()
{

	m_pSound_wave->Update();

	ChangeSound();

	Play();
}

//--------------------------------------
//�Ȃ̕ύX
//--------------------------------------
void CSoundManager::ChangeSound()
{
	if (CApplication::GetInput()->GetkeyboardTrigger(DIK_L))
	{ //�Ȃ̓���ւ�

		m_Switch = (m_Switch + 1) % 12;

		Select();

		if (m_Switch >= 11)
		{
			m_Switch = 0;
		}
	}
}

//--------------------------------------
//�I��
//--------------------------------------
void CSoundManager::Select()
{
	switch (m_Switch)
	{
	case 0:

		/*�ύX�Ȃ�*/

		break;

	case 1:
		m_pSound_wave->Stop();
		m_pSound_wave->Play(m_pSound_wave->WAVE_BGM_BATTLEBAN,0);
		m_pSound_wave->SetType(m_pSound_wave->WAVE_BGM_BATTLEBAN);
		break;

	case 2:
		m_pSound_wave->Stop();
		m_pSound_wave->Play(m_pSound_wave->WAVE_BGM_LAST_MEETING, 0);
		m_pSound_wave->SetType(m_pSound_wave->WAVE_BGM_LAST_MEETING);
		break;

	case 3:
		m_pSound_wave->Stop();
		m_pSound_wave->Play(m_pSound_wave->WAVE_BGM_RESULT_BGM, 0);
		m_pSound_wave->SetType(m_pSound_wave->WAVE_BGM_RESULT_BGM);
		break;

	case 4:
		m_pSound_wave->Stop();
		m_pSound_wave->Play(m_pSound_wave->WAVE_BGM_VIRTUAL, 0);
		m_pSound_wave->SetType(m_pSound_wave->WAVE_BGM_VIRTUAL);
		break;

	case 5:
		m_pSound_wave->Stop();
		m_pSound_wave->Play(m_pSound_wave->WAVE_BGM_BATTLEMEETING_VER_2, 0);
		m_pSound_wave->SetType(m_pSound_wave->WAVE_BGM_BATTLEMEETING_VER_2);
		break;

	case 6:
		m_pSound_wave->Stop();
		m_pSound_wave->Play(m_pSound_wave->WAVE_BGM_NO_NAME, 0);
		m_pSound_wave->SetType(m_pSound_wave->WAVE_BGM_NO_NAME);
		break;

	case 7:
		m_pSound_wave->Stop();
		m_pSound_wave->Play(m_pSound_wave->WAVE_BGM_CHALLENGE_TO_TOMORROW, 0);
		m_pSound_wave->SetType(m_pSound_wave->WAVE_BGM_CHALLENGE_TO_TOMORROW);
		break;

	case 8:
		m_pSound_wave->Stop();
		m_pSound_wave->Play(m_pSound_wave->WAVE_BGM_BATTLEMEETING, 0);
		m_pSound_wave->SetType(m_pSound_wave->WAVE_BGM_BATTLEMEETING);
		break;

	case 9:
		m_pSound_wave->Stop();
		m_pSound_wave->Play(m_pSound_wave->WAVE_BGM_HEART, 0);
		m_pSound_wave->SetType(m_pSound_wave->WAVE_BGM_HEART);
		break;

	case 10:
		m_pSound_wave->Stop();
		m_pSound_wave->Play(m_pSound_wave->WAVE_BGM_DRUM_VOICE, 0);
		m_pSound_wave->SetType(m_pSound_wave->WAVE_BGM_DRUM_VOICE);
		break;

	case 11:
		m_pSound_wave->Stop();
		m_pSound_wave->Play(m_pSound_wave->WAVE_BGM_RANKING, 0);
		m_pSound_wave->SetType(m_pSound_wave->WAVE_BGM_RANKING);
		break;

	default:
		assert(false);
		break;
	}
}

void CSoundManager::Play()
{
	if (CApplication::GetInput()->GetkeyboardTrigger(DIK_8))
	{
		m_pSound_wave->Play(m_pSound_wave->WAVE_SE_D, m_pSound_wave->GetCpounter());
		m_pSound_wave->SetVolume(m_pSound_wave->WAVE_SE_D, 0.5f);
		m_pSound_wave->SetCounter(1);
	}

	if (CApplication::GetInput()->GetkeyboardPress(DIK_UP))
	{
		m_pSound_wave->UpVolumeAll(0.1f);
	}

	else if (CApplication::GetInput()->GetkeyboardPress(DIK_DOWN))
	{
		m_pSound_wave->DownVolumeAll(0.1f);
	}

	else if (CApplication::GetInput()->GetkeyboardPress(DIK_O))
	{
		m_pSound_wave->UpPitcheAll(0.01f);
	}

	else if (CApplication::GetInput()->GetkeyboardPress(DIK_P))
	{
		m_pSound_wave->DownPitcheAll(0.01f);
	}
}

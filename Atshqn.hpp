// ��}�d�S �V�^ATS
// Copyright (C) 2009 Unicorn

#ifndef ATS_HQNATS_HPP_INCLUDED
#define ATS_HQNATS_HPP_INCLUDED

#include "stdafx.h"

#define SIGNAL_R 0 // 0
#define SIGNAL_YY 1 // 30
#define SIGNAL_Y 2 // 50
#define SIGNAL_YG 3 // 70
#define SIGNAL_G 4 // 115
#define SIGNAL_S 5 // S70
#define SIGNAL_N 7 // N

#define SPEED_R 0 // R
#define SPEED_YY 30+1 // YY
#define SPEED_Y 50+1 // Y
#define SPEED_YG 70+1 // YG
#define SPEED_S 70+1 // S1
#define SPEED_N 0 // N

#define LIMIT_F 0 // FREERUN / 15Hz
#define LIMIT_80 1 // 80km/h / 50.5Hz
#define LIMIT_70 2 // 70km/h / 20Hz
#define LIMIT_50 3 // 50km/h / 40Hz
#define LIMIT_30 4 // 30km/h / 80Hz
#define LIMIT_20 5 // 20km/h / 0Hz NOSIGNAL
#define LIMIT_20R 6 // 20km/h + OVEREB / 30Hz

#define ATSEB_NONE 0 // ATS�t���[
#define ATSEB_LIMIT 1 // ATS������ɉ�
#define ATSEB_STOP 2 // ATS��Β�~

#define MAX_SPEED 115+1 // �ō����x

#define IND_C 0 // ����
#define IND_0 1 // 0
#define IND_20 2 // 20
#define IND_30 3 // 30
#define IND_50 4 // 50
#define IND_70 5 // 70
#define IND_80 6 // 80
#define IND_F 7 // F
#define IND_R50 8 // ��50<�_��>
#define IND_R70 9 // ��70<�_��>
#define IND_R80 10 // ��80<�_��>
#define IND_RF 11 // ��F<�_��>
#define IND_P 12 // P

class CHqn
{
private:
	int m_door; // �h�A���
	int m_signal; // �M������
	int m_stepA; // ������A�_�̏��
	int m_stepS; // ������S�_�̏��
	int m_flat15; // �������[�h15km/h�ƍ�

	int m_hpat; // �����p�^�[�����
	int m_lpat; // �ᑬ�p�^�[�����
	int m_limit; // �VA�_�������

	float m_DistHp; // �����p�^�[���~���܂ł̋���[m]
	float m_DistLp; // �ᑬ�p�^�[���~���܂ł̋���[m]

	int m_result_sig; // �M���ƍ��̌���
	int m_result_lim; // �VA�_�ƍ��̌���

	int m_leaveAccept; // �o�����F���}
	int m_leaveAcceptTime; // �o�����F���}�܂ł̎���
	int m_tmrLeaveAccept; // �o�����F���}�^�C�}�[

	int m_beginPattern; // �p�^�[������
	int m_confirmBuzz; // �m�F���[�h�u�U�[
	int m_replaceSw; // �����X�C�b�`

	// �o�����F���}�^�C�}�[
	int LeaveAcceptTimer()
	{
		int is_keep = 1;

		if(*Time > m_tmrLeaveAccept)
		{
			is_keep = 0; // ���Z�b�g����
		}

		return is_keep;
	}

	// �\���������Z�b�g����
	void ResetIndicator()
	{
		Indicator = 0; // �\����V�t�g
		Ats_0 = 0; // 0
		Ats_20 = 0; // 20
		Ats_30 = 0; // 30
		Ats_50 = 0; // 50
		Ats_70 = 0; // 70
		Ats_80 = 0; // 80
		Ats_F = 0; // F
		Ats_R50 = 0; //��50<�_��>
		Ats_R70 = 0; // ��70<�_��>
		Ats_R80 = 0; // ��80<�_��>
		Ats_RF = 0; // ��F<�_��>
		Ats_P = 0; // P
		Ats_N = 0; // N
		Ats_HP = 0; // HP
	}

public:
	int EmgBrake; // ���m�b�`
	int SvcBrake; // ��p�ő�m�b�`

	int *BrakeNotch; // �u���[�L�m�b�`
	int *Reverser; // ���o�[�T
	int *Time; // ���ݎ���[s]
	float *TrainSpeed; // ���x�v�̑��x[km/h]
	int *DeltaT; // �t���[������[flame/ms]

	int AtsBrake; // ATS�u���[�L

	int Indicator; // �\����V�t�g(0�`12)
	// ����-0-20-30-50-70-80-F-��50-��70-��80-��F-P(�Ԃł͓_��)

	int Ats_P; // P
	int Ats_0; // 0
	int Ats_20; // 20
	int Ats_30; // 30
	int Ats_50; // 50
	int Ats_R50; //��50<�_��>
	int Ats_70; // 70
	int Ats_R70; // ��70<�_��>
	int Ats_80; // 80
	int Ats_R80; // ��80<�_��>
	int Ats_F; // F
	int Ats_RF; // ��F<�_��>
	int Ats_N; // N
	int Ats_HP; // HP

	int Confirm; // �m�F
	int Replace; // ����

	int BeginPattern; // �p�^�[������
	int ConfirmBuzz; // �m�F���[�h�u�U�[
	int SpeedOverBuzz; // ���x���߃u�U�[
	int ReplaceSw; // �����X�C�b�`

	CHqn()
	{
	}

	virtual ~CHqn()
	{
	}

	// Initalize�Ŏ��s���܂�
	void InitHqn()
	{
		AtsBrake = 0;

		m_door = 0; // �h�A���
		m_signal = 0;
		m_stepA = m_stepS = 0;
		m_flat15 = 0;
		m_hpat = 0;
		m_lpat = 0;
		m_limit = 0;
		m_result_sig = ATSEB_NONE;
		m_result_lim = ATSEB_NONE;
		m_leaveAcceptTime = 10000; // �o�����F���}�^�C�}�[
		m_beginPattern = ATS_SOUND_STOP;
		m_confirmBuzz = ATS_SOUND_STOP;
		m_replaceSw = ATS_SOUND_STOP;
	}

	// Elapse�Ŏ��s���܂�
	void RunHqn()
	{
		float speed = fabsf(*TrainSpeed); // ���x�̐�Βl[km/h]
		//float def = speed / 3600 * *DeltaT; // 1�t���[���œ���������(��Βl)[m]
		float def = *TrainSpeed / 3600 * *DeltaT; // 1�t���[���œ���������(��Βl)[m]
		// 2012/08/14 �����̌v�Z���@�ύX ���x�̐�Βl���g��Ȃ�����

		int blink = (*Time % 1000) / 500; // �\�����_��(0.5s)

		// �M���ɂ��ƍ�
		switch(m_signal)
		{
		case SIGNAL_G: // �t���[����
			if(!m_stepA) // A�_�łȂ�
			{
				if(speed > MAX_SPEED){m_result_sig = ATSEB_LIMIT;}
				else{m_result_sig = ATSEB_NONE;}
				break;
			}
		case SIGNAL_YG: // 70
			if(speed > SPEED_YG){m_result_sig = ATSEB_LIMIT;}
			else{m_result_sig = ATSEB_NONE;}
			break;
		case SIGNAL_Y: // 50
			if(!m_stepA || !m_stepS) // A�_�S�_�łȂ�
			{
				if(speed > SPEED_Y){m_result_sig = ATSEB_LIMIT;}
				else{m_result_sig = ATSEB_NONE;}
				break;
			}
		case SIGNAL_YY: // 30
			if(!m_stepS) // S�_�łȂ�
			{
				if(speed > SPEED_YY){m_result_sig = ATSEB_STOP;}
			}
			else // S�_20
			{
				if(speed > 20){m_result_sig = ATSEB_STOP;}
			}
			break;
		case SIGNAL_S: // 70
			if(speed > SPEED_S){m_result_sig = ATSEB_LIMIT;}
			else{m_result_sig = ATSEB_NONE;}
			break;
		case SIGNAL_N: // N
		case SIGNAL_R: // 0
		default:
			if(speed > 0){m_result_sig = ATSEB_STOP;}
			break;
		}

		// �����p�^�[���ɂ��ƍ�
		if(m_hpat)
		{
			m_DistHp -= def; // �c�苗�������Z����
			float pattern = speed * speed / 19.5F; // �p�^�[�����x
			if(pattern >= m_DistHp){m_result_sig = ATSEB_LIMIT;} // �u���[�L����
			else{m_result_sig = ATSEB_NONE;} // ������ɉ�

			// HP�͐ݒ苗��598m��8�����s(478.4m/-119.6m)����~���m�Ń��Z�b�g
			if(m_DistHp < 119.6F && m_DistHp >= 10.0F && speed == 0)
			{
				m_hpat = 0;
			}
		}

		// �ᑬ�p�^�[���ɂ��ƍ�
		if(m_lpat)
		{
			m_DistLp -= def; // �c�苗�������Z����
			float pattern = speed * speed / 19.5F; // �p�^�[�����x
			if(pattern >= m_DistLp){m_result_sig = ATSEB_STOP;} // �u���[�L����
		}

		// �VA�_�ɂ��ƍ�
		switch(m_limit)
		{
		case LIMIT_20R:
			if(speed > 20+1){m_result_lim = ATSEB_STOP;}
			break;
		case LIMIT_20:
			if(speed > 20+1){m_result_lim = ATSEB_LIMIT;}
			else{m_result_lim = ATSEB_NONE;}
			break;
		case LIMIT_30:
			if(speed > 30+1){m_result_lim = ATSEB_LIMIT;}
			else{m_result_lim = ATSEB_NONE;}
			break;
		case LIMIT_50:
			if(speed > 50+1){m_result_lim = ATSEB_LIMIT;}
			else{m_result_lim = ATSEB_NONE;}
			break;
		case LIMIT_70:
			if(speed > 70+1){m_result_lim = ATSEB_LIMIT;}
			else{m_result_lim = ATSEB_NONE;}
			break;
		case LIMIT_80:
			if(speed > 80+1){m_result_lim = ATSEB_LIMIT;}
			else{m_result_lim = ATSEB_NONE;}
			break;
		case LIMIT_F:
		default:
			break;
		}

		// �\���������Z�b�g
		ResetIndicator();

		// �M���ɂ��\����
		switch(m_signal)
		{
		case SIGNAL_G:
			if(m_hpat) // �����p�^�[��
			{
				if(!m_door || m_DistHp < 10.0F) // �I�[�o�[��N�Ɉڍs
				{
					Indicator = IND_C;
					Ats_N = m_leaveAccept; // N
				}
				else // ��F
				{
					Indicator = blink ? IND_RF : IND_C;
					Ats_RF = 1;
					Ats_HP = blink ? 1: 0; // HP
				}
				break;
			}
			else if(!m_stepA) // �t���[����(A�_�łȂ�)
			{
				Indicator = IND_F;
				Ats_F = 1;
				break;
			}
		case SIGNAL_YG: // 70
			Indicator = IND_70;
			Ats_70 = 1;
			break;
		case SIGNAL_Y: // 50
			if(!m_stepA || !m_stepS) // A�_�S�_�łȂ�
			{
				Indicator = IND_50;
				Ats_50 = 1;
				break;
			}
		case SIGNAL_YY: // 30
			if(!m_stepS) // S�_�łȂ�
			{
				Indicator = IND_30;
				Ats_30 = 1;
			}
			else // 20
			{
				if(m_lpat) // �ᑬ�p�^�[��
				{
					Indicator = IND_P; // P
					Ats_P = 1;
				}
				else
				{
					Indicator = IND_20;
					Ats_20 = 1;
				}
			}
			break;
		case SIGNAL_S: // 70
			Indicator = IND_70;
			Ats_70 = 1;
			break;
		case SIGNAL_N: // N
			Indicator = IND_C;
			Ats_N = 1;
			break;
		case SIGNAL_R: // 0
		default:
			Indicator = IND_0;
			Ats_0 = 1;
			break;
		}

		// �VA�ƍ��ɂ��\����
		switch(m_limit)
		{
		case LIMIT_20R:
		case LIMIT_20:
			if(m_signal > SIGNAL_R)
			{
				ResetIndicator();
				Indicator = IND_20; // 20
				Ats_20 = 1;
			}
			break;
		case LIMIT_30:
			if(m_signal > SIGNAL_YY || (m_signal == SIGNAL_Y && !m_stepA) || !m_stepS)
			{
				ResetIndicator();
				Indicator = IND_30; // ��30
				Ats_30 = 1;
			}
			break;
		case LIMIT_50:
			if(m_signal > SIGNAL_Y || (m_signal == SIGNAL_Y && !m_stepA) || !m_stepS)
			{
				ResetIndicator();
				Indicator = blink ? IND_R50 : IND_C; // ��50
				Ats_R50 = blink ? 1 : 0;
			}
			break;
		case LIMIT_70:
			if(m_signal > SIGNAL_YG || (m_signal == SIGNAL_G && !m_stepA))
			{
				ResetIndicator();
				Indicator = blink ? IND_R70 : IND_C; // ��70
				Ats_R70 = blink ? 1 : 0;
			}
			break;
		case LIMIT_80:
			if(m_signal == SIGNAL_G && !m_stepA)
			{
				ResetIndicator();
				Indicator = blink ? IND_R80 : IND_C; // ��80
				Ats_R80 = blink ? 1 : 0;
			}
			break;
		case LIMIT_F:
		default:
			break;
		}

		// �������[�h
		if(Replace) // 30
		{
			m_result_sig = ATSEB_NONE;
			ResetIndicator();

			if(m_flat15)
			{
				if(speed > 15+1){m_result_sig = ATSEB_STOP;}

				Indicator = IND_20;
				Ats_20 = 1;
			}
			else
			{
				if(speed > 30+1){m_result_sig = ATSEB_STOP;}

				Indicator = IND_30;
				Ats_30 = 1;
			}
		}

		// �m�F���[�h
		if(Confirm) // 20
		{
			m_result_sig = ATSEB_NONE;
			ResetIndicator();

			if(speed > 20+1)
			{
				m_result_sig = ATSEB_STOP;
			}

			Indicator = IND_20;
			Ats_20 = 1;
		}

		// ATS�u���[�L�Ɍ��ʂ��X�V
		AtsBrake = max(m_result_sig, m_result_lim);

		// �o�����F���}�^�C�}�[
		if(!m_door && m_leaveAccept) // �����p�^�[������N
		{
			m_leaveAccept = LeaveAcceptTimer();
			if(m_leaveAccept == 0)
			{
				m_hpat = 0; // �����p�^�[�������Z�b�g
			}
		}

		// ���x���߃u�U�[
		if(AtsBrake){SpeedOverBuzz = ATS_SOUND_PLAYLOOPING;}
		else{SpeedOverBuzz = ATS_SOUND_STOP;}

		BeginPattern = m_beginPattern; // �p�^�[������
		m_beginPattern = ATS_SOUND_CONTINUE;
		ConfirmBuzz = m_confirmBuzz; // �m�F���[�h�u�U�[
		m_confirmBuzz = ATS_SOUND_CONTINUE;
		ReplaceSw = m_replaceSw; // �����X�C�b�`
		m_replaceSw = ATS_SOUND_CONTINUE;
	}

	// �h�A��Ԃ��ς�������Ɏ��s���܂�
	void ChangedDoorState(int state)
	{
		m_door = state;

		if(state > 0) // ��
		{
			m_leaveAccept = 0;
		}
		else // �J��
		{
			m_tmrLeaveAccept = *Time + m_leaveAcceptTime;
		}
	}

	// SetBrake�Ŏ��s���܂�
	void SetBrakeNotch(int notch)
	{
		if(notch == EmgBrake)
		{
			Confirm = 0;
		}
	}

	// ATS���Z�b�g������ꂽ���Ɏ��s���܂�
	void AtsReset()
	{
		if(*BrakeNotch == EmgBrake)
		{
			AtsBrake = ATSEB_NONE;
			m_result_sig = m_result_lim = ATSEB_NONE;
		}
	}

	// �m�F���[�h������ꂽ���Ɏ��s���܂�
	void ConfirmAts(void)
	{
		if(*BrakeNotch == EmgBrake)
		{
			Confirm = 1;
			m_confirmBuzz = ATS_SOUND_PLAY;
		}
	}

	// �����X�C�b�`������ꂽ���Ɏ��s���܂�
	void ReplaceAts()
	{
		if(*BrakeNotch == EmgBrake && (m_signal == SIGNAL_S || Replace)) // �����M�����������̂Ƃ�
		{
			Replace = Replace ? 0 : 1;
			m_replaceSw = ATS_SOUND_PLAY;

			//if(Replace == 0) // �����؂ɂ���
			//{
			//	m_flat15 = 0; // �t���b�g15
			//}
		}
	}

	// �M���������ς�������Ɏ��s���܂�
	void Receive(int signal)
	{
		m_signal = signal; // �M������
		m_stepA = m_stepS = 0; // �������n�_�̏�����
		m_hpat = m_lpat = 0; // �����p�^�[���ƒᑬ�p�^�[���̃��Z�b�g

		// 2012/06/05 �����I�ɔp�~
		//if(signal == SIGNAL_S) // �����M�����󂯂��Ƃ��m�F���[�h�𖳌���
		//{
		//	Confirm = 0;
		//}
	}

	// ��I��ʉ߂������Ɏ��s���܂�
	void SetTrainData(int data)
	{
		// ��I�ɂ��ō����x�̐ݒ�
		// ���i�K�ł� 115km/h ���ō����x�Ƃ��ČŒ�
	}

	// �o�����F���}�^�C�}�[�ݒ��ʉ߂������Ɏ��s���܂�
	void PassedAcceptTimer(int data)
	{
		if(*TrainSpeed > 0)
		{
			m_leaveAcceptTime = data;
		}
	}

	// A�_��ʉ߂������Ɏ��s���܂�
	void PassedBeaconA(int signal)
	{
		if(*TrainSpeed > 0)
		{
			if(m_signal == SIGNAL_G && signal == SIGNAL_Y || m_signal == SIGNAL_Y && signal == SIGNAL_R)
			{
				m_stepA = 1;
			}
		}
	}

	// S�_��ʉ߂������Ɏ��s���܂�
	void PassedBeaconS(int signal, int data)
	{
		if(*TrainSpeed > 0)
		{
			if(m_signal == SIGNAL_S && (signal == SIGNAL_N || data > 0)) // �������[�h
			{
				m_flat15 = 1;
			}
			else if((m_signal == SIGNAL_Y || m_signal == SIGNAL_YY) && signal == SIGNAL_R)// �ʏ�
			{
				m_stepS = 1;
			}
		}
	}

	// HP�_��ʉ߂������Ɏ��s���܂�
	void PassedBeaconHP(int signal, int data)
	{
		if(*TrainSpeed > 0)
		{
			if(signal == SIGNAL_G) // �Ώƕǂ�G�����̏ꍇ
			{
				if(data != 1 && m_hpat == 0){
					m_hpat = 1;
					m_DistHp = 598; // 588[m]�n�_ + 10[m]�]�T
					m_beginPattern = ATS_SOUND_PLAY; // �p�^�[������
					m_leaveAccept = 1; // �o�����F���}

					if(data)
					{
						m_leaveAcceptTime = data; // �o�����F���}�^�C�}�[
					}
				}
				else if(data == 1) // �␳�p���[�v�R�C��
				{
					m_DistHp = 122; // 112[m]�n�_ + 10[m]�]�T
				}
			}
		}
	}

	// LP�_��ʉ߂������Ɏ��s���܂�
	void PassedBeaconLP(int signal)
	{
		if(*TrainSpeed > 0)
		{
			if(m_stepS == 1) // ��������S�_���L��
			{
				m_lpat = 1;
				m_DistLp = 31; // 31[m]�n�_
			}
		}
	}

	// �VA�_��ʉ߂������Ɏ��Ɏ��s���܂�
	void PassedBeaconA2(int data)
	{
		if(*TrainSpeed > 0)
		{
			if(data == 0 || m_limit < data) // ���Z�b�g���ƍ����x�����̂Ƃ�
			{
				m_limit = data;
				if(data){m_beginPattern = ATS_SOUND_PLAY;} // �p�^�[������
			}
		}
	}

};	//CHqn

#endif	// ATS_HQNATS_HPP_INCLUDED

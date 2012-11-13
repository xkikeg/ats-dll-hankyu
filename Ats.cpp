// Ats.cpp : DLL �A�v���P�[�V�����p�̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "atsplugin.h"
#include "Atshqn.hpp"
#include "Ats.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			g_hqn.BrakeNotch = &g_brakeNotch;
			g_hqn.Reverser = &g_reverser;
			g_hqn.Time = &g_time;
			g_hqn.TrainSpeed = &g_speed;
			g_hqn.DeltaT = &g_deltaT;
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

ATS_API int WINAPI GetPluginVersion()
{
	return ATS_VERSION;
}

ATS_API void WINAPI SetVehicleSpec(ATS_VEHICLESPEC vehicleSpec)
{
	g_svcBrake = vehicleSpec.BrakeNotches;
	g_emgBrake = g_svcBrake + 1;

	g_hqn.EmgBrake = g_emgBrake;
	g_hqn.SvcBrake = vehicleSpec.AtsNotch;
}

ATS_API void WINAPI Initialize(int brake)
{
	g_hqn.InitHqn();
	g_speed = 0;
}

ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vehicleState, int *panel, int *sound)
{
	g_deltaT = vehicleState.Time - g_time;
	g_time = vehicleState.Time;
	g_speed = vehicleState.Speed;

	g_hqn.RunHqn();

	// �n���h���o��
	if(g_hqn.AtsBrake)
	{
		g_output.Brake = g_emgBrake;
	}
	else
	{
		g_output.Brake = g_brakeNotch;
	}
	if(g_pilotlamp)
	{
		g_output.Reverser = g_reverser;
	}
	else
	{
		g_output.Reverser = 0;
	}
	if(g_hqn.Ats_N)
	{
		// 2012/08/14 �M��N�̂Ƃ� �͍s�ł��Ȃ��悤�ɂ���
		g_output.Power = 0;
	}
	else
	{
		g_output.Power = g_powerNotch;
	}
	g_output.ConstantSpeed = ATS_CONSTANTSPEED_CONTINUE;

	// �p�l���o��
	panel[0] = g_hqn.Indicator;

	panel[10] = g_hqn.Ats_0;
	panel[11] = g_hqn.Ats_20;
	panel[12] = g_hqn.Ats_30;
	panel[13] = g_hqn.Ats_50;
	panel[14] = g_hqn.Ats_70;
	panel[15] = g_hqn.Ats_80;
	panel[16] = g_hqn.Ats_F;

	panel[22] = g_hqn.Ats_R50;
	panel[23] = g_hqn.Ats_R70;
	panel[24] = g_hqn.Ats_R80;
	panel[25] = g_hqn.Ats_RF;
	panel[26] = g_hqn.Ats_P;

	panel[30] = g_hqn.Ats_N;
	panel[31] = g_hqn.Ats_HP;

	panel[35] = g_hqn.Confirm;
	panel[36] = g_hqn.Replace;

	panel[50] = vehicleState.BcPressure < 100 ? 10 : vehicleState.BcPressure / 100; // Bc100�̌�
	panel[51] = vehicleState.BcPressure < 10 ? 0 : vehicleState.BcPressure / 10 - (panel[50] % 10) * 10; // Bc10�̌�

	// �T�E���h�o��
	sound[0] = g_hqn.BeginPattern; // �p�^�[������
	sound[1] = g_hqn.ConfirmBuzz; // �m�F���[�h�u�U�[
	sound[2] = g_hqn.SpeedOverBuzz; // ���x���ߎ��u�U�[
	sound[5] = g_hqn.ReplaceSw; // �����X�C�b�`

    return g_output;
}

ATS_API void WINAPI SetPower(int notch)
{
	g_powerNotch = notch;
}

ATS_API void WINAPI SetBrake(int notch)
{
	g_brakeNotch = notch;

	g_hqn.SetBrakeNotch(notch);
}

ATS_API void WINAPI SetReverser(int pos)
{
	g_reverser = pos;
}

ATS_API void WINAPI KeyDown(int atsKeyCode)
{
	switch(atsKeyCode)
	{
	case ATS_KEY_B1: // ATS���Z�b�g(Home)
		g_hqn.AtsReset();
		break;
	case ATS_KEY_B2: // �m�F�{�^��(End)
		g_hqn.ConfirmAts();
		break;
	case ATS_KEY_C1: // �����X�C�b�`(PgUp)
		g_hqn.ReplaceAts();
		break;
	}
}

ATS_API void WINAPI KeyUp(int atsKeyCode)
{
}

ATS_API void WINAPI HornBlow(int hornType)
{
}

ATS_API void WINAPI DoorOpen()
{
	g_pilotlamp = false;

	g_hqn.ChangedDoorState(0);
}

ATS_API void WINAPI DoorClose()
{
	g_pilotlamp = true;

	g_hqn.ChangedDoorState(1);
}

ATS_API void WINAPI SetSignal(int signal)
{
	g_hqn.Receive(signal);
}

ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA beaconData){

	switch(beaconData.Type)
	{
	case ATS_BEACON_SET: // ��Ԏ�ʑI�ʑ��u
		g_hqn.SetTrainData(beaconData.Optional);
		break;
	case ATS_BEACON_ACCEPT: // �o�����F���}
		// 2012/06/08 �����I�ɔp�~
		//g_hqn.PassedAcceptTimer(beaconData.Optional);
		break;
	case ATS_BEACON_A: // ����A�_/�V�^B1�_
		g_hqn.PassedBeaconA(beaconData.Signal);
		break;
	case ATS_BEACON_S: // ����S�_/�V�^B2�_/����15�_
		g_hqn.PassedBeaconS(beaconData.Signal, beaconData.Optional);
		break;
	case ATS_BEACON_HP: // �V�^HP�_
		g_hqn.PassedBeaconHP(beaconData.Signal, beaconData.Optional);
		break;
	case ATS_BEACON_LP: // �V�^B3�_(LP�_)
		g_hqn.PassedBeaconLP(beaconData.Signal);
		break;
	case ATS_BEACON_A2: // �V�^A�_
		g_hqn.PassedBeaconA2(beaconData.Optional);
		break;
	}
}

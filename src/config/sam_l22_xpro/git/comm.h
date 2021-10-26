

#ifndef GIT_COMMON_H
#define GIT_COMMON_H


//******************************************************************************
//  Defined
#define 	RADAR_INFO_SKIP_TM 				15		//second


//******************************************************************************


//******************************************************************************
//  Global

//	Radar 		==================================================================
extern	int 		flg_Radar_Info_noSkip;
extern 	int 		Radar_ReStart_state;
extern 	TIMER*	tm_Radar_ReStart_state;


//******************************************************************************
//  Function
UINT16  Get_Kermit_CRC16( UINT8* dataPtr, UINT32 length );
UINT16  Get_ModBus_CRC16( UINT8* dataPtr, UINT32 length );


//==============================================================================
void 	TimerF_Radar_ReStart_M0_PWon( void );
void 	TimerF_Radar_ReStart( void );


#endif // GIT_COMMON_H


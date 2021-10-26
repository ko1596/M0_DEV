

// *****************************************************************************
//  ATSAML22N18A
//    Embedded Flash        0x00000000    0x00400000   256K
//    Embedded RWW section  0x00400000    0x00402000    8K
//    Embedded SRAM         0x20000000    0x20008000    32K
//    Peripheral Bridge A   0x40000000 64 64 64
//    Peripheral Bridge B   0x41000000 64 64 64
//    Peripheral Bridge C   0x42000000 64 64 64
//    IOBUS 0x60000000
// *****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________

//#ifndef ALL_DEFINE_H
//#define ALL_DEFINE_H





//******************************************************************************
//  System Defined
//******************************************************************************
//  Defined
#define   UINT8       uint8_t
#define   UINT16      uint16_t
#define   UINT32      uint32_t

#define   FAILURE     0
#define   SUCCESS     1


//==============================================================================
//	Device Version
#define 	M0_RADAR_VER_30_210930  		1  		//	FW03000102



//==============================================================================
//  Device SubType of UART CMD
//==============================================================================
#define 	SUBTYPE_RTC								0x01
#define 	SUBTYPE_MGC3130						0x11
#define 	SUBTYPE_ADC								0x12
#define 	SUBTYPE_G_SENSOR					0x13

#define 	SUBTYPE_RADAR_A						0x21
#define 	SUBTYPE_RADAR_B						0x22
#define 	SUBTYPE_LIDAR							0x28

#define 	SUBTYPE_TEMPERATURE				0x30

#define 	SUBTYPE_PW_METER0					0x38
#define 	SUBTYPE_PW_METER1					0x39
#define 	SUBTYPE_PW_METER2					0x3A
#define 	SUBTYPE_PW_METER3					0x3B

#define 	SUBTYPE_PW_BAT						0x40
#define 	SUBTYPE_PW_BAT_A					0x41
#define 	SUBTYPE_PW_BAT_B					0x42

#define 	SUBTYPE_TLSAM							0x71

#define 	SUBTYPE_ALL								0xFF


//==============================================================================
//  I2C
//==============================================================================
typedef struct _i2c_interface_{
	UINT8 		i2c_addr;

	UINT8     STATE;
  UINT16    PTR;
  UINT16 		i2c_delay;
}I2C_INTERFACE;



//==============================================================================
//  UART
//==============================================================================
typedef struct _uart_fifo {
    UINT8*  buffer; // used as a ring buffer
    UINT16  front;          // Head index of queue
    UINT16  tail;         // next new index of queue
    UINT8   buffull;        // =1, queue full
    UINT8   NC1;          // No used
    UINT8   NC2;          // No used
    UINT8   NC3;          // No used
}UART_FIFO;

typedef struct _uart_interface_{
  UART_FIFO rx;
  UART_FIFO tx;
  UINT16    PTR;
  UINT16    LENGTH;
  UINT8     STATE;
  UINT8     CMD;
  UINT16    CRC16;
  UINT8*    TrData;
}UART_INTERFACE;


//==============================================================================
//  RTC
//==============================================================================
typedef struct 	{
  UINT8   Year;
  UINT8   Month;
  UINT8   Day;
  UINT8   WeekDay;

  UINT8   Hour;
  UINT8   Minute;
  UINT8   Second;  
  UINT8   nc;
}M0_RTC_TIME_FRAME;



//==============================================================================
//  Chili2S
//==============================================================================
typedef struct {
	M0_RTC_TIME_FRAME  	rtc;

	UINT16  	panid;
	UINT16  	sAddr;

	UINT8  		rf_channel;
	UINT8  		nc01;
	UINT8  		nc11;

	UINT8 		fw_ver[48];
}CHILI2S_INFO_FRAME;





//==============================================================================
//  Tr - Data
//==============================================================================
//==============================================================================



//  System Data   ==============================================================
typedef struct  {
  UINT8           FW_ver[32];
  M0_RTC_TIME_FRAME  mcu_RTC;

  //  TEST !!!
  UINT32 	sysTick;
  UINT32  TstCnt;   //  TEST
  UINT32  TstBuf_t; 
  UINT32  uartM0_RxCnt;

  CHILI2S_INFO_FRAME  	Chili2S_info;
}M0_SYSTEM_INFO;





//==============================================================================
//  device status
//==============================================================================

//  DC Power Meter 		----------------------------------------------------------
//	LTC2944
typedef struct  {
	UINT32 								bat_v;
	UINT32 								bat_i;
	UINT32 								temp;	
	//M0_RTC_TIME_FRAME  		mcu_RTC;
}M0_PW_METER_DATA_FRAME;

//  ADC   ----------------------------------------------------------------------
#define 	PW_EN_BAT_A			0x01		//	0001
#define 	PW_EN_BAT_B			0x02		//	0010
#define 	PW_EN_DC_IN			0x04		//	0100
#define 	PW_EN_SOLAR			0x08		//	1000

typedef struct  {
	UINT32 V_batA;
	UINT32 V_batB;
	UINT32 V_Solar;
	UINT32 V_DC;

	UINT32 adc0;
	UINT32 adc1;
	UINT32 adc2;
	UINT32 adc3;

	UINT32 pw_EN;		//	bit0,	Bat_A
									//	bit1,	Bat_B
									//	bit2,	DC_In
									//	bit3,	Solar

	M0_PW_METER_DATA_FRAME 		pw_meter;

	M0_RTC_TIME_FRAME  mcu_RTC;
}M0_POWER_DATA_FRAME;

//  LM75-Sensor   --------------------------------------------------------------
typedef struct  {
	UINT32 alarm_temp_H;
	UINT32 alarm_temp_L;
}M0_TEMP_ALARMM_FRAME;

typedef struct  {
	UINT32 								temp0; 		//	xxx.xx;  negative : 0x80000000 true
	M0_TEMP_ALARMM_FRAME	alarm;
	M0_RTC_TIME_FRAME  		mcu_RTC;
}M0_TEMP_DATA_FRAME;


//  MGC3130   ------------------------------------------------------------------
typedef struct  {
  UINT32 mgc;
  M0_RTC_TIME_FRAME  mcu_RTC;
}M0_MGC_DATA_FRAME;












//  Radar   	------------------------------------------------------------------
#if 	M0_RADAR_VER_30_210930

	//  	RB-60P(3.0) UART Portocol_210930.pdf
	typedef struct  {
		UINT16 		radar_X;
		
		UINT16 		radar_Y;
		UINT16 		radar_L;

		UINT16 		radar_W;
		UINT16 		radar_H;

		UINT8 		Z_m;
		UINT8 		Z_p;
		UINT8 		DoA_E_m;
		UINT8 		DoA_E_p;

		UINT8 		DoA_H_m;
		UINT8 		DoA_H_p;
		UINT8 		Theta;
		UINT8 		Phi;

		UINT8 		L_R;
		UINT8 		Threshold_Boundary;
		UINT16 		Threshold_A;

		UINT16 		Threshold_B;
		UINT8  		Peak_amount;
		UINT8  		Compare_car;

		UINT8  		Compare_emp;
		UINT8  		nc01;
		UINT16 		Block_lim;
	}M0_RADAR_SET_FRAME;


	typedef struct  {
		UINT8 		Result;
		UINT8 		Current_status;
		UINT8 		Object_type;
		UINT8 		Current_amount;

		UINT16 		radar_X;
		UINT16 		radar_Y;

		UINT16 		radar_L;
		UINT16 		radar_W;

		UINT16 		radar_H;
		UINT8 		Z_m;
		UINT8 		Z_p;

		UINT8 		DoA_E_m;
		UINT8 		DoA_E_p;
		UINT8 		DoA_H_m;
		UINT8 		DoA_H_p;

		UINT8 		Theta;
		UINT8 		Phi;
		UINT8 		L_R;
		UINT8 		Threshold_Boundary;

		UINT16 		Threshold_A;
		UINT16 		Threshold_B;

		UINT8  		Peak_amount;
		UINT8  		Compare_car;
		UINT8  		Compare_emp;
		UINT8  		nc01;

		UINT16 		Block_lim;
		UINT16 		Block_index;

		UINT16 		Range_Object1;
		UINT16 		x_Object1;

		UINT16 		y_Object1;
		UINT16 		z_Object1;

		UINT16 		Power_Object1;
		UINT16 		Range_Object2;

		UINT16 		x_Object2;
		UINT16 		y_Object2;

		UINT16 		z_Object2;
		UINT16 		Power_Object2;
		UINT16 		Range_Object3;

		UINT16 		x_Object3;
		UINT16 		y_Object3;

		UINT16 		z_Object3;
		UINT16 		Power_Object3;
	}M0_RADAR_DATA_FRAME;

	typedef struct  {
		UINT8 								FW_version[4];
		M0_RADAR_DATA_FRAME		data;

		UINT8 	pre_Result;
		UINT8 	pre_Object_type;
		UINT8 	car;  				//	20211014-031270
		UINT8 	pre_car; 			//	20211014-031270
        
        UINT8   status;
        UINT8   blank0;
        UINT8   blank1;
        UINT8   blank2;

		M0_RTC_TIME_FRAME  		mcu_RTC;
	}M0_RADAR_FRAME;


#else 	//#if 	M0_RADAR_VER_30_210930

	//	Radar-RB-60P(台灣版) UART Portocol_210609
	//	UINT8 L_R :		=0, Right side
	//								=1, Left side
	typedef struct  {
		UINT16 		radar_X;
		
		UINT16 		radar_Y;
		UINT16 		radar_L;

		UINT16 		radar_W;
		UINT16 		radar_H;

		UINT8 		Theta;
		UINT8 		Phi;

		UINT8 		L_R;
		UINT8 		nc[9]; 			// 	"210610-020Cea"
	}M0_RADAR_SET_FRAME;


	//	"210610-020Ce0" 		Radar-RB-60P(台灣版) UART Portocol_210609 	................
	typedef struct  {
		UINT16 		car_change;
		UINT16 		obj_position_X;

		UINT16 		obj_position_Y;
		UINT16 		obj_position_Z;

		UINT16 		obj_distance_R;
		UINT16 		radar_X;
		
		UINT16 		radar_Y;
		UINT16 		radar_L;

		UINT16 		radar_W;
		UINT16 		radar_H;

		UINT8 		parking_status;
		UINT8 		CarChange_status;
		UINT8 		obj_type;
		UINT8 		Theta;

		UINT8 		Phi;
		UINT8 		L_R;
		
		//  M0 used
		UINT8 		pre_parking_status;		//"   210524-020Be0"
		UINT8 		pre_car_change;				//"...210608-020Cc0"

		UINT8 		Reserved_01[4];

		UINT16 		power;
		UINT8  		recordPos_X;
		UINT8  		recordPos_Y;

		UINT8  		recordPos_Z;
		UINT8  		record_Distance;
		UINT16  	record_power;

		UINT16  	motion_index1;
		UINT16  	motion_index2;

		UINT16  	block_index;
		UINT16  	nc01;	
	}M0_RADAR_DATA_FRAME;

	typedef struct  {
		UINT8 								FW_version[4];
		M0_RADAR_DATA_FRAME		data;

		UINT8  	status; 		//	=0. Camera Captuer
												//	=1, Captuer Delete
		UINT8 	nc01;
		UINT8 	nc02;
		UINT8 	nc03;

		M0_RTC_TIME_FRAME  		mcu_RTC;
	}M0_RADAR_FRAME;

#endif 	//#if 	M0_RADAR_VER_30_210930















//  Lidar  from Chili2S 	------------------------------------------------------
typedef struct  _vos_lidar{
	UINT16  	Distance;
	UINT16  	Strength;

	UINT16  	Temp;
	UINT16  	nc1;
}VOS_LIDAR_FRAME;

typedef struct  _parkmeter_lidar_msg{
	UINT16  	srcAddr;
	UINT16  	Dist;

	VOS_LIDAR_FRAME  	lidarData;
	VOS_LIDAR_FRAME  	pre_lidarData;

	UINT8  	car;
	UINT8  	pre_car;
	UINT8  	shoot;
	UINT8  	pre_shoot;

	UINT8  	parking_fee_status;
	UINT8  	nc01;
	UINT8  	nc02;
	UINT8  	nc03;
	
	M0_RTC_TIME_FRAME 	mcu_RTC;
}PARKMETER_VOS_MSG_FRAME;


//  G-Sensor   -----------------------------------------------------------------
// 	STK8BA53
typedef struct _icm20602_data_frame_{
	//	mg
	UINT32	acc_X;
	UINT32	acc_Y;
	UINT32	acc_Z;
	
	UINT8		acc_wom_X;
	UINT8		acc_wom_Y;
	UINT8		acc_wom_Z;
	
	UINT8 	flg_INT;

	UINT32	acc_INT_X;
	UINT32	acc_INT_Y;
	UINT32	acc_INT_Z;

}STK8BA53_DATA_FRAME;

typedef struct  {
	STK8BA53_DATA_FRAME 	stk8ba53;
	M0_RTC_TIME_FRAME  		mcu_RTC;
}M0_G_SENSOR_FRAME;



//  TL-SAM   	------------------------------------------------------------------
typedef struct  {
	UINT8 								FW_version[2];
	UINT16 								status;
	UINT8 								name[64];
	UINT32 								dataLength;
	UINT8 								data[1600];
}M0_TLSAM_FRAME;





//------------------------------------------------------------------------------
//  M0 ALarm A53  	------------------------------------------------------------
typedef struct  {
	UINT32 	alarm;
	M0_RTC_TIME_FRAME  	mcu_RTC;
}M0_ALARM_A53_FRAME;


//==============================================================================
//	All devices
//	M0_ALLDEV_STATUS_FRAME   M0_AllDevStatus;
typedef struct  {
  M0_POWER_DATA_FRAME  			adc_pw;
  M0_MGC_DATA_FRAME 				mgc;
  M0_TEMP_DATA_FRAME				temperature;  
  M0_RADAR_FRAME 						radar_A;
  M0_RADAR_FRAME 						radar_B;
  M0_G_SENSOR_FRAME 				g_sensor;

  PARKMETER_VOS_MSG_FRAME 	lidar;

  M0_RTC_TIME_FRAME 				mcu_RTC;

  //  TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  UINT32    TstCnt;   //  TEST
  UINT32    TstBuf_t;
}M0_ALLDEV_STATUS_FRAME;

//#endif // ALL_DEFINE_H


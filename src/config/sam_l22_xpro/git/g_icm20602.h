

// *****************************************************************************
// 	g_icm20602.h
// 	20210603
// *****************************************************************************

#ifndef DEV_ICM20602_H
#define DEV_ICM20602_H




//******************************************************************************
//  Defined
//==============================================================================
#define 	I2C_BAUDRATE_ICM20602 				200000U
#define 	I2C_DEV_ADDR_ICM20602_SA1 		0x69 			//	1101001

#define 	ICM20602_INT_COUNT						250				//	250ms
#define 	ICM20602_ACC_WOM_DEFAULT			50	//% 		Test
//#define 	ICM20602_ACC_WOM_DEFAULT			80	//%

#define 	ICM20602_WHO_AM_I							0x12

//------------------------------------------------------------------------------
//	INT 		PC09 EIC/EXTINT[1]
#define 	ICM_INT_PORT_GROUP			2
#define 	ICM_INT_PORT_PIN				9
#define 	ICM_INT_PORT_DIR 				0x200 		//	PC09	1000000000
#define 	ICM_INT_PORT_OUT 				0x200 		//	PC09	1000000000

#define 	MGC_TS_PORT_GROUP			2
#define 	MGC_TS_PORT_PIN				8
#define 	MGC_TS_PORT_DIR 				0x100 		//	PC08	100000000
#define 	MGC_TS_PORT_OUT 				0x100 		//	PC08	100000000



//	ICM20602 	REGISTER MAP 	====================================================
#define 	ICM20602REG_XG_OFFS_TC_H 		0x04
#define 	ICM20602REG_XG_OFFS_TC_L 		0x05
#define 	ICM20602REG_YG_OFFS_TC_H 		0x07
#define 	ICM20602REG_YG_OFFS_TC_L 		0x08
#define 	ICM20602REG_ZG_OFFS_TC_H 		0x0A
#define 	ICM20602REG_ZG_OFFS_TC_L 		0x0B
#define 	ICM20602REG_SELF_TEST_X_ACCEL 		0x0D
#define 	ICM20602REG_SELF_TEST_Y_ACCEL 		0x0E
#define 	ICM20602REG_SELF_TEST_Z_ACCEL 		0x0F
#define 	ICM20602REG_XG_OFFS_USRH 		0x13
#define 	ICM20602REG_XG_OFFS_USRL 		0x14
#define 	ICM20602REG_YG_OFFS_USRH 		0x15
#define 	ICM20602REG_YG_OFFS_USRL 		0x16
#define 	ICM20602REG_ZG_OFFS_USRH 		0x17
#define 	ICM20602REG_ZG_OFFS_USRL 		0x18
#define 	ICM20602REG_SMPLRT_DIV 		0x19
#define 	ICM20602REG_CONFIG 		0x1A
#define 	ICM20602REG_GYRO_CONFIG 		0x1B
#define 	ICM20602REG_ACCEL_CONFIG 		0x1C
#define 	ICM20602REG_ACCEL_CONFIG_2 		0x1D
#define 	ICM20602REG_LP_MODE_CFG 		0x1E
#define 	ICM20602REG_ACCEL_WOM_X_THR 		0x20
#define 	ICM20602REG_ACCEL_WOM_Y_THR 		0x21
#define 	ICM20602REG_ACCEL_WOM_Z_THR 		0x22
#define 	ICM20602REG_FIFO_EN 		0x23
#define 	ICM20602REG_FSYNC_INT 		0x36
#define 	ICM20602REG_INT_PIN_CFG 		0x37
#define 	ICM20602REG_INT_ENABLE 		0x38
#define 	ICM20602REG_FIFO_WM_INT_STATUS 		0x39
#define 	ICM20602REG_INT_STATUS 		0x3A
#define 	ICM20602REG_ACCEL_XOUT_H 		0x3B
#define 	ICM20602REG_ACCEL_XOUT_L 		0x3C
#define 	ICM20602REG_ACCEL_YOUT_H 		0x3D
#define 	ICM20602REG_ACCEL_YOUT_L 		0x3E
#define 	ICM20602REG_ACCEL_ZOUT_H 		0x3F
#define 	ICM20602REG_ACCEL_ZOUT_L 		0x40
#define 	ICM20602REG_TEMP_OUT_H 		0x41
#define 	ICM20602REG_TEMP_OUT_L 		0x42
#define 	ICM20602REG_GYRO_XOUT_H 		0x43
#define 	ICM20602REG_GYRO_XOUT_L 		0x44
#define 	ICM20602REG_GYRO_YOUT_H 		0x45
#define 	ICM20602REG_GYRO_YOUT_L 		0x46
#define 	ICM20602REG_GYRO_ZOUT_H 		0x47
#define 	ICM20602REG_GYRO_ZOUT_L 		0x48
#define 	ICM20602REG_SELF_TEST_X_GYRO 		0x50
#define 	ICM20602REG_SELF_TEST_Y_GYRO 		0x51
#define 	ICM20602REG_SELF_TEST_Z_GYRO 		0x52
#define 	ICM20602REG_FIFO_WM_TH1 		0x60
#define 	ICM20602REG_FIFO_WM_TH2 		0x61
#define 	ICM20602REG_SIGNAL_PATH_RESET 		0x68
#define 	ICM20602REG_ACCEL_INTEL_CTRL 		0x69
#define 	ICM20602REG_USER_CTRL 		0x6A
#define 	ICM20602REG_PWR_MGMT_1 		0x6B
#define 	ICM20602REG_PWR_MGMT_2 		0x6C
#define 	ICM20602REG_I2C_IF 		0x70
#define 	ICM20602REG_FIFO_COUNTH 		0x72
#define 	ICM20602REG_FIFO_COUNTL 		0x73
#define 	ICM20602REG_FIFO_R_W 		0x74
#define 	ICM20602REG_WHO_AM_I 		0x75
#define 	ICM20602REG_XA_OFFSET_H 		0x77
#define 	ICM20602REG_XA_OFFSET_L 		0x78
#define 	ICM20602REG_YA_OFFSET_H 		0x7A
#define 	ICM20602REG_YA_OFFSET_L 		0x7B
#define 	ICM20602REG_ZA_OFFSET_H 		0x7D
#define 	ICM20602REG_ZA_OFFSET_L 		0x7E






//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



//******************************************************************************
//  Global

extern 	UINT8  	ICM_who_am_i;

extern 	UINT8  	flg_g_sensor_INT;
extern 	TIMER*	tm_ICM20602_INT_start;


#if  	Tst_ICM_01
	TIMER*	tm_ICM20602_Req;

	UINT32	acc_X;
	UINT32	acc_Y;
	UINT32	acc_Z;
#endif  	//#if  	Tst_ICM_01


//******************************************************************************
//  Function
void 	ICM20602_i2c_Init( void );

UINT8 	ICM20602_i2c_Write( UINT8  regAddr, UINT8* wBuf, UINT16 length );
UINT8 	ICM20602_i2c_Read( UINT8  regAddr, UINT8* wBuf, UINT16 length );

UINT8 	ICM20602_acc_Read( void );
UINT8 	ICM20602_acc_Read_INT( void );

void 	TimerF_ICM20602_INT_period( void );
void 	ICM20602_AlarmMsg( void );


#if  	Tst_ICM_01
	void 	TimerF_ICM20602_Read( void );
#endif  	//#if  	Tst_ICM_01


#endif // DEV_ICM20602_H


       //name, section, default
EM_PAR(	P_VS1 ,      1 , 0x3E ) /* 5438 */
EM_PAR(	P_VS1h,      1 , 0x15 )
EM_PAR(	P_VS2 ,      1 , 0x14 ) /* 5396 */
EM_PAR(	P_VS2h,      1 , 0x15 )
EM_PAR(	P_VSo,       1 , 0x9E ) /* 22174 */
EM_PAR(	P_VSoh,      1 , 0x56 )
EM_PAR(	P_CS1,       1 , 0xde ) /* 990 */
EM_PAR(	P_CS1h,      1 , 0x03 )
EM_PAR(	P_CS2,       1 , 0xe8 ) /* 1000 */
EM_PAR(	P_CS2h,      1 , 0x03 )
EM_PAR(	P_CSo,       1 , 0x2B ) /* 555 */
EM_PAR(	P_CSoh,      1 , 0x02 )
EM_PAR(	P_CS1_offs,  1 , 0x14 ) /* 20 */
EM_PAR(	P_CS2_offs,  1 , 0x13 ) /* 19 */
EM_PAR(	P_CSo_offs,  1 , 0x16 ) /* 22 */
EM_PAR(	P_T_U0_1,    1 , 0x5d ) /* 93 */
EM_PAR(	P_T_U0_2,    1 , 0x5d ) /* 93 */
EM_PAR(	P_T_T0,      1 , 0x18 ) /* 24 */
EM_PAR(	P_T_SCALE_1, 1 , 0x1D ) /* 29 */
EM_PAR(	P_T_SCALE_2, 1 , 0x1D ) /* 29 */
EM_PAR(	P_T_LIM,     1 , 0x41 ) /* 65 */
EM_PAR(	P_MAX,       1 , 0xFA ) /* 250 */   //max channel power
EM_PAR(	P_MPPT_TYP,  1 , 0x00 ) /* 0 - PO, 1 - POM, 2 - CV */ 
EM_PAR(	P_U_START,   1 , 0x1C ) /* 28 */
EM_PAR(	P_U_STOP,    1 , 0x11 ) /* 17 */
EM_PAR(	P_PWM_START, 1 , 0x07 ) //4..8 us
EM_PAR(	P_PWM_MAX,   1 , 0x6e ) //110
EM_PAR(	P_PWM_STEP,  1 , 0x01 ) 
EM_PAR(	P_PWM_PERIOD,  1 , 50 ) //5.0us 
EM_PAR(	P_F_LEV1   ,  1 , 0x2D ) /* 45 */
EM_PAR(	P_F_LEV2   ,  1 , 0x3C ) /* 60 */
EM_PAR(	P_F_OFF   ,  1 , 0x28 ) /* 40 */
EM_PAR(	P_MAX_U_OUT  ,  1 , 160 ) /* 160V */
EM_PAR(	P_CFG,       1 , 0xFF )   //b0 - Ch1 en, b1 - Ch2 en , b2 - temp limit en
EM_PAR( P_CHK ,      1 , 0    )//checksum of frist section
EM_PAR( D_E1 ,       2 , 0    )//in 1 Wh, LSB are stored at power down only!
EM_PAR( D_E1h ,      1 ,  0   )
EM_PAR( D_E1hh ,     1 ,  0   )
EM_PAR( D_E1hhh ,    1 ,  0   )
EM_PAR( D_E2 ,       2 , 0    )
EM_PAR( D_E2h ,      1 ,  0   )
EM_PAR( D_E2hh ,     1 ,  0   )
EM_PAR( D_E2hhh ,    1 ,  0   )
EM_PAR( D_Eo ,       2 ,   0  )
EM_PAR( D_Eoh ,      1 ,   0  )
EM_PAR( D_Eohh ,     1 ,  0   )
EM_PAR( D_Eohhh ,    1 ,  0   )
EM_PAR( D_DTC ,      1 , 0    )
EM_PAR( D_HIST_IX ,  1 , 0    )
EM_PAR( D_HIST  ,  1 , 0    )
EM_PAR( D_HIST2  ,  1 , 0    )
EM_PAR( D_HIST3  ,  1 , 0    )
EM_PAR( D_HIST4  ,  1 , 0    )
EM_PAR( D_HIST5  ,  1 , 0    )
EM_PAR( D_HIST6  ,  1 , 0    )
EM_PAR( D_HIST7  ,  1 , 0    )
EM_PAR( D_HIST8  ,  1 , 0    )
EM_PAR( D_HIST9  ,  1 , 0    )
EM_PAR( D_HIST10  ,  1 , 0    )
EM_PAR( D_HIST11  ,  1 , 0    )
EM_PAR( D_HIST12  ,  1 , 0    )
EM_PAR( D_HIST13  ,  1 , 0    )
EM_PAR( D_HIST14  ,  1 , 0    )	
EM_PAR( D_HIST15  ,  1 , 0    )
EM_PAR( D_HIST16  ,  1 , 0    )	

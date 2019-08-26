


using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Serialization;



namespace HFHome
{
    class SerialProtocol
    {
        //LEN, DEST NAD, SRC NAD ,RES,  TYP, ADDR 4, DATA   
        enum TPaket { LEN = 0, DESTNAD = 1,SRCNAD=2, RES=3, CMD = 4,PAGE = 5, TX_DATA = 5, ADDH=6, ADDL=7, FALSHDATA = 8  };
        enum TCMD { SET_TIME = 1,ENRGY_CLR=8, GETSEED = 0xF0, SENDKEY=0xF1,ERASE=0xF2,WRITE=0xF3,VALIDATE=0xF4,ECURESET=0xF5,READ =0xF6,GET_MODE=0xF7,INVALIDATE=0xF8, COMCTL = 0xF9}
        enum TUDS { Pos, Neg, Wait };     

        //#define PAGE_FLASH    0x01
        //#define PAGE_EEPROM   0x02
        
        enum TFStates { SesionCheck, RequestSeed, SendKey, Invalidate,CommOFF1, CommOFF2, CommON1, CommON2, ECUReset, EraseApplication, WriteFlashData, ValidateApp, AppStart, Error1,Error, Done, SessionWait, WriteDBID, ReadDBID};
        enum TFSubStates { Req, Resp };
        public enum TCOMMode {Flash, WDBID, RDBID, RESET}

        long _sourceNAD, _destNAD,netID, Acurr; 
        System.IO.Ports.SerialPort serial;
        HexFileHandler hfh;
        TFStates FState;
        TFSubStates FSSubstate;
        byte[] RxData;
        byte[] RxDataL;
        byte[] TxData;
        byte[] DIDData;
        long DataReceived;
        long RxDataIndex;
        long _Timeout;
        long _MaxRespTime;
        int RetryCount;
        TFStates ErrorSt;
        string Errtext;
        UInt32 seed;
        int _RSSI_local;
        int _RSSI_remote;
        int NumRetrys;
        TCOMMode Mode;
        int DBIDLenght;
        byte _DID;
        byte _framecntr;
        long _TaskDelay;
        Boolean _bLock;
        Boolean _bUnlock;
        private Action<byte[],int> _logger;

        
        public void FlashApplication(string fname,long SNAD, long DNAD)
        {
            _MaxRespTime = 2000;
            _sourceNAD = SNAD;
            _destNAD = DNAD;
            if (DNAD == 0)
            {
                //error wrong nad
                ErrorSt = TFStates.Error;
                return;
            }
            FState = TFStates.CommOFF1;
            FSSubstate = TFSubStates.Req;
            ErrorSt = TFStates.Done;
            _RSSI_local = 0;
            _TaskDelay = 0;

            hfh = new HexFileHandler(fname, 65536, 255, 32);
            Acurr = hfh.GetLoAddress();
          
            Mode = TCOMMode.Flash;
            configModemNWID();
        }

        public SerialProtocol(System.IO.Ports.SerialPort sp, Action<byte[],int> log, long NWID)
        {
            serial = sp;
            netID = NWID;
            TxData = new byte[130];
            RxData = new byte[130];
            RxDataL = new byte[130];
            DataReceived = 0;
            _logger = log;
            _framecntr = 0;
        }

        public void WDBID(byte DID, byte[] Ddata, byte Lenght, long SNAD, long DNAD, Boolean bUnlock, Boolean bLock)
        {

            if (DNAD == 0)
            {
                //error wrong nad
                ErrorSt = TFStates.Error;
                return;
            }

            _bLock = bLock;
            _bUnlock = bUnlock;
            _MaxRespTime = 2000;
            
            _sourceNAD = SNAD;
            _destNAD = DNAD;
            _TaskDelay = 0;

            if (_bUnlock == true)
            {
                FState = TFStates.CommOFF1;
            }
            else
            {
                FState = TFStates.WriteDBID;
            }
            
            FSSubstate = TFSubStates.Req;
            ErrorSt = TFStates.Done;
            _RSSI_local = 0;

            DBIDLenght = Lenght;
            DIDData = new byte[Lenght];
            for (int i = 0; i < Lenght; i++)
            {
                DIDData[i] = Ddata[i];
            }
            _DID = DID;
            TxData = new byte[130];
            RxData = new byte[130];
            RxDataL = new byte[130];
            DataReceived = 0;
            Mode = TCOMMode.WDBID;

            configModemNWID();
        }

        public void RDBID(byte DID, byte[] Ddata, byte Lenght, long SNAD, long DNAD)
        {
            _sourceNAD = SNAD;
            _destNAD = DNAD;
            _DID = DID;
            _MaxRespTime = 200;
            _TaskDelay = 0;

            FState = TFStates.ReadDBID;
            FSSubstate = TFSubStates.Req;
            ErrorSt = TFStates.Done;
            _RSSI_local = 0;

            DBIDLenght = Lenght;
            DIDData = new byte[Lenght];
            for (int i = 0; i < Lenght; i++)
            {
                DIDData[i] = Ddata[i];
            }

            TxData = new byte[130];
            RxData = new byte[130];
            RxDataL = new byte[130];
            DataReceived = 0;
            Mode = TCOMMode.RDBID;

            configModemNWID();
        }

        private byte ToBCD(int v)
        {
            byte res = (byte)((((v / 10) % 10)<<4) | (v % 10));     
            return res;
        }

        public void SetTime(long SNAD, long DNAD)
        {
            _sourceNAD = SNAD;
            _destNAD = DNAD;
            _TaskDelay = 0;
            TxData[(int)TPaket.LEN] = 12;//len
            TxData[(int)TPaket.CMD] = 6;//status info ;
            
            DateTime dt = DateTime.Now;
            int dw = (int)dt.DayOfWeek;
            if (dw == 0)
            {
                dw = 7;//sunday
            }
            int i = (int)TPaket.CMD + 1;
            TxData[i++] = 7;//RTC signal
            TxData[i++] = ToBCD(dt.Second);
            TxData[i++] = ToBCD(dt.Minute);
            TxData[i++] = ToBCD(dt.Hour);
            TxData[i++] = ToBCD(dw);
            TxData[i++] = ToBCD(dt.Day);
            TxData[i++] = ToBCD(dt.Month);
            TxData[i++] = ToBCD(dt.Year % 100);

            SendDataPacket();
        }

        public void ClrEnergy(long SNAD, long DNAD)
        {
            _sourceNAD = SNAD;
            _destNAD = DNAD;
            _TaskDelay = 0;
            TxData[(int)TPaket.LEN] = 4;//len
            TxData[(int)TPaket.CMD] = (byte)TCMD.ENRGY_CLR;
            SendDataPacket();
        }

        public void ECUReset(long SNAD, long DNAD)
        {
            _sourceNAD = SNAD;
            _destNAD = DNAD;
            _TaskDelay = 0;
           
            _MaxRespTime = 200;

            FState = TFStates.RequestSeed;
            FSSubstate = TFSubStates.Req;
            ErrorSt = TFStates.Done;
            _RSSI_local = 0;

            
            TxData = new byte[130];
            RxData = new byte[130];
            RxDataL = new byte[130];
            DataReceived = 0;
            Mode = TCOMMode.RESET;

            configModemNWID();
        }


        #region Services

        private TUDS CommOff()
        {
            TUDS result = TUDS.Pos;
            long DNAD = _destNAD;
            _destNAD = 0;//global
            TxData[(int)TPaket.LEN] = 5;//len
            TxData[(int)TPaket.CMD] = (byte)TCMD.COMCTL;
            TxData[(int)TPaket.CMD + 1] = 0xA4;
            SendDataPacket();
            _destNAD = DNAD;
            return result;
        }

        private TUDS CommON()
        {
            TUDS result = TUDS.Pos;
            long DNAD = _destNAD;
            _destNAD = 0;//global
            TxData[(int)TPaket.LEN] = 5;//len
            TxData[(int)TPaket.CMD] = (byte)TCMD.COMCTL;
            TxData[(int)TPaket.CMD + 1] = 0x4A;
            SendDataPacket();
            _destNAD = DNAD;
            return result;
        }

        private void configModemNWID()
        {
            TxData[0] = 6;
            TxData[1] = 1;//config NWID
            TxData[2] = (byte)(netID >> 24);
            TxData[3] = (byte)(netID >> 16);
            TxData[4] = (byte)(netID >> 8);
            TxData[5] = (byte)(netID);
            TxData[6] = 255;//nad

            SendCommand();

        }

        private void Error(string error)
        {
            Errtext = error;
            ErrorSt = FState;

        }

        private bool WaitForResponse(int ms)
        {
            bool res = false;
            if ((FSSubstate == TFSubStates.Resp) && (0 == DataReceived))
            {
                if (_Timeout > ms)
                {
                    _Timeout -= ms;
                    res = true;
                }
                else
                {
                    if ((FState == TFStates.WriteFlashData) && (RetryCount < 10))
                    {
                        RetryCount++;
                        SendDataPacket();//resend
                        res = true;
                        NumRetrys++;
                    }
                    else
                    {
                        Error("Timeout");
                        FState = TFStates.Error;
                    }
                }
            }
            
            return res;
        }

        private void SM_CheckAndGoto(TUDS res, TFStates STrue, TFStates SFalse)
        {
            if (res != TUDS.Wait)
            {
                FSSubstate = TFSubStates.Req;
                if (res == TUDS.Pos)
                {
                    FState = STrue;
                }
                else
                {
                    FState = SFalse;
                }
            }
        }

        private TUDS RequestSeed()
        {
            TUDS result = TUDS.Wait;
            if (FSSubstate == TFSubStates.Req)
            {
                TxData[(int)TPaket.LEN] = 4;
                TxData[(int)TPaket.CMD] = (byte)TCMD.GETSEED;
                SendDataPacket();
            }
            else
            {
                if (RxData[(int)TPaket.LEN] == 8) //len,nad,nad,res,cmd,data1,data2,data3,data4
                {
                    seed = RxData[(int)TPaket.TX_DATA + 3];
                    seed <<= 8;
                    seed |= RxData[(int)TPaket.TX_DATA + 2];
                    seed <<= 8;
                    seed |= RxData[(int)TPaket.TX_DATA + 1];
                    seed <<= 8;
                    seed |= RxData[(int)TPaket.TX_DATA];
                    result = TUDS.Pos;
                }
                else
                {
                    Error("WrongResponseLen");
                    result = TUDS.Neg;
                }
            }
            return result;
        }

        private TUDS ReadDataBID()
        {
            TUDS result = TUDS.Wait;
            if (FSSubstate == TFSubStates.Req)
            {
                TxData[(int)TPaket.LEN] = (byte)(5 + DBIDLenght);//len
                TxData[(int)TPaket.CMD] = (byte)TCMD.READ;
                TxData[(int)TPaket.CMD + 1] = _DID;
                for (int i = 0; i < DBIDLenght; i++)
                {
                    TxData[(int)TPaket.CMD + 2 + i] = DIDData[i]; 
                }
                SendDataPacket();
            }
            else
            {
                if ((RxData[(int)TPaket.CMD] == (byte)TCMD.READ))
                {       
                        result = TUDS.Pos;                          
                }
                else
                {
                    Error("WrongResponse");
                    result = TUDS.Neg;
                }
            }
            return result;
        }
        
        private TUDS IsBootActive()
        {
            TUDS result = TUDS.Wait;
            if (FSSubstate == TFSubStates.Req)
            {
                TxData[(int)TPaket.LEN] = 5;//len
                TxData[(int)TPaket.CMD] = (byte)TCMD.READ;
                TxData[(int)TPaket.CMD + 1] = 1;
                SendDataPacket();
            }
            else
            {
                if ((RxData[(int)TPaket.CMD] == (byte)TCMD.READ))
                {
                    _RSSI_remote = RxData[(int)TPaket.PAGE + 1];
                    if (RxData[(int)TPaket.PAGE] == 2)
                    {
                        result = TUDS.Pos;
                        //already in boot, directly erase
                    }
                    else
                    {
                        result = TUDS.Neg;
                    }
                }
                else
                {
                    Error("WrongResponse");
                    result = TUDS.Neg;
                }
            }
            return result;
        }

        private TUDS SendKey()
        {
            TUDS result = TUDS.Wait;
            if (FSSubstate == TFSubStates.Req)
            {
                TxData[(int)TPaket.LEN] = 8;
                TxData[(int)TPaket.CMD] = (byte)TCMD.SENDKEY;

                UInt32 key = CalcKey();
                TxData[(int)TPaket.TX_DATA] = (byte)key;
                TxData[(int)TPaket.TX_DATA + 1] = (byte)(key >> 8);
                TxData[(int)TPaket.TX_DATA + 2] = (byte)(key >> 16);
                TxData[(int)TPaket.TX_DATA + 3] = (byte)(key >> 24);
                SendDataPacket();
            }
            else
            {
                if (RxData[(int)TPaket.CMD] == (int)TCMD.SENDKEY)
                {
                    result = TUDS.Pos;
                }
                else
                {
                    Error("WrongKey");
                    result = TUDS.Neg;
                }
            }
            return result;
        }

        private TUDS InvalidateApp()
        {
            TUDS result = TUDS.Wait;
            if (FSSubstate == TFSubStates.Req)
            {
                TxData[(int)TPaket.LEN] = 4;
                TxData[(int)TPaket.CMD] = (int)TCMD.INVALIDATE;
                SendDataPacket();
            }
            else
            {
                if (RxData[(int)TPaket.CMD] == (int)TCMD.INVALIDATE)//pos resp
                {
                    result = TUDS.Pos;

                }
                else
                {
                    Error("WrongResponse");
                    result = TUDS.Neg;
                }
            }
            return result;
        }

        private TUDS EraseApp()
        {
            TUDS result = TUDS.Wait;
            if (FSSubstate == TFSubStates.Req)
            {
                TxData[(int)TPaket.LEN] = 4;
                TxData[(int)TPaket.CMD] = (int)TCMD.ERASE;
                SendDataPacket();
            }
            else
            {
                if (RxData[(int)TPaket.CMD] == (int)TCMD.ERASE)//pos resp
                {
                    result = TUDS.Pos;
                    RetryCount = 0;
                    NumRetrys = 0;
                }
                else
                {
                    Error("WrongResponse");
                    result = TUDS.Neg;
                }
            }
            return result;
        }

        private TUDS EcuReset()
        {
            TUDS result = TUDS.Wait;
            if (FSSubstate == TFSubStates.Req)
            {
                TxData[(int)TPaket.LEN] = 4;
                TxData[(int)TPaket.CMD] = (int)TCMD.ECURESET;
                SendDataPacket();
            }
            else
            {
                if (RxData[(int)TPaket.CMD] == (int)TCMD.ECURESET)//pos resp
                {
                    result = TUDS.Pos;
                }
                else
                {
                    Error("WrongResponse");
                    result = TUDS.Neg;
                }
            }
            return result;
        }

        private TUDS WriteFlash()
        {
            TUDS result = TUDS.Wait;
            if (FSSubstate == TFSubStates.Req)
            {
                TxData[(int)TPaket.CMD] = (int)TCMD.WRITE;
                TxData[(int)TPaket.PAGE] = 1;
                long wacr = Acurr / 2;//word address
                TxData[(int)TPaket.ADDH] = (byte)(wacr >> 8);
                TxData[(int)TPaket.ADDL] = (byte)(wacr);
                for (int i = 0; i < hfh.GetAlign(); i++)
                {
                    TxData[(int)TPaket.FALSHDATA + i] = hfh.GetHexDataByte(Acurr + i);
                }
                TxData[0] = 39;//len,nad,nad,res,cmd,page,add4,data32
                SendDataPacket();
            }
            else
            {
                if (RxData[(int)TPaket.CMD] == (int)TCMD.WRITE)//pos resp
                {

                    UInt16 chk = 0;
                    UInt16 chk2 = RxData[(int)TPaket.TX_DATA + 1];
                    chk2 <<= 8;
                    chk2 |= RxData[(int)TPaket.TX_DATA];

                    for (int i = 0; i < hfh.GetAlign() / 2; i++)
                    {
                        UInt16 d = hfh.GetHexDataByte(Acurr + i + i + 1);
                        d <<= 8;
                        d += hfh.GetHexDataByte(Acurr + i + i);
                        chk += (UInt16)(d & 0x3FFF);//verify data
                    }
                    if (chk2 != chk)
                    {
                        Error("WriteCsumFail");
                        result = TUDS.Neg; ;
                    }
                    else
                    {
                        Acurr += hfh.GetAlign();
                        if (Acurr < hfh.GetHiAddress())
                        {
                            FSSubstate = TFSubStates.Req;//stay in this state as long as needed
                            RetryCount = 0;
                        }
                        else
                        {
                            result = TUDS.Pos;
                        }
                    }
                }
                else
                {
                    Error("WrongResponse");
                    result = TUDS.Neg;
                }
            }
            return result;
        }

        private TUDS ValidateApp()
        {
            TUDS result = TUDS.Wait;
            if (FSSubstate == TFSubStates.Req)
            {
                TxData[(int)TPaket.LEN] = 4;
                TxData[(int)TPaket.CMD] = (byte)TCMD.VALIDATE;
                SendDataPacket();
            }
            else
            {
                if (RxData[(int)TPaket.CMD] == (byte)TCMD.VALIDATE)//pos resp
                {
                    result = TUDS.Pos;
                }
                else
                {
                    Error("WrongResponse");
                    result = TUDS.Neg;
                }
            }
            return result;
        }

        private TUDS WriteDBID()
        {
            TUDS result = TUDS.Wait;
            if (FSSubstate == TFSubStates.Req)
            {
                TxData[(int)TPaket.CMD] = (int)TCMD.WRITE;
                TxData[(int)TPaket.PAGE] = _DID;
               
                for (int i = 0; i < DBIDLenght; i++)
                {
                    TxData[(int)TPaket.ADDH + i] = DIDData[i];
                }
                TxData[0] = (byte)(5 + DBIDLenght);//len,nad,nad,res,cmd,page,add4,data32
                SendDataPacket();
            }
            else
            {
                if (RxData[(int)TPaket.CMD] == (int)TCMD.WRITE)//pos resp
                {
                    result = TUDS.Pos;
                }
                else
                {
                    Error("WriteFail");
                    result = TUDS.Neg;
                }
            }
            return result;
        }

        
        #endregion

        #region Tasks
        public void SerialTick(int ms)
        {
            if (Mode == TCOMMode.Flash)
            {
                FlashTaskTick(ms);
            }
            else if (Mode == TCOMMode.WDBID)
            {
                WDBIDTaskTick(ms);
            }
            else if (Mode == TCOMMode.RESET)
            {
                ResetTask(ms);
            }
            else { RDBIDTask(ms); }
        }

        private void WDBIDTaskTick(int ms)
        {

            if (WaitForResponse(ms)) { return; }

            switch (FState)
            {

                case TFStates.CommOFF1:
                    SM_CheckAndGoto(CommOff(), TFStates.CommOFF2, TFStates.Error1);
                    _TaskDelay = 10;
                    break;

                case TFStates.CommOFF2:
                    SM_CheckAndGoto(CommOff(), TFStates.SesionCheck, TFStates.Error1);
                    _TaskDelay = 5;
                    break;
 
                case TFStates.SesionCheck:
                    SM_CheckAndGoto(IsBootActive(), TFStates.Error1, TFStates.RequestSeed);
                    break;

                case TFStates.RequestSeed:
                    SM_CheckAndGoto(RequestSeed(), TFStates.SendKey, TFStates.Error);
                    break;

                case TFStates.SendKey:
                    SM_CheckAndGoto(SendKey(), TFStates.WriteDBID, TFStates.Error);
                    break;

                case TFStates.WriteDBID:
                    TFStates nxt = TFStates.Done;
                    if (_bLock)
                    {
                        nxt = TFStates.CommON1;
                    }
                    SM_CheckAndGoto(WriteDBID(), nxt, TFStates.Error);
                    break;

                case TFStates.CommON1:
                    SM_CheckAndGoto(CommON(), TFStates.CommON2, TFStates.Error1);
                    _TaskDelay = 10;
                    break;

                case TFStates.CommON2:
                    SM_CheckAndGoto(CommON(), TFStates.Done, TFStates.Error1);
                    break;
                case TFStates.Done:

                    break;

                case TFStates.Error1:
                    SM_CheckAndGoto(CommON(), TFStates.Error, TFStates.Error);
                    break;

                case TFStates.Error:

                    break;

            }

        }

        private void FlashTaskTick(int ms)
        {
            if (WaitForResponse(ms)) { return; }
            if (_TaskDelay != 0)  {      _TaskDelay--;   return; }
            
            switch (FState)
            {
                case TFStates.CommOFF1:
                    SM_CheckAndGoto(CommOff(), TFStates.CommOFF2, TFStates.Error1);
                    _TaskDelay = 10;
                    break;

                case TFStates.CommOFF2:
                    SM_CheckAndGoto(CommOff(), TFStates.SesionCheck, TFStates.Error1);
                    _TaskDelay = 5;
                    break;
                
                case TFStates.SesionCheck:
                    SM_CheckAndGoto(IsBootActive(), TFStates.EraseApplication, TFStates.RequestSeed);
                    break;

                case TFStates.RequestSeed:
                    SM_CheckAndGoto(RequestSeed(), TFStates.SendKey, TFStates.Error1);
                    break;

                case TFStates.SendKey:
                    SM_CheckAndGoto(SendKey(), TFStates.Invalidate, TFStates.Error1);
                    break;

                case TFStates.Invalidate:
                    SM_CheckAndGoto(InvalidateApp(), TFStates.ECUReset, TFStates.Error1);
                    break;

                case TFStates.ECUReset:
                    _MaxRespTime = 5000;
                    SM_CheckAndGoto(EcuReset(), TFStates.SesionCheck, TFStates.Error1);
                    break;

                case TFStates.EraseApplication:
                    SM_CheckAndGoto(EraseApp(), TFStates.WriteFlashData, TFStates.Error1);
                    break;

                case TFStates.WriteFlashData:
                    _MaxRespTime = 300;
                   // _TaskDelay = 1;
                    SM_CheckAndGoto(WriteFlash(), TFStates.ValidateApp, TFStates.Error1);
                    break;

                case TFStates.ValidateApp:
                    SM_CheckAndGoto(ValidateApp(), TFStates.AppStart, TFStates.Error1);
                    break;

                case TFStates.AppStart:
                    _MaxRespTime = 5000;
                    SM_CheckAndGoto(EcuReset(), TFStates.CommON1, TFStates.Error1);
                    _TaskDelay = 30;
                    break;

                case TFStates.CommON1:
                    SM_CheckAndGoto(CommON(), TFStates.CommON2, TFStates.Error1);
                    _TaskDelay = 10;
                    break;

                case TFStates.CommON2:
                    SM_CheckAndGoto(CommON(), TFStates.Done, TFStates.Error1);
                    break;

                case TFStates.Done:

                    break;
                case TFStates.Error1:
                    SM_CheckAndGoto(CommON(), TFStates.Error, TFStates.Error);
                    break;
                case TFStates.Error:

                    break;

            }

        }

        private void RDBIDTask(int ms)
        {
             if (WaitForResponse(ms)) { return; }

             switch (FState)
             {
                 case TFStates.CommOFF1:
                     SM_CheckAndGoto(CommOff(), TFStates.CommOFF2, TFStates.Error1);
                     _TaskDelay = 10;
                     break;

                 case TFStates.CommOFF2:
                     SM_CheckAndGoto(CommOff(), TFStates.ReadDBID, TFStates.Error1);
                     _TaskDelay = 5;
                     break;
                 
                 case TFStates.ReadDBID:
                     SM_CheckAndGoto(ReadDataBID(), TFStates.Done, TFStates.Error);
                     break;

                 case TFStates.CommON1:
                     SM_CheckAndGoto(CommON(), TFStates.CommON2, TFStates.Error1);
                     _TaskDelay = 10;
                     break;

                 case TFStates.CommON2:
                     SM_CheckAndGoto(CommON(), TFStates.Done, TFStates.Error1);
                     break;
                 case TFStates.Done:

                     break;

                 case TFStates.Error1:
                     SM_CheckAndGoto(CommON(), TFStates.Error, TFStates.Error);
                     break;

                 case TFStates.Error:

                     break;

             }  
        }

        private void ResetTask(int ms)
        {
            if (WaitForResponse(ms)) { return; }
           
            switch (FState)
            {
                case TFStates.SesionCheck:
                    SM_CheckAndGoto(IsBootActive(), TFStates.Error, TFStates.RequestSeed);
                    break;

                case TFStates.RequestSeed:
                    SM_CheckAndGoto(RequestSeed(), TFStates.SendKey, TFStates.Error);
                    break;

                case TFStates.SendKey:
                    SM_CheckAndGoto(SendKey(), TFStates.ECUReset, TFStates.Error);
                    break;

                case TFStates.ECUReset:
                    _MaxRespTime = 5000;
                    SM_CheckAndGoto(EcuReset(), TFStates.Done, TFStates.Error);
                    break;

                case TFStates.Done:

                    break;
                case TFStates.Error:

                    break;

            }
            
        }
        #endregion

        #region API
        public TCOMMode GetMode()
        {
            return Mode;
        }

        public long GetProgress()
        {
            long pp;
            if (Mode == TCOMMode.Flash)
            {

                 pp = (Acurr - hfh.GetLoAddress()) * 100 / (hfh.GetHiAddress() - hfh.GetLoAddress());
            }
            else
            {
                pp = 100;
            }
            if (pp > 100)
            {
                pp = 100;
            }
            return pp;
        }

        public long GetFlashedSizeInBytes()
        {
            return (Acurr - hfh.GetLoAddress());
        }

        public bool IsCMDFinshedOK()
        {
            return (FState == TFStates.Done);
        }

        public bool IsCMDFinshedNOK()
        {
            return (FState == TFStates.Error);
        }

        public int GetRetryNumber()
        {
            return NumRetrys;
        }

        public string GetError()
        {
            return ErrorSt.ToString() + ":" + Errtext;
        }

        public string GetStateName()
        {
            return FState.ToString();
        }

        public int GetlocalRSSI()
        {
           
            return _RSSI_local;
        }

        public int GetremoteRSSI()
        {
            double rs = (0.55 * _RSSI_remote) - 118.5;
            return (int)rs;
        }

        public byte[] GetRXData()
        {
            return RxData;
        }

        #endregion

        #region SerialComm

        private void LogMsg(bool bRx)
        {
            int rssi;
            byte[] bbuf;
         
            if (bRx == false)
            {
                bbuf = TxData;
                rssi = 256;
            }
            else
            {
                rssi=_RSSI_local;
                bbuf = RxData;
            }



            _logger(bbuf, rssi);
           
        }

        private void SendDataPacket()
        {

            TxData[(int)TPaket.DESTNAD] = (byte)_destNAD;
            TxData[(int)TPaket.SRCNAD] = (byte)_sourceNAD;
            TxData[(int)TPaket.RES] = _framecntr++;
            DataReceived = 0;
            RxDataIndex = 0;
            _Timeout = _MaxRespTime;//ms
            FSSubstate = TFSubStates.Resp;

            int len = TxData[(int)TPaket.LEN] + 1;

            byte[] ss = new byte[120];
            byte mask = 0x80;//start
            int i, j;
            j = 0;
            for (i = 0; i < len; i++)
            {
                ss[j++] = (byte)((TxData[i] >> 4) | mask);
                mask = 0x20;//lsb
                ss[j++] = (byte)((TxData[i] & 0x0F) | mask);
                mask = 0x00;
            }
            j--;
            ss[j] |= 0x40;//stop
            if (serial.IsOpen)
            {
                serial.DiscardOutBuffer();
                
                serial.Write(ss, 0, j + 1);
                LogMsg(false);
            }
            
        }

        private void SendCommand()
        {
            int len = TxData[0]+1;
            byte[] ss = new byte[120];
            byte mask = 0x90;//start cmd
            int i, j;
            j = 0;
            for (i = 0; i < len; i++)
            {
                ss[j++] = (byte)((TxData[i] >> 4) | mask);
                mask = 0x20;//lsb
                ss[j++] = (byte)((TxData[i] & 0x0F) | mask);
                mask = 0x00;
            }
            j--;
            ss[j] |= 0x40;//stop
            if (serial.IsOpen)
            {
                serial.Write(ss, 0, j + 1);
            }
            
        }

        public void SerialProtocolRxData(byte data)
        {
            if (0 != (data & 0x80))
            {
                RxDataIndex = 0;
            }
            if (0 != (data & 0x20))
            {
                RxDataL[RxDataIndex++] |= (byte)((data) & 0x0F);
            }
            else
            {
                RxDataL[RxDataIndex] = (byte)((data << 4) & 0xF0);
            }

            if (0 == (data & 0x40))
            {
                return;
            }
            //stop detected ! copy data

            for (int i = 0; i < RxDataIndex; i++)
            {
                RxData[i] = RxDataL[i];//double buffering
            }
            

            double rs = (0.55 *  RxData[RxDataIndex - 1]) - 118.5;
            _RSSI_local = (int)rs;

            //check NADs
            if ((RxData[(int)TPaket.SRCNAD] == _destNAD) && (RxData[(int)TPaket.DESTNAD] == _sourceNAD))
            {
                DataReceived = RxDataIndex - 1;
            }

            LogMsg(true);           
        } 
        #endregion

        #region Security
        private UInt32 ROL(UInt32 val, int count)
        {
            UInt32 res = val;
            while (count > 0)
            {
                if (0 != (res & 0x80000000))
                {
                    res = (res << 1) | 1;
                }
                else
                {
                    res = (res << 1);
                }
                count--;
            }
            return res;
        }

        private UInt32 CalcKey()
        {
            UInt32 res = seed;
            res = ROL(res, 7);
            res = res ^ 0xCA236124;
            res = ROL(res, 5);
            res = res ^ 0xAC321641;
            res = ROL(res, 3);
            res = res ^ 0x01100112;
            res = ROL(res, 1);
            return res;
        } 
        #endregion
    }

    abstract class MyBackgroundWorker
    {
        public int _progress;
        abstract public void Tick(int ms);
        abstract public bool IsFinshed();
        public void IncProgress(int v)
        {
            _progress += v;
           if (_progress > 100)
           {
               _progress = 100;
           }
        }
        public int Progress()
        {
            return _progress;
        }
    }

    class Scanner : MyBackgroundWorker
    {
        enum TScanState {SendReq, WaitResp, End };
        TScanState _SState;
        byte _cnad;
        SerialProtocol _sp;
        long _devFound;
        long[] _devcaps;
        int[] _RSSI_local;
        int[] _RSSI_remote;

        byte _maxnad;
        
        public Scanner(SerialProtocol sp, byte maxNAD)
        {
            _SState = TScanState.SendReq;
            _cnad = 0;
            _sp = sp;
            _devcaps = new long[255];
            _RSSI_local = new int[255];
            _RSSI_remote = new int[255];

            for (int i = 0; i < 255; i++)
            {
                _devcaps[i] = 0;
                _RSSI_local[i] = 0;
                _RSSI_remote[i] = 0;
            }
            _devFound = 0;
            _maxnad = maxNAD;
        }

        public override void Tick(int ms)
        {
            _sp.SerialTick(ms);

            switch (_SState)
            {
                case TScanState.SendReq:
                {
                    byte[] b = new byte[2];
                    _sp.RDBID(1,b,0, 255, _cnad);
                    _SState = TScanState.WaitResp;
                }
                break;
                case TScanState.WaitResp:
                {
                        bool bMoveNext = false;
                        if (_sp.IsCMDFinshedOK())
                        {
                            //read dev cap
                            long v = _sp.GetRXData()[7];
                            v <<= 8;
                            v |= _sp.GetRXData()[8];
                            _devcaps[_cnad] = v;
                            _RSSI_local[_cnad] = _sp.GetlocalRSSI();
                            _RSSI_remote[_cnad] = _sp.GetremoteRSSI();

                            bMoveNext = true;
                            _devFound++;
                        }
                        else if (_sp.IsCMDFinshedNOK())
                        {
                            bMoveNext = true;
                        }

                        if (bMoveNext == true)
                        {
                            // move to next NAD
                            if (_cnad < _maxnad)
                            {
                                _cnad++;
                                _SState = TScanState.SendReq;
                            }
                            else
                            {
                                if (_cnad != 254)
                                {
                                    _cnad = 254;
                                    _SState = TScanState.SendReq;
                                }
                                else
                                {
                                    _SState = TScanState.End;
                                }
                            }
                        }
                    
                    
                }
                break;

                case TScanState.End:
                {
                }
                break;
            }
            int p = (_cnad * 100) / _maxnad;
            if (p > 100) { p = 100; }
            _progress = p;
        }

        public override bool IsFinshed()
        {
            return (bool)(_SState == TScanState.End);
        }

        public long GetNumDevFound()
        {
            return _devFound;
        }

        public long GetDevCaps(byte i)
        {
            if (i < 255)
            {
                return _devcaps[i];
            }
            else return 0;
        }

        public int GetDevRSSI(byte i)
        {
            if (i < 255)
            {
                return _RSSI_local[i];
            }
            else return 0;
        }

    }

    class NVMreader : MyBackgroundWorker
    {
        enum TNVMState { SendReq, WaitResp, End };
        TNVMState _SState;
        byte _cnad;
        SerialProtocol _sp;
        public Collection<NVMBlock> _mem;
        byte _cblock;

        public NVMreader(SerialProtocol sp, byte cNAD)
        {
            _SState = TNVMState.SendReq;
            _cnad = cNAD;
            _sp = sp;
            _mem = new Collection<NVMBlock>();
            _cblock = 0;
            _progress = 0;
        }

        public override void Tick(int ms)
        {
            _sp.SerialTick(ms);

            switch (_SState)
            {
                case TNVMState.SendReq:
                    {
                        byte[] b = new byte[2];
                        b[0] = _cblock;
                        _sp.RDBID(2,b,1, 255, _cnad);
                        _SState = TNVMState.WaitResp;
                        
                    }
                    break;
                case TNVMState.WaitResp:
                    {
                        
                        if (_sp.IsCMDFinshedOK())
                        {
                            int len = _sp.GetRXData()[0] - 4;
                            if (len > 0){
                                byte[] b = new byte[64];   //len,snad,dnad,res,did,data....

                                for (int i = 0; i < len; i++)
                                {
                                    b[i] = _sp.GetRXData()[i+5];
                                }

                                NVMBlock nv = new NVMBlock(_cblock.ToString(), _cblock, (byte)len, b);
                                _mem.Add(nv);
                            }
                            
                            //block exists
                            if (_cblock < 255)
                            {
                                _cblock++;
                                _SState = TNVMState.SendReq;
                               
                            }
                            IncProgress(10);
                        }
                        else if (_sp.IsCMDFinshedNOK())
                        {
                           //no more blocks
                            _SState = TNVMState.End;
                            IncProgress(100);
                        }
                    }
                    break;

                case TNVMState.End:
                    {
                    }
                    break;
            }

        }

        public override bool IsFinshed()
        {
            return (bool)(_SState == TNVMState.End);
        }

           
    }

    class NVMwriter : MyBackgroundWorker
    {
        enum TNVMState { SendReq, WaitResp, End };
        TNVMState _SState;
        byte _cnad;
        SerialProtocol _sp;
        public Collection<NVMBlock> _mem;
        byte _cblock;
        Boolean _firstreq;
        Boolean _lastreq;


        public NVMwriter(SerialProtocol sp, byte cNAD, Collection<NVMBlock> mem)
        {
            _SState = TNVMState.SendReq;
            _cnad = cNAD;
            _sp = sp;
            _mem = mem;
            _cblock = 0;
            _firstreq = true;
            _lastreq = false;
        }


        public override void Tick(int ms)
        {
            _sp.SerialTick(ms);

            switch (_SState)
            {
                case TNVMState.SendReq:
                    {
                        byte[] b = new byte[64];
                        b[0] = _cblock;
                        int ln = _mem[_cblock].Lenght;
                        for(int i = 0; i< ln; i++)
                        {
                            b[1 + i] = _mem[_cblock].DataByte(i);
                        }
                        _sp.WDBID(2, b, (byte)(ln+1), 255, _cnad,_firstreq,_lastreq);
                        _SState = TNVMState.WaitResp;
                        _firstreq = false;
                    }
                    break;

                case TNVMState.WaitResp:
                    {

                        if (_sp.IsCMDFinshedOK())
                        {
                            _cblock++;
                            
                            if (_cblock < _mem.Count)
                            {
                                _SState = TNVMState.SendReq;
                                if (_cblock == (_mem.Count - 1)) //last block
                                {
                                    _lastreq = true;
                                }
                            }
                            else
                            {
                                IncProgress(100);
                                _SState = TNVMState.End;
                            }
                            IncProgress(100 / _mem.Count);
                        }
                        else if (_sp.IsCMDFinshedNOK())
                        {
                            IncProgress(100);
                            _SState = TNVMState.End;
                        }
                    }
                    break;

                case TNVMState.End:
                    {
                    }
                    break;
            }

        }

        public override bool IsFinshed()
        {
            return (bool)(_SState == TNVMState.End);
        }

    }
}

#line 1 "../../MRF89_Drv/newfile.c"
#line 1 "../../MRF89_Drv/newfile.c"






#line 8 "../../MRF89_Drv/newfile.c"
#line 9 "../../MRF89_Drv/newfile.c"
#line 10 "../../MRF89_Drv/newfile.c"
#line 11 "../../MRF89_Drv/newfile.c"




RH_MRF89* RH_MRF89::_deviceForInterrupt[RH_MRF89_NUM_INTERRUPTS] = {0, 0, 0};
uint8_t RH_MRF89::_interruptCount = 0; 




PROGMEM static const RH_MRF89::ModemConfig MODEM_CONFIG_TABLE[] ={
    
    
    { RH_MRF89_MODSEL_FSK, 0x0B, 0x63, 0x40 | 0x01, 0x20}, 
    { RH_MRF89_MODSEL_FSK, 0x0B, 0x27, 0x40 | 0x01, 0x20}, 
    { RH_MRF89_MODSEL_FSK, 0x0B, 0x13, 0x40 | 0x01, 0x20}, 
    { RH_MRF89_MODSEL_FSK, 0x09, 0x09, 0x70 | 0x02, 0x20}, 
    { RH_MRF89_MODSEL_FSK, 0x04, 0x04, 0xB0 | 0x05, 0x40}, 
    { RH_MRF89_MODSEL_FSK, 0x03, 0x03, 0xD0 | 0x06, 0x40}, 
    { RH_MRF89_MODSEL_FSK, 0x02, 0x02, 0xE0 | 0x09, 0x60}, 
    { RH_MRF89_MODSEL_FSK, 0x01, 0x01, 0xF0 | 0x0F, 0x80}, 
    { RH_MRF89_MODSEL_FSK, 0x01, 0x00, 0xF0 | 0x0F, 0x80} 

};

RH_MRF89::RH_MRF89(uint8_t csconPin, uint8_t csdatPin, uint8_t interruptPin, RHGenericSPI& spi)
:
RHNRFSPIDriver(csconPin, spi),
_csconPin(csconPin),
_csdatPin(csdatPin),
_interruptPin(interruptPin) {
    _myInterruptIndex = 0xff; 
}

bool RH_MRF89::init() {
    
    
    _spi.setFrequency(RHGenericSPI::Frequency1MHz);
    if (!RHNRFSPIDriver::init())
        return false;

    
    pinMode(_csconPin, OUTPUT);
    digitalWrite(_csconPin, HIGH);
    pinMode(_csdatPin, OUTPUT);
    digitalWrite(_csdatPin, HIGH);

    
    int interruptNumber = digitalPinToInterrupt(_interruptPin);
    if (interruptNumber == NOT_AN_INTERRUPT)
        return false;
#line 65 "../../MRF89_Drv/newfile.c"

    
    spiUsingInterrupt(interruptNumber);

    
    setOpMode(RH_MRF89_CMOD_STANDBY);

    
    
    spiWriteRegister(RH_MRF89_REG_02_FDEVREG, 0xaa);
    if (spiReadRegister(RH_MRF89_REG_02_FDEVREG) != 0xaa)
        return false;
    spiWriteRegister(RH_MRF89_REG_02_FDEVREG, 0x3); 
    if (spiReadRegister(RH_MRF89_REG_02_FDEVREG) != 0x3)
        return false;

    
    
    
    pinMode(_interruptPin, INPUT);

    
    
    
    
    
    
    if (_myInterruptIndex == 0xff) {
        
        if (_interruptCount <= RH_MRF89_NUM_INTERRUPTS)
            _myInterruptIndex = _interruptCount++;
        else
            return false; 
    }
    _deviceForInterrupt[_myInterruptIndex] = this;
    if (_myInterruptIndex == 0)
        attachInterrupt(interruptNumber, isr0, RISING);
    else if (_myInterruptIndex == 1)
        attachInterrupt(interruptNumber, isr1, RISING);
    else if (_myInterruptIndex == 2)
        attachInterrupt(interruptNumber, isr2, RISING);
    else
        return false; 

    
    
    
    
    
    
    
    spiWriteRegister(RH_MRF89_REG_00_GCONREG, RH_MRF89_CMOD_STANDBY | RH_MRF89_FBS_950_960 | RH_MRF89_VCOT_60MV);
    spiWriteRegister(RH_MRF89_REG_01_DMODREG, RH_MRF89_MODSEL_FSK | RH_MRF89_OPMODE_PACKET); 
    spiWriteRegister(RH_MRF89_REG_02_FDEVREG, 0); 
    spiWriteRegister(RH_MRF89_REG_03_BRSREG, 0); 
    spiWriteRegister(RH_MRF89_REG_04_FLTHREG, 0); 
    spiWriteRegister(RH_MRF89_REG_05_FIFOCREG, RH_MRF89_FSIZE_64);
    spiWriteRegister(RH_MRF89_REG_06_R1CREG, 0); 
    spiWriteRegister(RH_MRF89_REG_07_P1CREG, 0); 
    spiWriteRegister(RH_MRF89_REG_08_S1CREG, 0); 
    spiWriteRegister(RH_MRF89_REG_09_R2CREG, 0); 
    spiWriteRegister(RH_MRF89_REG_0A_P2CREG, 0); 
    spiWriteRegister(RH_MRF89_REG_0B_S2CREG, 0); 
    spiWriteRegister(RH_MRF89_REG_0C_PACREG, RH_MRF89_PARC_23);
    
    
    
    spiWriteRegister(RH_MRF89_REG_0D_FTXRXIREG, RH_MRF89_IRQ0RXS_PACKET_SYNC | RH_MRF89_IRQ1RXS_PACKET_CRCOK | RH_MRF89_IRQ1TX);
    spiWriteRegister(RH_MRF89_REG_0E_FTPRIREG, RH_MRF89_LENPLL);
    spiWriteRegister(RH_MRF89_REG_0F_RSTHIREG, 0x00); 
    spiWriteRegister(RH_MRF89_REG_10_FILCREG, 0); 

    spiWriteRegister(RH_MRF89_REG_11_PFCREG, 0x38); 
    spiWriteRegister(RH_MRF89_REG_12_SYNCREG, RH_MRF89_SYNCREN | RH_MRF89_SYNCWSZ_32); 
    spiWriteRegister(RH_MRF89_REG_13_RSVREG, 0x07); 
    
    spiWriteRegister(RH_MRF89_REG_15_OOKCREG, 0x00); 
    spiWriteRegister(RH_MRF89_REG_16_SYNCV31REG, 0x69); 
    spiWriteRegister(RH_MRF89_REG_17_SYNCV23REG, 0x81); 
    spiWriteRegister(RH_MRF89_REG_18_SYNCV15REG, 0x7E); 
    spiWriteRegister(RH_MRF89_REG_19_SYNCV07REG, 0x96); 
    
    spiWriteRegister(RH_MRF89_REG_1A_TXCONREG, 0xf0 | RH_MRF89_TXOPVAL_13DBM); 
    spiWriteRegister(RH_MRF89_REG_1B_CLKOREG, 0x00); 
    spiWriteRegister(RH_MRF89_REG_1C_PLOADREG, 0x40); 
    spiWriteRegister(RH_MRF89_REG_1D_NADDSREG, 0x00); 
    spiWriteRegister(RH_MRF89_REG_1E_PKTCREG, RH_MRF89_PKTLENF | RH_MRF89_PRESIZE_4 | RH_MRF89_WHITEON | RH_MRF89_CHKCRCEN | RH_MRF89_ADDFIL_OFF);
    spiWriteRegister(RH_MRF89_REG_1F_FCRCREG, 0x00); 

    
    
    setPreambleLength(3); 
    uint8_t syncwords[] = {0x69, 0x81, 0x7e, 0x96}; 
    setSyncWords(syncwords, sizeof (syncwords));
    setTxPower(RH_MRF89_TXOPVAL_1DBM);
    if (!setFrequency(915.4))
        return false;
    
    if (!setModemConfig(FSK_Rb20Fd40))
        return false;

    return true;
}

bool RH_MRF89::printRegisters() {
#line 178 "../../MRF89_Drv/newfile.c"
    return true;
}







void RH_MRF89::handleInterrupt() {
    
    if (_mode == RHModeTx) {
        
        
        
        _txGood++;
        setModeIdle();
    } else if (_mode == RHModeRx) {
        
        
        
        

        
        
        _lastRssi = (spiReadRegister(RH_MRF89_REG_14_RSTSREG) >> 1) - 120;

        _bufLen = spiReadData();
        if (_bufLen < 4) {
            
            uint8_t i;
            for (i = 0; spiReadRegister(RH_MRF89_REG_0D_FTXRXIREG) & RH_MRF89_FIFOEMPTY; i++)
                spiReadData();
            clearRxBuf();
            return;
        }

        
        uint8_t i;
        for (i = 0; spiReadRegister(RH_MRF89_REG_0D_FTXRXIREG) & RH_MRF89_FIFOEMPTY; i++)
            _buf[i] = spiReadData();

        
        validateRxBuf();
        if (_rxBufValid)
            setModeIdle(); 
    }
}





void RH_MRF89::isr0() {
    if (_deviceForInterrupt[0])
        _deviceForInterrupt[0]->handleInterrupt();
}

void RH_MRF89::isr1() {
    if (_deviceForInterrupt[1])
        _deviceForInterrupt[1]->handleInterrupt();
}

void RH_MRF89::isr2() {
    if (_deviceForInterrupt[2])
        _deviceForInterrupt[2]->handleInterrupt();
}

uint8_t RH_MRF89::spiReadRegister(uint8_t reg) {
    
    setSlaveSelectPin(_csconPin);
    digitalWrite(_csdatPin, HIGH);
    return spiRead(((reg & 0x1f) << 1) | RH_MRF89_SPI_READ_MASK);
}

uint8_t RH_MRF89::spiWriteRegister(uint8_t reg, uint8_t val) {
    
    setSlaveSelectPin(_csconPin);
    digitalWrite(_csdatPin, HIGH);
    
    
    
    return spiWrite(((reg & 0x1f) << 1), val);
}

uint8_t RH_MRF89::spiWriteData(uint8_t data) {
    spiWriteRegister(RH_MRF89_REG_1F_FCRCREG, RH_MRF89_ACFCRC); 
    setSlaveSelectPin(_csdatPin);
    digitalWrite(_csconPin, HIGH);
    return spiCommand(data);
}

uint8_t RH_MRF89::spiWriteData(const uint8_t* data, uint8_t len) {
    spiWriteRegister(RH_MRF89_REG_1F_FCRCREG, RH_MRF89_ACFCRC); 
    setSlaveSelectPin(_csdatPin);
    digitalWrite(_csconPin, HIGH);

    uint8_t status = 0;
    ATOMIC_BLOCK_START;
    _spi.beginTransaction();
    digitalWrite(_slaveSelectPin, LOW);
    while (len--)
        _spi.transfer(*data++);
    digitalWrite(_slaveSelectPin, HIGH);
    _spi.endTransaction();
    ATOMIC_BLOCK_END;
    return status;

}

uint8_t RH_MRF89::spiReadData() {
    spiWriteRegister(RH_MRF89_REG_1F_FCRCREG, RH_MRF89_ACFCRC | RH_MRF89_FRWAXS); 
    setSlaveSelectPin(_csdatPin);
    digitalWrite(_csconPin, HIGH);
    return spiCommand(0);
}

void RH_MRF89::setOpMode(uint8_t mode) {
    
    uint8_t val = spiReadRegister(RH_MRF89_REG_00_GCONREG);
    val = (val & ~RH_MRF89_CMOD) | (mode & RH_MRF89_CMOD);
    spiWriteRegister(RH_MRF89_REG_00_GCONREG, val);
}

void RH_MRF89::setModeIdle() {
    if (_mode != RHModeIdle) {
        setOpMode(RH_MRF89_CMOD_STANDBY);
        _mode = RHModeIdle;
    }
}

bool RH_MRF89::sleep() {
    if (_mode != RHModeSleep) {
        setOpMode(RH_MRF89_CMOD_SLEEP);
        _mode = RHModeSleep;
    }
    return true;
}

void RH_MRF89::setModeRx() {
    if (_mode != RHModeRx) {
        setOpMode(RH_MRF89_CMOD_RECEIVE);
        _mode = RHModeRx;
    }
}

void RH_MRF89::setModeTx() {
    if (_mode != RHModeTx) {
        setOpMode(RH_MRF89_CMOD_TRANSMIT);
        _mode = RHModeTx;
    }
}

void RH_MRF89::setTxPower(uint8_t power) {
    uint8_t txconreg = spiReadRegister(RH_MRF89_REG_1A_TXCONREG);
    txconreg |= (power & RH_MRF89_TXOPVAL);
    spiWriteRegister(RH_MRF89_REG_1A_TXCONREG, txconreg);
}

bool RH_MRF89::available() {
    if (_mode == RHModeTx)
        return false;
    setModeRx();

    return _rxBufValid; 
}

bool RH_MRF89::recv(uint8_t* buf, uint8_t* len) {
    if (!available())
        return false;

    if (buf && len) {
        ATOMIC_BLOCK_START;
        
        if (*len > _bufLen - RH_MRF89_HEADER_LEN)
            *len = _bufLen - RH_MRF89_HEADER_LEN;
        memcpy(buf, _buf + RH_MRF89_HEADER_LEN, *len);
        ATOMIC_BLOCK_END;
    }
    clearRxBuf(); 

    return true;
}

bool RH_MRF89::send(const uint8_t* data, uint8_t len) {
    if (len > RH_MRF89_MAX_MESSAGE_LEN)
        return false;

    waitPacketSent(); 
    setModeIdle();

    if (!waitCAD())
        return false; 

    
    
    spiWriteData(len + RH_MRF89_HEADER_LEN);
    spiWriteData(_txHeaderTo);
    spiWriteData(_txHeaderFrom);
    spiWriteData(_txHeaderId);
    spiWriteData(_txHeaderFlags);
    spiWriteData(data, len);
    setModeTx(); 

    return true;
}

uint8_t RH_MRF89::maxMessageLength() {
    return RH_MRF89_MAX_MESSAGE_LEN;
}



void RH_MRF89::validateRxBuf() {
    if (_bufLen < 4)
        return; 
    
    _rxHeaderTo = _buf[0];
    _rxHeaderFrom = _buf[1];
    _rxHeaderId = _buf[2];
    _rxHeaderFlags = _buf[3];
    if (_promiscuous ||
            _rxHeaderTo == _thisAddress ||
            _rxHeaderTo == RH_BROADCAST_ADDRESS) {
        _rxGood++;
        _rxBufValid = true;
    }
}

void RH_MRF89::clearRxBuf() {
    ATOMIC_BLOCK_START;
    _rxBufValid = false;
    _bufLen = 0;
    ATOMIC_BLOCK_END;
}

bool RH_MRF89::verifyPLLLock() {
    
    
    uint8_t ftpriVal = spiReadRegister(RH_MRF89_REG_0E_FTPRIREG);
    spiWriteRegister(RH_MRF89_REG_0E_FTPRIREG, ftpriVal | RH_MRF89_LSTSPLL); 
    setOpMode(RH_MRF89_CMOD_FS);
    unsigned long ulStartTime = millis();
    while ((millis() - ulStartTime < 1000)) {
        ftpriVal = spiReadRegister(RH_MRF89_REG_0E_FTPRIREG);
        if ((ftpriVal & RH_MRF89_LSTSPLL) != 0)
            break;
    }
    setOpMode(RH_MRF89_CMOD_STANDBY);
    return ((ftpriVal & RH_MRF89_LSTSPLL) != 0);
}

bool RH_MRF89::setFrequency(float centre) {
    

    uint8_t FBS;
    if (centre >= 902.0 && centre < 915.0) {
        FBS = RH_MRF89_FBS_902_915;
    } else if (centre >= 915.0 && centre <= 928.0) {
        FBS = RH_MRF89_FBS_915_928;
    } else if (centre >= 950.0 && centre <= 960.0) {
        
        
        FBS = RH_MRF89_FBS_950_960;
    }        
        
        
        
        
        
    else {
        
        return false;
    }

    
    
    uint8_t R = 119; 
    uint32_t centre_kHz = centre * 1000;
    uint32_t xtal_kHz = (RH_MRF89_XTAL_FREQ * 1000);
    uint32_t compare = (centre_kHz * 8 * (R + 1)) / (9 * xtal_kHz);
    uint8_t P = ((compare - 75) / 76) + 1;
    uint8_t S = compare - (75 * (P + 1));

    
    uint8_t val = spiReadRegister(RH_MRF89_REG_00_GCONREG);
    val = (val & ~RH_MRF89_FBS) | (FBS & RH_MRF89_FBS);
    spiWriteRegister(RH_MRF89_REG_00_GCONREG, val);

    spiWriteRegister(RH_MRF89_REG_06_R1CREG, R);
    spiWriteRegister(RH_MRF89_REG_07_P1CREG, P);
    spiWriteRegister(RH_MRF89_REG_08_S1CREG, S);

    return verifyPLLLock();
}




bool RH_MRF89::setModemConfig(ModemConfigChoice index) {
    if (index > (signed int) (sizeof (MODEM_CONFIG_TABLE) / sizeof (ModemConfig)))
        return false;

    RH_MRF89::ModemConfig cfg;
    memcpy_P(&cfg, &MODEM_CONFIG_TABLE[index], sizeof (cfg));

    
    uint8_t val = spiReadRegister(RH_MRF89_REG_01_DMODREG);
    val = (val & ~RH_MRF89_MODSEL) | cfg.MODSEL;
    spiWriteRegister(RH_MRF89_REG_01_DMODREG, val);

    spiWriteRegister(RH_MRF89_REG_02_FDEVREG, cfg.FDVAL);
    spiWriteRegister(RH_MRF89_REG_03_BRSREG, cfg.BRVAL);
    spiWriteRegister(RH_MRF89_REG_10_FILCREG, cfg.FILCREG);

    
    val = spiReadRegister(RH_MRF89_REG_1A_TXCONREG);
    val = (val & ~RH_MRF89_TXIPOLFV) | (cfg.TXIPOLFV & RH_MRF89_TXIPOLFV);
    spiWriteRegister(RH_MRF89_REG_1A_TXCONREG, val);

    return true;
}

void RH_MRF89::setPreambleLength(uint8_t bytes) {
    if (bytes >= 1 && bytes <= 4) {
        bytes--;
        uint8_t pktcreg = spiReadRegister(RH_MRF89_REG_1E_PKTCREG);
        pktcreg = (pktcreg & ~RH_MRF89_PRESIZE) | ((bytes << 5) & RH_MRF89_PRESIZE);
        spiWriteRegister(RH_MRF89_REG_1E_PKTCREG, pktcreg);
    }
}

void RH_MRF89::setSyncWords(const uint8_t* syncWords, uint8_t len) {
    if (syncWords && (len > 0 and len <= 4)) {
        uint8_t syncreg = spiReadRegister(RH_MRF89_REG_12_SYNCREG);
        syncreg = (syncreg & ~RH_MRF89_SYNCWSZ) | (((len - 1) << 3) & RH_MRF89_SYNCWSZ);
        spiWriteRegister(RH_MRF89_REG_12_SYNCREG, syncreg);
        uint8_t i;
        for (i = 0; i < 4; i++) {
            if (len > i)
                spiWriteRegister(RH_MRF89_REG_16_SYNCV31REG + i, syncWords[i]);
        }
    }
}



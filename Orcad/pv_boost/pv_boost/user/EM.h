

#undef EM_PAR
#define EM_PAR(x,y, z) x,
typedef enum
{
  #include "em_cfg.h"
  EM_MAX_BYTES
}tEMID; 



extern byte u8Mirror[EM_MAX_BYTES];

void EM_Init(void);

void EM_Task(void);

void EM_StorageEn(byte section);

void EM_StorageDis(byte section);

#define EM_GetU8(x)  u8Mirror[x]

#define EM_GetU16(x)  *((word *)(&u8Mirror[x]))

#define EM_GetU32(x)  *((dword *)(&u8Mirror[x]))
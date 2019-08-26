/*********************************************************************
 * FileName:        user.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         sprut
 * Copyright:       2007-2010 Joerg Bredendiek (sprut)
 *
 *
 ********************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#ifndef USER_H
#define USER_H



/** I N C L U D E S **********************************************************/
#include "system\usb\usb.h"
#include "system\typedefs.h"


/** D E F I N I T I O N S ****************************************************/

/** S T R U C T U R E S ******************************************************/




/** P U B L I C  P R O T O T Y P E S *****************************************/
void UserInit(void);
void ProcessRx(void);
void InputTask(void);
void InputADCTaskIdle(void);
void FINCheckMeasureOnIdle(void);
void SSRFastTask(void);
void PWM_Task(void);
void TaskADCScale(void);



#endif	// USER_H

/****  E N D E  *********************************************/

/*
 * \file myk_fpga_init.h
 *
 */

/**
* \page Disclaimer Legal Disclaimer
* Copyright 2015-2017 Analog Devices Inc.
* Released under the AD9371 API license, for more information see the "LICENSE.txt" file in this zip file.
*
*/

#ifndef MYK_FPGA_INIT_H_
#define MYK_FPGA_INIT_H_

#include <stddef.h>
#include "mykonos_fpga_ip.h"

extern fpgaCpllConfig_t txQpll;

extern fpgaCpllConfig_t rxCpll1;

extern fpgaCpllConfig_t rxCpll2;

extern fpgaCpllConfig_t rxCpll0;


extern fpgaCpllConfig_t rxCpll3;


extern fpgaMmcmConfig_t mmcm;

extern fpgaTddStateMachine_t fpgaTddStateMachine;

extern fpgaJesd204bDeframerConfig_t fpgaRxDeframerConfig;

extern fpgaJesd204bDeframerConfig_t fpgaObsrxDeframerConfig;


extern fpgaJesd204bFramerConfig_t fpgaTxFramerConfig;

extern fpgaJesd204bSerializerConfig_t fpgaSerializerConfig;

extern fpgaJesd204bDeserializerConfig_t fpgaDeserializerConfig;

extern fpgaJesd204bClockConfig_t fpgaJESD204Clocks;

#endif /* MYK_FPGA_INIT_H_ */

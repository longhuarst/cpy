/**
 * myk_fpga_init.c
 *
 * Device clock : 122.88MHz
 * RX1 and RX2
 * TX1 and TX2
 * RX 20MHz IQrate 30.72, 2 lanes Lane0 and 1
 * TX 20/100MHz IQrate 122.88, 4 lanes
 * ORX 100MHz IQrate 122.88, 2 lanes 2 and 3
 * SRX 20MHz IQrate 30.72, 2 lanes 2 and 3
 */

/**
* \page Disclaimer Legal Disclaimer
* Copyright 2015-2017 Analog Devices Inc.
* Released under the AD9371 API license, for more information see the "LICENSE.txt" file in this zip file.
*
*/

#include <stddef.h>
#include "common.h"

#include "mykonos_fpga_ip.h"
#include "myk_fpga_init.h"

//fpgaTxQpllConfig_t txQpll=
//{
//		0,//uint32_t band;						/*!< \brief FPGA IP GTX QPLL upper or lower band VCO select, lower band = 5.93-8.0 Ghz, upper band = 9.8-12.5 Ghz, where '1' selects upper, '0' selects lower */
//		1,//uint32_t M;							/*!< \brief FPGA IP GTX QPLL 'M' reference clock divisor value */
//		80,//uint32_t N;							/*!< \brief FPGA IP GTX QPLL 'N' loop divisor value */
//		4//uint32_t D;							/*!< \brief FPGA IP GTX QPLL 'D' Tx out divisor value */
//
//};

fpgaCpllConfig_t rxCpll1=
{
		1,//uint32_t channel;					/*!< \brief FPGA IP GTX CPLL channel output select */
	    1,//uint32_t M;							/*!< \brief FPGA IP GTX CPLL 'M' reference clock divisor value */
		4,//uint32_t N2;						/*!< \brief FPGA IP GTX CPLL 'N2' divisor value */
		5,//uint32_t N1;						/*!< \brief FPGA IP GTX CPLL 'N1' divisor value */
		4//uint32_t D;							/*!< \brief FPGA IP GTX CPLL 'D' Rx out divisor value */
};

fpgaCpllConfig_t rxCpll2=
{
		2,//uint32_t channel;					/*!< \brief FPGA IP GTX CPLL channel output select */
	    1,//uint32_t M;							/*!< \brief FPGA IP GTX CPLL 'M' reference clock divisor value */
		4,//uint32_t N2;						/*!< \brief FPGA IP GTX CPLL 'N2' divisor value */
		5,//uint32_t N1;						/*!< \brief FPGA IP GTX CPLL 'N1' divisor value */
		4//uint32_t D;							/*!< \brief FPGA IP GTX CPLL 'D' Rx out divisor value */
};

fpgaCpllConfig_t rxCpll0=
{
		0,//uint32_t channel;					/*!< \brief FPGA IP GTX CPLL channel output select */
	    1,//uint32_t M;							/*!< \brief FPGA IP GTX CPLL 'M' reference clock divisor value */
		4,//uint32_t N2;						/*!< \brief FPGA IP GTX CPLL 'N2' divisor value */
		5,//uint32_t N1;						/*!< \brief FPGA IP GTX CPLL 'N1' divisor value */
		2//uint32_t D;							/*!< \brief FPGA IP GTX CPLL 'D' Rx out divisor value */
};


fpgaCpllConfig_t rxCpll3=
{
		3,//uint32_t channel;					/*!< \brief FPGA IP GTX CPLL channel output select */
	    1,//uint32_t M;							/*!< \brief FPGA IP GTX CPLL 'M' reference clock divisor value */
		4,//uint32_t N2;						/*!< \brief FPGA IP GTX CPLL 'N2' divisor value */
		5,//uint32_t N1;						/*!< \brief FPGA IP GTX CPLL 'N1' divisor value */
		2//uint32_t D;							/*!< \brief FPGA IP GTX CPLL 'D' Rx out divisor value */
};


fpgaMmcmConfig_t mmcm =
{
	11,	//uint32_t M;							/*!< \brief FPGA IP MMCM 'M' divisor value */
	22,	//uint32_t rx0LaneRateDiv40;			/*!< \brief FPGA IP MMCM Rx0 lane rate divide by 40 value */
	44,	//uint32_t rx1LaneRateDiv40;			/*!< \brief FPGA IP MMCM Rx1 lane rate divide by 40 value */
	44,	//uint32_t rx2LaneRateDiv40;			/*!< \brief FPGA IP MMCM Rx2 lane rate divide by 40 value */
	22,	//uint32_t rx3LaneRateDiv40;			/*!< \brief FPGA IP MMCM Rx3 lane rate divide by 40 value */
	44,	//uint32_t rxDeframerDiv40;			/*!< \brief FPGA IP MMCM Rx Deframer divide by 40 value */
	22,	//uint32_t obsRxDeframerDiv40;		/*!< \brief FPGA IP MMCM ObsRx Deframer divide by 40 value */
	22,	//uint32_t txFramerDiv40;				/*!< \brief FPGA IP MMCM Tx Framer divide by 40 value */
	61440000	//uint32_t txLrDiv40_Hz;				/*!< \stores tx lane rate divided by 40. */

};

/* default settings */
fpgaTddStateMachine_t fpgaTddStateMachine =
{

	0,	/* tddSecondPtrEnable - TDD secondary pointers enable  */
	0,	/* tddLoopCount - TDD loop count: 0 = infinite, 1..7 = number of loops */
	1,	/* tddContRxCapture - TDD continuous Rx capture bypass */
	1,	/* tddContTxTransmit - TDD continous Tx capture bypass */
	0,	/* tddSyncExtTrig - TDD external sync input enable for triggering start of frame */
	0,	/* tddEnableSnRxAPtrs - TDD SnRx A pointers enable */
	0,	/* tddEnableSnRxBPtrs - TDD SnRx B pointers enable */
	0,	/* tddEnableSnRxCPtrs - TDD SnRx C pointers enable */

	0x0012BFFF,	/* tddFrameCnt - TDD frame size count based on lane rate/40 (default = 10 ms @ 4.915 Gbs) */
	0x00000000,	/* tddTx1OnPtr - TDD Tx1 on pointer value based on lane rate/40 (default = 0 ms @ 4.915 Gbs) */
	0x0002CFFF,	/* tddTx1OffPtr - TDD Tx1 off pointer value based on lane rate/40 (default = 1500 us @ 4.915 Gbs) */
	0x0000000F,	/* tddTx2OnPtr - TDD Tx2 on pointer value based on lane rate/40  */
	0x0002CFFF,	/* tddTx2OffPtr - TDD Tx2 off pointer value based on lane rate/40 */
	0x0003BFFF,	/* tddRx1OnPtr - TDD Rx1 on pointer value based on lane rate/40 (default = 2000 us @ 4.915 Gbs) */
	0x00095FFF,	/* tddRx1OffPtr - TDD Rx1 off pointer value based on lane rate/40 (default = 5000 us @ 4.915 Gbs) */
	0x0003C00F,	/* tddRx2OnPtr - TDD Rx2 on pointer value based on lane rate/40 */
	0x00095FFF,	/* tddRx2OffPtr - TDD Rx2 off pointer value based on lane rate/40  */
	0,	/* tddOrx1OnPtr - TDD ORx1 on pointer value based on lane rate/40 */
	0,	/* tddOrx1OffPtr - TDD ORx1 off pointer value based on lane rate/40 */
	0,	/* tddOrx2OnPtr - TDD ORx2 on pointer value based on lane rate/40 */
	0,	/* tddOrx2OffPtr - TDD ORx2 off pointer value based on lane rate/40 */

	0,	/* tddTx1DataPathDel - TDD Tx1 data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tddTx2DataPathDel - TDD Tx2 data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tddRx1DataPathDel - TDD Rx1 data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tddRx2DataPathDel - TDD Rx2 data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tddOrx1DataPathDel - TDD ORx1 data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tddOrx2DataPathDel - TDD ORx2 data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */

	0,	/* tdd2ndTx1OnPtr - TDD Tx1 secondary on pointer value based on lane rate/40 (default = 5000 us @ 4.915 Gbs) */
	0,	/* tdd2ndTx1OffPtr - TDD Tx1 secondary off pointer value based on lane rate/40 (default = 6500 us @ 4.915 Gbs) */
	0,	/* tdd2ndTx2OnPtr - TDD Tx2 secondary on pointer value based on lane rate/40 */
	0,	/* tdd2ndTx2OffPtr - TDD Tx2 secondary off pointer value based on lane rate/40  */
	0,	/* tdd2ndRx1OnPtr - TDD Rx1 secondary on pointer value based on lane rate/40  (default = 7000 us @ 4.915 Gbs)*/
	0,	/* tdd2ndRx1OffPtr - TDD Tx1 secondary off pointer value based on lane rate/40 (default = 10000 us @ 4.915 Gbs)*/
	0,	/* tdd2ndRx2OnPtr - TDD Rx2 secondary on pointer value based on lane rate/40 */
	0,	/* tdd2ndRx2OffPtr - TDD Rx2 secondary off pointer value based on lane rate/40 */
	0,	/* tdd2ndOrx1OnPtr - TDD ORx1 secondary on pointer value based on lane rate/40 */
	0,	/* tdd2ndOrx1OffPtr - TDD ORx1 secondary off pointer value based on lane rate/40 */
	0,	/* tdd2ndOrx2OnPtr - TDD ORx2 secondary on pointer value based on lane rate/40 */
	0,	/* tdd2ndOrx2OffPtr - TDD ORx2 secondary off pointer value based on lane rate/40 */

	0,	/* tdd2ndTx1DataPathDel - TDD Tx1 secondary data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tdd2ndTx2DataPathDel - TDD Tx2 secondary data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tdd2ndRx1DataPathDel - TDD Rx1 secondary data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tdd2ndRx2DataPathDel - TDD Rx2 secondary data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tdd2ndOrx1DataPathDel - TDD ORx1 secondary data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tdd2ndOrx2DataPathDel - TDD ORx2 secondary data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */

	0x00000000,	/* tddExtTrigOnPtr - TDD external trigger output on frame pointer */
	0x0012C000,	/* tddExtTrigOffPtr - TDD external trigger output off frame pointer */

	0,	/* tddSnRxAonPtr - TDD SnRx 'A' on pointer value based on lane rate/40 */
	0,	/* tddSnRxAoffPtr - TDD SnRx 'A' off pointer value based on lane rate/40 */
	0,	/* tddSnRxBonPtr - TDD SnRx 'B' on pointer value based on lane rate/40 */
	0,	/* tddSnRxBoffPtr - TDD SnRx 'B' off pointer value based on lane rate/40 */
	0,	/* tddSnRxConPtr - TDD SnRx 'C' on pointer value based on lane rate/40 */
	0,	/* tddSnRxCoffPtr - TDD SnRx 'C' off pointer value based on lane rate/40 */

	0,	/* tddSnRxAdataPathDel - TDD SnRx 'A' data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tddSnRxBdataPathDel - TDD SnRx 'B' data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */
	0,	/* tddSnRxCdataPathDel - TDD SnRx 'C' data path delay configured as two's compliment number of samples where, negative = before pointer, positive = after pointer */

	0,	/* tddIntCalsOnPtr - TDD ObsRx/SnRx on pointer into frame counter to begin the observation to internal transmit region */
	0,	/* tddIntCalsOffPtr - TDD ObsRx/SnRx off pointer into frame counter to end the observation to internal transmit region */
	0,  /* tdd2ndIntCalsOnPtr - TDD ObsRx/SnRx secondary on pointer into frame counter to begin the observation to internal transmit region */
	0   /* tdd2ndIntCalsOffPtr - TDD ObsRx/SnRx secondary off pointer into frame counter to end the observation to internal transmit region */

};

fpgaJesd204bDeframerConfig_t fpgaRxDeframerConfig =
{
	2,//uint32_t L;                         /*!< \brief JESD204B Configuration L = lanes per data converter */
	1,//uint32_t SCR;                       /*!< \brief JESD204B Configuration Scramble setting */
	4,//uint32_t F;                         /*!< \brief JESD204B Configuration F = octets per frame */
	32,//uint32_t K;                         /*!< \brief JESD204B Configuration K = frames per multiframe */
	4,//uint32_t M;                         /*!< \brief JESD204B Configuration M = number of data converters */
	1,//uint32_t SUBCLASSV;					/*!< \brief JESD204B Configuration SUBCLASSV = defaults to '1' unless otherwise specified */

	0,//uint32_t bufferDelay;				/*!< \brief sets the Rx FIFO buffer delay */
	0,//uint32_t disableErrorReporting;		/*!< \brief enables or disables Rx lane error reporting, '0' = enabled, '1' = disabled */
	1,//uint32_t supportLaneSync;			/*!< \brief */
	0,//uint32_t sysrefAlways;				/*!< \brief */
	0//uint32_t enable;					/*!< \brief enables the JESD204 Rx path */

};//fpgaJesd204bDeframerConfig_t;

fpgaJesd204bDeframerConfig_t fpgaObsrxDeframerConfig =
{
	2,//uint32_t L;                         /*!< \brief JESD204B Configuration L = lanes per data converter */
	1,//uint32_t SCR;                       /*!< \brief JESD204B Configuration Scramble setting */
	2,//uint32_t F;                         /*!< \brief JESD204B Configuration F = octets per frame */
	32,//uint32_t K;                         /*!< \brief JESD204B Configuration K = frames per multiframe */
	2,//uint32_t M;                         /*!< \brief JESD204B Configuration M = number of data converters */
	1,//uint32_t SUBCLASSV;					/*!< \brief JESD204B Configuration SUBCLASSV = defaults to '1' unless otherwise specified */

	0,//uint32_t bufferDelay;				/*!< \brief sets the Rx FIFO buffer delay */
	0,//uint32_t disableErrorReporting;		/*!< \brief enables or disables Rx lane error reporting, '0' = enabled, '1' = disabled */
	1,//uint32_t supportLaneSync;			/*!< \brief */
	0,//uint32_t sysrefAlways;				/*!< \brief */
	0//uint32_t enable;					/*!< \brief enables the JESD204 Rx path */

};//fpgaJesd204bDeframerConfig_t;


fpgaJesd204bFramerConfig_t fpgaTxFramerConfig =
{
	0, //uint32_t DID;                       /*!< \brief JESD204B Configuration Device ID */
	0, //uint32_t BID;                       /*!< \brief JESD204B Configuration Bank ID */
	0, //uint32_t LID;                       /*!< \brief JESD204B Configuration Starting Lane ID */
	4, //uint32_t L;                         /*!< \brief JESD204B Configuration L = lanes per data converter */
	1, //uint32_t SCR;                       /*!< \brief JESD204B Configuration Scramble setting */
	2, //uint32_t F;                         /*!< \brief JESD204B Configuration F = octets per frame */
	32, //uint32_t K;                         /*!< \brief JESD204B Configuration K = frames per multiframe */
	4, //	uint32_t M;                         /*!< \brief JESD204B Configuration M = number of data converters */
	14, //	uint32_t N;                         /*!< \brief JESD204B Configuration N = data converter sample resolution */
	2, //	uint32_t CS;                        /*!< \brief JESD204B Configuration CS = number of control bits transferred per sample per frame */
	16, //	uint32_t NP;                        /*!< \brief JESD204B Configuration NP = JESD204B word size based on the highest resolution of the data converter */
	1, //	uint32_t S;                         /*!< \brief JESD204B Configuration S = number of samples/data converter/frame */
	0, //	uint32_t CF;                        /*!< \brief JESD204B Configuration CF = '0' = control bits appended to each sample, '1' = appended to end of frame */
	0, //	uint32_t HD;                        /*!< \brief JESD204B Configuration HD = high density bit - samples are contained within lane (0) or divided over more than one lane (1) */
	1, //	uint32_t JESDV;						/*!< \brief JESD204B Configuration JESDV = should always be '2' unless otherwise specified */
	1, //	uint32_t SUBCLASSV;					/*!< \brief JESD204B Configuration SUBCLASSV = defaults to '1' unless otherwise specified */
	71, //	uint32_t FCHK;						/*!< \brief JESD204B Configuration FCHK = checksum */

	4, //	uint32_t multiFrames;				/*!< \brief */
	1, //	uint32_t supportLaneSync;			/*!< \brief */
	0, //	uint32_t sysrefAlways;				/*!< \brief */
	0 //	uint32_t enable;					/*!< \brief enables the JESD204 Tx path */

};

fpgaJesd204bSerializerConfig_t fpgaSerializerConfig=
{
	0, //	uint32_t postCursor;				/*!< \brief Tx postcursor setting */
	0, //uint32_t preCursor;					/*!< \brief Tx precursor setting */
	4, //uint32_t amplitude;    				/*!< \brief ??? */
	0, //uint32_t polarity;					/*!< \brief sets Tx polarity based on consecutively weighted bit in nibble, where '0' = no inversion, '1' = inversion */
	15, //uint32_t lanesEnabled; 				/*!< \brief powers up Tx lane based on consecutively weighted bits [8=lane3, 4=lane2, 2=lane1, 1=lane0] in nibble, where '0' = enabled, '1' = disabled */
	141 //uint32_t lanesMux;					/*!< \brief chooses which framer lane outputs to a physical lane. */
};

fpgaJesd204bDeserializerConfig_t fpgaDeserializerConfig =
{
	0, //uint32_t lanesPolarity;				/*!< \brief sets Rx polarity based on consecutively weighted bit in nibble, where '0' = no inversion, '1' = inversion */
	150, //uint32_t lanesEnabled;				/*!< \brief powers up Rx lane based on consecutively weighted bits [8=lane3, 4=lane2, 2=lane1, 1=lane0] in nibble, where '0' = enabled, '1' = disabled */
	52377 //uint32_t lanesMux;					/*!< \brief chooses which Rx deframer lane outputs to a physical lane. */
};

fpgaJesd204bClockConfig_t fpgaJESD204Clocks =
{
	0, //uint32_t useInternalSysref; 		/*!< \brief determines use of external SYSREF signal, where '0' = internal SYSREF, '1' = external SYSREF */
	511 //uint32_t internSysrefDiv;			/*!< \brief ??? */
};

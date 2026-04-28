/* SPDX-License-Identifier: GPL-2.0 */
/*
 *  Copyright (C) 2015-2019 Altera Corporation <www.altera.com>
 */

#ifndef __CONFIG_SOCFGPA_ARRIA10_H__
#define __CONFIG_SOCFGPA_ARRIA10_H__

#include <asm/arch/base_addr_a10.h>

/*
 * U-Boot general configurations
 */

/* Memory configurations  */
#define PHYS_SDRAM_1_SIZE		0x40000000

/*
 * Serial / UART configurations
 */
#define CFG_SYS_BAUDRATE_TABLE {4800, 9600, 19200, 38400, 57600, 115200}

/*
 * L4 OSC1 Timer 0
 */
/* reload value when timer count to zero */
#define TIMER_LOAD_VAL			0xFFFFFFFF

/*
 * Flash configurations
 */

/* SPL memory allocation configuration, this is for FAT implementation */

/*
 * SD/MMC boot uses CFG_EXTRA_ENV_SETTINGS from socfpga_common.h; append
 * Arria 10 SoCDK-only variables here so other SoCFPGA boards are
 * unaffected.
 *
 * Default CONFIG_BOOTCOMMAND stays "run distro_bootcmd" (no MMC/FAT/FIT
 * assumptions at autoboot). For two-stage FPGA programming (load script,
 * program core bitstream from U-Boot proper, enable HPS-to-FPGA bridges,
 * then distro), run: bootcmd_fpga_mmc, e.g.:
 *
 *   setenv bootcmd "run bootcmd_fpga_mmc"; saveenv
 *
 * or invoke that from u-boot.scr.
 */
#if !defined(CONFIG_QSPI_BOOT) && !defined(CONFIG_NAND_BOOT)
#define SOCFPGA_BOARD_ENV_APPEND						\
	"fatscript=if fatload mmc 0:1 ${scriptaddr} ${scriptfile};"		\
		"then source ${scriptaddr}:script; fi\0"			\
	"prog_core=if load mmc 0:1 ${loadaddr} fit_spl_fpga.itb; then "		\
		"if fpga loadmk 0 ${loadaddr}:fpga-core-1; then "		\
			"echo prog_core: ok; "					\
		"else echo prog_core: fpga_loadmk_failed; fi; "			\
		"else echo prog_core: fit_load_failed; fi\0"			\
	"bootcmd_fpga_mmc=run fatscript; run prog_core; bridge enable; "	\
		"run distro_bootcmd\0"
#endif

/* The rest of the configuration is shared */
#include <configs/socfpga_common.h>

#endif	/* __CONFIG_SOCFGPA_ARRIA10_H__ */

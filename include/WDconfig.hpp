#ifndef _WDCONFIG__H
#define _WDCONFIG__H
#include "Data.hpp"
#include "flash.hpp"
#include <cstdio>

#define CFGRELOAD_CORRTABLES_BIT (0)

/* ###########################################################################
 *  Functions
 *  ###########################################################################
 */

/*! \fn      int ParseConfigFile(FILE *f_ini, WaveDumpConfig_t *WDcfg)
 *   \brief   Read the configuration file and set the WaveDump paremeters
 *
 *   \param   f_ini        Pointer to the config file
 *   \param   WDcfg:   Pointer to the WaveDumpConfig data structure
 *   \return  0 = Success; negative numbers are error codes
 */
int ParseConfigFile(FILE *f_ini, WaveDumpConfig_t &WDcfg);
#endif // _WDCONFIG__H

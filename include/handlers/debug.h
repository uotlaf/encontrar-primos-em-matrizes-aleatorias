/*
 * debug.h
 *
 *  Created on: 18 de jun. de 2022
 *      Author: uotlaf
 */

#ifndef INCLUDE_HANDLERS_DEBUG_H_
#define INCLUDE_HANDLERS_DEBUG_H_

#include <stdio.h>

#ifdef COLOR_DEBUG
#define COLOR_RED    "\033[31m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_CLEAR  "\033[0m"

#endif

#ifdef DEBUG
#define debug(text)       { printf("%s[%s:%d]%s[%s]%s%s", COLOR_YELLOW, __FILE__, __LINE__,COLOR_GREEN, __func__,COLOR_CLEAR, text);};
#define debugThread(text) { printf("%s[%s:%d]%s[%s:%d]%s%s", COLOR_YELLOW, __FILE__, __LINE__,COLOR_GREEN, __func__, arg->n_thread,COLOR_CLEAR, text);};
#else
#define debug(text)
#define debugThread(text)
#endif

#define error(text) {printf("%s[%s:%d][%s]%s", COLOR_RED, __FILE__, __LINE__, __func__, text);};

#endif /* INCLUDE_HANDLERS_DEBUG_H_ */

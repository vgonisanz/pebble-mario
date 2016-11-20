/**
* @file logger.h
* @brief Logs definition
* @details Need define before in source LOG_TAG string to identifier each call.
* Need define LOGGER_ACTIVE to work, if not won't print
* @author vgoni
* @date 2016/04/01
*/
#ifndef LOGGER_H
#define LOGGER_H

#define LOGGER_ACTIVE /* Comment to deactive */

#include <stdio.h>

#ifdef LOGGER_ACTIVE
  /* Check LOG_TAG */
# ifndef LOG_TAG
# error "LOG_TAG is not defined"
# endif
  /* Macro to print is ON */
  // If pebble! :-D
# define LOGD(...) do                   \
  {                                     \
          APP_LOG(APP_LOG_LEVEL_DEBUG, __VA_ARGS__);          \
  } while (0)
# define LOGE(...) do                   \
{                                       \
        APP_LOG(APP_LOG_LEVEL_ERROR, __VA_ARGS__);          \
} while (0)
#else
  /* Macro to print is OFF */
# define LOGD(...)
# define LOGE(...)
#endif

#endif /* LOGGER_H */

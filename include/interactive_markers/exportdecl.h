/*
 * Cross platform macros.
 *
 */
#ifndef INTERACTIVE_MARKERS__DECL_H_
#define INTERACTIVE_MARKERS__DECL_H_

#include <ros/macros.h>

#ifdef ROS_BUILD_SHARED_LIBS  // ros is being built around shared libraries
  #ifdef interactive_markers_EXPORTS  // we are building a shared lib/dll
    #define INTERACTIVE_MARKERS_DECL ROS_HELPER_EXPORT
  #else  // we are using shared lib/dll
    #define INTERACTIVE_MARKERS_DECL ROS_HELPER_IMPORT
  #endif
#else  // ros is being built around static libraries
  #define INTERACTIVE_MARKERS_DECL
#endif

#endif
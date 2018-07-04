/*
 * tkPkgConfig.c --
 *
 *	This file contains the configuration information to embed into the tcl
 *	binary library.
 *
 * Copyright (c) 2002 Andreas Kupries <andreas_kupries@users.sourceforge.net>
 * Copyright (c) 2017 Stuart Cassoff <stwo@users.sourceforge.net>
 *
 * See the file "license.terms" for information on usage and redistribution of
 * this file, and for a DISCLAIMER OF ALL WARRANTIES.
 */

/* Note, the definitions in this module are influenced by the following C
 * preprocessor macros:
 *
 * OSCMa  = shortcut for "old style configuration macro activates"
 * NSCMdt = shortcut for "new style configuration macro declares that"
 *
 * - TCL_THREADS		OSCMa compilation as threaded.
 * - TCL_MEM_DEBUG		OSCMa memory debugging.
 *
 * - TCL_CFG_DO64BIT		NSCMdt tk is compiled for a 64bit system.
 * - NDEBUG			NSCMdt tk is compiled with symbol info off.
 * - TCL_CFG_OPTIMIZED		NSCMdt tk is compiled with cc optimizations on
 * - TCL_CFG_PROFILED		NSCMdt tk is compiled with profiling info.
 *
 * - _WIN32 || __CYGWIN__	The value for the fontsytem key will be
 *   MAC_OSX_TK			chosen based on these macros/defines.
 *   HAVE_XFT			NSCMdt xft font support was requested.
 *
 * - CFG_RUNTIME_*		Paths to various stuff at runtime.
 * - CFG_INSTALL_*		Paths to various stuff at installation time.
 *
 * - TCL_CFGVAL_ENCODING	string containing the encoding used for the
 *				configuration values.
 */

#include "tkInt.h"


#ifndef TCL_CFGVAL_ENCODING
#define TCL_CFGVAL_ENCODING "ascii"
#endif

/*
 * Use C preprocessor statements to define the various values for the embedded
 * configuration information.
 */

#ifdef TCL_THREADS
#  define  CFG_THREADED		"1"
#else
#  define  CFG_THREADED		"0"
#endif

#ifdef TCL_MEM_DEBUG
#  define CFG_MEMDEBUG		"1"
#else
#  define CFG_MEMDEBUG		"0"
#endif

#ifdef TCL_CFG_DO64BIT
#  define CFG_64		"1"
#else
#  define CFG_64		"0"
#endif

#ifndef NDEBUG
#  define CFG_DEBUG		"1"
#else
#  define CFG_DEBUG		"0"
#endif

#ifdef TCL_CFG_OPTIMIZED
#  define CFG_OPTIMIZED		"1"
#else
#  define CFG_OPTIMIZED		"0"
#endif

#ifdef TCL_CFG_PROFILED
#  define CFG_PROFILED		"1"
#else
#  define CFG_PROFILED		"0"
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#  define CFG_FONTSYSTEM	"gdi"
#elif defined(MAC_OSX_TK)
#  define CFG_FONTSYSTEM	"cocoa"
#elif defined(HAVE_XFT)
#  define CFG_FONTSYSTEM	"xft"
#else
#  define CFG_FONTSYSTEM	"x11"
#endif

static Tcl_Config const cfg[] = {
    {"debug",			CFG_DEBUG},
    {"threaded",		CFG_THREADED},
    {"profiled",		CFG_PROFILED},
    {"64bit",			CFG_64},
    {"optimized",		CFG_OPTIMIZED},
    {"mem_debug",		CFG_MEMDEBUG},
    {"fontsystem",		CFG_FONTSYSTEM},

    /* Runtime paths to various stuff */

    {"libdir,runtime",		CFG_RUNTIME_LIBDIR},
    {"bindir,runtime",		CFG_RUNTIME_BINDIR},
    {"scriptdir,runtime",	CFG_RUNTIME_SCRDIR},
    {"includedir,runtime",	CFG_RUNTIME_INCDIR},
    {"docdir,runtime",		CFG_RUNTIME_DOCDIR},
    {"demodir,runtime",		CFG_RUNTIME_DEMODIR},

    /* Installation paths to various stuff */

    {"libdir,install",		CFG_INSTALL_LIBDIR},
    {"bindir,install",		CFG_INSTALL_BINDIR},
    {"scriptdir,install",	CFG_INSTALL_SCRDIR},
    {"includedir,install",	CFG_INSTALL_INCDIR},
    {"docdir,install",		CFG_INSTALL_DOCDIR},
    {"demodir,install",		CFG_INSTALL_DEMODIR},

    /* Last entry, closes the array */
    {NULL, NULL}
};

void
TkInitEmbeddedConfigurationInformation(
    Tcl_Interp *interp)		/* Interpreter the configuration command is
				 * registered in. */
{
    Tcl_RegisterConfig(interp, "tk", cfg, TCL_CFGVAL_ENCODING);
}

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 4
 * fill-column: 78
 * End:
 */

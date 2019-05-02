################################################################################
# \file module.mk
# \version 5.48
#
# \brief
# Segger Graphical user interface for embedded applications, core software 
# component hard FP, with operating system and touch support.
# It is required in any emWin display applications which use OS and touch input.
#
################################################################################
# \copyright
# Copyright 2018-2019, Cypress Semiconductor Corporation.  All rights reserved.
# You may use this file only in accordance with the license, terms, conditions,
# disclaimers, and limitations in the end user license agreement accompanying
# the software package with which this file was provided.
################################################################################

ifeq ($(WHICHFILE),true)
$(info Processing $(lastword $(MAKEFILE_LIST)) file from directory $(PWD))
$(info Path: $(MAKEFILE_LIST))
endif

#
# Needed by describe goal processing
#
ifeq ($(MAKECMDGOALS),describe)
ifndef PLATFORMS_VERSION
PLATFORMS_VERSION=1.0
endif
include $(CYSDK)/libraries/platforms-$(PLATFORMS_VERSION)/common/swcomps.mk
endif

#
# The internal tag name of the software component
#
MIDDLEWARE_EMWIN_OSTS_HARDFP_NAME=MIDDLEWARE_EMWIN_OSTS_HARDFP

#
# If defined, the list of legal PLATFORM values for this component.
# If not defined, this component is valid for all values of PLATFORM
#
CY_SUPPORTED_PLATFORM_LIST=PSOC6_DUAL_CORE PSoC6_cm4_dual PSoC6_cm0p PSOC6_SINGLE_CORE PSoC6_cm4_single

#
# If defined, the list of legal TOOLCHAIN values for this component. If not
# defined, this component is valid for all values of TOOLCHAIN
#
#CY_SUPPORTED_TOOLCHAIN_LIST=

#
# Used by the IDE to group and categorize components.
#
CY_COMP_CATEGORY=Middleware

#
# The displayed human readable name of the component
#
CY_COMP_NAME_DISPLAY=Segger emWin Core, OS, Touch, Hard FP v5.48

#
# The name in the form of an identifier ([a-z_][a-z0-9_]*).
# Used to generate directories in the IDE.
# 
CY_COMP_NAME_ID=middlewareemWinnOSnTSHardFp

#
# The human readable description of the component
#
CY_COMP_DESCR=Segger Graphical user interface for embedded applications, \
	core software component hard FP, with operating system and touch support. \
	It is required in any emWin display applications which use OS and touch input.


#
# The type of component ...
#   link - means link the source code from the IDE project to the SDK
#   copy - means copy the source code into the IDE project
#
CY_COMP_TYPE=link

#
# Defines if the component can change based on which artifact is being used
#
CY_COMP_PER_ARTIFACT=false

#
# The list of components this component is dependent on. Path is relative the
# the SDK's libraries folder.
#
CY_COMP_DEPS= \
    $(CY_PSOC_LIB_COMP_MIDDLEWARE_BASE)/emWin/MT/core/include \
    $(CY_PSOC_LIB_COMP_MIDDLEWARE_BASE)/emWin/MT/core/config/os

#
# Used by the build recipe for an ELF file to add this component
# to the list of components that must be included
#
$(CYARTIFACT)_OBJ_COMP_TAG_LIST += $(MIDDLEWARE_EMWIN_OSTS_HARDFP_NAME)

#
# Defines the series of needed make variables that include this component in the
# build process.  Also defines the describe target if we are describing a component
#
$(MIDDLEWARE_EMWIN_OSTS_HARDFP_NAME)_INCLUDES=\
    -I$(CY_PSOC_LIB_COMP_MIDDLEWARE)/emWin/GUI/Libs/hardfp/COMPONENT_EMWIN_OSTS

ifeq ($(TOOLCHAIN),GCC)
CY_EMWIN_LIB = \
    ../../../GUI/Libs/hardfp/COMPONENT_EMWIN_OSTS/TOOLCHAIN_GCC_ARM/libemWin_osts_cm4f_gcc.a
else
ifeq ($(TOOLCHAIN),IAR)
CY_EMWIN_LIB = \
    ../../../GUI/Libs/hardfp/COMPONENT_EMWIN_OSTS/TOOLCHAIN_IAR/libemWin_osts_cm4f_iar.a
else
ifeq ($(TOOLCHAIN),ARMCC)
CY_EMWIN_LIB = \
    ../../../GUI/Libs/hardfp/COMPONENT_EMWIN_OSTS/TOOLCHAIN_ARMC6/libemWin_osts_cm4f_armc6.ar
endif
endif
endif

$(eval $(call \
    CY_DECLARE_SWCOMP_OBJECT,$(MIDDLEWARE_EMWIN_OSTS_HARDFP_NAME),\
    $(lastword $(MAKEFILE_LIST)),\
    $(CY_EMWIN_LIB)\
    ../../../GUI/Libs/hardfp/COMPONENT_EMWIN_OSTS/GUIConf.h))


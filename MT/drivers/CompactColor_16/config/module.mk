################################################################################
# \file module.mk
# \version 5.48
#
# \brief
# Segger Graphical user interface for embedded applications, CompactColor_16 
# driver config files.
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
MIDDLEWARE_EMWIN_COMPACTCOLOR_16_CFG_NAME=MIDDLEWARE_EMWIN_COMPACTCOLOR_16_CFG

#
# If defined, the space separated list of legal OSNS values for
# this component. If not defined, this component is valid for all
# values of OSNS
#
#CY_SUPPORTED_OSNS_LIST=

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
CY_COMP_NAME_DISPLAY=Segger emWin CompactColor_16 display driver config files v5.48

#
# The name in the form of an identifier ([a-z_][a-z0-9_]*).
# Used to generate directories in the IDE.
# 
CY_COMP_NAME_ID=middlewareemWinCompactColor16Cfg

#
# The human readable description of the component
#
CY_COMP_DESCR=Segger Graphical user interface for embedded applications, \
	CompactColor_16 driver config files.
#
# CY_VISIBLE will decide whether to show the component in middleware configurator or not.
# If CY_VISIBLE set to Y then it will be shown up in middleware. If CY_VISIBLE set to N then
# component will not be shown up in middleware.
#
CY_VISIBLE=N

#
# The type of component ...
#   link - means link the source code from the IDE project to the SDK
#   copy - means copy the source code into the IDE project and preserve hierarchy
#   copyto - means copy the source code into the IDE project as is
#
CY_COMP_TYPE=copyto

#
# Defines if the component can change based on which artifact is being used
#
CY_COMP_PER_ARTIFACT=true

#
# Relative project directory to copy the source file(s) to
#
ifeq ($(CYARTIFACT),mainapp_cm0p)
	SOURCE_DIR=./Source_cm0p
else
	SOURCE_DIR=./Source
endif

CY_COMP_COPYTO_DIR=$(SOURCE_DIR)

#
# The list of components this component is dependent on. Path is relative the
# the SDK's libraries folder.
#
CY_COMP_DEPS=

#
# Used by the build recipe for an ELF file to add this component
# to the list of components that must be included
#
$(CYARTIFACT)_OBJ_COMP_TAG_LIST += $(MIDDLEWARE_EMWIN_COMPACTCOLOR_16_CFG_NAME)

#
# Defines the series of needed make variables that include this component in the
# build process.  Also defines the describe target if we are describing a component
#
$(MIDDLEWARE_EMWIN_COMPACTCOLOR_16_CFG_NAME)_INCLUDES=

$(eval $(call \
    CY_DECLARE_SWCOMP_OBJECT,$(MIDDLEWARE_EMWIN_COMPACTCOLOR_16_CFG_NAME),\
    $(lastword $(MAKEFILE_LIST)),\
    ../../../../Sample/LCDConf/GUIDRV_CompactColor_16/LCDConf.h\
    ../../../../Sample/LCDConf/GUIDRV_CompactColor_16/Generic/LCDConf.c\
    ../../../../Sample/LCDConf/GUIDRV_CompactColor_16/Generic/LCDConf_CompactColor_16.h))


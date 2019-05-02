################################################################################
# \file module.mk
# \version 5.48
#
# \brief
# Segger Graphical user interface for embedded applications, core software 
# component soft FP, without operating system support and without touch support.
# It is required in any emWin display applications.
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
MIDDLEWARE_EMWIN_INCLUDE_NAME=MIDDLEWARE_EMWIN_INCLUDE

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
CY_COMP_NAME_DISPLAY=Segger emWin include files, v5.48

#
# The name in the form of an identifier ([a-z_][a-z0-9_]*).
# Used to generate directories in the IDE.
# 
CY_COMP_NAME_ID=middlewareemWinInclude

#
# The human readable description of the component
#
CY_COMP_DESCR=Segger Graphical user interface for embedded applications, \
	include files.

#
# CY_VISIBLE will decide whether to show the component in middleware configurator or not.
# If CY_VISIBLE set to Y then it will be shown up in middleware. If CY_VISIBLE set to N then
# component will not be shown up in middleware.
#
CY_VISIBLE=N

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

#
# Used by the build recipe for an ELF file to add this component
# to the list of components that must be included
#
$(CYARTIFACT)_OBJ_COMP_TAG_LIST += $(MIDDLEWARE_EMWIN_INCLUDE_NAME)

#
# Defines the series of needed make variables that include this component in the
# build process.  Also defines the describe target if we are describing a component
#
$(MIDDLEWARE_EMWIN_INCLUDE_NAME)_INCLUDES=\
    -I$(CY_PSOC_LIB_COMP_MIDDLEWARE)/emWin/GUI/Include


$(eval $(call \
    CY_DECLARE_SWCOMP_OBJECT,$(MIDDLEWARE_EMWIN_INCLUDE_NAME),\
    $(lastword $(MAKEFILE_LIST)),\
    ../../../GUI/Include/BUTTON.h\
    ../../../GUI/Include/BUTTON_Private.h\
    ../../../GUI/Include/CALENDAR.h\
    ../../../GUI/Include/CHECKBOX.h\
    ../../../GUI/Include/CHECKBOX_Private.h\
    ../../../GUI/Include/CHOOSECOLOR.h\
    ../../../GUI/Include/CHOOSEFILE.h\
    ../../../GUI/Include/DIALOG.h\
    ../../../GUI/Include/DIALOG_Intern.h\
    ../../../GUI/Include/DROPDOWN.h\
    ../../../GUI/Include/DROPDOWN_Private.h\
    ../../../GUI/Include/EDIT.h\
    ../../../GUI/Include/EDIT_Private.h\
    ../../../GUI/Include/FRAMEWIN.h\
    ../../../GUI/Include/FRAMEWIN_Private.h\
    ../../../GUI/Include/Global.h\
    ../../../GUI/Include/GRAPH.h\
    ../../../GUI/Include/GRAPH_Private.h\
    ../../../GUI/Include/GUI.h\
    ../../../GUI/Include/GUI__BiDi2_Brackets_800.h\
    ../../../GUI/Include/GUI__BiDi2_Types_800.h\
    ../../../GUI/Include/GUI_ARRAY.h\
    ../../../GUI/Include/GUI_ARRAY_Private.h\
    ../../../GUI/Include/GUI_BMP_Private.h\
    ../../../GUI/Include/GUI_ConfDefaults.h\
    ../../../GUI/Include/GUI_Debug.h\
    ../../../GUI/Include/GUI_FontIntern.h\
    ../../../GUI/Include/GUI_GCache_Private.h\
    ../../../GUI/Include/GUI_GIF_Private.h\
    ../../../GUI/Include/GUI_HOOK.h\
    ../../../GUI/Include/GUI_JPEG_Private.h\
    ../../../GUI/Include/GUI_Private.h\
    ../../../GUI/Include/GUI_SetOrientation.h\
    ../../../GUI/Include/GUI_SetOrientationCX.h\
    ../../../GUI/Include/GUI_SPRITE_Private.h\
    ../../../GUI/Include/GUI_Type.h\
    ../../../GUI/Include/GUI_Version.h\
    ../../../GUI/Include/GUI_VNC.h\
    ../../../GUI/Include/GUIDRV_BitPlains.h\
    ../../../GUI/Include/GUIDRV_FlexColor.h\
    ../../../GUI/Include/GUIDRV_Generic.h\
    ../../../GUI/Include/GUIDRV_Lin.h\
    ../../../GUI/Include/HEADER.h\
    ../../../GUI/Include/HEADER_Private.h\
    ../../../GUI/Include/ICONVIEW.h\
    ../../../GUI/Include/ICONVIEW_Private.h\
    ../../../GUI/Include/IMAGE.h\
    ../../../GUI/Include/IMAGE_Private.h\
    ../../../GUI/Include/IP_FS.h\
    ../../../GUI/Include/KNOB.h\
    ../../../GUI/Include/KNOB_Private.h\
    ../../../GUI/Include/LCD.h\
    ../../../GUI/Include/LCD_ConfDefaults.h\
    ../../../GUI/Include/LCD_Private.h\
    ../../../GUI/Include/LCD_Protected.h\
    ../../../GUI/Include/LCD_SIM.h\
    ../../../GUI/Include/LISTBOX.h\
    ../../../GUI/Include/LISTBOX_Private.h\
    ../../../GUI/Include/LISTVIEW.h\
    ../../../GUI/Include/LISTVIEW_Private.h\
    ../../../GUI/Include/LISTWHEEL.h\
    ../../../GUI/Include/LISTWHEEL_Private.h\
    ../../../GUI/Include/MENU.h\
    ../../../GUI/Include/MENU_Private.h\
    ../../../GUI/Include/MESSAGEBOX.h\
    ../../../GUI/Include/MULTIEDIT.h\
    ../../../GUI/Include/MULTIPAGE.h\
    ../../../GUI/Include/MULTIPAGE_Private.h\
    ../../../GUI/Include/PROGBAR.h\
    ../../../GUI/Include/PROGBAR_Private.h\
    ../../../GUI/Include/RADIO.h\
    ../../../GUI/Include/RADIO_Private.h\
    ../../../GUI/Include/SCROLLBAR.h\
    ../../../GUI/Include/SCROLLBAR_Private.h\
    ../../../GUI/Include/SEGGER.h\
    ../../../GUI/Include/SLIDER.h\
    ../../../GUI/Include/SLIDER_Private.h\
    ../../../GUI/Include/SPINBOX.h\
    ../../../GUI/Include/SPINBOX_Private.h\
    ../../../GUI/Include/SWIPELIST.h\
    ../../../GUI/Include/SWIPELIST_Private.h\
    ../../../GUI/Include/TEXT.h\
    ../../../GUI/Include/TEXT_Private.h\
    ../../../GUI/Include/TREEVIEW.h\
    ../../../GUI/Include/TREEVIEW_Private.h\
    ../../../GUI/Include/WIDGET.h\
    ../../../GUI/Include/WINDOW_Private.h\
    ../../../GUI/Include/WM.h\
    ../../../GUI/Include/WM_GUI.h\
    ../../../GUI/Include/WM_Intern.h))


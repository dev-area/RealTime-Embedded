#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/PROGRA~1/TEXASI~1/ipc_1_21_02_23/packages;C:/PROGRA~1/TEXASI~1/bios_6_30_02_42/packages
override XDCROOT = C:/PROGRA~1/TEXASI~1/xdctools_3_20_03_63
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/PROGRA~1/TEXASI~1/ipc_1_21_02_23/packages;C:/PROGRA~1/TEXASI~1/bios_6_30_02_42/packages;C:/PROGRA~1/TEXASI~1/xdctools_3_20_03_63/packages;..
HOSTOS = Windows
endif

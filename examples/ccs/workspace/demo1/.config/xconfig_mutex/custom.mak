## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,11e linker.cmd \
  package/cfg/mutex_x11e.o11e \

linker.cmd: package/cfg/mutex_x11e.xdl
	$(SED) 's"^\"\(package/cfg/mutex_x11ecfg.cmd\)\"$""\"C:/Documents and Settings/Administrator/My Documents/workspace/demo1/.config/xconfig_mutex/\1\""' package/cfg/mutex_x11e.xdl > $@

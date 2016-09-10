mod_colormap.la: mod_colormap.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_colormap.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_colormap.la

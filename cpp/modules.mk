mod_randomtrip.la: mod_randomtrip.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_randomtrip.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_randomtrip.la

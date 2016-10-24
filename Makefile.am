AUTOMAKE_OPTIONS = foreign
SUBDIRS = src/ParserCpp src/PamAutoMount
install-exec-hook:
	$(LN_S) $(libdir)/libpam_automount.so /usr/lib/libpam_automount.so
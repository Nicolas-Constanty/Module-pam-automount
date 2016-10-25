AUTOMAKE_OPTIONS = foreign
SUBDIRS = src/ParserCpp src/PamAutoMount
install-exec-hook:
	$(LN_S) $(libdir)/libpam_automount.so /lib/x84_64-linux-gnu/security/pam_automount.so

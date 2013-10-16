#
# Generated from addCPPProject.sh, by dufaure@etud (Wed, 16 Oct 2013 10:24:44 +0200)
#
-include ../../Makefile.options
CCFLAGS=$(CCFLAGS_DEBUG)
LDFLAGS=$(LDFLAGS_DEBUG)
SRCDIR=../../src

$(EXEC): $(OBJS)
		$(LD) $(OBJS) $(LIBDIRS) $(LIBFLAGS) -Wl,$(LDFLAGS) -o $(EXEC)

%.o: $(SRCDIR)/%.cpp
		$(CC) $(INCDIRS) $(CCFLAGS) -c $<
		
clean:
		@rm -Rf $(UNCLEAN_FILES)

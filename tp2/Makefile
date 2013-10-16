#
# Generated from addCPPProject.sh, by dufaure@etud (Wed, 16 Oct 2013 10:24:44 +0200)
#
-include Makefile.options
.PHONY: debug release

all: debug

debug:
		@cd obj/debug && make
		@mv obj/debug/$(EXEC) .
        
release:
		@cd obj/release && make
		@mv obj/release/$(EXEC) .

clean:
		@cd obj/release && make clean
		@cd obj/debug && make clean
		@cd src && make clean
		@cd userCode && make distclean
		@rm -Rf $(UNCLEAN_FILES)
		
distclean: clean
		@rm -Rf $(TARBALL_DIR)
		@rm -Rf $(EXEC)

tarball: distclean
		@if [ ! -x $(TAR) ] ; then echo "" && echo "        unable to find TAR=$(TAR) binary" && exit 1 ; fi
		@if [ ! -x $(MD5) ] ; then echo "" && echo "        unable to find MD5=$(MD5) binary" && exit 1 ; fi
		@mkdir $(PROJECT_NAME)
		@cp -R $(TARBALL_FILES) $(PROJECT_NAME)
		@$(TAR) $(PROJECT_TAR_FLAGS) $(PROJECT_NAME).$(PROJECT_TARBALL_EXT) $(PROJECT_NAME)
		@rm -Rf $(PROJECT_NAME)
		@$(MD5) $(PROJECT_NAME).$(PROJECT_TARBALL_EXT)
		@mkdir -p $(TARBALL_DIR)
		@cp $(PROJECT_NAME).$(PROJECT_TARBALL_EXT) ./$(TARBALL_DIR)/$(PROJECT_NAME)_$$(date -R|sed 's/ /_/g'|sed 's/\+//g'|sed 's/\,//g'|sed 's/\://g').$(PROJECT_TARBALL_EXT)
		@rm $(PROJECT_NAME).$(PROJECT_TARBALL_EXT)


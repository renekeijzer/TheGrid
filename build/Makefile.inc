include Makefile.local
include Targets/Makefile.modules

CXX 							= g++
CXXFLAGS						= -std=c++11
INCLUDES 						= 
LDLIBS							=
LDFLAGS							= 
SRC 							= 
UI 								= 
UI_HEADERS						=
MODULES 						= 

ifeq ($(OS),Windows_NT)
	CXXFLAGS 	+= -DWIN32 -fPIC
endif

ifeq ($(MAKECMDGOALS),grid)
	ifeq ($(OS),Windows_NT)
		INCLUDES 	+= 
		LDFLAGS		+= 
		LDLIBS 		+= 
		CXXFLAGS	+= 
	else
		INCLUDES 	+= 
		LDFLAGS		+= 
		LDLIBS 		+= 
	endif
	include Targets/Makefile.vps
endif
ifeq ($(MAKECMDGOALS),clean)
	include Targets/Makefile.clean
else
	INCLUDES 		+= $(patsubst %, -I%, $(MODULES))
	include $(MODULES:=module.mk)
	OBJ 			+= $(SRC:.cpp=.o)
endif


%.d : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MM -MT"$@" $< -MF $@
	
%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
	
moc_%.cpp : %.h
	$(MOC) $< -o $@
	
ui_%.h : %.ui
	$(UIC) $< -o $@
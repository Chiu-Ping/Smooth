# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/zhangyulei/softwares/cmake-3.14.4/install/bin/cmake

# The command to remove a file.
RM = /home/zhangyulei/softwares/cmake-3.14.4/install/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shenqiuping/RPC_Anal/Smooth

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build

# Include any dependencies generated for this target.
include CMakeFiles/Channel.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Channel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Channel.dir/flags.make

G__Channel.cxx: ../../../include/ChannelLinkDef.hpp
G__Channel.cxx: ../../../include/Channel.hpp
G__Channel.cxx: ../../../include/Channel.hpp
G__Channel.cxx: ../../../include/ChannelLinkDef.hpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating G__Channel.cxx, libChannel_rdict.pcm, libChannel.rootmap"
	/home/zhangyulei/softwares/cmake-3.14.4/install/bin/cmake -E env LD_LIBRARY_PATH=/home/zhangyulei/softwares/Root-6.16/install/lib:/home/zhangyulei/softwares/Geant4-10.05/install/lib64:/home/zhangyulei/softwares/CEPC/cepcsoft/x86_64-sl6-gcc49/external/QT/4.7.4/install/lib:/home/zhangyulei/softwares/Python/install3/lib:/home/zhangyulei/softwares/Root-6.16/install/lib:/home/zhangyulei/softwares/CEPC/cepcsoft/x86_64-sl6-gcc49/external/GCC/4.9.4//install/lib:/home/zhangyulei/softwares/CEPC/cepcsoft/x86_64-sl6-gcc49/external/GCC/4.9.4/install/lib64:/opt/intel/composer_xe_2013.3.163/compiler/lib/intel64:/opt/intel/composer_xe_2013.3.163/mpirt/lib/intel64:/opt/intel/mic/coi/host-linux-release/lib:/opt/intel/mic/myo/lib:/opt/intel/composer_xe_2013.3.163/compiler/lib/intel64:/opt/intel/composer_xe_2013.3.163/mkl/lib/intel64:/usr/lib64 /home/zhangyulei/softwares/Root-6.16/install/bin/rootcling -v2 -f G__Channel.cxx -s /home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build/libChannel.so -rml libChannel.so -rmf /home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build/libChannel.rootmap -I/home/shenqiuping/RPC_Anal/Smooth/bin/include -I/home/zhangyulei/softwares/Root-6.16/install/include -I/home/shenqiuping/RPC_Anal/Smooth/include /home/shenqiuping/RPC_Anal/Smooth/include/Channel.hpp /home/shenqiuping/RPC_Anal/Smooth/include/ChannelLinkDef.hpp

libChannel_rdict.pcm: G__Channel.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate libChannel_rdict.pcm

libChannel.rootmap: G__Channel.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate libChannel.rootmap

CMakeFiles/Channel.dir/src/Channel.cpp.o: CMakeFiles/Channel.dir/flags.make
CMakeFiles/Channel.dir/src/Channel.cpp.o: ../../../src/Channel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Channel.dir/src/Channel.cpp.o"
	/home/zhangyulei/softwares/CEPC/cepcsoft/x86_64-sl6-gcc49/external/GCC/4.9.4/install/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Channel.dir/src/Channel.cpp.o -c /home/shenqiuping/RPC_Anal/Smooth/src/Channel.cpp

CMakeFiles/Channel.dir/src/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Channel.dir/src/Channel.cpp.i"
	/home/zhangyulei/softwares/CEPC/cepcsoft/x86_64-sl6-gcc49/external/GCC/4.9.4/install/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shenqiuping/RPC_Anal/Smooth/src/Channel.cpp > CMakeFiles/Channel.dir/src/Channel.cpp.i

CMakeFiles/Channel.dir/src/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Channel.dir/src/Channel.cpp.s"
	/home/zhangyulei/softwares/CEPC/cepcsoft/x86_64-sl6-gcc49/external/GCC/4.9.4/install/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shenqiuping/RPC_Anal/Smooth/src/Channel.cpp -o CMakeFiles/Channel.dir/src/Channel.cpp.s

CMakeFiles/Channel.dir/G__Channel.cxx.o: CMakeFiles/Channel.dir/flags.make
CMakeFiles/Channel.dir/G__Channel.cxx.o: G__Channel.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Channel.dir/G__Channel.cxx.o"
	/home/zhangyulei/softwares/CEPC/cepcsoft/x86_64-sl6-gcc49/external/GCC/4.9.4/install/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Channel.dir/G__Channel.cxx.o -c /home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build/G__Channel.cxx

CMakeFiles/Channel.dir/G__Channel.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Channel.dir/G__Channel.cxx.i"
	/home/zhangyulei/softwares/CEPC/cepcsoft/x86_64-sl6-gcc49/external/GCC/4.9.4/install/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build/G__Channel.cxx > CMakeFiles/Channel.dir/G__Channel.cxx.i

CMakeFiles/Channel.dir/G__Channel.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Channel.dir/G__Channel.cxx.s"
	/home/zhangyulei/softwares/CEPC/cepcsoft/x86_64-sl6-gcc49/external/GCC/4.9.4/install/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build/G__Channel.cxx -o CMakeFiles/Channel.dir/G__Channel.cxx.s

# Object files for target Channel
Channel_OBJECTS = \
"CMakeFiles/Channel.dir/src/Channel.cpp.o" \
"CMakeFiles/Channel.dir/G__Channel.cxx.o"

# External object files for target Channel
Channel_EXTERNAL_OBJECTS =

libChannel.so: CMakeFiles/Channel.dir/src/Channel.cpp.o
libChannel.so: CMakeFiles/Channel.dir/G__Channel.cxx.o
libChannel.so: CMakeFiles/Channel.dir/build.make
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libCore.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libImt.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libRIO.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libNet.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libHist.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libGraf.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libGraf3d.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libGpad.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libROOTDataFrame.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libTree.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libTreePlayer.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libRint.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libPostscript.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libMatrix.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libPhysics.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libMathCore.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libThread.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libMultiProc.so
libChannel.so: /home/zhangyulei/softwares/Root-6.16/install/lib/libSpectrum.so
libChannel.so: CMakeFiles/Channel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library libChannel.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Channel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Channel.dir/build: libChannel.so

.PHONY : CMakeFiles/Channel.dir/build

CMakeFiles/Channel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Channel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Channel.dir/clean

CMakeFiles/Channel.dir/depend: G__Channel.cxx
CMakeFiles/Channel.dir/depend: libChannel_rdict.pcm
CMakeFiles/Channel.dir/depend: libChannel.rootmap
	cd /home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shenqiuping/RPC_Anal/Smooth /home/shenqiuping/RPC_Anal/Smooth /home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build /home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build /home/shenqiuping/RPC_Anal/Smooth/Run/Studying/build/CMakeFiles/Channel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Channel.dir/depend


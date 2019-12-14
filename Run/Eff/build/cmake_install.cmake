# Install script for directory: /home/shenqiuping/RPC_Anal/Smooth

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/shenqiuping/RPC_Anal/Smooth/bin")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/shenqiuping/RPC_Anal/Smooth/bin/Analysis" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/shenqiuping/RPC_Anal/Smooth/bin/Analysis")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/shenqiuping/RPC_Anal/Smooth/bin/Analysis"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/shenqiuping/RPC_Anal/Smooth/bin/Analysis")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/shenqiuping/RPC_Anal/Smooth/bin" TYPE EXECUTABLE FILES "/home/shenqiuping/RPC_Anal/Smooth/Run/Eff/build/Analysis")
  if(EXISTS "$ENV{DESTDIR}/home/shenqiuping/RPC_Anal/Smooth/bin/Analysis" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/shenqiuping/RPC_Anal/Smooth/bin/Analysis")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/home/shenqiuping/RPC_Anal/Smooth/bin/Analysis"
         OLD_RPATH "/home/shenqiuping/RPC_Anal/Smooth/bin/lib:/home/zhangyulei/softwares/Root-6.16/install/lib:/home/shenqiuping/RPC_Anal/Smooth/Run/Eff/build:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/shenqiuping/RPC_Anal/Smooth/bin/Analysis")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/shenqiuping/RPC_Anal/Smooth/Run/Eff/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

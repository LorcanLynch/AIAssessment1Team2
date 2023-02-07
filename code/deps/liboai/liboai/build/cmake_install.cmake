# Install script for directory: C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/build/Debug/oai.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/build/Release/oai.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/build/MinSizeRel/oai.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/build/RelWithDebInfo/oai.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/liboai.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/components" TYPE FILE FILES
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/components/completions.h"
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/components/edits.h"
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/components/embeddings.h"
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/components/files.h"
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/components/fine_tunes.h"
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/components/images.h"
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/components/models.h"
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/components/moderations.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/core" TYPE FILE FILES
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/core/authorization.h"
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/core/exception.h"
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/core/network.h"
    "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/include/core/response.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/dev/projects/beamer_slides/modules/aipfg/lectures/chatbots/lab/code/deps/liboai/liboai/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

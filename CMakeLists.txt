cmake_minimum_required(VERSION 3.0)
project(black_hole_tracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -fopenmp")

FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# Prevent compilation in-source
if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
    Message( " " )
    Message( FATAL_ERROR "Source and build  directories are the same.
 Create an empty build directory,
 change into it and re-invoke cmake")
endif()

#Path of CImg.h file relative to this file path
include_directories( external )
include_directories( src )

# ### CIMG related stuff
# Flags to enable native support for PNG image files, using the PNG library.
# ( http://www.libpng.org/ )
SET(CIMG_PNG_CCFLAGS  -Dcimg_use_png)

# ### Search Additional Libraries ##########
FIND_PACKAGE(PNG)
FIND_PACKAGE(ZLIB)

if(NOT WIN32)
    FIND_PACKAGE(X11)
    FIND_PACKAGE(Threads REQUIRED)
endif()
# #### End of additional libraries search ##########

### Configure Paths according to detected packages
if (ZLIB_FOUND)
    SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_ZLIB_CCFLAGS}")
    link_directories(${ZLIB_LIB_DIRS})
    include_directories(${ZLIB_INCLUDE_DIR})
    SET(SYSTEM_LIBS ${SYSTEM_LIBS} ${ZLIB_LIBRARIES})

    # PNG requires ZLIB
    if(PNG_FOUND)
        SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_PNG_CCFLAGS}")
        link_directories(${PNG_LIB_DIRS})
        include_directories(${PNG_INCLUDE_DIR} )
        SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${PNG_LIBRARIES} )
    endif()
endif()

if(NOT APPLE)
    if(NOT WIN32)
        if(X11_FOUND)
            SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_XSHM_CCFLAGS} ${CIMG_XRANDR_CCFLAGS}")
            SET(SYSTEM_LIBS ${SYSTEM_LIBS} Xext Xrandr)
        endif()
    endif(NOT WIN32)
endif(NOT APPLE)

if(X11_FOUND)
    link_directories(${X11_LIB_DIRS})
    include_directories(${X11_INCLUDE_DIR})
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${X11_LIBRARIES} )
endif()

if (NOT WIN32)
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${CMAKE_THREAD_LIBS_INIT} )
endif()

if( WIN32)
    SET( SYSTEM_LIBS  ${SYSTEM_LIBS}  gdi32 )
endif()

# Add CIMG Flags to Compilation Flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CIMG_CFLAGS}")


add_subdirectory(external/glm)

file(GLOB SOURCE_FILES
        "src/*.h"
        "src/*.cpp"
        "src/*.tcc"
        "src/*/*.h"
        "src/*/*.cpp"
        "src/*/*.tcc")

add_executable(black_hole_tracer ${SOURCE_FILES})
target_link_libraries(black_hole_tracer ${SYSTEM_LIBS} ${Boost_LIBRARIES})

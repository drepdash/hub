project(tNETencule)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAME_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(${CMAKE_SYSTEM_NAME} True)


#find_package(Event COMPONENTS core REQUIRED)
include_directories(${EVENT_CORE_INCLUDE_DIRS})
set(${EVENT_CORE_LIBRARY}, ${USER_EVENT_CORE_LIBRARY})

set(SOURCES_LIST hub.c
	main.c)

if(Linux)
	set(SOURCES_LIST ${SOURCES_LIST} tun-linux.c)
elseif(Windows)
	set(SOURCES_LIST ${SOURCES_LIST} tun-windows.c)
else()
	set(SOURCES_LIST ${SOURCES_LIST} tun-bsd.c)
endif(Linux)


add_definitions(-D${CMAKE_SYSTEM_NAME})

add_executable(tNET
	${SOURCES_LIST})

target_link_libraries(tNET
	${EVENT_LIBRARIES})

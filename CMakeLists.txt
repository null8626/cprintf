cmake_minimum_required(VERSION 2.8.12)

set(CPRINTF_SRC cprintf.c)
set(CPRINTF_NAME cprintf)
set(CPRINTF_VERSION 1.1.0)

project(${CPRINTF_NAME})

if(WIN32)
set(CPRINTF_NAME_STATIC ${CPRINTF_NAME}_s)
else()
set(CPRINTF_NAME_STATIC ${CPRINTF_NAME})
endif()

add_library(${CPRINTF_NAME} SHARED ${CPRINTF_SRC})
add_library(${CPRINTF_NAME}_static STATIC ${CPRINTF_SRC})

add_compile_definitions(CPRINTF_BUILDING _CRT_SECURE_NO_WARNINGS)

if(WIN32)
target_compile_definitions(${CPRINTF_NAME} PUBLIC CPRINTF_DLL)
endif()

set_property(TARGET ${CPRINTF_NAME} PROPERTY OUTPUT_NAME ${CPRINTF_NAME})
set_property(TARGET ${CPRINTF_NAME}_static PROPERTY OUTPUT_NAME ${CPRINTF_NAME_STATIC})

set_target_properties(${CPRINTF_NAME} ${CPRINTF_NAME}_static PROPERTIES
  VERSION               ${CPRINTF_VERSION}
  SOVERSION             1
  MSVC_RUNTIME_LIBRARY  MultiThreadedDLL
)
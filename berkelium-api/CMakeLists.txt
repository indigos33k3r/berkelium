CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)

PROJECT(berkelium-api)

IF(NOT DEFINED BERKELIUM_BUILD)
	MESSAGE(FATAL_ERROR "this project should be build using berkelium build system!")
ENDIF()

###########
## Build API Doc
## --------
#  berkelium-cpp/src/demo/*/*.c
FILE(GLOB_RECURSE DOC_SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/.." "../berkelium-cpp/src/demo/*/*.cpp" "../berkelium-cpp/src/demo/*/*.c" "../berkelium-java/src/test/java/org/berkelium/demo/*/*.java")
FOREACH(SOURCE ${DOC_SOURCE})
	GET_FILENAME_COMPONENT(FILE "../${SOURCE}" ABSOLUTE)
	LIST(APPEND DOC_DEPS "${FILE}")
	GET_FILENAME_COMPONENT(FILE "${SOURCE}" ABSOLUTE)
	FILE(RELATIVE_PATH FILE "${CMAKE_CURRENT_SOURCE_DIR}" "${FILE}")
	LIST(APPEND DOC "${FILE}")
ENDFOREACH()
LIST(SORT DOC)

ADD_EXECUTABLE(buildjsdata buildjsdata.c)
ADD_CUSTOM_COMMAND(OUTPUT data.js COMMAND buildjsdata berkelium-api/data.js ${DOC} DEPENDS buildjsdata ${DOC_DEPS} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/..")

ADD_CUSTOM_TARGET(doc ALL DEPENDS data.js)

INCLUDE(CMakeParseArguments)

FIND_PROGRAM(XSLTPROC xsltproc DOC "xsltproc transforms XML via XSLT")

SET(API ${CMAKE_CURRENT_SOURCE_DIR}/api CACHE PATH "berkelium api files")

SET_DIRECTORY_PROPERTIES(PROPERTIES CLEAN_NO_CUSTOM 1)

MACRO(XSLT TARGET XSLT XML)
	CMAKE_PARSE_ARGUMENTS(ARG "" "" "ARGS" ${ARGN})

	SET(ARGS "")
	LIST(LENGTH ARG_ARGS to)
	SET(i 0)

	WHILE(${i} LESS ${to})
		LIST(GET ARG_ARGS ${i} key)
		MATH(EXPR i "${i} + 1")

		LIST(GET ARG_ARGS ${i} value)
		MATH(EXPR i "${i} + 1")

		LIST(APPEND ARGS "--stringparam")
		LIST(APPEND ARGS "${key}")
		LIST(APPEND ARGS "${value}")
	ENDWHILE()

	LIST(APPEND ARGS "-o")
	LIST(APPEND ARGS "${TARGET}")
	LIST(APPEND ARGS "${XSLT}")
	LIST(APPEND ARGS "${XML}")

	ADD_CUSTOM_COMMAND(
		OUTPUT "${TARGET}"
		COMMAND "${XSLTPROC}" ${ARGS}
		DEPENDS "${XSLT}" "${XML}"
		COMMENT "xslt ${TARGET}"
	)
ENDMACRO()

MACRO(API TARGET XSLT)
	GET_FILENAME_COMPONENT(FILE "${TARGET}" ABSOLUTE)
	CMAKE_PARSE_ARGUMENTS(ARG "" "" "ARGS" ${ARGN})
	XSLT("${FILE}" "${XSLT}" "${API}/api.xml" ARGS "${ARG_ARGS}")
ENDMACRO()

###########
## Build API Dependencies
## --------
SET(API_DEPS "")

MACRO(BUILD_API_DEPS VAR TARGET LANG)
	# build absolute path
	GET_FILENAME_COMPONENT(FILE "${TARGET}" ABSOLUTE)
	# append to API_DEPS
	LIST(APPEND API_DEPS "${FILE}")
	XSLT("${FILE}" "${API}/api-all.xslt" "${API}/api.xml" ARGS "list" "${LANG}")

	# read deps into VAR
	# you need to recall cmake if you added new files to the api!!
	FILE(STRINGS "${FILE}" "${VAR}")
	SET("${VAR}" "${${VAR}}" CACHE STRING "cached source deps" FORCE)
ENDMACRO()

BUILD_API_DEPS(BERKELIUM_SRC_CPP deps/cpp.txt cpp)
BUILD_API_DEPS(BERKELIUM_SRC_JAVA deps/java.txt java)
BUILD_API_DEPS(BERKELIUM_SRC_JAVA_IMPL deps/java-impl.txt java-impl)
BUILD_API_DEPS(BERKELIUM_SRC_JNI deps/jni.txt jni)

###########
## Build JNI Implementation
## --------
MACRO(BUILD_API_IMPL TARGET XSLT)
	# build absolute path
	GET_FILENAME_COMPONENT(FILE "${TARGET}" ABSOLUTE)
	# append to API_DEPS
	LIST(APPEND API_DEPS "${FILE}")
	XSLT("${FILE}" "${API}/${XSLT}" "${API}/api.xml")
ENDMACRO()

BUILD_API_IMPL("../berkelium-cpp/include/berkelium.h" "api-c.xslt")
BUILD_API_IMPL("../berkelium-cpp/include/Berkelium/API/Berkelium.hpp" "api-cpp-global.xslt")
BUILD_API_IMPL("../berkelium-cpp/src/lib/Impl/BerkeliumC.cpp" "api-c-impl.xslt")
BUILD_API_IMPL("../berkelium-java/src/main/cpp/berkelium-jni.cpp" "api-jni.xslt")

###########
## Build c++ Header Files with xslt
## --------
FOREACH(CLASS ${BERKELIUM_SRC_CPP})
	GET_FILENAME_COMPONENT(FILE "../berkelium-cpp/include/Berkelium/API/${CLASS}.hpp" ABSOLUTE)
	LIST(APPEND API_DEPS "${FILE}")
	XSLT("${FILE}" "${API}/api-cpp.xslt" "${API}/api.xml" ARGS "class" "${CLASS}")
ENDFOREACH()

###########
## Build Java Files with xslt
## --------
FOREACH(CLASS ${BERKELIUM_SRC_JAVA})
	GET_FILENAME_COMPONENT(FILE "../berkelium-java/src/main/java/org/berkelium/api/${CLASS}.java" ABSOLUTE)
	LIST(APPEND API_DEPS "${FILE}")
	XSLT("${FILE}" "${API}/api-java.xslt" "${API}/api.xml" ARGS "class" "${CLASS}")
ENDFOREACH()
FOREACH(CLASS ${BERKELIUM_SRC_JAVA_IMPL})
	GET_FILENAME_COMPONENT(FILE "../berkelium-java/src/main/java/org/berkelium/impl/${CLASS}Impl.java" ABSOLUTE)
	LIST(APPEND API_DEPS "${FILE}")
	XSLT("${FILE}" "${API}/api-java-impl.xslt" "${API}/api.xml" ARGS "class" "${CLASS}")
ENDFOREACH()

###########
## Note: rerun cmake
## --------
ADD_CUSTOM_COMMAND(
	OUTPUT rerun-cmake
	COMMAND ${CMAKE_COMMAND} -E echo_append
	COMMENT "You need to rerun cmake if you added new files!"
)

# this is not part of the default build
# call this command by hand if you changed the api
ADD_CUSTOM_TARGET(berkelium-api DEPENDS ${API_DEPS} rerun-cmake)

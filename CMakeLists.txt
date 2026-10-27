cmake_minimum_required(VERSION 3.19)

project(qdhrystone LANGUAGES C CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

qt_add_executable(qdhrystone WIN32 MACOSX_BUNDLE
	main.cpp
	qdhrystone.cpp qdhrystone.h
	qdhrystonewidget.ui
	qdhrystone.qrc
	dhrystone/dry.c dhrystone/dry2.c
)

if(WIN32)
	target_sources(qdhrystone PRIVATE qdhrystone.rc)
endif()

target_link_libraries(qdhrystone PRIVATE Qt6::Widgets)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(qdhrystone PRIVATE -Wall -Wextra)
endif()

# the Dhrystone benchmark, from https://github.com/teknoraver/benchs
# the code predates C23, where an empty parameter list means no parameters
set_target_properties(qdhrystone PROPERTIES C_STANDARD 17 C_EXTENSIONS ON)
# its main() is called by ours when run with --dhrystone
set_source_files_properties(dhrystone/dry.c PROPERTIES COMPILE_DEFINITIONS main=dhrystone_main)
# always optimize it, even in debug builds, or the scores are meaningless
set_source_files_properties(dhrystone/dry.c dhrystone/dry2.c PROPERTIES
	COMPILE_OPTIONS $<IF:$<C_COMPILER_ID:MSVC>,/O2,-O3>)

install(TARGETS qdhrystone
	BUNDLE DESTINATION .
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

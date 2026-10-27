cmake_minimum_required(VERSION 3.19)

project(qdhrystone LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

qt_add_executable(qdhrystone WIN32 MACOSX_BUNDLE
	main.cpp
	qdhrystone.cpp qdhrystone.h
	qdhrystonewidget.ui
	qdhrystone.qrc
)

if(WIN32)
	target_sources(qdhrystone PRIVATE dry_exe.h qdhrystone.rc)
endif()

target_link_libraries(qdhrystone PRIVATE Qt6::Widgets)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(qdhrystone PRIVATE -Wall -Wextra)
endif()

install(TARGETS qdhrystone
	BUNDLE DESTINATION .
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

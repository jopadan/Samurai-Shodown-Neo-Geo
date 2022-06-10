cmake_minimum_required(VERSION 3.0)
project(samurai_shodown LANGUAGES CXX)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "Samurai Shodown NEO-GEO")

if(CMAKE_C_COMPILER_LOADED)
  include (CheckIncludeFile)
  include (CheckCSourceCompiles)
elseif(CMAKE_CXX_COMPILER_LOADED)
  include (CheckIncludeFileCXX)
  include (CheckCXXSourceCompiles)
else()
  message(FATAL_ERROR "FindMath only works if either C or CXX language is enabled")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(GNUInstallDirs)
include(FindPkgConfig)
include(FindMath)
include(FindSDL2_mixer)
include(FindSDL2_image)

if(MSYS AND CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
set(CMAKE_INSTALL_PREFIX $ENV{MINGW_PREFIX} CACHE PATH $ENV{MINGW_PREFIX} FORCE)
endif()

set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD 23 )

set(SRC_DIR src)
set(INCLUDE_DIR src)

set(SOURCE_FILES
	${SRC_DIR}/Application.cpp
	${SRC_DIR}/Globals.cpp
	${SRC_DIR}/Main.cpp
	${SRC_DIR}/ModuleCollision.cpp
	${SRC_DIR}/ModuleEnding.cpp
	${SRC_DIR}/ModuleFadeToBlack.cpp
	${SRC_DIR}/ModuleFonts.cpp
	${SRC_DIR}/ModuleMenu.cpp
	${SRC_DIR}/ModuleMusic.cpp
	${SRC_DIR}/ModuleParticles.cpp
	${SRC_DIR}/ModulePetP1.cpp
	${SRC_DIR}/ModulePetP2.cpp
	${SRC_DIR}/ModulePlayer2.cpp
	${SRC_DIR}/ModuleSceneNakoruru.cpp
	${SRC_DIR}/ModuleSelect.cpp
	${SRC_DIR}/ModuleSlowdown.cpp
	${SRC_DIR}/ModuleUI.cpp
	${SRC_DIR}/ModuleVictoryHaohmaru.cpp
	${SRC_DIR}/ModuleSceneHaohmaru.cpp
	${SRC_DIR}/ModuleInput.cpp
	${SRC_DIR}/ModulePlayer.cpp
	${SRC_DIR}/ModuleRender.cpp
	${SRC_DIR}/ModuleTextures.cpp
	${SRC_DIR}/ModuleWindow.cpp
	${SRC_DIR}/ModuleReferee.cpp
)

set(INCLUDE_FILES
	${INCLUDE_DIR}/Animation.h
	${INCLUDE_DIR}/Application.h
	${INCLUDE_DIR}/Globals.h
	${INCLUDE_DIR}/MemLeaks.h
	${INCLUDE_DIR}/Module.h
	${INCLUDE_DIR}/ModuleCollision.h
	${INCLUDE_DIR}/ModuleEnding.h
	${INCLUDE_DIR}/ModuleFadeToBlack.h
	${INCLUDE_DIR}/ModuleFonts.h
	${INCLUDE_DIR}/ModuleMenu.h
	${INCLUDE_DIR}/ModuleMusic.h
	${INCLUDE_DIR}/ModuleParticles.h
	${INCLUDE_DIR}/ModulePetP1.h
	${INCLUDE_DIR}/ModulePetP2.h
	${INCLUDE_DIR}/ModulePlayer2.h
	${INCLUDE_DIR}/ModuleSceneNakoruru.h
	${INCLUDE_DIR}/ModuleSelect.h
	${INCLUDE_DIR}/ModuleSlowdown.h
	${INCLUDE_DIR}/ModuleUI.h
	${INCLUDE_DIR}/ModuleVictoryHaohmaru.h
	${INCLUDE_DIR}/ModuleSceneHaohmaru.h
	${INCLUDE_DIR}/ModuleInput.h
	${INCLUDE_DIR}/ModulePlayer.h
	${INCLUDE_DIR}/ModuleRender.h
	${INCLUDE_DIR}/ModuleTextures.h
	${INCLUDE_DIR}/ModuleWindow.h
	${INCLUDE_DIR}/p2Point.h
	${INCLUDE_DIR}/p2Qeue.h
	${INCLUDE_DIR}/ModuleReferee.h
)

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES} )

find_package(Math REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(OpenGL REQUIRED)

if(Math_FOUND AND SDL2_FOUND AND SDL2_mixer_FOUND AND SDL2_image_FOUND)
	target_include_directories(${PROJECT_NAME} PUBLIC Math::Math
		${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDES}
		${SDL2_IMAGE_INCLUDES} ${OPENGL_INCLUDE_DIR}
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> )
	target_link_libraries(${PROJECT_NAME} SDL2 Math::Math ${SDL2_LIBRARY}
		${SDL2_MIXER_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${OPENGL_LIBRARIES} )
endif()

set(CMAKE_INSTALL_DATADIR ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config )
install(DIRECTORY data/Assets data/Ui TYPE DATA COMPONENT assets)
install(FILES doc/Samurai_Shodown_Manual.pdf doc/index.html doc/haohmaru_anims.txt TYPE DOC COMPONENT documentation)
install(DIRECTORY doc/vscode doc/web doc/wiki TYPE DOC COMPONENT documentation)

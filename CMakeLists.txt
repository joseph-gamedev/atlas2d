cmake_minimum_required(VERSION 3.20)

project(GameEngine2D LANGUAGES CXX)

if(NOT WIN32)
  message(FATAL_ERROR "GameEngine2D currently supports Windows only.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(ENGINE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/engine/src")
set(ENGINE_DIR "${ENGINE_ROOT_DIR}/Core")
set(RENDER_D3D11_DIR "${ENGINE_ROOT_DIR}/Render/D3D11")
set(ENGINE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/engine/include")
set(GAME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/games/MonsterChaseGame")
set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets/MonsterChaseGame")
set(EXTERN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern")

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "${ENGINE_DIR}/*.cpp")
file(GLOB_RECURSE RENDER_D3D11_SOURCES CONFIGURE_DEPENDS "${RENDER_D3D11_DIR}/*.cpp")
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "${GAME_DIR}/*.cpp")

set(GAME_RESOURCES
  "${GAME_DIR}/MonsterChaseGame.rc"
  "${GAME_DIR}/MonsterChaseGame.ico"
  "${GAME_DIR}/small.ico"
)

add_library(RenderD3D11 STATIC ${RENDER_D3D11_SOURCES})
target_include_directories(RenderD3D11 PUBLIC "${RENDER_D3D11_DIR}")
target_compile_definitions(RenderD3D11 PRIVATE UNICODE _UNICODE $<$<CONFIG:Debug>:REPORT_LIVE_DXOBJECTS>)
target_link_libraries(RenderD3D11 PUBLIC d3d11)
add_library(GLib ALIAS RenderD3D11)

add_library(Engine STATIC ${ENGINE_SOURCES})
target_include_directories(Engine PUBLIC
  "${ENGINE_INCLUDE_DIR}/Core"
  "${ENGINE_ROOT_DIR}"
  "${EXTERN_DIR}"
)
target_compile_definitions(Engine PRIVATE UNICODE _UNICODE)
target_link_libraries(Engine PUBLIC RenderD3D11)

add_executable(MonsterChaseGame WIN32 ${GAME_SOURCES} ${GAME_RESOURCES})
target_include_directories(MonsterChaseGame PRIVATE
  "${GAME_DIR}"
  "${ENGINE_INCLUDE_DIR}/Core"
  "${ENGINE_ROOT_DIR}"
)
target_compile_definitions(MonsterChaseGame PRIVATE UNICODE _UNICODE _WINDOWS)
target_link_libraries(MonsterChaseGame PRIVATE Engine)

set_target_properties(MonsterChaseGame PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:MonsterChaseGame>"
)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT MonsterChaseGame)

add_custom_command(TARGET MonsterChaseGame POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${ASSETS_DIR}/data"
    "$<TARGET_FILE_DIR:MonsterChaseGame>/data"
)

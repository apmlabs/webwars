#the usual set of dependencies
find_package(OpenGL REQUIRED)

if(EMSCRIPTEN)
    message(STATUS "Emscripten build: using built-in SDL2 libraries via -sUSE_SDL flags")
    set(SDL2_INCLUDE_DIRS "${CMAKE_SYSROOT}/include/SDL2")
    set(SDL2_LIBRARIES "")
    set(SDL2_MIXER_LIBRARIES "")
    set(SDL2_IMAGE_LIBRARIES "")
    set(SDL2_TTF_LIBRARIES "")
    set(SDL2_FOUND TRUE)
else()
    find_package(SDL2 REQUIRED CONFIG)
    find_package(SDL2_mixer 2 REQUIRED)
    find_package(SDL2_net 2 REQUIRED)
    find_package(SDL2_image 2 REQUIRED)
    find_package(SDL2_ttf 2 REQUIRED)
endif()

#compile our rtl implementation
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtl)
include_directories(${PHYSFS_INCLUDE_DIR})
include_directories(${PHYSLAYER_INCLUDE_DIR})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})
add_subdirectory(rtl)

# convert list into pascal array
if(FONTS_DIRS)
  list(LENGTH FONTS_DIRS ndirs)
  set(FONTS_DIRS_ARRAY "array [0..${ndirs}] of PChar = (")
  foreach(fontdir ${FONTS_DIRS})
      set(FONTS_DIRS_ARRAY "${FONTS_DIRS_ARRAY}\n_P'${fontdir}',")
  endforeach(fontdir)
  set(FONTS_DIRS_ARRAY "${FONTS_DIRS_ARRAY}\nnil);\n")
else(FONTS_DIRS)
  set(FONTS_DIRS_ARRAY "array [0..1] of PChar = (nil, nil);")
endif(FONTS_DIRS)

configure_file(${CMAKE_SOURCE_DIR}/hedgewars/config.inc.in ${CMAKE_CURRENT_BINARY_DIR}/config.inc)

#get the list of pas files that are going to be converted and compiled
file(GLOB engine_sources_pas "${CMAKE_SOURCE_DIR}/hedgewars/*.pas")
list(REMOVE_ITEM engine_sources_pas "${CMAKE_SOURCE_DIR}/hedgewars/uTouch.pas")
list(REMOVE_ITEM engine_sources_pas "${CMAKE_SOURCE_DIR}/hedgewars/PNGh.pas")
list(REMOVE_ITEM engine_sources_pas "${CMAKE_SOURCE_DIR}/hedgewars/pas2cSystem.pas")
list(REMOVE_ITEM engine_sources_pas "${CMAKE_SOURCE_DIR}/hedgewars/pas2cRedo.pas")
list(REMOVE_ITEM engine_sources_pas "${CMAKE_SOURCE_DIR}/hedgewars/hwLibrary.pas")
if(NOVIDEOREC)
	list(REMOVE_ITEM engine_sources_pas "${CMAKE_SOURCE_DIR}/hedgewars/uVideoRec.pas")
endif()
if(NOT GL2)
    list(REMOVE_ITEM engine_sources_pas "${CMAKE_SOURCE_DIR}/hedgewars/uMatrix.pas")
endif()

#remove and readd hwengine so that it is compiled first, compiling every other file in the process
list(REMOVE_ITEM engine_sources_pas ${CMAKE_SOURCE_DIR}/hedgewars/hwengine.pas)
list(APPEND engine_sources_pas ${CMAKE_SOURCE_DIR}/hedgewars/hwengine.pas)

#process files .pas -> .c
foreach(sourcefile ${engine_sources_pas})
    get_filename_component(sourcename ${sourcefile} NAME_WE) #drops .pas
    list(APPEND engine_sources "${CMAKE_CURRENT_BINARY_DIR}/${sourcename}.c")
endforeach()

#add again files for external functions and for fpcrtl_ functions
list(APPEND engine_sources_pas ${CMAKE_SOURCE_DIR}/hedgewars/pas2cSystem.pas)
list(APPEND engine_sources_pas ${CMAKE_SOURCE_DIR}/hedgewars/pas2cRedo.pas)


set(pas2c_args -n hwengine
               -i ${CMAKE_SOURCE_DIR}/hedgewars
               -o ${CMAKE_CURRENT_BINARY_DIR}
               -a ${CMAKE_CURRENT_BINARY_DIR}
               -d ENDIAN_LITTLE
               -d DEBUGFILE)
if(BUILD_ENGINE_JS)
    set(pas2c_args ${pas2c_args} -d WEBGL)
endif()
if(BUILD_ENGINE_LIBRARY)
    set(pas2c_args ${pas2c_args} -d HWLIBRARY)
endif()
if(GL2)
    set(pas2c_args ${pas2c_args} -d GL2)
endif()
if(APPLE)
    set(pas2c_args ${pas2c_args} -d DARWIN)
endif()

if(LIBAV_FOUND)
    add_subdirectory(${CMAKE_SOURCE_DIR}/hedgewars/avwrapper ${CMAKE_CURRENT_BINARY_DIR}/avwrapper)
    list(APPEND HW_LINK_LIBS avwrapper)
    set(pas2c_args ${pas2c_args} -d USE_VIDEO_RECORDING)
endif()

if(BUILD_ENGINE_JS)
    set(pas2c_args ${pas2c_args} -d EMSCRIPTEN)
endif()

#invoke pas2c on main module, it will call all the others
add_custom_command(OUTPUT ${engine_sources}
                   COMMAND "${EXECUTABLE_OUTPUT_PATH}/pas2c${CMAKE_EXECUTABLE_SUFFIX}"
                   ARGS ${pas2c_args}
                   DEPENDS pas2c                     #converter tool
                           ${engine_sources_pas}     #original pascal file
                  )

#wrap conversion for all source in this command
add_custom_target(engine_c DEPENDS ${engine_sources})


if(BUILD_ENGINE_JS)
    set(HW_PRE_JS  "${CMAKE_SOURCE_DIR}/project_files/web/pre.js")
    set(HW_POST_JS "${CMAKE_SOURCE_DIR}/project_files/web/post.js")
    set(HW_DATA_DIR "${CMAKE_SOURCE_DIR}/share/hedgewars/Data")
    set(HW_DEMO_FILE "${CMAKE_SOURCE_DIR}/test.hwd")
    
    add_flag_append(CMAKE_C_FLAGS "--memory-init-file 0 -O0 --js-opts 0 -g4 -sASSERTIONS=2 -sUSE_SDL=2 -sUSE_SDL_IMAGE=1 -sUSE_LIBPNG=1 -sUSE_SDL_TTF=2 -sUSE_VORBIS=1 -sUSE_OGG=1 -sINITIAL_MEMORY=100007936 -sGL_UNSAFE_OPTS=0 -sLZ4=1 --preload-file ${HW_DATA_DIR}@/Data --preload-file ${HW_DEMO_FILE}@/test.hwd --post-js ${HW_POST_JS} --pre-js ${HW_PRE_JS}")
endif()

#compile the c files
add_definitions(-DPAS2C)
add_definitions(-DHWLIBRARY)
add_definitions(-Werror=incompatible-pointer-types)

add_executable(hwengine WIN32 ${engine_sources} ${CMAKE_CURRENT_SOURCE_DIR}/web_entry.c ${CMAKE_CURRENT_SOURCE_DIR}/ipc_browser.c)

if(EMSCRIPTEN)
    target_compile_options(hwengine PRIVATE -sUSE_SDL=2 -sUSE_SDL_MIXER=2 -sUSE_SDL_IMAGE=2 -sSDL2_IMAGE_FORMATS=["png"] -sUSE_SDL_TTF=2)
    target_include_directories(hwengine PRIVATE ${CMAKE_SOURCE_DIR}/misc/libphysfs)
    target_link_options(hwengine PRIVATE 
        -sUSE_SDL=2 
        -sUSE_SDL_MIXER=2 
        -sUSE_SDL_IMAGE=2
        -sSDL2_IMAGE_FORMATS=["png"]
        -sUSE_SDL_TTF=2
        -sMIN_WEBGL_VERSION=2 
        -sMAX_WEBGL_VERSION=2 
        -sFULL_ES2=1
        -sALLOW_MEMORY_GROWTH=1
        -sSTACK_SIZE=5MB
        "-sEXPORTED_RUNTIME_METHODS=FS,HEAPU8"
        "-sEXPORTED_FUNCTIONS=_hwengine_RunEngine_internal")
    set_target_properties(hwengine PROPERTIES SUFFIX ".html")
endif()

if(BUILD_ENGINE_JS)
    set_target_properties(hwengine PROPERTIES SUFFIX ".html")
    set_property(TARGET hwengine APPEND PROPERTY LINK_DEPENDS "${HW_PRE_JS};${HW_POST_JS}")
endif()

target_link_libraries(hwengine  fpcrtl
                                ${LUA_LIBRARY}
                                ${OPENGL_LIBRARY}
                                ${SDL2_LIBRARIES}
                                ${SDL2_MIXER_LIBRARY}
                                ${SDL2_NET_LIBRARIES}
                                ${SDL2_IMAGE_LIBRARIES}
                                ${SDL2_TTF_LIBRARIES}
                                physfs
                                physlayer
                                m
                                ${HW_LINK_LIBS})

# Link Rust library if enabled
if(HW_USE_RUST_MAPGEN)
    target_link_libraries(hwengine hwengine_future)
endif()

install(PROGRAMS "${EXECUTABLE_OUTPUT_PATH}/hwengine${CMAKE_EXECUTABLE_SUFFIX}" DESTINATION ${target_binary_install_dir})


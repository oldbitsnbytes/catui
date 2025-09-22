
cmake_minimum_required(VERSION 3.40 FATAL_ERROR)
cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(catui CXX)


set(HEADERS
    include/catui/defs.h
#    include/catui/cadres.h
#    include/catui/cmdargs.h
#    include/catui/colors.h
#    include/catui/notify.h
#    include/catui/expect.h
#    include/catui/geometry.h
#    include/catui/glyphes.h
#    include/catui/data/databits.h
#    include/catui/data/field.h
#    include/catui/data/table.h
#    include/catui/sys/sys.h
#    include/catui/sys/sys.inc
#    include/catui/object.h
#    include/catui/rem.h
#    include/catui/string.h
#    include/catui/app_base.h
#    include/catui/vchar.h
#    include/catui/strscan.h
#    include/catui/strscan.numeric_data.value.inc.h
#    include/catui/io/lfd.h
#    include/catui/io/listener.h
#    include/catui/io/tcp_socket.h
#    include/catui/io/kbhit.h
#    include/catui/io/mouse.h
#    include/catui/io/console.h

)


add_library(catui

            SHARED

            ${HEADERS}
#            c++/catui/colors.cc
#            c++/catui/geometry.cc
#            c++/catui/sys/sys.cc
#            c++/catui/cadres.cc
#            c++/catui/glyphes.cc
#            c++/catui/object.cc
#            c++/catui/rem.cc
#            c++/catui/cmdargs.cc
#            c++/catui/string.cc
#            c++/catui/app_base.cc
#            c++/catui/vchar.cc
#            c++/catui/vchar.pad.cc
#            c++/catui/strscan.cc
#            c++/catui/io/lfd.cc
#            c++/catui/io/listener.cc
#            c++/catui/io/tcp_socket.cc
#            c++/catui/io/kbhit.cc
#            c++/catui/io/mouse.cc
#            c++/catui/io/console.cc

)
target_include_directories(catui PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:include/catui>
)
message("build and include dir:" ${CMAKE_CURRENT_SOURCE_DIR}/catui)
set_target_properties(${WORK} PROPERTIES OUTPUT_NAME catui++)



target_compile_definitions(cat PUBLIC "catui_DEBUG=$<CONFIG:Debug>")
include(GenerateExportHeader)
generate_export_header(catui EXPORT_FILE_NAME "catui_export")

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF ()


target_link_libraries(catui ${CMAKE_DL_LIBS} sqlite3) # and other system dependencies...





install(TARGETS catui
        EXPORT catui
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)

INSTALL(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/catui)


add_custom_target("uninstall_catui" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall_${PROJECT_NAME}"
    POST_BUILD
    COMMENT "Uninstall ${PROJECT_NAME} files under include and lib"
    COMMAND rm -vrf ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/lib/lib${PROJECT_NAME}* || echo Nothing in install_manifest.txt to be uninstalled!
)


#add_subdirectory(test.app)

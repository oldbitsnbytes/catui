
cmake_minimum_required(VERSION 3.40 FATAL_ERROR)
cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(catui CXX)


set(HEADERS
    include/tui/defs.h
#    include/tui/cadres.h
#    include/tui/cmdargs.h
#    include/tui/colors.h
#    include/tui/notify.h
#    include/tui/expect.h
#    include/tui/geometry.h
#    include/tui/glyphes.h
#    include/tui/data/databits.h
#    include/tui/data/field.h
#    include/tui/data/table.h
#    include/tui/sys/sys.h
#    include/tui/sys/sys.inc
#    include/tui/object.h
#    include/tui/rem.h
#    include/tui/string.h
#    include/tui/app_base.h
#    include/tui/vchar.h
#    include/tui/strscan.h
#    include/tui/strscan.numeric_data.value.inc.h
#    include/tui/io/lfd.h
#    include/tui/io/listener.h
#    include/tui/io/tcp_socket.h
#    include/tui/io/kbhit.h
#    include/tui/io/mouse.h
#    include/tui/io/console.h

)


add_library(catui

            SHARED

            ${HEADERS}
#            c++/tui/colors.cc
#            c++/tui/geometry.cc
#            c++/tui/sys/sys.cc
#            c++/tui/cadres.cc
#            c++/tui/glyphes.cc
#            c++/tui/object.cc
#            c++/tui/rem.cc
#            c++/tui/cmdargs.cc
#            c++/tui/string.cc
#            c++/tui/app_base.cc
#            c++/tui/vchar.cc
#            c++/tui/vchar.pad.cc
#            c++/tui/strscan.cc
#            c++/tui/io/lfd.cc
#            c++/tui/io/listener.cc
#            c++/tui/io/tcp_socket.cc
#            c++/tui/io/kbhit.cc
#            c++/tui/io/mouse.cc
#            c++/tui/io/console.cc

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


cmake_minimum_required(VERSION 3.40 FATAL_ERROR)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(catui
        VERSION 0.1.0
        DESCRIPTION "A non-standard c++ framework suite of my personal hobby projects"
        LANGUAGES CXX
)


set(HEADERS
    include/${PROJECT_NAME}/root.h
    include/${PROJECT_NAME}/ui/border.h
    include/${PROJECT_NAME}/sys/cmdargs.h
    include/${PROJECT_NAME}/ui/colors.h
    include/${PROJECT_NAME}/sys/notify.h
    include/${PROJECT_NAME}/sys/expect.h
    include/${PROJECT_NAME}/ui/geometry.h
    include/${PROJECT_NAME}/ui/glyphes.h
    include/${PROJECT_NAME}/sys/dbase.h
    include/${PROJECT_NAME}/sys/dbase_field_impl.h
    #    include/${PROJECT_NAME}/ui/data/field.h
    #    include/${PROJECT_NAME}/ui/data/table.h
    include/${PROJECT_NAME}/sys/sys.h

    include/${PROJECT_NAME}/sys/rem.h
    include/${PROJECT_NAME}/sys/string.h
    include/${PROJECT_NAME}/ui/vchar.h
    include/${PROJECT_NAME}/io/polling.h
    #    include/${PROJECT_NAME}/ui/io/listener.h
    #    include/${PROJECT_NAME}/ui/io/tcp_socket.h
    include/${PROJECT_NAME}/io/kstroke.h
    include/${PROJECT_NAME}/io/mouse.h
    include/${PROJECT_NAME}/io/console.h
    include/${PROJECT_NAME}/ui/dom/element.h
    include/${PROJECT_NAME}/ui/dom/object.h
    include/${PROJECT_NAME}/sys/application.h
    include/${PROJECT_NAME}/sys/strscan.h
    include/${PROJECT_NAME}/lexer/lang.h
    include/${PROJECT_NAME}/lexer/token_info.h
    include/${PROJECT_NAME}/lexer/lexer.h

)


add_library(${PROJECT_NAME}

            SHARED

            ${HEADERS}
            c++/ui/colors.cc
            c++/ui/geometry.cc
            c++/ui/border.cc
            c++/sys/sys.cc
            c++/sys/cmdargs.cc
            c++/sys/application.cc
            c++/sys/rem.cc
            c++/ui/glyphes.cc
            c++/ui/dom/object.cc
            c++/ui/dom/element.cc
            c++/sys/string.cc
            c++/sys/dbase.cc
            c++/ui/vchar.cc
            c++/ui/vchar.pad.cc
            c++/io/polling.cc
#            c++/ui/io/listener.cc
#            c++/ui/io/tcp_socket.cc
            c++/io/kstroke.cc
            c++/io/mouse.cc
            c++/io/console.cc
            c++/lexer/token_info.cc
            c++/lexer/lang.cc
            c++/lexer/lexer.cc
            c++/sys/strscan.cc
)



target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)
message("build and include dir:" ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}++)



target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_DEBUG=$<CONFIG:Debug>")
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_NAME}_export")

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF ()


target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} sqlite3) # and other system dependencies...


add_executable(catapp
    app/main.cc
)

target_link_libraries(catapp catui)


install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)

INSTALL(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})


add_custom_target("uninstall_${PROJECT_NAME}" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall_${PROJECT_NAME}"
    POST_BUILD
    COMMENT "Uninstall ${PROJECT_NAME} files under include and lib"
    COMMAND rm -vrf ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/lib/lib${PROJECT_NAME}++* || echo "Nothing in install_manifest.txt to be uninstalled!"
)


#add_subdirectory(test.app)

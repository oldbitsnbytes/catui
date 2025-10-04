
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
    #    include/${PROJECT_NAME}/ui/cmdargs.h
    include/${PROJECT_NAME}/ui/colors.h
    #    include/${PROJECT_NAME}/ui/notify.h
    include/${PROJECT_NAME}/sys/expect.h
    include/${PROJECT_NAME}/ui/geometry.h
    include/${PROJECT_NAME}/ui/glyphes.h
    #    include/${PROJECT_NAME}/ui/data/databits.h
    #    include/${PROJECT_NAME}/ui/data/field.h
    #    include/${PROJECT_NAME}/ui/data/table.h
    include/${PROJECT_NAME}/sys/sys.h
    #    include/${PROJECT_NAME}/ui/sys/sys.inc
    #    include/${PROJECT_NAME}/ui/object.h
    include/${PROJECT_NAME}/sys/rem.h
    include/${PROJECT_NAME}/sys/application.cc
    include/${PROJECT_NAME}/utxt.h
    #    include/${PROJECT_NAME}/ui/app_base.h
    include/${PROJECT_NAME}/ui/vchar.h
    #    include/${PROJECT_NAME}/ui/strscan.h
    #    include/${PROJECT_NAME}/ui/strscan.numeric_data.value.inc.h
    include/${PROJECT_NAME}/io/polling.h
    #    include/${PROJECT_NAME}/ui/io/listener.h
    #    include/${PROJECT_NAME}/ui/io/tcp_socket.h
    include/${PROJECT_NAME}/io/kstroke.h
    include/${PROJECT_NAME}/io/mouse.h
    include/${PROJECT_NAME}/io/console.h
    include/catui/ui/dom/element.h
    include/catui/ui/dom/object.h
    c++/sys/application.cc
    include/catui/sys/application.h


)


add_library(${PROJECT_NAME}

            SHARED

            ${HEADERS}
            c++/ui/colors.cc
            c++/ui/geometry.cc
            c++/ui/border.cc
            c++/sys/sys.cc
            c++/sys/application.cc
#            c++/ui/cadres.cc
            c++/ui/glyphes.cc
            c++/ui/dom/object.cc
            c++/ui/dom/element.cc
#             c++/ui/cmdargs.cc
             c++/utxt.cc
#            c++/ui/app_base.cc
            c++/ui/vchar.cc
            c++/ui/vchar.pad.cc
#            c++/ui/strscan.cc
            c++/io/polling.cc
#            c++/ui/io/listener.cc
#            c++/ui/io/tcp_socket.cc
            c++/io/kstroke.cc
            c++/io/mouse.cc
            c++/io/console.cc

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

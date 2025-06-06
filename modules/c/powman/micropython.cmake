add_library(usermod_sleep INTERFACE)

target_sources(usermod_sleep INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/bindings.c
    ${CMAKE_CURRENT_LIST_DIR}/powman.c
    ${CMAKE_CURRENT_LIST_DIR}/rosc.c
)

target_include_directories(usermod_sleep INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(usermod_sleep INTERFACE hardware_powman hardware_gpio)

target_link_libraries(usermod INTERFACE usermod_sleep)

#set_source_files_properties(
#    ${CMAKE_CURRENT_LIST_DIR}/sleep.c
#    PROPERTIES COMPILE_FLAGS
#    "-Wno-maybe-uninitialized"
#)

set_source_files_properties(
    ${CMAKE_CURRENT_LIST_DIR}/bindings.c
    PROPERTIES COMPILE_FLAGS
    "-Wno-discarded-qualifiers"
)

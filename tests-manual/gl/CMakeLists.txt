# This is a windows only test
if(NOT WIN32)
    return()
endif ()

set(TARGET_NAME gl-test)
# This is not a testcase -- just set it up as a regular hifi project
setup_hifi_project(Quick Gui OpenGL)
setup_memory_debugger()
setup_thread_debugger()
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Tests/manual-tests/")
link_hifi_libraries(shared gl)
package_libraries_for_deployment()
target_nsight()
target_opengl()

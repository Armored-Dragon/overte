set(TARGET_NAME ac-client)
setup_hifi_project(Core)
setup_memory_debugger()
setup_thread_debugger()
link_hifi_libraries(shared networking)

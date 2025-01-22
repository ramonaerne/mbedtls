set(exe bl11)

#message(FATAL_ERROR "$<TARGET_OBJECTS:mbedtls_test>")

add_executable(${exe} ${exe}.c) # $<TARGET_OBJECTS:mbedtls_test>)
target_link_libraries(${exe} ${mbedcrypto_target}) #${CMAKE_THREAD_LIBS_INIT})
#target_include_directories(${exe} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../tests/include)

install(TARGETS ${exe}
        DESTINATION "bin"
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

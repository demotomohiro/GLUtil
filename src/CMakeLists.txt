find_package(GLEW REQUIRED)

add_library(shader SHARED shader.cpp)
target_link_libraries(shader GLEW::GLEW)
target_enable_warning(shader)
export_library(shader)

add_library(contextUtil SHARED contextUtil.cpp)
target_link_libraries(contextUtil GLEW::GLEW)
set_target_properties(contextUtil PROPERTIES CXX_STANDARD 11)
set_target_properties(contextUtil PROPERTIES CXX_STANDARD_REQUIRED ON)
target_enable_warning(contextUtil)
export_library(contextUtil)

find_package(Boost COMPONENTS wave)

if(Boost_WAVE_FOUND)
    add_library(cStdShader SHARED cStdShader.cpp)
    set_target_properties(cStdShader PROPERTIES CXX_STANDARD 11)
    set_target_properties(cStdShader PROPERTIES CXX_STANDARD_REQUIRED ON)
    target_link_libraries(cStdShader PRIVATE shader Boost::wave)
    target_enable_warning(cStdShader)
    export_library(cStdShader)
endif()

set(version_config
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake)
set(config_dest lib/cmake/${PROJECT_NAME})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${version_config}
    COMPATIBILITY SameMajorVersion)
install(FILES ${version_config} DESTINATION ${config_dest})

install(EXPORT ${PROJECT_NAME}Config DESTINATION ${config_dest}
    NAMESPACE ${PROJECT_NAME}::
)


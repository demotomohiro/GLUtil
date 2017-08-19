find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_library(shader shader.cpp)
if(CMAKE_VERSION VERSION_LESS 3.8)
    target_link_libraries(shader GLEW::GLEW ${OPENGL_gl_LIBRARY})
    include_directories(${OPENGL_INCLUDE_DIR})
else()
    target_link_libraries(shader GLEW::GLEW OpenGL::GL)
endif()
target_enable_warning(shader)
export_library(shader)

add_library(contextUtil contextUtil.cpp)
if(CMAKE_VERSION VERSION_LESS 3.8)
    target_link_libraries(contextUtil GLEW::GLEW ${OPENGL_gl_LIBRARY})
    include_directories(${OPENGL_INCLUDE_DIR})
else()
    target_link_libraries(contextUtil GLEW::GLEW OpenGL::GL)
endif()
set_target_properties(contextUtil PROPERTIES CXX_STANDARD 11)
set_target_properties(contextUtil PROPERTIES CXX_STANDARD_REQUIRED ON)
target_enable_warning(contextUtil)
export_library(contextUtil)

find_package(Boost COMPONENTS wave)

if(Boost_WAVE_FOUND)
    add_library(cStdShader cStdShader.cpp)
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


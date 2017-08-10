#pragma once

#include "cstdshader_export.h"
#include <string>
#include <vector>

//Load shader from C++ standard library like string or ifstream and output messages to cout or cerr.
namespace GLUtil {
GLuint CSTDSHADER_EXPORT load_shader(GLenum type, const std::string& source, bool& status, const std::vector<std::string>& macro_definitions = std::vector<std::string>());
GLuint CSTDSHADER_EXPORT load_shader_from_file(GLenum type, const std::string& file, bool& status, const std::vector<std::string>& macro_definitions = std::vector<std::string>());
GLuint CSTDSHADER_EXPORT link_program(GLuint vert_shader, GLuint frag_shader, bool& status);
}


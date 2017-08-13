#pragma once

#include "shader_export.h"
#include <string>

namespace GLUtil {

class SHADER_EXPORT scoped_shader {
public:

    scoped_shader(GLuint src=0);

    ~scoped_shader() {
        delete_shader();
    }

    operator GLuint() const {
        return shader;
    }

    void operator=(GLuint src);

    bool operator!() const {
        return this->shader == 0;
    }

private:

    void delete_shader();

    GLuint shader;
};

class SHADER_EXPORT scoped_program {
public:

    scoped_program(GLuint src=0);

    ~scoped_program();

    operator GLuint() const {
        return program;
    }

    scoped_program& operator = (GLuint src);

private:

    GLuint program;
};

void    SHADER_EXPORT set_shader_source(GLuint shader, const char* source);
GLuint  SHADER_EXPORT get_shader_obj(GLenum type, const char* source);
GLuint  SHADER_EXPORT get_shader_obj(GLenum type, const std::string& source);

bool    SHADER_EXPORT compile_shader(GLuint shader);

std::string SHADER_EXPORT get_shader_info_log(GLuint shader);
GLuint      SHADER_EXPORT get_program_obj(GLuint shader0, GLuint shader1);
bool        SHADER_EXPORT link_program(GLuint program);
std::string SHADER_EXPORT get_program_info_log(GLuint program);

}


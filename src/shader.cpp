#include <GL/glew.h>
#include "shader.hpp"

#include <cassert>
#include <string>
#include <vector>

using namespace std;
using namespace GLUtil;

scoped_shader::scoped_shader(GLuint src):shader(src) {
    assert(glIsShader(shader) == GL_TRUE || shader == 0);
}

void scoped_shader::operator=(GLuint src) {
    if(shader == src)
        return;

    delete_shader();
    shader = src;
}

void scoped_shader::delete_shader() {
    glDeleteShader(shader);
}

scoped_program::scoped_program(GLuint src):program(src) {
    assert(glIsProgram(program) || program == 0);
}

scoped_program& scoped_program::operator = (GLuint src) {
    assert(glIsProgram(src) == GL_TRUE || src == 0);
    assert(glIsProgram(this->program) == GL_TRUE || this->program == 0);

    if(program == src)
        return *this;

    glDeleteProgram(program);
    program = src;

    return *this;
}

scoped_program::~scoped_program() {
    glDeleteProgram(program);
}

void GLUtil::set_shader_source(GLuint shader, const char* source) {
    const char* string[] = {source};
    glShaderSource(shader, 1, string, NULL);
}

GLuint GLUtil::get_shader_obj(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    if(shader==0)
        return 0;

    set_shader_source(shader, source);
    return shader;
}

GLuint GLUtil::get_shader_obj(GLenum type, const std::string& source) {
    return get_shader_obj(type, source.c_str());
}

bool GLUtil::compile_shader(GLuint shader) {
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    return success == GL_TRUE;
}

string GLUtil::get_shader_info_log(GLuint shader) {
    GLint log_len;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

    if(log_len==0)
        return string();

    vector<char> log(log_len);
    glGetShaderInfoLog(shader, log_len, NULL, &log[0]);

    return string(log.begin(), log.end());
}

GLuint GLUtil::get_program_obj(GLuint shader0, GLuint shader1) {
    GLuint program = glCreateProgram();
    if(program == 0)
        return 0;

    glAttachShader(program, shader0);
    glAttachShader(program, shader1);

    return program;
}

bool GLUtil::link_program(GLuint program) {
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    return success==GL_TRUE;
}

string GLUtil::get_program_info_log(GLuint program) {
    GLint log_len;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

    if(log_len==0)
        return string();

    vector<char> log(log_len);
    glGetProgramInfoLog(program, log_len, NULL, &log[0]);

    return string(log.begin(), log.end());
}


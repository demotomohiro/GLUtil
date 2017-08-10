#pragma once

#include "contextutil_export.h"
#include <string>

namespace GLUtil {
//Return text about current OpenGL context(Version, Renderer, Vender, etc).
std::string CONTEXTUTIL_EXPORT get_context_info_text();
//Output above text to cout.
void CONTEXTUTIL_EXPORT print_context_info();
//Enable OpenGL Debug message callback only if current context is debug context.
void CONTEXTUTIL_EXPORT enable_debug_message_callback_if_available(GLDEBUGPROC callback, const void *userParam = nullptr);
//Enable OpenGL Debug message output to cerr.
void CONTEXTUTIL_EXPORT enable_debug_message_cerr_out_if_available();
}

//Record filename and line number of the source code when OpenGL function is called so that debug message callback function can access it using GLUtil::get_gl_call_info() function.
//I hope it will help you to identify which OpenGL function call caused debug message callback.
//GLEW_GET_FUN macro is defined by GLEW.
//Following code redefine it so that set_last_gl_call function is called every time OpenGL functions from GLEW is called.
//When you use other OpenGL function, use GL_CALL macro like:
//GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
#ifndef DISABLE_REDEFINING_GLEW_GET_FUN
#ifndef NDEBUG
#   undef GLEW_GET_FUN
#   define GLEW_GET_FUN(x)  (set_last_gl_call(__FILE__, __LINE__, #x), x)
#   define GL_CALL(x)       (set_last_gl_call(__FILE__, __LINE__, #x), x)
#else
#   define GL_CALL(x)       x
#endif
#endif

namespace GLUtil {

struct gl_call_info {
    const   char*   filename = nullptr;
    int     line     = 0;
    const   char*   funcname = nullptr;
};

gl_call_info CONTEXTUTIL_EXPORT &get_gl_call_info();

struct CONTEXTUTIL_EXPORT set_last_gl_call {
    set_last_gl_call(const char* filename, int line, const char* funcname);
    ~set_last_gl_call();
};
}


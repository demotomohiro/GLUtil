#include <GL/glew.h>
#include "contextUtil.hpp"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace GLUtil;

string GLUtil::get_context_info_text() {
    GLint contextProfileMask;
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &contextProfileMask);
    string contextProfileMaskStr;
    if(contextProfileMask & GL_CONTEXT_CORE_PROFILE_BIT)
        contextProfileMaskStr += "GL_CONTEXT_CORE_PROFILE_BIT ";
    if(contextProfileMask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
        contextProfileMaskStr += "CONTEXT_COMPATIBILITY_PROFILE_BIT ";

    GLint contextFlags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &contextFlags);
    string contextFlagsStr;
    if(contextFlags & GL_CONTEXT_FLAG_DEBUG_BIT)
        contextFlagsStr += "GL_CONTEXT_FLAG_DEBUG_BIT ";
    if(contextFlags & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT)
        contextFlagsStr += "GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT ";

    ostringstream oss;
    oss <<
        "GL_VERSION:\n\t" <<
        reinterpret_cast<const char*>(glGetString(GL_VERSION)) <<
        "\nGL_SHADING_LANGUAGE_VERSION:\n\t" <<
        reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)) <<
        "\nGL_RENDERER:\n\t" <<
        reinterpret_cast<const char*>(glGetString(GL_RENDERER)) <<
        "\nGL_VENDOR:\n\t" <<
        reinterpret_cast<const char*>(glGetString(GL_VENDOR)) <<
        "\nGL_CONTEXT_PROFILE_MASK:\n\t" <<
        contextProfileMaskStr   <<
        "\nGL_CONTEXT_FLAGS:\n\t" <<
        contextFlagsStr <<
        '\n'
        ;

    GLint major_ver;
    GLint minor_ver;
    glGetIntegerv(GL_MAJOR_VERSION, &major_ver);
    glGetIntegerv(GL_MINOR_VERSION, &minor_ver);
    oss << "OpenGL version:" << major_ver << "." << minor_ver << '\n';

    return oss.str();
}

void GLUtil::print_context_info() {
    cout << get_context_info_text();
}

void GLUtil::enable_debug_message_callback_if_available(GLDEBUGPROC callback, const void *userParam) {
    GLint cntxt_flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &cntxt_flags);
    if(cntxt_flags & GL_CONTEXT_FLAG_DEBUG_BIT && glIsEnabled(GL_DEBUG_OUTPUT)==GL_TRUE) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        GLuint ids = 0;
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &ids, GL_TRUE);
        glDebugMessageCallback(callback, userParam);
    }
}

namespace {
void GLEWAPIENTRY gl_debug_callback(
    GLenum /*source*/, GLenum /*type*/, GLuint /*id*/,
    GLenum /*severity*/,
    GLsizei /*length*/, const char *message,
    const GLvoid * /*userParam*/) {
    cerr << "Message from glDebugMessageCallback:\n";
    if(get_gl_call_info().filename) {
        cerr <<
            "In " << get_gl_call_info().funcname << ", " <<
            get_gl_call_info().filename << ":" <<
            get_gl_call_info().line <<
            endl;
    }else {
        cerr << "In somewhere untracked place:" << endl;
    }

    cerr << message << endl;
}
}

void GLUtil::enable_debug_message_cerr_out_if_available() {
    GLUtil::enable_debug_message_callback_if_available(&gl_debug_callback);
}

gl_call_info& GLUtil::get_gl_call_info() {
    static gl_call_info gci;

    return gci;
}

GLUtil::set_last_gl_call::set_last_gl_call(const char* filename, int line, const char* funcname) {
    gl_call_info& gci = get_gl_call_info();
    gci.filename    = filename;
    gci.line        = line;
    gci.funcname    = funcname;
}

GLUtil::set_last_gl_call::~set_last_gl_call() {
    gl_call_info& gci = get_gl_call_info();
    gci.filename    = nullptr;
    gci.line        = -1;
    gci.funcname    = nullptr;
}


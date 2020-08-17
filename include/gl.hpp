#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <GL/glcorearb.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#if !defined(OPENGL_HPP_NAMESPACE)
#define OPENGL_HPP_NAMESPACE gl
#endif

namespace OPENGL_HPP_NAMESPACE {

class DispatchLoaderDynamic;

enum class StateVariables;

template <typename T>
class ArrayProxy;
#if !defined(OPENGL_HPP_DISPATCH_LOADER_DYNAMIC)
#if !defined(GL_GLEXT_PROTOTYPES)
#define OPENGL_HPP_DISPATCH_LOADER_DYNAMIC 1
#else
#define OPENGL_HPP_DISPATCH_LOADER_DYNAMIC 0
#endif
#endif

#if defined(_WIN32) && defined(OPENGL_HPP_STORAGE_SHARED)
#ifdef OPENGL_HPP_STORAGE_SHARED_EXPORT
#define OPENGL_HPP_STORAGE_API __declspec(dllexport)
#else
#define OPENGL_HPP_STORAGE_API __declspec(dllimport)
#endif
#else
#define OPENGL_HPP_STORAGE_API
#endif

#if !defined(OPENGL_HPP_DEFAULT_DISPATCHER)
#if OPENGL_HPP_DISPATCH_LOADER_DYNAMIC == 1
#define OPENGL_HPP_DEFAULT_DISPATCHER \
    ::OPENGL_HPP_NAMESPACE::defaultDispatchLoaderDynamic
#define OPENGL_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE                     \
    namespace OPENGL_HPP_NAMESPACE {                                           \
    OPENGL_HPP_STORAGE_API DispatchLoaderDynamic defaultDispatchLoaderDynamic; \
    }
extern OPENGL_HPP_STORAGE_API DispatchLoaderDynamic
    defaultDispatchLoaderDynamic;
#else
#define OPENGL_HPP_DEFAULT_DISPATCHER \
    ::OPENGL_HPP_NAMESPACE::DispatchLoaderStatic()
#define OPENGL_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE
#endif
#endif

#if !defined(OPENGL_HPP_DEFAULT_DISPATCHER_TYPE)
#if OPENGL_HPP_DISPATCH_LOADER_DYNAMIC == 1
#define OPENGL_HPP_DEFAULT_DISPATCHER_TYPE \
    ::OPENGL_HPP_NAMESPACE::DispatchLoaderDynamic
#else
#define OPENGL_HPP_DEFAULT_DISPATCHER_TYPE \
    ::OPENGL_HPP_NAMESPACE::DispatchLoaderStatic
#endif
#endif

template <typename T, GLsizei N = 1,
          typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE,
          typename = std::enable_if_t<
              std::is_invocable_v<decltype(Dispatch{}.*
                                           T::template createFunc<Dispatch>),
                                  GLsizei, typename T::handleType *> &&
                  (N > 0U),
              int>>
decltype(auto) createObject(Dispatch const &d = OPENGL_HPP_DEFAULT_DISPATCHER);

template <typename T, typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE,
          typename = std::enable_if_t<
              std::is_invocable_v<decltype(Dispatch{}.*
                                           T::template createFunc<Dispatch>),
                                  GLsizei, typename T::handleType *>,
              int>>
std::vector<T> createObjectv(GLsizei n, Dispatch const &d = OPENGL_HPP_DEFAULT_DISPATCHER);

template <typename T, typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE,
          typename = std::enable_if_t<
              std::is_invocable_v<decltype(Dispatch{}.*
                                           T::template deleteFunc<Dispatch>),
                                  GLsizei, const typename T::handleType *>,
              int>>
void deleteObject(ArrayProxy<const T> const &arrays,
                  Dispatch const &d = OPENGL_HPP_DEFAULT_DISPATCHER);

template <typename _Tx, size_t N>
constexpr decltype(auto) ArrayOrObject(std::array<_Tx, N> &_array) noexcept;

template <
    typename _Tx, std::size_t N = 1,
    typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE,
    typename = std::enable_if_t<
        std::is_same_v<_Tx, GLint> || std::is_same_v<_Tx, GLfloat> ||
            std::is_same_v<_Tx, GLint64> || std::is_same_v<_Tx, GLboolean> ||
            std::is_same_v<_Tx, GLdouble> ||
            std::is_same_v<_Tx, bool> && (N > 0U),
        int>>
decltype(auto) get(StateVariables pname,
                   Dispatch const &d = OPENGL_HPP_DEFAULT_DISPATCHER);

template <
    typename _Tx, std::size_t N = 1,
    typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE,
    typename = std::enable_if_t<
        std::is_same_v<_Tx, GLint> || std::is_same_v<_Tx, GLfloat> ||
            std::is_same_v<_Tx, GLint64> || std::is_same_v<_Tx, GLboolean> ||
            std::is_same_v<_Tx, GLdouble> ||
            std::is_same_v<_Tx, bool> && (N > 0U),
        int>>
decltype(auto) get(StateVariables pname, GLuint index,
                   Dispatch const &d = OPENGL_HPP_DEFAULT_DISPATCHER);

class DispatchLoaderDynamic {
   public:
#ifdef GL_VERSION_1_0
    PFNGLCULLFACEPROC glCullFace = nullptr;
    PFNGLFRONTFACEPROC glFrontFace = nullptr;
    PFNGLHINTPROC glHint = nullptr;
    PFNGLLINEWIDTHPROC glLineWidth = nullptr;
    PFNGLPOINTSIZEPROC glPointSize = nullptr;
    PFNGLPOLYGONMODEPROC glPolygonMode = nullptr;
    PFNGLSCISSORPROC glScissor = nullptr;
    PFNGLTEXPARAMETERFPROC glTexParameterf = nullptr;
    PFNGLTEXPARAMETERFVPROC glTexParameterfv = nullptr;
    PFNGLTEXPARAMETERIPROC glTexParameteri = nullptr;
    PFNGLTEXPARAMETERIVPROC glTexParameteriv = nullptr;
    PFNGLTEXIMAGE1DPROC glTexImage1D = nullptr;
    PFNGLTEXIMAGE2DPROC glTexImage2D = nullptr;
    PFNGLDRAWBUFFERPROC glDrawBuffer = nullptr;
    PFNGLCLEARPROC glClear = nullptr;
    PFNGLCLEARCOLORPROC glClearColor = nullptr;
    PFNGLCLEARSTENCILPROC glClearStencil = nullptr;
    PFNGLCLEARDEPTHPROC glClearDepth = nullptr;
    PFNGLSTENCILMASKPROC glStencilMask = nullptr;
    PFNGLCOLORMASKPROC glColorMask = nullptr;
    PFNGLDEPTHMASKPROC glDepthMask = nullptr;
    PFNGLDISABLEPROC glDisable = nullptr;
    PFNGLENABLEPROC glEnable = nullptr;
    PFNGLFINISHPROC glFinish = nullptr;
    PFNGLFLUSHPROC glFlush = nullptr;
    PFNGLBLENDFUNCPROC glBlendFunc = nullptr;
    PFNGLLOGICOPPROC glLogicOp = nullptr;
    PFNGLSTENCILFUNCPROC glStencilFunc = nullptr;
    PFNGLSTENCILOPPROC glStencilOp = nullptr;
    PFNGLDEPTHFUNCPROC glDepthFunc = nullptr;
    PFNGLPIXELSTOREFPROC glPixelStoref = nullptr;
    PFNGLPIXELSTOREIPROC glPixelStorei = nullptr;
    PFNGLREADBUFFERPROC glReadBuffer = nullptr;
    PFNGLREADPIXELSPROC glReadPixels = nullptr;
    PFNGLGETBOOLEANVPROC glGetBooleanv = nullptr;
    PFNGLGETDOUBLEVPROC glGetDoublev = nullptr;
    PFNGLGETERRORPROC glGetError = nullptr;
    PFNGLGETFLOATVPROC glGetFloatv = nullptr;
    PFNGLGETINTEGERVPROC glGetIntegerv = nullptr;
    PFNGLGETSTRINGPROC glGetString = nullptr;
    PFNGLGETTEXIMAGEPROC glGetTexImage = nullptr;
    PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfv = nullptr;
    PFNGLGETTEXPARAMETERIVPROC glGetTexParameteriv = nullptr;
    PFNGLGETTEXLEVELPARAMETERFVPROC glGetTexLevelParameterfv = nullptr;
    PFNGLGETTEXLEVELPARAMETERIVPROC glGetTexLevelParameteriv = nullptr;
    PFNGLISENABLEDPROC glIsEnabled = nullptr;
    PFNGLDEPTHRANGEPROC glDepthRange = nullptr;
    PFNGLVIEWPORTPROC glViewport = nullptr;
#endif /* GL_VERSION_1_0 */
#ifdef GL_VERSION_1_1
    PFNGLDRAWARRAYSPROC glDrawArrays = nullptr;
    PFNGLDRAWELEMENTSPROC glDrawElements = nullptr;
    PFNGLGETPOINTERVPROC glGetPointerv = nullptr;
    PFNGLPOLYGONOFFSETPROC glPolygonOffset = nullptr;
    PFNGLCOPYTEXIMAGE1DPROC glCopyTexImage1D = nullptr;
    PFNGLCOPYTEXIMAGE2DPROC glCopyTexImage2D = nullptr;
    PFNGLCOPYTEXSUBIMAGE1DPROC glCopyTexSubImage1D = nullptr;
    PFNGLCOPYTEXSUBIMAGE2DPROC glCopyTexSubImage2D = nullptr;
    PFNGLTEXSUBIMAGE1DPROC glTexSubImage1D = nullptr;
    PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D = nullptr;
    PFNGLBINDTEXTUREPROC glBindTexture = nullptr;
    PFNGLDELETETEXTURESPROC glDeleteTextures = nullptr;
    PFNGLGENTEXTURESPROC glGenTextures = nullptr;
    PFNGLISTEXTUREPROC glIsTexture = nullptr;
#endif /* GL_VERSION_1_1 */
#ifdef GL_VERSION_1_2
    PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = nullptr;
    PFNGLTEXIMAGE3DPROC glTexImage3D = nullptr;
    PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = nullptr;
    PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = nullptr;
#endif /* GL_VERSION_1_2 */
#ifdef GL_VERSION_1_3
    PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;
    PFNGLSAMPLECOVERAGEPROC glSampleCoverage = nullptr;
    PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = nullptr;
    PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = nullptr;
    PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D = nullptr;
    PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = nullptr;
    PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = nullptr;
    PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D = nullptr;
    PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage = nullptr;
#endif /* GL_VERSION_1_3 */
#ifdef GL_VERSION_1_4
    PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = nullptr;
    PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays = nullptr;
    PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements = nullptr;
    PFNGLPOINTPARAMETERFPROC glPointParameterf = nullptr;
    PFNGLPOINTPARAMETERFVPROC glPointParameterfv = nullptr;
    PFNGLPOINTPARAMETERIPROC glPointParameteri = nullptr;
    PFNGLPOINTPARAMETERIVPROC glPointParameteriv = nullptr;
    PFNGLBLENDCOLORPROC glBlendColor = nullptr;
    PFNGLBLENDEQUATIONPROC glBlendEquation = nullptr;
#endif /* GL_VERSION_1_4 */
#ifdef GL_VERSION_1_5
    PFNGLGENQUERIESPROC glGenQueries = nullptr;
    PFNGLDELETEQUERIESPROC glDeleteQueries = nullptr;
    PFNGLISQUERYPROC glIsQuery = nullptr;
    PFNGLBEGINQUERYPROC glBeginQuery = nullptr;
    PFNGLENDQUERYPROC glEndQuery = nullptr;
    PFNGLGETQUERYIVPROC glGetQueryiv = nullptr;
    PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv = nullptr;
    PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv = nullptr;
    PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
    PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
    PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
    PFNGLISBUFFERPROC glIsBuffer = nullptr;
    PFNGLBUFFERDATAPROC glBufferData = nullptr;
    PFNGLBUFFERSUBDATAPROC glBufferSubData = nullptr;
    PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData = nullptr;
    PFNGLMAPBUFFERPROC glMapBuffer = nullptr;
    PFNGLUNMAPBUFFERPROC glUnmapBuffer = nullptr;
    PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = nullptr;
    PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = nullptr;
#endif /* GL_VERSION_1_5 */
#ifdef GL_VERSION_2_0
    PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate = nullptr;
    PFNGLDRAWBUFFERSPROC glDrawBuffers = nullptr;
    PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = nullptr;
    PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate = nullptr;
    PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate = nullptr;
    PFNGLATTACHSHADERPROC glAttachShader = nullptr;
    PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;
    PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
    PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
    PFNGLCREATESHADERPROC glCreateShader = nullptr;
    PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
    PFNGLDELETESHADERPROC glDeleteShader = nullptr;
    PFNGLDETACHSHADERPROC glDetachShader = nullptr;
    PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;
    PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
    PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = nullptr;
    PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = nullptr;
    PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders = nullptr;
    PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = nullptr;
    PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
    PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
    PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
    PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
    PFNGLGETSHADERSOURCEPROC glGetShaderSource = nullptr;
    PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
    PFNGLGETUNIFORMFVPROC glGetUniformfv = nullptr;
    PFNGLGETUNIFORMIVPROC glGetUniformiv = nullptr;
    PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv = nullptr;
    PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv = nullptr;
    PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = nullptr;
    PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = nullptr;
    PFNGLISPROGRAMPROC glIsProgram = nullptr;
    PFNGLISSHADERPROC glIsShader = nullptr;
    PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
    PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
    PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
    PFNGLUNIFORM1FPROC glUniform1f = nullptr;
    PFNGLUNIFORM2FPROC glUniform2f = nullptr;
    PFNGLUNIFORM3FPROC glUniform3f = nullptr;
    PFNGLUNIFORM4FPROC glUniform4f = nullptr;
    PFNGLUNIFORM1IPROC glUniform1i = nullptr;
    PFNGLUNIFORM2IPROC glUniform2i = nullptr;
    PFNGLUNIFORM3IPROC glUniform3i = nullptr;
    PFNGLUNIFORM4IPROC glUniform4i = nullptr;
    PFNGLUNIFORM1FVPROC glUniform1fv = nullptr;
    PFNGLUNIFORM2FVPROC glUniform2fv = nullptr;
    PFNGLUNIFORM3FVPROC glUniform3fv = nullptr;
    PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;
    PFNGLUNIFORM1IVPROC glUniform1iv = nullptr;
    PFNGLUNIFORM2IVPROC glUniform2iv = nullptr;
    PFNGLUNIFORM3IVPROC glUniform3iv = nullptr;
    PFNGLUNIFORM4IVPROC glUniform4iv = nullptr;
    PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = nullptr;
    PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = nullptr;
    PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
    PFNGLVALIDATEPROGRAMPROC glValidateProgram = nullptr;
    PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d = nullptr;
    PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv = nullptr;
    PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = nullptr;
    PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = nullptr;
    PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s = nullptr;
    PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv = nullptr;
    PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d = nullptr;
    PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv = nullptr;
    PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f = nullptr;
    PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = nullptr;
    PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s = nullptr;
    PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv = nullptr;
    PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d = nullptr;
    PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv = nullptr;
    PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f = nullptr;
    PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = nullptr;
    PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s = nullptr;
    PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv = nullptr;
    PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv = nullptr;
    PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv = nullptr;
    PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv = nullptr;
    PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub = nullptr;
    PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv = nullptr;
    PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv = nullptr;
    PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv = nullptr;
    PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv = nullptr;
    PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d = nullptr;
    PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv = nullptr;
    PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f = nullptr;
    PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = nullptr;
    PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv = nullptr;
    PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s = nullptr;
    PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv = nullptr;
    PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv = nullptr;
    PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv = nullptr;
    PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv = nullptr;
    PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
#endif /* GL_VERSION_2_0 */
#ifdef GL_VERSION_2_1
    PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = nullptr;
    PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = nullptr;
    PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = nullptr;
    PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = nullptr;
    PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = nullptr;
    PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = nullptr;
#endif /* GL_VERSION_2_1 */
#ifdef GL_VERSION_3_0
    PFNGLCOLORMASKIPROC glColorMaski = nullptr;
    PFNGLGETBOOLEANI_VPROC glGetBooleani_v = nullptr;
    PFNGLGETINTEGERI_VPROC glGetIntegeri_v = nullptr;
    PFNGLENABLEIPROC glEnablei = nullptr;
    PFNGLDISABLEIPROC glDisablei = nullptr;
    PFNGLISENABLEDIPROC glIsEnabledi = nullptr;
    PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback = nullptr;
    PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback = nullptr;
    PFNGLBINDBUFFERRANGEPROC glBindBufferRange = nullptr;
    PFNGLBINDBUFFERBASEPROC glBindBufferBase = nullptr;
    PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings = nullptr;
    PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying =
        nullptr;
    PFNGLCLAMPCOLORPROC glClampColor = nullptr;
    PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender = nullptr;
    PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender = nullptr;
    PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = nullptr;
    PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = nullptr;
    PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = nullptr;
    PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i = nullptr;
    PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i = nullptr;
    PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i = nullptr;
    PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = nullptr;
    PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui = nullptr;
    PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui = nullptr;
    PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui = nullptr;
    PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = nullptr;
    PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv = nullptr;
    PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv = nullptr;
    PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv = nullptr;
    PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = nullptr;
    PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv = nullptr;
    PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv = nullptr;
    PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv = nullptr;
    PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = nullptr;
    PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv = nullptr;
    PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv = nullptr;
    PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv = nullptr;
    PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv = nullptr;
    PFNGLGETUNIFORMUIVPROC glGetUniformuiv = nullptr;
    PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation = nullptr;
    PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation = nullptr;
    PFNGLUNIFORM1UIPROC glUniform1ui = nullptr;
    PFNGLUNIFORM2UIPROC glUniform2ui = nullptr;
    PFNGLUNIFORM3UIPROC glUniform3ui = nullptr;
    PFNGLUNIFORM4UIPROC glUniform4ui = nullptr;
    PFNGLUNIFORM1UIVPROC glUniform1uiv = nullptr;
    PFNGLUNIFORM2UIVPROC glUniform2uiv = nullptr;
    PFNGLUNIFORM3UIVPROC glUniform3uiv = nullptr;
    PFNGLUNIFORM4UIVPROC glUniform4uiv = nullptr;
    PFNGLTEXPARAMETERIIVPROC glTexParameterIiv = nullptr;
    PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv = nullptr;
    PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv = nullptr;
    PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv = nullptr;
    PFNGLCLEARBUFFERIVPROC glClearBufferiv = nullptr;
    PFNGLCLEARBUFFERUIVPROC glClearBufferuiv = nullptr;
    PFNGLCLEARBUFFERFVPROC glClearBufferfv = nullptr;
    PFNGLCLEARBUFFERFIPROC glClearBufferfi = nullptr;
    PFNGLGETSTRINGIPROC glGetStringi = nullptr;
    PFNGLISRENDERBUFFERPROC glIsRenderbuffer = nullptr;
    PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = nullptr;
    PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = nullptr;
    PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = nullptr;
    PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = nullptr;
    PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv = nullptr;
    PFNGLISFRAMEBUFFERPROC glIsFramebuffer = nullptr;
    PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = nullptr;
    PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = nullptr;
    PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = nullptr;
    PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = nullptr;
    PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D = nullptr;
    PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = nullptr;
    PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D = nullptr;
    PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = nullptr;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC
    glGetFramebufferAttachmentParameteriv = nullptr;
    PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;
    PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer = nullptr;
    PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample =
        nullptr;
    PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer = nullptr;
    PFNGLMAPBUFFERRANGEPROC glMapBufferRange = nullptr;
    PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange = nullptr;
    PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
    PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;
    PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
    PFNGLISVERTEXARRAYPROC glIsVertexArray = nullptr;
#endif /* GL_VERSION_3_0 */
#ifdef GL_VERSION_3_1
    PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = nullptr;
    PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = nullptr;
    PFNGLTEXBUFFERPROC glTexBuffer = nullptr;
    PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex = nullptr;
    PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData = nullptr;
    PFNGLGETUNIFORMINDICESPROC glGetUniformIndices = nullptr;
    PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv = nullptr;
    PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName = nullptr;
    PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex = nullptr;
    PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv = nullptr;
    PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName = nullptr;
    PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding = nullptr;
#endif /* GL_VERSION_3_1 */
#ifdef GL_VERSION_3_2
    PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex = nullptr;
    PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glDrawRangeElementsBaseVertex =
        nullptr;
    PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glDrawElementsInstancedBaseVertex =
        nullptr;
    PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertex =
        nullptr;
    PFNGLPROVOKINGVERTEXPROC glProvokingVertex = nullptr;
    PFNGLFENCESYNCPROC glFenceSync = nullptr;
    PFNGLISSYNCPROC glIsSync = nullptr;
    PFNGLDELETESYNCPROC glDeleteSync = nullptr;
    PFNGLCLIENTWAITSYNCPROC glClientWaitSync = nullptr;
    PFNGLWAITSYNCPROC glWaitSync = nullptr;
    PFNGLGETINTEGER64VPROC glGetInteger64v = nullptr;
    PFNGLGETSYNCIVPROC glGetSynciv = nullptr;
    PFNGLGETINTEGER64I_VPROC glGetInteger64i_v = nullptr;
    PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v = nullptr;
    PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture = nullptr;
    PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample = nullptr;
    PFNGLTEXIMAGE3DMULTISAMPLEPROC glTexImage3DMultisample = nullptr;
    PFNGLGETMULTISAMPLEFVPROC glGetMultisamplefv = nullptr;
    PFNGLSAMPLEMASKIPROC glSampleMaski = nullptr;
#endif /* GL_VERSION_3_2 */
#ifdef GL_VERSION_3_3
    PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glBindFragDataLocationIndexed =
        nullptr;
    PFNGLGETFRAGDATAINDEXPROC glGetFragDataIndex = nullptr;
    PFNGLGENSAMPLERSPROC glGenSamplers = nullptr;
    PFNGLDELETESAMPLERSPROC glDeleteSamplers = nullptr;
    PFNGLISSAMPLERPROC glIsSampler = nullptr;
    PFNGLBINDSAMPLERPROC glBindSampler = nullptr;
    PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri = nullptr;
    PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv = nullptr;
    PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf = nullptr;
    PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv = nullptr;
    PFNGLSAMPLERPARAMETERIIVPROC glSamplerParameterIiv = nullptr;
    PFNGLSAMPLERPARAMETERIUIVPROC glSamplerParameterIuiv = nullptr;
    PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv = nullptr;
    PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIiv = nullptr;
    PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv = nullptr;
    PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameterIuiv = nullptr;
    PFNGLQUERYCOUNTERPROC glQueryCounter = nullptr;
    PFNGLGETQUERYOBJECTI64VPROC glGetQueryObjecti64v = nullptr;
    PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v = nullptr;
    PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor = nullptr;
    PFNGLVERTEXATTRIBP1UIPROC glVertexAttribP1ui = nullptr;
    PFNGLVERTEXATTRIBP1UIVPROC glVertexAttribP1uiv = nullptr;
    PFNGLVERTEXATTRIBP2UIPROC glVertexAttribP2ui = nullptr;
    PFNGLVERTEXATTRIBP2UIVPROC glVertexAttribP2uiv = nullptr;
    PFNGLVERTEXATTRIBP3UIPROC glVertexAttribP3ui = nullptr;
    PFNGLVERTEXATTRIBP3UIVPROC glVertexAttribP3uiv = nullptr;
    PFNGLVERTEXATTRIBP4UIPROC glVertexAttribP4ui = nullptr;
    PFNGLVERTEXATTRIBP4UIVPROC glVertexAttribP4uiv = nullptr;
#endif /* GL_VERSION_3_3 */
#ifdef GL_VERSION_4_0
    PFNGLMINSAMPLESHADINGPROC glMinSampleShading = nullptr;
    PFNGLBLENDEQUATIONIPROC glBlendEquationi = nullptr;
    PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei = nullptr;
    PFNGLBLENDFUNCIPROC glBlendFunci = nullptr;
    PFNGLBLENDFUNCSEPARATEIPROC glBlendFuncSeparatei = nullptr;
    PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirect = nullptr;
    PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirect = nullptr;
    PFNGLUNIFORM1DPROC glUniform1d = nullptr;
    PFNGLUNIFORM2DPROC glUniform2d = nullptr;
    PFNGLUNIFORM3DPROC glUniform3d = nullptr;
    PFNGLUNIFORM4DPROC glUniform4d = nullptr;
    PFNGLUNIFORM1DVPROC glUniform1dv = nullptr;
    PFNGLUNIFORM2DVPROC glUniform2dv = nullptr;
    PFNGLUNIFORM3DVPROC glUniform3dv = nullptr;
    PFNGLUNIFORM4DVPROC glUniform4dv = nullptr;
    PFNGLUNIFORMMATRIX2DVPROC glUniformMatrix2dv = nullptr;
    PFNGLUNIFORMMATRIX3DVPROC glUniformMatrix3dv = nullptr;
    PFNGLUNIFORMMATRIX4DVPROC glUniformMatrix4dv = nullptr;
    PFNGLUNIFORMMATRIX2X3DVPROC glUniformMatrix2x3dv = nullptr;
    PFNGLUNIFORMMATRIX2X4DVPROC glUniformMatrix2x4dv = nullptr;
    PFNGLUNIFORMMATRIX3X2DVPROC glUniformMatrix3x2dv = nullptr;
    PFNGLUNIFORMMATRIX3X4DVPROC glUniformMatrix3x4dv = nullptr;
    PFNGLUNIFORMMATRIX4X2DVPROC glUniformMatrix4x2dv = nullptr;
    PFNGLUNIFORMMATRIX4X3DVPROC glUniformMatrix4x3dv = nullptr;
    PFNGLGETUNIFORMDVPROC glGetUniformdv = nullptr;
    PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glGetSubroutineUniformLocation =
        nullptr;
    PFNGLGETSUBROUTINEINDEXPROC glGetSubroutineIndex = nullptr;
    PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformiv =
        nullptr;
    PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformName =
        nullptr;
    PFNGLGETACTIVESUBROUTINENAMEPROC glGetActiveSubroutineName = nullptr;
    PFNGLUNIFORMSUBROUTINESUIVPROC glUniformSubroutinesuiv = nullptr;
    PFNGLGETUNIFORMSUBROUTINEUIVPROC glGetUniformSubroutineuiv = nullptr;
    PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageiv = nullptr;
    PFNGLPATCHPARAMETERIPROC glPatchParameteri = nullptr;
    PFNGLPATCHPARAMETERFVPROC glPatchParameterfv = nullptr;
    PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback = nullptr;
    PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks = nullptr;
    PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks = nullptr;
    PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback = nullptr;
    PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback = nullptr;
    PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback = nullptr;
    PFNGLDRAWTRANSFORMFEEDBACKPROC glDrawTransformFeedback = nullptr;
    PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glDrawTransformFeedbackStream =
        nullptr;
    PFNGLBEGINQUERYINDEXEDPROC glBeginQueryIndexed = nullptr;
    PFNGLENDQUERYINDEXEDPROC glEndQueryIndexed = nullptr;
    PFNGLGETQUERYINDEXEDIVPROC glGetQueryIndexediv = nullptr;
#endif /* GL_VERSION_4_0 */
#ifdef GL_VERSION_4_1
    PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler = nullptr;
    PFNGLSHADERBINARYPROC glShaderBinary = nullptr;
    PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat = nullptr;
    PFNGLDEPTHRANGEFPROC glDepthRangef = nullptr;
    PFNGLCLEARDEPTHFPROC glClearDepthf = nullptr;
    PFNGLGETPROGRAMBINARYPROC glGetProgramBinary = nullptr;
    PFNGLPROGRAMBINARYPROC glProgramBinary = nullptr;
    PFNGLPROGRAMPARAMETERIPROC glProgramParameteri = nullptr;
    PFNGLUSEPROGRAMSTAGESPROC glUseProgramStages = nullptr;
    PFNGLACTIVESHADERPROGRAMPROC glActiveShaderProgram = nullptr;
    PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv = nullptr;
    PFNGLBINDPROGRAMPIPELINEPROC glBindProgramPipeline = nullptr;
    PFNGLDELETEPROGRAMPIPELINESPROC glDeleteProgramPipelines = nullptr;
    PFNGLGENPROGRAMPIPELINESPROC glGenProgramPipelines = nullptr;
    PFNGLISPROGRAMPIPELINEPROC glIsProgramPipeline = nullptr;
    PFNGLGETPROGRAMPIPELINEIVPROC glGetProgramPipelineiv = nullptr;
    PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i = nullptr;
    PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1iv = nullptr;
    PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f = nullptr;
    PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fv = nullptr;
    PFNGLPROGRAMUNIFORM1DPROC glProgramUniform1d = nullptr;
    PFNGLPROGRAMUNIFORM1DVPROC glProgramUniform1dv = nullptr;
    PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1ui = nullptr;
    PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uiv = nullptr;
    PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2i = nullptr;
    PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2iv = nullptr;
    PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f = nullptr;
    PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fv = nullptr;
    PFNGLPROGRAMUNIFORM2DPROC glProgramUniform2d = nullptr;
    PFNGLPROGRAMUNIFORM2DVPROC glProgramUniform2dv = nullptr;
    PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2ui = nullptr;
    PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uiv = nullptr;
    PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3i = nullptr;
    PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3iv = nullptr;
    PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f = nullptr;
    PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv = nullptr;
    PFNGLPROGRAMUNIFORM3DPROC glProgramUniform3d = nullptr;
    PFNGLPROGRAMUNIFORM3DVPROC glProgramUniform3dv = nullptr;
    PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3ui = nullptr;
    PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uiv = nullptr;
    PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i = nullptr;
    PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4iv = nullptr;
    PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f = nullptr;
    PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv = nullptr;
    PFNGLPROGRAMUNIFORM4DPROC glProgramUniform4d = nullptr;
    PFNGLPROGRAMUNIFORM4DVPROC glProgramUniform4dv = nullptr;
    PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4ui = nullptr;
    PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uiv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2DVPROC glProgramUniformMatrix2dv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3DVPROC glProgramUniformMatrix3dv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4DVPROC glProgramUniformMatrix4dv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glProgramUniformMatrix2x3dv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glProgramUniformMatrix3x2dv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glProgramUniformMatrix2x4dv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glProgramUniformMatrix4x2dv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glProgramUniformMatrix3x4dv = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glProgramUniformMatrix4x3dv = nullptr;
    PFNGLVALIDATEPROGRAMPIPELINEPROC glValidateProgramPipeline = nullptr;
    PFNGLGETPROGRAMPIPELINEINFOLOGPROC glGetProgramPipelineInfoLog = nullptr;
    PFNGLVERTEXATTRIBL1DPROC glVertexAttribL1d = nullptr;
    PFNGLVERTEXATTRIBL2DPROC glVertexAttribL2d = nullptr;
    PFNGLVERTEXATTRIBL3DPROC glVertexAttribL3d = nullptr;
    PFNGLVERTEXATTRIBL4DPROC glVertexAttribL4d = nullptr;
    PFNGLVERTEXATTRIBL1DVPROC glVertexAttribL1dv = nullptr;
    PFNGLVERTEXATTRIBL2DVPROC glVertexAttribL2dv = nullptr;
    PFNGLVERTEXATTRIBL3DVPROC glVertexAttribL3dv = nullptr;
    PFNGLVERTEXATTRIBL4DVPROC glVertexAttribL4dv = nullptr;
    PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttribLPointer = nullptr;
    PFNGLGETVERTEXATTRIBLDVPROC glGetVertexAttribLdv = nullptr;
    PFNGLVIEWPORTARRAYVPROC glViewportArrayv = nullptr;
    PFNGLVIEWPORTINDEXEDFPROC glViewportIndexedf = nullptr;
    PFNGLVIEWPORTINDEXEDFVPROC glViewportIndexedfv = nullptr;
    PFNGLSCISSORARRAYVPROC glScissorArrayv = nullptr;
    PFNGLSCISSORINDEXEDPROC glScissorIndexed = nullptr;
    PFNGLSCISSORINDEXEDVPROC glScissorIndexedv = nullptr;
    PFNGLDEPTHRANGEARRAYVPROC glDepthRangeArrayv = nullptr;
    PFNGLDEPTHRANGEINDEXEDPROC glDepthRangeIndexed = nullptr;
    PFNGLGETFLOATI_VPROC glGetFloati_v = nullptr;
    PFNGLGETDOUBLEI_VPROC glGetDoublei_v = nullptr;
#endif /* GL_VERSION_4_1 */
#ifdef GL_VERSION_4_2
    PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glDrawArraysInstancedBaseInstance =
        nullptr;
    PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC
    glDrawElementsInstancedBaseInstance = nullptr;
    PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC
    glDrawElementsInstancedBaseVertexBaseInstance = nullptr;
    PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ = nullptr;
    PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glGetActiveAtomicCounterBufferiv =
        nullptr;
    PFNGLBINDIMAGETEXTUREPROC glBindImageTexture = nullptr;
    PFNGLMEMORYBARRIERPROC glMemoryBarrier = nullptr;
    PFNGLTEXSTORAGE1DPROC glTexStorage1D = nullptr;
    PFNGLTEXSTORAGE2DPROC glTexStorage2D = nullptr;
    PFNGLTEXSTORAGE3DPROC glTexStorage3D = nullptr;
    PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glDrawTransformFeedbackInstanced =
        nullptr;
    PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC
    glDrawTransformFeedbackStreamInstanced = nullptr;
#endif /* GL_VERSION_4_2 */
#ifdef GL_VERSION_4_3
    PFNGLCLEARBUFFERDATAPROC glClearBufferData = nullptr;
    PFNGLCLEARBUFFERSUBDATAPROC glClearBufferSubData = nullptr;
    PFNGLDISPATCHCOMPUTEPROC glDispatchCompute = nullptr;
    PFNGLDISPATCHCOMPUTEINDIRECTPROC glDispatchComputeIndirect = nullptr;
    PFNGLCOPYIMAGESUBDATAPROC glCopyImageSubData = nullptr;
    PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteri = nullptr;
    PFNGLGETFRAMEBUFFERPARAMETERIVPROC glGetFramebufferParameteriv = nullptr;
    PFNGLGETINTERNALFORMATI64VPROC glGetInternalformati64v = nullptr;
    PFNGLINVALIDATETEXSUBIMAGEPROC glInvalidateTexSubImage = nullptr;
    PFNGLINVALIDATETEXIMAGEPROC glInvalidateTexImage = nullptr;
    PFNGLINVALIDATEBUFFERSUBDATAPROC glInvalidateBufferSubData = nullptr;
    PFNGLINVALIDATEBUFFERDATAPROC glInvalidateBufferData = nullptr;
    PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer = nullptr;
    PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer = nullptr;
    PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirect = nullptr;
    PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirect = nullptr;
    PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceiv = nullptr;
    PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndex = nullptr;
    PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName = nullptr;
    PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv = nullptr;
    PFNGLGETPROGRAMRESOURCELOCATIONPROC glGetProgramResourceLocation = nullptr;
    PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glGetProgramResourceLocationIndex =
        nullptr;
    PFNGLSHADERSTORAGEBLOCKBINDINGPROC glShaderStorageBlockBinding = nullptr;
    PFNGLTEXBUFFERRANGEPROC glTexBufferRange = nullptr;
    PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisample = nullptr;
    PFNGLTEXSTORAGE3DMULTISAMPLEPROC glTexStorage3DMultisample = nullptr;
    PFNGLTEXTUREVIEWPROC glTextureView = nullptr;
    PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer = nullptr;
    PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormat = nullptr;
    PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormat = nullptr;
    PFNGLVERTEXATTRIBLFORMATPROC glVertexAttribLFormat = nullptr;
    PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBinding = nullptr;
    PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisor = nullptr;
    PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl = nullptr;
    PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsert = nullptr;
    PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback = nullptr;
    PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLog = nullptr;
    PFNGLPUSHDEBUGGROUPPROC glPushDebugGroup = nullptr;
    PFNGLPOPDEBUGGROUPPROC glPopDebugGroup = nullptr;
    PFNGLOBJECTLABELPROC glObjectLabel = nullptr;
    PFNGLGETOBJECTLABELPROC glGetObjectLabel = nullptr;
    PFNGLOBJECTPTRLABELPROC glObjectPtrLabel = nullptr;
    PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabel = nullptr;
#endif /* GL_VERSION_4_3 */
#ifdef GL_VERSION_4_4
    PFNGLBUFFERSTORAGEPROC glBufferStorage = nullptr;
    PFNGLCLEARTEXIMAGEPROC glClearTexImage = nullptr;
    PFNGLCLEARTEXSUBIMAGEPROC glClearTexSubImage = nullptr;
    PFNGLBINDBUFFERSBASEPROC glBindBuffersBase = nullptr;
    PFNGLBINDBUFFERSRANGEPROC glBindBuffersRange = nullptr;
    PFNGLBINDTEXTURESPROC glBindTextures = nullptr;
    PFNGLBINDSAMPLERSPROC glBindSamplers = nullptr;
    PFNGLBINDIMAGETEXTURESPROC glBindImageTextures = nullptr;
    PFNGLBINDVERTEXBUFFERSPROC glBindVertexBuffers = nullptr;
#endif /* GL_VERSION_4_4 */
#ifdef GL_VERSION_4_5
    PFNGLCLIPCONTROLPROC glClipControl = nullptr;
    PFNGLCREATETRANSFORMFEEDBACKSPROC glCreateTransformFeedbacks = nullptr;
    PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC glTransformFeedbackBufferBase =
        nullptr;
    PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC glTransformFeedbackBufferRange =
        nullptr;
    PFNGLGETTRANSFORMFEEDBACKIVPROC glGetTransformFeedbackiv = nullptr;
    PFNGLGETTRANSFORMFEEDBACKI_VPROC glGetTransformFeedbacki_v = nullptr;
    PFNGLGETTRANSFORMFEEDBACKI64_VPROC glGetTransformFeedbacki64_v = nullptr;
    PFNGLCREATEBUFFERSPROC glCreateBuffers = nullptr;
    PFNGLNAMEDBUFFERSTORAGEPROC glNamedBufferStorage = nullptr;
    PFNGLNAMEDBUFFERDATAPROC glNamedBufferData = nullptr;
    PFNGLNAMEDBUFFERSUBDATAPROC glNamedBufferSubData = nullptr;
    PFNGLCOPYNAMEDBUFFERSUBDATAPROC glCopyNamedBufferSubData = nullptr;
    PFNGLCLEARNAMEDBUFFERDATAPROC glClearNamedBufferData = nullptr;
    PFNGLCLEARNAMEDBUFFERSUBDATAPROC glClearNamedBufferSubData = nullptr;
    PFNGLMAPNAMEDBUFFERPROC glMapNamedBuffer = nullptr;
    PFNGLMAPNAMEDBUFFERRANGEPROC glMapNamedBufferRange = nullptr;
    PFNGLUNMAPNAMEDBUFFERPROC glUnmapNamedBuffer = nullptr;
    PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC glFlushMappedNamedBufferRange =
        nullptr;
    PFNGLGETNAMEDBUFFERPARAMETERIVPROC glGetNamedBufferParameteriv = nullptr;
    PFNGLGETNAMEDBUFFERPARAMETERI64VPROC glGetNamedBufferParameteri64v =
        nullptr;
    PFNGLGETNAMEDBUFFERPOINTERVPROC glGetNamedBufferPointerv = nullptr;
    PFNGLGETNAMEDBUFFERSUBDATAPROC glGetNamedBufferSubData = nullptr;
    PFNGLCREATEFRAMEBUFFERSPROC glCreateFramebuffers = nullptr;
    PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC glNamedFramebufferRenderbuffer =
        nullptr;
    PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC glNamedFramebufferParameteri = nullptr;
    PFNGLNAMEDFRAMEBUFFERTEXTUREPROC glNamedFramebufferTexture = nullptr;
    PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC glNamedFramebufferTextureLayer =
        nullptr;
    PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC glNamedFramebufferDrawBuffer = nullptr;
    PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC glNamedFramebufferDrawBuffers =
        nullptr;
    PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC glNamedFramebufferReadBuffer = nullptr;
    PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC glInvalidateNamedFramebufferData =
        nullptr;
    PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC
    glInvalidateNamedFramebufferSubData = nullptr;
    PFNGLCLEARNAMEDFRAMEBUFFERIVPROC glClearNamedFramebufferiv = nullptr;
    PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC glClearNamedFramebufferuiv = nullptr;
    PFNGLCLEARNAMEDFRAMEBUFFERFVPROC glClearNamedFramebufferfv = nullptr;
    PFNGLCLEARNAMEDFRAMEBUFFERFIPROC glClearNamedFramebufferfi = nullptr;
    PFNGLBLITNAMEDFRAMEBUFFERPROC glBlitNamedFramebuffer = nullptr;
    PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC glCheckNamedFramebufferStatus =
        nullptr;
    PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC glGetNamedFramebufferParameteriv =
        nullptr;
    PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC
    glGetNamedFramebufferAttachmentParameteriv = nullptr;
    PFNGLCREATERENDERBUFFERSPROC glCreateRenderbuffers = nullptr;
    PFNGLNAMEDRENDERBUFFERSTORAGEPROC glNamedRenderbufferStorage = nullptr;
    PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC
    glNamedRenderbufferStorageMultisample = nullptr;
    PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC glGetNamedRenderbufferParameteriv =
        nullptr;
    PFNGLCREATETEXTURESPROC glCreateTextures = nullptr;
    PFNGLTEXTUREBUFFERPROC glTextureBuffer = nullptr;
    PFNGLTEXTUREBUFFERRANGEPROC glTextureBufferRange = nullptr;
    PFNGLTEXTURESTORAGE1DPROC glTextureStorage1D = nullptr;
    PFNGLTEXTURESTORAGE2DPROC glTextureStorage2D = nullptr;
    PFNGLTEXTURESTORAGE3DPROC glTextureStorage3D = nullptr;
    PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC glTextureStorage2DMultisample =
        nullptr;
    PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC glTextureStorage3DMultisample =
        nullptr;
    PFNGLTEXTURESUBIMAGE1DPROC glTextureSubImage1D = nullptr;
    PFNGLTEXTURESUBIMAGE2DPROC glTextureSubImage2D = nullptr;
    PFNGLTEXTURESUBIMAGE3DPROC glTextureSubImage3D = nullptr;
    PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC glCompressedTextureSubImage1D =
        nullptr;
    PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC glCompressedTextureSubImage2D =
        nullptr;
    PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC glCompressedTextureSubImage3D =
        nullptr;
    PFNGLCOPYTEXTURESUBIMAGE1DPROC glCopyTextureSubImage1D = nullptr;
    PFNGLCOPYTEXTURESUBIMAGE2DPROC glCopyTextureSubImage2D = nullptr;
    PFNGLCOPYTEXTURESUBIMAGE3DPROC glCopyTextureSubImage3D = nullptr;
    PFNGLTEXTUREPARAMETERFPROC glTextureParameterf = nullptr;
    PFNGLTEXTUREPARAMETERFVPROC glTextureParameterfv = nullptr;
    PFNGLTEXTUREPARAMETERIPROC glTextureParameteri = nullptr;
    PFNGLTEXTUREPARAMETERIIVPROC glTextureParameterIiv = nullptr;
    PFNGLTEXTUREPARAMETERIUIVPROC glTextureParameterIuiv = nullptr;
    PFNGLTEXTUREPARAMETERIVPROC glTextureParameteriv = nullptr;
    PFNGLGENERATETEXTUREMIPMAPPROC glGenerateTextureMipmap = nullptr;
    PFNGLBINDTEXTUREUNITPROC glBindTextureUnit = nullptr;
    PFNGLGETTEXTUREIMAGEPROC glGetTextureImage = nullptr;
    PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC glGetCompressedTextureImage = nullptr;
    PFNGLGETTEXTURELEVELPARAMETERFVPROC glGetTextureLevelParameterfv = nullptr;
    PFNGLGETTEXTURELEVELPARAMETERIVPROC glGetTextureLevelParameteriv = nullptr;
    PFNGLGETTEXTUREPARAMETERFVPROC glGetTextureParameterfv = nullptr;
    PFNGLGETTEXTUREPARAMETERIIVPROC glGetTextureParameterIiv = nullptr;
    PFNGLGETTEXTUREPARAMETERIUIVPROC glGetTextureParameterIuiv = nullptr;
    PFNGLGETTEXTUREPARAMETERIVPROC glGetTextureParameteriv = nullptr;
    PFNGLCREATEVERTEXARRAYSPROC glCreateVertexArrays = nullptr;
    PFNGLDISABLEVERTEXARRAYATTRIBPROC glDisableVertexArrayAttrib = nullptr;
    PFNGLENABLEVERTEXARRAYATTRIBPROC glEnableVertexArrayAttrib = nullptr;
    PFNGLVERTEXARRAYELEMENTBUFFERPROC glVertexArrayElementBuffer = nullptr;
    PFNGLVERTEXARRAYVERTEXBUFFERPROC glVertexArrayVertexBuffer = nullptr;
    PFNGLVERTEXARRAYVERTEXBUFFERSPROC glVertexArrayVertexBuffers = nullptr;
    PFNGLVERTEXARRAYATTRIBBINDINGPROC glVertexArrayAttribBinding = nullptr;
    PFNGLVERTEXARRAYATTRIBFORMATPROC glVertexArrayAttribFormat = nullptr;
    PFNGLVERTEXARRAYATTRIBIFORMATPROC glVertexArrayAttribIFormat = nullptr;
    PFNGLVERTEXARRAYATTRIBLFORMATPROC glVertexArrayAttribLFormat = nullptr;
    PFNGLVERTEXARRAYBINDINGDIVISORPROC glVertexArrayBindingDivisor = nullptr;
    PFNGLGETVERTEXARRAYIVPROC glGetVertexArrayiv = nullptr;
    PFNGLGETVERTEXARRAYINDEXEDIVPROC glGetVertexArrayIndexediv = nullptr;
    PFNGLGETVERTEXARRAYINDEXED64IVPROC glGetVertexArrayIndexed64iv = nullptr;
    PFNGLCREATESAMPLERSPROC glCreateSamplers = nullptr;
    PFNGLCREATEPROGRAMPIPELINESPROC glCreateProgramPipelines = nullptr;
    PFNGLCREATEQUERIESPROC glCreateQueries = nullptr;
    PFNGLGETQUERYBUFFEROBJECTI64VPROC glGetQueryBufferObjecti64v = nullptr;
    PFNGLGETQUERYBUFFEROBJECTIVPROC glGetQueryBufferObjectiv = nullptr;
    PFNGLGETQUERYBUFFEROBJECTUI64VPROC glGetQueryBufferObjectui64v = nullptr;
    PFNGLGETQUERYBUFFEROBJECTUIVPROC glGetQueryBufferObjectuiv = nullptr;
    PFNGLMEMORYBARRIERBYREGIONPROC glMemoryBarrierByRegion = nullptr;
    PFNGLGETTEXTURESUBIMAGEPROC glGetTextureSubImage = nullptr;
    PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC glGetCompressedTextureSubImage =
        nullptr;
    PFNGLGETGRAPHICSRESETSTATUSPROC glGetGraphicsResetStatus = nullptr;
    PFNGLGETNCOMPRESSEDTEXIMAGEPROC glGetnCompressedTexImage = nullptr;
    PFNGLGETNTEXIMAGEPROC glGetnTexImage = nullptr;
    PFNGLGETNUNIFORMDVPROC glGetnUniformdv = nullptr;
    PFNGLGETNUNIFORMFVPROC glGetnUniformfv = nullptr;
    PFNGLGETNUNIFORMIVPROC glGetnUniformiv = nullptr;
    PFNGLGETNUNIFORMUIVPROC glGetnUniformuiv = nullptr;
    PFNGLREADNPIXELSPROC glReadnPixels = nullptr;
    PFNGLTEXTUREBARRIERPROC glTextureBarrier = nullptr;
#endif /* GL_VERSION_4_5 */
#ifdef GL_VERSION_4_6
    PFNGLSPECIALIZESHADERPROC glSpecializeShader = nullptr;
    PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC glMultiDrawArraysIndirectCount =
        nullptr;
    PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC glMultiDrawElementsIndirectCount =
        nullptr;
    PFNGLPOLYGONOFFSETCLAMPPROC glPolygonOffsetClamp = nullptr;
#endif /* GL_VERSION_4_6 */
#ifdef GL_ARB_ES2_compatibility
#endif /* GL_ARB_ES2_compatibility */
#ifdef GL_ARB_ES3_1_compatibility
#endif /* GL_ARB_ES3_1_compatibility */
#ifdef GL_ARB_ES3_2_compatibility
    PFNGLPRIMITIVEBOUNDINGBOXARBPROC glPrimitiveBoundingBoxARB = nullptr;
#endif /* GL_ARB_ES3_2_compatibility */
#ifdef GL_ARB_ES3_compatibility
#endif /* GL_ARB_ES3_compatibility */
#ifdef GL_ARB_arrays_of_arrays
#endif /* GL_ARB_arrays_of_arrays */
#ifdef GL_ARB_base_instance
#endif /* GL_ARB_base_instance */
#ifdef GL_ARB_bindless_texture
    PFNGLGETTEXTUREHANDLEARBPROC glGetTextureHandleARB = nullptr;
    PFNGLGETTEXTURESAMPLERHANDLEARBPROC glGetTextureSamplerHandleARB = nullptr;
    PFNGLMAKETEXTUREHANDLERESIDENTARBPROC glMakeTextureHandleResidentARB =
        nullptr;
    PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC glMakeTextureHandleNonResidentARB =
        nullptr;
    PFNGLGETIMAGEHANDLEARBPROC glGetImageHandleARB = nullptr;
    PFNGLMAKEIMAGEHANDLERESIDENTARBPROC glMakeImageHandleResidentARB = nullptr;
    PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC glMakeImageHandleNonResidentARB =
        nullptr;
    PFNGLUNIFORMHANDLEUI64ARBPROC glUniformHandleui64ARB = nullptr;
    PFNGLUNIFORMHANDLEUI64VARBPROC glUniformHandleui64vARB = nullptr;
    PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC glProgramUniformHandleui64ARB =
        nullptr;
    PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC glProgramUniformHandleui64vARB =
        nullptr;
    PFNGLISTEXTUREHANDLERESIDENTARBPROC glIsTextureHandleResidentARB = nullptr;
    PFNGLISIMAGEHANDLERESIDENTARBPROC glIsImageHandleResidentARB = nullptr;
    PFNGLVERTEXATTRIBL1UI64ARBPROC glVertexAttribL1ui64ARB = nullptr;
    PFNGLVERTEXATTRIBL1UI64VARBPROC glVertexAttribL1ui64vARB = nullptr;
    PFNGLGETVERTEXATTRIBLUI64VARBPROC glGetVertexAttribLui64vARB = nullptr;
#endif /* GL_ARB_bindless_texture */
#ifdef GL_ARB_blend_func_extended
#endif /* GL_ARB_blend_func_extended */
#ifdef GL_ARB_buffer_storage
#endif /* GL_ARB_buffer_storage */
#ifdef GL_ARB_cl_event
    PFNGLCREATESYNCFROMCLEVENTARBPROC glCreateSyncFromCLeventARB = nullptr;
#endif /* GL_ARB_cl_event */
#ifdef GL_ARB_clear_buffer_object
#endif /* GL_ARB_clear_buffer_object */
#ifdef GL_ARB_clear_texture
#endif /* GL_ARB_clear_texture */
#ifdef GL_ARB_clip_control
#endif /* GL_ARB_clip_control */
#ifdef GL_ARB_compressed_texture_pixel_storage
#endif /* GL_ARB_compressed_texture_pixel_storage */
#ifdef GL_ARB_compute_shader
#endif /* GL_ARB_compute_shader */
#ifdef GL_ARB_compute_variable_group_size
    PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC glDispatchComputeGroupSizeARB =
        nullptr;
#endif /* GL_ARB_compute_variable_group_size */
#ifdef GL_ARB_conditional_render_inverted
#endif /* GL_ARB_conditional_render_inverted */
#ifdef GL_ARB_conservative_depth
#endif /* GL_ARB_conservative_depth */
#ifdef GL_ARB_copy_buffer
#endif /* GL_ARB_copy_buffer */
#ifdef GL_ARB_copy_image
#endif /* GL_ARB_copy_image */
#ifdef GL_ARB_cull_distance
#endif /* GL_ARB_cull_distance */
#ifdef GL_ARB_debug_output
    PFNGLDEBUGMESSAGECONTROLARBPROC glDebugMessageControlARB = nullptr;
    PFNGLDEBUGMESSAGEINSERTARBPROC glDebugMessageInsertARB = nullptr;
    PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallbackARB = nullptr;
    PFNGLGETDEBUGMESSAGELOGARBPROC glGetDebugMessageLogARB = nullptr;
#endif /* GL_ARB_debug_output */
#ifdef GL_ARB_depth_buffer_float
#endif /* GL_ARB_depth_buffer_float */
#ifdef GL_ARB_depth_clamp
#endif /* GL_ARB_depth_clamp */
#ifdef GL_ARB_derivative_control
#endif /* GL_ARB_derivative_control */
#ifdef GL_ARB_direct_state_access
#endif /* GL_ARB_direct_state_access */
#ifdef GL_ARB_draw_buffers_blend
    PFNGLBLENDEQUATIONIARBPROC glBlendEquationiARB = nullptr;
    PFNGLBLENDEQUATIONSEPARATEIARBPROC glBlendEquationSeparateiARB = nullptr;
    PFNGLBLENDFUNCIARBPROC glBlendFunciARB = nullptr;
    PFNGLBLENDFUNCSEPARATEIARBPROC glBlendFuncSeparateiARB = nullptr;
#endif /* GL_ARB_draw_buffers_blend */
#ifdef GL_ARB_draw_elements_base_vertex
#endif /* GL_ARB_draw_elements_base_vertex */
#ifdef GL_ARB_draw_indirect
#endif /* GL_ARB_draw_indirect */
#ifdef GL_ARB_draw_instanced
    PFNGLDRAWARRAYSINSTANCEDARBPROC glDrawArraysInstancedARB = nullptr;
    PFNGLDRAWELEMENTSINSTANCEDARBPROC glDrawElementsInstancedARB = nullptr;
#endif /* GL_ARB_draw_instanced */
#ifdef GL_ARB_enhanced_layouts
#endif /* GL_ARB_enhanced_layouts */
#ifdef GL_ARB_explicit_attrib_location
#endif /* GL_ARB_explicit_attrib_location */
#ifdef GL_ARB_explicit_uniform_location
#endif /* GL_ARB_explicit_uniform_location */
#ifdef GL_ARB_fragment_coord_conventions
#endif /* GL_ARB_fragment_coord_conventions */
#ifdef GL_ARB_fragment_layer_viewport
#endif /* GL_ARB_fragment_layer_viewport */
#ifdef GL_ARB_fragment_shader_interlock
#endif /* GL_ARB_fragment_shader_interlock */
#ifdef GL_ARB_framebuffer_no_attachments
#endif /* GL_ARB_framebuffer_no_attachments */
#ifdef GL_ARB_framebuffer_object
#endif /* GL_ARB_framebuffer_object */
#ifdef GL_ARB_framebuffer_sRGB
#endif /* GL_ARB_framebuffer_sRGB */
#ifdef GL_ARB_geometry_shader4
    PFNGLPROGRAMPARAMETERIARBPROC glProgramParameteriARB = nullptr;
    PFNGLFRAMEBUFFERTEXTUREARBPROC glFramebufferTextureARB = nullptr;
    PFNGLFRAMEBUFFERTEXTURELAYERARBPROC glFramebufferTextureLayerARB = nullptr;
    PFNGLFRAMEBUFFERTEXTUREFACEARBPROC glFramebufferTextureFaceARB = nullptr;
#endif /* GL_ARB_geometry_shader4 */
#ifdef GL_ARB_get_program_binary
#endif /* GL_ARB_get_program_binary */
#ifdef GL_ARB_get_texture_sub_image
#endif /* GL_ARB_get_texture_sub_image */
#ifdef GL_ARB_gl_spirv
    PFNGLSPECIALIZESHADERARBPROC glSpecializeShaderARB = nullptr;
#endif /* GL_ARB_gl_spirv */
#ifdef GL_ARB_gpu_shader5
#endif /* GL_ARB_gpu_shader5 */
#ifdef GL_ARB_gpu_shader_fp64
#endif /* GL_ARB_gpu_shader_fp64 */
#ifdef GL_ARB_gpu_shader_int64
    PFNGLUNIFORM1I64ARBPROC glUniform1i64ARB = nullptr;
    PFNGLUNIFORM2I64ARBPROC glUniform2i64ARB = nullptr;
    PFNGLUNIFORM3I64ARBPROC glUniform3i64ARB = nullptr;
    PFNGLUNIFORM4I64ARBPROC glUniform4i64ARB = nullptr;
    PFNGLUNIFORM1I64VARBPROC glUniform1i64vARB = nullptr;
    PFNGLUNIFORM2I64VARBPROC glUniform2i64vARB = nullptr;
    PFNGLUNIFORM3I64VARBPROC glUniform3i64vARB = nullptr;
    PFNGLUNIFORM4I64VARBPROC glUniform4i64vARB = nullptr;
    PFNGLUNIFORM1UI64ARBPROC glUniform1ui64ARB = nullptr;
    PFNGLUNIFORM2UI64ARBPROC glUniform2ui64ARB = nullptr;
    PFNGLUNIFORM3UI64ARBPROC glUniform3ui64ARB = nullptr;
    PFNGLUNIFORM4UI64ARBPROC glUniform4ui64ARB = nullptr;
    PFNGLUNIFORM1UI64VARBPROC glUniform1ui64vARB = nullptr;
    PFNGLUNIFORM2UI64VARBPROC glUniform2ui64vARB = nullptr;
    PFNGLUNIFORM3UI64VARBPROC glUniform3ui64vARB = nullptr;
    PFNGLUNIFORM4UI64VARBPROC glUniform4ui64vARB = nullptr;
    PFNGLGETUNIFORMI64VARBPROC glGetUniformi64vARB = nullptr;
    PFNGLGETUNIFORMUI64VARBPROC glGetUniformui64vARB = nullptr;
    PFNGLGETNUNIFORMI64VARBPROC glGetnUniformi64vARB = nullptr;
    PFNGLGETNUNIFORMUI64VARBPROC glGetnUniformui64vARB = nullptr;
    PFNGLPROGRAMUNIFORM1I64ARBPROC glProgramUniform1i64ARB = nullptr;
    PFNGLPROGRAMUNIFORM2I64ARBPROC glProgramUniform2i64ARB = nullptr;
    PFNGLPROGRAMUNIFORM3I64ARBPROC glProgramUniform3i64ARB = nullptr;
    PFNGLPROGRAMUNIFORM4I64ARBPROC glProgramUniform4i64ARB = nullptr;
    PFNGLPROGRAMUNIFORM1I64VARBPROC glProgramUniform1i64vARB = nullptr;
    PFNGLPROGRAMUNIFORM2I64VARBPROC glProgramUniform2i64vARB = nullptr;
    PFNGLPROGRAMUNIFORM3I64VARBPROC glProgramUniform3i64vARB = nullptr;
    PFNGLPROGRAMUNIFORM4I64VARBPROC glProgramUniform4i64vARB = nullptr;
    PFNGLPROGRAMUNIFORM1UI64ARBPROC glProgramUniform1ui64ARB = nullptr;
    PFNGLPROGRAMUNIFORM2UI64ARBPROC glProgramUniform2ui64ARB = nullptr;
    PFNGLPROGRAMUNIFORM3UI64ARBPROC glProgramUniform3ui64ARB = nullptr;
    PFNGLPROGRAMUNIFORM4UI64ARBPROC glProgramUniform4ui64ARB = nullptr;
    PFNGLPROGRAMUNIFORM1UI64VARBPROC glProgramUniform1ui64vARB = nullptr;
    PFNGLPROGRAMUNIFORM2UI64VARBPROC glProgramUniform2ui64vARB = nullptr;
    PFNGLPROGRAMUNIFORM3UI64VARBPROC glProgramUniform3ui64vARB = nullptr;
    PFNGLPROGRAMUNIFORM4UI64VARBPROC glProgramUniform4ui64vARB = nullptr;
#endif /* GL_ARB_gpu_shader_int64 */
#ifdef GL_ARB_half_float_vertex
#endif /* GL_ARB_half_float_vertex */
#ifdef GL_ARB_imaging
#endif /* GL_ARB_imaging */
#ifdef GL_ARB_indirect_parameters
    PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC glMultiDrawArraysIndirectCountARB =
        nullptr;
    PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC
    glMultiDrawElementsIndirectCountARB = nullptr;
#endif /* GL_ARB_indirect_parameters */
#ifdef GL_ARB_instanced_arrays
    PFNGLVERTEXATTRIBDIVISORARBPROC glVertexAttribDivisorARB = nullptr;
#endif /* GL_ARB_instanced_arrays */
#ifdef GL_ARB_internalformat_query
#endif /* GL_ARB_internalformat_query */
#ifdef GL_ARB_internalformat_query2
#endif /* GL_ARB_internalformat_query2 */
#ifdef GL_ARB_invalidate_subdata
#endif /* GL_ARB_invalidate_subdata */
#ifdef GL_ARB_map_buffer_alignment
#endif /* GL_ARB_map_buffer_alignment */
#ifdef GL_ARB_map_buffer_range
#endif /* GL_ARB_map_buffer_range */
#ifdef GL_ARB_multi_bind
#endif /* GL_ARB_multi_bind */
#ifdef GL_ARB_multi_draw_indirect
#endif /* GL_ARB_multi_draw_indirect */
#ifdef GL_ARB_occlusion_query2
#endif /* GL_ARB_occlusion_query2 */
#ifdef GL_ARB_parallel_shader_compile
    PFNGLMAXSHADERCOMPILERTHREADSARBPROC glMaxShaderCompilerThreadsARB =
        nullptr;
#endif /* GL_ARB_parallel_shader_compile */
#ifdef GL_ARB_pipeline_statistics_query
#endif /* GL_ARB_pipeline_statistics_query */
#ifdef GL_ARB_pixel_buffer_object
#endif /* GL_ARB_pixel_buffer_object */
#ifdef GL_ARB_polygon_offset_clamp
#endif /* GL_ARB_polygon_offset_clamp */
#ifdef GL_ARB_post_depth_coverage
#endif /* GL_ARB_post_depth_coverage */
#ifdef GL_ARB_program_interface_query
#endif /* GL_ARB_program_interface_query */
#ifdef GL_ARB_provoking_vertex
#endif /* GL_ARB_provoking_vertex */
#ifdef GL_ARB_query_buffer_object
#endif /* GL_ARB_query_buffer_object */
#ifdef GL_ARB_robust_buffer_access_behavior
#endif /* GL_ARB_robust_buffer_access_behavior */
#ifdef GL_ARB_robustness
    PFNGLGETGRAPHICSRESETSTATUSARBPROC glGetGraphicsResetStatusARB = nullptr;
    PFNGLGETNTEXIMAGEARBPROC glGetnTexImageARB = nullptr;
    PFNGLREADNPIXELSARBPROC glReadnPixelsARB = nullptr;
    PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC glGetnCompressedTexImageARB = nullptr;
    PFNGLGETNUNIFORMFVARBPROC glGetnUniformfvARB = nullptr;
    PFNGLGETNUNIFORMIVARBPROC glGetnUniformivARB = nullptr;
    PFNGLGETNUNIFORMUIVARBPROC glGetnUniformuivARB = nullptr;
    PFNGLGETNUNIFORMDVARBPROC glGetnUniformdvARB = nullptr;
#endif /* GL_ARB_robustness */
#ifdef GL_ARB_robustness_isolation
#endif /* GL_ARB_robustness_isolation */
#ifdef GL_ARB_sample_locations
    PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC glFramebufferSampleLocationsfvARB =
        nullptr;
    PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC
    glNamedFramebufferSampleLocationsfvARB = nullptr;
    PFNGLEVALUATEDEPTHVALUESARBPROC glEvaluateDepthValuesARB = nullptr;
#endif /* GL_ARB_sample_locations */
#ifdef GL_ARB_sample_shading
    PFNGLMINSAMPLESHADINGARBPROC glMinSampleShadingARB = nullptr;
#endif /* GL_ARB_sample_shading */
#ifdef GL_ARB_sampler_objects
#endif /* GL_ARB_sampler_objects */
#ifdef GL_ARB_seamless_cube_map
#endif /* GL_ARB_seamless_cube_map */
#ifdef GL_ARB_seamless_cubemap_per_texture
#endif /* GL_ARB_seamless_cubemap_per_texture */
#ifdef GL_ARB_separate_shader_objects
#endif /* GL_ARB_separate_shader_objects */
#ifdef GL_ARB_shader_atomic_counter_ops
#endif /* GL_ARB_shader_atomic_counter_ops */
#ifdef GL_ARB_shader_atomic_counters
#endif /* GL_ARB_shader_atomic_counters */
#ifdef GL_ARB_shader_ballot
#endif /* GL_ARB_shader_ballot */
#ifdef GL_ARB_shader_bit_encoding
#endif /* GL_ARB_shader_bit_encoding */
#ifdef GL_ARB_shader_clock
#endif /* GL_ARB_shader_clock */
#ifdef GL_ARB_shader_draw_parameters
#endif /* GL_ARB_shader_draw_parameters */
#ifdef GL_ARB_shader_group_vote
#endif /* GL_ARB_shader_group_vote */
#ifdef GL_ARB_shader_image_load_store
#endif /* GL_ARB_shader_image_load_store */
#ifdef GL_ARB_shader_image_size
#endif /* GL_ARB_shader_image_size */
#ifdef GL_ARB_shader_precision
#endif /* GL_ARB_shader_precision */
#ifdef GL_ARB_shader_stencil_export
#endif /* GL_ARB_shader_stencil_export */
#ifdef GL_ARB_shader_storage_buffer_object
#endif /* GL_ARB_shader_storage_buffer_object */
#ifdef GL_ARB_shader_subroutine
#endif /* GL_ARB_shader_subroutine */
#ifdef GL_ARB_shader_texture_image_samples
#endif /* GL_ARB_shader_texture_image_samples */
#ifdef GL_ARB_shader_viewport_layer_array
#endif /* GL_ARB_shader_viewport_layer_array */
#ifdef GL_ARB_shading_language_420pack
#endif /* GL_ARB_shading_language_420pack */
#ifdef GL_ARB_shading_language_include
    PFNGLNAMEDSTRINGARBPROC glNamedStringARB = nullptr;
    PFNGLDELETENAMEDSTRINGARBPROC glDeleteNamedStringARB = nullptr;
    PFNGLCOMPILESHADERINCLUDEARBPROC glCompileShaderIncludeARB = nullptr;
    PFNGLISNAMEDSTRINGARBPROC glIsNamedStringARB = nullptr;
    PFNGLGETNAMEDSTRINGARBPROC glGetNamedStringARB = nullptr;
    PFNGLGETNAMEDSTRINGIVARBPROC glGetNamedStringivARB = nullptr;
#endif /* GL_ARB_shading_language_include */
#ifdef GL_ARB_shading_language_packing
#endif /* GL_ARB_shading_language_packing */
#ifdef GL_ARB_sparse_buffer
    PFNGLBUFFERPAGECOMMITMENTARBPROC glBufferPageCommitmentARB = nullptr;
    PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC glNamedBufferPageCommitmentEXT =
        nullptr;
    PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC glNamedBufferPageCommitmentARB =
        nullptr;
#endif /* GL_ARB_sparse_buffer */
#ifdef GL_ARB_sparse_texture
    PFNGLTEXPAGECOMMITMENTARBPROC glTexPageCommitmentARB = nullptr;
#endif /* GL_ARB_sparse_texture */
#ifdef GL_ARB_sparse_texture2
#endif /* GL_ARB_sparse_texture2 */
#ifdef GL_ARB_sparse_texture_clamp
#endif /* GL_ARB_sparse_texture_clamp */
#ifdef GL_ARB_spirv_extensions
#endif /* GL_ARB_spirv_extensions */
#ifdef GL_ARB_stencil_texturing
#endif /* GL_ARB_stencil_texturing */
#ifdef GL_ARB_sync
#endif /* GL_ARB_sync */
#ifdef GL_ARB_tessellation_shader
#endif /* GL_ARB_tessellation_shader */
#ifdef GL_ARB_texture_barrier
#endif /* GL_ARB_texture_barrier */
#ifdef GL_ARB_texture_border_clamp
#endif /* GL_ARB_texture_border_clamp */
#ifdef GL_ARB_texture_buffer_object
    PFNGLTEXBUFFERARBPROC glTexBufferARB = nullptr;
#endif /* GL_ARB_texture_buffer_object */
#ifdef GL_ARB_texture_buffer_object_rgb32
#endif /* GL_ARB_texture_buffer_object_rgb32 */
#ifdef GL_ARB_texture_buffer_range
#endif /* GL_ARB_texture_buffer_range */
#ifdef GL_ARB_texture_compression_bptc
#endif /* GL_ARB_texture_compression_bptc */
#ifdef GL_ARB_texture_compression_rgtc
#endif /* GL_ARB_texture_compression_rgtc */
#ifdef GL_ARB_texture_cube_map_array
#endif /* GL_ARB_texture_cube_map_array */
#ifdef GL_ARB_texture_filter_anisotropic
#endif /* GL_ARB_texture_filter_anisotropic */
#ifdef GL_ARB_texture_filter_minmax
#endif /* GL_ARB_texture_filter_minmax */
#ifdef GL_ARB_texture_gather
#endif /* GL_ARB_texture_gather */
#ifdef GL_ARB_texture_mirror_clamp_to_edge
#endif /* GL_ARB_texture_mirror_clamp_to_edge */
#ifdef GL_ARB_texture_mirrored_repeat
#endif /* GL_ARB_texture_mirrored_repeat */
#ifdef GL_ARB_texture_multisample
#endif /* GL_ARB_texture_multisample */
#ifdef GL_ARB_texture_non_power_of_two
#endif /* GL_ARB_texture_non_power_of_two */
#ifdef GL_ARB_texture_query_levels
#endif /* GL_ARB_texture_query_levels */
#ifdef GL_ARB_texture_query_lod
#endif /* GL_ARB_texture_query_lod */
#ifdef GL_ARB_texture_rg
#endif /* GL_ARB_texture_rg */
#ifdef GL_ARB_texture_rgb10_a2ui
#endif /* GL_ARB_texture_rgb10_a2ui */
#ifdef GL_ARB_texture_stencil8
#endif /* GL_ARB_texture_stencil8 */
#ifdef GL_ARB_texture_storage
#endif /* GL_ARB_texture_storage */
#ifdef GL_ARB_texture_storage_multisample
#endif /* GL_ARB_texture_storage_multisample */
#ifdef GL_ARB_texture_swizzle
#endif /* GL_ARB_texture_swizzle */
#ifdef GL_ARB_texture_view
#endif /* GL_ARB_texture_view */
#ifdef GL_ARB_timer_query
#endif /* GL_ARB_timer_query */
#ifdef GL_ARB_transform_feedback2
#endif /* GL_ARB_transform_feedback2 */
#ifdef GL_ARB_transform_feedback3
#endif /* GL_ARB_transform_feedback3 */
#ifdef GL_ARB_transform_feedback_instanced
#endif /* GL_ARB_transform_feedback_instanced */
#ifdef GL_ARB_transform_feedback_overflow_query
#endif /* GL_ARB_transform_feedback_overflow_query */
#ifdef GL_ARB_uniform_buffer_object
#endif /* GL_ARB_uniform_buffer_object */
#ifdef GL_ARB_vertex_array_bgra
#endif /* GL_ARB_vertex_array_bgra */
#ifdef GL_ARB_vertex_array_object
#endif /* GL_ARB_vertex_array_object */
#ifdef GL_ARB_vertex_attrib_64bit
#endif /* GL_ARB_vertex_attrib_64bit */
#ifdef GL_ARB_vertex_attrib_binding
#endif /* GL_ARB_vertex_attrib_binding */
#ifdef GL_ARB_vertex_type_10f_11f_11f_rev
#endif /* GL_ARB_vertex_type_10f_11f_11f_rev */
#ifdef GL_ARB_vertex_type_2_10_10_10_rev
#endif /* GL_ARB_vertex_type_2_10_10_10_rev */
#ifdef GL_ARB_viewport_array
    PFNGLDEPTHRANGEARRAYDVNVPROC glDepthRangeArraydvNV = nullptr;
    PFNGLDEPTHRANGEINDEXEDDNVPROC glDepthRangeIndexeddNV = nullptr;
#endif /* GL_ARB_viewport_array */
#ifdef GL_KHR_blend_equation_advanced
    PFNGLBLENDBARRIERKHRPROC glBlendBarrierKHR = nullptr;
#endif /* GL_KHR_blend_equation_advanced */
#ifdef GL_KHR_blend_equation_advanced_coherent
#endif /* GL_KHR_blend_equation_advanced_coherent */
#ifdef GL_KHR_context_flush_control
#endif /* GL_KHR_context_flush_control */
#ifdef GL_KHR_debug
#endif /* GL_KHR_debug */
#ifdef GL_KHR_no_error
#endif /* GL_KHR_no_error */
#ifdef GL_KHR_parallel_shader_compile
    PFNGLMAXSHADERCOMPILERTHREADSKHRPROC glMaxShaderCompilerThreadsKHR =
        nullptr;
#endif /* GL_KHR_parallel_shader_compile */
#ifdef GL_KHR_robust_buffer_access_behavior
#endif /* GL_KHR_robust_buffer_access_behavior */
#ifdef GL_KHR_robustness
#endif /* GL_KHR_robustness */
#ifdef GL_KHR_shader_subgroup
#endif /* GL_KHR_shader_subgroup */
#ifdef GL_KHR_texture_compression_astc_hdr
#endif /* GL_KHR_texture_compression_astc_hdr */
#ifdef GL_KHR_texture_compression_astc_ldr
#endif /* GL_KHR_texture_compression_astc_ldr */
#ifdef GL_KHR_texture_compression_astc_sliced_3d
#endif /* GL_KHR_texture_compression_astc_sliced_3d */
#ifdef GL_AMD_framebuffer_multisample_advanced
    PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC
    glRenderbufferStorageMultisampleAdvancedAMD = nullptr;
    PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC
    glNamedRenderbufferStorageMultisampleAdvancedAMD = nullptr;
#endif /* GL_AMD_framebuffer_multisample_advanced */
#ifdef GL_AMD_performance_monitor
    PFNGLGETPERFMONITORGROUPSAMDPROC glGetPerfMonitorGroupsAMD = nullptr;
    PFNGLGETPERFMONITORCOUNTERSAMDPROC glGetPerfMonitorCountersAMD = nullptr;
    PFNGLGETPERFMONITORGROUPSTRINGAMDPROC glGetPerfMonitorGroupStringAMD =
        nullptr;
    PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC glGetPerfMonitorCounterStringAMD =
        nullptr;
    PFNGLGETPERFMONITORCOUNTERINFOAMDPROC glGetPerfMonitorCounterInfoAMD =
        nullptr;
    PFNGLGENPERFMONITORSAMDPROC glGenPerfMonitorsAMD = nullptr;
    PFNGLDELETEPERFMONITORSAMDPROC glDeletePerfMonitorsAMD = nullptr;
    PFNGLSELECTPERFMONITORCOUNTERSAMDPROC glSelectPerfMonitorCountersAMD =
        nullptr;
    PFNGLBEGINPERFMONITORAMDPROC glBeginPerfMonitorAMD = nullptr;
    PFNGLENDPERFMONITORAMDPROC glEndPerfMonitorAMD = nullptr;
    PFNGLGETPERFMONITORCOUNTERDATAAMDPROC glGetPerfMonitorCounterDataAMD =
        nullptr;
#endif /* GL_AMD_performance_monitor */
#ifdef GL_APPLE_rgb_422
#endif /* GL_APPLE_rgb_422 */
#ifdef GL_EXT_EGL_image_storage
    PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC glEGLImageTargetTexStorageEXT =
        nullptr;
    PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC glEGLImageTargetTextureStorageEXT =
        nullptr;
#endif /* GL_EXT_EGL_image_storage */
#ifdef GL_EXT_EGL_sync
#endif /* GL_EXT_EGL_sync */
#ifdef GL_EXT_debug_label
    PFNGLLABELOBJECTEXTPROC glLabelObjectEXT = nullptr;
    PFNGLGETOBJECTLABELEXTPROC glGetObjectLabelEXT = nullptr;
#endif /* GL_EXT_debug_label */
#ifdef GL_EXT_debug_marker
    PFNGLINSERTEVENTMARKEREXTPROC glInsertEventMarkerEXT = nullptr;
    PFNGLPUSHGROUPMARKEREXTPROC glPushGroupMarkerEXT = nullptr;
    PFNGLPOPGROUPMARKEREXTPROC glPopGroupMarkerEXT = nullptr;
#endif /* GL_EXT_debug_marker */
#ifdef GL_EXT_direct_state_access
    PFNGLMATRIXLOADFEXTPROC glMatrixLoadfEXT = nullptr;
    PFNGLMATRIXLOADDEXTPROC glMatrixLoaddEXT = nullptr;
    PFNGLMATRIXMULTFEXTPROC glMatrixMultfEXT = nullptr;
    PFNGLMATRIXMULTDEXTPROC glMatrixMultdEXT = nullptr;
    PFNGLMATRIXLOADIDENTITYEXTPROC glMatrixLoadIdentityEXT = nullptr;
    PFNGLMATRIXROTATEFEXTPROC glMatrixRotatefEXT = nullptr;
    PFNGLMATRIXROTATEDEXTPROC glMatrixRotatedEXT = nullptr;
    PFNGLMATRIXSCALEFEXTPROC glMatrixScalefEXT = nullptr;
    PFNGLMATRIXSCALEDEXTPROC glMatrixScaledEXT = nullptr;
    PFNGLMATRIXTRANSLATEFEXTPROC glMatrixTranslatefEXT = nullptr;
    PFNGLMATRIXTRANSLATEDEXTPROC glMatrixTranslatedEXT = nullptr;
    PFNGLMATRIXFRUSTUMEXTPROC glMatrixFrustumEXT = nullptr;
    PFNGLMATRIXORTHOEXTPROC glMatrixOrthoEXT = nullptr;
    PFNGLMATRIXPOPEXTPROC glMatrixPopEXT = nullptr;
    PFNGLMATRIXPUSHEXTPROC glMatrixPushEXT = nullptr;
    PFNGLCLIENTATTRIBDEFAULTEXTPROC glClientAttribDefaultEXT = nullptr;
    PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC glPushClientAttribDefaultEXT = nullptr;
    PFNGLTEXTUREPARAMETERFEXTPROC glTextureParameterfEXT = nullptr;
    PFNGLTEXTUREPARAMETERFVEXTPROC glTextureParameterfvEXT = nullptr;
    PFNGLTEXTUREPARAMETERIEXTPROC glTextureParameteriEXT = nullptr;
    PFNGLTEXTUREPARAMETERIVEXTPROC glTextureParameterivEXT = nullptr;
    PFNGLTEXTUREIMAGE1DEXTPROC glTextureImage1DEXT = nullptr;
    PFNGLTEXTUREIMAGE2DEXTPROC glTextureImage2DEXT = nullptr;
    PFNGLTEXTURESUBIMAGE1DEXTPROC glTextureSubImage1DEXT = nullptr;
    PFNGLTEXTURESUBIMAGE2DEXTPROC glTextureSubImage2DEXT = nullptr;
    PFNGLCOPYTEXTUREIMAGE1DEXTPROC glCopyTextureImage1DEXT = nullptr;
    PFNGLCOPYTEXTUREIMAGE2DEXTPROC glCopyTextureImage2DEXT = nullptr;
    PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC glCopyTextureSubImage1DEXT = nullptr;
    PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC glCopyTextureSubImage2DEXT = nullptr;
    PFNGLGETTEXTUREIMAGEEXTPROC glGetTextureImageEXT = nullptr;
    PFNGLGETTEXTUREPARAMETERFVEXTPROC glGetTextureParameterfvEXT = nullptr;
    PFNGLGETTEXTUREPARAMETERIVEXTPROC glGetTextureParameterivEXT = nullptr;
    PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC glGetTextureLevelParameterfvEXT =
        nullptr;
    PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC glGetTextureLevelParameterivEXT =
        nullptr;
    PFNGLTEXTUREIMAGE3DEXTPROC glTextureImage3DEXT = nullptr;
    PFNGLTEXTURESUBIMAGE3DEXTPROC glTextureSubImage3DEXT = nullptr;
    PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC glCopyTextureSubImage3DEXT = nullptr;
    PFNGLBINDMULTITEXTUREEXTPROC glBindMultiTextureEXT = nullptr;
    PFNGLMULTITEXCOORDPOINTEREXTPROC glMultiTexCoordPointerEXT = nullptr;
    PFNGLMULTITEXENVFEXTPROC glMultiTexEnvfEXT = nullptr;
    PFNGLMULTITEXENVFVEXTPROC glMultiTexEnvfvEXT = nullptr;
    PFNGLMULTITEXENVIEXTPROC glMultiTexEnviEXT = nullptr;
    PFNGLMULTITEXENVIVEXTPROC glMultiTexEnvivEXT = nullptr;
    PFNGLMULTITEXGENDEXTPROC glMultiTexGendEXT = nullptr;
    PFNGLMULTITEXGENDVEXTPROC glMultiTexGendvEXT = nullptr;
    PFNGLMULTITEXGENFEXTPROC glMultiTexGenfEXT = nullptr;
    PFNGLMULTITEXGENFVEXTPROC glMultiTexGenfvEXT = nullptr;
    PFNGLMULTITEXGENIEXTPROC glMultiTexGeniEXT = nullptr;
    PFNGLMULTITEXGENIVEXTPROC glMultiTexGenivEXT = nullptr;
    PFNGLGETMULTITEXENVFVEXTPROC glGetMultiTexEnvfvEXT = nullptr;
    PFNGLGETMULTITEXENVIVEXTPROC glGetMultiTexEnvivEXT = nullptr;
    PFNGLGETMULTITEXGENDVEXTPROC glGetMultiTexGendvEXT = nullptr;
    PFNGLGETMULTITEXGENFVEXTPROC glGetMultiTexGenfvEXT = nullptr;
    PFNGLGETMULTITEXGENIVEXTPROC glGetMultiTexGenivEXT = nullptr;
    PFNGLMULTITEXPARAMETERIEXTPROC glMultiTexParameteriEXT = nullptr;
    PFNGLMULTITEXPARAMETERIVEXTPROC glMultiTexParameterivEXT = nullptr;
    PFNGLMULTITEXPARAMETERFEXTPROC glMultiTexParameterfEXT = nullptr;
    PFNGLMULTITEXPARAMETERFVEXTPROC glMultiTexParameterfvEXT = nullptr;
    PFNGLMULTITEXIMAGE1DEXTPROC glMultiTexImage1DEXT = nullptr;
    PFNGLMULTITEXIMAGE2DEXTPROC glMultiTexImage2DEXT = nullptr;
    PFNGLMULTITEXSUBIMAGE1DEXTPROC glMultiTexSubImage1DEXT = nullptr;
    PFNGLMULTITEXSUBIMAGE2DEXTPROC glMultiTexSubImage2DEXT = nullptr;
    PFNGLCOPYMULTITEXIMAGE1DEXTPROC glCopyMultiTexImage1DEXT = nullptr;
    PFNGLCOPYMULTITEXIMAGE2DEXTPROC glCopyMultiTexImage2DEXT = nullptr;
    PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC glCopyMultiTexSubImage1DEXT = nullptr;
    PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC glCopyMultiTexSubImage2DEXT = nullptr;
    PFNGLGETMULTITEXIMAGEEXTPROC glGetMultiTexImageEXT = nullptr;
    PFNGLGETMULTITEXPARAMETERFVEXTPROC glGetMultiTexParameterfvEXT = nullptr;
    PFNGLGETMULTITEXPARAMETERIVEXTPROC glGetMultiTexParameterivEXT = nullptr;
    PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC glGetMultiTexLevelParameterfvEXT =
        nullptr;
    PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC glGetMultiTexLevelParameterivEXT =
        nullptr;
    PFNGLMULTITEXIMAGE3DEXTPROC glMultiTexImage3DEXT = nullptr;
    PFNGLMULTITEXSUBIMAGE3DEXTPROC glMultiTexSubImage3DEXT = nullptr;
    PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC glCopyMultiTexSubImage3DEXT = nullptr;
    PFNGLENABLECLIENTSTATEINDEXEDEXTPROC glEnableClientStateIndexedEXT =
        nullptr;
    PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC glDisableClientStateIndexedEXT =
        nullptr;
    PFNGLGETFLOATINDEXEDVEXTPROC glGetFloatIndexedvEXT = nullptr;
    PFNGLGETDOUBLEINDEXEDVEXTPROC glGetDoubleIndexedvEXT = nullptr;
    PFNGLGETPOINTERINDEXEDVEXTPROC glGetPointerIndexedvEXT = nullptr;
    PFNGLENABLEINDEXEDEXTPROC glEnableIndexedEXT = nullptr;
    PFNGLDISABLEINDEXEDEXTPROC glDisableIndexedEXT = nullptr;
    PFNGLISENABLEDINDEXEDEXTPROC glIsEnabledIndexedEXT = nullptr;
    PFNGLGETINTEGERINDEXEDVEXTPROC glGetIntegerIndexedvEXT = nullptr;
    PFNGLGETBOOLEANINDEXEDVEXTPROC glGetBooleanIndexedvEXT = nullptr;
    PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC glCompressedTextureImage3DEXT =
        nullptr;
    PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC glCompressedTextureImage2DEXT =
        nullptr;
    PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC glCompressedTextureImage1DEXT =
        nullptr;
    PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC glCompressedTextureSubImage3DEXT =
        nullptr;
    PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC glCompressedTextureSubImage2DEXT =
        nullptr;
    PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC glCompressedTextureSubImage1DEXT =
        nullptr;
    PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC glGetCompressedTextureImageEXT =
        nullptr;
    PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC glCompressedMultiTexImage3DEXT =
        nullptr;
    PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC glCompressedMultiTexImage2DEXT =
        nullptr;
    PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC glCompressedMultiTexImage1DEXT =
        nullptr;
    PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC glCompressedMultiTexSubImage3DEXT =
        nullptr;
    PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC glCompressedMultiTexSubImage2DEXT =
        nullptr;
    PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC glCompressedMultiTexSubImage1DEXT =
        nullptr;
    PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC glGetCompressedMultiTexImageEXT =
        nullptr;
    PFNGLMATRIXLOADTRANSPOSEFEXTPROC glMatrixLoadTransposefEXT = nullptr;
    PFNGLMATRIXLOADTRANSPOSEDEXTPROC glMatrixLoadTransposedEXT = nullptr;
    PFNGLMATRIXMULTTRANSPOSEFEXTPROC glMatrixMultTransposefEXT = nullptr;
    PFNGLMATRIXMULTTRANSPOSEDEXTPROC glMatrixMultTransposedEXT = nullptr;
    PFNGLNAMEDBUFFERDATAEXTPROC glNamedBufferDataEXT = nullptr;
    PFNGLNAMEDBUFFERSUBDATAEXTPROC glNamedBufferSubDataEXT = nullptr;
    PFNGLMAPNAMEDBUFFEREXTPROC glMapNamedBufferEXT = nullptr;
    PFNGLUNMAPNAMEDBUFFEREXTPROC glUnmapNamedBufferEXT = nullptr;
    PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC glGetNamedBufferParameterivEXT =
        nullptr;
    PFNGLGETNAMEDBUFFERPOINTERVEXTPROC glGetNamedBufferPointervEXT = nullptr;
    PFNGLGETNAMEDBUFFERSUBDATAEXTPROC glGetNamedBufferSubDataEXT = nullptr;
    PFNGLPROGRAMUNIFORM1FEXTPROC glProgramUniform1fEXT = nullptr;
    PFNGLPROGRAMUNIFORM2FEXTPROC glProgramUniform2fEXT = nullptr;
    PFNGLPROGRAMUNIFORM3FEXTPROC glProgramUniform3fEXT = nullptr;
    PFNGLPROGRAMUNIFORM4FEXTPROC glProgramUniform4fEXT = nullptr;
    PFNGLPROGRAMUNIFORM1IEXTPROC glProgramUniform1iEXT = nullptr;
    PFNGLPROGRAMUNIFORM2IEXTPROC glProgramUniform2iEXT = nullptr;
    PFNGLPROGRAMUNIFORM3IEXTPROC glProgramUniform3iEXT = nullptr;
    PFNGLPROGRAMUNIFORM4IEXTPROC glProgramUniform4iEXT = nullptr;
    PFNGLPROGRAMUNIFORM1FVEXTPROC glProgramUniform1fvEXT = nullptr;
    PFNGLPROGRAMUNIFORM2FVEXTPROC glProgramUniform2fvEXT = nullptr;
    PFNGLPROGRAMUNIFORM3FVEXTPROC glProgramUniform3fvEXT = nullptr;
    PFNGLPROGRAMUNIFORM4FVEXTPROC glProgramUniform4fvEXT = nullptr;
    PFNGLPROGRAMUNIFORM1IVEXTPROC glProgramUniform1ivEXT = nullptr;
    PFNGLPROGRAMUNIFORM2IVEXTPROC glProgramUniform2ivEXT = nullptr;
    PFNGLPROGRAMUNIFORM3IVEXTPROC glProgramUniform3ivEXT = nullptr;
    PFNGLPROGRAMUNIFORM4IVEXTPROC glProgramUniform4ivEXT = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC glProgramUniformMatrix2fvEXT = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC glProgramUniformMatrix3fvEXT = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC glProgramUniformMatrix4fvEXT = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC glProgramUniformMatrix2x3fvEXT =
        nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC glProgramUniformMatrix3x2fvEXT =
        nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC glProgramUniformMatrix2x4fvEXT =
        nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC glProgramUniformMatrix4x2fvEXT =
        nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC glProgramUniformMatrix3x4fvEXT =
        nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC glProgramUniformMatrix4x3fvEXT =
        nullptr;
    PFNGLTEXTUREBUFFEREXTPROC glTextureBufferEXT = nullptr;
    PFNGLMULTITEXBUFFEREXTPROC glMultiTexBufferEXT = nullptr;
    PFNGLTEXTUREPARAMETERIIVEXTPROC glTextureParameterIivEXT = nullptr;
    PFNGLTEXTUREPARAMETERIUIVEXTPROC glTextureParameterIuivEXT = nullptr;
    PFNGLGETTEXTUREPARAMETERIIVEXTPROC glGetTextureParameterIivEXT = nullptr;
    PFNGLGETTEXTUREPARAMETERIUIVEXTPROC glGetTextureParameterIuivEXT = nullptr;
    PFNGLMULTITEXPARAMETERIIVEXTPROC glMultiTexParameterIivEXT = nullptr;
    PFNGLMULTITEXPARAMETERIUIVEXTPROC glMultiTexParameterIuivEXT = nullptr;
    PFNGLGETMULTITEXPARAMETERIIVEXTPROC glGetMultiTexParameterIivEXT = nullptr;
    PFNGLGETMULTITEXPARAMETERIUIVEXTPROC glGetMultiTexParameterIuivEXT =
        nullptr;
    PFNGLPROGRAMUNIFORM1UIEXTPROC glProgramUniform1uiEXT = nullptr;
    PFNGLPROGRAMUNIFORM2UIEXTPROC glProgramUniform2uiEXT = nullptr;
    PFNGLPROGRAMUNIFORM3UIEXTPROC glProgramUniform3uiEXT = nullptr;
    PFNGLPROGRAMUNIFORM4UIEXTPROC glProgramUniform4uiEXT = nullptr;
    PFNGLPROGRAMUNIFORM1UIVEXTPROC glProgramUniform1uivEXT = nullptr;
    PFNGLPROGRAMUNIFORM2UIVEXTPROC glProgramUniform2uivEXT = nullptr;
    PFNGLPROGRAMUNIFORM3UIVEXTPROC glProgramUniform3uivEXT = nullptr;
    PFNGLPROGRAMUNIFORM4UIVEXTPROC glProgramUniform4uivEXT = nullptr;
    PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC
    glNamedProgramLocalParameters4fvEXT = nullptr;
    PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC
    glNamedProgramLocalParameterI4iEXT = nullptr;
    PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC
    glNamedProgramLocalParameterI4ivEXT = nullptr;
    PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC
    glNamedProgramLocalParametersI4ivEXT = nullptr;
    PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC
    glNamedProgramLocalParameterI4uiEXT = nullptr;
    PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC
    glNamedProgramLocalParameterI4uivEXT = nullptr;
    PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC
    glNamedProgramLocalParametersI4uivEXT = nullptr;
    PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC
    glGetNamedProgramLocalParameterIivEXT = nullptr;
    PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC
    glGetNamedProgramLocalParameterIuivEXT = nullptr;
    PFNGLENABLECLIENTSTATEIEXTPROC glEnableClientStateiEXT = nullptr;
    PFNGLDISABLECLIENTSTATEIEXTPROC glDisableClientStateiEXT = nullptr;
    PFNGLGETFLOATI_VEXTPROC glGetFloati_vEXT = nullptr;
    PFNGLGETDOUBLEI_VEXTPROC glGetDoublei_vEXT = nullptr;
    PFNGLGETPOINTERI_VEXTPROC glGetPointeri_vEXT = nullptr;
    PFNGLNAMEDPROGRAMSTRINGEXTPROC glNamedProgramStringEXT = nullptr;
    PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC glNamedProgramLocalParameter4dEXT =
        nullptr;
    PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC
    glNamedProgramLocalParameter4dvEXT = nullptr;
    PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC glNamedProgramLocalParameter4fEXT =
        nullptr;
    PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC
    glNamedProgramLocalParameter4fvEXT = nullptr;
    PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC
    glGetNamedProgramLocalParameterdvEXT = nullptr;
    PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC
    glGetNamedProgramLocalParameterfvEXT = nullptr;
    PFNGLGETNAMEDPROGRAMIVEXTPROC glGetNamedProgramivEXT = nullptr;
    PFNGLGETNAMEDPROGRAMSTRINGEXTPROC glGetNamedProgramStringEXT = nullptr;
    PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC glNamedRenderbufferStorageEXT =
        nullptr;
    PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC
    glGetNamedRenderbufferParameterivEXT = nullptr;
    PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC
    glNamedRenderbufferStorageMultisampleEXT = nullptr;
    PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC
    glNamedRenderbufferStorageMultisampleCoverageEXT = nullptr;
    PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC glCheckNamedFramebufferStatusEXT =
        nullptr;
    PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC glNamedFramebufferTexture1DEXT =
        nullptr;
    PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC glNamedFramebufferTexture2DEXT =
        nullptr;
    PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC glNamedFramebufferTexture3DEXT =
        nullptr;
    PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC glNamedFramebufferRenderbufferEXT =
        nullptr;
    PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC
    glGetNamedFramebufferAttachmentParameterivEXT = nullptr;
    PFNGLGENERATETEXTUREMIPMAPEXTPROC glGenerateTextureMipmapEXT = nullptr;
    PFNGLGENERATEMULTITEXMIPMAPEXTPROC glGenerateMultiTexMipmapEXT = nullptr;
    PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC glFramebufferDrawBufferEXT = nullptr;
    PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC glFramebufferDrawBuffersEXT = nullptr;
    PFNGLFRAMEBUFFERREADBUFFEREXTPROC glFramebufferReadBufferEXT = nullptr;
    PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC glGetFramebufferParameterivEXT =
        nullptr;
    PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC glNamedCopyBufferSubDataEXT = nullptr;
    PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC glNamedFramebufferTextureEXT = nullptr;
    PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC glNamedFramebufferTextureLayerEXT =
        nullptr;
    PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC glNamedFramebufferTextureFaceEXT =
        nullptr;
    PFNGLTEXTURERENDERBUFFEREXTPROC glTextureRenderbufferEXT = nullptr;
    PFNGLMULTITEXRENDERBUFFEREXTPROC glMultiTexRenderbufferEXT = nullptr;
    PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC glVertexArrayVertexOffsetEXT = nullptr;
    PFNGLVERTEXARRAYCOLOROFFSETEXTPROC glVertexArrayColorOffsetEXT = nullptr;
    PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC glVertexArrayEdgeFlagOffsetEXT =
        nullptr;
    PFNGLVERTEXARRAYINDEXOFFSETEXTPROC glVertexArrayIndexOffsetEXT = nullptr;
    PFNGLVERTEXARRAYNORMALOFFSETEXTPROC glVertexArrayNormalOffsetEXT = nullptr;
    PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC glVertexArrayTexCoordOffsetEXT =
        nullptr;
    PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC
    glVertexArrayMultiTexCoordOffsetEXT = nullptr;
    PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC glVertexArrayFogCoordOffsetEXT =
        nullptr;
    PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC
    glVertexArraySecondaryColorOffsetEXT = nullptr;
    PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC
    glVertexArrayVertexAttribOffsetEXT = nullptr;
    PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC
    glVertexArrayVertexAttribIOffsetEXT = nullptr;
    PFNGLENABLEVERTEXARRAYEXTPROC glEnableVertexArrayEXT = nullptr;
    PFNGLDISABLEVERTEXARRAYEXTPROC glDisableVertexArrayEXT = nullptr;
    PFNGLENABLEVERTEXARRAYATTRIBEXTPROC glEnableVertexArrayAttribEXT = nullptr;
    PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC glDisableVertexArrayAttribEXT =
        nullptr;
    PFNGLGETVERTEXARRAYINTEGERVEXTPROC glGetVertexArrayIntegervEXT = nullptr;
    PFNGLGETVERTEXARRAYPOINTERVEXTPROC glGetVertexArrayPointervEXT = nullptr;
    PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC glGetVertexArrayIntegeri_vEXT =
        nullptr;
    PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC glGetVertexArrayPointeri_vEXT =
        nullptr;
    PFNGLMAPNAMEDBUFFERRANGEEXTPROC glMapNamedBufferRangeEXT = nullptr;
    PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC glFlushMappedNamedBufferRangeEXT =
        nullptr;
    PFNGLNAMEDBUFFERSTORAGEEXTPROC glNamedBufferStorageEXT = nullptr;
    PFNGLCLEARNAMEDBUFFERDATAEXTPROC glClearNamedBufferDataEXT = nullptr;
    PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC glClearNamedBufferSubDataEXT = nullptr;
    PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC glNamedFramebufferParameteriEXT =
        nullptr;
    PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC
    glGetNamedFramebufferParameterivEXT = nullptr;
    PFNGLPROGRAMUNIFORM1DEXTPROC glProgramUniform1dEXT = nullptr;
    PFNGLPROGRAMUNIFORM2DEXTPROC glProgramUniform2dEXT = nullptr;
    PFNGLPROGRAMUNIFORM3DEXTPROC glProgramUniform3dEXT = nullptr;
    PFNGLPROGRAMUNIFORM4DEXTPROC glProgramUniform4dEXT = nullptr;
    PFNGLPROGRAMUNIFORM1DVEXTPROC glProgramUniform1dvEXT = nullptr;
    PFNGLPROGRAMUNIFORM2DVEXTPROC glProgramUniform2dvEXT = nullptr;
    PFNGLPROGRAMUNIFORM3DVEXTPROC glProgramUniform3dvEXT = nullptr;
    PFNGLPROGRAMUNIFORM4DVEXTPROC glProgramUniform4dvEXT = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC glProgramUniformMatrix2dvEXT = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC glProgramUniformMatrix3dvEXT = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC glProgramUniformMatrix4dvEXT = nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC glProgramUniformMatrix2x3dvEXT =
        nullptr;
    PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC glProgramUniformMatrix2x4dvEXT =
        nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC glProgramUniformMatrix3x2dvEXT =
        nullptr;
    PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC glProgramUniformMatrix3x4dvEXT =
        nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC glProgramUniformMatrix4x2dvEXT =
        nullptr;
    PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC glProgramUniformMatrix4x3dvEXT =
        nullptr;
    PFNGLTEXTUREBUFFERRANGEEXTPROC glTextureBufferRangeEXT = nullptr;
    PFNGLTEXTURESTORAGE1DEXTPROC glTextureStorage1DEXT = nullptr;
    PFNGLTEXTURESTORAGE2DEXTPROC glTextureStorage2DEXT = nullptr;
    PFNGLTEXTURESTORAGE3DEXTPROC glTextureStorage3DEXT = nullptr;
    PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC glTextureStorage2DMultisampleEXT =
        nullptr;
    PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC glTextureStorage3DMultisampleEXT =
        nullptr;
    PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC glVertexArrayBindVertexBufferEXT =
        nullptr;
    PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC
    glVertexArrayVertexAttribFormatEXT = nullptr;
    PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC
    glVertexArrayVertexAttribIFormatEXT = nullptr;
    PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC
    glVertexArrayVertexAttribLFormatEXT = nullptr;
    PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC
    glVertexArrayVertexAttribBindingEXT = nullptr;
    PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC
    glVertexArrayVertexBindingDivisorEXT = nullptr;
    PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC
    glVertexArrayVertexAttribLOffsetEXT = nullptr;
    PFNGLTEXTUREPAGECOMMITMENTEXTPROC glTexturePageCommitmentEXT = nullptr;
    PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC
    glVertexArrayVertexAttribDivisorEXT = nullptr;
#endif /* GL_EXT_direct_state_access */
#ifdef GL_EXT_draw_instanced
    PFNGLDRAWARRAYSINSTANCEDEXTPROC glDrawArraysInstancedEXT = nullptr;
    PFNGLDRAWELEMENTSINSTANCEDEXTPROC glDrawElementsInstancedEXT = nullptr;
#endif /* GL_EXT_draw_instanced */
#ifdef GL_EXT_multiview_tessellation_geometry_shader
#endif /* GL_EXT_multiview_tessellation_geometry_shader */
#ifdef GL_EXT_multiview_texture_multisample
#endif /* GL_EXT_multiview_texture_multisample */
#ifdef GL_EXT_multiview_timer_query
#endif /* GL_EXT_multiview_timer_query */
#ifdef GL_EXT_polygon_offset_clamp
    PFNGLPOLYGONOFFSETCLAMPEXTPROC glPolygonOffsetClampEXT = nullptr;
#endif /* GL_EXT_polygon_offset_clamp */
#ifdef GL_EXT_post_depth_coverage
#endif /* GL_EXT_post_depth_coverage */
#ifdef GL_EXT_raster_multisample
    PFNGLRASTERSAMPLESEXTPROC glRasterSamplesEXT = nullptr;
#endif /* GL_EXT_raster_multisample */
#ifdef GL_EXT_separate_shader_objects
    PFNGLUSESHADERPROGRAMEXTPROC glUseShaderProgramEXT = nullptr;
    PFNGLACTIVEPROGRAMEXTPROC glActiveProgramEXT = nullptr;
    PFNGLCREATESHADERPROGRAMEXTPROC glCreateShaderProgramEXT = nullptr;
#endif /* GL_EXT_separate_shader_objects */
#ifdef GL_EXT_shader_framebuffer_fetch
#endif /* GL_EXT_shader_framebuffer_fetch */
#ifdef GL_EXT_shader_framebuffer_fetch_non_coherent
    PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC glFramebufferFetchBarrierEXT = nullptr;
#endif /* GL_EXT_shader_framebuffer_fetch_non_coherent */
#ifdef GL_EXT_shader_integer_mix
#endif /* GL_EXT_shader_integer_mix */
#ifdef GL_EXT_texture_compression_s3tc
#endif /* GL_EXT_texture_compression_s3tc */
#ifdef GL_EXT_texture_filter_minmax
#endif /* GL_EXT_texture_filter_minmax */
#ifdef GL_EXT_texture_sRGB_R8
#endif /* GL_EXT_texture_sRGB_R8 */
#ifdef GL_EXT_texture_sRGB_decode
#endif /* GL_EXT_texture_sRGB_decode */
#ifdef GL_EXT_texture_shadow_lod
#endif /* GL_EXT_texture_shadow_lod */
#ifdef GL_EXT_window_rectangles
    PFNGLWINDOWRECTANGLESEXTPROC glWindowRectanglesEXT = nullptr;
#endif /* GL_EXT_window_rectangles */
#ifdef GL_INTEL_blackhole_render
#endif /* GL_INTEL_blackhole_render */
#ifdef GL_INTEL_conservative_rasterization
#endif /* GL_INTEL_conservative_rasterization */
#ifdef GL_INTEL_framebuffer_CMAA
    PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC
    glApplyFramebufferAttachmentCMAAINTEL = nullptr;
#endif /* GL_INTEL_framebuffer_CMAA */
#ifdef GL_INTEL_performance_query
    PFNGLBEGINPERFQUERYINTELPROC glBeginPerfQueryINTEL = nullptr;
    PFNGLCREATEPERFQUERYINTELPROC glCreatePerfQueryINTEL = nullptr;
    PFNGLDELETEPERFQUERYINTELPROC glDeletePerfQueryINTEL = nullptr;
    PFNGLENDPERFQUERYINTELPROC glEndPerfQueryINTEL = nullptr;
    PFNGLGETFIRSTPERFQUERYIDINTELPROC glGetFirstPerfQueryIdINTEL = nullptr;
    PFNGLGETNEXTPERFQUERYIDINTELPROC glGetNextPerfQueryIdINTEL = nullptr;
    PFNGLGETPERFCOUNTERINFOINTELPROC glGetPerfCounterInfoINTEL = nullptr;
    PFNGLGETPERFQUERYDATAINTELPROC glGetPerfQueryDataINTEL = nullptr;
    PFNGLGETPERFQUERYIDBYNAMEINTELPROC glGetPerfQueryIdByNameINTEL = nullptr;
    PFNGLGETPERFQUERYINFOINTELPROC glGetPerfQueryInfoINTEL = nullptr;
#endif /* GL_INTEL_performance_query */
#ifdef GL_MESA_framebuffer_flip_x
#endif /* GL_MESA_framebuffer_flip_x */
#ifdef GL_MESA_framebuffer_flip_y
    PFNGLFRAMEBUFFERPARAMETERIMESAPROC glFramebufferParameteriMESA = nullptr;
    PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC glGetFramebufferParameterivMESA =
        nullptr;
#endif /* GL_MESA_framebuffer_flip_y */
#ifdef GL_MESA_framebuffer_swap_xy
#endif /* GL_MESA_framebuffer_swap_xy */
#ifdef GL_NV_bindless_multi_draw_indirect
    PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC
    glMultiDrawArraysIndirectBindlessNV = nullptr;
    PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC
    glMultiDrawElementsIndirectBindlessNV = nullptr;
#endif /* GL_NV_bindless_multi_draw_indirect */
#ifdef GL_NV_bindless_multi_draw_indirect_count
    PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC
    glMultiDrawArraysIndirectBindlessCountNV = nullptr;
    PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC
    glMultiDrawElementsIndirectBindlessCountNV = nullptr;
#endif /* GL_NV_bindless_multi_draw_indirect_count */
#ifdef GL_NV_bindless_texture
    PFNGLGETTEXTUREHANDLENVPROC glGetTextureHandleNV = nullptr;
    PFNGLGETTEXTURESAMPLERHANDLENVPROC glGetTextureSamplerHandleNV = nullptr;
    PFNGLMAKETEXTUREHANDLERESIDENTNVPROC glMakeTextureHandleResidentNV =
        nullptr;
    PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC glMakeTextureHandleNonResidentNV =
        nullptr;
    PFNGLGETIMAGEHANDLENVPROC glGetImageHandleNV = nullptr;
    PFNGLMAKEIMAGEHANDLERESIDENTNVPROC glMakeImageHandleResidentNV = nullptr;
    PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC glMakeImageHandleNonResidentNV =
        nullptr;
    PFNGLUNIFORMHANDLEUI64NVPROC glUniformHandleui64NV = nullptr;
    PFNGLUNIFORMHANDLEUI64VNVPROC glUniformHandleui64vNV = nullptr;
    PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC glProgramUniformHandleui64NV = nullptr;
    PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC glProgramUniformHandleui64vNV =
        nullptr;
    PFNGLISTEXTUREHANDLERESIDENTNVPROC glIsTextureHandleResidentNV = nullptr;
    PFNGLISIMAGEHANDLERESIDENTNVPROC glIsImageHandleResidentNV = nullptr;
#endif /* GL_NV_bindless_texture */
#ifdef GL_NV_blend_equation_advanced
    PFNGLBLENDPARAMETERINVPROC glBlendParameteriNV = nullptr;
    PFNGLBLENDBARRIERNVPROC glBlendBarrierNV = nullptr;
#endif /* GL_NV_blend_equation_advanced */
#ifdef GL_NV_blend_equation_advanced_coherent
#endif /* GL_NV_blend_equation_advanced_coherent */
#ifdef GL_NV_blend_minmax_factor
#endif /* GL_NV_blend_minmax_factor */
#ifdef GL_NV_clip_space_w_scaling
    PFNGLVIEWPORTPOSITIONWSCALENVPROC glViewportPositionWScaleNV = nullptr;
#endif /* GL_NV_clip_space_w_scaling */
#ifdef GL_NV_command_list
    PFNGLCREATESTATESNVPROC glCreateStatesNV = nullptr;
    PFNGLDELETESTATESNVPROC glDeleteStatesNV = nullptr;
    PFNGLISSTATENVPROC glIsStateNV = nullptr;
    PFNGLSTATECAPTURENVPROC glStateCaptureNV = nullptr;
    PFNGLGETCOMMANDHEADERNVPROC glGetCommandHeaderNV = nullptr;
    PFNGLGETSTAGEINDEXNVPROC glGetStageIndexNV = nullptr;
    PFNGLDRAWCOMMANDSNVPROC glDrawCommandsNV = nullptr;
    PFNGLDRAWCOMMANDSADDRESSNVPROC glDrawCommandsAddressNV = nullptr;
    PFNGLDRAWCOMMANDSSTATESNVPROC glDrawCommandsStatesNV = nullptr;
    PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC glDrawCommandsStatesAddressNV =
        nullptr;
    PFNGLCREATECOMMANDLISTSNVPROC glCreateCommandListsNV = nullptr;
    PFNGLDELETECOMMANDLISTSNVPROC glDeleteCommandListsNV = nullptr;
    PFNGLISCOMMANDLISTNVPROC glIsCommandListNV = nullptr;
    PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC glListDrawCommandsStatesClientNV =
        nullptr;
    PFNGLCOMMANDLISTSEGMENTSNVPROC glCommandListSegmentsNV = nullptr;
    PFNGLCOMPILECOMMANDLISTNVPROC glCompileCommandListNV = nullptr;
    PFNGLCALLCOMMANDLISTNVPROC glCallCommandListNV = nullptr;
#endif /* GL_NV_command_list */
#ifdef GL_NV_compute_shader_derivatives
#endif /* GL_NV_compute_shader_derivatives */
#ifdef GL_NV_conditional_render
    PFNGLBEGINCONDITIONALRENDERNVPROC glBeginConditionalRenderNV = nullptr;
    PFNGLENDCONDITIONALRENDERNVPROC glEndConditionalRenderNV = nullptr;
#endif /* GL_NV_conditional_render */
#ifdef GL_NV_conservative_raster
    PFNGLSUBPIXELPRECISIONBIASNVPROC glSubpixelPrecisionBiasNV = nullptr;
#endif /* GL_NV_conservative_raster */
#ifdef GL_NV_conservative_raster_dilate
    PFNGLCONSERVATIVERASTERPARAMETERFNVPROC glConservativeRasterParameterfNV =
        nullptr;
#endif /* GL_NV_conservative_raster_dilate */
#ifdef GL_NV_conservative_raster_pre_snap
#endif /* GL_NV_conservative_raster_pre_snap */
#ifdef GL_NV_conservative_raster_pre_snap_triangles
    PFNGLCONSERVATIVERASTERPARAMETERINVPROC glConservativeRasterParameteriNV =
        nullptr;
#endif /* GL_NV_conservative_raster_pre_snap_triangles */
#ifdef GL_NV_conservative_raster_underestimation
#endif /* GL_NV_conservative_raster_underestimation */
#ifdef GL_NV_depth_buffer_float
    PFNGLDEPTHRANGEDNVPROC glDepthRangedNV = nullptr;
    PFNGLCLEARDEPTHDNVPROC glClearDepthdNV = nullptr;
    PFNGLDEPTHBOUNDSDNVPROC glDepthBoundsdNV = nullptr;
#endif /* GL_NV_depth_buffer_float */
#ifdef GL_NV_draw_vulkan_image
    PFNGLDRAWVKIMAGENVPROC glDrawVkImageNV = nullptr;
    PFNGLGETVKPROCADDRNVPROC glGetVkProcAddrNV = nullptr;
    PFNGLWAITVKSEMAPHORENVPROC glWaitVkSemaphoreNV = nullptr;
    PFNGLSIGNALVKSEMAPHORENVPROC glSignalVkSemaphoreNV = nullptr;
    PFNGLSIGNALVKFENCENVPROC glSignalVkFenceNV = nullptr;
#endif /* GL_NV_draw_vulkan_image */
#ifdef GL_NV_fill_rectangle
#endif /* GL_NV_fill_rectangle */
#ifdef GL_NV_fragment_coverage_to_color
    PFNGLFRAGMENTCOVERAGECOLORNVPROC glFragmentCoverageColorNV = nullptr;
#endif /* GL_NV_fragment_coverage_to_color */
#ifdef GL_NV_fragment_shader_barycentric
#endif /* GL_NV_fragment_shader_barycentric */
#ifdef GL_NV_fragment_shader_interlock
#endif /* GL_NV_fragment_shader_interlock */
#ifdef GL_NV_framebuffer_mixed_samples
    PFNGLCOVERAGEMODULATIONTABLENVPROC glCoverageModulationTableNV = nullptr;
    PFNGLGETCOVERAGEMODULATIONTABLENVPROC glGetCoverageModulationTableNV =
        nullptr;
    PFNGLCOVERAGEMODULATIONNVPROC glCoverageModulationNV = nullptr;
#endif /* GL_NV_framebuffer_mixed_samples */
#ifdef GL_NV_framebuffer_multisample_coverage
    PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC
    glRenderbufferStorageMultisampleCoverageNV = nullptr;
#endif /* GL_NV_framebuffer_multisample_coverage */
#ifdef GL_NV_geometry_shader_passthrough
#endif /* GL_NV_geometry_shader_passthrough */
#ifdef GL_NV_gpu_shader5
    PFNGLUNIFORM1I64NVPROC glUniform1i64NV = nullptr;
    PFNGLUNIFORM2I64NVPROC glUniform2i64NV = nullptr;
    PFNGLUNIFORM3I64NVPROC glUniform3i64NV = nullptr;
    PFNGLUNIFORM4I64NVPROC glUniform4i64NV = nullptr;
    PFNGLUNIFORM1I64VNVPROC glUniform1i64vNV = nullptr;
    PFNGLUNIFORM2I64VNVPROC glUniform2i64vNV = nullptr;
    PFNGLUNIFORM3I64VNVPROC glUniform3i64vNV = nullptr;
    PFNGLUNIFORM4I64VNVPROC glUniform4i64vNV = nullptr;
    PFNGLUNIFORM1UI64NVPROC glUniform1ui64NV = nullptr;
    PFNGLUNIFORM2UI64NVPROC glUniform2ui64NV = nullptr;
    PFNGLUNIFORM3UI64NVPROC glUniform3ui64NV = nullptr;
    PFNGLUNIFORM4UI64NVPROC glUniform4ui64NV = nullptr;
    PFNGLUNIFORM1UI64VNVPROC glUniform1ui64vNV = nullptr;
    PFNGLUNIFORM2UI64VNVPROC glUniform2ui64vNV = nullptr;
    PFNGLUNIFORM3UI64VNVPROC glUniform3ui64vNV = nullptr;
    PFNGLUNIFORM4UI64VNVPROC glUniform4ui64vNV = nullptr;
    PFNGLGETUNIFORMI64VNVPROC glGetUniformi64vNV = nullptr;
    PFNGLPROGRAMUNIFORM1I64NVPROC glProgramUniform1i64NV = nullptr;
    PFNGLPROGRAMUNIFORM2I64NVPROC glProgramUniform2i64NV = nullptr;
    PFNGLPROGRAMUNIFORM3I64NVPROC glProgramUniform3i64NV = nullptr;
    PFNGLPROGRAMUNIFORM4I64NVPROC glProgramUniform4i64NV = nullptr;
    PFNGLPROGRAMUNIFORM1I64VNVPROC glProgramUniform1i64vNV = nullptr;
    PFNGLPROGRAMUNIFORM2I64VNVPROC glProgramUniform2i64vNV = nullptr;
    PFNGLPROGRAMUNIFORM3I64VNVPROC glProgramUniform3i64vNV = nullptr;
    PFNGLPROGRAMUNIFORM4I64VNVPROC glProgramUniform4i64vNV = nullptr;
    PFNGLPROGRAMUNIFORM1UI64NVPROC glProgramUniform1ui64NV = nullptr;
    PFNGLPROGRAMUNIFORM2UI64NVPROC glProgramUniform2ui64NV = nullptr;
    PFNGLPROGRAMUNIFORM3UI64NVPROC glProgramUniform3ui64NV = nullptr;
    PFNGLPROGRAMUNIFORM4UI64NVPROC glProgramUniform4ui64NV = nullptr;
    PFNGLPROGRAMUNIFORM1UI64VNVPROC glProgramUniform1ui64vNV = nullptr;
    PFNGLPROGRAMUNIFORM2UI64VNVPROC glProgramUniform2ui64vNV = nullptr;
    PFNGLPROGRAMUNIFORM3UI64VNVPROC glProgramUniform3ui64vNV = nullptr;
    PFNGLPROGRAMUNIFORM4UI64VNVPROC glProgramUniform4ui64vNV = nullptr;
#endif /* GL_NV_gpu_shader5 */
#ifdef GL_NV_internalformat_sample_query
    PFNGLGETINTERNALFORMATSAMPLEIVNVPROC glGetInternalformatSampleivNV =
        nullptr;
#endif /* GL_NV_internalformat_sample_query */
#ifdef GL_NV_memory_attachment
    PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC
    glGetMemoryObjectDetachedResourcesuivNV = nullptr;
    PFNGLRESETMEMORYOBJECTPARAMETERNVPROC glResetMemoryObjectParameterNV =
        nullptr;
    PFNGLTEXATTACHMEMORYNVPROC glTexAttachMemoryNV = nullptr;
    PFNGLBUFFERATTACHMEMORYNVPROC glBufferAttachMemoryNV = nullptr;
    PFNGLTEXTUREATTACHMEMORYNVPROC glTextureAttachMemoryNV = nullptr;
    PFNGLNAMEDBUFFERATTACHMEMORYNVPROC glNamedBufferAttachMemoryNV = nullptr;
#endif /* GL_NV_memory_attachment */
#ifdef GL_NV_memory_object_sparse
    PFNGLBUFFERPAGECOMMITMENTMEMNVPROC glBufferPageCommitmentMemNV = nullptr;
    PFNGLTEXPAGECOMMITMENTMEMNVPROC glTexPageCommitmentMemNV = nullptr;
    PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC glNamedBufferPageCommitmentMemNV =
        nullptr;
    PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC glTexturePageCommitmentMemNV = nullptr;
#endif /* GL_NV_memory_object_sparse */
#ifdef GL_NV_mesh_shader
    PFNGLDRAWMESHTASKSNVPROC glDrawMeshTasksNV = nullptr;
    PFNGLDRAWMESHTASKSINDIRECTNVPROC glDrawMeshTasksIndirectNV = nullptr;
    PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC glMultiDrawMeshTasksIndirectNV =
        nullptr;
    PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC
    glMultiDrawMeshTasksIndirectCountNV = nullptr;
#endif /* GL_NV_mesh_shader */
#ifdef GL_NV_path_rendering
    PFNGLGENPATHSNVPROC glGenPathsNV = nullptr;
    PFNGLDELETEPATHSNVPROC glDeletePathsNV = nullptr;
    PFNGLISPATHNVPROC glIsPathNV = nullptr;
    PFNGLPATHCOMMANDSNVPROC glPathCommandsNV = nullptr;
    PFNGLPATHCOORDSNVPROC glPathCoordsNV = nullptr;
    PFNGLPATHSUBCOMMANDSNVPROC glPathSubCommandsNV = nullptr;
    PFNGLPATHSUBCOORDSNVPROC glPathSubCoordsNV = nullptr;
    PFNGLPATHSTRINGNVPROC glPathStringNV = nullptr;
    PFNGLPATHGLYPHSNVPROC glPathGlyphsNV = nullptr;
    PFNGLPATHGLYPHRANGENVPROC glPathGlyphRangeNV = nullptr;
    PFNGLWEIGHTPATHSNVPROC glWeightPathsNV = nullptr;
    PFNGLCOPYPATHNVPROC glCopyPathNV = nullptr;
    PFNGLINTERPOLATEPATHSNVPROC glInterpolatePathsNV = nullptr;
    PFNGLTRANSFORMPATHNVPROC glTransformPathNV = nullptr;
    PFNGLPATHPARAMETERIVNVPROC glPathParameterivNV = nullptr;
    PFNGLPATHPARAMETERINVPROC glPathParameteriNV = nullptr;
    PFNGLPATHPARAMETERFVNVPROC glPathParameterfvNV = nullptr;
    PFNGLPATHPARAMETERFNVPROC glPathParameterfNV = nullptr;
    PFNGLPATHDASHARRAYNVPROC glPathDashArrayNV = nullptr;
    PFNGLPATHSTENCILFUNCNVPROC glPathStencilFuncNV = nullptr;
    PFNGLPATHSTENCILDEPTHOFFSETNVPROC glPathStencilDepthOffsetNV = nullptr;
    PFNGLSTENCILFILLPATHNVPROC glStencilFillPathNV = nullptr;
    PFNGLSTENCILSTROKEPATHNVPROC glStencilStrokePathNV = nullptr;
    PFNGLSTENCILFILLPATHINSTANCEDNVPROC glStencilFillPathInstancedNV = nullptr;
    PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC glStencilStrokePathInstancedNV =
        nullptr;
    PFNGLPATHCOVERDEPTHFUNCNVPROC glPathCoverDepthFuncNV = nullptr;
    PFNGLCOVERFILLPATHNVPROC glCoverFillPathNV = nullptr;
    PFNGLCOVERSTROKEPATHNVPROC glCoverStrokePathNV = nullptr;
    PFNGLCOVERFILLPATHINSTANCEDNVPROC glCoverFillPathInstancedNV = nullptr;
    PFNGLCOVERSTROKEPATHINSTANCEDNVPROC glCoverStrokePathInstancedNV = nullptr;
    PFNGLGETPATHPARAMETERIVNVPROC glGetPathParameterivNV = nullptr;
    PFNGLGETPATHPARAMETERFVNVPROC glGetPathParameterfvNV = nullptr;
    PFNGLGETPATHCOMMANDSNVPROC glGetPathCommandsNV = nullptr;
    PFNGLGETPATHCOORDSNVPROC glGetPathCoordsNV = nullptr;
    PFNGLGETPATHDASHARRAYNVPROC glGetPathDashArrayNV = nullptr;
    PFNGLGETPATHMETRICSNVPROC glGetPathMetricsNV = nullptr;
    PFNGLGETPATHMETRICRANGENVPROC glGetPathMetricRangeNV = nullptr;
    PFNGLGETPATHSPACINGNVPROC glGetPathSpacingNV = nullptr;
    PFNGLISPOINTINFILLPATHNVPROC glIsPointInFillPathNV = nullptr;
    PFNGLISPOINTINSTROKEPATHNVPROC glIsPointInStrokePathNV = nullptr;
    PFNGLGETPATHLENGTHNVPROC glGetPathLengthNV = nullptr;
    PFNGLPOINTALONGPATHNVPROC glPointAlongPathNV = nullptr;
    PFNGLMATRIXLOAD3X2FNVPROC glMatrixLoad3x2fNV = nullptr;
    PFNGLMATRIXLOAD3X3FNVPROC glMatrixLoad3x3fNV = nullptr;
    PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC glMatrixLoadTranspose3x3fNV = nullptr;
    PFNGLMATRIXMULT3X2FNVPROC glMatrixMult3x2fNV = nullptr;
    PFNGLMATRIXMULT3X3FNVPROC glMatrixMult3x3fNV = nullptr;
    PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC glMatrixMultTranspose3x3fNV = nullptr;
    PFNGLSTENCILTHENCOVERFILLPATHNVPROC glStencilThenCoverFillPathNV = nullptr;
    PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC glStencilThenCoverStrokePathNV =
        nullptr;
    PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC
    glStencilThenCoverFillPathInstancedNV = nullptr;
    PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC
    glStencilThenCoverStrokePathInstancedNV = nullptr;
    PFNGLPATHGLYPHINDEXRANGENVPROC glPathGlyphIndexRangeNV = nullptr;
    PFNGLPATHGLYPHINDEXARRAYNVPROC glPathGlyphIndexArrayNV = nullptr;
    PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC glPathMemoryGlyphIndexArrayNV =
        nullptr;
    PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC glProgramPathFragmentInputGenNV =
        nullptr;
    PFNGLGETPROGRAMRESOURCEFVNVPROC glGetProgramResourcefvNV = nullptr;
#endif /* GL_NV_path_rendering */
#ifdef GL_NV_path_rendering_shared_edge
#endif /* GL_NV_path_rendering_shared_edge */
#ifdef GL_NV_representative_fragment_test
#endif /* GL_NV_representative_fragment_test */
#ifdef GL_NV_sample_locations
    PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC glFramebufferSampleLocationsfvNV =
        nullptr;
    PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC
    glNamedFramebufferSampleLocationsfvNV = nullptr;
    PFNGLRESOLVEDEPTHVALUESNVPROC glResolveDepthValuesNV = nullptr;
#endif /* GL_NV_sample_locations */
#ifdef GL_NV_sample_mask_override_coverage
#endif /* GL_NV_sample_mask_override_coverage */
#ifdef GL_NV_scissor_exclusive
    PFNGLSCISSOREXCLUSIVENVPROC glScissorExclusiveNV = nullptr;
    PFNGLSCISSOREXCLUSIVEARRAYVNVPROC glScissorExclusiveArrayvNV = nullptr;
#endif /* GL_NV_scissor_exclusive */
#ifdef GL_NV_shader_atomic_counters
#endif /* GL_NV_shader_atomic_counters */
#ifdef GL_NV_shader_atomic_float
#endif /* GL_NV_shader_atomic_float */
#ifdef GL_NV_shader_atomic_float64
#endif /* GL_NV_shader_atomic_float64 */
#ifdef GL_NV_shader_atomic_fp16_vector
#endif /* GL_NV_shader_atomic_fp16_vector */
#ifdef GL_NV_shader_atomic_int64
#endif /* GL_NV_shader_atomic_int64 */
#ifdef GL_NV_shader_buffer_load
    PFNGLMAKEBUFFERRESIDENTNVPROC glMakeBufferResidentNV = nullptr;
    PFNGLMAKEBUFFERNONRESIDENTNVPROC glMakeBufferNonResidentNV = nullptr;
    PFNGLISBUFFERRESIDENTNVPROC glIsBufferResidentNV = nullptr;
    PFNGLMAKENAMEDBUFFERRESIDENTNVPROC glMakeNamedBufferResidentNV = nullptr;
    PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC glMakeNamedBufferNonResidentNV =
        nullptr;
    PFNGLISNAMEDBUFFERRESIDENTNVPROC glIsNamedBufferResidentNV = nullptr;
    PFNGLGETBUFFERPARAMETERUI64VNVPROC glGetBufferParameterui64vNV = nullptr;
    PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC glGetNamedBufferParameterui64vNV =
        nullptr;
    PFNGLGETINTEGERUI64VNVPROC glGetIntegerui64vNV = nullptr;
    PFNGLUNIFORMUI64NVPROC glUniformui64NV = nullptr;
    PFNGLUNIFORMUI64VNVPROC glUniformui64vNV = nullptr;
    PFNGLGETUNIFORMUI64VNVPROC glGetUniformui64vNV = nullptr;
    PFNGLPROGRAMUNIFORMUI64NVPROC glProgramUniformui64NV = nullptr;
    PFNGLPROGRAMUNIFORMUI64VNVPROC glProgramUniformui64vNV = nullptr;
#endif /* GL_NV_shader_buffer_load */
#ifdef GL_NV_shader_buffer_store
#endif /* GL_NV_shader_buffer_store */
#ifdef GL_NV_shader_subgroup_partitioned
#endif /* GL_NV_shader_subgroup_partitioned */
#ifdef GL_NV_shader_texture_footprint
#endif /* GL_NV_shader_texture_footprint */
#ifdef GL_NV_shader_thread_group
#endif /* GL_NV_shader_thread_group */
#ifdef GL_NV_shader_thread_shuffle
#endif /* GL_NV_shader_thread_shuffle */
#ifdef GL_NV_shading_rate_image
    PFNGLBINDSHADINGRATEIMAGENVPROC glBindShadingRateImageNV = nullptr;
    PFNGLGETSHADINGRATEIMAGEPALETTENVPROC glGetShadingRateImagePaletteNV =
        nullptr;
    PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC
    glGetShadingRateSampleLocationivNV = nullptr;
    PFNGLSHADINGRATEIMAGEBARRIERNVPROC glShadingRateImageBarrierNV = nullptr;
    PFNGLSHADINGRATEIMAGEPALETTENVPROC glShadingRateImagePaletteNV = nullptr;
    PFNGLSHADINGRATESAMPLEORDERNVPROC glShadingRateSampleOrderNV = nullptr;
    PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC glShadingRateSampleOrderCustomNV =
        nullptr;
#endif /* GL_NV_shading_rate_image */
#ifdef GL_NV_stereo_view_rendering
#endif /* GL_NV_stereo_view_rendering */
#ifdef GL_NV_texture_barrier
    PFNGLTEXTUREBARRIERNVPROC glTextureBarrierNV = nullptr;
#endif /* GL_NV_texture_barrier */
#ifdef GL_NV_texture_rectangle_compressed
#endif /* GL_NV_texture_rectangle_compressed */
#ifdef GL_NV_uniform_buffer_unified_memory
#endif /* GL_NV_uniform_buffer_unified_memory */
#ifdef GL_NV_vertex_attrib_integer_64bit
    PFNGLVERTEXATTRIBL1I64NVPROC glVertexAttribL1i64NV = nullptr;
    PFNGLVERTEXATTRIBL2I64NVPROC glVertexAttribL2i64NV = nullptr;
    PFNGLVERTEXATTRIBL3I64NVPROC glVertexAttribL3i64NV = nullptr;
    PFNGLVERTEXATTRIBL4I64NVPROC glVertexAttribL4i64NV = nullptr;
    PFNGLVERTEXATTRIBL1I64VNVPROC glVertexAttribL1i64vNV = nullptr;
    PFNGLVERTEXATTRIBL2I64VNVPROC glVertexAttribL2i64vNV = nullptr;
    PFNGLVERTEXATTRIBL3I64VNVPROC glVertexAttribL3i64vNV = nullptr;
    PFNGLVERTEXATTRIBL4I64VNVPROC glVertexAttribL4i64vNV = nullptr;
    PFNGLVERTEXATTRIBL1UI64NVPROC glVertexAttribL1ui64NV = nullptr;
    PFNGLVERTEXATTRIBL2UI64NVPROC glVertexAttribL2ui64NV = nullptr;
    PFNGLVERTEXATTRIBL3UI64NVPROC glVertexAttribL3ui64NV = nullptr;
    PFNGLVERTEXATTRIBL4UI64NVPROC glVertexAttribL4ui64NV = nullptr;
    PFNGLVERTEXATTRIBL1UI64VNVPROC glVertexAttribL1ui64vNV = nullptr;
    PFNGLVERTEXATTRIBL2UI64VNVPROC glVertexAttribL2ui64vNV = nullptr;
    PFNGLVERTEXATTRIBL3UI64VNVPROC glVertexAttribL3ui64vNV = nullptr;
    PFNGLVERTEXATTRIBL4UI64VNVPROC glVertexAttribL4ui64vNV = nullptr;
    PFNGLGETVERTEXATTRIBLI64VNVPROC glGetVertexAttribLi64vNV = nullptr;
    PFNGLGETVERTEXATTRIBLUI64VNVPROC glGetVertexAttribLui64vNV = nullptr;
    PFNGLVERTEXATTRIBLFORMATNVPROC glVertexAttribLFormatNV = nullptr;
#endif /* GL_NV_vertex_attrib_integer_64bit */
#ifdef GL_NV_vertex_buffer_unified_memory
    PFNGLBUFFERADDRESSRANGENVPROC glBufferAddressRangeNV = nullptr;
    PFNGLVERTEXFORMATNVPROC glVertexFormatNV = nullptr;
    PFNGLNORMALFORMATNVPROC glNormalFormatNV = nullptr;
    PFNGLCOLORFORMATNVPROC glColorFormatNV = nullptr;
    PFNGLINDEXFORMATNVPROC glIndexFormatNV = nullptr;
    PFNGLTEXCOORDFORMATNVPROC glTexCoordFormatNV = nullptr;
    PFNGLEDGEFLAGFORMATNVPROC glEdgeFlagFormatNV = nullptr;
    PFNGLSECONDARYCOLORFORMATNVPROC glSecondaryColorFormatNV = nullptr;
    PFNGLFOGCOORDFORMATNVPROC glFogCoordFormatNV = nullptr;
    PFNGLVERTEXATTRIBFORMATNVPROC glVertexAttribFormatNV = nullptr;
    PFNGLVERTEXATTRIBIFORMATNVPROC glVertexAttribIFormatNV = nullptr;
    PFNGLGETINTEGERUI64I_VNVPROC glGetIntegerui64i_vNV = nullptr;
#endif /* GL_NV_vertex_buffer_unified_memory */
#ifdef GL_NV_viewport_array2
#endif /* GL_NV_viewport_array2 */
#ifdef GL_NV_viewport_swizzle
    PFNGLVIEWPORTSWIZZLENVPROC glViewportSwizzleNV = nullptr;
#endif /* GL_NV_viewport_swizzle */
#ifdef GL_OVR_multiview
    PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC glFramebufferTextureMultiviewOVR =
        nullptr;
#endif /* GL_OVR_multiview */
#ifdef GL_OVR_multiview2
#endif /* GL_OVR_multiview2 */
    using PFN_GetProcAddr = std::function<void*(const char *)>;
    DispatchLoaderDynamic() = default;
    DispatchLoaderDynamic(PFN_GetProcAddr const & getProcAddr) { init(getProcAddr); }

    void init(PFN_GetProcAddr const & _loadProcAddr) {
        if (_loadProcAddr == nullptr) return;
#ifdef GL_VERSION_1_0
        glCullFace =
            reinterpret_cast<PFNGLCULLFACEPROC>(_loadProcAddr("glCullFace"));
        glFrontFace =
            reinterpret_cast<PFNGLFRONTFACEPROC>(_loadProcAddr("glFrontFace"));
        glHint = reinterpret_cast<PFNGLHINTPROC>(_loadProcAddr("glHint"));
        glLineWidth =
            reinterpret_cast<PFNGLLINEWIDTHPROC>(_loadProcAddr("glLineWidth"));
        glPointSize =
            reinterpret_cast<PFNGLPOINTSIZEPROC>(_loadProcAddr("glPointSize"));
        glPolygonMode = reinterpret_cast<PFNGLPOLYGONMODEPROC>(
            _loadProcAddr("glPolygonMode"));
        glScissor =
            reinterpret_cast<PFNGLSCISSORPROC>(_loadProcAddr("glScissor"));
        glTexParameterf = reinterpret_cast<PFNGLTEXPARAMETERFPROC>(
            _loadProcAddr("glTexParameterf"));
        glTexParameterfv = reinterpret_cast<PFNGLTEXPARAMETERFVPROC>(
            _loadProcAddr("glTexParameterfv"));
        glTexParameteri = reinterpret_cast<PFNGLTEXPARAMETERIPROC>(
            _loadProcAddr("glTexParameteri"));
        glTexParameteriv = reinterpret_cast<PFNGLTEXPARAMETERIVPROC>(
            _loadProcAddr("glTexParameteriv"));
        glTexImage1D = reinterpret_cast<PFNGLTEXIMAGE1DPROC>(
            _loadProcAddr("glTexImage1D"));
        glTexImage2D = reinterpret_cast<PFNGLTEXIMAGE2DPROC>(
            _loadProcAddr("glTexImage2D"));
        glDrawBuffer = reinterpret_cast<PFNGLDRAWBUFFERPROC>(
            _loadProcAddr("glDrawBuffer"));
        glClear = reinterpret_cast<PFNGLCLEARPROC>(_loadProcAddr("glClear"));
        glClearColor = reinterpret_cast<PFNGLCLEARCOLORPROC>(
            _loadProcAddr("glClearColor"));
        glClearStencil = reinterpret_cast<PFNGLCLEARSTENCILPROC>(
            _loadProcAddr("glClearStencil"));
        glClearDepth = reinterpret_cast<PFNGLCLEARDEPTHPROC>(
            _loadProcAddr("glClearDepth"));
        glStencilMask = reinterpret_cast<PFNGLSTENCILMASKPROC>(
            _loadProcAddr("glStencilMask"));
        glColorMask =
            reinterpret_cast<PFNGLCOLORMASKPROC>(_loadProcAddr("glColorMask"));
        glDepthMask =
            reinterpret_cast<PFNGLDEPTHMASKPROC>(_loadProcAddr("glDepthMask"));
        glDisable =
            reinterpret_cast<PFNGLDISABLEPROC>(_loadProcAddr("glDisable"));
        glEnable = reinterpret_cast<PFNGLENABLEPROC>(_loadProcAddr("glEnable"));
        glFinish = reinterpret_cast<PFNGLFINISHPROC>(_loadProcAddr("glFinish"));
        glFlush = reinterpret_cast<PFNGLFLUSHPROC>(_loadProcAddr("glFlush"));
        glBlendFunc =
            reinterpret_cast<PFNGLBLENDFUNCPROC>(_loadProcAddr("glBlendFunc"));
        glLogicOp =
            reinterpret_cast<PFNGLLOGICOPPROC>(_loadProcAddr("glLogicOp"));
        glStencilFunc = reinterpret_cast<PFNGLSTENCILFUNCPROC>(
            _loadProcAddr("glStencilFunc"));
        glStencilOp =
            reinterpret_cast<PFNGLSTENCILOPPROC>(_loadProcAddr("glStencilOp"));
        glDepthFunc =
            reinterpret_cast<PFNGLDEPTHFUNCPROC>(_loadProcAddr("glDepthFunc"));
        glPixelStoref = reinterpret_cast<PFNGLPIXELSTOREFPROC>(
            _loadProcAddr("glPixelStoref"));
        glPixelStorei = reinterpret_cast<PFNGLPIXELSTOREIPROC>(
            _loadProcAddr("glPixelStorei"));
        glReadBuffer = reinterpret_cast<PFNGLREADBUFFERPROC>(
            _loadProcAddr("glReadBuffer"));
        glReadPixels = reinterpret_cast<PFNGLREADPIXELSPROC>(
            _loadProcAddr("glReadPixels"));
        glGetBooleanv = reinterpret_cast<PFNGLGETBOOLEANVPROC>(
            _loadProcAddr("glGetBooleanv"));
        glGetDoublev = reinterpret_cast<PFNGLGETDOUBLEVPROC>(
            _loadProcAddr("glGetDoublev"));
        glGetError =
            reinterpret_cast<PFNGLGETERRORPROC>(_loadProcAddr("glGetError"));
        glGetFloatv =
            reinterpret_cast<PFNGLGETFLOATVPROC>(_loadProcAddr("glGetFloatv"));
        glGetIntegerv = reinterpret_cast<PFNGLGETINTEGERVPROC>(
            _loadProcAddr("glGetIntegerv"));
        glGetString =
            reinterpret_cast<PFNGLGETSTRINGPROC>(_loadProcAddr("glGetString"));
        glGetTexImage = reinterpret_cast<PFNGLGETTEXIMAGEPROC>(
            _loadProcAddr("glGetTexImage"));
        glGetTexParameterfv = reinterpret_cast<PFNGLGETTEXPARAMETERFVPROC>(
            _loadProcAddr("glGetTexParameterfv"));
        glGetTexParameteriv = reinterpret_cast<PFNGLGETTEXPARAMETERIVPROC>(
            _loadProcAddr("glGetTexParameteriv"));
        glGetTexLevelParameterfv =
            reinterpret_cast<PFNGLGETTEXLEVELPARAMETERFVPROC>(
                _loadProcAddr("glGetTexLevelParameterfv"));
        glGetTexLevelParameteriv =
            reinterpret_cast<PFNGLGETTEXLEVELPARAMETERIVPROC>(
                _loadProcAddr("glGetTexLevelParameteriv"));
        glIsEnabled =
            reinterpret_cast<PFNGLISENABLEDPROC>(_loadProcAddr("glIsEnabled"));
        glDepthRange = reinterpret_cast<PFNGLDEPTHRANGEPROC>(
            _loadProcAddr("glDepthRange"));
        glViewport =
            reinterpret_cast<PFNGLVIEWPORTPROC>(_loadProcAddr("glViewport"));
#endif /* GL_VERSION_1_0 */
#ifdef GL_VERSION_1_1
        glDrawArrays = reinterpret_cast<PFNGLDRAWARRAYSPROC>(
            _loadProcAddr("glDrawArrays"));
        glDrawElements = reinterpret_cast<PFNGLDRAWELEMENTSPROC>(
            _loadProcAddr("glDrawElements"));
        glGetPointerv = reinterpret_cast<PFNGLGETPOINTERVPROC>(
            _loadProcAddr("glGetPointerv"));
        glPolygonOffset = reinterpret_cast<PFNGLPOLYGONOFFSETPROC>(
            _loadProcAddr("glPolygonOffset"));
        glCopyTexImage1D = reinterpret_cast<PFNGLCOPYTEXIMAGE1DPROC>(
            _loadProcAddr("glCopyTexImage1D"));
        glCopyTexImage2D = reinterpret_cast<PFNGLCOPYTEXIMAGE2DPROC>(
            _loadProcAddr("glCopyTexImage2D"));
        glCopyTexSubImage1D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE1DPROC>(
            _loadProcAddr("glCopyTexSubImage1D"));
        glCopyTexSubImage2D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE2DPROC>(
            _loadProcAddr("glCopyTexSubImage2D"));
        glTexSubImage1D = reinterpret_cast<PFNGLTEXSUBIMAGE1DPROC>(
            _loadProcAddr("glTexSubImage1D"));
        glTexSubImage2D = reinterpret_cast<PFNGLTEXSUBIMAGE2DPROC>(
            _loadProcAddr("glTexSubImage2D"));
        glBindTexture = reinterpret_cast<PFNGLBINDTEXTUREPROC>(
            _loadProcAddr("glBindTexture"));
        glDeleteTextures = reinterpret_cast<PFNGLDELETETEXTURESPROC>(
            _loadProcAddr("glDeleteTextures"));
        glGenTextures = reinterpret_cast<PFNGLGENTEXTURESPROC>(
            _loadProcAddr("glGenTextures"));
        glIsTexture =
            reinterpret_cast<PFNGLISTEXTUREPROC>(_loadProcAddr("glIsTexture"));
#endif /* GL_VERSION_1_1 */
#ifdef GL_VERSION_1_2
        glDrawRangeElements = reinterpret_cast<PFNGLDRAWRANGEELEMENTSPROC>(
            _loadProcAddr("glDrawRangeElements"));
        glTexImage3D = reinterpret_cast<PFNGLTEXIMAGE3DPROC>(
            _loadProcAddr("glTexImage3D"));
        glTexSubImage3D = reinterpret_cast<PFNGLTEXSUBIMAGE3DPROC>(
            _loadProcAddr("glTexSubImage3D"));
        glCopyTexSubImage3D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE3DPROC>(
            _loadProcAddr("glCopyTexSubImage3D"));
#endif /* GL_VERSION_1_2 */
#ifdef GL_VERSION_1_3
        glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTUREPROC>(
            _loadProcAddr("glActiveTexture"));
        glSampleCoverage = reinterpret_cast<PFNGLSAMPLECOVERAGEPROC>(
            _loadProcAddr("glSampleCoverage"));
        glCompressedTexImage3D =
            reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE3DPROC>(
                _loadProcAddr("glCompressedTexImage3D"));
        glCompressedTexImage2D =
            reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE2DPROC>(
                _loadProcAddr("glCompressedTexImage2D"));
        glCompressedTexImage1D =
            reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE1DPROC>(
                _loadProcAddr("glCompressedTexImage1D"));
        glCompressedTexSubImage3D =
            reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC>(
                _loadProcAddr("glCompressedTexSubImage3D"));
        glCompressedTexSubImage2D =
            reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC>(
                _loadProcAddr("glCompressedTexSubImage2D"));
        glCompressedTexSubImage1D =
            reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC>(
                _loadProcAddr("glCompressedTexSubImage1D"));
        glGetCompressedTexImage =
            reinterpret_cast<PFNGLGETCOMPRESSEDTEXIMAGEPROC>(
                _loadProcAddr("glGetCompressedTexImage"));
#endif /* GL_VERSION_1_3 */
#ifdef GL_VERSION_1_4
        glBlendFuncSeparate = reinterpret_cast<PFNGLBLENDFUNCSEPARATEPROC>(
            _loadProcAddr("glBlendFuncSeparate"));
        glMultiDrawArrays = reinterpret_cast<PFNGLMULTIDRAWARRAYSPROC>(
            _loadProcAddr("glMultiDrawArrays"));
        glMultiDrawElements = reinterpret_cast<PFNGLMULTIDRAWELEMENTSPROC>(
            _loadProcAddr("glMultiDrawElements"));
        glPointParameterf = reinterpret_cast<PFNGLPOINTPARAMETERFPROC>(
            _loadProcAddr("glPointParameterf"));
        glPointParameterfv = reinterpret_cast<PFNGLPOINTPARAMETERFVPROC>(
            _loadProcAddr("glPointParameterfv"));
        glPointParameteri = reinterpret_cast<PFNGLPOINTPARAMETERIPROC>(
            _loadProcAddr("glPointParameteri"));
        glPointParameteriv = reinterpret_cast<PFNGLPOINTPARAMETERIVPROC>(
            _loadProcAddr("glPointParameteriv"));
        glBlendColor = reinterpret_cast<PFNGLBLENDCOLORPROC>(
            _loadProcAddr("glBlendColor"));
        glBlendEquation = reinterpret_cast<PFNGLBLENDEQUATIONPROC>(
            _loadProcAddr("glBlendEquation"));
#endif /* GL_VERSION_1_4 */
#ifdef GL_VERSION_1_5
        glGenQueries = reinterpret_cast<PFNGLGENQUERIESPROC>(
            _loadProcAddr("glGenQueries"));
        glDeleteQueries = reinterpret_cast<PFNGLDELETEQUERIESPROC>(
            _loadProcAddr("glDeleteQueries"));
        glIsQuery =
            reinterpret_cast<PFNGLISQUERYPROC>(_loadProcAddr("glIsQuery"));
        glBeginQuery = reinterpret_cast<PFNGLBEGINQUERYPROC>(
            _loadProcAddr("glBeginQuery"));
        glEndQuery =
            reinterpret_cast<PFNGLENDQUERYPROC>(_loadProcAddr("glEndQuery"));
        glGetQueryiv = reinterpret_cast<PFNGLGETQUERYIVPROC>(
            _loadProcAddr("glGetQueryiv"));
        glGetQueryObjectiv = reinterpret_cast<PFNGLGETQUERYOBJECTIVPROC>(
            _loadProcAddr("glGetQueryObjectiv"));
        glGetQueryObjectuiv = reinterpret_cast<PFNGLGETQUERYOBJECTUIVPROC>(
            _loadProcAddr("glGetQueryObjectuiv"));
        glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(
            _loadProcAddr("glBindBuffer"));
        glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(
            _loadProcAddr("glDeleteBuffers"));
        glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(
            _loadProcAddr("glGenBuffers"));
        glIsBuffer =
            reinterpret_cast<PFNGLISBUFFERPROC>(_loadProcAddr("glIsBuffer"));
        glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(
            _loadProcAddr("glBufferData"));
        glBufferSubData = reinterpret_cast<PFNGLBUFFERSUBDATAPROC>(
            _loadProcAddr("glBufferSubData"));
        glGetBufferSubData = reinterpret_cast<PFNGLGETBUFFERSUBDATAPROC>(
            _loadProcAddr("glGetBufferSubData"));
        glMapBuffer =
            reinterpret_cast<PFNGLMAPBUFFERPROC>(_loadProcAddr("glMapBuffer"));
        glUnmapBuffer = reinterpret_cast<PFNGLUNMAPBUFFERPROC>(
            _loadProcAddr("glUnmapBuffer"));
        glGetBufferParameteriv =
            reinterpret_cast<PFNGLGETBUFFERPARAMETERIVPROC>(
                _loadProcAddr("glGetBufferParameteriv"));
        glGetBufferPointerv = reinterpret_cast<PFNGLGETBUFFERPOINTERVPROC>(
            _loadProcAddr("glGetBufferPointerv"));
#endif /* GL_VERSION_1_5 */
#ifdef GL_VERSION_2_0
        glBlendEquationSeparate =
            reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEPROC>(
                _loadProcAddr("glBlendEquationSeparate"));
        glDrawBuffers = reinterpret_cast<PFNGLDRAWBUFFERSPROC>(
            _loadProcAddr("glDrawBuffers"));
        glStencilOpSeparate = reinterpret_cast<PFNGLSTENCILOPSEPARATEPROC>(
            _loadProcAddr("glStencilOpSeparate"));
        glStencilFuncSeparate = reinterpret_cast<PFNGLSTENCILFUNCSEPARATEPROC>(
            _loadProcAddr("glStencilFuncSeparate"));
        glStencilMaskSeparate = reinterpret_cast<PFNGLSTENCILMASKSEPARATEPROC>(
            _loadProcAddr("glStencilMaskSeparate"));
        glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(
            _loadProcAddr("glAttachShader"));
        glBindAttribLocation = reinterpret_cast<PFNGLBINDATTRIBLOCATIONPROC>(
            _loadProcAddr("glBindAttribLocation"));
        glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(
            _loadProcAddr("glCompileShader"));
        glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(
            _loadProcAddr("glCreateProgram"));
        glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(
            _loadProcAddr("glCreateShader"));
        glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(
            _loadProcAddr("glDeleteProgram"));
        glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(
            _loadProcAddr("glDeleteShader"));
        glDetachShader = reinterpret_cast<PFNGLDETACHSHADERPROC>(
            _loadProcAddr("glDetachShader"));
        glDisableVertexAttribArray =
            reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(
                _loadProcAddr("glDisableVertexAttribArray"));
        glEnableVertexAttribArray =
            reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(
                _loadProcAddr("glEnableVertexAttribArray"));
        glGetActiveAttrib = reinterpret_cast<PFNGLGETACTIVEATTRIBPROC>(
            _loadProcAddr("glGetActiveAttrib"));
        glGetActiveUniform = reinterpret_cast<PFNGLGETACTIVEUNIFORMPROC>(
            _loadProcAddr("glGetActiveUniform"));
        glGetAttachedShaders = reinterpret_cast<PFNGLGETATTACHEDSHADERSPROC>(
            _loadProcAddr("glGetAttachedShaders"));
        glGetAttribLocation = reinterpret_cast<PFNGLGETATTRIBLOCATIONPROC>(
            _loadProcAddr("glGetAttribLocation"));
        glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(
            _loadProcAddr("glGetProgramiv"));
        glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(
            _loadProcAddr("glGetProgramInfoLog"));
        glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(
            _loadProcAddr("glGetShaderiv"));
        glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(
            _loadProcAddr("glGetShaderInfoLog"));
        glGetShaderSource = reinterpret_cast<PFNGLGETSHADERSOURCEPROC>(
            _loadProcAddr("glGetShaderSource"));
        glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(
            _loadProcAddr("glGetUniformLocation"));
        glGetUniformfv = reinterpret_cast<PFNGLGETUNIFORMFVPROC>(
            _loadProcAddr("glGetUniformfv"));
        glGetUniformiv = reinterpret_cast<PFNGLGETUNIFORMIVPROC>(
            _loadProcAddr("glGetUniformiv"));
        glGetVertexAttribdv = reinterpret_cast<PFNGLGETVERTEXATTRIBDVPROC>(
            _loadProcAddr("glGetVertexAttribdv"));
        glGetVertexAttribfv = reinterpret_cast<PFNGLGETVERTEXATTRIBFVPROC>(
            _loadProcAddr("glGetVertexAttribfv"));
        glGetVertexAttribiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIVPROC>(
            _loadProcAddr("glGetVertexAttribiv"));
        glGetVertexAttribPointerv =
            reinterpret_cast<PFNGLGETVERTEXATTRIBPOINTERVPROC>(
                _loadProcAddr("glGetVertexAttribPointerv"));
        glIsProgram =
            reinterpret_cast<PFNGLISPROGRAMPROC>(_loadProcAddr("glIsProgram"));
        glIsShader =
            reinterpret_cast<PFNGLISSHADERPROC>(_loadProcAddr("glIsShader"));
        glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(
            _loadProcAddr("glLinkProgram"));
        glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(
            _loadProcAddr("glShaderSource"));
        glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(
            _loadProcAddr("glUseProgram"));
        glUniform1f =
            reinterpret_cast<PFNGLUNIFORM1FPROC>(_loadProcAddr("glUniform1f"));
        glUniform2f =
            reinterpret_cast<PFNGLUNIFORM2FPROC>(_loadProcAddr("glUniform2f"));
        glUniform3f =
            reinterpret_cast<PFNGLUNIFORM3FPROC>(_loadProcAddr("glUniform3f"));
        glUniform4f =
            reinterpret_cast<PFNGLUNIFORM4FPROC>(_loadProcAddr("glUniform4f"));
        glUniform1i =
            reinterpret_cast<PFNGLUNIFORM1IPROC>(_loadProcAddr("glUniform1i"));
        glUniform2i =
            reinterpret_cast<PFNGLUNIFORM2IPROC>(_loadProcAddr("glUniform2i"));
        glUniform3i =
            reinterpret_cast<PFNGLUNIFORM3IPROC>(_loadProcAddr("glUniform3i"));
        glUniform4i =
            reinterpret_cast<PFNGLUNIFORM4IPROC>(_loadProcAddr("glUniform4i"));
        glUniform1fv = reinterpret_cast<PFNGLUNIFORM1FVPROC>(
            _loadProcAddr("glUniform1fv"));
        glUniform2fv = reinterpret_cast<PFNGLUNIFORM2FVPROC>(
            _loadProcAddr("glUniform2fv"));
        glUniform3fv = reinterpret_cast<PFNGLUNIFORM3FVPROC>(
            _loadProcAddr("glUniform3fv"));
        glUniform4fv = reinterpret_cast<PFNGLUNIFORM4FVPROC>(
            _loadProcAddr("glUniform4fv"));
        glUniform1iv = reinterpret_cast<PFNGLUNIFORM1IVPROC>(
            _loadProcAddr("glUniform1iv"));
        glUniform2iv = reinterpret_cast<PFNGLUNIFORM2IVPROC>(
            _loadProcAddr("glUniform2iv"));
        glUniform3iv = reinterpret_cast<PFNGLUNIFORM3IVPROC>(
            _loadProcAddr("glUniform3iv"));
        glUniform4iv = reinterpret_cast<PFNGLUNIFORM4IVPROC>(
            _loadProcAddr("glUniform4iv"));
        glUniformMatrix2fv = reinterpret_cast<PFNGLUNIFORMMATRIX2FVPROC>(
            _loadProcAddr("glUniformMatrix2fv"));
        glUniformMatrix3fv = reinterpret_cast<PFNGLUNIFORMMATRIX3FVPROC>(
            _loadProcAddr("glUniformMatrix3fv"));
        glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(
            _loadProcAddr("glUniformMatrix4fv"));
        glValidateProgram = reinterpret_cast<PFNGLVALIDATEPROGRAMPROC>(
            _loadProcAddr("glValidateProgram"));
        glVertexAttrib1d = reinterpret_cast<PFNGLVERTEXATTRIB1DPROC>(
            _loadProcAddr("glVertexAttrib1d"));
        glVertexAttrib1dv = reinterpret_cast<PFNGLVERTEXATTRIB1DVPROC>(
            _loadProcAddr("glVertexAttrib1dv"));
        glVertexAttrib1f = reinterpret_cast<PFNGLVERTEXATTRIB1FPROC>(
            _loadProcAddr("glVertexAttrib1f"));
        glVertexAttrib1fv = reinterpret_cast<PFNGLVERTEXATTRIB1FVPROC>(
            _loadProcAddr("glVertexAttrib1fv"));
        glVertexAttrib1s = reinterpret_cast<PFNGLVERTEXATTRIB1SPROC>(
            _loadProcAddr("glVertexAttrib1s"));
        glVertexAttrib1sv = reinterpret_cast<PFNGLVERTEXATTRIB1SVPROC>(
            _loadProcAddr("glVertexAttrib1sv"));
        glVertexAttrib2d = reinterpret_cast<PFNGLVERTEXATTRIB2DPROC>(
            _loadProcAddr("glVertexAttrib2d"));
        glVertexAttrib2dv = reinterpret_cast<PFNGLVERTEXATTRIB2DVPROC>(
            _loadProcAddr("glVertexAttrib2dv"));
        glVertexAttrib2f = reinterpret_cast<PFNGLVERTEXATTRIB2FPROC>(
            _loadProcAddr("glVertexAttrib2f"));
        glVertexAttrib2fv = reinterpret_cast<PFNGLVERTEXATTRIB2FVPROC>(
            _loadProcAddr("glVertexAttrib2fv"));
        glVertexAttrib2s = reinterpret_cast<PFNGLVERTEXATTRIB2SPROC>(
            _loadProcAddr("glVertexAttrib2s"));
        glVertexAttrib2sv = reinterpret_cast<PFNGLVERTEXATTRIB2SVPROC>(
            _loadProcAddr("glVertexAttrib2sv"));
        glVertexAttrib3d = reinterpret_cast<PFNGLVERTEXATTRIB3DPROC>(
            _loadProcAddr("glVertexAttrib3d"));
        glVertexAttrib3dv = reinterpret_cast<PFNGLVERTEXATTRIB3DVPROC>(
            _loadProcAddr("glVertexAttrib3dv"));
        glVertexAttrib3f = reinterpret_cast<PFNGLVERTEXATTRIB3FPROC>(
            _loadProcAddr("glVertexAttrib3f"));
        glVertexAttrib3fv = reinterpret_cast<PFNGLVERTEXATTRIB3FVPROC>(
            _loadProcAddr("glVertexAttrib3fv"));
        glVertexAttrib3s = reinterpret_cast<PFNGLVERTEXATTRIB3SPROC>(
            _loadProcAddr("glVertexAttrib3s"));
        glVertexAttrib3sv = reinterpret_cast<PFNGLVERTEXATTRIB3SVPROC>(
            _loadProcAddr("glVertexAttrib3sv"));
        glVertexAttrib4Nbv = reinterpret_cast<PFNGLVERTEXATTRIB4NBVPROC>(
            _loadProcAddr("glVertexAttrib4Nbv"));
        glVertexAttrib4Niv = reinterpret_cast<PFNGLVERTEXATTRIB4NIVPROC>(
            _loadProcAddr("glVertexAttrib4Niv"));
        glVertexAttrib4Nsv = reinterpret_cast<PFNGLVERTEXATTRIB4NSVPROC>(
            _loadProcAddr("glVertexAttrib4Nsv"));
        glVertexAttrib4Nub = reinterpret_cast<PFNGLVERTEXATTRIB4NUBPROC>(
            _loadProcAddr("glVertexAttrib4Nub"));
        glVertexAttrib4Nubv = reinterpret_cast<PFNGLVERTEXATTRIB4NUBVPROC>(
            _loadProcAddr("glVertexAttrib4Nubv"));
        glVertexAttrib4Nuiv = reinterpret_cast<PFNGLVERTEXATTRIB4NUIVPROC>(
            _loadProcAddr("glVertexAttrib4Nuiv"));
        glVertexAttrib4Nusv = reinterpret_cast<PFNGLVERTEXATTRIB4NUSVPROC>(
            _loadProcAddr("glVertexAttrib4Nusv"));
        glVertexAttrib4bv = reinterpret_cast<PFNGLVERTEXATTRIB4BVPROC>(
            _loadProcAddr("glVertexAttrib4bv"));
        glVertexAttrib4d = reinterpret_cast<PFNGLVERTEXATTRIB4DPROC>(
            _loadProcAddr("glVertexAttrib4d"));
        glVertexAttrib4dv = reinterpret_cast<PFNGLVERTEXATTRIB4DVPROC>(
            _loadProcAddr("glVertexAttrib4dv"));
        glVertexAttrib4f = reinterpret_cast<PFNGLVERTEXATTRIB4FPROC>(
            _loadProcAddr("glVertexAttrib4f"));
        glVertexAttrib4fv = reinterpret_cast<PFNGLVERTEXATTRIB4FVPROC>(
            _loadProcAddr("glVertexAttrib4fv"));
        glVertexAttrib4iv = reinterpret_cast<PFNGLVERTEXATTRIB4IVPROC>(
            _loadProcAddr("glVertexAttrib4iv"));
        glVertexAttrib4s = reinterpret_cast<PFNGLVERTEXATTRIB4SPROC>(
            _loadProcAddr("glVertexAttrib4s"));
        glVertexAttrib4sv = reinterpret_cast<PFNGLVERTEXATTRIB4SVPROC>(
            _loadProcAddr("glVertexAttrib4sv"));
        glVertexAttrib4ubv = reinterpret_cast<PFNGLVERTEXATTRIB4UBVPROC>(
            _loadProcAddr("glVertexAttrib4ubv"));
        glVertexAttrib4uiv = reinterpret_cast<PFNGLVERTEXATTRIB4UIVPROC>(
            _loadProcAddr("glVertexAttrib4uiv"));
        glVertexAttrib4usv = reinterpret_cast<PFNGLVERTEXATTRIB4USVPROC>(
            _loadProcAddr("glVertexAttrib4usv"));
        glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(
            _loadProcAddr("glVertexAttribPointer"));
#endif /* GL_VERSION_2_0 */
#ifdef GL_VERSION_2_1
        glUniformMatrix2x3fv = reinterpret_cast<PFNGLUNIFORMMATRIX2X3FVPROC>(
            _loadProcAddr("glUniformMatrix2x3fv"));
        glUniformMatrix3x2fv = reinterpret_cast<PFNGLUNIFORMMATRIX3X2FVPROC>(
            _loadProcAddr("glUniformMatrix3x2fv"));
        glUniformMatrix2x4fv = reinterpret_cast<PFNGLUNIFORMMATRIX2X4FVPROC>(
            _loadProcAddr("glUniformMatrix2x4fv"));
        glUniformMatrix4x2fv = reinterpret_cast<PFNGLUNIFORMMATRIX4X2FVPROC>(
            _loadProcAddr("glUniformMatrix4x2fv"));
        glUniformMatrix3x4fv = reinterpret_cast<PFNGLUNIFORMMATRIX3X4FVPROC>(
            _loadProcAddr("glUniformMatrix3x4fv"));
        glUniformMatrix4x3fv = reinterpret_cast<PFNGLUNIFORMMATRIX4X3FVPROC>(
            _loadProcAddr("glUniformMatrix4x3fv"));
#endif /* GL_VERSION_2_1 */
#ifdef GL_VERSION_3_0
        glColorMaski = reinterpret_cast<PFNGLCOLORMASKIPROC>(
            _loadProcAddr("glColorMaski"));
        glGetBooleani_v = reinterpret_cast<PFNGLGETBOOLEANI_VPROC>(
            _loadProcAddr("glGetBooleani_v"));
        glGetIntegeri_v = reinterpret_cast<PFNGLGETINTEGERI_VPROC>(
            _loadProcAddr("glGetIntegeri_v"));
        glEnablei =
            reinterpret_cast<PFNGLENABLEIPROC>(_loadProcAddr("glEnablei"));
        glDisablei =
            reinterpret_cast<PFNGLDISABLEIPROC>(_loadProcAddr("glDisablei"));
        glIsEnabledi = reinterpret_cast<PFNGLISENABLEDIPROC>(
            _loadProcAddr("glIsEnabledi"));
        glBeginTransformFeedback =
            reinterpret_cast<PFNGLBEGINTRANSFORMFEEDBACKPROC>(
                _loadProcAddr("glBeginTransformFeedback"));
        glEndTransformFeedback =
            reinterpret_cast<PFNGLENDTRANSFORMFEEDBACKPROC>(
                _loadProcAddr("glEndTransformFeedback"));
        glBindBufferRange = reinterpret_cast<PFNGLBINDBUFFERRANGEPROC>(
            _loadProcAddr("glBindBufferRange"));
        glBindBufferBase = reinterpret_cast<PFNGLBINDBUFFERBASEPROC>(
            _loadProcAddr("glBindBufferBase"));
        glTransformFeedbackVaryings =
            reinterpret_cast<PFNGLTRANSFORMFEEDBACKVARYINGSPROC>(
                _loadProcAddr("glTransformFeedbackVaryings"));
        glGetTransformFeedbackVarying =
            reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKVARYINGPROC>(
                _loadProcAddr("glGetTransformFeedbackVarying"));
        glClampColor = reinterpret_cast<PFNGLCLAMPCOLORPROC>(
            _loadProcAddr("glClampColor"));
        glBeginConditionalRender =
            reinterpret_cast<PFNGLBEGINCONDITIONALRENDERPROC>(
                _loadProcAddr("glBeginConditionalRender"));
        glEndConditionalRender =
            reinterpret_cast<PFNGLENDCONDITIONALRENDERPROC>(
                _loadProcAddr("glEndConditionalRender"));
        glVertexAttribIPointer =
            reinterpret_cast<PFNGLVERTEXATTRIBIPOINTERPROC>(
                _loadProcAddr("glVertexAttribIPointer"));
        glGetVertexAttribIiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIIVPROC>(
            _loadProcAddr("glGetVertexAttribIiv"));
        glGetVertexAttribIuiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIUIVPROC>(
            _loadProcAddr("glGetVertexAttribIuiv"));
        glVertexAttribI1i = reinterpret_cast<PFNGLVERTEXATTRIBI1IPROC>(
            _loadProcAddr("glVertexAttribI1i"));
        glVertexAttribI2i = reinterpret_cast<PFNGLVERTEXATTRIBI2IPROC>(
            _loadProcAddr("glVertexAttribI2i"));
        glVertexAttribI3i = reinterpret_cast<PFNGLVERTEXATTRIBI3IPROC>(
            _loadProcAddr("glVertexAttribI3i"));
        glVertexAttribI4i = reinterpret_cast<PFNGLVERTEXATTRIBI4IPROC>(
            _loadProcAddr("glVertexAttribI4i"));
        glVertexAttribI1ui = reinterpret_cast<PFNGLVERTEXATTRIBI1UIPROC>(
            _loadProcAddr("glVertexAttribI1ui"));
        glVertexAttribI2ui = reinterpret_cast<PFNGLVERTEXATTRIBI2UIPROC>(
            _loadProcAddr("glVertexAttribI2ui"));
        glVertexAttribI3ui = reinterpret_cast<PFNGLVERTEXATTRIBI3UIPROC>(
            _loadProcAddr("glVertexAttribI3ui"));
        glVertexAttribI4ui = reinterpret_cast<PFNGLVERTEXATTRIBI4UIPROC>(
            _loadProcAddr("glVertexAttribI4ui"));
        glVertexAttribI1iv = reinterpret_cast<PFNGLVERTEXATTRIBI1IVPROC>(
            _loadProcAddr("glVertexAttribI1iv"));
        glVertexAttribI2iv = reinterpret_cast<PFNGLVERTEXATTRIBI2IVPROC>(
            _loadProcAddr("glVertexAttribI2iv"));
        glVertexAttribI3iv = reinterpret_cast<PFNGLVERTEXATTRIBI3IVPROC>(
            _loadProcAddr("glVertexAttribI3iv"));
        glVertexAttribI4iv = reinterpret_cast<PFNGLVERTEXATTRIBI4IVPROC>(
            _loadProcAddr("glVertexAttribI4iv"));
        glVertexAttribI1uiv = reinterpret_cast<PFNGLVERTEXATTRIBI1UIVPROC>(
            _loadProcAddr("glVertexAttribI1uiv"));
        glVertexAttribI2uiv = reinterpret_cast<PFNGLVERTEXATTRIBI2UIVPROC>(
            _loadProcAddr("glVertexAttribI2uiv"));
        glVertexAttribI3uiv = reinterpret_cast<PFNGLVERTEXATTRIBI3UIVPROC>(
            _loadProcAddr("glVertexAttribI3uiv"));
        glVertexAttribI4uiv = reinterpret_cast<PFNGLVERTEXATTRIBI4UIVPROC>(
            _loadProcAddr("glVertexAttribI4uiv"));
        glVertexAttribI4bv = reinterpret_cast<PFNGLVERTEXATTRIBI4BVPROC>(
            _loadProcAddr("glVertexAttribI4bv"));
        glVertexAttribI4sv = reinterpret_cast<PFNGLVERTEXATTRIBI4SVPROC>(
            _loadProcAddr("glVertexAttribI4sv"));
        glVertexAttribI4ubv = reinterpret_cast<PFNGLVERTEXATTRIBI4UBVPROC>(
            _loadProcAddr("glVertexAttribI4ubv"));
        glVertexAttribI4usv = reinterpret_cast<PFNGLVERTEXATTRIBI4USVPROC>(
            _loadProcAddr("glVertexAttribI4usv"));
        glGetUniformuiv = reinterpret_cast<PFNGLGETUNIFORMUIVPROC>(
            _loadProcAddr("glGetUniformuiv"));
        glBindFragDataLocation =
            reinterpret_cast<PFNGLBINDFRAGDATALOCATIONPROC>(
                _loadProcAddr("glBindFragDataLocation"));
        glGetFragDataLocation = reinterpret_cast<PFNGLGETFRAGDATALOCATIONPROC>(
            _loadProcAddr("glGetFragDataLocation"));
        glUniform1ui = reinterpret_cast<PFNGLUNIFORM1UIPROC>(
            _loadProcAddr("glUniform1ui"));
        glUniform2ui = reinterpret_cast<PFNGLUNIFORM2UIPROC>(
            _loadProcAddr("glUniform2ui"));
        glUniform3ui = reinterpret_cast<PFNGLUNIFORM3UIPROC>(
            _loadProcAddr("glUniform3ui"));
        glUniform4ui = reinterpret_cast<PFNGLUNIFORM4UIPROC>(
            _loadProcAddr("glUniform4ui"));
        glUniform1uiv = reinterpret_cast<PFNGLUNIFORM1UIVPROC>(
            _loadProcAddr("glUniform1uiv"));
        glUniform2uiv = reinterpret_cast<PFNGLUNIFORM2UIVPROC>(
            _loadProcAddr("glUniform2uiv"));
        glUniform3uiv = reinterpret_cast<PFNGLUNIFORM3UIVPROC>(
            _loadProcAddr("glUniform3uiv"));
        glUniform4uiv = reinterpret_cast<PFNGLUNIFORM4UIVPROC>(
            _loadProcAddr("glUniform4uiv"));
        glTexParameterIiv = reinterpret_cast<PFNGLTEXPARAMETERIIVPROC>(
            _loadProcAddr("glTexParameterIiv"));
        glTexParameterIuiv = reinterpret_cast<PFNGLTEXPARAMETERIUIVPROC>(
            _loadProcAddr("glTexParameterIuiv"));
        glGetTexParameterIiv = reinterpret_cast<PFNGLGETTEXPARAMETERIIVPROC>(
            _loadProcAddr("glGetTexParameterIiv"));
        glGetTexParameterIuiv = reinterpret_cast<PFNGLGETTEXPARAMETERIUIVPROC>(
            _loadProcAddr("glGetTexParameterIuiv"));
        glClearBufferiv = reinterpret_cast<PFNGLCLEARBUFFERIVPROC>(
            _loadProcAddr("glClearBufferiv"));
        glClearBufferuiv = reinterpret_cast<PFNGLCLEARBUFFERUIVPROC>(
            _loadProcAddr("glClearBufferuiv"));
        glClearBufferfv = reinterpret_cast<PFNGLCLEARBUFFERFVPROC>(
            _loadProcAddr("glClearBufferfv"));
        glClearBufferfi = reinterpret_cast<PFNGLCLEARBUFFERFIPROC>(
            _loadProcAddr("glClearBufferfi"));
        glGetStringi = reinterpret_cast<PFNGLGETSTRINGIPROC>(
            _loadProcAddr("glGetStringi"));
        glIsRenderbuffer = reinterpret_cast<PFNGLISRENDERBUFFERPROC>(
            _loadProcAddr("glIsRenderbuffer"));
        glBindRenderbuffer = reinterpret_cast<PFNGLBINDRENDERBUFFERPROC>(
            _loadProcAddr("glBindRenderbuffer"));
        glDeleteRenderbuffers = reinterpret_cast<PFNGLDELETERENDERBUFFERSPROC>(
            _loadProcAddr("glDeleteRenderbuffers"));
        glGenRenderbuffers = reinterpret_cast<PFNGLGENRENDERBUFFERSPROC>(
            _loadProcAddr("glGenRenderbuffers"));
        glRenderbufferStorage = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEPROC>(
            _loadProcAddr("glRenderbufferStorage"));
        glGetRenderbufferParameteriv =
            reinterpret_cast<PFNGLGETRENDERBUFFERPARAMETERIVPROC>(
                _loadProcAddr("glGetRenderbufferParameteriv"));
        glIsFramebuffer = reinterpret_cast<PFNGLISFRAMEBUFFERPROC>(
            _loadProcAddr("glIsFramebuffer"));
        glBindFramebuffer = reinterpret_cast<PFNGLBINDFRAMEBUFFERPROC>(
            _loadProcAddr("glBindFramebuffer"));
        glDeleteFramebuffers = reinterpret_cast<PFNGLDELETEFRAMEBUFFERSPROC>(
            _loadProcAddr("glDeleteFramebuffers"));
        glGenFramebuffers = reinterpret_cast<PFNGLGENFRAMEBUFFERSPROC>(
            _loadProcAddr("glGenFramebuffers"));
        glCheckFramebufferStatus =
            reinterpret_cast<PFNGLCHECKFRAMEBUFFERSTATUSPROC>(
                _loadProcAddr("glCheckFramebufferStatus"));
        glFramebufferTexture1D =
            reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE1DPROC>(
                _loadProcAddr("glFramebufferTexture1D"));
        glFramebufferTexture2D =
            reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE2DPROC>(
                _loadProcAddr("glFramebufferTexture2D"));
        glFramebufferTexture3D =
            reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE3DPROC>(
                _loadProcAddr("glFramebufferTexture3D"));
        glFramebufferRenderbuffer =
            reinterpret_cast<PFNGLFRAMEBUFFERRENDERBUFFERPROC>(
                _loadProcAddr("glFramebufferRenderbuffer"));
        glGetFramebufferAttachmentParameteriv =
            reinterpret_cast<PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC>(
                _loadProcAddr("glGetFramebufferAttachmentParameteriv"));
        glGenerateMipmap = reinterpret_cast<PFNGLGENERATEMIPMAPPROC>(
            _loadProcAddr("glGenerateMipmap"));
        glBlitFramebuffer = reinterpret_cast<PFNGLBLITFRAMEBUFFERPROC>(
            _loadProcAddr("glBlitFramebuffer"));
        glRenderbufferStorageMultisample =
            reinterpret_cast<PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC>(
                _loadProcAddr("glRenderbufferStorageMultisample"));
        glFramebufferTextureLayer =
            reinterpret_cast<PFNGLFRAMEBUFFERTEXTURELAYERPROC>(
                _loadProcAddr("glFramebufferTextureLayer"));
        glMapBufferRange = reinterpret_cast<PFNGLMAPBUFFERRANGEPROC>(
            _loadProcAddr("glMapBufferRange"));
        glFlushMappedBufferRange =
            reinterpret_cast<PFNGLFLUSHMAPPEDBUFFERRANGEPROC>(
                _loadProcAddr("glFlushMappedBufferRange"));
        glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(
            _loadProcAddr("glBindVertexArray"));
        glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(
            _loadProcAddr("glDeleteVertexArrays"));
        glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(
            _loadProcAddr("glGenVertexArrays"));
        glIsVertexArray = reinterpret_cast<PFNGLISVERTEXARRAYPROC>(
            _loadProcAddr("glIsVertexArray"));
#endif /* GL_VERSION_3_0 */
#ifdef GL_VERSION_3_1
        glDrawArraysInstanced = reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDPROC>(
            _loadProcAddr("glDrawArraysInstanced"));
        glDrawElementsInstanced =
            reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDPROC>(
                _loadProcAddr("glDrawElementsInstanced"));
        glTexBuffer =
            reinterpret_cast<PFNGLTEXBUFFERPROC>(_loadProcAddr("glTexBuffer"));
        glPrimitiveRestartIndex =
            reinterpret_cast<PFNGLPRIMITIVERESTARTINDEXPROC>(
                _loadProcAddr("glPrimitiveRestartIndex"));
        glCopyBufferSubData = reinterpret_cast<PFNGLCOPYBUFFERSUBDATAPROC>(
            _loadProcAddr("glCopyBufferSubData"));
        glGetUniformIndices = reinterpret_cast<PFNGLGETUNIFORMINDICESPROC>(
            _loadProcAddr("glGetUniformIndices"));
        glGetActiveUniformsiv = reinterpret_cast<PFNGLGETACTIVEUNIFORMSIVPROC>(
            _loadProcAddr("glGetActiveUniformsiv"));
        glGetActiveUniformName =
            reinterpret_cast<PFNGLGETACTIVEUNIFORMNAMEPROC>(
                _loadProcAddr("glGetActiveUniformName"));
        glGetUniformBlockIndex =
            reinterpret_cast<PFNGLGETUNIFORMBLOCKINDEXPROC>(
                _loadProcAddr("glGetUniformBlockIndex"));
        glGetActiveUniformBlockiv =
            reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKIVPROC>(
                _loadProcAddr("glGetActiveUniformBlockiv"));
        glGetActiveUniformBlockName =
            reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC>(
                _loadProcAddr("glGetActiveUniformBlockName"));
        glUniformBlockBinding = reinterpret_cast<PFNGLUNIFORMBLOCKBINDINGPROC>(
            _loadProcAddr("glUniformBlockBinding"));
#endif /* GL_VERSION_3_1 */
#ifdef GL_VERSION_3_2
        glDrawElementsBaseVertex =
            reinterpret_cast<PFNGLDRAWELEMENTSBASEVERTEXPROC>(
                _loadProcAddr("glDrawElementsBaseVertex"));
        glDrawRangeElementsBaseVertex =
            reinterpret_cast<PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC>(
                _loadProcAddr("glDrawRangeElementsBaseVertex"));
        glDrawElementsInstancedBaseVertex =
            reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC>(
                _loadProcAddr("glDrawElementsInstancedBaseVertex"));
        glMultiDrawElementsBaseVertex =
            reinterpret_cast<PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC>(
                _loadProcAddr("glMultiDrawElementsBaseVertex"));
        glProvokingVertex = reinterpret_cast<PFNGLPROVOKINGVERTEXPROC>(
            _loadProcAddr("glProvokingVertex"));
        glFenceSync =
            reinterpret_cast<PFNGLFENCESYNCPROC>(_loadProcAddr("glFenceSync"));
        glIsSync = reinterpret_cast<PFNGLISSYNCPROC>(_loadProcAddr("glIsSync"));
        glDeleteSync = reinterpret_cast<PFNGLDELETESYNCPROC>(
            _loadProcAddr("glDeleteSync"));
        glClientWaitSync = reinterpret_cast<PFNGLCLIENTWAITSYNCPROC>(
            _loadProcAddr("glClientWaitSync"));
        glWaitSync =
            reinterpret_cast<PFNGLWAITSYNCPROC>(_loadProcAddr("glWaitSync"));
        glGetInteger64v = reinterpret_cast<PFNGLGETINTEGER64VPROC>(
            _loadProcAddr("glGetInteger64v"));
        glGetSynciv =
            reinterpret_cast<PFNGLGETSYNCIVPROC>(_loadProcAddr("glGetSynciv"));
        glGetInteger64i_v = reinterpret_cast<PFNGLGETINTEGER64I_VPROC>(
            _loadProcAddr("glGetInteger64i_v"));
        glGetBufferParameteri64v =
            reinterpret_cast<PFNGLGETBUFFERPARAMETERI64VPROC>(
                _loadProcAddr("glGetBufferParameteri64v"));
        glFramebufferTexture = reinterpret_cast<PFNGLFRAMEBUFFERTEXTUREPROC>(
            _loadProcAddr("glFramebufferTexture"));
        glTexImage2DMultisample =
            reinterpret_cast<PFNGLTEXIMAGE2DMULTISAMPLEPROC>(
                _loadProcAddr("glTexImage2DMultisample"));
        glTexImage3DMultisample =
            reinterpret_cast<PFNGLTEXIMAGE3DMULTISAMPLEPROC>(
                _loadProcAddr("glTexImage3DMultisample"));
        glGetMultisamplefv = reinterpret_cast<PFNGLGETMULTISAMPLEFVPROC>(
            _loadProcAddr("glGetMultisamplefv"));
        glSampleMaski = reinterpret_cast<PFNGLSAMPLEMASKIPROC>(
            _loadProcAddr("glSampleMaski"));
#endif /* GL_VERSION_3_2 */
#ifdef GL_VERSION_3_3
        glBindFragDataLocationIndexed =
            reinterpret_cast<PFNGLBINDFRAGDATALOCATIONINDEXEDPROC>(
                _loadProcAddr("glBindFragDataLocationIndexed"));
        glGetFragDataIndex = reinterpret_cast<PFNGLGETFRAGDATAINDEXPROC>(
            _loadProcAddr("glGetFragDataIndex"));
        glGenSamplers = reinterpret_cast<PFNGLGENSAMPLERSPROC>(
            _loadProcAddr("glGenSamplers"));
        glDeleteSamplers = reinterpret_cast<PFNGLDELETESAMPLERSPROC>(
            _loadProcAddr("glDeleteSamplers"));
        glIsSampler =
            reinterpret_cast<PFNGLISSAMPLERPROC>(_loadProcAddr("glIsSampler"));
        glBindSampler = reinterpret_cast<PFNGLBINDSAMPLERPROC>(
            _loadProcAddr("glBindSampler"));
        glSamplerParameteri = reinterpret_cast<PFNGLSAMPLERPARAMETERIPROC>(
            _loadProcAddr("glSamplerParameteri"));
        glSamplerParameteriv = reinterpret_cast<PFNGLSAMPLERPARAMETERIVPROC>(
            _loadProcAddr("glSamplerParameteriv"));
        glSamplerParameterf = reinterpret_cast<PFNGLSAMPLERPARAMETERFPROC>(
            _loadProcAddr("glSamplerParameterf"));
        glSamplerParameterfv = reinterpret_cast<PFNGLSAMPLERPARAMETERFVPROC>(
            _loadProcAddr("glSamplerParameterfv"));
        glSamplerParameterIiv = reinterpret_cast<PFNGLSAMPLERPARAMETERIIVPROC>(
            _loadProcAddr("glSamplerParameterIiv"));
        glSamplerParameterIuiv =
            reinterpret_cast<PFNGLSAMPLERPARAMETERIUIVPROC>(
                _loadProcAddr("glSamplerParameterIuiv"));
        glGetSamplerParameteriv =
            reinterpret_cast<PFNGLGETSAMPLERPARAMETERIVPROC>(
                _loadProcAddr("glGetSamplerParameteriv"));
        glGetSamplerParameterIiv =
            reinterpret_cast<PFNGLGETSAMPLERPARAMETERIIVPROC>(
                _loadProcAddr("glGetSamplerParameterIiv"));
        glGetSamplerParameterfv =
            reinterpret_cast<PFNGLGETSAMPLERPARAMETERFVPROC>(
                _loadProcAddr("glGetSamplerParameterfv"));
        glGetSamplerParameterIuiv =
            reinterpret_cast<PFNGLGETSAMPLERPARAMETERIUIVPROC>(
                _loadProcAddr("glGetSamplerParameterIuiv"));
        glQueryCounter = reinterpret_cast<PFNGLQUERYCOUNTERPROC>(
            _loadProcAddr("glQueryCounter"));
        glGetQueryObjecti64v = reinterpret_cast<PFNGLGETQUERYOBJECTI64VPROC>(
            _loadProcAddr("glGetQueryObjecti64v"));
        glGetQueryObjectui64v = reinterpret_cast<PFNGLGETQUERYOBJECTUI64VPROC>(
            _loadProcAddr("glGetQueryObjectui64v"));
        glVertexAttribDivisor = reinterpret_cast<PFNGLVERTEXATTRIBDIVISORPROC>(
            _loadProcAddr("glVertexAttribDivisor"));
        glVertexAttribP1ui = reinterpret_cast<PFNGLVERTEXATTRIBP1UIPROC>(
            _loadProcAddr("glVertexAttribP1ui"));
        glVertexAttribP1uiv = reinterpret_cast<PFNGLVERTEXATTRIBP1UIVPROC>(
            _loadProcAddr("glVertexAttribP1uiv"));
        glVertexAttribP2ui = reinterpret_cast<PFNGLVERTEXATTRIBP2UIPROC>(
            _loadProcAddr("glVertexAttribP2ui"));
        glVertexAttribP2uiv = reinterpret_cast<PFNGLVERTEXATTRIBP2UIVPROC>(
            _loadProcAddr("glVertexAttribP2uiv"));
        glVertexAttribP3ui = reinterpret_cast<PFNGLVERTEXATTRIBP3UIPROC>(
            _loadProcAddr("glVertexAttribP3ui"));
        glVertexAttribP3uiv = reinterpret_cast<PFNGLVERTEXATTRIBP3UIVPROC>(
            _loadProcAddr("glVertexAttribP3uiv"));
        glVertexAttribP4ui = reinterpret_cast<PFNGLVERTEXATTRIBP4UIPROC>(
            _loadProcAddr("glVertexAttribP4ui"));
        glVertexAttribP4uiv = reinterpret_cast<PFNGLVERTEXATTRIBP4UIVPROC>(
            _loadProcAddr("glVertexAttribP4uiv"));
#endif /* GL_VERSION_3_3 */
#ifdef GL_VERSION_4_0
        glMinSampleShading = reinterpret_cast<PFNGLMINSAMPLESHADINGPROC>(
            _loadProcAddr("glMinSampleShading"));
        glBlendEquationi = reinterpret_cast<PFNGLBLENDEQUATIONIPROC>(
            _loadProcAddr("glBlendEquationi"));
        glBlendEquationSeparatei =
            reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEIPROC>(
                _loadProcAddr("glBlendEquationSeparatei"));
        glBlendFunci = reinterpret_cast<PFNGLBLENDFUNCIPROC>(
            _loadProcAddr("glBlendFunci"));
        glBlendFuncSeparatei = reinterpret_cast<PFNGLBLENDFUNCSEPARATEIPROC>(
            _loadProcAddr("glBlendFuncSeparatei"));
        glDrawArraysIndirect = reinterpret_cast<PFNGLDRAWARRAYSINDIRECTPROC>(
            _loadProcAddr("glDrawArraysIndirect"));
        glDrawElementsIndirect =
            reinterpret_cast<PFNGLDRAWELEMENTSINDIRECTPROC>(
                _loadProcAddr("glDrawElementsIndirect"));
        glUniform1d =
            reinterpret_cast<PFNGLUNIFORM1DPROC>(_loadProcAddr("glUniform1d"));
        glUniform2d =
            reinterpret_cast<PFNGLUNIFORM2DPROC>(_loadProcAddr("glUniform2d"));
        glUniform3d =
            reinterpret_cast<PFNGLUNIFORM3DPROC>(_loadProcAddr("glUniform3d"));
        glUniform4d =
            reinterpret_cast<PFNGLUNIFORM4DPROC>(_loadProcAddr("glUniform4d"));
        glUniform1dv = reinterpret_cast<PFNGLUNIFORM1DVPROC>(
            _loadProcAddr("glUniform1dv"));
        glUniform2dv = reinterpret_cast<PFNGLUNIFORM2DVPROC>(
            _loadProcAddr("glUniform2dv"));
        glUniform3dv = reinterpret_cast<PFNGLUNIFORM3DVPROC>(
            _loadProcAddr("glUniform3dv"));
        glUniform4dv = reinterpret_cast<PFNGLUNIFORM4DVPROC>(
            _loadProcAddr("glUniform4dv"));
        glUniformMatrix2dv = reinterpret_cast<PFNGLUNIFORMMATRIX2DVPROC>(
            _loadProcAddr("glUniformMatrix2dv"));
        glUniformMatrix3dv = reinterpret_cast<PFNGLUNIFORMMATRIX3DVPROC>(
            _loadProcAddr("glUniformMatrix3dv"));
        glUniformMatrix4dv = reinterpret_cast<PFNGLUNIFORMMATRIX4DVPROC>(
            _loadProcAddr("glUniformMatrix4dv"));
        glUniformMatrix2x3dv = reinterpret_cast<PFNGLUNIFORMMATRIX2X3DVPROC>(
            _loadProcAddr("glUniformMatrix2x3dv"));
        glUniformMatrix2x4dv = reinterpret_cast<PFNGLUNIFORMMATRIX2X4DVPROC>(
            _loadProcAddr("glUniformMatrix2x4dv"));
        glUniformMatrix3x2dv = reinterpret_cast<PFNGLUNIFORMMATRIX3X2DVPROC>(
            _loadProcAddr("glUniformMatrix3x2dv"));
        glUniformMatrix3x4dv = reinterpret_cast<PFNGLUNIFORMMATRIX3X4DVPROC>(
            _loadProcAddr("glUniformMatrix3x4dv"));
        glUniformMatrix4x2dv = reinterpret_cast<PFNGLUNIFORMMATRIX4X2DVPROC>(
            _loadProcAddr("glUniformMatrix4x2dv"));
        glUniformMatrix4x3dv = reinterpret_cast<PFNGLUNIFORMMATRIX4X3DVPROC>(
            _loadProcAddr("glUniformMatrix4x3dv"));
        glGetUniformdv = reinterpret_cast<PFNGLGETUNIFORMDVPROC>(
            _loadProcAddr("glGetUniformdv"));
        glGetSubroutineUniformLocation =
            reinterpret_cast<PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC>(
                _loadProcAddr("glGetSubroutineUniformLocation"));
        glGetSubroutineIndex = reinterpret_cast<PFNGLGETSUBROUTINEINDEXPROC>(
            _loadProcAddr("glGetSubroutineIndex"));
        glGetActiveSubroutineUniformiv =
            reinterpret_cast<PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC>(
                _loadProcAddr("glGetActiveSubroutineUniformiv"));
        glGetActiveSubroutineUniformName =
            reinterpret_cast<PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC>(
                _loadProcAddr("glGetActiveSubroutineUniformName"));
        glGetActiveSubroutineName =
            reinterpret_cast<PFNGLGETACTIVESUBROUTINENAMEPROC>(
                _loadProcAddr("glGetActiveSubroutineName"));
        glUniformSubroutinesuiv =
            reinterpret_cast<PFNGLUNIFORMSUBROUTINESUIVPROC>(
                _loadProcAddr("glUniformSubroutinesuiv"));
        glGetUniformSubroutineuiv =
            reinterpret_cast<PFNGLGETUNIFORMSUBROUTINEUIVPROC>(
                _loadProcAddr("glGetUniformSubroutineuiv"));
        glGetProgramStageiv = reinterpret_cast<PFNGLGETPROGRAMSTAGEIVPROC>(
            _loadProcAddr("glGetProgramStageiv"));
        glPatchParameteri = reinterpret_cast<PFNGLPATCHPARAMETERIPROC>(
            _loadProcAddr("glPatchParameteri"));
        glPatchParameterfv = reinterpret_cast<PFNGLPATCHPARAMETERFVPROC>(
            _loadProcAddr("glPatchParameterfv"));
        glBindTransformFeedback =
            reinterpret_cast<PFNGLBINDTRANSFORMFEEDBACKPROC>(
                _loadProcAddr("glBindTransformFeedback"));
        glDeleteTransformFeedbacks =
            reinterpret_cast<PFNGLDELETETRANSFORMFEEDBACKSPROC>(
                _loadProcAddr("glDeleteTransformFeedbacks"));
        glGenTransformFeedbacks =
            reinterpret_cast<PFNGLGENTRANSFORMFEEDBACKSPROC>(
                _loadProcAddr("glGenTransformFeedbacks"));
        glIsTransformFeedback = reinterpret_cast<PFNGLISTRANSFORMFEEDBACKPROC>(
            _loadProcAddr("glIsTransformFeedback"));
        glPauseTransformFeedback =
            reinterpret_cast<PFNGLPAUSETRANSFORMFEEDBACKPROC>(
                _loadProcAddr("glPauseTransformFeedback"));
        glResumeTransformFeedback =
            reinterpret_cast<PFNGLRESUMETRANSFORMFEEDBACKPROC>(
                _loadProcAddr("glResumeTransformFeedback"));
        glDrawTransformFeedback =
            reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKPROC>(
                _loadProcAddr("glDrawTransformFeedback"));
        glDrawTransformFeedbackStream =
            reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC>(
                _loadProcAddr("glDrawTransformFeedbackStream"));
        glBeginQueryIndexed = reinterpret_cast<PFNGLBEGINQUERYINDEXEDPROC>(
            _loadProcAddr("glBeginQueryIndexed"));
        glEndQueryIndexed = reinterpret_cast<PFNGLENDQUERYINDEXEDPROC>(
            _loadProcAddr("glEndQueryIndexed"));
        glGetQueryIndexediv = reinterpret_cast<PFNGLGETQUERYINDEXEDIVPROC>(
            _loadProcAddr("glGetQueryIndexediv"));
#endif /* GL_VERSION_4_0 */
#ifdef GL_VERSION_4_1
        glReleaseShaderCompiler =
            reinterpret_cast<PFNGLRELEASESHADERCOMPILERPROC>(
                _loadProcAddr("glReleaseShaderCompiler"));
        glShaderBinary = reinterpret_cast<PFNGLSHADERBINARYPROC>(
            _loadProcAddr("glShaderBinary"));
        glGetShaderPrecisionFormat =
            reinterpret_cast<PFNGLGETSHADERPRECISIONFORMATPROC>(
                _loadProcAddr("glGetShaderPrecisionFormat"));
        glDepthRangef = reinterpret_cast<PFNGLDEPTHRANGEFPROC>(
            _loadProcAddr("glDepthRangef"));
        glClearDepthf = reinterpret_cast<PFNGLCLEARDEPTHFPROC>(
            _loadProcAddr("glClearDepthf"));
        glGetProgramBinary = reinterpret_cast<PFNGLGETPROGRAMBINARYPROC>(
            _loadProcAddr("glGetProgramBinary"));
        glProgramBinary = reinterpret_cast<PFNGLPROGRAMBINARYPROC>(
            _loadProcAddr("glProgramBinary"));
        glProgramParameteri = reinterpret_cast<PFNGLPROGRAMPARAMETERIPROC>(
            _loadProcAddr("glProgramParameteri"));
        glUseProgramStages = reinterpret_cast<PFNGLUSEPROGRAMSTAGESPROC>(
            _loadProcAddr("glUseProgramStages"));
        glActiveShaderProgram = reinterpret_cast<PFNGLACTIVESHADERPROGRAMPROC>(
            _loadProcAddr("glActiveShaderProgram"));
        glCreateShaderProgramv =
            reinterpret_cast<PFNGLCREATESHADERPROGRAMVPROC>(
                _loadProcAddr("glCreateShaderProgramv"));
        glBindProgramPipeline = reinterpret_cast<PFNGLBINDPROGRAMPIPELINEPROC>(
            _loadProcAddr("glBindProgramPipeline"));
        glDeleteProgramPipelines =
            reinterpret_cast<PFNGLDELETEPROGRAMPIPELINESPROC>(
                _loadProcAddr("glDeleteProgramPipelines"));
        glGenProgramPipelines = reinterpret_cast<PFNGLGENPROGRAMPIPELINESPROC>(
            _loadProcAddr("glGenProgramPipelines"));
        glIsProgramPipeline = reinterpret_cast<PFNGLISPROGRAMPIPELINEPROC>(
            _loadProcAddr("glIsProgramPipeline"));
        glGetProgramPipelineiv =
            reinterpret_cast<PFNGLGETPROGRAMPIPELINEIVPROC>(
                _loadProcAddr("glGetProgramPipelineiv"));
        glProgramUniform1i = reinterpret_cast<PFNGLPROGRAMUNIFORM1IPROC>(
            _loadProcAddr("glProgramUniform1i"));
        glProgramUniform1iv = reinterpret_cast<PFNGLPROGRAMUNIFORM1IVPROC>(
            _loadProcAddr("glProgramUniform1iv"));
        glProgramUniform1f = reinterpret_cast<PFNGLPROGRAMUNIFORM1FPROC>(
            _loadProcAddr("glProgramUniform1f"));
        glProgramUniform1fv = reinterpret_cast<PFNGLPROGRAMUNIFORM1FVPROC>(
            _loadProcAddr("glProgramUniform1fv"));
        glProgramUniform1d = reinterpret_cast<PFNGLPROGRAMUNIFORM1DPROC>(
            _loadProcAddr("glProgramUniform1d"));
        glProgramUniform1dv = reinterpret_cast<PFNGLPROGRAMUNIFORM1DVPROC>(
            _loadProcAddr("glProgramUniform1dv"));
        glProgramUniform1ui = reinterpret_cast<PFNGLPROGRAMUNIFORM1UIPROC>(
            _loadProcAddr("glProgramUniform1ui"));
        glProgramUniform1uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM1UIVPROC>(
            _loadProcAddr("glProgramUniform1uiv"));
        glProgramUniform2i = reinterpret_cast<PFNGLPROGRAMUNIFORM2IPROC>(
            _loadProcAddr("glProgramUniform2i"));
        glProgramUniform2iv = reinterpret_cast<PFNGLPROGRAMUNIFORM2IVPROC>(
            _loadProcAddr("glProgramUniform2iv"));
        glProgramUniform2f = reinterpret_cast<PFNGLPROGRAMUNIFORM2FPROC>(
            _loadProcAddr("glProgramUniform2f"));
        glProgramUniform2fv = reinterpret_cast<PFNGLPROGRAMUNIFORM2FVPROC>(
            _loadProcAddr("glProgramUniform2fv"));
        glProgramUniform2d = reinterpret_cast<PFNGLPROGRAMUNIFORM2DPROC>(
            _loadProcAddr("glProgramUniform2d"));
        glProgramUniform2dv = reinterpret_cast<PFNGLPROGRAMUNIFORM2DVPROC>(
            _loadProcAddr("glProgramUniform2dv"));
        glProgramUniform2ui = reinterpret_cast<PFNGLPROGRAMUNIFORM2UIPROC>(
            _loadProcAddr("glProgramUniform2ui"));
        glProgramUniform2uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM2UIVPROC>(
            _loadProcAddr("glProgramUniform2uiv"));
        glProgramUniform3i = reinterpret_cast<PFNGLPROGRAMUNIFORM3IPROC>(
            _loadProcAddr("glProgramUniform3i"));
        glProgramUniform3iv = reinterpret_cast<PFNGLPROGRAMUNIFORM3IVPROC>(
            _loadProcAddr("glProgramUniform3iv"));
        glProgramUniform3f = reinterpret_cast<PFNGLPROGRAMUNIFORM3FPROC>(
            _loadProcAddr("glProgramUniform3f"));
        glProgramUniform3fv = reinterpret_cast<PFNGLPROGRAMUNIFORM3FVPROC>(
            _loadProcAddr("glProgramUniform3fv"));
        glProgramUniform3d = reinterpret_cast<PFNGLPROGRAMUNIFORM3DPROC>(
            _loadProcAddr("glProgramUniform3d"));
        glProgramUniform3dv = reinterpret_cast<PFNGLPROGRAMUNIFORM3DVPROC>(
            _loadProcAddr("glProgramUniform3dv"));
        glProgramUniform3ui = reinterpret_cast<PFNGLPROGRAMUNIFORM3UIPROC>(
            _loadProcAddr("glProgramUniform3ui"));
        glProgramUniform3uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM3UIVPROC>(
            _loadProcAddr("glProgramUniform3uiv"));
        glProgramUniform4i = reinterpret_cast<PFNGLPROGRAMUNIFORM4IPROC>(
            _loadProcAddr("glProgramUniform4i"));
        glProgramUniform4iv = reinterpret_cast<PFNGLPROGRAMUNIFORM4IVPROC>(
            _loadProcAddr("glProgramUniform4iv"));
        glProgramUniform4f = reinterpret_cast<PFNGLPROGRAMUNIFORM4FPROC>(
            _loadProcAddr("glProgramUniform4f"));
        glProgramUniform4fv = reinterpret_cast<PFNGLPROGRAMUNIFORM4FVPROC>(
            _loadProcAddr("glProgramUniform4fv"));
        glProgramUniform4d = reinterpret_cast<PFNGLPROGRAMUNIFORM4DPROC>(
            _loadProcAddr("glProgramUniform4d"));
        glProgramUniform4dv = reinterpret_cast<PFNGLPROGRAMUNIFORM4DVPROC>(
            _loadProcAddr("glProgramUniform4dv"));
        glProgramUniform4ui = reinterpret_cast<PFNGLPROGRAMUNIFORM4UIPROC>(
            _loadProcAddr("glProgramUniform4ui"));
        glProgramUniform4uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM4UIVPROC>(
            _loadProcAddr("glProgramUniform4uiv"));
        glProgramUniformMatrix2fv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2FVPROC>(
                _loadProcAddr("glProgramUniformMatrix2fv"));
        glProgramUniformMatrix3fv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3FVPROC>(
                _loadProcAddr("glProgramUniformMatrix3fv"));
        glProgramUniformMatrix4fv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4FVPROC>(
                _loadProcAddr("glProgramUniformMatrix4fv"));
        glProgramUniformMatrix2dv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2DVPROC>(
                _loadProcAddr("glProgramUniformMatrix2dv"));
        glProgramUniformMatrix3dv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3DVPROC>(
                _loadProcAddr("glProgramUniformMatrix3dv"));
        glProgramUniformMatrix4dv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4DVPROC>(
                _loadProcAddr("glProgramUniformMatrix4dv"));
        glProgramUniformMatrix2x3fv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC>(
                _loadProcAddr("glProgramUniformMatrix2x3fv"));
        glProgramUniformMatrix3x2fv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC>(
                _loadProcAddr("glProgramUniformMatrix3x2fv"));
        glProgramUniformMatrix2x4fv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC>(
                _loadProcAddr("glProgramUniformMatrix2x4fv"));
        glProgramUniformMatrix4x2fv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC>(
                _loadProcAddr("glProgramUniformMatrix4x2fv"));
        glProgramUniformMatrix3x4fv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC>(
                _loadProcAddr("glProgramUniformMatrix3x4fv"));
        glProgramUniformMatrix4x3fv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC>(
                _loadProcAddr("glProgramUniformMatrix4x3fv"));
        glProgramUniformMatrix2x3dv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC>(
                _loadProcAddr("glProgramUniformMatrix2x3dv"));
        glProgramUniformMatrix3x2dv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC>(
                _loadProcAddr("glProgramUniformMatrix3x2dv"));
        glProgramUniformMatrix2x4dv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC>(
                _loadProcAddr("glProgramUniformMatrix2x4dv"));
        glProgramUniformMatrix4x2dv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC>(
                _loadProcAddr("glProgramUniformMatrix4x2dv"));
        glProgramUniformMatrix3x4dv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC>(
                _loadProcAddr("glProgramUniformMatrix3x4dv"));
        glProgramUniformMatrix4x3dv =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC>(
                _loadProcAddr("glProgramUniformMatrix4x3dv"));
        glValidateProgramPipeline =
            reinterpret_cast<PFNGLVALIDATEPROGRAMPIPELINEPROC>(
                _loadProcAddr("glValidateProgramPipeline"));
        glGetProgramPipelineInfoLog =
            reinterpret_cast<PFNGLGETPROGRAMPIPELINEINFOLOGPROC>(
                _loadProcAddr("glGetProgramPipelineInfoLog"));
        glVertexAttribL1d = reinterpret_cast<PFNGLVERTEXATTRIBL1DPROC>(
            _loadProcAddr("glVertexAttribL1d"));
        glVertexAttribL2d = reinterpret_cast<PFNGLVERTEXATTRIBL2DPROC>(
            _loadProcAddr("glVertexAttribL2d"));
        glVertexAttribL3d = reinterpret_cast<PFNGLVERTEXATTRIBL3DPROC>(
            _loadProcAddr("glVertexAttribL3d"));
        glVertexAttribL4d = reinterpret_cast<PFNGLVERTEXATTRIBL4DPROC>(
            _loadProcAddr("glVertexAttribL4d"));
        glVertexAttribL1dv = reinterpret_cast<PFNGLVERTEXATTRIBL1DVPROC>(
            _loadProcAddr("glVertexAttribL1dv"));
        glVertexAttribL2dv = reinterpret_cast<PFNGLVERTEXATTRIBL2DVPROC>(
            _loadProcAddr("glVertexAttribL2dv"));
        glVertexAttribL3dv = reinterpret_cast<PFNGLVERTEXATTRIBL3DVPROC>(
            _loadProcAddr("glVertexAttribL3dv"));
        glVertexAttribL4dv = reinterpret_cast<PFNGLVERTEXATTRIBL4DVPROC>(
            _loadProcAddr("glVertexAttribL4dv"));
        glVertexAttribLPointer =
            reinterpret_cast<PFNGLVERTEXATTRIBLPOINTERPROC>(
                _loadProcAddr("glVertexAttribLPointer"));
        glGetVertexAttribLdv = reinterpret_cast<PFNGLGETVERTEXATTRIBLDVPROC>(
            _loadProcAddr("glGetVertexAttribLdv"));
        glViewportArrayv = reinterpret_cast<PFNGLVIEWPORTARRAYVPROC>(
            _loadProcAddr("glViewportArrayv"));
        glViewportIndexedf = reinterpret_cast<PFNGLVIEWPORTINDEXEDFPROC>(
            _loadProcAddr("glViewportIndexedf"));
        glViewportIndexedfv = reinterpret_cast<PFNGLVIEWPORTINDEXEDFVPROC>(
            _loadProcAddr("glViewportIndexedfv"));
        glScissorArrayv = reinterpret_cast<PFNGLSCISSORARRAYVPROC>(
            _loadProcAddr("glScissorArrayv"));
        glScissorIndexed = reinterpret_cast<PFNGLSCISSORINDEXEDPROC>(
            _loadProcAddr("glScissorIndexed"));
        glScissorIndexedv = reinterpret_cast<PFNGLSCISSORINDEXEDVPROC>(
            _loadProcAddr("glScissorIndexedv"));
        glDepthRangeArrayv = reinterpret_cast<PFNGLDEPTHRANGEARRAYVPROC>(
            _loadProcAddr("glDepthRangeArrayv"));
        glDepthRangeIndexed = reinterpret_cast<PFNGLDEPTHRANGEINDEXEDPROC>(
            _loadProcAddr("glDepthRangeIndexed"));
        glGetFloati_v = reinterpret_cast<PFNGLGETFLOATI_VPROC>(
            _loadProcAddr("glGetFloati_v"));
        glGetDoublei_v = reinterpret_cast<PFNGLGETDOUBLEI_VPROC>(
            _loadProcAddr("glGetDoublei_v"));
#endif /* GL_VERSION_4_1 */
#ifdef GL_VERSION_4_2
        glDrawArraysInstancedBaseInstance =
            reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC>(
                _loadProcAddr("glDrawArraysInstancedBaseInstance"));
        glDrawElementsInstancedBaseInstance =
            reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC>(
                _loadProcAddr("glDrawElementsInstancedBaseInstance"));
        glDrawElementsInstancedBaseVertexBaseInstance = reinterpret_cast<
            PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC>(
            _loadProcAddr("glDrawElementsInstancedBaseVertexBaseInstance"));
        glGetInternalformativ = reinterpret_cast<PFNGLGETINTERNALFORMATIVPROC>(
            _loadProcAddr("glGetInternalformativ"));
        glGetActiveAtomicCounterBufferiv =
            reinterpret_cast<PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC>(
                _loadProcAddr("glGetActiveAtomicCounterBufferiv"));
        glBindImageTexture = reinterpret_cast<PFNGLBINDIMAGETEXTUREPROC>(
            _loadProcAddr("glBindImageTexture"));
        glMemoryBarrier = reinterpret_cast<PFNGLMEMORYBARRIERPROC>(
            _loadProcAddr("glMemoryBarrier"));
        glTexStorage1D = reinterpret_cast<PFNGLTEXSTORAGE1DPROC>(
            _loadProcAddr("glTexStorage1D"));
        glTexStorage2D = reinterpret_cast<PFNGLTEXSTORAGE2DPROC>(
            _loadProcAddr("glTexStorage2D"));
        glTexStorage3D = reinterpret_cast<PFNGLTEXSTORAGE3DPROC>(
            _loadProcAddr("glTexStorage3D"));
        glDrawTransformFeedbackInstanced =
            reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC>(
                _loadProcAddr("glDrawTransformFeedbackInstanced"));
        glDrawTransformFeedbackStreamInstanced =
            reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC>(
                _loadProcAddr("glDrawTransformFeedbackStreamInstanced"));
#endif /* GL_VERSION_4_2 */
#ifdef GL_VERSION_4_3
        glClearBufferData = reinterpret_cast<PFNGLCLEARBUFFERDATAPROC>(
            _loadProcAddr("glClearBufferData"));
        glClearBufferSubData = reinterpret_cast<PFNGLCLEARBUFFERSUBDATAPROC>(
            _loadProcAddr("glClearBufferSubData"));
        glDispatchCompute = reinterpret_cast<PFNGLDISPATCHCOMPUTEPROC>(
            _loadProcAddr("glDispatchCompute"));
        glDispatchComputeIndirect =
            reinterpret_cast<PFNGLDISPATCHCOMPUTEINDIRECTPROC>(
                _loadProcAddr("glDispatchComputeIndirect"));
        glCopyImageSubData = reinterpret_cast<PFNGLCOPYIMAGESUBDATAPROC>(
            _loadProcAddr("glCopyImageSubData"));
        glFramebufferParameteri =
            reinterpret_cast<PFNGLFRAMEBUFFERPARAMETERIPROC>(
                _loadProcAddr("glFramebufferParameteri"));
        glGetFramebufferParameteriv =
            reinterpret_cast<PFNGLGETFRAMEBUFFERPARAMETERIVPROC>(
                _loadProcAddr("glGetFramebufferParameteriv"));
        glGetInternalformati64v =
            reinterpret_cast<PFNGLGETINTERNALFORMATI64VPROC>(
                _loadProcAddr("glGetInternalformati64v"));
        glInvalidateTexSubImage =
            reinterpret_cast<PFNGLINVALIDATETEXSUBIMAGEPROC>(
                _loadProcAddr("glInvalidateTexSubImage"));
        glInvalidateTexImage = reinterpret_cast<PFNGLINVALIDATETEXIMAGEPROC>(
            _loadProcAddr("glInvalidateTexImage"));
        glInvalidateBufferSubData =
            reinterpret_cast<PFNGLINVALIDATEBUFFERSUBDATAPROC>(
                _loadProcAddr("glInvalidateBufferSubData"));
        glInvalidateBufferData =
            reinterpret_cast<PFNGLINVALIDATEBUFFERDATAPROC>(
                _loadProcAddr("glInvalidateBufferData"));
        glInvalidateFramebuffer =
            reinterpret_cast<PFNGLINVALIDATEFRAMEBUFFERPROC>(
                _loadProcAddr("glInvalidateFramebuffer"));
        glInvalidateSubFramebuffer =
            reinterpret_cast<PFNGLINVALIDATESUBFRAMEBUFFERPROC>(
                _loadProcAddr("glInvalidateSubFramebuffer"));
        glMultiDrawArraysIndirect =
            reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTPROC>(
                _loadProcAddr("glMultiDrawArraysIndirect"));
        glMultiDrawElementsIndirect =
            reinterpret_cast<PFNGLMULTIDRAWELEMENTSINDIRECTPROC>(
                _loadProcAddr("glMultiDrawElementsIndirect"));
        glGetProgramInterfaceiv =
            reinterpret_cast<PFNGLGETPROGRAMINTERFACEIVPROC>(
                _loadProcAddr("glGetProgramInterfaceiv"));
        glGetProgramResourceIndex =
            reinterpret_cast<PFNGLGETPROGRAMRESOURCEINDEXPROC>(
                _loadProcAddr("glGetProgramResourceIndex"));
        glGetProgramResourceName =
            reinterpret_cast<PFNGLGETPROGRAMRESOURCENAMEPROC>(
                _loadProcAddr("glGetProgramResourceName"));
        glGetProgramResourceiv =
            reinterpret_cast<PFNGLGETPROGRAMRESOURCEIVPROC>(
                _loadProcAddr("glGetProgramResourceiv"));
        glGetProgramResourceLocation =
            reinterpret_cast<PFNGLGETPROGRAMRESOURCELOCATIONPROC>(
                _loadProcAddr("glGetProgramResourceLocation"));
        glGetProgramResourceLocationIndex =
            reinterpret_cast<PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC>(
                _loadProcAddr("glGetProgramResourceLocationIndex"));
        glShaderStorageBlockBinding =
            reinterpret_cast<PFNGLSHADERSTORAGEBLOCKBINDINGPROC>(
                _loadProcAddr("glShaderStorageBlockBinding"));
        glTexBufferRange = reinterpret_cast<PFNGLTEXBUFFERRANGEPROC>(
            _loadProcAddr("glTexBufferRange"));
        glTexStorage2DMultisample =
            reinterpret_cast<PFNGLTEXSTORAGE2DMULTISAMPLEPROC>(
                _loadProcAddr("glTexStorage2DMultisample"));
        glTexStorage3DMultisample =
            reinterpret_cast<PFNGLTEXSTORAGE3DMULTISAMPLEPROC>(
                _loadProcAddr("glTexStorage3DMultisample"));
        glTextureView = reinterpret_cast<PFNGLTEXTUREVIEWPROC>(
            _loadProcAddr("glTextureView"));
        glBindVertexBuffer = reinterpret_cast<PFNGLBINDVERTEXBUFFERPROC>(
            _loadProcAddr("glBindVertexBuffer"));
        glVertexAttribFormat = reinterpret_cast<PFNGLVERTEXATTRIBFORMATPROC>(
            _loadProcAddr("glVertexAttribFormat"));
        glVertexAttribIFormat = reinterpret_cast<PFNGLVERTEXATTRIBIFORMATPROC>(
            _loadProcAddr("glVertexAttribIFormat"));
        glVertexAttribLFormat = reinterpret_cast<PFNGLVERTEXATTRIBLFORMATPROC>(
            _loadProcAddr("glVertexAttribLFormat"));
        glVertexAttribBinding = reinterpret_cast<PFNGLVERTEXATTRIBBINDINGPROC>(
            _loadProcAddr("glVertexAttribBinding"));
        glVertexBindingDivisor =
            reinterpret_cast<PFNGLVERTEXBINDINGDIVISORPROC>(
                _loadProcAddr("glVertexBindingDivisor"));
        glDebugMessageControl = reinterpret_cast<PFNGLDEBUGMESSAGECONTROLPROC>(
            _loadProcAddr("glDebugMessageControl"));
        glDebugMessageInsert = reinterpret_cast<PFNGLDEBUGMESSAGEINSERTPROC>(
            _loadProcAddr("glDebugMessageInsert"));
        glDebugMessageCallback =
            reinterpret_cast<PFNGLDEBUGMESSAGECALLBACKPROC>(
                _loadProcAddr("glDebugMessageCallback"));
        glGetDebugMessageLog = reinterpret_cast<PFNGLGETDEBUGMESSAGELOGPROC>(
            _loadProcAddr("glGetDebugMessageLog"));
        glPushDebugGroup = reinterpret_cast<PFNGLPUSHDEBUGGROUPPROC>(
            _loadProcAddr("glPushDebugGroup"));
        glPopDebugGroup = reinterpret_cast<PFNGLPOPDEBUGGROUPPROC>(
            _loadProcAddr("glPopDebugGroup"));
        glObjectLabel = reinterpret_cast<PFNGLOBJECTLABELPROC>(
            _loadProcAddr("glObjectLabel"));
        glGetObjectLabel = reinterpret_cast<PFNGLGETOBJECTLABELPROC>(
            _loadProcAddr("glGetObjectLabel"));
        glObjectPtrLabel = reinterpret_cast<PFNGLOBJECTPTRLABELPROC>(
            _loadProcAddr("glObjectPtrLabel"));
        glGetObjectPtrLabel = reinterpret_cast<PFNGLGETOBJECTPTRLABELPROC>(
            _loadProcAddr("glGetObjectPtrLabel"));
#endif /* GL_VERSION_4_3 */
#ifdef GL_VERSION_4_4
        glBufferStorage = reinterpret_cast<PFNGLBUFFERSTORAGEPROC>(
            _loadProcAddr("glBufferStorage"));
        glClearTexImage = reinterpret_cast<PFNGLCLEARTEXIMAGEPROC>(
            _loadProcAddr("glClearTexImage"));
        glClearTexSubImage = reinterpret_cast<PFNGLCLEARTEXSUBIMAGEPROC>(
            _loadProcAddr("glClearTexSubImage"));
        glBindBuffersBase = reinterpret_cast<PFNGLBINDBUFFERSBASEPROC>(
            _loadProcAddr("glBindBuffersBase"));
        glBindBuffersRange = reinterpret_cast<PFNGLBINDBUFFERSRANGEPROC>(
            _loadProcAddr("glBindBuffersRange"));
        glBindTextures = reinterpret_cast<PFNGLBINDTEXTURESPROC>(
            _loadProcAddr("glBindTextures"));
        glBindSamplers = reinterpret_cast<PFNGLBINDSAMPLERSPROC>(
            _loadProcAddr("glBindSamplers"));
        glBindImageTextures = reinterpret_cast<PFNGLBINDIMAGETEXTURESPROC>(
            _loadProcAddr("glBindImageTextures"));
        glBindVertexBuffers = reinterpret_cast<PFNGLBINDVERTEXBUFFERSPROC>(
            _loadProcAddr("glBindVertexBuffers"));
#endif /* GL_VERSION_4_4 */
#ifdef GL_VERSION_4_5
        glClipControl = reinterpret_cast<PFNGLCLIPCONTROLPROC>(
            _loadProcAddr("glClipControl"));
        glCreateTransformFeedbacks =
            reinterpret_cast<PFNGLCREATETRANSFORMFEEDBACKSPROC>(
                _loadProcAddr("glCreateTransformFeedbacks"));
        glTransformFeedbackBufferBase =
            reinterpret_cast<PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC>(
                _loadProcAddr("glTransformFeedbackBufferBase"));
        glTransformFeedbackBufferRange =
            reinterpret_cast<PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC>(
                _loadProcAddr("glTransformFeedbackBufferRange"));
        glGetTransformFeedbackiv =
            reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKIVPROC>(
                _loadProcAddr("glGetTransformFeedbackiv"));
        glGetTransformFeedbacki_v =
            reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKI_VPROC>(
                _loadProcAddr("glGetTransformFeedbacki_v"));
        glGetTransformFeedbacki64_v =
            reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKI64_VPROC>(
                _loadProcAddr("glGetTransformFeedbacki64_v"));
        glCreateBuffers = reinterpret_cast<PFNGLCREATEBUFFERSPROC>(
            _loadProcAddr("glCreateBuffers"));
        glNamedBufferStorage = reinterpret_cast<PFNGLNAMEDBUFFERSTORAGEPROC>(
            _loadProcAddr("glNamedBufferStorage"));
        glNamedBufferData = reinterpret_cast<PFNGLNAMEDBUFFERDATAPROC>(
            _loadProcAddr("glNamedBufferData"));
        glNamedBufferSubData = reinterpret_cast<PFNGLNAMEDBUFFERSUBDATAPROC>(
            _loadProcAddr("glNamedBufferSubData"));
        glCopyNamedBufferSubData =
            reinterpret_cast<PFNGLCOPYNAMEDBUFFERSUBDATAPROC>(
                _loadProcAddr("glCopyNamedBufferSubData"));
        glClearNamedBufferData =
            reinterpret_cast<PFNGLCLEARNAMEDBUFFERDATAPROC>(
                _loadProcAddr("glClearNamedBufferData"));
        glClearNamedBufferSubData =
            reinterpret_cast<PFNGLCLEARNAMEDBUFFERSUBDATAPROC>(
                _loadProcAddr("glClearNamedBufferSubData"));
        glMapNamedBuffer = reinterpret_cast<PFNGLMAPNAMEDBUFFERPROC>(
            _loadProcAddr("glMapNamedBuffer"));
        glMapNamedBufferRange = reinterpret_cast<PFNGLMAPNAMEDBUFFERRANGEPROC>(
            _loadProcAddr("glMapNamedBufferRange"));
        glUnmapNamedBuffer = reinterpret_cast<PFNGLUNMAPNAMEDBUFFERPROC>(
            _loadProcAddr("glUnmapNamedBuffer"));
        glFlushMappedNamedBufferRange =
            reinterpret_cast<PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC>(
                _loadProcAddr("glFlushMappedNamedBufferRange"));
        glGetNamedBufferParameteriv =
            reinterpret_cast<PFNGLGETNAMEDBUFFERPARAMETERIVPROC>(
                _loadProcAddr("glGetNamedBufferParameteriv"));
        glGetNamedBufferParameteri64v =
            reinterpret_cast<PFNGLGETNAMEDBUFFERPARAMETERI64VPROC>(
                _loadProcAddr("glGetNamedBufferParameteri64v"));
        glGetNamedBufferPointerv =
            reinterpret_cast<PFNGLGETNAMEDBUFFERPOINTERVPROC>(
                _loadProcAddr("glGetNamedBufferPointerv"));
        glGetNamedBufferSubData =
            reinterpret_cast<PFNGLGETNAMEDBUFFERSUBDATAPROC>(
                _loadProcAddr("glGetNamedBufferSubData"));
        glCreateFramebuffers = reinterpret_cast<PFNGLCREATEFRAMEBUFFERSPROC>(
            _loadProcAddr("glCreateFramebuffers"));
        glNamedFramebufferRenderbuffer =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC>(
                _loadProcAddr("glNamedFramebufferRenderbuffer"));
        glNamedFramebufferParameteri =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC>(
                _loadProcAddr("glNamedFramebufferParameteri"));
        glNamedFramebufferTexture =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTUREPROC>(
                _loadProcAddr("glNamedFramebufferTexture"));
        glNamedFramebufferTextureLayer =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC>(
                _loadProcAddr("glNamedFramebufferTextureLayer"));
        glNamedFramebufferDrawBuffer =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC>(
                _loadProcAddr("glNamedFramebufferDrawBuffer"));
        glNamedFramebufferDrawBuffers =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC>(
                _loadProcAddr("glNamedFramebufferDrawBuffers"));
        glNamedFramebufferReadBuffer =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC>(
                _loadProcAddr("glNamedFramebufferReadBuffer"));
        glInvalidateNamedFramebufferData =
            reinterpret_cast<PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC>(
                _loadProcAddr("glInvalidateNamedFramebufferData"));
        glInvalidateNamedFramebufferSubData =
            reinterpret_cast<PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC>(
                _loadProcAddr("glInvalidateNamedFramebufferSubData"));
        glClearNamedFramebufferiv =
            reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERIVPROC>(
                _loadProcAddr("glClearNamedFramebufferiv"));
        glClearNamedFramebufferuiv =
            reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC>(
                _loadProcAddr("glClearNamedFramebufferuiv"));
        glClearNamedFramebufferfv =
            reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERFVPROC>(
                _loadProcAddr("glClearNamedFramebufferfv"));
        glClearNamedFramebufferfi =
            reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERFIPROC>(
                _loadProcAddr("glClearNamedFramebufferfi"));
        glBlitNamedFramebuffer =
            reinterpret_cast<PFNGLBLITNAMEDFRAMEBUFFERPROC>(
                _loadProcAddr("glBlitNamedFramebuffer"));
        glCheckNamedFramebufferStatus =
            reinterpret_cast<PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC>(
                _loadProcAddr("glCheckNamedFramebufferStatus"));
        glGetNamedFramebufferParameteriv =
            reinterpret_cast<PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC>(
                _loadProcAddr("glGetNamedFramebufferParameteriv"));
        glGetNamedFramebufferAttachmentParameteriv =
            reinterpret_cast<PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC>(
                _loadProcAddr("glGetNamedFramebufferAttachmentParameteriv"));
        glCreateRenderbuffers = reinterpret_cast<PFNGLCREATERENDERBUFFERSPROC>(
            _loadProcAddr("glCreateRenderbuffers"));
        glNamedRenderbufferStorage =
            reinterpret_cast<PFNGLNAMEDRENDERBUFFERSTORAGEPROC>(
                _loadProcAddr("glNamedRenderbufferStorage"));
        glNamedRenderbufferStorageMultisample =
            reinterpret_cast<PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC>(
                _loadProcAddr("glNamedRenderbufferStorageMultisample"));
        glGetNamedRenderbufferParameteriv =
            reinterpret_cast<PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC>(
                _loadProcAddr("glGetNamedRenderbufferParameteriv"));
        glCreateTextures = reinterpret_cast<PFNGLCREATETEXTURESPROC>(
            _loadProcAddr("glCreateTextures"));
        glTextureBuffer = reinterpret_cast<PFNGLTEXTUREBUFFERPROC>(
            _loadProcAddr("glTextureBuffer"));
        glTextureBufferRange = reinterpret_cast<PFNGLTEXTUREBUFFERRANGEPROC>(
            _loadProcAddr("glTextureBufferRange"));
        glTextureStorage1D = reinterpret_cast<PFNGLTEXTURESTORAGE1DPROC>(
            _loadProcAddr("glTextureStorage1D"));
        glTextureStorage2D = reinterpret_cast<PFNGLTEXTURESTORAGE2DPROC>(
            _loadProcAddr("glTextureStorage2D"));
        glTextureStorage3D = reinterpret_cast<PFNGLTEXTURESTORAGE3DPROC>(
            _loadProcAddr("glTextureStorage3D"));
        glTextureStorage2DMultisample =
            reinterpret_cast<PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC>(
                _loadProcAddr("glTextureStorage2DMultisample"));
        glTextureStorage3DMultisample =
            reinterpret_cast<PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC>(
                _loadProcAddr("glTextureStorage3DMultisample"));
        glTextureSubImage1D = reinterpret_cast<PFNGLTEXTURESUBIMAGE1DPROC>(
            _loadProcAddr("glTextureSubImage1D"));
        glTextureSubImage2D = reinterpret_cast<PFNGLTEXTURESUBIMAGE2DPROC>(
            _loadProcAddr("glTextureSubImage2D"));
        glTextureSubImage3D = reinterpret_cast<PFNGLTEXTURESUBIMAGE3DPROC>(
            _loadProcAddr("glTextureSubImage3D"));
        glCompressedTextureSubImage1D =
            reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC>(
                _loadProcAddr("glCompressedTextureSubImage1D"));
        glCompressedTextureSubImage2D =
            reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC>(
                _loadProcAddr("glCompressedTextureSubImage2D"));
        glCompressedTextureSubImage3D =
            reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC>(
                _loadProcAddr("glCompressedTextureSubImage3D"));
        glCopyTextureSubImage1D =
            reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE1DPROC>(
                _loadProcAddr("glCopyTextureSubImage1D"));
        glCopyTextureSubImage2D =
            reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE2DPROC>(
                _loadProcAddr("glCopyTextureSubImage2D"));
        glCopyTextureSubImage3D =
            reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE3DPROC>(
                _loadProcAddr("glCopyTextureSubImage3D"));
        glTextureParameterf = reinterpret_cast<PFNGLTEXTUREPARAMETERFPROC>(
            _loadProcAddr("glTextureParameterf"));
        glTextureParameterfv = reinterpret_cast<PFNGLTEXTUREPARAMETERFVPROC>(
            _loadProcAddr("glTextureParameterfv"));
        glTextureParameteri = reinterpret_cast<PFNGLTEXTUREPARAMETERIPROC>(
            _loadProcAddr("glTextureParameteri"));
        glTextureParameterIiv = reinterpret_cast<PFNGLTEXTUREPARAMETERIIVPROC>(
            _loadProcAddr("glTextureParameterIiv"));
        glTextureParameterIuiv =
            reinterpret_cast<PFNGLTEXTUREPARAMETERIUIVPROC>(
                _loadProcAddr("glTextureParameterIuiv"));
        glTextureParameteriv = reinterpret_cast<PFNGLTEXTUREPARAMETERIVPROC>(
            _loadProcAddr("glTextureParameteriv"));
        glGenerateTextureMipmap =
            reinterpret_cast<PFNGLGENERATETEXTUREMIPMAPPROC>(
                _loadProcAddr("glGenerateTextureMipmap"));
        glBindTextureUnit = reinterpret_cast<PFNGLBINDTEXTUREUNITPROC>(
            _loadProcAddr("glBindTextureUnit"));
        glGetTextureImage = reinterpret_cast<PFNGLGETTEXTUREIMAGEPROC>(
            _loadProcAddr("glGetTextureImage"));
        glGetCompressedTextureImage =
            reinterpret_cast<PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC>(
                _loadProcAddr("glGetCompressedTextureImage"));
        glGetTextureLevelParameterfv =
            reinterpret_cast<PFNGLGETTEXTURELEVELPARAMETERFVPROC>(
                _loadProcAddr("glGetTextureLevelParameterfv"));
        glGetTextureLevelParameteriv =
            reinterpret_cast<PFNGLGETTEXTURELEVELPARAMETERIVPROC>(
                _loadProcAddr("glGetTextureLevelParameteriv"));
        glGetTextureParameterfv =
            reinterpret_cast<PFNGLGETTEXTUREPARAMETERFVPROC>(
                _loadProcAddr("glGetTextureParameterfv"));
        glGetTextureParameterIiv =
            reinterpret_cast<PFNGLGETTEXTUREPARAMETERIIVPROC>(
                _loadProcAddr("glGetTextureParameterIiv"));
        glGetTextureParameterIuiv =
            reinterpret_cast<PFNGLGETTEXTUREPARAMETERIUIVPROC>(
                _loadProcAddr("glGetTextureParameterIuiv"));
        glGetTextureParameteriv =
            reinterpret_cast<PFNGLGETTEXTUREPARAMETERIVPROC>(
                _loadProcAddr("glGetTextureParameteriv"));
        glCreateVertexArrays = reinterpret_cast<PFNGLCREATEVERTEXARRAYSPROC>(
            _loadProcAddr("glCreateVertexArrays"));
        glDisableVertexArrayAttrib =
            reinterpret_cast<PFNGLDISABLEVERTEXARRAYATTRIBPROC>(
                _loadProcAddr("glDisableVertexArrayAttrib"));
        glEnableVertexArrayAttrib =
            reinterpret_cast<PFNGLENABLEVERTEXARRAYATTRIBPROC>(
                _loadProcAddr("glEnableVertexArrayAttrib"));
        glVertexArrayElementBuffer =
            reinterpret_cast<PFNGLVERTEXARRAYELEMENTBUFFERPROC>(
                _loadProcAddr("glVertexArrayElementBuffer"));
        glVertexArrayVertexBuffer =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXBUFFERPROC>(
                _loadProcAddr("glVertexArrayVertexBuffer"));
        glVertexArrayVertexBuffers =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXBUFFERSPROC>(
                _loadProcAddr("glVertexArrayVertexBuffers"));
        glVertexArrayAttribBinding =
            reinterpret_cast<PFNGLVERTEXARRAYATTRIBBINDINGPROC>(
                _loadProcAddr("glVertexArrayAttribBinding"));
        glVertexArrayAttribFormat =
            reinterpret_cast<PFNGLVERTEXARRAYATTRIBFORMATPROC>(
                _loadProcAddr("glVertexArrayAttribFormat"));
        glVertexArrayAttribIFormat =
            reinterpret_cast<PFNGLVERTEXARRAYATTRIBIFORMATPROC>(
                _loadProcAddr("glVertexArrayAttribIFormat"));
        glVertexArrayAttribLFormat =
            reinterpret_cast<PFNGLVERTEXARRAYATTRIBLFORMATPROC>(
                _loadProcAddr("glVertexArrayAttribLFormat"));
        glVertexArrayBindingDivisor =
            reinterpret_cast<PFNGLVERTEXARRAYBINDINGDIVISORPROC>(
                _loadProcAddr("glVertexArrayBindingDivisor"));
        glGetVertexArrayiv = reinterpret_cast<PFNGLGETVERTEXARRAYIVPROC>(
            _loadProcAddr("glGetVertexArrayiv"));
        glGetVertexArrayIndexediv =
            reinterpret_cast<PFNGLGETVERTEXARRAYINDEXEDIVPROC>(
                _loadProcAddr("glGetVertexArrayIndexediv"));
        glGetVertexArrayIndexed64iv =
            reinterpret_cast<PFNGLGETVERTEXARRAYINDEXED64IVPROC>(
                _loadProcAddr("glGetVertexArrayIndexed64iv"));
        glCreateSamplers = reinterpret_cast<PFNGLCREATESAMPLERSPROC>(
            _loadProcAddr("glCreateSamplers"));
        glCreateProgramPipelines =
            reinterpret_cast<PFNGLCREATEPROGRAMPIPELINESPROC>(
                _loadProcAddr("glCreateProgramPipelines"));
        glCreateQueries = reinterpret_cast<PFNGLCREATEQUERIESPROC>(
            _loadProcAddr("glCreateQueries"));
        glGetQueryBufferObjecti64v =
            reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTI64VPROC>(
                _loadProcAddr("glGetQueryBufferObjecti64v"));
        glGetQueryBufferObjectiv =
            reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTIVPROC>(
                _loadProcAddr("glGetQueryBufferObjectiv"));
        glGetQueryBufferObjectui64v =
            reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTUI64VPROC>(
                _loadProcAddr("glGetQueryBufferObjectui64v"));
        glGetQueryBufferObjectuiv =
            reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTUIVPROC>(
                _loadProcAddr("glGetQueryBufferObjectuiv"));
        glMemoryBarrierByRegion =
            reinterpret_cast<PFNGLMEMORYBARRIERBYREGIONPROC>(
                _loadProcAddr("glMemoryBarrierByRegion"));
        glGetTextureSubImage = reinterpret_cast<PFNGLGETTEXTURESUBIMAGEPROC>(
            _loadProcAddr("glGetTextureSubImage"));
        glGetCompressedTextureSubImage =
            reinterpret_cast<PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC>(
                _loadProcAddr("glGetCompressedTextureSubImage"));
        glGetGraphicsResetStatus =
            reinterpret_cast<PFNGLGETGRAPHICSRESETSTATUSPROC>(
                _loadProcAddr("glGetGraphicsResetStatus"));
        glGetnCompressedTexImage =
            reinterpret_cast<PFNGLGETNCOMPRESSEDTEXIMAGEPROC>(
                _loadProcAddr("glGetnCompressedTexImage"));
        glGetnTexImage = reinterpret_cast<PFNGLGETNTEXIMAGEPROC>(
            _loadProcAddr("glGetnTexImage"));
        glGetnUniformdv = reinterpret_cast<PFNGLGETNUNIFORMDVPROC>(
            _loadProcAddr("glGetnUniformdv"));
        glGetnUniformfv = reinterpret_cast<PFNGLGETNUNIFORMFVPROC>(
            _loadProcAddr("glGetnUniformfv"));
        glGetnUniformiv = reinterpret_cast<PFNGLGETNUNIFORMIVPROC>(
            _loadProcAddr("glGetnUniformiv"));
        glGetnUniformuiv = reinterpret_cast<PFNGLGETNUNIFORMUIVPROC>(
            _loadProcAddr("glGetnUniformuiv"));
        glReadnPixels = reinterpret_cast<PFNGLREADNPIXELSPROC>(
            _loadProcAddr("glReadnPixels"));
        glTextureBarrier = reinterpret_cast<PFNGLTEXTUREBARRIERPROC>(
            _loadProcAddr("glTextureBarrier"));
#endif /* GL_VERSION_4_5 */
#ifdef GL_VERSION_4_6
        glSpecializeShader = reinterpret_cast<PFNGLSPECIALIZESHADERPROC>(
            _loadProcAddr("glSpecializeShader"));
        glMultiDrawArraysIndirectCount =
            reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC>(
                _loadProcAddr("glMultiDrawArraysIndirectCount"));
        glMultiDrawElementsIndirectCount =
            reinterpret_cast<PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC>(
                _loadProcAddr("glMultiDrawElementsIndirectCount"));
        glPolygonOffsetClamp = reinterpret_cast<PFNGLPOLYGONOFFSETCLAMPPROC>(
            _loadProcAddr("glPolygonOffsetClamp"));
#endif /* GL_VERSION_4_6 */
#ifdef GL_ARB_ES2_compatibility
#endif /* GL_ARB_ES2_compatibility */
#ifdef GL_ARB_ES3_1_compatibility
#endif /* GL_ARB_ES3_1_compatibility */
#ifdef GL_ARB_ES3_2_compatibility
        glPrimitiveBoundingBoxARB =
            reinterpret_cast<PFNGLPRIMITIVEBOUNDINGBOXARBPROC>(
                _loadProcAddr("glPrimitiveBoundingBoxARB"));
#endif /* GL_ARB_ES3_2_compatibility */
#ifdef GL_ARB_ES3_compatibility
#endif /* GL_ARB_ES3_compatibility */
#ifdef GL_ARB_arrays_of_arrays
#endif /* GL_ARB_arrays_of_arrays */
#ifdef GL_ARB_base_instance
#endif /* GL_ARB_base_instance */
#ifdef GL_ARB_bindless_texture
        glGetTextureHandleARB = reinterpret_cast<PFNGLGETTEXTUREHANDLEARBPROC>(
            _loadProcAddr("glGetTextureHandleARB"));
        glGetTextureSamplerHandleARB =
            reinterpret_cast<PFNGLGETTEXTURESAMPLERHANDLEARBPROC>(
                _loadProcAddr("glGetTextureSamplerHandleARB"));
        glMakeTextureHandleResidentARB =
            reinterpret_cast<PFNGLMAKETEXTUREHANDLERESIDENTARBPROC>(
                _loadProcAddr("glMakeTextureHandleResidentARB"));
        glMakeTextureHandleNonResidentARB =
            reinterpret_cast<PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC>(
                _loadProcAddr("glMakeTextureHandleNonResidentARB"));
        glGetImageHandleARB = reinterpret_cast<PFNGLGETIMAGEHANDLEARBPROC>(
            _loadProcAddr("glGetImageHandleARB"));
        glMakeImageHandleResidentARB =
            reinterpret_cast<PFNGLMAKEIMAGEHANDLERESIDENTARBPROC>(
                _loadProcAddr("glMakeImageHandleResidentARB"));
        glMakeImageHandleNonResidentARB =
            reinterpret_cast<PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC>(
                _loadProcAddr("glMakeImageHandleNonResidentARB"));
        glUniformHandleui64ARB =
            reinterpret_cast<PFNGLUNIFORMHANDLEUI64ARBPROC>(
                _loadProcAddr("glUniformHandleui64ARB"));
        glUniformHandleui64vARB =
            reinterpret_cast<PFNGLUNIFORMHANDLEUI64VARBPROC>(
                _loadProcAddr("glUniformHandleui64vARB"));
        glProgramUniformHandleui64ARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC>(
                _loadProcAddr("glProgramUniformHandleui64ARB"));
        glProgramUniformHandleui64vARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC>(
                _loadProcAddr("glProgramUniformHandleui64vARB"));
        glIsTextureHandleResidentARB =
            reinterpret_cast<PFNGLISTEXTUREHANDLERESIDENTARBPROC>(
                _loadProcAddr("glIsTextureHandleResidentARB"));
        glIsImageHandleResidentARB =
            reinterpret_cast<PFNGLISIMAGEHANDLERESIDENTARBPROC>(
                _loadProcAddr("glIsImageHandleResidentARB"));
        glVertexAttribL1ui64ARB =
            reinterpret_cast<PFNGLVERTEXATTRIBL1UI64ARBPROC>(
                _loadProcAddr("glVertexAttribL1ui64ARB"));
        glVertexAttribL1ui64vARB =
            reinterpret_cast<PFNGLVERTEXATTRIBL1UI64VARBPROC>(
                _loadProcAddr("glVertexAttribL1ui64vARB"));
        glGetVertexAttribLui64vARB =
            reinterpret_cast<PFNGLGETVERTEXATTRIBLUI64VARBPROC>(
                _loadProcAddr("glGetVertexAttribLui64vARB"));
#endif /* GL_ARB_bindless_texture */
#ifdef GL_ARB_blend_func_extended
#endif /* GL_ARB_blend_func_extended */
#ifdef GL_ARB_buffer_storage
#endif /* GL_ARB_buffer_storage */
#ifdef GL_ARB_cl_event
        glCreateSyncFromCLeventARB =
            reinterpret_cast<PFNGLCREATESYNCFROMCLEVENTARBPROC>(
                _loadProcAddr("glCreateSyncFromCLeventARB"));
#endif /* GL_ARB_cl_event */
#ifdef GL_ARB_clear_buffer_object
#endif /* GL_ARB_clear_buffer_object */
#ifdef GL_ARB_clear_texture
#endif /* GL_ARB_clear_texture */
#ifdef GL_ARB_clip_control
#endif /* GL_ARB_clip_control */
#ifdef GL_ARB_compressed_texture_pixel_storage
#endif /* GL_ARB_compressed_texture_pixel_storage */
#ifdef GL_ARB_compute_shader
#endif /* GL_ARB_compute_shader */
#ifdef GL_ARB_compute_variable_group_size
        glDispatchComputeGroupSizeARB =
            reinterpret_cast<PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC>(
                _loadProcAddr("glDispatchComputeGroupSizeARB"));
#endif /* GL_ARB_compute_variable_group_size */
#ifdef GL_ARB_conditional_render_inverted
#endif /* GL_ARB_conditional_render_inverted */
#ifdef GL_ARB_conservative_depth
#endif /* GL_ARB_conservative_depth */
#ifdef GL_ARB_copy_buffer
#endif /* GL_ARB_copy_buffer */
#ifdef GL_ARB_copy_image
#endif /* GL_ARB_copy_image */
#ifdef GL_ARB_cull_distance
#endif /* GL_ARB_cull_distance */
#ifdef GL_ARB_debug_output
        glDebugMessageControlARB =
            reinterpret_cast<PFNGLDEBUGMESSAGECONTROLARBPROC>(
                _loadProcAddr("glDebugMessageControlARB"));
        glDebugMessageInsertARB =
            reinterpret_cast<PFNGLDEBUGMESSAGEINSERTARBPROC>(
                _loadProcAddr("glDebugMessageInsertARB"));
        glDebugMessageCallbackARB =
            reinterpret_cast<PFNGLDEBUGMESSAGECALLBACKARBPROC>(
                _loadProcAddr("glDebugMessageCallbackARB"));
        glGetDebugMessageLogARB =
            reinterpret_cast<PFNGLGETDEBUGMESSAGELOGARBPROC>(
                _loadProcAddr("glGetDebugMessageLogARB"));
#endif /* GL_ARB_debug_output */
#ifdef GL_ARB_depth_buffer_float
#endif /* GL_ARB_depth_buffer_float */
#ifdef GL_ARB_depth_clamp
#endif /* GL_ARB_depth_clamp */
#ifdef GL_ARB_derivative_control
#endif /* GL_ARB_derivative_control */
#ifdef GL_ARB_direct_state_access
#endif /* GL_ARB_direct_state_access */
#ifdef GL_ARB_draw_buffers_blend
        glBlendEquationiARB = reinterpret_cast<PFNGLBLENDEQUATIONIARBPROC>(
            _loadProcAddr("glBlendEquationiARB"));
        glBlendEquationSeparateiARB =
            reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEIARBPROC>(
                _loadProcAddr("glBlendEquationSeparateiARB"));
        glBlendFunciARB = reinterpret_cast<PFNGLBLENDFUNCIARBPROC>(
            _loadProcAddr("glBlendFunciARB"));
        glBlendFuncSeparateiARB =
            reinterpret_cast<PFNGLBLENDFUNCSEPARATEIARBPROC>(
                _loadProcAddr("glBlendFuncSeparateiARB"));
#endif /* GL_ARB_draw_buffers_blend */
#ifdef GL_ARB_draw_elements_base_vertex
#endif /* GL_ARB_draw_elements_base_vertex */
#ifdef GL_ARB_draw_indirect
#endif /* GL_ARB_draw_indirect */
#ifdef GL_ARB_draw_instanced
        glDrawArraysInstancedARB =
            reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDARBPROC>(
                _loadProcAddr("glDrawArraysInstancedARB"));
        glDrawElementsInstancedARB =
            reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDARBPROC>(
                _loadProcAddr("glDrawElementsInstancedARB"));
#endif /* GL_ARB_draw_instanced */
#ifdef GL_ARB_enhanced_layouts
#endif /* GL_ARB_enhanced_layouts */
#ifdef GL_ARB_explicit_attrib_location
#endif /* GL_ARB_explicit_attrib_location */
#ifdef GL_ARB_explicit_uniform_location
#endif /* GL_ARB_explicit_uniform_location */
#ifdef GL_ARB_fragment_coord_conventions
#endif /* GL_ARB_fragment_coord_conventions */
#ifdef GL_ARB_fragment_layer_viewport
#endif /* GL_ARB_fragment_layer_viewport */
#ifdef GL_ARB_fragment_shader_interlock
#endif /* GL_ARB_fragment_shader_interlock */
#ifdef GL_ARB_framebuffer_no_attachments
#endif /* GL_ARB_framebuffer_no_attachments */
#ifdef GL_ARB_framebuffer_object
#endif /* GL_ARB_framebuffer_object */
#ifdef GL_ARB_framebuffer_sRGB
#endif /* GL_ARB_framebuffer_sRGB */
#ifdef GL_ARB_geometry_shader4
        glProgramParameteriARB =
            reinterpret_cast<PFNGLPROGRAMPARAMETERIARBPROC>(
                _loadProcAddr("glProgramParameteriARB"));
        glFramebufferTextureARB =
            reinterpret_cast<PFNGLFRAMEBUFFERTEXTUREARBPROC>(
                _loadProcAddr("glFramebufferTextureARB"));
        glFramebufferTextureLayerARB =
            reinterpret_cast<PFNGLFRAMEBUFFERTEXTURELAYERARBPROC>(
                _loadProcAddr("glFramebufferTextureLayerARB"));
        glFramebufferTextureFaceARB =
            reinterpret_cast<PFNGLFRAMEBUFFERTEXTUREFACEARBPROC>(
                _loadProcAddr("glFramebufferTextureFaceARB"));
#endif /* GL_ARB_geometry_shader4 */
#ifdef GL_ARB_get_program_binary
#endif /* GL_ARB_get_program_binary */
#ifdef GL_ARB_get_texture_sub_image
#endif /* GL_ARB_get_texture_sub_image */
#ifdef GL_ARB_gl_spirv
        glSpecializeShaderARB = reinterpret_cast<PFNGLSPECIALIZESHADERARBPROC>(
            _loadProcAddr("glSpecializeShaderARB"));
#endif /* GL_ARB_gl_spirv */
#ifdef GL_ARB_gpu_shader5
#endif /* GL_ARB_gpu_shader5 */
#ifdef GL_ARB_gpu_shader_fp64
#endif /* GL_ARB_gpu_shader_fp64 */
#ifdef GL_ARB_gpu_shader_int64
        glUniform1i64ARB = reinterpret_cast<PFNGLUNIFORM1I64ARBPROC>(
            _loadProcAddr("glUniform1i64ARB"));
        glUniform2i64ARB = reinterpret_cast<PFNGLUNIFORM2I64ARBPROC>(
            _loadProcAddr("glUniform2i64ARB"));
        glUniform3i64ARB = reinterpret_cast<PFNGLUNIFORM3I64ARBPROC>(
            _loadProcAddr("glUniform3i64ARB"));
        glUniform4i64ARB = reinterpret_cast<PFNGLUNIFORM4I64ARBPROC>(
            _loadProcAddr("glUniform4i64ARB"));
        glUniform1i64vARB = reinterpret_cast<PFNGLUNIFORM1I64VARBPROC>(
            _loadProcAddr("glUniform1i64vARB"));
        glUniform2i64vARB = reinterpret_cast<PFNGLUNIFORM2I64VARBPROC>(
            _loadProcAddr("glUniform2i64vARB"));
        glUniform3i64vARB = reinterpret_cast<PFNGLUNIFORM3I64VARBPROC>(
            _loadProcAddr("glUniform3i64vARB"));
        glUniform4i64vARB = reinterpret_cast<PFNGLUNIFORM4I64VARBPROC>(
            _loadProcAddr("glUniform4i64vARB"));
        glUniform1ui64ARB = reinterpret_cast<PFNGLUNIFORM1UI64ARBPROC>(
            _loadProcAddr("glUniform1ui64ARB"));
        glUniform2ui64ARB = reinterpret_cast<PFNGLUNIFORM2UI64ARBPROC>(
            _loadProcAddr("glUniform2ui64ARB"));
        glUniform3ui64ARB = reinterpret_cast<PFNGLUNIFORM3UI64ARBPROC>(
            _loadProcAddr("glUniform3ui64ARB"));
        glUniform4ui64ARB = reinterpret_cast<PFNGLUNIFORM4UI64ARBPROC>(
            _loadProcAddr("glUniform4ui64ARB"));
        glUniform1ui64vARB = reinterpret_cast<PFNGLUNIFORM1UI64VARBPROC>(
            _loadProcAddr("glUniform1ui64vARB"));
        glUniform2ui64vARB = reinterpret_cast<PFNGLUNIFORM2UI64VARBPROC>(
            _loadProcAddr("glUniform2ui64vARB"));
        glUniform3ui64vARB = reinterpret_cast<PFNGLUNIFORM3UI64VARBPROC>(
            _loadProcAddr("glUniform3ui64vARB"));
        glUniform4ui64vARB = reinterpret_cast<PFNGLUNIFORM4UI64VARBPROC>(
            _loadProcAddr("glUniform4ui64vARB"));
        glGetUniformi64vARB = reinterpret_cast<PFNGLGETUNIFORMI64VARBPROC>(
            _loadProcAddr("glGetUniformi64vARB"));
        glGetUniformui64vARB = reinterpret_cast<PFNGLGETUNIFORMUI64VARBPROC>(
            _loadProcAddr("glGetUniformui64vARB"));
        glGetnUniformi64vARB = reinterpret_cast<PFNGLGETNUNIFORMI64VARBPROC>(
            _loadProcAddr("glGetnUniformi64vARB"));
        glGetnUniformui64vARB = reinterpret_cast<PFNGLGETNUNIFORMUI64VARBPROC>(
            _loadProcAddr("glGetnUniformui64vARB"));
        glProgramUniform1i64ARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1I64ARBPROC>(
                _loadProcAddr("glProgramUniform1i64ARB"));
        glProgramUniform2i64ARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2I64ARBPROC>(
                _loadProcAddr("glProgramUniform2i64ARB"));
        glProgramUniform3i64ARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3I64ARBPROC>(
                _loadProcAddr("glProgramUniform3i64ARB"));
        glProgramUniform4i64ARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4I64ARBPROC>(
                _loadProcAddr("glProgramUniform4i64ARB"));
        glProgramUniform1i64vARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1I64VARBPROC>(
                _loadProcAddr("glProgramUniform1i64vARB"));
        glProgramUniform2i64vARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2I64VARBPROC>(
                _loadProcAddr("glProgramUniform2i64vARB"));
        glProgramUniform3i64vARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3I64VARBPROC>(
                _loadProcAddr("glProgramUniform3i64vARB"));
        glProgramUniform4i64vARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4I64VARBPROC>(
                _loadProcAddr("glProgramUniform4i64vARB"));
        glProgramUniform1ui64ARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1UI64ARBPROC>(
                _loadProcAddr("glProgramUniform1ui64ARB"));
        glProgramUniform2ui64ARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2UI64ARBPROC>(
                _loadProcAddr("glProgramUniform2ui64ARB"));
        glProgramUniform3ui64ARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3UI64ARBPROC>(
                _loadProcAddr("glProgramUniform3ui64ARB"));
        glProgramUniform4ui64ARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4UI64ARBPROC>(
                _loadProcAddr("glProgramUniform4ui64ARB"));
        glProgramUniform1ui64vARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1UI64VARBPROC>(
                _loadProcAddr("glProgramUniform1ui64vARB"));
        glProgramUniform2ui64vARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2UI64VARBPROC>(
                _loadProcAddr("glProgramUniform2ui64vARB"));
        glProgramUniform3ui64vARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3UI64VARBPROC>(
                _loadProcAddr("glProgramUniform3ui64vARB"));
        glProgramUniform4ui64vARB =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4UI64VARBPROC>(
                _loadProcAddr("glProgramUniform4ui64vARB"));
#endif /* GL_ARB_gpu_shader_int64 */
#ifdef GL_ARB_half_float_vertex
#endif /* GL_ARB_half_float_vertex */
#ifdef GL_ARB_imaging
#endif /* GL_ARB_imaging */
#ifdef GL_ARB_indirect_parameters
        glMultiDrawArraysIndirectCountARB =
            reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC>(
                _loadProcAddr("glMultiDrawArraysIndirectCountARB"));
        glMultiDrawElementsIndirectCountARB =
            reinterpret_cast<PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC>(
                _loadProcAddr("glMultiDrawElementsIndirectCountARB"));
#endif /* GL_ARB_indirect_parameters */
#ifdef GL_ARB_instanced_arrays
        glVertexAttribDivisorARB =
            reinterpret_cast<PFNGLVERTEXATTRIBDIVISORARBPROC>(
                _loadProcAddr("glVertexAttribDivisorARB"));
#endif /* GL_ARB_instanced_arrays */
#ifdef GL_ARB_internalformat_query
#endif /* GL_ARB_internalformat_query */
#ifdef GL_ARB_internalformat_query2
#endif /* GL_ARB_internalformat_query2 */
#ifdef GL_ARB_invalidate_subdata
#endif /* GL_ARB_invalidate_subdata */
#ifdef GL_ARB_map_buffer_alignment
#endif /* GL_ARB_map_buffer_alignment */
#ifdef GL_ARB_map_buffer_range
#endif /* GL_ARB_map_buffer_range */
#ifdef GL_ARB_multi_bind
#endif /* GL_ARB_multi_bind */
#ifdef GL_ARB_multi_draw_indirect
#endif /* GL_ARB_multi_draw_indirect */
#ifdef GL_ARB_occlusion_query2
#endif /* GL_ARB_occlusion_query2 */
#ifdef GL_ARB_parallel_shader_compile
        glMaxShaderCompilerThreadsARB =
            reinterpret_cast<PFNGLMAXSHADERCOMPILERTHREADSARBPROC>(
                _loadProcAddr("glMaxShaderCompilerThreadsARB"));
#endif /* GL_ARB_parallel_shader_compile */
#ifdef GL_ARB_pipeline_statistics_query
#endif /* GL_ARB_pipeline_statistics_query */
#ifdef GL_ARB_pixel_buffer_object
#endif /* GL_ARB_pixel_buffer_object */
#ifdef GL_ARB_polygon_offset_clamp
#endif /* GL_ARB_polygon_offset_clamp */
#ifdef GL_ARB_post_depth_coverage
#endif /* GL_ARB_post_depth_coverage */
#ifdef GL_ARB_program_interface_query
#endif /* GL_ARB_program_interface_query */
#ifdef GL_ARB_provoking_vertex
#endif /* GL_ARB_provoking_vertex */
#ifdef GL_ARB_query_buffer_object
#endif /* GL_ARB_query_buffer_object */
#ifdef GL_ARB_robust_buffer_access_behavior
#endif /* GL_ARB_robust_buffer_access_behavior */
#ifdef GL_ARB_robustness
        glGetGraphicsResetStatusARB =
            reinterpret_cast<PFNGLGETGRAPHICSRESETSTATUSARBPROC>(
                _loadProcAddr("glGetGraphicsResetStatusARB"));
        glGetnTexImageARB = reinterpret_cast<PFNGLGETNTEXIMAGEARBPROC>(
            _loadProcAddr("glGetnTexImageARB"));
        glReadnPixelsARB = reinterpret_cast<PFNGLREADNPIXELSARBPROC>(
            _loadProcAddr("glReadnPixelsARB"));
        glGetnCompressedTexImageARB =
            reinterpret_cast<PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC>(
                _loadProcAddr("glGetnCompressedTexImageARB"));
        glGetnUniformfvARB = reinterpret_cast<PFNGLGETNUNIFORMFVARBPROC>(
            _loadProcAddr("glGetnUniformfvARB"));
        glGetnUniformivARB = reinterpret_cast<PFNGLGETNUNIFORMIVARBPROC>(
            _loadProcAddr("glGetnUniformivARB"));
        glGetnUniformuivARB = reinterpret_cast<PFNGLGETNUNIFORMUIVARBPROC>(
            _loadProcAddr("glGetnUniformuivARB"));
        glGetnUniformdvARB = reinterpret_cast<PFNGLGETNUNIFORMDVARBPROC>(
            _loadProcAddr("glGetnUniformdvARB"));
#endif /* GL_ARB_robustness */
#ifdef GL_ARB_robustness_isolation
#endif /* GL_ARB_robustness_isolation */
#ifdef GL_ARB_sample_locations
        glFramebufferSampleLocationsfvARB =
            reinterpret_cast<PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC>(
                _loadProcAddr("glFramebufferSampleLocationsfvARB"));
        glNamedFramebufferSampleLocationsfvARB =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC>(
                _loadProcAddr("glNamedFramebufferSampleLocationsfvARB"));
        glEvaluateDepthValuesARB =
            reinterpret_cast<PFNGLEVALUATEDEPTHVALUESARBPROC>(
                _loadProcAddr("glEvaluateDepthValuesARB"));
#endif /* GL_ARB_sample_locations */
#ifdef GL_ARB_sample_shading
        glMinSampleShadingARB = reinterpret_cast<PFNGLMINSAMPLESHADINGARBPROC>(
            _loadProcAddr("glMinSampleShadingARB"));
#endif /* GL_ARB_sample_shading */
#ifdef GL_ARB_sampler_objects
#endif /* GL_ARB_sampler_objects */
#ifdef GL_ARB_seamless_cube_map
#endif /* GL_ARB_seamless_cube_map */
#ifdef GL_ARB_seamless_cubemap_per_texture
#endif /* GL_ARB_seamless_cubemap_per_texture */
#ifdef GL_ARB_separate_shader_objects
#endif /* GL_ARB_separate_shader_objects */
#ifdef GL_ARB_shader_atomic_counter_ops
#endif /* GL_ARB_shader_atomic_counter_ops */
#ifdef GL_ARB_shader_atomic_counters
#endif /* GL_ARB_shader_atomic_counters */
#ifdef GL_ARB_shader_ballot
#endif /* GL_ARB_shader_ballot */
#ifdef GL_ARB_shader_bit_encoding
#endif /* GL_ARB_shader_bit_encoding */
#ifdef GL_ARB_shader_clock
#endif /* GL_ARB_shader_clock */
#ifdef GL_ARB_shader_draw_parameters
#endif /* GL_ARB_shader_draw_parameters */
#ifdef GL_ARB_shader_group_vote
#endif /* GL_ARB_shader_group_vote */
#ifdef GL_ARB_shader_image_load_store
#endif /* GL_ARB_shader_image_load_store */
#ifdef GL_ARB_shader_image_size
#endif /* GL_ARB_shader_image_size */
#ifdef GL_ARB_shader_precision
#endif /* GL_ARB_shader_precision */
#ifdef GL_ARB_shader_stencil_export
#endif /* GL_ARB_shader_stencil_export */
#ifdef GL_ARB_shader_storage_buffer_object
#endif /* GL_ARB_shader_storage_buffer_object */
#ifdef GL_ARB_shader_subroutine
#endif /* GL_ARB_shader_subroutine */
#ifdef GL_ARB_shader_texture_image_samples
#endif /* GL_ARB_shader_texture_image_samples */
#ifdef GL_ARB_shader_viewport_layer_array
#endif /* GL_ARB_shader_viewport_layer_array */
#ifdef GL_ARB_shading_language_420pack
#endif /* GL_ARB_shading_language_420pack */
#ifdef GL_ARB_shading_language_include
        glNamedStringARB = reinterpret_cast<PFNGLNAMEDSTRINGARBPROC>(
            _loadProcAddr("glNamedStringARB"));
        glDeleteNamedStringARB =
            reinterpret_cast<PFNGLDELETENAMEDSTRINGARBPROC>(
                _loadProcAddr("glDeleteNamedStringARB"));
        glCompileShaderIncludeARB =
            reinterpret_cast<PFNGLCOMPILESHADERINCLUDEARBPROC>(
                _loadProcAddr("glCompileShaderIncludeARB"));
        glIsNamedStringARB = reinterpret_cast<PFNGLISNAMEDSTRINGARBPROC>(
            _loadProcAddr("glIsNamedStringARB"));
        glGetNamedStringARB = reinterpret_cast<PFNGLGETNAMEDSTRINGARBPROC>(
            _loadProcAddr("glGetNamedStringARB"));
        glGetNamedStringivARB = reinterpret_cast<PFNGLGETNAMEDSTRINGIVARBPROC>(
            _loadProcAddr("glGetNamedStringivARB"));
#endif /* GL_ARB_shading_language_include */
#ifdef GL_ARB_shading_language_packing
#endif /* GL_ARB_shading_language_packing */
#ifdef GL_ARB_sparse_buffer
        glBufferPageCommitmentARB =
            reinterpret_cast<PFNGLBUFFERPAGECOMMITMENTARBPROC>(
                _loadProcAddr("glBufferPageCommitmentARB"));
        glNamedBufferPageCommitmentEXT =
            reinterpret_cast<PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC>(
                _loadProcAddr("glNamedBufferPageCommitmentEXT"));
        glNamedBufferPageCommitmentARB =
            reinterpret_cast<PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC>(
                _loadProcAddr("glNamedBufferPageCommitmentARB"));
#endif /* GL_ARB_sparse_buffer */
#ifdef GL_ARB_sparse_texture
        glTexPageCommitmentARB =
            reinterpret_cast<PFNGLTEXPAGECOMMITMENTARBPROC>(
                _loadProcAddr("glTexPageCommitmentARB"));
#endif /* GL_ARB_sparse_texture */
#ifdef GL_ARB_sparse_texture2
#endif /* GL_ARB_sparse_texture2 */
#ifdef GL_ARB_sparse_texture_clamp
#endif /* GL_ARB_sparse_texture_clamp */
#ifdef GL_ARB_spirv_extensions
#endif /* GL_ARB_spirv_extensions */
#ifdef GL_ARB_stencil_texturing
#endif /* GL_ARB_stencil_texturing */
#ifdef GL_ARB_sync
#endif /* GL_ARB_sync */
#ifdef GL_ARB_tessellation_shader
#endif /* GL_ARB_tessellation_shader */
#ifdef GL_ARB_texture_barrier
#endif /* GL_ARB_texture_barrier */
#ifdef GL_ARB_texture_border_clamp
#endif /* GL_ARB_texture_border_clamp */
#ifdef GL_ARB_texture_buffer_object
        glTexBufferARB = reinterpret_cast<PFNGLTEXBUFFERARBPROC>(
            _loadProcAddr("glTexBufferARB"));
#endif /* GL_ARB_texture_buffer_object */
#ifdef GL_ARB_texture_buffer_object_rgb32
#endif /* GL_ARB_texture_buffer_object_rgb32 */
#ifdef GL_ARB_texture_buffer_range
#endif /* GL_ARB_texture_buffer_range */
#ifdef GL_ARB_texture_compression_bptc
#endif /* GL_ARB_texture_compression_bptc */
#ifdef GL_ARB_texture_compression_rgtc
#endif /* GL_ARB_texture_compression_rgtc */
#ifdef GL_ARB_texture_cube_map_array
#endif /* GL_ARB_texture_cube_map_array */
#ifdef GL_ARB_texture_filter_anisotropic
#endif /* GL_ARB_texture_filter_anisotropic */
#ifdef GL_ARB_texture_filter_minmax
#endif /* GL_ARB_texture_filter_minmax */
#ifdef GL_ARB_texture_gather
#endif /* GL_ARB_texture_gather */
#ifdef GL_ARB_texture_mirror_clamp_to_edge
#endif /* GL_ARB_texture_mirror_clamp_to_edge */
#ifdef GL_ARB_texture_mirrored_repeat
#endif /* GL_ARB_texture_mirrored_repeat */
#ifdef GL_ARB_texture_multisample
#endif /* GL_ARB_texture_multisample */
#ifdef GL_ARB_texture_non_power_of_two
#endif /* GL_ARB_texture_non_power_of_two */
#ifdef GL_ARB_texture_query_levels
#endif /* GL_ARB_texture_query_levels */
#ifdef GL_ARB_texture_query_lod
#endif /* GL_ARB_texture_query_lod */
#ifdef GL_ARB_texture_rg
#endif /* GL_ARB_texture_rg */
#ifdef GL_ARB_texture_rgb10_a2ui
#endif /* GL_ARB_texture_rgb10_a2ui */
#ifdef GL_ARB_texture_stencil8
#endif /* GL_ARB_texture_stencil8 */
#ifdef GL_ARB_texture_storage
#endif /* GL_ARB_texture_storage */
#ifdef GL_ARB_texture_storage_multisample
#endif /* GL_ARB_texture_storage_multisample */
#ifdef GL_ARB_texture_swizzle
#endif /* GL_ARB_texture_swizzle */
#ifdef GL_ARB_texture_view
#endif /* GL_ARB_texture_view */
#ifdef GL_ARB_timer_query
#endif /* GL_ARB_timer_query */
#ifdef GL_ARB_transform_feedback2
#endif /* GL_ARB_transform_feedback2 */
#ifdef GL_ARB_transform_feedback3
#endif /* GL_ARB_transform_feedback3 */
#ifdef GL_ARB_transform_feedback_instanced
#endif /* GL_ARB_transform_feedback_instanced */
#ifdef GL_ARB_transform_feedback_overflow_query
#endif /* GL_ARB_transform_feedback_overflow_query */
#ifdef GL_ARB_uniform_buffer_object
#endif /* GL_ARB_uniform_buffer_object */
#ifdef GL_ARB_vertex_array_bgra
#endif /* GL_ARB_vertex_array_bgra */
#ifdef GL_ARB_vertex_array_object
#endif /* GL_ARB_vertex_array_object */
#ifdef GL_ARB_vertex_attrib_64bit
#endif /* GL_ARB_vertex_attrib_64bit */
#ifdef GL_ARB_vertex_attrib_binding
#endif /* GL_ARB_vertex_attrib_binding */
#ifdef GL_ARB_vertex_type_10f_11f_11f_rev
#endif /* GL_ARB_vertex_type_10f_11f_11f_rev */
#ifdef GL_ARB_vertex_type_2_10_10_10_rev
#endif /* GL_ARB_vertex_type_2_10_10_10_rev */
#ifdef GL_ARB_viewport_array
        glDepthRangeArraydvNV = reinterpret_cast<PFNGLDEPTHRANGEARRAYDVNVPROC>(
            _loadProcAddr("glDepthRangeArraydvNV"));
        glDepthRangeIndexeddNV =
            reinterpret_cast<PFNGLDEPTHRANGEINDEXEDDNVPROC>(
                _loadProcAddr("glDepthRangeIndexeddNV"));
#endif /* GL_ARB_viewport_array */
#ifdef GL_KHR_blend_equation_advanced
        glBlendBarrierKHR = reinterpret_cast<PFNGLBLENDBARRIERKHRPROC>(
            _loadProcAddr("glBlendBarrierKHR"));
#endif /* GL_KHR_blend_equation_advanced */
#ifdef GL_KHR_blend_equation_advanced_coherent
#endif /* GL_KHR_blend_equation_advanced_coherent */
#ifdef GL_KHR_context_flush_control
#endif /* GL_KHR_context_flush_control */
#ifdef GL_KHR_debug
#endif /* GL_KHR_debug */
#ifdef GL_KHR_no_error
#endif /* GL_KHR_no_error */
#ifdef GL_KHR_parallel_shader_compile
        glMaxShaderCompilerThreadsKHR =
            reinterpret_cast<PFNGLMAXSHADERCOMPILERTHREADSKHRPROC>(
                _loadProcAddr("glMaxShaderCompilerThreadsKHR"));
#endif /* GL_KHR_parallel_shader_compile */
#ifdef GL_KHR_robust_buffer_access_behavior
#endif /* GL_KHR_robust_buffer_access_behavior */
#ifdef GL_KHR_robustness
#endif /* GL_KHR_robustness */
#ifdef GL_KHR_shader_subgroup
#endif /* GL_KHR_shader_subgroup */
#ifdef GL_KHR_texture_compression_astc_hdr
#endif /* GL_KHR_texture_compression_astc_hdr */
#ifdef GL_KHR_texture_compression_astc_ldr
#endif /* GL_KHR_texture_compression_astc_ldr */
#ifdef GL_KHR_texture_compression_astc_sliced_3d
#endif /* GL_KHR_texture_compression_astc_sliced_3d */
#ifdef GL_AMD_framebuffer_multisample_advanced
        glRenderbufferStorageMultisampleAdvancedAMD = reinterpret_cast<
            PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC>(
            _loadProcAddr("glRenderbufferStorageMultisampleAdvancedAMD"));
        glNamedRenderbufferStorageMultisampleAdvancedAMD = reinterpret_cast<
            PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC>(
            _loadProcAddr("glNamedRenderbufferStorageMultisampleAdvancedAMD"));
#endif /* GL_AMD_framebuffer_multisample_advanced */
#ifdef GL_AMD_performance_monitor
        glGetPerfMonitorGroupsAMD =
            reinterpret_cast<PFNGLGETPERFMONITORGROUPSAMDPROC>(
                _loadProcAddr("glGetPerfMonitorGroupsAMD"));
        glGetPerfMonitorCountersAMD =
            reinterpret_cast<PFNGLGETPERFMONITORCOUNTERSAMDPROC>(
                _loadProcAddr("glGetPerfMonitorCountersAMD"));
        glGetPerfMonitorGroupStringAMD =
            reinterpret_cast<PFNGLGETPERFMONITORGROUPSTRINGAMDPROC>(
                _loadProcAddr("glGetPerfMonitorGroupStringAMD"));
        glGetPerfMonitorCounterStringAMD =
            reinterpret_cast<PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC>(
                _loadProcAddr("glGetPerfMonitorCounterStringAMD"));
        glGetPerfMonitorCounterInfoAMD =
            reinterpret_cast<PFNGLGETPERFMONITORCOUNTERINFOAMDPROC>(
                _loadProcAddr("glGetPerfMonitorCounterInfoAMD"));
        glGenPerfMonitorsAMD = reinterpret_cast<PFNGLGENPERFMONITORSAMDPROC>(
            _loadProcAddr("glGenPerfMonitorsAMD"));
        glDeletePerfMonitorsAMD =
            reinterpret_cast<PFNGLDELETEPERFMONITORSAMDPROC>(
                _loadProcAddr("glDeletePerfMonitorsAMD"));
        glSelectPerfMonitorCountersAMD =
            reinterpret_cast<PFNGLSELECTPERFMONITORCOUNTERSAMDPROC>(
                _loadProcAddr("glSelectPerfMonitorCountersAMD"));
        glBeginPerfMonitorAMD = reinterpret_cast<PFNGLBEGINPERFMONITORAMDPROC>(
            _loadProcAddr("glBeginPerfMonitorAMD"));
        glEndPerfMonitorAMD = reinterpret_cast<PFNGLENDPERFMONITORAMDPROC>(
            _loadProcAddr("glEndPerfMonitorAMD"));
        glGetPerfMonitorCounterDataAMD =
            reinterpret_cast<PFNGLGETPERFMONITORCOUNTERDATAAMDPROC>(
                _loadProcAddr("glGetPerfMonitorCounterDataAMD"));
#endif /* GL_AMD_performance_monitor */
#ifdef GL_APPLE_rgb_422
#endif /* GL_APPLE_rgb_422 */
#ifdef GL_EXT_EGL_image_storage
        glEGLImageTargetTexStorageEXT =
            reinterpret_cast<PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC>(
                _loadProcAddr("glEGLImageTargetTexStorageEXT"));
        glEGLImageTargetTextureStorageEXT =
            reinterpret_cast<PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC>(
                _loadProcAddr("glEGLImageTargetTextureStorageEXT"));
#endif /* GL_EXT_EGL_image_storage */
#ifdef GL_EXT_EGL_sync
#endif /* GL_EXT_EGL_sync */
#ifdef GL_EXT_debug_label
        glLabelObjectEXT = reinterpret_cast<PFNGLLABELOBJECTEXTPROC>(
            _loadProcAddr("glLabelObjectEXT"));
        glGetObjectLabelEXT = reinterpret_cast<PFNGLGETOBJECTLABELEXTPROC>(
            _loadProcAddr("glGetObjectLabelEXT"));
#endif /* GL_EXT_debug_label */
#ifdef GL_EXT_debug_marker
        glInsertEventMarkerEXT =
            reinterpret_cast<PFNGLINSERTEVENTMARKEREXTPROC>(
                _loadProcAddr("glInsertEventMarkerEXT"));
        glPushGroupMarkerEXT = reinterpret_cast<PFNGLPUSHGROUPMARKEREXTPROC>(
            _loadProcAddr("glPushGroupMarkerEXT"));
        glPopGroupMarkerEXT = reinterpret_cast<PFNGLPOPGROUPMARKEREXTPROC>(
            _loadProcAddr("glPopGroupMarkerEXT"));
#endif /* GL_EXT_debug_marker */
#ifdef GL_EXT_direct_state_access
        glMatrixLoadfEXT = reinterpret_cast<PFNGLMATRIXLOADFEXTPROC>(
            _loadProcAddr("glMatrixLoadfEXT"));
        glMatrixLoaddEXT = reinterpret_cast<PFNGLMATRIXLOADDEXTPROC>(
            _loadProcAddr("glMatrixLoaddEXT"));
        glMatrixMultfEXT = reinterpret_cast<PFNGLMATRIXMULTFEXTPROC>(
            _loadProcAddr("glMatrixMultfEXT"));
        glMatrixMultdEXT = reinterpret_cast<PFNGLMATRIXMULTDEXTPROC>(
            _loadProcAddr("glMatrixMultdEXT"));
        glMatrixLoadIdentityEXT =
            reinterpret_cast<PFNGLMATRIXLOADIDENTITYEXTPROC>(
                _loadProcAddr("glMatrixLoadIdentityEXT"));
        glMatrixRotatefEXT = reinterpret_cast<PFNGLMATRIXROTATEFEXTPROC>(
            _loadProcAddr("glMatrixRotatefEXT"));
        glMatrixRotatedEXT = reinterpret_cast<PFNGLMATRIXROTATEDEXTPROC>(
            _loadProcAddr("glMatrixRotatedEXT"));
        glMatrixScalefEXT = reinterpret_cast<PFNGLMATRIXSCALEFEXTPROC>(
            _loadProcAddr("glMatrixScalefEXT"));
        glMatrixScaledEXT = reinterpret_cast<PFNGLMATRIXSCALEDEXTPROC>(
            _loadProcAddr("glMatrixScaledEXT"));
        glMatrixTranslatefEXT = reinterpret_cast<PFNGLMATRIXTRANSLATEFEXTPROC>(
            _loadProcAddr("glMatrixTranslatefEXT"));
        glMatrixTranslatedEXT = reinterpret_cast<PFNGLMATRIXTRANSLATEDEXTPROC>(
            _loadProcAddr("glMatrixTranslatedEXT"));
        glMatrixFrustumEXT = reinterpret_cast<PFNGLMATRIXFRUSTUMEXTPROC>(
            _loadProcAddr("glMatrixFrustumEXT"));
        glMatrixOrthoEXT = reinterpret_cast<PFNGLMATRIXORTHOEXTPROC>(
            _loadProcAddr("glMatrixOrthoEXT"));
        glMatrixPopEXT = reinterpret_cast<PFNGLMATRIXPOPEXTPROC>(
            _loadProcAddr("glMatrixPopEXT"));
        glMatrixPushEXT = reinterpret_cast<PFNGLMATRIXPUSHEXTPROC>(
            _loadProcAddr("glMatrixPushEXT"));
        glClientAttribDefaultEXT =
            reinterpret_cast<PFNGLCLIENTATTRIBDEFAULTEXTPROC>(
                _loadProcAddr("glClientAttribDefaultEXT"));
        glPushClientAttribDefaultEXT =
            reinterpret_cast<PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC>(
                _loadProcAddr("glPushClientAttribDefaultEXT"));
        glTextureParameterfEXT =
            reinterpret_cast<PFNGLTEXTUREPARAMETERFEXTPROC>(
                _loadProcAddr("glTextureParameterfEXT"));
        glTextureParameterfvEXT =
            reinterpret_cast<PFNGLTEXTUREPARAMETERFVEXTPROC>(
                _loadProcAddr("glTextureParameterfvEXT"));
        glTextureParameteriEXT =
            reinterpret_cast<PFNGLTEXTUREPARAMETERIEXTPROC>(
                _loadProcAddr("glTextureParameteriEXT"));
        glTextureParameterivEXT =
            reinterpret_cast<PFNGLTEXTUREPARAMETERIVEXTPROC>(
                _loadProcAddr("glTextureParameterivEXT"));
        glTextureImage1DEXT = reinterpret_cast<PFNGLTEXTUREIMAGE1DEXTPROC>(
            _loadProcAddr("glTextureImage1DEXT"));
        glTextureImage2DEXT = reinterpret_cast<PFNGLTEXTUREIMAGE2DEXTPROC>(
            _loadProcAddr("glTextureImage2DEXT"));
        glTextureSubImage1DEXT =
            reinterpret_cast<PFNGLTEXTURESUBIMAGE1DEXTPROC>(
                _loadProcAddr("glTextureSubImage1DEXT"));
        glTextureSubImage2DEXT =
            reinterpret_cast<PFNGLTEXTURESUBIMAGE2DEXTPROC>(
                _loadProcAddr("glTextureSubImage2DEXT"));
        glCopyTextureImage1DEXT =
            reinterpret_cast<PFNGLCOPYTEXTUREIMAGE1DEXTPROC>(
                _loadProcAddr("glCopyTextureImage1DEXT"));
        glCopyTextureImage2DEXT =
            reinterpret_cast<PFNGLCOPYTEXTUREIMAGE2DEXTPROC>(
                _loadProcAddr("glCopyTextureImage2DEXT"));
        glCopyTextureSubImage1DEXT =
            reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC>(
                _loadProcAddr("glCopyTextureSubImage1DEXT"));
        glCopyTextureSubImage2DEXT =
            reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC>(
                _loadProcAddr("glCopyTextureSubImage2DEXT"));
        glGetTextureImageEXT = reinterpret_cast<PFNGLGETTEXTUREIMAGEEXTPROC>(
            _loadProcAddr("glGetTextureImageEXT"));
        glGetTextureParameterfvEXT =
            reinterpret_cast<PFNGLGETTEXTUREPARAMETERFVEXTPROC>(
                _loadProcAddr("glGetTextureParameterfvEXT"));
        glGetTextureParameterivEXT =
            reinterpret_cast<PFNGLGETTEXTUREPARAMETERIVEXTPROC>(
                _loadProcAddr("glGetTextureParameterivEXT"));
        glGetTextureLevelParameterfvEXT =
            reinterpret_cast<PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC>(
                _loadProcAddr("glGetTextureLevelParameterfvEXT"));
        glGetTextureLevelParameterivEXT =
            reinterpret_cast<PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC>(
                _loadProcAddr("glGetTextureLevelParameterivEXT"));
        glTextureImage3DEXT = reinterpret_cast<PFNGLTEXTUREIMAGE3DEXTPROC>(
            _loadProcAddr("glTextureImage3DEXT"));
        glTextureSubImage3DEXT =
            reinterpret_cast<PFNGLTEXTURESUBIMAGE3DEXTPROC>(
                _loadProcAddr("glTextureSubImage3DEXT"));
        glCopyTextureSubImage3DEXT =
            reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC>(
                _loadProcAddr("glCopyTextureSubImage3DEXT"));
        glBindMultiTextureEXT = reinterpret_cast<PFNGLBINDMULTITEXTUREEXTPROC>(
            _loadProcAddr("glBindMultiTextureEXT"));
        glMultiTexCoordPointerEXT =
            reinterpret_cast<PFNGLMULTITEXCOORDPOINTEREXTPROC>(
                _loadProcAddr("glMultiTexCoordPointerEXT"));
        glMultiTexEnvfEXT = reinterpret_cast<PFNGLMULTITEXENVFEXTPROC>(
            _loadProcAddr("glMultiTexEnvfEXT"));
        glMultiTexEnvfvEXT = reinterpret_cast<PFNGLMULTITEXENVFVEXTPROC>(
            _loadProcAddr("glMultiTexEnvfvEXT"));
        glMultiTexEnviEXT = reinterpret_cast<PFNGLMULTITEXENVIEXTPROC>(
            _loadProcAddr("glMultiTexEnviEXT"));
        glMultiTexEnvivEXT = reinterpret_cast<PFNGLMULTITEXENVIVEXTPROC>(
            _loadProcAddr("glMultiTexEnvivEXT"));
        glMultiTexGendEXT = reinterpret_cast<PFNGLMULTITEXGENDEXTPROC>(
            _loadProcAddr("glMultiTexGendEXT"));
        glMultiTexGendvEXT = reinterpret_cast<PFNGLMULTITEXGENDVEXTPROC>(
            _loadProcAddr("glMultiTexGendvEXT"));
        glMultiTexGenfEXT = reinterpret_cast<PFNGLMULTITEXGENFEXTPROC>(
            _loadProcAddr("glMultiTexGenfEXT"));
        glMultiTexGenfvEXT = reinterpret_cast<PFNGLMULTITEXGENFVEXTPROC>(
            _loadProcAddr("glMultiTexGenfvEXT"));
        glMultiTexGeniEXT = reinterpret_cast<PFNGLMULTITEXGENIEXTPROC>(
            _loadProcAddr("glMultiTexGeniEXT"));
        glMultiTexGenivEXT = reinterpret_cast<PFNGLMULTITEXGENIVEXTPROC>(
            _loadProcAddr("glMultiTexGenivEXT"));
        glGetMultiTexEnvfvEXT = reinterpret_cast<PFNGLGETMULTITEXENVFVEXTPROC>(
            _loadProcAddr("glGetMultiTexEnvfvEXT"));
        glGetMultiTexEnvivEXT = reinterpret_cast<PFNGLGETMULTITEXENVIVEXTPROC>(
            _loadProcAddr("glGetMultiTexEnvivEXT"));
        glGetMultiTexGendvEXT = reinterpret_cast<PFNGLGETMULTITEXGENDVEXTPROC>(
            _loadProcAddr("glGetMultiTexGendvEXT"));
        glGetMultiTexGenfvEXT = reinterpret_cast<PFNGLGETMULTITEXGENFVEXTPROC>(
            _loadProcAddr("glGetMultiTexGenfvEXT"));
        glGetMultiTexGenivEXT = reinterpret_cast<PFNGLGETMULTITEXGENIVEXTPROC>(
            _loadProcAddr("glGetMultiTexGenivEXT"));
        glMultiTexParameteriEXT =
            reinterpret_cast<PFNGLMULTITEXPARAMETERIEXTPROC>(
                _loadProcAddr("glMultiTexParameteriEXT"));
        glMultiTexParameterivEXT =
            reinterpret_cast<PFNGLMULTITEXPARAMETERIVEXTPROC>(
                _loadProcAddr("glMultiTexParameterivEXT"));
        glMultiTexParameterfEXT =
            reinterpret_cast<PFNGLMULTITEXPARAMETERFEXTPROC>(
                _loadProcAddr("glMultiTexParameterfEXT"));
        glMultiTexParameterfvEXT =
            reinterpret_cast<PFNGLMULTITEXPARAMETERFVEXTPROC>(
                _loadProcAddr("glMultiTexParameterfvEXT"));
        glMultiTexImage1DEXT = reinterpret_cast<PFNGLMULTITEXIMAGE1DEXTPROC>(
            _loadProcAddr("glMultiTexImage1DEXT"));
        glMultiTexImage2DEXT = reinterpret_cast<PFNGLMULTITEXIMAGE2DEXTPROC>(
            _loadProcAddr("glMultiTexImage2DEXT"));
        glMultiTexSubImage1DEXT =
            reinterpret_cast<PFNGLMULTITEXSUBIMAGE1DEXTPROC>(
                _loadProcAddr("glMultiTexSubImage1DEXT"));
        glMultiTexSubImage2DEXT =
            reinterpret_cast<PFNGLMULTITEXSUBIMAGE2DEXTPROC>(
                _loadProcAddr("glMultiTexSubImage2DEXT"));
        glCopyMultiTexImage1DEXT =
            reinterpret_cast<PFNGLCOPYMULTITEXIMAGE1DEXTPROC>(
                _loadProcAddr("glCopyMultiTexImage1DEXT"));
        glCopyMultiTexImage2DEXT =
            reinterpret_cast<PFNGLCOPYMULTITEXIMAGE2DEXTPROC>(
                _loadProcAddr("glCopyMultiTexImage2DEXT"));
        glCopyMultiTexSubImage1DEXT =
            reinterpret_cast<PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC>(
                _loadProcAddr("glCopyMultiTexSubImage1DEXT"));
        glCopyMultiTexSubImage2DEXT =
            reinterpret_cast<PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC>(
                _loadProcAddr("glCopyMultiTexSubImage2DEXT"));
        glGetMultiTexImageEXT = reinterpret_cast<PFNGLGETMULTITEXIMAGEEXTPROC>(
            _loadProcAddr("glGetMultiTexImageEXT"));
        glGetMultiTexParameterfvEXT =
            reinterpret_cast<PFNGLGETMULTITEXPARAMETERFVEXTPROC>(
                _loadProcAddr("glGetMultiTexParameterfvEXT"));
        glGetMultiTexParameterivEXT =
            reinterpret_cast<PFNGLGETMULTITEXPARAMETERIVEXTPROC>(
                _loadProcAddr("glGetMultiTexParameterivEXT"));
        glGetMultiTexLevelParameterfvEXT =
            reinterpret_cast<PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC>(
                _loadProcAddr("glGetMultiTexLevelParameterfvEXT"));
        glGetMultiTexLevelParameterivEXT =
            reinterpret_cast<PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC>(
                _loadProcAddr("glGetMultiTexLevelParameterivEXT"));
        glMultiTexImage3DEXT = reinterpret_cast<PFNGLMULTITEXIMAGE3DEXTPROC>(
            _loadProcAddr("glMultiTexImage3DEXT"));
        glMultiTexSubImage3DEXT =
            reinterpret_cast<PFNGLMULTITEXSUBIMAGE3DEXTPROC>(
                _loadProcAddr("glMultiTexSubImage3DEXT"));
        glCopyMultiTexSubImage3DEXT =
            reinterpret_cast<PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC>(
                _loadProcAddr("glCopyMultiTexSubImage3DEXT"));
        glEnableClientStateIndexedEXT =
            reinterpret_cast<PFNGLENABLECLIENTSTATEINDEXEDEXTPROC>(
                _loadProcAddr("glEnableClientStateIndexedEXT"));
        glDisableClientStateIndexedEXT =
            reinterpret_cast<PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC>(
                _loadProcAddr("glDisableClientStateIndexedEXT"));
        glGetFloatIndexedvEXT = reinterpret_cast<PFNGLGETFLOATINDEXEDVEXTPROC>(
            _loadProcAddr("glGetFloatIndexedvEXT"));
        glGetDoubleIndexedvEXT =
            reinterpret_cast<PFNGLGETDOUBLEINDEXEDVEXTPROC>(
                _loadProcAddr("glGetDoubleIndexedvEXT"));
        glGetPointerIndexedvEXT =
            reinterpret_cast<PFNGLGETPOINTERINDEXEDVEXTPROC>(
                _loadProcAddr("glGetPointerIndexedvEXT"));
        glEnableIndexedEXT = reinterpret_cast<PFNGLENABLEINDEXEDEXTPROC>(
            _loadProcAddr("glEnableIndexedEXT"));
        glDisableIndexedEXT = reinterpret_cast<PFNGLDISABLEINDEXEDEXTPROC>(
            _loadProcAddr("glDisableIndexedEXT"));
        glIsEnabledIndexedEXT = reinterpret_cast<PFNGLISENABLEDINDEXEDEXTPROC>(
            _loadProcAddr("glIsEnabledIndexedEXT"));
        glGetIntegerIndexedvEXT =
            reinterpret_cast<PFNGLGETINTEGERINDEXEDVEXTPROC>(
                _loadProcAddr("glGetIntegerIndexedvEXT"));
        glGetBooleanIndexedvEXT =
            reinterpret_cast<PFNGLGETBOOLEANINDEXEDVEXTPROC>(
                _loadProcAddr("glGetBooleanIndexedvEXT"));
        glCompressedTextureImage3DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC>(
                _loadProcAddr("glCompressedTextureImage3DEXT"));
        glCompressedTextureImage2DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC>(
                _loadProcAddr("glCompressedTextureImage2DEXT"));
        glCompressedTextureImage1DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC>(
                _loadProcAddr("glCompressedTextureImage1DEXT"));
        glCompressedTextureSubImage3DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC>(
                _loadProcAddr("glCompressedTextureSubImage3DEXT"));
        glCompressedTextureSubImage2DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC>(
                _loadProcAddr("glCompressedTextureSubImage2DEXT"));
        glCompressedTextureSubImage1DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC>(
                _loadProcAddr("glCompressedTextureSubImage1DEXT"));
        glGetCompressedTextureImageEXT =
            reinterpret_cast<PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC>(
                _loadProcAddr("glGetCompressedTextureImageEXT"));
        glCompressedMultiTexImage3DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC>(
                _loadProcAddr("glCompressedMultiTexImage3DEXT"));
        glCompressedMultiTexImage2DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC>(
                _loadProcAddr("glCompressedMultiTexImage2DEXT"));
        glCompressedMultiTexImage1DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC>(
                _loadProcAddr("glCompressedMultiTexImage1DEXT"));
        glCompressedMultiTexSubImage3DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC>(
                _loadProcAddr("glCompressedMultiTexSubImage3DEXT"));
        glCompressedMultiTexSubImage2DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC>(
                _loadProcAddr("glCompressedMultiTexSubImage2DEXT"));
        glCompressedMultiTexSubImage1DEXT =
            reinterpret_cast<PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC>(
                _loadProcAddr("glCompressedMultiTexSubImage1DEXT"));
        glGetCompressedMultiTexImageEXT =
            reinterpret_cast<PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC>(
                _loadProcAddr("glGetCompressedMultiTexImageEXT"));
        glMatrixLoadTransposefEXT =
            reinterpret_cast<PFNGLMATRIXLOADTRANSPOSEFEXTPROC>(
                _loadProcAddr("glMatrixLoadTransposefEXT"));
        glMatrixLoadTransposedEXT =
            reinterpret_cast<PFNGLMATRIXLOADTRANSPOSEDEXTPROC>(
                _loadProcAddr("glMatrixLoadTransposedEXT"));
        glMatrixMultTransposefEXT =
            reinterpret_cast<PFNGLMATRIXMULTTRANSPOSEFEXTPROC>(
                _loadProcAddr("glMatrixMultTransposefEXT"));
        glMatrixMultTransposedEXT =
            reinterpret_cast<PFNGLMATRIXMULTTRANSPOSEDEXTPROC>(
                _loadProcAddr("glMatrixMultTransposedEXT"));
        glNamedBufferDataEXT = reinterpret_cast<PFNGLNAMEDBUFFERDATAEXTPROC>(
            _loadProcAddr("glNamedBufferDataEXT"));
        glNamedBufferSubDataEXT =
            reinterpret_cast<PFNGLNAMEDBUFFERSUBDATAEXTPROC>(
                _loadProcAddr("glNamedBufferSubDataEXT"));
        glMapNamedBufferEXT = reinterpret_cast<PFNGLMAPNAMEDBUFFEREXTPROC>(
            _loadProcAddr("glMapNamedBufferEXT"));
        glUnmapNamedBufferEXT = reinterpret_cast<PFNGLUNMAPNAMEDBUFFEREXTPROC>(
            _loadProcAddr("glUnmapNamedBufferEXT"));
        glGetNamedBufferParameterivEXT =
            reinterpret_cast<PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC>(
                _loadProcAddr("glGetNamedBufferParameterivEXT"));
        glGetNamedBufferPointervEXT =
            reinterpret_cast<PFNGLGETNAMEDBUFFERPOINTERVEXTPROC>(
                _loadProcAddr("glGetNamedBufferPointervEXT"));
        glGetNamedBufferSubDataEXT =
            reinterpret_cast<PFNGLGETNAMEDBUFFERSUBDATAEXTPROC>(
                _loadProcAddr("glGetNamedBufferSubDataEXT"));
        glProgramUniform1fEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM1FEXTPROC>(
            _loadProcAddr("glProgramUniform1fEXT"));
        glProgramUniform2fEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM2FEXTPROC>(
            _loadProcAddr("glProgramUniform2fEXT"));
        glProgramUniform3fEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM3FEXTPROC>(
            _loadProcAddr("glProgramUniform3fEXT"));
        glProgramUniform4fEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM4FEXTPROC>(
            _loadProcAddr("glProgramUniform4fEXT"));
        glProgramUniform1iEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM1IEXTPROC>(
            _loadProcAddr("glProgramUniform1iEXT"));
        glProgramUniform2iEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM2IEXTPROC>(
            _loadProcAddr("glProgramUniform2iEXT"));
        glProgramUniform3iEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM3IEXTPROC>(
            _loadProcAddr("glProgramUniform3iEXT"));
        glProgramUniform4iEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM4IEXTPROC>(
            _loadProcAddr("glProgramUniform4iEXT"));
        glProgramUniform1fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1FVEXTPROC>(
                _loadProcAddr("glProgramUniform1fvEXT"));
        glProgramUniform2fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2FVEXTPROC>(
                _loadProcAddr("glProgramUniform2fvEXT"));
        glProgramUniform3fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3FVEXTPROC>(
                _loadProcAddr("glProgramUniform3fvEXT"));
        glProgramUniform4fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4FVEXTPROC>(
                _loadProcAddr("glProgramUniform4fvEXT"));
        glProgramUniform1ivEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1IVEXTPROC>(
                _loadProcAddr("glProgramUniform1ivEXT"));
        glProgramUniform2ivEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2IVEXTPROC>(
                _loadProcAddr("glProgramUniform2ivEXT"));
        glProgramUniform3ivEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3IVEXTPROC>(
                _loadProcAddr("glProgramUniform3ivEXT"));
        glProgramUniform4ivEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4IVEXTPROC>(
                _loadProcAddr("glProgramUniform4ivEXT"));
        glProgramUniformMatrix2fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix2fvEXT"));
        glProgramUniformMatrix3fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix3fvEXT"));
        glProgramUniformMatrix4fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix4fvEXT"));
        glProgramUniformMatrix2x3fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix2x3fvEXT"));
        glProgramUniformMatrix3x2fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix3x2fvEXT"));
        glProgramUniformMatrix2x4fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix2x4fvEXT"));
        glProgramUniformMatrix4x2fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix4x2fvEXT"));
        glProgramUniformMatrix3x4fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix3x4fvEXT"));
        glProgramUniformMatrix4x3fvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix4x3fvEXT"));
        glTextureBufferEXT = reinterpret_cast<PFNGLTEXTUREBUFFEREXTPROC>(
            _loadProcAddr("glTextureBufferEXT"));
        glMultiTexBufferEXT = reinterpret_cast<PFNGLMULTITEXBUFFEREXTPROC>(
            _loadProcAddr("glMultiTexBufferEXT"));
        glTextureParameterIivEXT =
            reinterpret_cast<PFNGLTEXTUREPARAMETERIIVEXTPROC>(
                _loadProcAddr("glTextureParameterIivEXT"));
        glTextureParameterIuivEXT =
            reinterpret_cast<PFNGLTEXTUREPARAMETERIUIVEXTPROC>(
                _loadProcAddr("glTextureParameterIuivEXT"));
        glGetTextureParameterIivEXT =
            reinterpret_cast<PFNGLGETTEXTUREPARAMETERIIVEXTPROC>(
                _loadProcAddr("glGetTextureParameterIivEXT"));
        glGetTextureParameterIuivEXT =
            reinterpret_cast<PFNGLGETTEXTUREPARAMETERIUIVEXTPROC>(
                _loadProcAddr("glGetTextureParameterIuivEXT"));
        glMultiTexParameterIivEXT =
            reinterpret_cast<PFNGLMULTITEXPARAMETERIIVEXTPROC>(
                _loadProcAddr("glMultiTexParameterIivEXT"));
        glMultiTexParameterIuivEXT =
            reinterpret_cast<PFNGLMULTITEXPARAMETERIUIVEXTPROC>(
                _loadProcAddr("glMultiTexParameterIuivEXT"));
        glGetMultiTexParameterIivEXT =
            reinterpret_cast<PFNGLGETMULTITEXPARAMETERIIVEXTPROC>(
                _loadProcAddr("glGetMultiTexParameterIivEXT"));
        glGetMultiTexParameterIuivEXT =
            reinterpret_cast<PFNGLGETMULTITEXPARAMETERIUIVEXTPROC>(
                _loadProcAddr("glGetMultiTexParameterIuivEXT"));
        glProgramUniform1uiEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1UIEXTPROC>(
                _loadProcAddr("glProgramUniform1uiEXT"));
        glProgramUniform2uiEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2UIEXTPROC>(
                _loadProcAddr("glProgramUniform2uiEXT"));
        glProgramUniform3uiEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3UIEXTPROC>(
                _loadProcAddr("glProgramUniform3uiEXT"));
        glProgramUniform4uiEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4UIEXTPROC>(
                _loadProcAddr("glProgramUniform4uiEXT"));
        glProgramUniform1uivEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1UIVEXTPROC>(
                _loadProcAddr("glProgramUniform1uivEXT"));
        glProgramUniform2uivEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2UIVEXTPROC>(
                _loadProcAddr("glProgramUniform2uivEXT"));
        glProgramUniform3uivEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3UIVEXTPROC>(
                _loadProcAddr("glProgramUniform3uivEXT"));
        glProgramUniform4uivEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4UIVEXTPROC>(
                _loadProcAddr("glProgramUniform4uivEXT"));
        glNamedProgramLocalParameters4fvEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC>(
                _loadProcAddr("glNamedProgramLocalParameters4fvEXT"));
        glNamedProgramLocalParameterI4iEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC>(
                _loadProcAddr("glNamedProgramLocalParameterI4iEXT"));
        glNamedProgramLocalParameterI4ivEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC>(
                _loadProcAddr("glNamedProgramLocalParameterI4ivEXT"));
        glNamedProgramLocalParametersI4ivEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC>(
                _loadProcAddr("glNamedProgramLocalParametersI4ivEXT"));
        glNamedProgramLocalParameterI4uiEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC>(
                _loadProcAddr("glNamedProgramLocalParameterI4uiEXT"));
        glNamedProgramLocalParameterI4uivEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC>(
                _loadProcAddr("glNamedProgramLocalParameterI4uivEXT"));
        glNamedProgramLocalParametersI4uivEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC>(
                _loadProcAddr("glNamedProgramLocalParametersI4uivEXT"));
        glGetNamedProgramLocalParameterIivEXT =
            reinterpret_cast<PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC>(
                _loadProcAddr("glGetNamedProgramLocalParameterIivEXT"));
        glGetNamedProgramLocalParameterIuivEXT =
            reinterpret_cast<PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC>(
                _loadProcAddr("glGetNamedProgramLocalParameterIuivEXT"));
        glEnableClientStateiEXT =
            reinterpret_cast<PFNGLENABLECLIENTSTATEIEXTPROC>(
                _loadProcAddr("glEnableClientStateiEXT"));
        glDisableClientStateiEXT =
            reinterpret_cast<PFNGLDISABLECLIENTSTATEIEXTPROC>(
                _loadProcAddr("glDisableClientStateiEXT"));
        glGetFloati_vEXT = reinterpret_cast<PFNGLGETFLOATI_VEXTPROC>(
            _loadProcAddr("glGetFloati_vEXT"));
        glGetDoublei_vEXT = reinterpret_cast<PFNGLGETDOUBLEI_VEXTPROC>(
            _loadProcAddr("glGetDoublei_vEXT"));
        glGetPointeri_vEXT = reinterpret_cast<PFNGLGETPOINTERI_VEXTPROC>(
            _loadProcAddr("glGetPointeri_vEXT"));
        glNamedProgramStringEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMSTRINGEXTPROC>(
                _loadProcAddr("glNamedProgramStringEXT"));
        glNamedProgramLocalParameter4dEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC>(
                _loadProcAddr("glNamedProgramLocalParameter4dEXT"));
        glNamedProgramLocalParameter4dvEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC>(
                _loadProcAddr("glNamedProgramLocalParameter4dvEXT"));
        glNamedProgramLocalParameter4fEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC>(
                _loadProcAddr("glNamedProgramLocalParameter4fEXT"));
        glNamedProgramLocalParameter4fvEXT =
            reinterpret_cast<PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC>(
                _loadProcAddr("glNamedProgramLocalParameter4fvEXT"));
        glGetNamedProgramLocalParameterdvEXT =
            reinterpret_cast<PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC>(
                _loadProcAddr("glGetNamedProgramLocalParameterdvEXT"));
        glGetNamedProgramLocalParameterfvEXT =
            reinterpret_cast<PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC>(
                _loadProcAddr("glGetNamedProgramLocalParameterfvEXT"));
        glGetNamedProgramivEXT =
            reinterpret_cast<PFNGLGETNAMEDPROGRAMIVEXTPROC>(
                _loadProcAddr("glGetNamedProgramivEXT"));
        glGetNamedProgramStringEXT =
            reinterpret_cast<PFNGLGETNAMEDPROGRAMSTRINGEXTPROC>(
                _loadProcAddr("glGetNamedProgramStringEXT"));
        glNamedRenderbufferStorageEXT =
            reinterpret_cast<PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC>(
                _loadProcAddr("glNamedRenderbufferStorageEXT"));
        glGetNamedRenderbufferParameterivEXT =
            reinterpret_cast<PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC>(
                _loadProcAddr("glGetNamedRenderbufferParameterivEXT"));
        glNamedRenderbufferStorageMultisampleEXT =
            reinterpret_cast<PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC>(
                _loadProcAddr("glNamedRenderbufferStorageMultisampleEXT"));
        glNamedRenderbufferStorageMultisampleCoverageEXT = reinterpret_cast<
            PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC>(
            _loadProcAddr("glNamedRenderbufferStorageMultisampleCoverageEXT"));
        glCheckNamedFramebufferStatusEXT =
            reinterpret_cast<PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC>(
                _loadProcAddr("glCheckNamedFramebufferStatusEXT"));
        glNamedFramebufferTexture1DEXT =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC>(
                _loadProcAddr("glNamedFramebufferTexture1DEXT"));
        glNamedFramebufferTexture2DEXT =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC>(
                _loadProcAddr("glNamedFramebufferTexture2DEXT"));
        glNamedFramebufferTexture3DEXT =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC>(
                _loadProcAddr("glNamedFramebufferTexture3DEXT"));
        glNamedFramebufferRenderbufferEXT =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC>(
                _loadProcAddr("glNamedFramebufferRenderbufferEXT"));
        glGetNamedFramebufferAttachmentParameterivEXT = reinterpret_cast<
            PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC>(
            _loadProcAddr("glGetNamedFramebufferAttachmentParameterivEXT"));
        glGenerateTextureMipmapEXT =
            reinterpret_cast<PFNGLGENERATETEXTUREMIPMAPEXTPROC>(
                _loadProcAddr("glGenerateTextureMipmapEXT"));
        glGenerateMultiTexMipmapEXT =
            reinterpret_cast<PFNGLGENERATEMULTITEXMIPMAPEXTPROC>(
                _loadProcAddr("glGenerateMultiTexMipmapEXT"));
        glFramebufferDrawBufferEXT =
            reinterpret_cast<PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC>(
                _loadProcAddr("glFramebufferDrawBufferEXT"));
        glFramebufferDrawBuffersEXT =
            reinterpret_cast<PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC>(
                _loadProcAddr("glFramebufferDrawBuffersEXT"));
        glFramebufferReadBufferEXT =
            reinterpret_cast<PFNGLFRAMEBUFFERREADBUFFEREXTPROC>(
                _loadProcAddr("glFramebufferReadBufferEXT"));
        glGetFramebufferParameterivEXT =
            reinterpret_cast<PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC>(
                _loadProcAddr("glGetFramebufferParameterivEXT"));
        glNamedCopyBufferSubDataEXT =
            reinterpret_cast<PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC>(
                _loadProcAddr("glNamedCopyBufferSubDataEXT"));
        glNamedFramebufferTextureEXT =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC>(
                _loadProcAddr("glNamedFramebufferTextureEXT"));
        glNamedFramebufferTextureLayerEXT =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC>(
                _loadProcAddr("glNamedFramebufferTextureLayerEXT"));
        glNamedFramebufferTextureFaceEXT =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC>(
                _loadProcAddr("glNamedFramebufferTextureFaceEXT"));
        glTextureRenderbufferEXT =
            reinterpret_cast<PFNGLTEXTURERENDERBUFFEREXTPROC>(
                _loadProcAddr("glTextureRenderbufferEXT"));
        glMultiTexRenderbufferEXT =
            reinterpret_cast<PFNGLMULTITEXRENDERBUFFEREXTPROC>(
                _loadProcAddr("glMultiTexRenderbufferEXT"));
        glVertexArrayVertexOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC>(
                _loadProcAddr("glVertexArrayVertexOffsetEXT"));
        glVertexArrayColorOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYCOLOROFFSETEXTPROC>(
                _loadProcAddr("glVertexArrayColorOffsetEXT"));
        glVertexArrayEdgeFlagOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC>(
                _loadProcAddr("glVertexArrayEdgeFlagOffsetEXT"));
        glVertexArrayIndexOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYINDEXOFFSETEXTPROC>(
                _loadProcAddr("glVertexArrayIndexOffsetEXT"));
        glVertexArrayNormalOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYNORMALOFFSETEXTPROC>(
                _loadProcAddr("glVertexArrayNormalOffsetEXT"));
        glVertexArrayTexCoordOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC>(
                _loadProcAddr("glVertexArrayTexCoordOffsetEXT"));
        glVertexArrayMultiTexCoordOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC>(
                _loadProcAddr("glVertexArrayMultiTexCoordOffsetEXT"));
        glVertexArrayFogCoordOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC>(
                _loadProcAddr("glVertexArrayFogCoordOffsetEXT"));
        glVertexArraySecondaryColorOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC>(
                _loadProcAddr("glVertexArraySecondaryColorOffsetEXT"));
        glVertexArrayVertexAttribOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC>(
                _loadProcAddr("glVertexArrayVertexAttribOffsetEXT"));
        glVertexArrayVertexAttribIOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC>(
                _loadProcAddr("glVertexArrayVertexAttribIOffsetEXT"));
        glEnableVertexArrayEXT =
            reinterpret_cast<PFNGLENABLEVERTEXARRAYEXTPROC>(
                _loadProcAddr("glEnableVertexArrayEXT"));
        glDisableVertexArrayEXT =
            reinterpret_cast<PFNGLDISABLEVERTEXARRAYEXTPROC>(
                _loadProcAddr("glDisableVertexArrayEXT"));
        glEnableVertexArrayAttribEXT =
            reinterpret_cast<PFNGLENABLEVERTEXARRAYATTRIBEXTPROC>(
                _loadProcAddr("glEnableVertexArrayAttribEXT"));
        glDisableVertexArrayAttribEXT =
            reinterpret_cast<PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC>(
                _loadProcAddr("glDisableVertexArrayAttribEXT"));
        glGetVertexArrayIntegervEXT =
            reinterpret_cast<PFNGLGETVERTEXARRAYINTEGERVEXTPROC>(
                _loadProcAddr("glGetVertexArrayIntegervEXT"));
        glGetVertexArrayPointervEXT =
            reinterpret_cast<PFNGLGETVERTEXARRAYPOINTERVEXTPROC>(
                _loadProcAddr("glGetVertexArrayPointervEXT"));
        glGetVertexArrayIntegeri_vEXT =
            reinterpret_cast<PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC>(
                _loadProcAddr("glGetVertexArrayIntegeri_vEXT"));
        glGetVertexArrayPointeri_vEXT =
            reinterpret_cast<PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC>(
                _loadProcAddr("glGetVertexArrayPointeri_vEXT"));
        glMapNamedBufferRangeEXT =
            reinterpret_cast<PFNGLMAPNAMEDBUFFERRANGEEXTPROC>(
                _loadProcAddr("glMapNamedBufferRangeEXT"));
        glFlushMappedNamedBufferRangeEXT =
            reinterpret_cast<PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC>(
                _loadProcAddr("glFlushMappedNamedBufferRangeEXT"));
        glNamedBufferStorageEXT =
            reinterpret_cast<PFNGLNAMEDBUFFERSTORAGEEXTPROC>(
                _loadProcAddr("glNamedBufferStorageEXT"));
        glClearNamedBufferDataEXT =
            reinterpret_cast<PFNGLCLEARNAMEDBUFFERDATAEXTPROC>(
                _loadProcAddr("glClearNamedBufferDataEXT"));
        glClearNamedBufferSubDataEXT =
            reinterpret_cast<PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC>(
                _loadProcAddr("glClearNamedBufferSubDataEXT"));
        glNamedFramebufferParameteriEXT =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC>(
                _loadProcAddr("glNamedFramebufferParameteriEXT"));
        glGetNamedFramebufferParameterivEXT =
            reinterpret_cast<PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC>(
                _loadProcAddr("glGetNamedFramebufferParameterivEXT"));
        glProgramUniform1dEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM1DEXTPROC>(
            _loadProcAddr("glProgramUniform1dEXT"));
        glProgramUniform2dEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM2DEXTPROC>(
            _loadProcAddr("glProgramUniform2dEXT"));
        glProgramUniform3dEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM3DEXTPROC>(
            _loadProcAddr("glProgramUniform3dEXT"));
        glProgramUniform4dEXT = reinterpret_cast<PFNGLPROGRAMUNIFORM4DEXTPROC>(
            _loadProcAddr("glProgramUniform4dEXT"));
        glProgramUniform1dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1DVEXTPROC>(
                _loadProcAddr("glProgramUniform1dvEXT"));
        glProgramUniform2dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2DVEXTPROC>(
                _loadProcAddr("glProgramUniform2dvEXT"));
        glProgramUniform3dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3DVEXTPROC>(
                _loadProcAddr("glProgramUniform3dvEXT"));
        glProgramUniform4dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4DVEXTPROC>(
                _loadProcAddr("glProgramUniform4dvEXT"));
        glProgramUniformMatrix2dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix2dvEXT"));
        glProgramUniformMatrix3dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix3dvEXT"));
        glProgramUniformMatrix4dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix4dvEXT"));
        glProgramUniformMatrix2x3dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix2x3dvEXT"));
        glProgramUniformMatrix2x4dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix2x4dvEXT"));
        glProgramUniformMatrix3x2dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix3x2dvEXT"));
        glProgramUniformMatrix3x4dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix3x4dvEXT"));
        glProgramUniformMatrix4x2dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix4x2dvEXT"));
        glProgramUniformMatrix4x3dvEXT =
            reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC>(
                _loadProcAddr("glProgramUniformMatrix4x3dvEXT"));
        glTextureBufferRangeEXT =
            reinterpret_cast<PFNGLTEXTUREBUFFERRANGEEXTPROC>(
                _loadProcAddr("glTextureBufferRangeEXT"));
        glTextureStorage1DEXT = reinterpret_cast<PFNGLTEXTURESTORAGE1DEXTPROC>(
            _loadProcAddr("glTextureStorage1DEXT"));
        glTextureStorage2DEXT = reinterpret_cast<PFNGLTEXTURESTORAGE2DEXTPROC>(
            _loadProcAddr("glTextureStorage2DEXT"));
        glTextureStorage3DEXT = reinterpret_cast<PFNGLTEXTURESTORAGE3DEXTPROC>(
            _loadProcAddr("glTextureStorage3DEXT"));
        glTextureStorage2DMultisampleEXT =
            reinterpret_cast<PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC>(
                _loadProcAddr("glTextureStorage2DMultisampleEXT"));
        glTextureStorage3DMultisampleEXT =
            reinterpret_cast<PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC>(
                _loadProcAddr("glTextureStorage3DMultisampleEXT"));
        glVertexArrayBindVertexBufferEXT =
            reinterpret_cast<PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC>(
                _loadProcAddr("glVertexArrayBindVertexBufferEXT"));
        glVertexArrayVertexAttribFormatEXT =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC>(
                _loadProcAddr("glVertexArrayVertexAttribFormatEXT"));
        glVertexArrayVertexAttribIFormatEXT =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC>(
                _loadProcAddr("glVertexArrayVertexAttribIFormatEXT"));
        glVertexArrayVertexAttribLFormatEXT =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC>(
                _loadProcAddr("glVertexArrayVertexAttribLFormatEXT"));
        glVertexArrayVertexAttribBindingEXT =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC>(
                _loadProcAddr("glVertexArrayVertexAttribBindingEXT"));
        glVertexArrayVertexBindingDivisorEXT =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC>(
                _loadProcAddr("glVertexArrayVertexBindingDivisorEXT"));
        glVertexArrayVertexAttribLOffsetEXT =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC>(
                _loadProcAddr("glVertexArrayVertexAttribLOffsetEXT"));
        glTexturePageCommitmentEXT =
            reinterpret_cast<PFNGLTEXTUREPAGECOMMITMENTEXTPROC>(
                _loadProcAddr("glTexturePageCommitmentEXT"));
        glVertexArrayVertexAttribDivisorEXT =
            reinterpret_cast<PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC>(
                _loadProcAddr("glVertexArrayVertexAttribDivisorEXT"));
#endif /* GL_EXT_direct_state_access */
#ifdef GL_EXT_draw_instanced
        glDrawArraysInstancedEXT =
            reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDEXTPROC>(
                _loadProcAddr("glDrawArraysInstancedEXT"));
        glDrawElementsInstancedEXT =
            reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDEXTPROC>(
                _loadProcAddr("glDrawElementsInstancedEXT"));
#endif /* GL_EXT_draw_instanced */
#ifdef GL_EXT_multiview_tessellation_geometry_shader
#endif /* GL_EXT_multiview_tessellation_geometry_shader */
#ifdef GL_EXT_multiview_texture_multisample
#endif /* GL_EXT_multiview_texture_multisample */
#ifdef GL_EXT_multiview_timer_query
#endif /* GL_EXT_multiview_timer_query */
#ifdef GL_EXT_polygon_offset_clamp
        glPolygonOffsetClampEXT =
            reinterpret_cast<PFNGLPOLYGONOFFSETCLAMPEXTPROC>(
                _loadProcAddr("glPolygonOffsetClampEXT"));
#endif /* GL_EXT_polygon_offset_clamp */
#ifdef GL_EXT_post_depth_coverage
#endif /* GL_EXT_post_depth_coverage */
#ifdef GL_EXT_raster_multisample
        glRasterSamplesEXT = reinterpret_cast<PFNGLRASTERSAMPLESEXTPROC>(
            _loadProcAddr("glRasterSamplesEXT"));
#endif /* GL_EXT_raster_multisample */
#ifdef GL_EXT_separate_shader_objects
        glUseShaderProgramEXT = reinterpret_cast<PFNGLUSESHADERPROGRAMEXTPROC>(
            _loadProcAddr("glUseShaderProgramEXT"));
        glActiveProgramEXT = reinterpret_cast<PFNGLACTIVEPROGRAMEXTPROC>(
            _loadProcAddr("glActiveProgramEXT"));
        glCreateShaderProgramEXT =
            reinterpret_cast<PFNGLCREATESHADERPROGRAMEXTPROC>(
                _loadProcAddr("glCreateShaderProgramEXT"));
#endif /* GL_EXT_separate_shader_objects */
#ifdef GL_EXT_shader_framebuffer_fetch
#endif /* GL_EXT_shader_framebuffer_fetch */
#ifdef GL_EXT_shader_framebuffer_fetch_non_coherent
        glFramebufferFetchBarrierEXT =
            reinterpret_cast<PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC>(
                _loadProcAddr("glFramebufferFetchBarrierEXT"));
#endif /* GL_EXT_shader_framebuffer_fetch_non_coherent */
#ifdef GL_EXT_shader_integer_mix
#endif /* GL_EXT_shader_integer_mix */
#ifdef GL_EXT_texture_compression_s3tc
#endif /* GL_EXT_texture_compression_s3tc */
#ifdef GL_EXT_texture_filter_minmax
#endif /* GL_EXT_texture_filter_minmax */
#ifdef GL_EXT_texture_sRGB_R8
#endif /* GL_EXT_texture_sRGB_R8 */
#ifdef GL_EXT_texture_sRGB_decode
#endif /* GL_EXT_texture_sRGB_decode */
#ifdef GL_EXT_texture_shadow_lod
#endif /* GL_EXT_texture_shadow_lod */
#ifdef GL_EXT_window_rectangles
        glWindowRectanglesEXT = reinterpret_cast<PFNGLWINDOWRECTANGLESEXTPROC>(
            _loadProcAddr("glWindowRectanglesEXT"));
#endif /* GL_EXT_window_rectangles */
#ifdef GL_INTEL_blackhole_render
#endif /* GL_INTEL_blackhole_render */
#ifdef GL_INTEL_conservative_rasterization
#endif /* GL_INTEL_conservative_rasterization */
#ifdef GL_INTEL_framebuffer_CMAA
        glApplyFramebufferAttachmentCMAAINTEL =
            reinterpret_cast<PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC>(
                _loadProcAddr("glApplyFramebufferAttachmentCMAAINTEL"));
#endif /* GL_INTEL_framebuffer_CMAA */
#ifdef GL_INTEL_performance_query
        glBeginPerfQueryINTEL = reinterpret_cast<PFNGLBEGINPERFQUERYINTELPROC>(
            _loadProcAddr("glBeginPerfQueryINTEL"));
        glCreatePerfQueryINTEL =
            reinterpret_cast<PFNGLCREATEPERFQUERYINTELPROC>(
                _loadProcAddr("glCreatePerfQueryINTEL"));
        glDeletePerfQueryINTEL =
            reinterpret_cast<PFNGLDELETEPERFQUERYINTELPROC>(
                _loadProcAddr("glDeletePerfQueryINTEL"));
        glEndPerfQueryINTEL = reinterpret_cast<PFNGLENDPERFQUERYINTELPROC>(
            _loadProcAddr("glEndPerfQueryINTEL"));
        glGetFirstPerfQueryIdINTEL =
            reinterpret_cast<PFNGLGETFIRSTPERFQUERYIDINTELPROC>(
                _loadProcAddr("glGetFirstPerfQueryIdINTEL"));
        glGetNextPerfQueryIdINTEL =
            reinterpret_cast<PFNGLGETNEXTPERFQUERYIDINTELPROC>(
                _loadProcAddr("glGetNextPerfQueryIdINTEL"));
        glGetPerfCounterInfoINTEL =
            reinterpret_cast<PFNGLGETPERFCOUNTERINFOINTELPROC>(
                _loadProcAddr("glGetPerfCounterInfoINTEL"));
        glGetPerfQueryDataINTEL =
            reinterpret_cast<PFNGLGETPERFQUERYDATAINTELPROC>(
                _loadProcAddr("glGetPerfQueryDataINTEL"));
        glGetPerfQueryIdByNameINTEL =
            reinterpret_cast<PFNGLGETPERFQUERYIDBYNAMEINTELPROC>(
                _loadProcAddr("glGetPerfQueryIdByNameINTEL"));
        glGetPerfQueryInfoINTEL =
            reinterpret_cast<PFNGLGETPERFQUERYINFOINTELPROC>(
                _loadProcAddr("glGetPerfQueryInfoINTEL"));
#endif /* GL_INTEL_performance_query */
#ifdef GL_MESA_framebuffer_flip_x
#endif /* GL_MESA_framebuffer_flip_x */
#ifdef GL_MESA_framebuffer_flip_y
        glFramebufferParameteriMESA =
            reinterpret_cast<PFNGLFRAMEBUFFERPARAMETERIMESAPROC>(
                _loadProcAddr("glFramebufferParameteriMESA"));
        glGetFramebufferParameterivMESA =
            reinterpret_cast<PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC>(
                _loadProcAddr("glGetFramebufferParameterivMESA"));
#endif /* GL_MESA_framebuffer_flip_y */
#ifdef GL_MESA_framebuffer_swap_xy
#endif /* GL_MESA_framebuffer_swap_xy */
#ifdef GL_NV_bindless_multi_draw_indirect
        glMultiDrawArraysIndirectBindlessNV =
            reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC>(
                _loadProcAddr("glMultiDrawArraysIndirectBindlessNV"));
        glMultiDrawElementsIndirectBindlessNV =
            reinterpret_cast<PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC>(
                _loadProcAddr("glMultiDrawElementsIndirectBindlessNV"));
#endif /* GL_NV_bindless_multi_draw_indirect */
#ifdef GL_NV_bindless_multi_draw_indirect_count
        glMultiDrawArraysIndirectBindlessCountNV =
            reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC>(
                _loadProcAddr("glMultiDrawArraysIndirectBindlessCountNV"));
        glMultiDrawElementsIndirectBindlessCountNV =
            reinterpret_cast<PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC>(
                _loadProcAddr("glMultiDrawElementsIndirectBindlessCountNV"));
#endif /* GL_NV_bindless_multi_draw_indirect_count */
#ifdef GL_NV_bindless_texture
        glGetTextureHandleNV = reinterpret_cast<PFNGLGETTEXTUREHANDLENVPROC>(
            _loadProcAddr("glGetTextureHandleNV"));
        glGetTextureSamplerHandleNV =
            reinterpret_cast<PFNGLGETTEXTURESAMPLERHANDLENVPROC>(
                _loadProcAddr("glGetTextureSamplerHandleNV"));
        glMakeTextureHandleResidentNV =
            reinterpret_cast<PFNGLMAKETEXTUREHANDLERESIDENTNVPROC>(
                _loadProcAddr("glMakeTextureHandleResidentNV"));
        glMakeTextureHandleNonResidentNV =
            reinterpret_cast<PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC>(
                _loadProcAddr("glMakeTextureHandleNonResidentNV"));
        glGetImageHandleNV = reinterpret_cast<PFNGLGETIMAGEHANDLENVPROC>(
            _loadProcAddr("glGetImageHandleNV"));
        glMakeImageHandleResidentNV =
            reinterpret_cast<PFNGLMAKEIMAGEHANDLERESIDENTNVPROC>(
                _loadProcAddr("glMakeImageHandleResidentNV"));
        glMakeImageHandleNonResidentNV =
            reinterpret_cast<PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC>(
                _loadProcAddr("glMakeImageHandleNonResidentNV"));
        glUniformHandleui64NV = reinterpret_cast<PFNGLUNIFORMHANDLEUI64NVPROC>(
            _loadProcAddr("glUniformHandleui64NV"));
        glUniformHandleui64vNV =
            reinterpret_cast<PFNGLUNIFORMHANDLEUI64VNVPROC>(
                _loadProcAddr("glUniformHandleui64vNV"));
        glProgramUniformHandleui64NV =
            reinterpret_cast<PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC>(
                _loadProcAddr("glProgramUniformHandleui64NV"));
        glProgramUniformHandleui64vNV =
            reinterpret_cast<PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC>(
                _loadProcAddr("glProgramUniformHandleui64vNV"));
        glIsTextureHandleResidentNV =
            reinterpret_cast<PFNGLISTEXTUREHANDLERESIDENTNVPROC>(
                _loadProcAddr("glIsTextureHandleResidentNV"));
        glIsImageHandleResidentNV =
            reinterpret_cast<PFNGLISIMAGEHANDLERESIDENTNVPROC>(
                _loadProcAddr("glIsImageHandleResidentNV"));
#endif /* GL_NV_bindless_texture */
#ifdef GL_NV_blend_equation_advanced
        glBlendParameteriNV = reinterpret_cast<PFNGLBLENDPARAMETERINVPROC>(
            _loadProcAddr("glBlendParameteriNV"));
        glBlendBarrierNV = reinterpret_cast<PFNGLBLENDBARRIERNVPROC>(
            _loadProcAddr("glBlendBarrierNV"));
#endif /* GL_NV_blend_equation_advanced */
#ifdef GL_NV_blend_equation_advanced_coherent
#endif /* GL_NV_blend_equation_advanced_coherent */
#ifdef GL_NV_blend_minmax_factor
#endif /* GL_NV_blend_minmax_factor */
#ifdef GL_NV_clip_space_w_scaling
        glViewportPositionWScaleNV =
            reinterpret_cast<PFNGLVIEWPORTPOSITIONWSCALENVPROC>(
                _loadProcAddr("glViewportPositionWScaleNV"));
#endif /* GL_NV_clip_space_w_scaling */
#ifdef GL_NV_command_list
        glCreateStatesNV = reinterpret_cast<PFNGLCREATESTATESNVPROC>(
            _loadProcAddr("glCreateStatesNV"));
        glDeleteStatesNV = reinterpret_cast<PFNGLDELETESTATESNVPROC>(
            _loadProcAddr("glDeleteStatesNV"));
        glIsStateNV =
            reinterpret_cast<PFNGLISSTATENVPROC>(_loadProcAddr("glIsStateNV"));
        glStateCaptureNV = reinterpret_cast<PFNGLSTATECAPTURENVPROC>(
            _loadProcAddr("glStateCaptureNV"));
        glGetCommandHeaderNV = reinterpret_cast<PFNGLGETCOMMANDHEADERNVPROC>(
            _loadProcAddr("glGetCommandHeaderNV"));
        glGetStageIndexNV = reinterpret_cast<PFNGLGETSTAGEINDEXNVPROC>(
            _loadProcAddr("glGetStageIndexNV"));
        glDrawCommandsNV = reinterpret_cast<PFNGLDRAWCOMMANDSNVPROC>(
            _loadProcAddr("glDrawCommandsNV"));
        glDrawCommandsAddressNV =
            reinterpret_cast<PFNGLDRAWCOMMANDSADDRESSNVPROC>(
                _loadProcAddr("glDrawCommandsAddressNV"));
        glDrawCommandsStatesNV =
            reinterpret_cast<PFNGLDRAWCOMMANDSSTATESNVPROC>(
                _loadProcAddr("glDrawCommandsStatesNV"));
        glDrawCommandsStatesAddressNV =
            reinterpret_cast<PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC>(
                _loadProcAddr("glDrawCommandsStatesAddressNV"));
        glCreateCommandListsNV =
            reinterpret_cast<PFNGLCREATECOMMANDLISTSNVPROC>(
                _loadProcAddr("glCreateCommandListsNV"));
        glDeleteCommandListsNV =
            reinterpret_cast<PFNGLDELETECOMMANDLISTSNVPROC>(
                _loadProcAddr("glDeleteCommandListsNV"));
        glIsCommandListNV = reinterpret_cast<PFNGLISCOMMANDLISTNVPROC>(
            _loadProcAddr("glIsCommandListNV"));
        glListDrawCommandsStatesClientNV =
            reinterpret_cast<PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC>(
                _loadProcAddr("glListDrawCommandsStatesClientNV"));
        glCommandListSegmentsNV =
            reinterpret_cast<PFNGLCOMMANDLISTSEGMENTSNVPROC>(
                _loadProcAddr("glCommandListSegmentsNV"));
        glCompileCommandListNV =
            reinterpret_cast<PFNGLCOMPILECOMMANDLISTNVPROC>(
                _loadProcAddr("glCompileCommandListNV"));
        glCallCommandListNV = reinterpret_cast<PFNGLCALLCOMMANDLISTNVPROC>(
            _loadProcAddr("glCallCommandListNV"));
#endif /* GL_NV_command_list */
#ifdef GL_NV_compute_shader_derivatives
#endif /* GL_NV_compute_shader_derivatives */
#ifdef GL_NV_conditional_render
        glBeginConditionalRenderNV =
            reinterpret_cast<PFNGLBEGINCONDITIONALRENDERNVPROC>(
                _loadProcAddr("glBeginConditionalRenderNV"));
        glEndConditionalRenderNV =
            reinterpret_cast<PFNGLENDCONDITIONALRENDERNVPROC>(
                _loadProcAddr("glEndConditionalRenderNV"));
#endif /* GL_NV_conditional_render */
#ifdef GL_NV_conservative_raster
        glSubpixelPrecisionBiasNV =
            reinterpret_cast<PFNGLSUBPIXELPRECISIONBIASNVPROC>(
                _loadProcAddr("glSubpixelPrecisionBiasNV"));
#endif /* GL_NV_conservative_raster */
#ifdef GL_NV_conservative_raster_dilate
        glConservativeRasterParameterfNV =
            reinterpret_cast<PFNGLCONSERVATIVERASTERPARAMETERFNVPROC>(
                _loadProcAddr("glConservativeRasterParameterfNV"));
#endif /* GL_NV_conservative_raster_dilate */
#ifdef GL_NV_conservative_raster_pre_snap
#endif /* GL_NV_conservative_raster_pre_snap */
#ifdef GL_NV_conservative_raster_pre_snap_triangles
        glConservativeRasterParameteriNV =
            reinterpret_cast<PFNGLCONSERVATIVERASTERPARAMETERINVPROC>(
                _loadProcAddr("glConservativeRasterParameteriNV"));
#endif /* GL_NV_conservative_raster_pre_snap_triangles */
#ifdef GL_NV_conservative_raster_underestimation
#endif /* GL_NV_conservative_raster_underestimation */
#ifdef GL_NV_depth_buffer_float
        glDepthRangedNV = reinterpret_cast<PFNGLDEPTHRANGEDNVPROC>(
            _loadProcAddr("glDepthRangedNV"));
        glClearDepthdNV = reinterpret_cast<PFNGLCLEARDEPTHDNVPROC>(
            _loadProcAddr("glClearDepthdNV"));
        glDepthBoundsdNV = reinterpret_cast<PFNGLDEPTHBOUNDSDNVPROC>(
            _loadProcAddr("glDepthBoundsdNV"));
#endif /* GL_NV_depth_buffer_float */
#ifdef GL_NV_draw_vulkan_image
        glDrawVkImageNV = reinterpret_cast<PFNGLDRAWVKIMAGENVPROC>(
            _loadProcAddr("glDrawVkImageNV"));
        glGetVkProcAddrNV = reinterpret_cast<PFNGLGETVKPROCADDRNVPROC>(
            _loadProcAddr("glGetVkProcAddrNV"));
        glWaitVkSemaphoreNV = reinterpret_cast<PFNGLWAITVKSEMAPHORENVPROC>(
            _loadProcAddr("glWaitVkSemaphoreNV"));
        glSignalVkSemaphoreNV = reinterpret_cast<PFNGLSIGNALVKSEMAPHORENVPROC>(
            _loadProcAddr("glSignalVkSemaphoreNV"));
        glSignalVkFenceNV = reinterpret_cast<PFNGLSIGNALVKFENCENVPROC>(
            _loadProcAddr("glSignalVkFenceNV"));
#endif /* GL_NV_draw_vulkan_image */
#ifdef GL_NV_fill_rectangle
#endif /* GL_NV_fill_rectangle */
#ifdef GL_NV_fragment_coverage_to_color
        glFragmentCoverageColorNV =
            reinterpret_cast<PFNGLFRAGMENTCOVERAGECOLORNVPROC>(
                _loadProcAddr("glFragmentCoverageColorNV"));
#endif /* GL_NV_fragment_coverage_to_color */
#ifdef GL_NV_fragment_shader_barycentric
#endif /* GL_NV_fragment_shader_barycentric */
#ifdef GL_NV_fragment_shader_interlock
#endif /* GL_NV_fragment_shader_interlock */
#ifdef GL_NV_framebuffer_mixed_samples
        glCoverageModulationTableNV =
            reinterpret_cast<PFNGLCOVERAGEMODULATIONTABLENVPROC>(
                _loadProcAddr("glCoverageModulationTableNV"));
        glGetCoverageModulationTableNV =
            reinterpret_cast<PFNGLGETCOVERAGEMODULATIONTABLENVPROC>(
                _loadProcAddr("glGetCoverageModulationTableNV"));
        glCoverageModulationNV =
            reinterpret_cast<PFNGLCOVERAGEMODULATIONNVPROC>(
                _loadProcAddr("glCoverageModulationNV"));
#endif /* GL_NV_framebuffer_mixed_samples */
#ifdef GL_NV_framebuffer_multisample_coverage
        glRenderbufferStorageMultisampleCoverageNV =
            reinterpret_cast<PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC>(
                _loadProcAddr("glRenderbufferStorageMultisampleCoverageNV"));
#endif /* GL_NV_framebuffer_multisample_coverage */
#ifdef GL_NV_geometry_shader_passthrough
#endif /* GL_NV_geometry_shader_passthrough */
#ifdef GL_NV_gpu_shader5
        glUniform1i64NV = reinterpret_cast<PFNGLUNIFORM1I64NVPROC>(
            _loadProcAddr("glUniform1i64NV"));
        glUniform2i64NV = reinterpret_cast<PFNGLUNIFORM2I64NVPROC>(
            _loadProcAddr("glUniform2i64NV"));
        glUniform3i64NV = reinterpret_cast<PFNGLUNIFORM3I64NVPROC>(
            _loadProcAddr("glUniform3i64NV"));
        glUniform4i64NV = reinterpret_cast<PFNGLUNIFORM4I64NVPROC>(
            _loadProcAddr("glUniform4i64NV"));
        glUniform1i64vNV = reinterpret_cast<PFNGLUNIFORM1I64VNVPROC>(
            _loadProcAddr("glUniform1i64vNV"));
        glUniform2i64vNV = reinterpret_cast<PFNGLUNIFORM2I64VNVPROC>(
            _loadProcAddr("glUniform2i64vNV"));
        glUniform3i64vNV = reinterpret_cast<PFNGLUNIFORM3I64VNVPROC>(
            _loadProcAddr("glUniform3i64vNV"));
        glUniform4i64vNV = reinterpret_cast<PFNGLUNIFORM4I64VNVPROC>(
            _loadProcAddr("glUniform4i64vNV"));
        glUniform1ui64NV = reinterpret_cast<PFNGLUNIFORM1UI64NVPROC>(
            _loadProcAddr("glUniform1ui64NV"));
        glUniform2ui64NV = reinterpret_cast<PFNGLUNIFORM2UI64NVPROC>(
            _loadProcAddr("glUniform2ui64NV"));
        glUniform3ui64NV = reinterpret_cast<PFNGLUNIFORM3UI64NVPROC>(
            _loadProcAddr("glUniform3ui64NV"));
        glUniform4ui64NV = reinterpret_cast<PFNGLUNIFORM4UI64NVPROC>(
            _loadProcAddr("glUniform4ui64NV"));
        glUniform1ui64vNV = reinterpret_cast<PFNGLUNIFORM1UI64VNVPROC>(
            _loadProcAddr("glUniform1ui64vNV"));
        glUniform2ui64vNV = reinterpret_cast<PFNGLUNIFORM2UI64VNVPROC>(
            _loadProcAddr("glUniform2ui64vNV"));
        glUniform3ui64vNV = reinterpret_cast<PFNGLUNIFORM3UI64VNVPROC>(
            _loadProcAddr("glUniform3ui64vNV"));
        glUniform4ui64vNV = reinterpret_cast<PFNGLUNIFORM4UI64VNVPROC>(
            _loadProcAddr("glUniform4ui64vNV"));
        glGetUniformi64vNV = reinterpret_cast<PFNGLGETUNIFORMI64VNVPROC>(
            _loadProcAddr("glGetUniformi64vNV"));
        glProgramUniform1i64NV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1I64NVPROC>(
                _loadProcAddr("glProgramUniform1i64NV"));
        glProgramUniform2i64NV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2I64NVPROC>(
                _loadProcAddr("glProgramUniform2i64NV"));
        glProgramUniform3i64NV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3I64NVPROC>(
                _loadProcAddr("glProgramUniform3i64NV"));
        glProgramUniform4i64NV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4I64NVPROC>(
                _loadProcAddr("glProgramUniform4i64NV"));
        glProgramUniform1i64vNV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1I64VNVPROC>(
                _loadProcAddr("glProgramUniform1i64vNV"));
        glProgramUniform2i64vNV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2I64VNVPROC>(
                _loadProcAddr("glProgramUniform2i64vNV"));
        glProgramUniform3i64vNV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3I64VNVPROC>(
                _loadProcAddr("glProgramUniform3i64vNV"));
        glProgramUniform4i64vNV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4I64VNVPROC>(
                _loadProcAddr("glProgramUniform4i64vNV"));
        glProgramUniform1ui64NV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1UI64NVPROC>(
                _loadProcAddr("glProgramUniform1ui64NV"));
        glProgramUniform2ui64NV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2UI64NVPROC>(
                _loadProcAddr("glProgramUniform2ui64NV"));
        glProgramUniform3ui64NV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3UI64NVPROC>(
                _loadProcAddr("glProgramUniform3ui64NV"));
        glProgramUniform4ui64NV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4UI64NVPROC>(
                _loadProcAddr("glProgramUniform4ui64NV"));
        glProgramUniform1ui64vNV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM1UI64VNVPROC>(
                _loadProcAddr("glProgramUniform1ui64vNV"));
        glProgramUniform2ui64vNV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM2UI64VNVPROC>(
                _loadProcAddr("glProgramUniform2ui64vNV"));
        glProgramUniform3ui64vNV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM3UI64VNVPROC>(
                _loadProcAddr("glProgramUniform3ui64vNV"));
        glProgramUniform4ui64vNV =
            reinterpret_cast<PFNGLPROGRAMUNIFORM4UI64VNVPROC>(
                _loadProcAddr("glProgramUniform4ui64vNV"));
#endif /* GL_NV_gpu_shader5 */
#ifdef GL_NV_internalformat_sample_query
        glGetInternalformatSampleivNV =
            reinterpret_cast<PFNGLGETINTERNALFORMATSAMPLEIVNVPROC>(
                _loadProcAddr("glGetInternalformatSampleivNV"));
#endif /* GL_NV_internalformat_sample_query */
#ifdef GL_NV_memory_attachment
        glGetMemoryObjectDetachedResourcesuivNV =
            reinterpret_cast<PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC>(
                _loadProcAddr("glGetMemoryObjectDetachedResourcesuivNV"));
        glResetMemoryObjectParameterNV =
            reinterpret_cast<PFNGLRESETMEMORYOBJECTPARAMETERNVPROC>(
                _loadProcAddr("glResetMemoryObjectParameterNV"));
        glTexAttachMemoryNV = reinterpret_cast<PFNGLTEXATTACHMEMORYNVPROC>(
            _loadProcAddr("glTexAttachMemoryNV"));
        glBufferAttachMemoryNV =
            reinterpret_cast<PFNGLBUFFERATTACHMEMORYNVPROC>(
                _loadProcAddr("glBufferAttachMemoryNV"));
        glTextureAttachMemoryNV =
            reinterpret_cast<PFNGLTEXTUREATTACHMEMORYNVPROC>(
                _loadProcAddr("glTextureAttachMemoryNV"));
        glNamedBufferAttachMemoryNV =
            reinterpret_cast<PFNGLNAMEDBUFFERATTACHMEMORYNVPROC>(
                _loadProcAddr("glNamedBufferAttachMemoryNV"));
#endif /* GL_NV_memory_attachment */
#ifdef GL_NV_memory_object_sparse
        glBufferPageCommitmentMemNV =
            reinterpret_cast<PFNGLBUFFERPAGECOMMITMENTMEMNVPROC>(
                _loadProcAddr("glBufferPageCommitmentMemNV"));
        glTexPageCommitmentMemNV =
            reinterpret_cast<PFNGLTEXPAGECOMMITMENTMEMNVPROC>(
                _loadProcAddr("glTexPageCommitmentMemNV"));
        glNamedBufferPageCommitmentMemNV =
            reinterpret_cast<PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC>(
                _loadProcAddr("glNamedBufferPageCommitmentMemNV"));
        glTexturePageCommitmentMemNV =
            reinterpret_cast<PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC>(
                _loadProcAddr("glTexturePageCommitmentMemNV"));
#endif /* GL_NV_memory_object_sparse */
#ifdef GL_NV_mesh_shader
        glDrawMeshTasksNV = reinterpret_cast<PFNGLDRAWMESHTASKSNVPROC>(
            _loadProcAddr("glDrawMeshTasksNV"));
        glDrawMeshTasksIndirectNV =
            reinterpret_cast<PFNGLDRAWMESHTASKSINDIRECTNVPROC>(
                _loadProcAddr("glDrawMeshTasksIndirectNV"));
        glMultiDrawMeshTasksIndirectNV =
            reinterpret_cast<PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC>(
                _loadProcAddr("glMultiDrawMeshTasksIndirectNV"));
        glMultiDrawMeshTasksIndirectCountNV =
            reinterpret_cast<PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC>(
                _loadProcAddr("glMultiDrawMeshTasksIndirectCountNV"));
#endif /* GL_NV_mesh_shader */
#ifdef GL_NV_path_rendering
        glGenPathsNV = reinterpret_cast<PFNGLGENPATHSNVPROC>(
            _loadProcAddr("glGenPathsNV"));
        glDeletePathsNV = reinterpret_cast<PFNGLDELETEPATHSNVPROC>(
            _loadProcAddr("glDeletePathsNV"));
        glIsPathNV =
            reinterpret_cast<PFNGLISPATHNVPROC>(_loadProcAddr("glIsPathNV"));
        glPathCommandsNV = reinterpret_cast<PFNGLPATHCOMMANDSNVPROC>(
            _loadProcAddr("glPathCommandsNV"));
        glPathCoordsNV = reinterpret_cast<PFNGLPATHCOORDSNVPROC>(
            _loadProcAddr("glPathCoordsNV"));
        glPathSubCommandsNV = reinterpret_cast<PFNGLPATHSUBCOMMANDSNVPROC>(
            _loadProcAddr("glPathSubCommandsNV"));
        glPathSubCoordsNV = reinterpret_cast<PFNGLPATHSUBCOORDSNVPROC>(
            _loadProcAddr("glPathSubCoordsNV"));
        glPathStringNV = reinterpret_cast<PFNGLPATHSTRINGNVPROC>(
            _loadProcAddr("glPathStringNV"));
        glPathGlyphsNV = reinterpret_cast<PFNGLPATHGLYPHSNVPROC>(
            _loadProcAddr("glPathGlyphsNV"));
        glPathGlyphRangeNV = reinterpret_cast<PFNGLPATHGLYPHRANGENVPROC>(
            _loadProcAddr("glPathGlyphRangeNV"));
        glWeightPathsNV = reinterpret_cast<PFNGLWEIGHTPATHSNVPROC>(
            _loadProcAddr("glWeightPathsNV"));
        glCopyPathNV = reinterpret_cast<PFNGLCOPYPATHNVPROC>(
            _loadProcAddr("glCopyPathNV"));
        glInterpolatePathsNV = reinterpret_cast<PFNGLINTERPOLATEPATHSNVPROC>(
            _loadProcAddr("glInterpolatePathsNV"));
        glTransformPathNV = reinterpret_cast<PFNGLTRANSFORMPATHNVPROC>(
            _loadProcAddr("glTransformPathNV"));
        glPathParameterivNV = reinterpret_cast<PFNGLPATHPARAMETERIVNVPROC>(
            _loadProcAddr("glPathParameterivNV"));
        glPathParameteriNV = reinterpret_cast<PFNGLPATHPARAMETERINVPROC>(
            _loadProcAddr("glPathParameteriNV"));
        glPathParameterfvNV = reinterpret_cast<PFNGLPATHPARAMETERFVNVPROC>(
            _loadProcAddr("glPathParameterfvNV"));
        glPathParameterfNV = reinterpret_cast<PFNGLPATHPARAMETERFNVPROC>(
            _loadProcAddr("glPathParameterfNV"));
        glPathDashArrayNV = reinterpret_cast<PFNGLPATHDASHARRAYNVPROC>(
            _loadProcAddr("glPathDashArrayNV"));
        glPathStencilFuncNV = reinterpret_cast<PFNGLPATHSTENCILFUNCNVPROC>(
            _loadProcAddr("glPathStencilFuncNV"));
        glPathStencilDepthOffsetNV =
            reinterpret_cast<PFNGLPATHSTENCILDEPTHOFFSETNVPROC>(
                _loadProcAddr("glPathStencilDepthOffsetNV"));
        glStencilFillPathNV = reinterpret_cast<PFNGLSTENCILFILLPATHNVPROC>(
            _loadProcAddr("glStencilFillPathNV"));
        glStencilStrokePathNV = reinterpret_cast<PFNGLSTENCILSTROKEPATHNVPROC>(
            _loadProcAddr("glStencilStrokePathNV"));
        glStencilFillPathInstancedNV =
            reinterpret_cast<PFNGLSTENCILFILLPATHINSTANCEDNVPROC>(
                _loadProcAddr("glStencilFillPathInstancedNV"));
        glStencilStrokePathInstancedNV =
            reinterpret_cast<PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC>(
                _loadProcAddr("glStencilStrokePathInstancedNV"));
        glPathCoverDepthFuncNV =
            reinterpret_cast<PFNGLPATHCOVERDEPTHFUNCNVPROC>(
                _loadProcAddr("glPathCoverDepthFuncNV"));
        glCoverFillPathNV = reinterpret_cast<PFNGLCOVERFILLPATHNVPROC>(
            _loadProcAddr("glCoverFillPathNV"));
        glCoverStrokePathNV = reinterpret_cast<PFNGLCOVERSTROKEPATHNVPROC>(
            _loadProcAddr("glCoverStrokePathNV"));
        glCoverFillPathInstancedNV =
            reinterpret_cast<PFNGLCOVERFILLPATHINSTANCEDNVPROC>(
                _loadProcAddr("glCoverFillPathInstancedNV"));
        glCoverStrokePathInstancedNV =
            reinterpret_cast<PFNGLCOVERSTROKEPATHINSTANCEDNVPROC>(
                _loadProcAddr("glCoverStrokePathInstancedNV"));
        glGetPathParameterivNV =
            reinterpret_cast<PFNGLGETPATHPARAMETERIVNVPROC>(
                _loadProcAddr("glGetPathParameterivNV"));
        glGetPathParameterfvNV =
            reinterpret_cast<PFNGLGETPATHPARAMETERFVNVPROC>(
                _loadProcAddr("glGetPathParameterfvNV"));
        glGetPathCommandsNV = reinterpret_cast<PFNGLGETPATHCOMMANDSNVPROC>(
            _loadProcAddr("glGetPathCommandsNV"));
        glGetPathCoordsNV = reinterpret_cast<PFNGLGETPATHCOORDSNVPROC>(
            _loadProcAddr("glGetPathCoordsNV"));
        glGetPathDashArrayNV = reinterpret_cast<PFNGLGETPATHDASHARRAYNVPROC>(
            _loadProcAddr("glGetPathDashArrayNV"));
        glGetPathMetricsNV = reinterpret_cast<PFNGLGETPATHMETRICSNVPROC>(
            _loadProcAddr("glGetPathMetricsNV"));
        glGetPathMetricRangeNV =
            reinterpret_cast<PFNGLGETPATHMETRICRANGENVPROC>(
                _loadProcAddr("glGetPathMetricRangeNV"));
        glGetPathSpacingNV = reinterpret_cast<PFNGLGETPATHSPACINGNVPROC>(
            _loadProcAddr("glGetPathSpacingNV"));
        glIsPointInFillPathNV = reinterpret_cast<PFNGLISPOINTINFILLPATHNVPROC>(
            _loadProcAddr("glIsPointInFillPathNV"));
        glIsPointInStrokePathNV =
            reinterpret_cast<PFNGLISPOINTINSTROKEPATHNVPROC>(
                _loadProcAddr("glIsPointInStrokePathNV"));
        glGetPathLengthNV = reinterpret_cast<PFNGLGETPATHLENGTHNVPROC>(
            _loadProcAddr("glGetPathLengthNV"));
        glPointAlongPathNV = reinterpret_cast<PFNGLPOINTALONGPATHNVPROC>(
            _loadProcAddr("glPointAlongPathNV"));
        glMatrixLoad3x2fNV = reinterpret_cast<PFNGLMATRIXLOAD3X2FNVPROC>(
            _loadProcAddr("glMatrixLoad3x2fNV"));
        glMatrixLoad3x3fNV = reinterpret_cast<PFNGLMATRIXLOAD3X3FNVPROC>(
            _loadProcAddr("glMatrixLoad3x3fNV"));
        glMatrixLoadTranspose3x3fNV =
            reinterpret_cast<PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC>(
                _loadProcAddr("glMatrixLoadTranspose3x3fNV"));
        glMatrixMult3x2fNV = reinterpret_cast<PFNGLMATRIXMULT3X2FNVPROC>(
            _loadProcAddr("glMatrixMult3x2fNV"));
        glMatrixMult3x3fNV = reinterpret_cast<PFNGLMATRIXMULT3X3FNVPROC>(
            _loadProcAddr("glMatrixMult3x3fNV"));
        glMatrixMultTranspose3x3fNV =
            reinterpret_cast<PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC>(
                _loadProcAddr("glMatrixMultTranspose3x3fNV"));
        glStencilThenCoverFillPathNV =
            reinterpret_cast<PFNGLSTENCILTHENCOVERFILLPATHNVPROC>(
                _loadProcAddr("glStencilThenCoverFillPathNV"));
        glStencilThenCoverStrokePathNV =
            reinterpret_cast<PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC>(
                _loadProcAddr("glStencilThenCoverStrokePathNV"));
        glStencilThenCoverFillPathInstancedNV =
            reinterpret_cast<PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC>(
                _loadProcAddr("glStencilThenCoverFillPathInstancedNV"));
        glStencilThenCoverStrokePathInstancedNV =
            reinterpret_cast<PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC>(
                _loadProcAddr("glStencilThenCoverStrokePathInstancedNV"));
        glPathGlyphIndexRangeNV =
            reinterpret_cast<PFNGLPATHGLYPHINDEXRANGENVPROC>(
                _loadProcAddr("glPathGlyphIndexRangeNV"));
        glPathGlyphIndexArrayNV =
            reinterpret_cast<PFNGLPATHGLYPHINDEXARRAYNVPROC>(
                _loadProcAddr("glPathGlyphIndexArrayNV"));
        glPathMemoryGlyphIndexArrayNV =
            reinterpret_cast<PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC>(
                _loadProcAddr("glPathMemoryGlyphIndexArrayNV"));
        glProgramPathFragmentInputGenNV =
            reinterpret_cast<PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC>(
                _loadProcAddr("glProgramPathFragmentInputGenNV"));
        glGetProgramResourcefvNV =
            reinterpret_cast<PFNGLGETPROGRAMRESOURCEFVNVPROC>(
                _loadProcAddr("glGetProgramResourcefvNV"));
#endif /* GL_NV_path_rendering */
#ifdef GL_NV_path_rendering_shared_edge
#endif /* GL_NV_path_rendering_shared_edge */
#ifdef GL_NV_representative_fragment_test
#endif /* GL_NV_representative_fragment_test */
#ifdef GL_NV_sample_locations
        glFramebufferSampleLocationsfvNV =
            reinterpret_cast<PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC>(
                _loadProcAddr("glFramebufferSampleLocationsfvNV"));
        glNamedFramebufferSampleLocationsfvNV =
            reinterpret_cast<PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC>(
                _loadProcAddr("glNamedFramebufferSampleLocationsfvNV"));
        glResolveDepthValuesNV =
            reinterpret_cast<PFNGLRESOLVEDEPTHVALUESNVPROC>(
                _loadProcAddr("glResolveDepthValuesNV"));
#endif /* GL_NV_sample_locations */
#ifdef GL_NV_sample_mask_override_coverage
#endif /* GL_NV_sample_mask_override_coverage */
#ifdef GL_NV_scissor_exclusive
        glScissorExclusiveNV = reinterpret_cast<PFNGLSCISSOREXCLUSIVENVPROC>(
            _loadProcAddr("glScissorExclusiveNV"));
        glScissorExclusiveArrayvNV =
            reinterpret_cast<PFNGLSCISSOREXCLUSIVEARRAYVNVPROC>(
                _loadProcAddr("glScissorExclusiveArrayvNV"));
#endif /* GL_NV_scissor_exclusive */
#ifdef GL_NV_shader_atomic_counters
#endif /* GL_NV_shader_atomic_counters */
#ifdef GL_NV_shader_atomic_float
#endif /* GL_NV_shader_atomic_float */
#ifdef GL_NV_shader_atomic_float64
#endif /* GL_NV_shader_atomic_float64 */
#ifdef GL_NV_shader_atomic_fp16_vector
#endif /* GL_NV_shader_atomic_fp16_vector */
#ifdef GL_NV_shader_atomic_int64
#endif /* GL_NV_shader_atomic_int64 */
#ifdef GL_NV_shader_buffer_load
        glMakeBufferResidentNV =
            reinterpret_cast<PFNGLMAKEBUFFERRESIDENTNVPROC>(
                _loadProcAddr("glMakeBufferResidentNV"));
        glMakeBufferNonResidentNV =
            reinterpret_cast<PFNGLMAKEBUFFERNONRESIDENTNVPROC>(
                _loadProcAddr("glMakeBufferNonResidentNV"));
        glIsBufferResidentNV = reinterpret_cast<PFNGLISBUFFERRESIDENTNVPROC>(
            _loadProcAddr("glIsBufferResidentNV"));
        glMakeNamedBufferResidentNV =
            reinterpret_cast<PFNGLMAKENAMEDBUFFERRESIDENTNVPROC>(
                _loadProcAddr("glMakeNamedBufferResidentNV"));
        glMakeNamedBufferNonResidentNV =
            reinterpret_cast<PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC>(
                _loadProcAddr("glMakeNamedBufferNonResidentNV"));
        glIsNamedBufferResidentNV =
            reinterpret_cast<PFNGLISNAMEDBUFFERRESIDENTNVPROC>(
                _loadProcAddr("glIsNamedBufferResidentNV"));
        glGetBufferParameterui64vNV =
            reinterpret_cast<PFNGLGETBUFFERPARAMETERUI64VNVPROC>(
                _loadProcAddr("glGetBufferParameterui64vNV"));
        glGetNamedBufferParameterui64vNV =
            reinterpret_cast<PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC>(
                _loadProcAddr("glGetNamedBufferParameterui64vNV"));
        glGetIntegerui64vNV = reinterpret_cast<PFNGLGETINTEGERUI64VNVPROC>(
            _loadProcAddr("glGetIntegerui64vNV"));
        glUniformui64NV = reinterpret_cast<PFNGLUNIFORMUI64NVPROC>(
            _loadProcAddr("glUniformui64NV"));
        glUniformui64vNV = reinterpret_cast<PFNGLUNIFORMUI64VNVPROC>(
            _loadProcAddr("glUniformui64vNV"));
        glGetUniformui64vNV = reinterpret_cast<PFNGLGETUNIFORMUI64VNVPROC>(
            _loadProcAddr("glGetUniformui64vNV"));
        glProgramUniformui64NV =
            reinterpret_cast<PFNGLPROGRAMUNIFORMUI64NVPROC>(
                _loadProcAddr("glProgramUniformui64NV"));
        glProgramUniformui64vNV =
            reinterpret_cast<PFNGLPROGRAMUNIFORMUI64VNVPROC>(
                _loadProcAddr("glProgramUniformui64vNV"));
#endif /* GL_NV_shader_buffer_load */
#ifdef GL_NV_shader_buffer_store
#endif /* GL_NV_shader_buffer_store */
#ifdef GL_NV_shader_subgroup_partitioned
#endif /* GL_NV_shader_subgroup_partitioned */
#ifdef GL_NV_shader_texture_footprint
#endif /* GL_NV_shader_texture_footprint */
#ifdef GL_NV_shader_thread_group
#endif /* GL_NV_shader_thread_group */
#ifdef GL_NV_shader_thread_shuffle
#endif /* GL_NV_shader_thread_shuffle */
#ifdef GL_NV_shading_rate_image
        glBindShadingRateImageNV =
            reinterpret_cast<PFNGLBINDSHADINGRATEIMAGENVPROC>(
                _loadProcAddr("glBindShadingRateImageNV"));
        glGetShadingRateImagePaletteNV =
            reinterpret_cast<PFNGLGETSHADINGRATEIMAGEPALETTENVPROC>(
                _loadProcAddr("glGetShadingRateImagePaletteNV"));
        glGetShadingRateSampleLocationivNV =
            reinterpret_cast<PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC>(
                _loadProcAddr("glGetShadingRateSampleLocationivNV"));
        glShadingRateImageBarrierNV =
            reinterpret_cast<PFNGLSHADINGRATEIMAGEBARRIERNVPROC>(
                _loadProcAddr("glShadingRateImageBarrierNV"));
        glShadingRateImagePaletteNV =
            reinterpret_cast<PFNGLSHADINGRATEIMAGEPALETTENVPROC>(
                _loadProcAddr("glShadingRateImagePaletteNV"));
        glShadingRateSampleOrderNV =
            reinterpret_cast<PFNGLSHADINGRATESAMPLEORDERNVPROC>(
                _loadProcAddr("glShadingRateSampleOrderNV"));
        glShadingRateSampleOrderCustomNV =
            reinterpret_cast<PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC>(
                _loadProcAddr("glShadingRateSampleOrderCustomNV"));
#endif /* GL_NV_shading_rate_image */
#ifdef GL_NV_stereo_view_rendering
#endif /* GL_NV_stereo_view_rendering */
#ifdef GL_NV_texture_barrier
        glTextureBarrierNV = reinterpret_cast<PFNGLTEXTUREBARRIERNVPROC>(
            _loadProcAddr("glTextureBarrierNV"));
#endif /* GL_NV_texture_barrier */
#ifdef GL_NV_texture_rectangle_compressed
#endif /* GL_NV_texture_rectangle_compressed */
#ifdef GL_NV_uniform_buffer_unified_memory
#endif /* GL_NV_uniform_buffer_unified_memory */
#ifdef GL_NV_vertex_attrib_integer_64bit
        glVertexAttribL1i64NV = reinterpret_cast<PFNGLVERTEXATTRIBL1I64NVPROC>(
            _loadProcAddr("glVertexAttribL1i64NV"));
        glVertexAttribL2i64NV = reinterpret_cast<PFNGLVERTEXATTRIBL2I64NVPROC>(
            _loadProcAddr("glVertexAttribL2i64NV"));
        glVertexAttribL3i64NV = reinterpret_cast<PFNGLVERTEXATTRIBL3I64NVPROC>(
            _loadProcAddr("glVertexAttribL3i64NV"));
        glVertexAttribL4i64NV = reinterpret_cast<PFNGLVERTEXATTRIBL4I64NVPROC>(
            _loadProcAddr("glVertexAttribL4i64NV"));
        glVertexAttribL1i64vNV =
            reinterpret_cast<PFNGLVERTEXATTRIBL1I64VNVPROC>(
                _loadProcAddr("glVertexAttribL1i64vNV"));
        glVertexAttribL2i64vNV =
            reinterpret_cast<PFNGLVERTEXATTRIBL2I64VNVPROC>(
                _loadProcAddr("glVertexAttribL2i64vNV"));
        glVertexAttribL3i64vNV =
            reinterpret_cast<PFNGLVERTEXATTRIBL3I64VNVPROC>(
                _loadProcAddr("glVertexAttribL3i64vNV"));
        glVertexAttribL4i64vNV =
            reinterpret_cast<PFNGLVERTEXATTRIBL4I64VNVPROC>(
                _loadProcAddr("glVertexAttribL4i64vNV"));
        glVertexAttribL1ui64NV =
            reinterpret_cast<PFNGLVERTEXATTRIBL1UI64NVPROC>(
                _loadProcAddr("glVertexAttribL1ui64NV"));
        glVertexAttribL2ui64NV =
            reinterpret_cast<PFNGLVERTEXATTRIBL2UI64NVPROC>(
                _loadProcAddr("glVertexAttribL2ui64NV"));
        glVertexAttribL3ui64NV =
            reinterpret_cast<PFNGLVERTEXATTRIBL3UI64NVPROC>(
                _loadProcAddr("glVertexAttribL3ui64NV"));
        glVertexAttribL4ui64NV =
            reinterpret_cast<PFNGLVERTEXATTRIBL4UI64NVPROC>(
                _loadProcAddr("glVertexAttribL4ui64NV"));
        glVertexAttribL1ui64vNV =
            reinterpret_cast<PFNGLVERTEXATTRIBL1UI64VNVPROC>(
                _loadProcAddr("glVertexAttribL1ui64vNV"));
        glVertexAttribL2ui64vNV =
            reinterpret_cast<PFNGLVERTEXATTRIBL2UI64VNVPROC>(
                _loadProcAddr("glVertexAttribL2ui64vNV"));
        glVertexAttribL3ui64vNV =
            reinterpret_cast<PFNGLVERTEXATTRIBL3UI64VNVPROC>(
                _loadProcAddr("glVertexAttribL3ui64vNV"));
        glVertexAttribL4ui64vNV =
            reinterpret_cast<PFNGLVERTEXATTRIBL4UI64VNVPROC>(
                _loadProcAddr("glVertexAttribL4ui64vNV"));
        glGetVertexAttribLi64vNV =
            reinterpret_cast<PFNGLGETVERTEXATTRIBLI64VNVPROC>(
                _loadProcAddr("glGetVertexAttribLi64vNV"));
        glGetVertexAttribLui64vNV =
            reinterpret_cast<PFNGLGETVERTEXATTRIBLUI64VNVPROC>(
                _loadProcAddr("glGetVertexAttribLui64vNV"));
        glVertexAttribLFormatNV =
            reinterpret_cast<PFNGLVERTEXATTRIBLFORMATNVPROC>(
                _loadProcAddr("glVertexAttribLFormatNV"));
#endif /* GL_NV_vertex_attrib_integer_64bit */
#ifdef GL_NV_vertex_buffer_unified_memory
        glBufferAddressRangeNV =
            reinterpret_cast<PFNGLBUFFERADDRESSRANGENVPROC>(
                _loadProcAddr("glBufferAddressRangeNV"));
        glVertexFormatNV = reinterpret_cast<PFNGLVERTEXFORMATNVPROC>(
            _loadProcAddr("glVertexFormatNV"));
        glNormalFormatNV = reinterpret_cast<PFNGLNORMALFORMATNVPROC>(
            _loadProcAddr("glNormalFormatNV"));
        glColorFormatNV = reinterpret_cast<PFNGLCOLORFORMATNVPROC>(
            _loadProcAddr("glColorFormatNV"));
        glIndexFormatNV = reinterpret_cast<PFNGLINDEXFORMATNVPROC>(
            _loadProcAddr("glIndexFormatNV"));
        glTexCoordFormatNV = reinterpret_cast<PFNGLTEXCOORDFORMATNVPROC>(
            _loadProcAddr("glTexCoordFormatNV"));
        glEdgeFlagFormatNV = reinterpret_cast<PFNGLEDGEFLAGFORMATNVPROC>(
            _loadProcAddr("glEdgeFlagFormatNV"));
        glSecondaryColorFormatNV =
            reinterpret_cast<PFNGLSECONDARYCOLORFORMATNVPROC>(
                _loadProcAddr("glSecondaryColorFormatNV"));
        glFogCoordFormatNV = reinterpret_cast<PFNGLFOGCOORDFORMATNVPROC>(
            _loadProcAddr("glFogCoordFormatNV"));
        glVertexAttribFormatNV =
            reinterpret_cast<PFNGLVERTEXATTRIBFORMATNVPROC>(
                _loadProcAddr("glVertexAttribFormatNV"));
        glVertexAttribIFormatNV =
            reinterpret_cast<PFNGLVERTEXATTRIBIFORMATNVPROC>(
                _loadProcAddr("glVertexAttribIFormatNV"));
        glGetIntegerui64i_vNV = reinterpret_cast<PFNGLGETINTEGERUI64I_VNVPROC>(
            _loadProcAddr("glGetIntegerui64i_vNV"));
#endif /* GL_NV_vertex_buffer_unified_memory */
#ifdef GL_NV_viewport_array2
#endif /* GL_NV_viewport_array2 */
#ifdef GL_NV_viewport_swizzle
        glViewportSwizzleNV = reinterpret_cast<PFNGLVIEWPORTSWIZZLENVPROC>(
            _loadProcAddr("glViewportSwizzleNV"));
#endif /* GL_NV_viewport_swizzle */
#ifdef GL_OVR_multiview
        glFramebufferTextureMultiviewOVR =
            reinterpret_cast<PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC>(
                _loadProcAddr("glFramebufferTextureMultiviewOVR"));
#endif /* GL_OVR_multiview */
#ifdef GL_OVR_multiview2
#endif /* GL_OVR_multiview2 */
    }
};

enum class Error {
    eNoError = GL_NO_ERROR,
    eInvalidEnum = GL_INVALID_ENUM,
    eInvalidValue = GL_INVALID_VALUE,
    eInvalidOperation = GL_INVALID_OPERATION,
    eOutOfMemory = GL_OUT_OF_MEMORY,
    eStackUnderflow = GL_STACK_UNDERFLOW,
    eStackOverflow = GL_STACK_OVERFLOW
};

std::string to_string(Error value) {
    switch (value) {
        case Error::eInvalidEnum:
            return "InvalidEnum";
        case Error::eInvalidOperation:
            return "InvalidOperation";
        case Error::eInvalidValue:
            return "InvalidValue";
        case Error::eNoError:
            return "NoError";
        case Error::eOutOfMemory:
            return "OutOfMemory";
        case Error::eStackOverflow:
            return "StackOverflow";
        case Error::eStackUnderflow:
            return "StackUnderflow";
        default:
            return "InvalidEnum";
    }
}

enum class StateVariables {
    eActiveTexture = GL_ACTIVE_TEXTURE,
    eAliasedLineWidthRange = GL_ALIASED_LINE_WIDTH_RANGE,
    eArrayBufferBinding = GL_ARRAY_BUFFER_BINDING,
    eBlend = GL_BLEND,
    eBlendColor = GL_BLEND_COLOR,
    eBlendDstAlpha = GL_BLEND_DST_ALPHA,
    eBlendDstRgb = GL_BLEND_DST_RGB,
    eBlendEquationRgb = GL_BLEND_EQUATION_RGB,
    eBlendEquationAlpha = GL_BLEND_EQUATION_ALPHA,
    eBlendSrcAlpha = GL_BLEND_SRC_ALPHA,
    eBlendSrcRgb = GL_BLEND_SRC_RGB,
    eColorClearValue = GL_COLOR_CLEAR_VALUE,
    eColorLogicOp = GL_COLOR_LOGIC_OP,
    eColorWritemask = GL_COLOR_WRITEMASK,
    eCompressedTextureFormats = GL_COMPRESSED_TEXTURE_FORMATS,
    eMaxComputeShaderStorageBlocks = GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS,
    eMaxCombinedShaderStorageBlocks = GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS,
    eMaxComputeUniformBlocks = GL_MAX_COMPUTE_UNIFORM_BLOCKS,
    eMaxComputeTextureImageUnits = GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS,
    eMaxComputeUniformComponents = GL_MAX_COMPUTE_UNIFORM_COMPONENTS,
    eMaxComputeAtomicCounters = GL_MAX_COMPUTE_ATOMIC_COUNTERS,
    eMaxComputeAtomicCounterBuffers = GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS,
    eMaxCombinedComputeUniformComponents =
        GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS,
    eMaxComputeWorkGroupInvocations = GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS,
    eMaxComputeWorkGroupCount = GL_MAX_COMPUTE_WORK_GROUP_COUNT,
    eMaxComputeWorkGroupSize = GL_MAX_COMPUTE_WORK_GROUP_SIZE,
    eDispatchIndirectBufferBinding = GL_DISPATCH_INDIRECT_BUFFER_BINDING,
    eMaxDebugGroupStackDepth = GL_MAX_DEBUG_GROUP_STACK_DEPTH,
    eDebugGroupStackDepth = GL_DEBUG_GROUP_STACK_DEPTH,
    eContextFlags = GL_CONTEXT_FLAGS,
    eCullFace = GL_CULL_FACE,
    eCullFaceMode = GL_CULL_FACE_MODE,
    eCurrentProgram = GL_CURRENT_PROGRAM,
    eDepthClearValue = GL_DEPTH_CLEAR_VALUE,
    eDepthFunc = GL_DEPTH_FUNC,
    eDepthRange = GL_DEPTH_RANGE,
    eDepthTest = GL_DEPTH_TEST,
    eDepthWritemask = GL_DEPTH_WRITEMASK,
    eDither = GL_DITHER,
    eDoublebuffer = GL_DOUBLEBUFFER,
    eDrawBuffer = GL_DRAW_BUFFER,
    eDrawFramebufferBinding = GL_DRAW_FRAMEBUFFER_BINDING,
    eReadFramebufferBinding = GL_READ_FRAMEBUFFER_BINDING,
    eElementArrayBufferBinding = GL_ELEMENT_ARRAY_BUFFER_BINDING,
    eFragmentShaderDerivativeHint = GL_FRAGMENT_SHADER_DERIVATIVE_HINT,
    eImplementationColorReadFormat = GL_IMPLEMENTATION_COLOR_READ_FORMAT,
    eImplementationColorReadType = GL_IMPLEMENTATION_COLOR_READ_TYPE,
    eLineSmooth = GL_LINE_SMOOTH,
    eLineSmoothHint = GL_LINE_SMOOTH_HINT,
    eLineWidth = GL_LINE_WIDTH,
    eLayerProvokingVertex = GL_LAYER_PROVOKING_VERTEX,
    eLogicOpMode = GL_LOGIC_OP_MODE,
    eMajorVersion = GL_MAJOR_VERSION,
    eMax3dTextureSize = GL_MAX_3D_TEXTURE_SIZE,
    eMaxArrayTextureLayers = GL_MAX_ARRAY_TEXTURE_LAYERS,
    eMaxClipDistances = GL_MAX_CLIP_DISTANCES,
    eMaxColorTextureSamples = GL_MAX_COLOR_TEXTURE_SAMPLES,
    eMaxCombinedAtomicCounters = GL_MAX_COMBINED_ATOMIC_COUNTERS,
    eMaxCombinedFragmentUniformComponents =
        GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,
    eMaxCombinedGeometryUniformComponents =
        GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS,
    eMaxCombinedTextureImageUnits = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
    eMaxCombinedUniformBlocks = GL_MAX_COMBINED_UNIFORM_BLOCKS,
    eMaxCombinedVertexUniformComponents =
        GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS,
    eMaxCubeMapTextureSize = GL_MAX_CUBE_MAP_TEXTURE_SIZE,
    eMaxDepthTextureSamples = GL_MAX_DEPTH_TEXTURE_SAMPLES,
    eMaxDrawBuffers = GL_MAX_DRAW_BUFFERS,
    eMaxDualSourceDrawBuffers = GL_MAX_DUAL_SOURCE_DRAW_BUFFERS,
    eMaxElementsIndices = GL_MAX_ELEMENTS_INDICES,
    eMaxElementsVertices = GL_MAX_ELEMENTS_VERTICES,
    eMaxFragmentAtomicCounters = GL_MAX_FRAGMENT_ATOMIC_COUNTERS,
    eMaxFragmentShaderStorageBlocks = GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS,
    eMaxFragmentInputComponents = GL_MAX_FRAGMENT_INPUT_COMPONENTS,
    eMaxFragmentUniformComponents = GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
    eMaxFragmentUniformVectors = GL_MAX_FRAGMENT_UNIFORM_VECTORS,
    eMaxFragmentUniformBlocks = GL_MAX_FRAGMENT_UNIFORM_BLOCKS,
    eMaxFramebufferWidth = GL_MAX_FRAMEBUFFER_WIDTH,
    eMaxFramebufferHeight = GL_MAX_FRAMEBUFFER_HEIGHT,
    eMaxFramebufferLayers = GL_MAX_FRAMEBUFFER_LAYERS,
    eMaxFramebufferSamples = GL_MAX_FRAMEBUFFER_SAMPLES,
    eMaxGeometryAtomicCounters = GL_MAX_GEOMETRY_ATOMIC_COUNTERS,
    eMaxGeometryShaderStorageBlocks = GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS,
    eMaxGeometryInputComponents = GL_MAX_GEOMETRY_INPUT_COMPONENTS,
    eMaxGeometryOutputComponents = GL_MAX_GEOMETRY_OUTPUT_COMPONENTS,
    eMaxGeometryTextureImageUnits = GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS,
    eMaxGeometryUniformBlocks = GL_MAX_GEOMETRY_UNIFORM_BLOCKS,
    eMaxGeometryUniformComponents = GL_MAX_GEOMETRY_UNIFORM_COMPONENTS,
    eMaxIntegerSamples = GL_MAX_INTEGER_SAMPLES,
    eMinMapBufferAlignment = GL_MIN_MAP_BUFFER_ALIGNMENT,
    eMaxLabelLength = GL_MAX_LABEL_LENGTH,
    eMaxProgramTexelOffset = GL_MAX_PROGRAM_TEXEL_OFFSET,
    eMinProgramTexelOffset = GL_MIN_PROGRAM_TEXEL_OFFSET,
    eMaxRectangleTextureSize = GL_MAX_RECTANGLE_TEXTURE_SIZE,
    eMaxRenderbufferSize = GL_MAX_RENDERBUFFER_SIZE,
    eMaxSampleMaskWords = GL_MAX_SAMPLE_MASK_WORDS,
    eMaxServerWaitTimeout = GL_MAX_SERVER_WAIT_TIMEOUT,
    eMaxShaderStorageBufferBindings = GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS,
    eMaxTessControlAtomicCounters = GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS,
    eMaxTessEvaluationAtomicCounters = GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS,
    eMaxTessControlShaderStorageBlocks =
        GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS,
    eMaxTessEvaluationShaderStorageBlocks =
        GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS,
    eMaxTextureBufferSize = GL_MAX_TEXTURE_BUFFER_SIZE,
    eMaxTextureImageUnits = GL_MAX_TEXTURE_IMAGE_UNITS,
    eMaxTextureLodBias = GL_MAX_TEXTURE_LOD_BIAS,
    eMaxTextureSize = GL_MAX_TEXTURE_SIZE,
    eMaxUniformBufferBindings = GL_MAX_UNIFORM_BUFFER_BINDINGS,
    eMaxUniformBlockSize = GL_MAX_UNIFORM_BLOCK_SIZE,
    eMaxUniformLocations = GL_MAX_UNIFORM_LOCATIONS,
    eMaxVaryingComponents = GL_MAX_VARYING_COMPONENTS,
    eMaxVaryingVectors = GL_MAX_VARYING_VECTORS,
    eMaxVaryingFloats = GL_MAX_VARYING_FLOATS,
    eMaxVertexAtomicCounters = GL_MAX_VERTEX_ATOMIC_COUNTERS,
    eMaxVertexAttribs = GL_MAX_VERTEX_ATTRIBS,
    eMaxVertexShaderStorageBlocks = GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS,
    eMaxVertexTextureImageUnits = GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
    eMaxVertexUniformComponents = GL_MAX_VERTEX_UNIFORM_COMPONENTS,
    eMaxVertexUniformVectors = GL_MAX_VERTEX_UNIFORM_VECTORS,
    eMaxVertexOutputComponents = GL_MAX_VERTEX_OUTPUT_COMPONENTS,
    eMaxVertexUniformBlocks = GL_MAX_VERTEX_UNIFORM_BLOCKS,
    eMaxViewportDims = GL_MAX_VIEWPORT_DIMS,
    eMaxViewports = GL_MAX_VIEWPORTS,
    eMinorVersion = GL_MINOR_VERSION,
    eNumCompressedTextureFormats = GL_NUM_COMPRESSED_TEXTURE_FORMATS,
    eNumExtensions = GL_NUM_EXTENSIONS,
    eNumProgramBinaryFormats = GL_NUM_PROGRAM_BINARY_FORMATS,
    eNumShaderBinaryFormats = GL_NUM_SHADER_BINARY_FORMATS,
    ePackAlignment = GL_PACK_ALIGNMENT,
    ePackImageHeight = GL_PACK_IMAGE_HEIGHT,
    ePackLsbFirst = GL_PACK_LSB_FIRST,
    ePackRowLength = GL_PACK_ROW_LENGTH,
    ePackSkipImages = GL_PACK_SKIP_IMAGES,
    ePackSkipPixels = GL_PACK_SKIP_PIXELS,
    ePackSkipRows = GL_PACK_SKIP_ROWS,
    ePackSwapBytes = GL_PACK_SWAP_BYTES,
    ePixelPackBufferBinding = GL_PIXEL_PACK_BUFFER_BINDING,
    ePixelUnpackBufferBinding = GL_PIXEL_UNPACK_BUFFER_BINDING,
    ePointFadeThresholdSize = GL_POINT_FADE_THRESHOLD_SIZE,
    ePrimitiveRestartIndex = GL_PRIMITIVE_RESTART_INDEX,
    eProgramBinaryFormats = GL_PROGRAM_BINARY_FORMATS,
    eProgramPipelineBinding = GL_PROGRAM_PIPELINE_BINDING,
    eProgramPointSize = GL_PROGRAM_POINT_SIZE,
    eProvokingVertex = GL_PROVOKING_VERTEX,
    ePointSize = GL_POINT_SIZE,
    ePointSizeGranularity = GL_POINT_SIZE_GRANULARITY,
    ePointSizeRange = GL_POINT_SIZE_RANGE,
    ePolygonOffsetFactor = GL_POLYGON_OFFSET_FACTOR,
    ePolygonOffsetUnits = GL_POLYGON_OFFSET_UNITS,
    ePolygonOffsetFill = GL_POLYGON_OFFSET_FILL,
    ePolygonOffsetLine = GL_POLYGON_OFFSET_LINE,
    ePolygonOffsetPoint = GL_POLYGON_OFFSET_POINT,
    ePolygonSmooth = GL_POLYGON_SMOOTH,
    ePolygonSmoothHint = GL_POLYGON_SMOOTH_HINT,
    eReadBuffer = GL_READ_BUFFER,
    eRenderbufferBinding = GL_RENDERBUFFER_BINDING,
    eSampleBuffers = GL_SAMPLE_BUFFERS,
    eSampleCoverageValue = GL_SAMPLE_COVERAGE_VALUE,
    eSampleCoverageInvert = GL_SAMPLE_COVERAGE_INVERT,
    eSamplerBinding = GL_SAMPLER_BINDING,
    eSamples = GL_SAMPLES,
    eScissorBox = GL_SCISSOR_BOX,
    eScissorTest = GL_SCISSOR_TEST,
    eShaderCompiler = GL_SHADER_COMPILER,
    eShaderStorageBufferBinding = GL_SHADER_STORAGE_BUFFER_BINDING,
    eShaderStorageBufferOffsetAlignment =
        GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT,
    eShaderStorageBufferStart = GL_SHADER_STORAGE_BUFFER_START,
    eShaderStorageBufferSize = GL_SHADER_STORAGE_BUFFER_SIZE,
    eSmoothLineWidthRange = GL_SMOOTH_LINE_WIDTH_RANGE,
    eSmoothLineWidthGranularity = GL_SMOOTH_LINE_WIDTH_GRANULARITY,
    eStencilBackFail = GL_STENCIL_BACK_FAIL,
    eStencilBackFunc = GL_STENCIL_BACK_FUNC,
    eStencilBackPassDepthFail = GL_STENCIL_BACK_PASS_DEPTH_FAIL,
    eStencilBackPassDepthPass = GL_STENCIL_BACK_PASS_DEPTH_PASS,
    eStencilBackRef = GL_STENCIL_BACK_REF,
    eStencilBackValueMask = GL_STENCIL_BACK_VALUE_MASK,
    eStencilBackWritemask = GL_STENCIL_BACK_WRITEMASK,
    eStencilClearValue = GL_STENCIL_CLEAR_VALUE,
    eStencilFail = GL_STENCIL_FAIL,
    eStencilFunc = GL_STENCIL_FUNC,
    eStencilPassDepthFail = GL_STENCIL_PASS_DEPTH_FAIL,
    eStencilPassDepthPass = GL_STENCIL_PASS_DEPTH_PASS,
    eStencilRef = GL_STENCIL_REF,
    eStencilTest = GL_STENCIL_TEST,
    eStencilValueMask = GL_STENCIL_VALUE_MASK,
    eStencilWritemask = GL_STENCIL_WRITEMASK,
    eStereo = GL_STEREO,
    eSubpixelBits = GL_SUBPIXEL_BITS,
    eTextureBinding1d = GL_TEXTURE_BINDING_1D,
    eTextureBinding1dArray = GL_TEXTURE_BINDING_1D_ARRAY,
    eTextureBinding2d = GL_TEXTURE_BINDING_2D,
    eTextureBinding2dArray = GL_TEXTURE_BINDING_2D_ARRAY,
    eTextureBinding2dMultisample = GL_TEXTURE_BINDING_2D_MULTISAMPLE,
    eTextureBinding2dMultisampleArray = GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY,
    eTextureBinding3d = GL_TEXTURE_BINDING_3D,
    eTextureBindingBuffer = GL_TEXTURE_BINDING_BUFFER,
    eTextureBindingCubeMap = GL_TEXTURE_BINDING_CUBE_MAP,
    eTextureBindingRectangle = GL_TEXTURE_BINDING_RECTANGLE,
    eTextureCompressionHint = GL_TEXTURE_COMPRESSION_HINT,
    eTextureBufferOffsetAlignment = GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT,
    eTimestamp = GL_TIMESTAMP,
    eTransformFeedbackBufferBinding = GL_TRANSFORM_FEEDBACK_BUFFER_BINDING,
    eTransformFeedbackBufferStart = GL_TRANSFORM_FEEDBACK_BUFFER_START,
    eTransformFeedbackBufferSize = GL_TRANSFORM_FEEDBACK_BUFFER_SIZE,
    eUniformBufferBinding = GL_UNIFORM_BUFFER_BINDING,
    eUniformBufferOffsetAlignment = GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
    eUniformBufferSize = GL_UNIFORM_BUFFER_SIZE,
    eUniformBufferStart = GL_UNIFORM_BUFFER_START,
    eUnpackAlignment = GL_UNPACK_ALIGNMENT,
    eUnpackImageHeight = GL_UNPACK_IMAGE_HEIGHT,
    eUnpackLsbFirst = GL_UNPACK_LSB_FIRST,
    eUnpackRowLength = GL_UNPACK_ROW_LENGTH,
    eUnpackSkipImages = GL_UNPACK_SKIP_IMAGES,
    eUnpackSkipPixels = GL_UNPACK_SKIP_PIXELS,
    eUnpackSkipRows = GL_UNPACK_SKIP_ROWS,
    eUnpackSwapBytes = GL_UNPACK_SWAP_BYTES,
    eVertexArrayBinding = GL_VERTEX_ARRAY_BINDING,
    eVertexBindingDivisor = GL_VERTEX_BINDING_DIVISOR,
    eVertexBindingOffset = GL_VERTEX_BINDING_OFFSET,
    eVertexBindingStride = GL_VERTEX_BINDING_STRIDE,
    eVertexBindingBuffer = GL_VERTEX_BINDING_BUFFER,
    eMaxVertexAttribRelativeOffset = GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET,
    eMaxVertexAttribBindings = GL_MAX_VERTEX_ATTRIB_BINDINGS,
    eViewport = GL_VIEWPORT,
    eViewportBoundsRange = GL_VIEWPORT_BOUNDS_RANGE,
    eViewportIndexProvokingVertex = GL_VIEWPORT_INDEX_PROVOKING_VERTEX,
    eViewportSubpixelBits = GL_VIEWPORT_SUBPIXEL_BITS,
    eMaxElementIndex = GL_MAX_ELEMENT_INDEX
};

template <typename T>
class ArrayProxy {
   public:
    constexpr ArrayProxy() noexcept : m_count(0), m_ptr(nullptr) {}

    constexpr ArrayProxy(std::nullptr_t) noexcept
        : m_count(0), m_ptr(nullptr) {}

    ArrayProxy(T &value) noexcept : m_count(1), m_ptr(&value) {}

    template <typename B = T,
              typename std::enable_if<std::is_const<B>::value, int>::type = 0>
    ArrayProxy(typename std::remove_const<T>::type &value) noexcept
        : m_count(1), m_ptr(&value) {}

    ArrayProxy(uint32_t count, T *ptr) noexcept : m_count(count), m_ptr(ptr) {}

    template <typename B = T,
              typename std::enable_if<std::is_const<B>::value, int>::type = 0>
    ArrayProxy(uint32_t count,
               typename std::remove_const<T>::type *ptr) noexcept
        : m_count(count), m_ptr(ptr) {}

    ArrayProxy(std::initializer_list<T> const &list) noexcept
        : m_count(static_cast<uint32_t>(list.size())), m_ptr(list.begin()) {}

    template <typename B = T,
              typename std::enable_if<std::is_const<B>::value, int>::type = 0>
    ArrayProxy(std::initializer_list<typename std::remove_const<T>::type> const
                   &list) noexcept
        : m_count(static_cast<uint32_t>(list.size())), m_ptr(list.begin()) {}

    ArrayProxy(std::initializer_list<T> &list) noexcept
        : m_count(static_cast<uint32_t>(list.size())), m_ptr(list.begin()) {}

    template <typename B = T,
              typename std::enable_if<std::is_const<B>::value, int>::type = 0>
    ArrayProxy(std::initializer_list<typename std::remove_const<T>::type>
                   &list) noexcept
        : m_count(static_cast<uint32_t>(list.size())), m_ptr(list.begin()) {}

    template <size_t N>
    ArrayProxy(std::array<T, N> const &data) noexcept
        : m_count(N), m_ptr(data.data()) {}

    template <size_t N, typename B = T,
              typename std::enable_if<std::is_const<B>::value, int>::type = 0>
    ArrayProxy(
        std::array<typename std::remove_const<T>::type, N> const &data) noexcept
        : m_count(N), m_ptr(data.data()) {}

    template <size_t N>
    ArrayProxy(std::array<T, N> &data) noexcept
        : m_count(N), m_ptr(data.data()) {}

    template <size_t N, typename B = T,
              typename std::enable_if<std::is_const<B>::value, int>::type = 0>
    ArrayProxy(
        std::array<typename std::remove_const<T>::type, N> &data) noexcept
        : m_count(N), m_ptr(data.data()) {}

    template <
        class Allocator = std::allocator<typename std::remove_const<T>::type>>
    ArrayProxy(std::vector<T, Allocator> const &data) noexcept
        : m_count(static_cast<uint32_t>(data.size())), m_ptr(data.data()) {}

    template <
        class Allocator = std::allocator<typename std::remove_const<T>::type>,
        typename B = T,
        typename std::enable_if<std::is_const<B>::value, int>::type = 0>
    ArrayProxy(std::vector<typename std::remove_const<T>::type, Allocator> const
                   &data) noexcept
        : m_count(static_cast<uint32_t>(data.size())), m_ptr(data.data()) {}

    template <
        class Allocator = std::allocator<typename std::remove_const<T>::type>>
    ArrayProxy(std::vector<T, Allocator> &data) noexcept
        : m_count(static_cast<uint32_t>(data.size())), m_ptr(data.data()) {}

    template <
        class Allocator = std::allocator<typename std::remove_const<T>::type>,
        typename B = T,
        typename std::enable_if<std::is_const<B>::value, int>::type = 0>
    ArrayProxy(std::vector<typename std::remove_const<T>::type, Allocator>
                   &data) noexcept
        : m_count(static_cast<uint32_t>(data.size())), m_ptr(data.data()) {}

    const T *begin() const noexcept { return m_ptr; }

    const T *end() const noexcept { return m_ptr + m_count; }

    const T &front() const noexcept {
        OPENGL_HPP_ASSERT(m_count && m_ptr);
        return *m_ptr;
    }

    const T &back() const noexcept {
        OPENGL_HPP_ASSERT(m_count && m_ptr);
        return *(m_ptr + m_count - 1);
    }

    bool empty() const noexcept { return (m_count == 0); }

    uint32_t size() const noexcept { return m_count; }

    T *data() const noexcept { return m_ptr; }

   private:
    uint32_t m_count;
    T *m_ptr;
};

class Buffer {
   public:
    using handleType = GLuint;

    template <typename Dispatch>
    static constexpr auto const &createFunc = &Dispatch::glCreateBuffers;

    template <typename Dispatch>
    static constexpr auto const &deleteFunc = &Dispatch::glDeleteBuffers;

    enum class BindTarget {
        eArrayBuffer = GL_ARRAY_BUFFER,
        eAtomicCounterBuffer = GL_ATOMIC_COUNTER_BUFFER,
        eCopyReadBuffer = GL_COPY_READ_BUFFER,
        eCopyWriteBuffer = GL_COPY_WRITE_BUFFER,
        eDispatchIndirectBuffer = GL_DISPATCH_INDIRECT_BUFFER,
        eDrawIndirectBuffer = GL_DRAW_INDIRECT_BUFFER,
        eElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
        ePixelPackBuffer = GL_PIXEL_PACK_BUFFER,
        ePixelUnpackBuffer = GL_PIXEL_UNPACK_BUFFER,
        eQueryBuffer = GL_QUERY_BUFFER,
        eShaderStorageBuffer = GL_SHADER_STORAGE_BUFFER,
        eTextureBuffer = GL_TEXTURE_BUFFER,
        eTransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
        eUniformBuffer = GL_UNIFORM_BUFFER,
    };

    enum class BindBaseTarget {
        eAtomicCounterBuffer = GL_ATOMIC_COUNTER_BUFFER,
        eShaderStorageBuffer = GL_SHADER_STORAGE_BUFFER,
        eTransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
        eUniformBuffer = GL_UNIFORM_BUFFER,
    };

    Buffer() : m_Buffer(0) {}

    Buffer(std::nullptr_t) : m_Buffer(0) {}

    Buffer(GLuint buffer) : m_Buffer(buffer) {}

    Buffer &operator=(std::nullptr_t) noexcept {
        m_Buffer = 0;
        return *this;
    }

    Buffer &operator=(GLuint buffer) noexcept {
        m_Buffer = buffer;
        return *this;
    }

    explicit operator GLuint() const noexcept { return m_Buffer; }

    explicit operator bool() const noexcept { return m_Buffer != 0; }

    bool operator!() const noexcept { return m_Buffer == 0; }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void bind(BindTarget target,
              Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glBindBuffer(static_cast<GLenum>(target), m_Buffer);
    }
    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void bindBase(BindBaseTarget target, GLuint index,
                  Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glBindBufferBase(static_cast<GLenum>(target), index, m_Buffer);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void bindRange(BindBaseTarget target, GLuint index, GLintptr offset,
                   GLsizeiptr size,
                   Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glBindBufferRange(static_cast<GLenum>(target), index, m_Buffer,
                            offset, size);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void unbind(BindTarget target,
                Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glBindBuffer(static_cast<GLenum>(target), 0);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void destroy(Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) {
        deleteObject<Buffer>(*this);
    }

   private:
    GLuint m_Buffer;
};

class VertexArray {
   public:
    using handleType = GLuint;

    template <typename Dispatch>
    static constexpr auto const &createFunc = &Dispatch::glCreateVertexArrays;

    template <typename Dispatch>
    static constexpr auto const &deleteFunc = &Dispatch::glDeleteVertexArrays;

    enum class AttributeType {
        eByte = GL_BYTE,
        eDouble = GL_DOUBLE,
        eFixed = GL_FIXED,
        eFloat = GL_FLOAT,
        eHalfFloat = GL_HALF_FLOAT,
        eInt = GL_INT,
        eInt_2_10_10_10Rev = GL_INT_2_10_10_10_REV,
        eShort = GL_SHORT,
        eUnsignedByte = GL_UNSIGNED_BYTE,
        eUnsignedShort = GL_UNSIGNED_SHORT,
        eUnsignedInt = GL_UNSIGNED_INT,
        eUnsignedInt_2_10_10_10Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
        eUnsignedInt_10f_11f_11fRev = GL_UNSIGNED_INT_10F_11F_11F_REV,
    };

    VertexArray() : m_VertexArray(0) {}

    VertexArray(std::nullptr_t) : m_VertexArray(0) {}

    VertexArray(GLuint vertexarray) : m_VertexArray(vertexarray) {}

    VertexArray &operator=(std::nullptr_t) noexcept {
        m_VertexArray = 0;
        return *this;
    }

    VertexArray &operator=(GLuint vertexarray) noexcept {
        m_VertexArray = vertexarray;
        return *this;
    }

    explicit operator GLuint() const noexcept { return m_VertexArray; }

    explicit operator bool() const noexcept { return m_VertexArray != 0; }

    bool operator!() const noexcept { return m_VertexArray == 0; }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void attribBinding(GLuint attribindex, GLuint bindingindex,
                       Dispatch const &d = {
                           OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glVertexArrayAttribBinding(m_VertexArray, attribindex, bindingindex);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void bind(Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glBindVertexArray(m_VertexArray);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void unBind(Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glBindVertexArray(0);
    };

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void destroy(Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) {
        deleteObject<VertexArray>(*this);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    GLint getElementArrayBufferBinding(
        Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        GLint result{};
        d.glGetVertexArrayiv(m_VertexArray, GL_ELEMENT_ARRAY_BUFFER_BINDING,
                             &result);
        return result;
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    bool getVertexAttribArrayEnabled(GLuint index,
                                     Dispatch const &d = {
                                         OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        GLint result{};
        d.glGetVertexArrayIndexediv(m_VertexArray, index,
                                    GL_VERTEX_ATTRIB_ARRAY_ENABLED, &result);
        return result != GL_FALSE;
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    GLint getVertexAttribArraySize(GLuint index,
                                   Dispatch const &d = {
                                       OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        GLint result{};
        d.glGetVertexArrayIndexediv(m_VertexArray, index,
                                    GL_VERTEX_ATTRIB_ARRAY_SIZE, &result);
        return result;
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    GLint getVertexAttribArrayStride(GLuint index,
                                     Dispatch const &d = {
                                         OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        GLint result{};
        d.glGetVertexArrayIndexediv(m_VertexArray, index,
                                    GL_VERTEX_ATTRIB_ARRAY_STRIDE, &result);
        return result;
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    AttributeType getVertexAttribArrayType(
        GLuint index,
        Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        GLint result{};
        d.glGetVertexArrayIndexediv(m_VertexArray, index,
                                    GL_VERTEX_ATTRIB_ARRAY_TYPE, &result);
        return static_cast<AttributeType>(result);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    bool getVertexAttribArrayNormalized(
        GLuint index,
        Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        GLint result{};
        d.glGetVertexArrayIndexediv(m_VertexArray, index,
                                    GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &result);
        return result != GL_FALSE;
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    bool getVertexAttribArrayInteger(GLuint index,
                                     Dispatch const &d = {
                                         OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        GLint result{};
        d.glGetVertexArrayIndexediv(m_VertexArray, index,
                                    GL_VERTEX_ATTRIB_ARRAY_INTEGER, &result);
        return result != GL_FALSE;
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    bool getVertexAttribArrayLong(GLuint index,
                                  Dispatch const &d = {
                                      OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        GLint result{};
        d.glGetVertexArrayIndexediv(m_VertexArray, index,
                                    GL_VERTEX_ATTRIB_ARRAY_LONG, &result);
        return result != GL_FALSE;
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    GLint getVertexAttribArrayDivisor(
        GLuint index,
        Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        GLint result{};
        d.glGetVertexArrayIndexediv(m_VertexArray, index,
                                    GL_VERTEX_ATTRIB_ARRAY_DIVISOR, &result);
        return result;
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    GLint getVertexAttribRelativeOffset(
        GLuint index,
        Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        GLint result{};
        d.glGetVertexArrayIndexediv(m_VertexArray, index,
                                    GL_VERTEX_ATTRIB_RELATIVE_OFFSET, &result);
        return result;
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    GLint64 getVertexBindingOffset(GLuint index,
                                   Dispatch const &d = {
                                       OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        GLint64 result{};
        d.glGetVertexArrayIndexed64iv(m_VertexArray, index,
                                      GL_VERTEX_BINDING_OFFSET, &result);
        return result;
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void enableAttribute(GLuint index,
                         Dispatch const &d = {
                             OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glEnableVertexArrayAttrib(m_VertexArray, index);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void disableAttribute(GLuint index,
                          Dispatch const &d = {
                              OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glDisableVertexArrayAttrib(m_VertexArray, index);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void attributeFormat(GLuint attribindex, GLint size, AttributeType type,
                         GLboolean normalized, GLuint relativeoffset,
                         Dispatch const &d = {
                             OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glVertexArrayAttribFormat(m_VertexArray, attribindex, size,
                                    static_cast<GLenum>(type), normalized,
                                    relativeoffset);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void attributeIFormat(GLuint attribindex, GLint size, AttributeType type,
                          GLuint relativeoffset,
                          Dispatch const &d = {
                              OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glVertexArrayAttribIFormat(m_VertexArray, attribindex, size,
                                     static_cast<GLenum>(type), relativeoffset);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void attributeLFormat(GLuint attribindex, GLint size, AttributeType type,
                          GLuint relativeoffset,
                          Dispatch const &d = {
                              OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glVertexArrayAttribLFormat(m_VertexArray, attribindex, size,
                                     static_cast<GLenum>(type), relativeoffset);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void bindingDivisor(GLuint bindingindex, GLuint divisor,
                        Dispatch const &d = {
                            OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glVertexArrayBindingDivisor(m_VertexArray, bindingindex, divisor);
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void bindElementBuffer(Buffer const &buffer,
                           Dispatch const &d = {
                               OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        d.glVertexArrayElementBuffer(m_VertexArray,
                                     static_cast<GLuint>(buffer));
    }

    template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
    void bindVertexBuffers(GLuint firstBindingIndex,
                           ArrayProxy<const Buffer> const &buffers,
                           ArrayProxy<const GLintptr> const &offsets,
                           ArrayProxy<const GLsizei> const &strides,
                           Dispatch const &d = {
                               OPENGL_HPP_DEFAULT_DISPATCHER}) const {
        assert(buffers.size() == offsets.size() &&
               buffers.size() == strides.size());
        std::vector<handleType> vbos(buffers.begin(), buffers.end());
        d.glVertexArrayVertexBuffers(
            m_VertexArray, firstBindingIndex, static_cast<GLsizei>(vbos.size()),
            vbos.data(), offsets.data(), strides.data());
    }

   private:
    GLuint m_VertexArray;
};

// No index version,static length
template <typename _Tx, std::size_t N, typename Dispatch, typename>
inline decltype(auto) get(StateVariables pname, Dispatch const &d) {
    std::array<_Tx, N> result{};
    if constexpr (std::is_same_v<GLint, _Tx>) {
        d.glGetIntegerv(static_cast<GLenum>(pname), result.data());
    } else if constexpr (std::is_same_v<GLfloat, _Tx>) {
        d.glGetFloatv(static_cast<GLenum>(pname), result.data());
    } else if constexpr (std::is_same_v<GLdouble, _Tx>) {
        d.glGetDoublev(static_cast<GLenum>(pname), result.data());
    } else if constexpr (std::is_same_v<GLboolean, _Tx> ||
                         std::is_same_v<bool, _Tx>) {
        std::array<GLboolean, N> query{};
        d.glGetBooleanv(static_cast<GLenum>(pname), query.data());
        std::array<bool, N> boolResult;
        std::transform(query.cbegin(), query.cend(), boolResult.begin(),
                       [](const auto &val) { return static_cast<bool>(val); });
        return ArrayOrObject(boolResult);
    } else if constexpr (std::is_same_v<GLint64, _Tx>) {
        d.glGetBooleanv(static_cast<GLenum>(pname), result.data());
    }
    return ArrayOrObject(result);
}

template <typename _Tx, std::size_t N, typename Dispatch, typename>
inline decltype(auto) get(StateVariables pname, GLuint index,
                          Dispatch const &d) {
    std::array<_Tx, N> result{};
    if constexpr (std::is_same_v<GLint, _Tx>) {
        d.glGetIntegeri_v(static_cast<GLenum>(pname), index, result.data());
    } else if constexpr (std::is_same_v<GLfloat, _Tx>) {
        d.glGetFloati_v(static_cast<GLenum>(pname), index, result.data());
    } else if constexpr (std::is_same_v<GLdouble, _Tx>) {
        d.glGetDoublei_v(static_cast<GLenum>(pname), index, result.data());
    } else if constexpr (std::is_same_v<GLboolean, _Tx> ||
                         std::is_same_v<bool, _Tx>) {
        std::array<GLboolean, N> query{};
        d.glGetBooleani_v(static_cast<GLenum>(pname), index, query.data());
        std::array<bool, N> boolResult;
        std::transform(query.cbegin(), query.cend(), boolResult.begin(),
                       [](const auto &val) { return static_cast<bool>(val); });
        return ArrayOrObject(boolResult);
    } else if constexpr (std::is_same_v<GLint64, _Tx>) {
        d.glGetBooleani_v(static_cast<GLenum>(pname), index, result.data());
    }
    return ArrayOrObject(result);
}

template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
inline Error getError(Dispatch const &d = {OPENGL_HPP_DEFAULT_DISPATCHER}) {
    return static_cast<Error>(d.glGetError());
}

template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
inline void bindBuffersBase(Buffer::BindBaseTarget target,
                            GLuint firstBindingIndex,
                            ArrayProxy<const Buffer> const &buffers,
                            Dispatch const &d = {
                                OPENGL_HPP_DEFAULT_DISPATCHER}) {
    std::vector<Buffer::handleType> bufferHandles(buffers.begin(),
                                                  buffers.end());
    d.glBindBuffersBase(static_cast<GLenum>(target), firstBindingIndex,
                        static_cast<GLsizei>(bufferHandles.size()),
                        bufferHandles.data());
}

template <typename Dispatch = OPENGL_HPP_DEFAULT_DISPATCHER_TYPE>
inline void bindBuffersRange(Buffer::BindBaseTarget target,
                             GLuint firstBindingIndex,
                             ArrayProxy<const Buffer> const &buffers,
                             ArrayProxy<const GLintptr> const &offsets,
                             ArrayProxy<const GLsizeiptr> const &sizes,
                             Dispatch const &d = {
                                 OPENGL_HPP_DEFAULT_DISPATCHER}) {
    assert(buffers.size() == offsets.size() && buffers.size() == sizes.size());
    std::vector<Buffer::handleType> bufferHandles(buffers.begin(),
                                                  buffers.end());
    d.glBindBuffersRange(static_cast<GLenum>(target), firstBindingIndex,
                         static_cast<GLsizei>(bufferHandles.size()),
                         bufferHandles.data(), offsets.data(), sizes.data());
}

// dynamic length
template <typename T, typename Dispatch, typename>
inline std::vector<T> createObjectv(GLsizei n, Dispatch const &d) {
    assert(n >= 0);
    std::vector<typename T::handleType> handles(n);
    std::invoke(d.*T::template createFunc<Dispatch>, n, handles.data());
    return std::vector<T>(handles.cbegin(), handles.cend());
}

// static length, return single object if N = 1
template <typename T, GLsizei N, typename Dispatch, typename>
inline decltype(auto) createObject(Dispatch const &d) {
    std::array<typename T::handleType, N> handles;
    std::invoke(d.*T::template createFunc<Dispatch>, N, handles.data());
    std::array<T, N> result;
    std::transform(handles.cbegin(), handles.cend(), result.begin(),
                   [](const auto &val) { return T{val}; });
    return ArrayOrObject(result);
}

template <typename T, typename Dispatch, typename>
inline void deleteObject(ArrayProxy<const T> const &arrays, Dispatch const &d) {
    std::vector<typename T::handleType> handles(arrays.begin(), arrays.end());
    std::invoke(d.*T::template deleteFunc<Dispatch>,
                static_cast<GLsizei>(arrays.size()), handles.data());
}

template <typename _Tx, size_t N>
inline constexpr decltype(auto) ArrayOrObject(
    std::array<_Tx, N> &_array) noexcept {
    if constexpr (N == 1) {
        return _array[0];
    } else {
        return _array;
    }
}

void initLoader(DispatchLoaderDynamic::PFN_GetProcAddr const & pGetProcAddr){
#if defined(OPENGL_HPP_DISPATCH_LOADER_DYNAMIC)
    OPENGL_HPP_DEFAULT_DISPATCHER = gl::DispatchLoaderDynamic(pGetProcAddr);
#endif // OPENGL_HPP_DISPATCH_LOADER_DYNAMIC
}

}  // namespace OPENGL_HPP_NAMESPACE

#endif  // OPENGL_HPP
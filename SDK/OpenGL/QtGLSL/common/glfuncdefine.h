#ifndef GLFUNCDEFINE_H
#define GLFUNCDEFINE_H
#include <QtOpenGL>
#include <QOpenGLFunctions_4_4_Compatibility>

#define MyGLFunc ((QOpenGLExtraFunctions*)(QOpenGLContext::currentContext()->functions()))
#define MyGLFuncOfVer ((QOpenGLFunctions_4_4_Compatibility*)(QOpenGLContext::currentContext()->versionFunctions()))
#define glEnable					MyGLFunc->glEnable
#define glDisable					MyGLFunc->glDisable
#define glClearDepth					MyGLFunc->glClearDepthf
#define glCullFace					MyGLFunc->glCullFace
#define glDepthFunc					MyGLFunc->glDepthFunc
#define glGetIntegerv					MyGLFunc->glGetIntegerv

#define glCreateShader					MyGLFunc->glCreateShader
#define glShaderSource 					MyGLFunc->glShaderSource
#define glCompileShader 				MyGLFunc->glCompileShader
#define glGetShaderiv   				MyGLFunc->glGetShaderiv
#define glGetShaderInfoLog 				MyGLFunc->glGetShaderInfoLog
#define glCreateProgram 				MyGLFunc->glCreateProgram
#define glAttachShader  				MyGLFunc->glAttachShader
#define glLinkProgram   				MyGLFunc->glLinkProgram
#define glDeleteShader  				MyGLFunc->glDeleteShader
#define glGetProgramiv  				MyGLFunc->glGetProgramiv
#define glGetProgramInfoLog 				MyGLFunc->glGetProgramInfoLog
#define glIsProgram  					MyGLFunc->glIsProgram
#define glUseProgram					MyGLFunc->glUseProgram
#define glGetUniformLocation 				MyGLFunc->glGetUniformLocation
#define glGetActiveUniformBlockiv       		MyGLFunc->glGetActiveUniformBlockiv
#define glGenerateMipmap                		MyGLFunc->glGenerateMipmap
#define glDrawArrays					MyGLFunc->glDrawArrays
#define glDrawArraysInstanced				MyGLFunc->glDrawArraysInstanced
#define glDrawElements					MyGLFunc->glDrawElements
#define glDrawElementsInstanced				MyGLFunc->glDrawElementsInstanced
#define glGenTextures                   		MyGLFunc->glGenTextures
#define glBindTexture                   		MyGLFunc->glBindTexture
#define glTexParameteri                 		MyGLFunc->glTexParameteri
#define glTexParameterf                                 MyGLFunc->glTexParameterf
#define glGetError                      		MyGLFunc->glGetError
#define glTexImage2D                    		MyGLFunc->glTexImage2D
#define glDeleteTextures                                MyGLFunc->glDeleteTextures
#define glGenVertexArrays               		MyGLFunc->glGenVertexArrays
#define glBindVertexArray               		MyGLFunc->glBindVertexArray
#define glDeleteVertexArrays            		MyGLFunc->glDeleteVertexArrays
#define glVertexAttribPointer           		MyGLFunc->glVertexAttribPointer
#define glEnableVertexAttribArray       		MyGLFunc->glEnableVertexAttribArray
#define glDisableVertexAttribArray                      MyGLFunc->glDisableVertexAttribArray
#define glGenBuffers					MyGLFunc->glGenBuffers
#define glBindBuffer					MyGLFunc->glBindBuffer
#define glBindBufferBase                                MyGLFunc->glBindBufferBase
#define glDeleteBuffers					MyGLFunc->glDeleteBuffers
#define glBufferData                    		MyGLFunc->glBufferData
#define glBufferSubData					MyGLFunc->glBufferSubData
#define glGenTransformFeedbacks                         MyGLFunc->glGenTransformFeedbacks
#define glBindTransformFeedback                         MyGLFunc->glBindTransformFeedback
#define glTransformFeedbackVaryings                     MyGLFunc->glTransformFeedbackVaryings
#define glBeginTransformFeedback                        MyGLFunc->glBeginTransformFeedback
#define glEndTransformFeedback                          MyGLFunc->glEndTransformFeedback
#define glFramebufferTexture				MyGLFunc->glFramebufferTexture2D
#define glUniform1i					MyGLFunc->glUniform1i
#define glUniform1f                     		MyGLFunc->glUniform1f
#define glUniform3fv                    		MyGLFunc->glUniform3fv
#define glUniform4fv                    		MyGLFunc->glUniform4fv
#define glUniformMatrix3fv				MyGLFunc->glUniformMatrix3fv
#define glUniformMatrix4fv				MyGLFunc->glUniformMatrix4fv
#define glActiveTexture					MyGLFunc->glActiveTexture

#define glShaderModel                                   MyGLFuncOfVer->glShadeModel
#define glPolygonMode                                   MyGLFuncOfVer->glPolygonMode
#define glDrawElementsBaseVertex        		MyGLFuncOfVer->glDrawElementsBaseVertex
#define glDrawTransformFeedback                         MyGLFuncOfVer->glDrawTransformFeedback
#define glTexImage1D                                    MyGLFuncOfVer->glTexImage1D
#endif // GLFUNCDEFINE_H

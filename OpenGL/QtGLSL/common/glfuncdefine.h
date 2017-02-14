#ifndef GLFUNCDEFINE_H
#define GLFUNCDEFINE_H
#include <QtOpenGL>
#include <QOpenGLFunctions_4_1_Compatibility>

#define MyGLFunc ((QOpenGLExtraFunctions*)(QOpenGLContext::currentContext()->functions()))
#define glClearDepth					MyGLFunc->glClearDepthf
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
#define glGetProgramInfoLog 			MyGLFunc->glGetProgramInfoLog
#define glIsProgram  					MyGLFunc->glIsProgram
#define glUseProgram					MyGLFunc->glUseProgram
#define glGetUniformLocation 			MyGLFunc->glGetUniformLocation
#define glGetActiveUniformBlockiv       MyGLFunc->glGetActiveUniformBlockiv
#define glGenerateMipmap                MyGLFunc->glGenerateMipmap
#define glDrawArrays					MyGLFunc->glDrawArrays
#define glDrawArraysInstanced			MyGLFunc->glDrawArraysInstanced
#define glDrawElements					MyGLFunc->glDrawElements
#define glDrawElementsBaseVertex        MyGLFunc->glDrawElementsBaseVertex
#define glDrawElementsInstanced			MyGLFunc->glDrawElementsInstanced
#define glGenTextures                   MyGLFunc->glGenTextures
#define glBindTexture                   MyGLFunc->glBindTexture
#define glTexParameteri                 MyGLFunc->glTexParameteri
#define glGetError                      MyGLFunc->glGetError
#define glTexImage2D                    MyGLFunc->glTexImage2D
#define glGenVertexArrays               MyGLFunc->glGenVertexArrays
#define glBindVertexArray               MyGLFunc->glBindVertexArray
#define glDeleteVertexArrays            MyGLFunc->glDeleteVertexArrays
#define glVertexAttribPointer           MyGLFunc->glVertexAttribPointer
#define glEnableVertexAttribArray       MyGLFunc->glEnableVertexAttribArray
#define glGenBuffers			  		MyGLFunc->glGenBuffers
#define glBindBuffer			        MyGLFunc->glBindBuffer
#define glDeleteBuffers			  		MyGLFunc->glDeleteBuffers
#define glBufferData                    MyGLFunc->glBufferData
#define glUniform1f                     MyGLFunc->glUniform1f
#define glUniform4fv                    MyGLFunc->glUniform4fv

#endif // GLFUNCDEFINE_H

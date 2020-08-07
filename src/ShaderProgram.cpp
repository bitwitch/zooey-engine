#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vert_path, const char* frag_path) 
{
    m_vertexShaderId = loadShader(vert_path, GL_VERTEX_SHADER);
    m_fragmentShaderId = loadShader(frag_path, GL_FRAGMENT_SHADER);
    m_programId = glCreateProgram();
    glAttachShader(m_programId, m_vertexShaderId);
    glAttachShader(m_programId, m_fragmentShaderId);
    glLinkProgram(m_programId);
    glValidateProgram(m_programId);

	GLint status;
	glGetProgramiv (m_programId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length_info_log;
		glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &length_info_log);

		GLchar *info_log = new GLchar[length_info_log + 1];
		glGetProgramInfoLog(m_programId, length_info_log, NULL, info_log);
		fprintf(stderr, "Linker failure: %s\n", info_log);
		delete[] info_log;
	}
}

void ShaderProgram::start() 
{
    glUseProgram(m_programId);
}

void ShaderProgram::stop() 
{
    glUseProgram(0);
}

ShaderProgram::~ShaderProgram()
{
    stop();
    glDetachShader(m_programId, m_vertexShaderId);
    glDetachShader(m_programId, m_fragmentShaderId);
    glDeleteShader(m_vertexShaderId);
    glDeleteShader(m_fragmentShaderId);
    glDeleteProgram(m_programId);
}

void ShaderProgram::bindAttribute(GLuint attribute, const char* variable_name) 
{
    const GLchar* name = (const GLchar *)variable_name;
    glBindAttribLocation(m_programId, attribute, name);
}

GLuint ShaderProgram::loadShader(const char* filename, GLenum shader_type) 
{
    // read shader file into a buffer
    char *buffer = NULL;
    long length;
    FILE *fp = fopen(filename, "r");

    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buffer = (char *)malloc(length + 1); // for null character
        if (buffer) 
        {
            fread(buffer, 1, length, fp);
            buffer[length] = '\0';
        }
        fclose(fp);
    }

    if (!buffer)
    {
        printf("Error reading shader %s\n", filename);
        throw;
    }

    const GLchar* shader_source = (const GLchar *)buffer;

	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length_info_log;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length_info_log);

		GLchar* info_log = new GLchar[length_info_log + 1];
		glGetShaderInfoLog(shader, length_info_log, NULL, info_log);

		const char* str_shader_type = NULL;
		switch(shader_type)
		{
            case GL_VERTEX_SHADER: str_shader_type = "vertex"; break;
            case GL_GEOMETRY_SHADER: str_shader_type = "geometry"; break;
            case GL_FRAGMENT_SHADER: str_shader_type = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", str_shader_type, info_log);
		delete[] info_log;
	}

	return shader;
}

void ShaderProgram::loadFloat(GLuint location, GLfloat value) {
    glUniform1f(location, value);
}

void ShaderProgram::loadVector(GLuint location, glm::vec3 vector) {
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::loadBool(GLuint location, bool value) {
    GLfloat to_load = 0;
    if (value)
        to_load = 1;
    glUniform1f(location, to_load);
}

void ShaderProgram::loadMatrix(GLuint location, glm::mat4 matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint ShaderProgram::getUniformLocation(const char* uniformName) {
    return glGetUniformLocation(m_programId, uniformName);
}


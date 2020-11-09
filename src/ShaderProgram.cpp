#include "shader_program.h"

Shader_Program::Shader_Program(const char* vert_path, const char* frag_path) 
{
    vertex_shader_id = load_shader(vert_path, GL_VERTEX_SHADER);
    fragment_shader_id = load_shader(frag_path, GL_FRAGMENT_SHADER);
    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    glValidateProgram(program_id);

	GLint status;
	glGetProgramiv (program_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length_info_log;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length_info_log);

		GLchar *info_log = new GLchar[length_info_log + 1];
		glGetProgramInfoLog(program_id, length_info_log, NULL, info_log);
		fprintf(stderr, "Linker failure: %s\n", info_log);
		delete[] info_log;
	}
}

void Shader_Program::start() 
{
    glUseProgram(program_id);
}

void Shader_Program::stop() 
{
    glUseProgram(0);
}

Shader_Program::~Shader_Program()
{
    stop();
    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    glDeleteProgram(program_id);
}

void Shader_Program::bind_attribute(GLuint attribute, const char* name) {
    glBindAttribLocation(program_id, attribute, name);
}

GLuint Shader_Program::load_shader(const char* filename, GLenum shader_type) 
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

void Shader_Program::load_float(GLuint location, GLfloat value) {
    glUniform1f(location, value);
}

void Shader_Program::load_vector(GLuint location, glm::vec3 vector) {
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader_Program::load_bool(GLuint location, bool value) {
    GLfloat to_load = 0;
    if (value)
        to_load = 1;
    glUniform1f(location, to_load);
}

void Shader_Program::load_matrix(GLuint location, const glm::mat4* matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint Shader_Program::getUniformLocation(const char* uniformName) {
    return glGetUniformLocation(program_id, uniformName);
}


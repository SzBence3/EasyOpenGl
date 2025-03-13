#include "ShaderProgram.h"
#include<fstream>
#include<iostream>
#include<GL/glew.h>
#include"Debug.h"
#include<iostream>
#include<stdexcept>
namespace eogl {
	unsigned int ShaderProgram::compileShader(unsigned int type, std::string source)
	{
		unsigned int s_id;
		s_id = glCreateShader(type);
		const char* ptr = source.c_str();
		GlCall(glShaderSource(s_id, 1, &ptr, NULL));
		GlCall(glCompileShader(s_id));
		int result;
		GlCall(glGetShaderiv(s_id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) {
			int length;
			GlCall(glGetShaderiv(s_id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length);
			GlCall(glGetShaderInfoLog(s_id, length, &length, message));
			std::cout << "Shader failed to compile!" << std::endl
				<< message << std::endl;
			GlCall(glDeleteShader(s_id));
			
			return 0;
		}

		return s_id;
	}

	int ShaderProgram::getUniformLocation(std::string name)
	{

		if (cache.count(name)) {
			return cache[name];

		}
		GlCall(int res = glGetUniformLocation(id, name.c_str()));
		if (res == -1)std::cout << "Warnig: Uniform: " << name << " is not found!\n";
		return cache[name] = res;
	}

	ShaderProgram::ShaderProgram(std::string vspath, std::string fspath) {
		init(vspath, fspath, 1, "");
	}

	ShaderProgram::ShaderProgram(std::string vspath, std::string fspath, bool isPath) {
		init(vspath, fspath, isPath, "");
	}

	ShaderProgram::ShaderProgram(std::string vspath, std::string fspath, std::string gspath) {
		init(vspath, fspath, 1, gspath);
	}

	ShaderProgram::ShaderProgram(std::string vspath, std::string fspath, bool isPath = true, std::string gspath = "") {
		init(vspath, fspath, isPath, gspath);
	}
	void ShaderProgram::init(std::string vspath, std::string fspath, bool isPath = true, std::string gspath = "")
	{
		std::string vs, fs, gs;
		if (isPath) {
			std::ifstream fin(vspath);
			if (!fin.is_open())
				throw std::invalid_argument("vertex shader at "+vspath+" can't be opened!");
			while (!fin.eof()) {
				std::string s;
				getline(fin, s);
				vs += s+"\n";
			}
			std::ifstream fin2(fspath);
			if (!fin2.is_open())
				throw std::invalid_argument("fragment shader at " + fspath + " can't be opened!");
			while (!fin2.eof()) {
				std::string s;
				getline(fin2, s);
				fs += s+"\n";
			}
			fin.close();
			fin2.close();
			if (gspath != "") {
				std::ifstream fin3(gspath);
				if (!fin3)
					throw std::invalid_argument("geometry shader at " + gspath + " can't be opened!");
				while (!fin3.eof()) {
					std::string s;
					getline(fin3, s);
					gs += s + "\n";
				}
				fin3.close();
			}
		}
		else {
			vs = vspath;
			fs = fspath;
			gs = gspath;
		}

		GlCall(id = glCreateProgram());
		unsigned int vsid = compileShader(GL_VERTEX_SHADER, vs), fsid = compileShader(GL_FRAGMENT_SHADER, fs);
		
		GlCall(glAttachShader(id, vsid));
		unsigned int gsid;
		if (gs != "") {
			gsid = compileShader(GL_GEOMETRY_SHADER, gs);
			GlCall(glAttachShader(id, gsid));
		}
		GlCall(glAttachShader(id, fsid));

		GlCall(glLinkProgram(id));
		int success;
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog [512];
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			ASSERT(0);
		}

		GlCall(glValidateProgram(id));

		GlCall(glDeleteShader(vsid));
		GlCall(glDeleteShader(fsid));
		if(gspath != "") glDeleteShader(gsid);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(id);
	}

	void ShaderProgram::setUniform(const std::string name,float v1, float v2, float v3, float v4)
	{
		bind();
		GlCall(glUniform4f(getUniformLocation(name), v1, v2, v3, v4));
	}
	void ShaderProgram::setUniform(const std::string name, glm::vec3 v)
	{
		bind();
		GlCall(glUniform3f(getUniformLocation(name), v.x, v.y, v.z));
	}
	void ShaderProgram::setUniform(const std::string name, glm::vec4 v)
	{
		bind();
		GlCall(glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w));
	}
	void ShaderProgram::setUniform(const std::string name, glm::vec2 v)
	{
		bind();
		GlCall(glUniform2f(getUniformLocation(name), v.x, v.y));
	}
	void ShaderProgram::setUniform(const std::string name, float v1, float v2, float v3)
	{
		bind();
		GlCall(glUniform3f(getUniformLocation(name), v1, v2, v3));
	}
	void ShaderProgram::setUniform(const std::string name, float v1, float v2)
	{
		bind();
		GlCall(glUniform2f(getUniformLocation(name), v1, v2));
	}
	void ShaderProgram::setUniform(const std::string name, float v1)
	{
		bind();
		GlCall(glUniform1f(getUniformLocation(name), v1));
	}
	void ShaderProgram::setUniform(const std::string name, int v1)
	{
		bind();
		GlCall(glUniform1i(getUniformLocation(name), v1));
	}
	void ShaderProgram::setUniform(const std::string name, int v1, int v2)
	{
		bind();
		GlCall(glUniform2i(getUniformLocation(name), v1, v2));
	}
	void ShaderProgram::setUniform(const std::string name, glm::mat4 mat) {
		GlCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
	}

	void ShaderProgram::bind()
	{
		GlCall(glUseProgram(id));
	}

	void ShaderProgram::unBind()
	{
		glUseProgram(0);
	}
}
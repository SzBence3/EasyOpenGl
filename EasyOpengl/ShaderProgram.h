#pragma once
#include<string>
#include<unordered_map>
#include<string>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace eogl {
	class ShaderProgram {
		unsigned int id;
		std::unordered_map<std::string, int>cache;
		unsigned int compileShader(unsigned int type, std::string source);
		int getUniformLocation(std::string name);
	public:
		ShaderProgram(std::string vspath, std::string fspath);
		ShaderProgram(std::string vspath, std::string fspath, bool isPath);
		ShaderProgram(std::string vspath, std::string fspath, std::string gspath);
		ShaderProgram(std::string vspath,std::string fspath, bool isPath, std::string gs);
		void init(std::string vspath, std::string fspath, bool isPath, std::string gspath);
		~ShaderProgram();
		void setUniform(const std::string name, float v1, float v2, float v3, float v4);
		void setUniform(const std::string name, float v1, float v2, float v3);
		void setUniform(const std::string name, float v1, float v2);
		void setUniform(const std::string name, float v1);
		void setUniform(const std::string name, int v1);
		void setUniform(const std::string name, int v1, int v2);
		void setUniform(const std::string name, const glm::mat4 mat);
		void setUniform(const std::string name, const glm::vec2 v);
		void setUniform(const std::string name, const glm::vec3 v);
		void setUniform(const std::string name, const glm::vec4 v);

		void bind();
		void unBind();
	};
}
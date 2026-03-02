#include "DebugDraw.h"
#include<iostream>

#include <vector>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


struct DebugVertex {

    glm::vec3 position;
    glm::vec3 color;

};

namespace DebugDraw
{
    static std::vector<DebugVertex> s_Vertices;

    static GLuint s_VAO = 0;
    static GLuint s_VBO = 0;
    static GLuint s_Shader = 0;

    void Init() {

        glGenVertexArrays(1, &s_VAO);
        glGenBuffers(1, &s_VBO);

        glBindVertexArray(s_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color));
        
        glBindVertexArray(0);

        const char* vertexSrc = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;

        uniform mat4 u_ViewProj;

        out vec3 vColor;

        void main()
        {
            vColor = aColor;
            gl_Position = u_ViewProj * vec4(aPos, 1.0);
        }
        )";

        const char* fragmentSrc = R"(
        #version 330 core
        in vec3 vColor;
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(vColor, 1.0);
        }
        )";

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertexSrc, nullptr);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragmentSrc, nullptr);
        glCompileShader(fs);

        s_Shader = glCreateProgram();
        glAttachShader(s_Shader, vs);
        glAttachShader(s_Shader, fs);
        glLinkProgram(s_Shader);

        GLint success;                                             //Linking Error Checker
        glGetProgramiv(s_Shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            char info[512];
            glGetProgramInfoLog(s_Shader, 512, nullptr, info);
            std::cout << "Shader Link Error:\n" << info << std::endl;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);

    
    }
    void Shutdown() {
    
        glDeleteBuffers(1, &s_VBO);
        glDeleteVertexArrays(1, &s_VAO);
        glDeleteProgram(s_Shader);

    }
    void BeginFrame() {
        
        s_Vertices.clear();
    
    }
    void EndFrame(const glm::mat4& viewProj) {

        if (s_Vertices.empty())
            return;

        glUseProgram(s_Shader);

        glUniformMatrix4fv(glGetUniformLocation(s_Shader, "u_ViewProj"), 1, GL_FALSE, glm::value_ptr(viewProj));

        glBindVertexArray(s_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);

        glBufferData(GL_ARRAY_BUFFER, s_Vertices.size() * sizeof(DebugVertex),s_Vertices.data(), GL_DYNAMIC_DRAW);
        glDrawArrays(GL_LINES, 0, (GLsizei)s_Vertices.size());

        glBindVertexArray(0);


    
    }
    void DrawLine(
        const glm::vec3& start,
        const glm::vec3& end,
        const glm::vec3& color) {

        s_Vertices.push_back({ start, color });
        s_Vertices.push_back({ end, color });


    }
}

//
// Created by Jeramy on 7/22/2015.
//

#ifndef SUSHI_MESH_HPP
#define SUSHI_MESH_HPP

#include "gl.hpp"
#include "common.hpp"

#include <string>

/// Sushi
namespace sushi {

/// Deleter for OpenGL buffer objects.
struct buffer_deleter {
    using pointer = fake_nullable<GLuint>;

    void operator()(pointer p) const {
        auto buf = GLuint(p);
        glDeleteBuffers(1, &buf);
    }
};

/// Deleter for OpenGL vertex array objects.
struct vertex_array_deleter {
    using pointer = fake_nullable<GLuint>;

    void operator()(pointer p) const {
        auto buf = GLuint(p);
        glDeleteVertexArrays(1, &buf);
    }
};

/// A unique handle to an OpenGL buffer object.
using unique_buffer = unique_gl_resource<buffer_deleter>;

/// A unique handle to an OpenGL vertex array object.
using unique_vertex_array = unique_gl_resource<vertex_array_deleter>;

/// Creates a unique OpenGL buffer object.
/// \return A unique buffer object.
inline unique_buffer make_unique_buffer() {
    GLuint buf;
    glGenBuffers(1, &buf);
    return unique_buffer(buf);
}

/// Creates a unique OpenGL vertex array object.
/// \return A unique vertex array object.
inline unique_vertex_array make_unique_vertex_array() {
    GLuint buf;
    glGenVertexArrays(1, &buf);
    return unique_vertex_array(buf);
}

/// A static OpenGL mesh made of triangles.
struct static_mesh {
    unique_vertex_array vao;
    unique_buffer vertex_buffer;
    int num_triangles = 0;
};

struct attrib_location {
    static constexpr auto POSITION = 0;
    static constexpr auto TEXCOORD = 1;
    static constexpr auto NORMAL = 2;
};

/// Loads a mesh from an OBJ file.
/// The following OBJ directives are supported:
/// - `#` - Comments
/// - `v` - Vertex location.
/// - `vn` - Vertex normal.
/// - `vt` - Vertex texture coordinate.
/// - `f` - Face (triangles only).
/// \param fname File name.
/// \return The static mesh described by the file.
static_mesh load_static_mesh(const std::string& fname);

/// Draws a mesh.
/// \param mesh The mesh to draw.
inline void draw_mesh(const static_mesh& mesh) {
    glBindVertexArray(mesh.vao.get());
    glDrawArrays(GL_TRIANGLES, 0, mesh.num_triangles * 3);
}

}

#endif //SUSHI_MESH_HPP

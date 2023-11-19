#ifndef CUBE_H
#define CUBE_H
float vertices[] = {
    // Vertices of the cube
    -1.0f, -1.0f, 1.0f,    // Vertex 0
     1.0f, -1.0f, 1.0f,    // Vertex 1
     1.0f,  1.0f, 1.0f,    // Vertex 2
    -1.0f,  1.0f, 1.0f,    // Vertex 3
    -1.0f, -1.0f, -1.0f,   // Vertex 4
     1.0f, -1.0f, -1.0f,   // Vertex 5
     1.0f,  1.0f, -1.0f,   // Vertex 6
    -1.0f,  1.0f, -1.0f    // Vertex 7
};

// Define indices for rendering triangles
unsigned int indices[] = {
    0, 1, 2,   // Front face
    0, 2, 3,   // Front face
    4, 5, 6,   // Back face
    4, 6, 7,   // Back face
    0, 4, 7,   // Left face
    0, 7, 3,   // Left face
    1, 5, 6,   // Right face
    1, 6, 2,   // Right face
    3, 2, 6,   // Top face
    3, 6, 7,   // Top face
    0, 1, 5,   // Bottom face
    0, 5, 4    // Bottom face
};
float colors[] = {
    // Colors for each vertex
    1.0f, 0.0f, 0.0f,  // Red   (Vertex 0)
    1.0f, 0.0f, 0.0f,  // Red   (Vertex 1)
    0.0f, 1.0f, 0.0f,  // Green (Vertex 2)
    0.0f, 1.0f, 0.0f,  // Green (Vertex 3)
    0.0f, 0.0f, 1.0f,  // Blue  (Vertex 4)
    0.0f, 0.0f, 1.0f,  // Blue  (Vertex 5)
    1.0f, 1.0f, 0.0f,  // Yellow (Vertex 6)
    1.0f, 1.0f, 0.0f   // Yellow (Vertex 7)
};
#endif
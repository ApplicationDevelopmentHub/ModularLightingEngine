#pragma once
struct GPUMesh {
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;
   /* uint32_t indexCount = 0;

    ~GPUMesh() {
        if (ebo) glDeleteBuffers(1, &ebo);
        if (vbo) glDeleteBuffers(1, &vbo);
        if (vao) glDeleteVertexArrays(1, &vao);
    }*/
};

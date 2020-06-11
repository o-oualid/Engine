glslc default/shader.vert -o default/vert.spv
glslc default/shader.frag -o default/frag.spv
glslangValidator -V -x -o glsl_shader.frag.u32 glsl_shader.frag
glslangValidator -V -x -o glsl_shader.vert.u32 glsl_shader.vert

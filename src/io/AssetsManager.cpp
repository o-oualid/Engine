#include "AssetsManager.h"

#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <tiny_obj_loader.h>

#define STB_IMAGE_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION

#include <tiny_gltf.h>

namespace Engine {

    Model AssetsManager::loadModel(const std::string &path) {
        Model mModel;
        tinygltf::Model model;
        tinygltf::TinyGLTF loader;
        std::string err;
        std::string warn;
        loader.LoadBinaryFromFile(&model, &err, &warn, path);
        for (auto node:model.nodes) {
            NodeData nodeData{};
            nodeData.meshId = node.mesh;
            nodeData.name = node.name;
            nodeData.children = node.children;
            if (!node.translation.empty()) {

                nodeData.transform.location = {
                        (float) node.translation[0],
                        (float) node.translation[1],
                        (float) node.translation[2],};
            }

            if (!node.rotation.empty()) {
                nodeData.transform.rotation = {(float) node.rotation[3],
                                               (float) node.rotation[0],
                                               (float) node.rotation[1],
                                               (float) node.rotation[2]};
            }

            if (!node.scale.empty()) {
                nodeData.transform.scale = {(float) node.scale[0],
                                            (float) node.scale[1],
                                            (float) node.scale[2],};
            }

            mModel.nodes.push_back(nodeData);
        }

        for (const auto &mesh:model.meshes) {
            MeshData meshData{};

            for (tinygltf::Primitive primitive:mesh.primitives) {
                PrimitiveData primitiveData{};
                const tinygltf::Accessor &vertexAccessor = model.accessors[primitive.attributes["POSITION"]];
                const tinygltf::BufferView &vertexBufferView = model.bufferViews[vertexAccessor.bufferView];
                const tinygltf::Buffer &vertexBuffer = model.buffers[vertexBufferView.buffer];
                const auto *positions = reinterpret_cast<const float *>(&vertexBuffer.data[vertexBufferView.byteOffset +
                                                                                           vertexAccessor.byteOffset]);
                const float *normals;
                bool hasNormals = primitive.attributes["NORMAL"] != NULL;
                if (hasNormals) {
                    const tinygltf::Accessor &normalAccessor = model.accessors[primitive.attributes["NORMAL"]];
                    const tinygltf::BufferView &normalBufferView = model.bufferViews[normalAccessor.bufferView];
                    const tinygltf::Buffer &normalBuffer = model.buffers[normalBufferView.buffer];
                    normals = reinterpret_cast<const float *>(&normalBuffer.data[
                            normalBufferView.byteOffset +
                            normalAccessor.byteOffset]);
                }
                bool hasVertexColor = primitive.attributes["COLOR_0"] != NULL;
                const float *colors;

                if (hasVertexColor) {
                    const tinygltf::Accessor &colorAccessor = model.accessors[primitive.attributes["COLOR_0"]];
                    const tinygltf::BufferView &colorBufferView = model.bufferViews[colorAccessor.bufferView];
                    const tinygltf::Buffer &colorBuffer = model.buffers[colorBufferView.buffer];
                    colors = reinterpret_cast<const float *>(&colorBuffer.data[colorBufferView.byteOffset +
                                                                               colorAccessor.byteOffset]);
                }

                bool hasUV = primitive.attributes["TEXCOORD_0"] != NULL;
                const float *uv;
                if (hasUV) {
                    const tinygltf::Accessor &uvAccessor = model.accessors[primitive.attributes["TEXCOORD_0"]];
                    const tinygltf::BufferView &uvBufferView = model.bufferViews[uvAccessor.bufferView];
                    const tinygltf::Buffer &uvBuffer = model.buffers[uvBufferView.buffer];
                    uv = reinterpret_cast<const float *>(&uvBuffer.data[uvBufferView.byteOffset +
                                                                        uvAccessor.byteOffset]);
                }

                for (size_t i = 0; i < vertexAccessor.count; ++i) {
                    Vertex vertex{};
                    vertex.pos = {positions[i * 3 + 0],
                                  positions[i * 3 + 1],
                                  positions[i * 3 + 2],};

                    if (hasNormals) {
                        vertex.normal = {normals[i * 3 + 0],
                                         normals[i * 3 + 1],
                                         normals[i * 3 + 2],};
                    } else vertex.normal = {0, 0, 1,};
                    if (hasVertexColor) {
                        vertex.color = {colors[i * 4 + 0],
                                        colors[i * 4 + 1],
                                        colors[i * 4 + 2],};
                    } else vertex.color = {1, 0, 1,};

                    if (hasUV) vertex.uv = {uv[i * 2 + 0], uv[i * 2 + 1]};
                    else vertex.uv = {1.0f, 1.0f};

                    primitiveData.vertices.push_back(vertex);
                }

                tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];
                const tinygltf::BufferView &indexBufferView = model.bufferViews[indexAccessor.bufferView];
                const tinygltf::Buffer &indexBuffer = model.buffers[indexBufferView.buffer];
                switch (indexAccessor.componentType) {
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: {
                        const uint16_t *indices;
                        indices = reinterpret_cast<const uint16_t *>(&indexBuffer.data[
                                indexBufferView.byteOffset +
                                indexAccessor.byteOffset]);
                        for (size_t i = 0; i < indexAccessor.count; ++i) primitiveData.indices.push_back(indices[i]);

                    }
                        break;
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: {
                        const uint32_t *indices;
                        indices = reinterpret_cast<const uint32_t *>(&indexBuffer.data[
                                indexBufferView.byteOffset +
                                indexAccessor.byteOffset]);
                        for (size_t i = 0; i < indexAccessor.count; ++i) primitiveData.indices.push_back(indices[i]);
                    }
                        break;
                    default:
                        throw std::runtime_error("Indice type not defined");
                }

                if (primitive.material != -1) {
                    auto color = model.materials[primitive.material].pbrMetallicRoughness.baseColorFactor;
                    primitiveData.material.color = glm::vec4{color[0], color[1], color[2], color[3]};
                } else
                    primitiveData.material.color = glm::vec4{1.0f, 0.0f, 1.0f, 1.0f};


                meshData.primitives.push_back(primitiveData);
            }
            mModel.meshData.push_back(meshData);
        }
        return mModel;
    }

/*
    Mesh AssetsManager::loadModel(const std::string &path) {
        Mesh mesh{};
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
            throw std::runtime_error(warn + err);
        }


        std::unordered_map<Vertex, uint32_t> uniqueVertices{};

        for (const auto &shape : shapes) {
            for (const auto &index : shape.mesh.indices) {
                Vertex vertex{};

                vertex.pos = {
                        attrib.vertices[3 * index.vertex_index + 0],
                        attrib.vertices[3 * index.vertex_index + 1],
                        attrib.vertices[3 * index.vertex_index + 2],
                };

                vertex.uv = {
                        attrib.texcoords[2 * index.texcoord_index + 0],
                        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                };

                vertex.color = {
                        attrib.colors[3 * index.vertex_index + 0],
                        attrib.colors[3 * index.vertex_index + 1],
                        attrib.colors[3 * index.vertex_index + 2],
                };

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(mesh.vertices.size());
                    mesh.vertices.push_back(vertex);
                }

                mesh.indices.push_back(uniqueVertices[vertex]);
            }
        }
        return mesh;
    }
*/

/*
    Mesh AssetsManager::loadModel(const std::string &path) {
        Mesh mesh{};
        mesh.vertices = {
                Vertex{glm::vec3{-1.0f, +1.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec2{0, 1}},
                Vertex{glm::vec3{+1.0f, +1.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec2{1, 1}},
                Vertex{glm::vec3{+1.0f, -1.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec2{1, 0}},
                Vertex{glm::vec3{-1.0f, -1.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec2{0, 0}},
        };
        mesh.indices = {
                1,4,3,3,2,1,
        };
        return mesh;
    }
*/

    Texture AssetsManager::loadTexture(const std::string &path) {
        Texture texture{};
        texture.pixels = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.channels,
                                   STBI_rgb_alpha);
        if (!texture.pixels)
            throw std::runtime_error("failed to load texture image!");
        return texture;
    }

    void AssetsManager::freeTexture(Texture *texture) {
        stbi_image_free(texture->pixels);
    }

    std::vector<char> AssetsManager::loadFile(const std::string &path) {
        std::ifstream file(path, std::ios::ate | std::ios::binary);
        if (!file.is_open())
            throw std::runtime_error("failed to open file!");

        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        
        return buffer;
    }

}
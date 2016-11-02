#include "mesh.h"
#include <vector>

Mesh::Mesh(const string& fileName)
{
    m_model = OBJModel(fileName).ToIndexedModel();
    cout << "Sizeof positions: " << m_model.positions.size() << endl;

    InitMesh(m_model);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
    for(unsigned int i = 0; i < numVertices; i++)
    {
        m_model.positions.push_back(*vertices[i].GetPos());
        m_model.texCoords.push_back(*vertices[i].GetTexCoord());
        m_model.normals.push_back(*vertices[i].GetNormal());
    }

    for(unsigned int i = 0; i < numIndices; i++)
    {
        m_model.indices.push_back(indices[i]);
    }

    InitMesh(m_model);
//    m_drawCount = numIndices;

//    glGenVertexArrays(1, &m_vertexArrayObject);
//    glBindVertexArray(m_vertexArrayObject);
//
//    vector<glm::vec3> positions;
//    vector<glm::vec2> texCoords;
//
//    positions.reserve(numVertices);
//    texCoords.reserve(numVertices);
//
//    for(unsigned int i = 0; i < numVertices; i++)
//    {
//        positions.push_back(*vertices[i].GetPos());
//        texCoords.push_back(*vertices[i].GetTexCoord());
//    }
//
//    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[POSITION_VB]);
//    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[TEXCOORD_VB]);
//    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffer[INDEX_VB]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
//
//    glBindVertexArray(0);
}

Mesh::Mesh(const IndexedModel& model)
{
    InitMesh(model);
}

Mesh::Mesh()
{
    m_model.positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    m_model.texCoords.push_back(glm::vec2(0.0f, 0.0f));
    m_model.normals.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    m_model.indices.push_back(0);
    InitMesh(m_model);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::InitMesh(const IndexedModel& model)
{
    m_drawCount = model.indices.size();

    glGenVertexArrays(1, &m_vertexArrayObject);
        glBindVertexArray(m_vertexArrayObject);

        glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
        glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::AddModel(const IndexedModel& model)
{
    for(unsigned int i = 0; i < model.positions.size(); i++)
        m_model.positions.push_back(model.positions[i]);

    for(unsigned int i = 0; i < model.normals.size(); i++)
        m_model.normals.push_back(model.normals[i]);

    for(unsigned int i = 0; i < model.texCoords.size(); i++)
        m_model.texCoords.push_back(model.texCoords[i]);

    for(unsigned int i = 0; i < model.indices.size(); i++)
        m_model.indices.push_back(model.indices[i] + (m_model.indices.size() - 1));

}

void Mesh::Draw()
{
    glBindVertexArray(m_vertexArrayObject);

    glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

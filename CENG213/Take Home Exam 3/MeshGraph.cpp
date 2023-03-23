#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>


MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,
    const std::vector<IdPair>& edges)
{
    // TODO:
    vertices.resize(vertexPositions.size());
    adjList.resize(vertexPositions.size());
    for (int i = 0; i < vertexPositions.size(); i++)
    {
        vertices[i].id = i;
        vertices[i].position3D = vertexPositions[i];
    }
    for (int i = 0; i < edges.size(); i++)
    {

        adjList[edges[i].vertexId0].push_back(&vertices[edges[i].vertexId1]);
        adjList[edges[i].vertexId1].push_back(&vertices[edges[i].vertexId0]);
    }
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
    // TODO:
    double sum = 0;
    int num_vertices = adjList.size();
    std::vector<std::vector<bool> > visited;
    visited.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        visited[i].resize(num_vertices);
    }
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            visited[i][j] = false;
        }
    }

    for (int i = 0; i < adjList.size(); i++)
    {
        std::list<Vertex*>::const_iterator it = adjList[i].begin();
        //Double3 left = vertices[i].position3D;
        for (; it != adjList[i].end(); it++)
        {
            if (!visited[i][(*it)->id])
            {
                //Double3 right = (*it)->position3D;
                sum += vertices[i].position3D.Distance(vertices[i].position3D, (*it)->position3D);
                visited[i][(*it)->id] = true;
                visited[(*it)->id][i] = true;
            }
        }
    }
    return sum / TotalEdgeCount();
}

double MeshGraph::AverageEdgePerVertex() const
{
    // TODO:
    double sum = 0;
    int num_vertices = adjList.size();
    std::vector<std::vector<bool> > visited;
    visited.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        visited[i].resize(num_vertices);
    }
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            visited[i][j] = false;
        }
    }
    for (int i = 0; i < adjList.size(); i++)
    {
        sum += adjList[i].size();
    }
    sum /= 2;
    return sum / vertices.size();
}

int MeshGraph::TotalVertexCount() const
{
    // TODO:
    return vertices.size();
}

int MeshGraph::TotalEdgeCount() const
{
    // TODO:
    int sum = 0;

    for (int i = 0; i < vertices.size(); i++)
        sum += adjList[i].size();
    return sum / 2;
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    // TODO:
    if (vertexId > vertices.size() - 1 || vertexId < 0)
        return -1;

    return adjList[vertexId].size();
}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
    int vertexId) const
{
    outVertexIds.clear();
    // TODO:
    if (vertexId > vertices.size() - 1 || vertexId < 0)
        return;
    for (std::list<Vertex*>::const_iterator it = adjList[vertexId].begin(); it != adjList[vertexId].end(); it++)
    {
        outVertexIds.push_back((*it)->id);
    }
    return;
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
    int vertexIdFrom, int vertexIdTo,
    const Color& color) const
{
    // TODO:
    outputColorAllVertex.clear();
    if (vertexIdFrom < 0 || vertexIdFrom > vertices.size() - 1 || vertexIdTo < 0 || vertexIdTo > vertices.size() - 1)
        return;

    outputColorAllVertex.resize(vertices.size());
    for (int i = 0; i < outputColorAllVertex.size(); i++)
    {
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }
    BinaryHeap pq;
    std::vector<double> dist;
    dist.resize(vertices.size());
    for (int i = 0; i < dist.size(); i++)
    {
        dist[i] = INFINITY;
    }
    dist[vertexIdFrom] = 0;
    std::vector<int> path;
    path.resize(vertices.size(), -1);

    for (int i = 0; i < vertices.size(); i++)
    {
        if (i != vertexIdFrom)
        {
            pq.Add(i, INFINITY);
        }
    }
    pq.Add(vertexIdFrom, 0);
    while (!pq.isEmpty())
    {
        Vertex v;
        double weight;
        pq.PopHeap(v.id, weight);
        //visited[v.id] = true;
        for (std::list<Vertex*>::const_iterator it = adjList[v.id].begin(); it != adjList[v.id].end(); it++)
        {
            // I am currently traversing edges of vertexIdFrom
            double curr = weight + vertices[v.id].position3D.Distance(vertices[v.id].position3D, (*it)->position3D);
            if (curr < dist[(*it)->id])
            {
                dist[(*it)->id] = curr;
                path[(*it)->id] = v.id;
                pq.ChangePriority((*it)->id, curr);
            }
        }
    }
    int temp = vertexIdTo;

    while (temp != -1)
    {
        outputColorAllVertex[temp].r = color.r;
        outputColorAllVertex[temp].g = color.g;
        outputColorAllVertex[temp].b = color.b;
        temp = path[temp];
    }
    return;
}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
    int vertexId, const Color& color,
    int maxDepth, FilterType type,
    double alpha) const
{
    // TODO:
    if (vertexId < 0 || vertexId > vertices.size() - 1 || maxDepth < 0)
    {
        return;
    }
    std::vector<bool> visited(vertices.size(), false);
    outputColorAllVertex.resize(vertices.size());
    for (int i = 0; i < outputColorAllVertex.size(); i++)
    {
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }
    // Step 1: Put vertexId to the priority queue
    // Step 2: popHeap, then add adjacent vertices (be careful, smaller id should be put first)
    BinaryHeap pq;
    int dummy_weight = 0;
    std::vector<double> distance(vertices.size(), 0);
    pq.Add(vertexId, dummy_weight++);
    visited[vertexId] = true;

    outputColorAllVertex[vertexId].r = color.r;
    outputColorAllVertex[vertexId].g = color.g;
    outputColorAllVertex[vertexId].b = color.b;

    while (!pq.isEmpty() && maxDepth > 0)
    {

        int size = pq.HeapSize();

        // SORTING BELOW
        for (int i = 0; i < size; i++)
        {
            int uniqueId;
            double weight;
            pq.PopHeap(uniqueId, weight);
            for (std::list<Vertex*>::const_iterator left = adjList[uniqueId].begin(); left != adjList[uniqueId].end(); left++)
            {
                Vertex* v_left = *left;
                for (std::list<Vertex*>::const_iterator right = left; right != adjList[uniqueId].end(); right++)
                {
                    Vertex* v_right = *right;
                    if (v_right->id < v_left->id)
                    {
                        Vertex* tmp = v_right;
                        v_right = v_left;
                        v_left = tmp;
                    }
                }
            }
            // SORTING ABOVE

           
            // ADDING ADJACENT VERTICES BELOW
            for (std::list<Vertex*>::const_iterator it = adjList[uniqueId].begin(); it != adjList[uniqueId].end(); it++)
            {
                double curr_weight = distance[uniqueId] + vertices[uniqueId].position3D.Distance(vertices[uniqueId].position3D, (*it)->position3D);

                if (!visited[(*it)->id])
                {
                    if (type == FILTER_GAUSSIAN)
                    {
                        double x = curr_weight * curr_weight;
                        double a = alpha * alpha;
                        Double3 tmp;
                        tmp.x = color.r * exp(-x / a);
                        tmp.y = color.g * exp(-x / a);
                        tmp.z = color.b * exp(-x / a);
                        outputColorAllVertex[(*it)->id].r = (unsigned char)floor(tmp.x);
                        outputColorAllVertex[(*it)->id].g = (unsigned char)floor(tmp.y);
                        outputColorAllVertex[(*it)->id].b = (unsigned char)floor(tmp.z);
                    }
                    else if (type == FILTER_BOX)
                    {
                        if (curr_weight <= alpha && -alpha <= curr_weight)
                        {
                            outputColorAllVertex[(*it)->id] = color;
                        }
                    }
                    pq.Add((*it)->id, dummy_weight++);
                    visited[(*it)->id] = true;
                    distance[(*it)->id] = curr_weight;
                }

            }
        }
        maxDepth--;
        // ADDING ADJACENT VERTICES ABOVE
    }
    return;
}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
    int vertexId, const Color& color,
    int maxDepth, FilterType type,
    double alpha) const
{
    // TODO:
    if (vertexId < 0 || vertexId > vertices.size() - 1 || maxDepth < 0)
    {
        return;
    }
    std::vector<bool> visited(vertices.size(), false);
    outputColorAllVertex.resize(vertices.size());
    for (int i = 0; i < outputColorAllVertex.size(); i++)
    {
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }
    // Step 1: Put vertexId to the priority queue
    // Step 2: popHeap, then add adjacent vertices (be careful, smaller id should be put first)
    BinaryHeap pq;
    int dummy_weight = 0;
    pq.Add(vertexId, dummy_weight++);
    visited[vertexId] = true;

    outputColorAllVertex[vertexId].r = color.r;
    outputColorAllVertex[vertexId].g = color.g;
    outputColorAllVertex[vertexId].b = color.b;

    while (!pq.isEmpty() && maxDepth > 0)
    {

        int size = pq.HeapSize();

        // SORTING BELOW
        for (int i = 0; i < size; i++)
        {
            int uniqueId;
            double weight;
            pq.PopHeap(uniqueId, weight);
            for (std::list<Vertex*>::const_iterator left = adjList[uniqueId].begin(); left != adjList[uniqueId].end(); left++)
            {
                Vertex* v_left = *left;
                for (std::list<Vertex*>::const_iterator right = left; right != adjList[uniqueId].end(); right++)
                {
                    Vertex* v_right = *right;
                    if (v_right->id < v_left->id)
                    {
                        Vertex* tmp = v_right;
                        v_right = v_left;
                        v_left = tmp;
                    }
                }
            }
            // SORTING ABOVE


            // ADDING ADJACENT VERTICES BELOW
            for (std::list<Vertex*>::const_iterator it = adjList[uniqueId].begin(); it != adjList[uniqueId].end(); it++)
            {
                double curr_weight = vertices[vertexId].position3D.Distance(vertices[vertexId].position3D, (*it)->position3D);

                if (!visited[(*it)->id])
                {
                    if (type == FILTER_GAUSSIAN)
                    {
                        double x = curr_weight * curr_weight;
                        double a = alpha * alpha;
                        Double3 tmp;
                        tmp.x = color.r * exp(-x / a);
                        tmp.y = color.g * exp(-x / a);
                        tmp.z = color.b * exp(-x / a);
                        outputColorAllVertex[(*it)->id].r = (unsigned char)floor(tmp.x);
                        outputColorAllVertex[(*it)->id].g = (unsigned char)floor(tmp.y);
                        outputColorAllVertex[(*it)->id].b = (unsigned char)floor(tmp.z);
                    }
                    else if (type == FILTER_BOX)
                    {
                        if (curr_weight <= alpha && -alpha <= curr_weight)
                        {
                            outputColorAllVertex[(*it)->id] = color;
                        }
                    }
                    pq.Add((*it)->id, dummy_weight++);
                    visited[(*it)->id] = true;
                }

            }
        }
        maxDepth--;
        // ADDING ADJACENT VERTICES ABOVE
    }
    return;
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
    const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for (int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for (int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
            << static_cast<int>(colors[i].g) << ", "
            << static_cast<int>(colors[i].b) << "\n";
    }
}
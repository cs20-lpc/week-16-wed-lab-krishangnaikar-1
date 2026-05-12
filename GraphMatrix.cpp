#include "GraphMatrix.hpp"

GraphMatrix::GraphMatrix(int numV, GType type)
    : Graph(numV, 0, type) {
    // Allocate 2D adjacency matrix and initialize all entries to false
    adjMatrix = new bool*[numV];
    for (int i = 0; i < numV; i++) {
        adjMatrix[i] = new bool[numV];
        for (int j = 0; j < numV; j++) {
            adjMatrix[i][j] = false;
        }
    }
}

GraphMatrix::~GraphMatrix() {
    // Release each row, then the array of row pointers
    for (int i = 0; i < v; i++) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

bool GraphMatrix::isEdge(int i, int j) const {
    // Validate vertex indices
    if (i < 0 || i >= v || j < 0 || j >= v) {
        return false;
    }
    return adjMatrix[i][j];
}

ostream& GraphMatrix::print(ostream& os) const {
    os << "    ";
    for (int i = 0; i < v; i++) {
        os << i << ' ';
    }
    os << endl;

    os << "---";
    for (int i = 0; i < v; i++) {
        os << "--";
    }
    os << endl;

    for (int i = 0; i < v; i++) {
        os << i << " | ";
        for (int j = 0; j < v; j++) {
            os << adjMatrix[i][j] << ' ';
        }
        os << endl;
    }

    return os;
}

void GraphMatrix::toggleEdge(int i, int j) {
    // Validate vertex indices
    if (i < 0 || i >= v || j < 0 || j >= v) {
        return;
    }

    if (graphType == UNDIRECTED) {
        // Toggle both directions symmetrically
        adjMatrix[i][j] = !adjMatrix[i][j];
        adjMatrix[j][i] =  adjMatrix[i][j];
        e += adjMatrix[i][j] ? 1 : -1;
    }
    else {
        // Directed: toggle only the i→j direction
        adjMatrix[i][j] = !adjMatrix[i][j];
        e += adjMatrix[i][j] ? 1 : -1;
    }
}

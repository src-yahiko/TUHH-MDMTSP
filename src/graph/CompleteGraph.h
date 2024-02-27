#ifndef COMPLETEGRAPH_H
#define COMPLETEGRAPH_H

#include <iostream>
#include <vector>
#include <random>
#include <utility>
#include <cmath>

class CompleteGraph
{
private:
    int numVertices;
    std::vector<std::vector<double>> adjacencyMatrix;

public:
    CompleteGraph(int n) : numVertices(n), adjacencyMatrix(n, std::vector<double>(n, 1.0))
    {
        for (int i = 0; i < numVertices; ++i)
            adjacencyMatrix[i][i] = 0.0;
    }

    CompleteGraph(const std::vector<std::vector<double>>& matrix) : numVertices(matrix.size()), adjacencyMatrix(matrix) {};

    void printMatrix() const
    {
        for (int i = 0; i < numVertices; ++i)
        {
            for (int j = 0; j < numVertices; ++j)
                std::cout << adjacencyMatrix[i][j] << " ";
            std::cout << std::endl;
        }
    }

    static std::vector<std::pair<double, double>> getRandomCoordinates(int n)
    {
        std::vector<std::pair<double, double>> coordinates;
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        for (int i = 0; i < n; ++i)
            coordinates.emplace_back(dis(gen), dis(gen));

        return coordinates;
    }

    static std::vector<std::vector<double>> adjacencyMatrixFromCoordinates(const std::vector<std::pair<double, double>> &coordinates)
    {
        int n = coordinates.size();
        std::vector<std::vector<double>> matrix(n, std::vector<double>(n, 0.0));

        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            { 
                double dx = coordinates[i].first - coordinates[j].first;
                double dy = coordinates[i].second - coordinates[j].second;
                double distance = std::sqrt(dx * dx + dy * dy);

                matrix[i][j] = distance;
                matrix[j][i] = distance;
            }
        }
        return matrix;
    }

    static void printCoordinates(const std::vector<std::pair<double, double>>& coordinates) {
        std::cout << "#MAP#" << coordinates.size();
        for (const auto& coord : coordinates) {
            std::cout << " " << coord.first << " " << coord.second;
        }
    }
};

#endif // COMPLETEGRAPH_H

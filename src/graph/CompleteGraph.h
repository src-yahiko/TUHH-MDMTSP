// #ifndef COMPLETEGRAPH_H
// #define COMPLETEGRAPH_H

// #include <iostream>
// #include <vector>
// #include <random>
// #include <utility>
// #include <cmath>
// #include <sstream>

// class CompleteGraph
// {
// private:
//     int numVertices;
//     std::vector<std::vector<double>> adjacencyMatrix;

// public:
//     CompleteGraph(int n) : numVertices(n), adjacencyMatrix(n, std::vector<double>(n, 1.0))
//     {
//         for (int i = 0; i < numVertices; ++i)
//             adjacencyMatrix[i][i] = 0.0;
//     }

//     CompleteGraph(const std::vector<std::vector<double>> &matrix) : numVertices(matrix.size()), adjacencyMatrix(matrix){};

//     void printMatrix() const
//     {
//         for (int i = 0; i < numVertices; ++i)
//         {
//             for (int j = 0; j < numVertices; ++j)
//                 std::cout << adjacencyMatrix[i][j] << " ";
//             std::cout << std::endl;
//         }
//     }

//     static std::vector<std::pair<double, double>> getRandomCoordinates(int n)
//     {
//         std::vector<std::pair<double, double>> coordinates;
//         static std::random_device rd;
//         static std::mt19937 gen(rd());
//         std::uniform_real_distribution<double> dis(0.0, 1.0);

//         for (int i = 0; i < n; ++i)
//             coordinates.emplace_back(dis(gen), dis(gen));

//         return coordinates;
//     }

//     static std::vector<std::vector<double>> adjacencyMatrixFromCoordinates(const std::vector<std::pair<double, double>> &coordinates)
//     {
//         int n = coordinates.size();
//         std::vector<std::vector<double>> matrix(n, std::vector<double>(n, 0.0));

//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = i + 1; j < n; ++j)
//             {
//                 double dx = coordinates[i].first - coordinates[j].first;
//                 double dy = coordinates[i].second - coordinates[j].second;
//                 double distance = std::sqrt(dx * dx + dy * dy);

//                 matrix[i][j] = distance;
//                 matrix[j][i] = distance;
//             }
//         }
//         return matrix;
//     }

//     static void printCoordinates(const std::vector<std::pair<double, double>> &coordinates)
//     {
//         std::cout << "#MAP#" << coordinates.size();
//         for (const auto &coord : coordinates)
//         {
//             std::cout << "_" << coord.first << "_" << coord.second;
//         }
//     }

//     static std::vector<std::pair<double, double>> parseCoordinates(const std::string &input)
//     {
//         std::vector<std::pair<double, double>> coordinates;
//         std::istringstream stream(input);
//         std::string token;
//         std::vector<std::string> tokens;
//         while (std::getline(stream, token, '_'))
//         {
//             tokens.push_back(token);
//         }

//         size_t numCoordinates;
//         std::istringstream(tokens[0]) >> numCoordinates;

//         if (tokens.size() != 1 + (numCoordinates * 2))
//         {
//             std::cerr << "Invalid input format." << std::endl;
//             return coordinates;
//         }

//         double x, y;
//         for (size_t i = 1; i < tokens.size(); i += 2)
//         {
//             std::istringstream(tokens[i]) >> x;
//             std::istringstream(tokens[i + 1]) >> y;
//             coordinates.emplace_back(x, y);
//         }

//         return coordinates;
//     }
// };

// #endif // COMPLETEGRAPH_H

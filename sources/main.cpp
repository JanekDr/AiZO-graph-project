#include <iostream>
#include "file_handler.hpp"
#include "Timer.h"
#include "structures/graph.hpp"
#include "structures/graph_adjacency_matrix.hpp"
#include "structures/dynamic_array.hpp"
#include "structures/graph_incidence_matrix.hpp"
#include "algorithms/prim.hpp"
#include "algorithms/prim_matrix.hpp"
#include "algorithms/prim_incidence_matrix.hpp"
#include "algorithms/kruskal.hpp"
#include "algorithms/kruskal_matrix.hpp"
#include "algorithms/kruskal_incidence_matrix.hpp"
#include "algorithms/dijkstra.hpp"
#include "algorithms/dijkstra_incidence_matrix.hpp"
#include "algorithms/bellman_ford.hpp"
#include "algorithms/bellman_ford_incidence_matrix.hpp"
#include "graph_generator.hpp"

using namespace std;

bool parseToInt(string str, int& value){
    try {
        value = stoi(str);
        return true;
    } catch (invalid_argument& e) {
        return false;
    }
}

bool parseToDouble(string str, double& value){
    try {
        value = stod(str);
        return true;
    } catch (invalid_argument& e) {
        return false;
    }
}

void printHelp() {
    cout << "FILE TEST MODE:\n"
         << "Usage:\n"
         << "./YourProject --file <problem> <algorithm> <data structure> <inputFile> [outputFile] [start] [end]\n"
         << "<problem>     Problem to solve (0 - MST, 1 - shortest path)\n"
         << "<algorithm>   Algorithm (MST[0 - Prim, 1 - Kruskal], Shortest path[0 - Dijkstra, 1 - Bellman-Ford])\n"
         << "<data structure> Data structure (0 - adjacency list, 1 - incidence matrix, 2 - adjacency matrix (only available for MST problem))\n"
         << "<inputFile>   File containing the graph\n"
         << "[outputFile]  Optional file to store the solution\n\n"
         << "[start]      Optional start vertex for shortest path algorithms (default: 0)\n"
         << "[end]        Optional end vertex for shortest path algorithms (default: -1, meaning last vertex)\n\n"

         << "BENCHMARK MODE:\n"
         << "Usage:\n"
         << "./YourProject --test <problem> <algorithm> <data structure> <size> <density> <outputFile> [start] [end]\n"
         << "<problem>     Problem to solve (0 - MST, 1 - shortest path)\n"
         << "<algorithm>   Algorithm (MST[0 - Prim, 1 - Kruskal], Shortest path[0 - Dijkstra, 1 - Bellman-Ford])\n"
         << "<data structure> Data structure (0 - adjacency list, 1 - incidence matrix, 2 - adjacency matrix (only available for MST problem))\n"
         << "<size>        Number of nodes\n"
         << "<density>     Density of edges (0.0 - 1.0)\n"
         << "<outputFile>  File to store benchmark times\n\n"
         << "[start]      Optional start vertex for shortest path algorithms (default: 0)\n"
         << "[end]        Optional end vertex for shortest path algorithms (default: -1, meaning last vertex)\n\n"

         <<"WARNING:\n"
         <<"If you provide only one element of start or end, it will be interpreted as start.\n\n"

         << "HELP MODE:\n"
         << "Usage:\n"
         << "./YourProject --help\n"
         << "Displays this help message.\n\n";
}

void processFileMode(int problem, int algorithm, int dataStructure, const string& inputFile, const string& outputFile, int start = 0, int end = -1) {
    FileHandler fileHandler(inputFile);
    Timer timer;

    Graph* graph;
    Graph* resultList = nullptr;

    GraphAdjacencyMatrix* graphMatrix;
    GraphAdjacencyMatrix* resultMatrix = nullptr;

    GraphIncidenceMatrix* graphIncidence;
    GraphIncidenceMatrix* resultIncidence = nullptr;

    int shortestPathCost;

    if (problem == 0){
        if (algorithm == 0){
            if (dataStructure == 0){
                graph = fileHandler.getGraphListFromFile();
                graph->printAdjacencyList();

                timer.start();
                Prim prim;
                resultList = prim.run(graph);
                timer.stop();

            } else if (dataStructure == 1) {
                graphIncidence = fileHandler.getGraphIncidenceMatrixFromFile();
                graphIncidence->printIncidenceMatrix();

                timer.start();
                PrimIncidenceMatrix primMatrix;
                resultIncidence = primMatrix.run(graphIncidence);
                timer.stop();

            } else if (dataStructure == 2) {
                GraphAdjacencyMatrix* graphMatrix = fileHandler.getGraphMatrixFromFile();
                graphMatrix->printAdjacencyMatrix();

                timer.start();
                PrimMatrix primMatrix;
                GraphAdjacencyMatrix* resultMatrix = primMatrix.run(graphMatrix);
                timer.stop();

            } else {
                cerr << "Error: Invalid data structure for MST problem.\n";
                return;
            }
        } else if (algorithm == 1) {
            if (dataStructure == 0) {
                graph = fileHandler.getGraphListFromFile();
                graph->printAdjacencyList();

                timer.start();
                Kruskal kruskal;
                resultList = kruskal.run(graph);
                timer.stop();

            } else if (dataStructure == 1) {
                graphIncidence = fileHandler.getGraphIncidenceMatrixFromFile();
                graphIncidence->printIncidenceMatrix();

                timer.start();
                KruskalIncidenceMatrix kruskalIncidence;
                resultIncidence = kruskalIncidence.run(graphIncidence);
                timer.stop();

            } else if (dataStructure == 2) {
                graphMatrix = fileHandler.getGraphMatrixFromFile();
                graphMatrix->printAdjacencyMatrix();

                timer.start();
                KruskalMatrix kruskalMatrix;
                resultMatrix = kruskalMatrix.run(graphMatrix);
                timer.stop();

            } else {
                cerr << "Error: Invalid data structure for MST problem.\n";
                return;
            }
        } else {
            cerr << "Error: Invalid algorithm for MST problem.\n";
            return;
        }
    } else if (problem == 1){
        if (algorithm == 0) {
            if (dataStructure == 0) {
                graph = fileHandler.getGraphListFromFile(true);
                graph->printAdjacencyList();

                timer.start();
                Dijkstra dijkstra;
                resultList = dijkstra.run(graph, start);
                shortestPathCost = dijkstra.getShortestDistance(start, end);
                timer.stop();

            } else if (dataStructure == 1) {
                graphIncidence = fileHandler.getGraphIncidenceMatrixFromFile(true);
                graphIncidence->printIncidenceMatrix();

                timer.start();
                DijkstraIncidenceMatrix dijkstraIncidence;
                resultIncidence = dijkstraIncidence.run(graphIncidence, start);
                shortestPathCost = dijkstraIncidence.getShortestDistance(start, end);
                timer.stop();

            } else {
                cerr << "Error: Invalid data structure for shortest path problem.\n";
                return;
            }
        } else if (algorithm == 1) {
            if (dataStructure == 0) {
                graph = fileHandler.getGraphListFromFile(true);
                graph->printAdjacencyList();

                timer.start();
                BellmanFord bellmanFord;
                resultList = bellmanFord.run(graph, start);
                shortestPathCost = bellmanFord.getShortestDistance(end);
                timer.stop();

            } else if (dataStructure == 1) {
                graphIncidence = fileHandler.getGraphIncidenceMatrixFromFile(true);
                graphIncidence->printIncidenceMatrix();

                timer.start();
                BellmanFordIncidenceMatrix bellmanFordIncidence;
                resultIncidence = bellmanFordIncidence.run(graphIncidence, start);
                shortestPathCost = bellmanFordIncidence.getShortestDistance(end);
                timer.stop();

            } else {
                cerr << "Error: Invalid data structure for shortest path problem.\n";
                return;
            }
        } else {
            cerr << "Error: Invalid algorithm for shortest path problem.\n";
            return;
        }
    } else {
        cerr << "Error: Invalid problem type. Use 0 for MST or 1 for shortest path.\n";
        return;
    }

    ofstream out(outputFile);
    if (out.is_open()) {
        if (problem == 0){
           if (resultList != nullptr){
                out << "MST using adjacency list:\n";
                out << "Original graph:\n";
                out << graphIncidence << endl;
                out << "MST:" <<endl;
                out << resultList << endl;
                out << "Time: " << timer.result() << " ms\n";
            } else if (resultIncidence != nullptr) {
                out << "MST using incidence matrix:\n";
                out << "Original graph:\n";
                out << graphIncidence << endl;
                out << "MST:" <<endl;
                out << resultIncidence << endl;
                out << "Time: " << timer.result() << " ms\n";
            } else {
                out << "MST using adjacency matrix:\n";
                out << "Original graph:\n";
                out << graphMatrix << endl;
                out << "MST:" <<endl;
                out << resultMatrix << endl;
                out << "Time: " << timer.result() << " ms\n";
            } 
        } else {
            if (resultList != nullptr) {
                out << "Shortest path using adjacency list:\n";
                out << "Original graph:\n";
                out << graph << endl;
                out << "Shortest path from " << start << " to " << end << ":\n";
                out << resultList << endl;
                out << "Shortest path cost from " << start << " to " << end << ": " << shortestPathCost << endl;
                out << "Time: " << timer.result() << " ms\n";
            } else if (resultIncidence != nullptr) {
                out << "Shortest path using incidence matrix:\n";
                out << "Original graph:\n";
                out << graphIncidence << endl;
                out << "Shortest path from " << start << " to " << end << ":\n";
                out << resultIncidence << endl;
                out << "Shortest path cost from " << start << " to " << end << ": " << shortestPathCost << endl;
                out << "Time: " << timer.result() << " ms\n";
            } else {
                cerr << "Error: No results to write to output file.\n";
            }
        }
    } else {
        cerr << "Error: Cannot open output file " << outputFile << endl;
    }
    delete graph;
    delete graphMatrix;
    delete graphIncidence;
    delete resultList;
    delete resultMatrix;
    delete resultIncidence;
    out.close();
}

void processTestMode(int problem, int algorithm, int dataStructure, int size, double density, const string& outputFile, int start = 0, int end = -1) {
    Timer timer;
    ofstream out(outputFile);
    if (!out.is_open()) {
        cerr << "Error: Cannot open output file " << outputFile << endl;
        return;
    }

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 0;
    }
    cout << argc << endl;
    string mode = argv[1];
    int problem, algorithm, dataStructure, start = 0, end = -1;

    if (mode == "--file") {
        if (argc < 5) {
            cerr << "Error: Not enough arguments for file mode.\n";
            printHelp();
            return 1;
        }
    
        string outputFile = "";
        parseToInt(argv[2], problem);
        parseToInt(argv[3], algorithm);
        parseToInt(argv[4], dataStructure);
        string inputFile = argv[5];

        if (dataStructure == 2 && problem != 0) {
            cerr << "Error: Adjacency matrix is only available for MST problem.\n";
            printHelp();
            return 1;
        }

        if (argc >= 9){ //wszystkie argumenty podane
            outputFile = argv[6];
            parseToInt(argv[7], start);
            parseToInt(argv[8], end);
        } else if (argc == 8) { // outputFile + start / start + end
            if (!parseToInt(argv[6], start)) {
                outputFile = argv[6];
                parseToInt(argv[7], start);
            } else {
                parseToInt(argv[6], end);
            }
        } else {
            if (!parseToInt(argv[6], start)) outputFile = argv[6];    
        }    
       
        processFileMode(problem, algorithm, dataStructure,inputFile, outputFile, start, end);

    } else if (mode == "--test") {
        if (argc < 7) {
            cerr << "Error: Not enough arguments for test mode.\n";
            printHelp();
            return 1;
        }

        int size;
        double density;

        parseToInt(argv[2], problem);
        parseToInt(argv[3], algorithm);
        parseToInt(argv[4], dataStructure);
        parseToInt(argv[5], size);
        parseToDouble(argv[6], density);   
        string outputFile = argv[7];

        if (dataStructure == 2 && problem != 0) {
            cerr << "Error: Adjacency matrix is only available for MST problem.\n";
            printHelp();
            return 1;
        }

        if (argc == 9) {
            parseToInt(argv[8], start);
            parseToInt(argv[9], end);
        } else if (argc == 8) {
            parseToInt(argv[8], start);
        }

        processTestMode(problem, algorithm, dataStructure, size, density, outputFile, start, end);
    } else {
        cerr << "Error: Unknown mode. Use --file, --test or --help.\n";
        printHelp();
        return 1;
    }

    return 0;
}
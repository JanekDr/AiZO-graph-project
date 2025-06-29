import subprocess
import csv
from datetime import datetime

sizes = ['50','150', '300', '450', '600', '750', '900']
densities = [0.25, 0.5, 0.99]

def badanieMST():
    # int problem, int algorithm, int dataStructure, int size, float density, const string& outputFile, int start = 0, int end = -1
    output_file = open("results/badanieMSTwyniki.csv", mode="w", newline="")
    writer = csv.writer(output_file, delimiter=";")
    writer.writerow(["problem", "algorithm", "data_structure", "size", "density", "time_ms", "timestamp"])
    # timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    for algorithm in range(2):
        for size in sizes:
            for density in densities:
                for data_structure in range(3):
                    for j in range(50):
                        subprocess.run(["../sources/main.exe", "--test", "0", str(algorithm), str(data_structure), size, str(density), "../data/execution_time.txt"], capture_output=True, text=True)
                        with open("../data/execution_time.txt", "r") as file:
                            time = file.readline().strip()
                            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                            writer.writerow([0, algorithm, data_structure, size, density, time, timestamp])
    output_file.close()

def badanieMST_reszta():
    # int problem, int algorithm, int dataStructure, int size, float density, const string& outputFile, int start = 0, int end = -1
    output_file = open("results/badanieMSTwyniki-0-1-2-750-099.csv", mode="w", newline="")
    writer = csv.writer(output_file, delimiter=";")
    writer.writerow(["problem", "algorithm", "data_structure", "size", "density", "time_ms", "timestamp"])
    # timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    # 0;1;2;750;0.99;110977;2025-06-27 21:58:48
    # 0;1;2;750;0.99;116039;2025-06-27 22:00:46
    for j in range(48):
        subprocess.run(["../sources/main.exe", "--test", "0", "1", "2", "750", "0.99", "../data/execution_time.txt"], capture_output=True, text=True)
        with open("../data/execution_time.txt", "r") as file:
            time = file.readline().strip()
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            writer.writerow([0, 1, 2, 750, 0.99, time, timestamp])
    output_file.close()

def badanieMST_reszta2():
    # int problem, int algorithm, int dataStructure, int size, float density, const string& outputFile, int start = 0, int end = -1
    output_file = open("results/badanieMSTwyniki-0-1-2-750-099+.csv", mode="w", newline="")
    writer = csv.writer(output_file, delimiter=";")
    writer.writerow(["problem", "algorithm", "data_structure", "size", "density", "time_ms", "timestamp"])
    
    rest_sizes = ['900', '1100']
    for size in rest_sizes:
        for density in densities:
            for data_structure in range(3):
                for j in range(50):
                    subprocess.run(["../sources/main.exe", "--test", "0", "1", str(data_structure), size, str(density), "../data/execution_time.txt"], capture_output=True, text=True)
                    with open("../data/execution_time.txt", "r") as file:
                        time = file.readline().strip()
                        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                        writer.writerow([0, 1, data_structure, size, density, time, timestamp])
    output_file.close()

def badanieShortestPath():
    # int problem, int algorithm, int dataStructure, int size, float density, const string& outputFile, int start = 0, int end = -1
    output_file = open("results/badanieSPwyniki.csv", mode="w", newline="")
    writer = csv.writer(output_file, delimiter=";")
    writer.writerow(["problem", "algorithm", "data_structure", "size", "density","start", "end", "time_ms", "timestamp"])
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    for algorithm in range(2):
        for size in sizes:
            for density in densities:
                for data_structure in range(2):
                    for j in range(50):
                        subprocess.run(["../sources/main.exe", "--test", "1", str(algorithm), str(data_structure), size, str(density), "../data/execution_time.txt"], capture_output=True, text=True)
                        with open("../data/execution_time.txt", "r") as file:
                            time = file.readline().strip()
                            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                            writer.writerow([1, algorithm, data_structure, size, density, 0, -1, time, timestamp])
    output_file.close()
    
def badanieMST_size50():
    output_file = open("results/badanieMSTwynikiSize50.csv", mode="w", newline="")
    writer = csv.writer(output_file, delimiter=";")
    writer.writerow(["problem", "algorithm", "data_structure", "size", "density", "time_ms", "timestamp"])
    # timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    for algorithm in range(2):
        for density in densities:
            for data_structure in range(3):
                for j in range(50):
                    subprocess.run(["../sources/main.exe", "--test", "0", str(algorithm), str(data_structure), "50", str(density), "../data/execution_time.txt"], capture_output=True, text=True)
                    with open("../data/execution_time.txt", "r") as file:
                        time = file.readline().strip()
                        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                        writer.writerow([0, algorithm, data_structure, 50, density, time, timestamp])
    output_file.close()

# badanieMST()
# badanieMST_reszta()
# badanieMST_reszta2()
badanieShortestPath()
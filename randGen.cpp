#include <iostream>
#include <set>
#include <random>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

void vecGen(string filename, vector<int> & v){
    ifstream file(filename);
    int num;
    v.clear();
    while (file.is_open() && file >> num){
        v.push_back(num);
    }
    file.close();
}

int main() {
    vector<int> file_sizes;
    vecGen("sizes.csv", file_sizes);
    for (int i = 0 ; i < file_sizes.size(); i++) {
    int N = file_sizes[i]; //ten million Total number of unique numbers to generate
    std::set<double> numbers;

    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    int range = 100000000;//hundred million
    std::uniform_int_distribution<> dis(1, range); // Adjust the range as needed

    // Generate unique random numbers
    while (numbers.size() < N) {
        numbers.insert(dis(gen));
    }

    // Open the file for writing
    std::string fname =  std::to_string(N) + ".csv";
    std::ofstream writeFile(fname);
    if (!writeFile.is_open()) {
        std::cerr << "Unable to open file for writing." << std::endl;
        return 1; // Return an error code
    }

    // Write the numbers to the file in ascending order
    for (int num : numbers) {
        writeFile << num << "\n";
    }

    // Close the file
    writeFile.close();

    std::cout << "Numbers written to numbers.txt successfully." << std::endl;
    }
    return 0;
}
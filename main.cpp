#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a struct to represent each row in the CSV file
struct TrendData {
    string date;
    int count;
};

// Define a function to read data from CSV file and store it in a vector of TrendData objects
vector<TrendData> readDataFromFile(string filename) {
    vector<TrendData> data;
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return data;
    }
    // skip the first line (header) in the file
    string line;
    getline(inputFile, line);
    while (getline(inputFile, line)) {
        // split the line by comma
        size_t pos = line.find(',');
        string date = line.substr(0, pos);
        int count = stoi(line.substr(pos + 1));
        data.push_back({date, count});
    }
    inputFile.close();
    return data;
}

// Define a function to write data from a vector of TrendData objects to a CSV file
void writeDataToFile(string filename, vector<TrendData> data) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return;
    }
    // write the header line
    outputFile << "Date,Count" << endl;
    // write each row to the file
    for (auto row : data) {
        outputFile << row.date << "," << row.count << endl;
    }
    outputFile.close();
}

// Define a comparison function to sort TrendData objects by count in descending order
bool compareTrendData(TrendData a, TrendData b) {
    return a.count > b.count;
}

int main() {
    // read data from the input file and store it in a vector of TrendData objects
    vector<TrendData> data = readDataFromFile("multiTimeline.csv");
    if (data.empty()) {
        return 1;
    }
    // sort the data by count in descending order
    sort(data.begin(), data.end(), compareTrendData);
    // write the sorted data to the output file
    writeDataToFile("sortedTrends.csv", data);
    return 0;
}

#pragma once

/// <summary>
/// Create all the needed keys for both human and LLM results
/// </summary>
/// <param name="results">Either the human or LLM results</param>
void setUpResults(std::map<std::string, double>&);

/// <summary>
/// Store and calculate the results of all test from both human and LLM programmers
/// </summary>
/// <param name="start">What index of results to start at</param>
/// <param name="end">What is the last result to be measured</param>
/// <param name="measuredResults">All results catagories that will be calculate and stored</param>
/// <param name="tests">All test results</param>
void measureResults(size_t, const size_t, std::map<std::string, double>&, const std::map<std::string, Results*>&);

/// <summary>
/// Print all the results of both human and LLM's code
/// </summary>
/// <param name="results"></param>
void displayResults(std::map<std::string, double>&);

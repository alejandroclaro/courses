//
// tarea2-3.cpp : Problema 3 de la tarea 2 de teoria de algoritmos.
//

#include <cstdlib>
#include <fstream>
#include <vector>

#define N 12

                            // v1 v2 v3 v4 v5 v6 v7 v8 v9 v10 v11 v12
int adjacentTable[N][N]  = { { 1, 1, 0, 0, 0, 0, 0, 1, 1,  0,  0,  0 }, // v1
                             { 1, 1, 1, 0, 0, 0, 0, 0, 1,  1,  0,  0 }, // v2
                             { 0, 1, 1, 1, 0, 0, 0, 0, 0,  1,  0,  0 }, // v3
                             { 0, 0, 1, 1, 1, 0, 0, 0, 0,  1,  1,  0 }, // v4
                             { 0, 0, 0, 1, 1, 1, 0, 0, 0,  0,  1,  0 }, // v5
                             { 0, 0, 0, 0, 1, 1, 1, 0, 0,  0,  1,  1 }, // v6
                             { 0, 0, 0, 0, 0, 1, 1, 1, 0,  0,  0,  1 }, // v7
                             { 1, 0, 0, 0, 0, 0, 1, 1, 1,  0,  0,  1 }, // v8
                             { 1, 1, 0, 0, 0, 0, 0, 1, 1,  1,  0,  1 }, // v9
                             { 0, 1, 1, 1, 0, 0, 0, 0, 1,  1,  1,  0 }, // v10
                             { 0, 0, 0, 1, 1, 1, 0, 0, 0,  1,  1,  1 }, // v11
                             { 0, 0, 0, 0, 0, 1, 1, 1, 1,  0,  1,  1 }  // v12
                           };

int nStepCounter = 0;
std::ofstream output("output.txt", std::ios_base::out | std::ios_base::trunc);

void printSet(const std::vector<int>& set)
{
	output << "$\\{ ";
	for(size_t i = 0; i < set.size(); ++i)
	{
		output << "v_{" << set[i]+1 << "} ";

		if(i < set.size()-1)
			output << ",";
	}

	output << "\\}$";
}

std::vector<int> getSuccessors(const std::vector<int>& set)
{
	std::vector<int> ret;

	for(int i = set.empty() ? 0 : set.back(); i < N; ++i)
	{
		bool bConnected = false;

		for(size_t j = 0; j < set.size(); ++j)
		{
			if(adjacentTable[i][set[j]])
			{
				bConnected = true;
				break;
			}
		}

		if(!bConnected)
			ret.push_back(i);
	}

	return ret;
}

int computeBranchAndBound(std::vector<int>& set, std::vector<int>& bestSet)
{
	std::vector<int> successors = getSuccessors(set);

	output << ++nStepCounter << " & ";
	printSet(set);
	output << " & " << set.size() << " & ";
	printSet(successors);
	output << " & " << set.size() + successors.size() << " & ";
	//printSet(bestSet);
	//output << " & ";

	// paso bound
	if((set.size() + successors.size()) <= bestSet.size())
	{
		if(successors.empty())
			output <<  "No es mejor solución." << "\\\\ \n\\hline\n";
		else
			output <<  "Por esta ramificación no se encontrara una mejor solución." << "\\\\ \n\\hline\n";

		return -1;
	}

	if(set.size() >= bestSet.size() && !successors.empty())
	{
		bestSet = set;
		bestSet.push_back(successors[0]);

		output <<  "Esta es una mejor solución.";
	}

	output << "\\\\ \n\\hline\n";

	// paso branch
	for(size_t i = 0; i < successors.size(); ++i)
	{
		std::vector<int> nextSet(set);
		nextSet.push_back(successors[i]);

		computeBranchAndBound(nextSet, bestSet);
	}

	return 0;
}

int main(int argc, char* argv[])
{
	int nCardinality = 4;
	std::vector<int> x;
	std::vector<int> greedy(nCardinality);

	// solucion greedy
	greedy[0] = 0;
	greedy[1] = 2;
	greedy[2] = 4;
	greedy[3] = 6;

	computeBranchAndBound(x, greedy);

	getchar();
	return 0;
}


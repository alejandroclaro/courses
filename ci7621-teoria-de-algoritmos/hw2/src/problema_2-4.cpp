//
// tarea2-4.cpp : Problema 4 de la tarea 2 de teoria de algoritmos.
//

#include <fstream>
#include <vector>
#include <numeric>

struct vertex_t
{
	std::vector<int> A, A1, A2;
	int nDiff;
};

int nStepCounter = 0;
int nTotalSum    = 0;

std::ofstream output("output.txt", std::ios_base::out | std::ios_base::trunc);

void printSet(const std::vector<int>& set)
{
	output << "\\{";
	for(size_t i = 0; i < set.size(); ++i)
	{
		output << set[set.size() - i - 1];

		if(i < set.size()-1)
			output << ",";
	}

	output << "\\}";
}

void branchAndBound(const vertex_t& vertex, vertex_t& best)
{
	int nS1 = std::accumulate(vertex.A1.begin(), vertex.A1.end(), 0);
	int nS2 = std::accumulate(vertex.A2.begin(), vertex.A2.end(), 0);

	output << ++nStepCounter << " & ($"; printSet(vertex.A); output << ","; printSet(vertex.A1); output << ","; printSet(vertex.A2);
	output << "$) & " << nS1 << " & " << nS2 << " & " << 0.5*(nTotalSum + best.nDiff) << " & ";

	if(vertex.A.empty())
	{
		int nDiff = std::abs(nS1 - nS2);

		output << nDiff;

		if(nDiff < best.nDiff)
		{
			output << " & Mejor solución hasta el momento. \\\\ \n\\hline\n";

			best.A     = vertex.A;
			best.A1    = vertex.A1;
			best.A2    = vertex.A2;
			best.nDiff = nDiff;
		}
		else
		{
			output << " & No es una mejor solución.\\\\ \n\\hline\n";
		}

		return;
	}

	if((std::max)(nS1, nS2) >= 0.5*(nTotalSum + best.nDiff))
	{
		output << " & Por esta ramificación no se encontrará una mejor solución. \\\\ \n\\hline\n";
		return;
	}

	output << " & \\\\ \n\\hline\n";

	vertex_t left, right;
	int nX = vertex.A.back();

	left.A  = right.A  = vertex.A;
	left.A1 = right.A1 = vertex.A1;
	left.A2 = right.A2 = vertex.A2;

	left.A.pop_back();
	right.A.pop_back();

	left.A1.push_back(nX);
	right.A2.push_back(nX);

	branchAndBound(left, best);
	branchAndBound(right, best);

	return;
}

int main(int argc, char* argv[])
{
	vertex_t root, best;

	root.A.push_back(2);
	root.A.push_back(6);
	root.A.push_back(9);
	root.A.push_back(10);
	root.A.push_back(11);
	root.A.push_back(15);

	nTotalSum = std::accumulate(root.A.begin(), root.A.end(), 0);

	best.A1.push_back(2);
	best.A1.push_back(6);
	best.A1.push_back(9);
	best.A2.push_back(10);
	best.A2.push_back(11);
	best.A2.push_back(15);
	best.nDiff = abs(std::accumulate(best.A1.begin(), best.A1.end(), 0) - std::accumulate(best.A2.begin(), best.A2.end(), 0));

	branchAndBound(root, best);

	getchar();
	return 0;
}


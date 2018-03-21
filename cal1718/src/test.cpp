#include <iostream>

#include <boost/graph/adjacency_list.hpp>
using namespace boost;
using namespace std;
typedef property<edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<listS, vecS, directedS, no_property,
		EdgeWeightProperty > mygraph;
int main()
{
	mygraph g;
	add_edge (0, 1, 20, g);
	add_edge (0, 2, 10, g);
	add_edge (0, 3, 14, g);

	add_edge (1, 0, 20, g);
	add_edge (1, 2, 5, g);
	add_edge (1, 4, 5, g);

	add_edge (2, 0, 10, g);
	add_edge (2, 1, 5, g);
	add_edge (2, 3, 14, g);
	add_edge (2, 4, 5, g);
	add_edge (2, 7, 25, g);
	add_edge (2, 5, 20, g);

	add_edge (3, 0, 10, g);
	add_edge (3, 2, 14, g);
	add_edge (3, 5, 8, g);

	add_edge (4, 1, 4, g);
	add_edge (4, 2, 5, g);
	add_edge (4, 6, 8, g);

	add_edge (5, 3, 8, g);
	add_edge (5, 2, 20, g);
	add_edge (5, 7, 10, g);

	add_edge (6, 7, 8, g);

	add_edge (7, 2, 25, g);
	add_edge (7, 5, 10, g);
	add_edge (7, 6, 8, g);

}

/*mygraph g;
	add_edge (0, 1, g);
	add_edge (0, 3, g);
	add_edge (1, 2, g);
	add_edge (2, 3, g);
	mygraph::vertex_iterator vertexIt, vertexEnd;
	mygraph::adjacency_iterator neighbourIt, neighbourEnd;
	tie(vertexIt, vertexEnd) = vertices(g);
	for (; vertexIt != vertexEnd; ++vertexIt)
	{
		cout << *vertexIt << " is connected with ";
		tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, g);
		for (; neighbourIt != neighbourEnd; ++neighbourIt)
			cout << *neighbourIt << " ";
		cout << "\n";
	}*/

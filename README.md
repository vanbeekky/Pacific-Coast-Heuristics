How to Compile and Run (README)
To compile the project, use a C++17 compatible compiler. For example:
g++ -O2 main.cpp Graph.cpp -o shortestpath
This will produce an executable (named shortestpath in this case). The -O2 flag enables optimizations which we recommend for better performance, especially on large inputs.
Inputs: You will need the road network edge list file, and optionally the node coordinates file:
The edge list file (e.g., roadNet-CA.txt) can be downloaded from the SNAP dataset page. Ensure it’s uncompressed if it’s in .gz format.


The coordinate file (if using) should contain lines of the format: <node_id> <longitude> <latitude>. We used a provided dataset for coordinates of California’s road network. If you don’t have this file, you can still run the program by specifying none for the node file, in which case all edges will be weight 1 and A* will default to no heuristic (essentially performing the same as Dijkstra).


Running the program: There are two ways to provide file paths:
Command-line arguments: You can pass the edge file and node file paths as arguments. For example:

./shortestpath roadNet-CA.txt roadNet-CA.nodes
 If you don’t have a node coordinate file or do not want to use one, you can omit it or type none:

./shortestpath roadNet-CA.txt none
 This will load only the edges and treat all weights as equal (not recommended for actual distance queries, but fine for algorithm comparison purposes).


Interactive prompt: If you run the program without arguments, it will ask you to enter the file paths. First, it will prompt “Edge list file:” – enter the path to the edge list (or place the file in the same directory and just type its name). Then it will prompt “Node coordinate file (or 'none'):” – you can type the coordinate filename or type none if you don’t have one.


After loading the data, the program will inform you of the number of nodes loaded and whether coordinates were loaded. Then it enters the query loop.
Query format: When prompted “Enter start node and destination node (or -1 -1 to quit):”, input two integers:
The first is the starting intersection/node ID.


The second is the destination intersection/node ID. For example:


Enter start node and destination node (or -1 -1 to quit): 12345 67890

After pressing enter, the program will run Dijkstra and A* and print out something like:
Shortest distance:  XYZ.ZZZZZZ
Dijkstra: explored YYY nodes, time TTT.ms
A*: explored WWW nodes, time UUU.ms

Where XYZ.ZZZZZZ is the distance between node 12345 and 67890 (in whatever units the weights represent, likely Euclidean degree units or kilometers if the coords were in those units), YYY vs WWW is the number of nodes each algorithm expanded, and TTT vs UUU is the time each took in milliseconds.
You can perform multiple queries one after another. If you enter an invalid node ID (outside 0 to N-1 range), it will warn you and allow you to try again. To exit the query loop, type -1 -1 when asked for a query, or use Ctrl+D (EOF) to terminate.
Note on Node IDs: The node IDs in the SNAP dataset are numeric (0-based). If you want to lookup a specific location, you’d need to know its node ID. (Since this is a raw dataset, there are no readily human-meaningful IDs like place names – that mapping is outside our scope). For testing purposes, you might pick some random node IDs or use ones provided in example queries.
The program does not output the actual path (list of nodes) – it only outputs the distance and performance metrics. This was per requirements focusing on algorithm comparison. If needed, one could extend the code to record predecessors and reconstruct the path, but be mindful that the path could be very long to print for large distances.
Performance expectations: Loading the full California graph may take a bit of time (several seconds to tens of seconds) because it’s reading millions of lines. Once loaded, each query typically runs very fast (fractions of a second). A query across the entire network might take on the order of 1-2 seconds with Dijkstra, and much less with A*. Most local queries return almost instantaneously. The program prints metrics which you can use to verify performance or do your own analysis.


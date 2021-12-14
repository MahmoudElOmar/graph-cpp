# Graph Library in C++
A quick  off-the-shelf library for handling graphs under OOP paradigm.

It contains 2 classes, a Vertex class and a Graph class. Graph connectivity is handled through adjacency lists.  
It also contains a python script for visually representing the graph using force-directed drawing methods.  


It also implements traversing algorithms : Depth-first, breadth-first...    
The ```Vertex``` class has the following interesting API :

```isLinked(Vertex *v)``` returns a boolean describing wether or nor the current vertex to linked the vertex passed as argument.  
```linkVertex(Vertex *v)``` creates an edge between the calling vertex and tht vertex passed as argument.  
```SerializeToStringJSON()``` serializes the current state of the ```Vertex``` class instance into a string following the ```JSON``` format.  
```DeserializeFromStringJSON()``` restores the serialized object from a string following the ```JSON``` format.  



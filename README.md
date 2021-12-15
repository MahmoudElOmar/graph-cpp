# Graph Library in C++
A quick  off-the-shelf library for handling graphs under OOP paradigm.

It contains 2 classes, a Vertex class and a Graph class. Graph connectivity is handled through adjacency lists.  
It also contains a python script for visually representing the graph using force-directed drawing methods.  


It also implements traversing algorithms : Depth-first, breadth-first...    

## C++ API

The ```Vertex``` class has the following attributes and notable API :

```id``` : an integer representing an ID from the vertex. Each vertex must have a unique ID.   
```visited``` : a boolean representing whether this vertex has been visited during a graph search of not.
```adj```: an adjacency list containing the IDs of all the adjacent vertices.

```isLinked(Vertex *v)``` returns a boolean describing wether or nor the current vertex to linked the vertex passed as argument.  
```linkVertex(Vertex *v)``` creates an edge between the calling vertex and tht vertex passed as argument.  
```SerializeToStringJSON()``` serializes the current state of the ```Vertex``` class instance into a string following the ```JSON``` format.  
```DeserializeFromStringJSON()``` restores the serialized object from a string following the ```JSON``` format.  


the ```Graph``` class has similar attirbutes and functions: 
```vertices``` a list of ```Vertex``` instances describing the vertices belonging to the graph.

```addVertex()``` adds a vertex to the graph under the condition that it hasn't been added yet.  
```removeVertex()``` removes a vertex from the graph assuming that it already exists in the graph.  
```SerializeJSON(string filePath)``` serializes the state of this ```Graph``` instance into a JSON file at the location designated by ```filePath```.  
```DeserializeJSON(string filePath)``` restores the state of the ```Graph``` object from a JSON file at the location desginated by ```filePath```.  

All files must follow the ```JSON``` convention.
<br></br>
## Python scripts
The included python scripts are an implementation of drawing methods that allow to draw a graph serialized in a JSON file, most compatible with the serialization protocol implemented by the C++ API.  

The utilised drawing method is force-directed drawing.  



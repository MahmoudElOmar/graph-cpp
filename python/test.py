import graph
window = graph.Canvas()

vertex = graph.VisualVertex((100,70))

vertex1 = graph.VisualVertex((410,370),text="B")

vertex.draw(window)
vertex1.draw(window)

edge = graph.VisualEdge(vertex,vertex1)

edge.draw(window)

window.show()
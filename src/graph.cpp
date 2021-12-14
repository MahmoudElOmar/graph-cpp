#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Vertex
{
    public:
        Vertex(){}
        Vertex(int id)
        {
            this->id = id;
            this->visited = false;
        }
        Vertex(int id,bool visited)
        {
            this->id = id;
            this->visited = visited;
        }
        void markVisited()
        {
            this->visited = true;
        }
        void markUnvisited()
        {
            this->visited = false;
        }
        bool isVisited()
        {
            return this->visited;
        }
        bool isLinked(Vertex *v)
        {
            int i = 0;
            while (i<this->adj.size() && v->id != this->adj[i])
                i++;
            return i != this->adj.size();
        }
        bool linkVertex(Vertex *v)
        {
            if (!isLinked(v)) {
                this->adj.push_back(v->id);
                v->adj.push_back(this->id);
                return true;
            }
            else
                return false;
        }

        string SerializeToStringJSON()
        {
            stringstream ss;
            ss << "{\"id\":" << to_string(this->id) <<",\"adj\":[";
            for (int i = 0;i < this->adj.size();i++)
            {
                ss << to_string(this->adj[i]);
                if (i < this->adj.size() - 1)
                    ss << ",";
            }
            ss << "]}";
            return ss.str();
        }
        static Vertex DeserializeFromStringJSON(string data)
        {
            Vertex* v = new Vertex();
            int L = data.length();
            size_t index = data.find("id");
            index += 4;

            v->id = atoi((data.substr(index,1)).c_str());

            index = data.find("adj");
            index += 6;


            string adj = data.substr(index,L-2-index);

            int adj_id;
            while((index = adj.find(",")) != string::npos)
            {
                adj_id = atoi(adj.substr(0,index).c_str());
                v->adj.push_back(adj_id);
                adj.erase(0,index + 1);
            }
            adj_id = atoi(adj.c_str());
            v->adj.push_back(adj_id);

            return *v;
        }
        void PrintVertex()
        {
            stringstream ss;
            ss << "Vertex " << to_string(this->id) << " Linked to : ";
            for (int i=0;i<this->adj.size();i++)
            {
                ss << to_string(this->adj[i]);
                if (i < this->adj.size() - 1)
                    ss <<", ";
            }
            ss << endl;

            cout << ss.str();
        }
    // Vertex attributes
    public:
        int id;
        vector<int> adj;

    private:
        bool visited = false;
};

class Graph
{
    public:
        Graph() {}
        bool addVertex(Vertex *v)
        {
            if (!contains(v))
            {
                this->vertices.push_back(*v);
                return true;
            }
            else
            {
                cout << "Vertex Already Exists" << endl;
                return false;
            }
        }
        bool removeVertex(Vertex *v)
        {
            if(!contains(v))
            {
                cout << "Vertex does not exist to be removed" << endl;
                return false;
            }
            else
            {
                int i = index(v);
                auto it = this->vertices.begin();
                it += i;
                this->vertices.erase(it);
                return true;

            }
        }
        int index(Vertex *v)
        {
            int i = 0;

            if (!this->contains(v))
                return -1;
            else
            {
                while (i < this->vertices.size() && v->id != this->vertices[i].id)
                    i++;
                return i;
            }

        }
        bool contains(Vertex *v)
        {
            int i = 0;
            while (i < this->vertices.size() && v->id != this->vertices[i].id)
                i++;
            return i != this->vertices.size();
        }


        // serialization API
        void SerializeJSON(string filePath)
        {
            ofstream out;

            out.open(filePath);

            out << "[" << endl;

            for (int i=0;i<this->vertices.size();i++)
            {
                out << "\t"<< this->vertices[i].SerializeToStringJSON();
                if (i < this->vertices.size() - 1) {
                    out << ",";
                }
                out  << endl;
            }
            out << "]";
            out.close();
        }
        static Graph DerserializeJSON(string filePath)
        {

            Graph g = Graph();

            ifstream infile;
            string line;

            infile.open(filePath);

            while(getline(infile,line))
            {
                // if the line is a bracket
                if (line[1] == '{')
                {
                    if (line[line.length()-1] != '}')
                        line = line.substr(0,line.length()-1);
                    Vertex v = Vertex::DeserializeFromStringJSON(line);
                    g.addVertex(&v);
                }

            }
            infile.close();
            return g;
        }

    // properties
    public:
        vector<Vertex> vertices;

};


int main(int argc, char **argv)
{

    // example using the Vertex and Graph classes
    Vertex A = Vertex(0);
    Vertex B = Vertex(1);
    Vertex C = Vertex(2);
    Vertex D = Vertex(3);
    Vertex E = Vertex(4);



    A.linkVertex(&B);
    A.linkVertex(&E);

    B.linkVertex(&E);
    B.linkVertex(&D);
    B.linkVertex(&C);

    C.linkVertex(&D);

    D.linkVertex(&E);



    Graph g =  Graph();

    g.addVertex(&A);
    g.addVertex(&B);
    g.addVertex(&C);
    g.addVertex(&D);
    g.addVertex(&E);

    //cout << to_string(g.vertices.size()) << endl;
    g.SerializeJSON("graph.json");

    Graph g1 = Graph::DerserializeJSON("graph.json");

    int idx = 2;

    if(g1.contains(&g.vertices[idx]))
    {
        printf("Original graph member\n");
        g.vertices[idx].PrintVertex();

        printf("Deserialized Graph Member From File with same index\n");

        g1.vertices[idx].PrintVertex();
    }

    return 0;
}

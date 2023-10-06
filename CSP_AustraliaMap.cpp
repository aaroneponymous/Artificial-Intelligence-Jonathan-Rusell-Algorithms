#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>

// CSP: Constraint Satisfaction Problem: Region Colors for Australia's Map
// Australia has regions (state will be referred specifically in the context of state space search)
// Western Australia, Northern Territory, South Australia, Queensland, New South Wales, Victoria, and Tasmania
// Variables: {WA, NT, Q, NSW, V, SA, T}
// Domain: Each variable has the same set of values {red, green, blue}
// Problem:
// Assign a color to each region such that no two neighboring regions have the same color
// Return a list of first ordering/all the possible orderings

// Variation of the Problem:
// Undirected Graph given of regions with edges representing borders to other regions
// Get the adjacency and store valid constraints
// Then solve the problem


// Implementation:
// Using a state-space search algorithm DFS
// Specifically use Depth-Limited Search because the orderings will be at the depth n = no. of variables
// Method 1: Empty Assignment State has n * v children where v = value that n takes, will result in O(n!nxd)
// Inefficient because of commutative property of combinations: the combinations will repeat
// Method 2: Empty Assignment Stat has v state for any n, therefore O(nxd)

// Constraints
// Can be derived from the graph
// WA != NT, WA != SA
// NT != Q, NT != SA
// Q != SA
// NSW != V, NSW != SA, V != SA

// Enum Class for Color
enum class Colors {
    RED, GREEN, BLUE, UNASSIGNED
};

// Class for Nodes To Represent Vertices
class Node {
private:
    const std::string region;
    Colors color;
public:
    // Single-Argument Constructors Should be Marked Explicit to Avoid Implicit Conversions
    explicit Node(std::string region_name): region{std::move(region_name)}, color{Colors::UNASSIGNED} {}

    // Return Node Name
    std::string get_region_name() {
        return region;
    }

    // Color to_string
    std::string get_color_name() {
        if (color == Colors::RED) {
            return "Red";
        }
        else if (color == Colors::BLUE) {
            return "Blue";
        }
        else if (color == Colors::GREEN) {
            return "Green";
        }
        else {
            return "Not Assigned";
        }
    }

    // Set Color
    void set_region_color(Colors new_color) {
        color = new_color;
    }
};

// Class to Represent Edges/Graph
class Graph {
    std::unordered_map<std::string, std::list<Node*>> graph;
    int vertices;

public:
    // Constructor
    explicit Graph(int v): vertices{v} {}
    // Add Edge
    void add_edge(std::string vertex, Node* node) {
        // Should Implement Exception Handling
        if (node != nullptr) {
            graph[vertex].push_back(node);
        }
        else {
            graph[vertex] = std::list<Node*>();
        }

    }
    // Get Adjacency List
    std::list<Node*> get_adjacency_list(std::string &vertex) {
        // Should Implement Exception Handling
        return graph[vertex];
    }
    // Get Number of Vertices
    int get_vertices() const {
        return vertices;
    }
    // Get Number of Edges
    int get_edges() {
        return graph.size();
    }
    // Print Graph
    void print_graph() {
        for (auto &i: graph) {
            std::cout << i.first << ": ";
            if (!i.second.empty()) {
                for (auto &j: i.second) {
                    if (!i.second.empty()) {
                        std::cout << j->get_region_name() << " ";
                    }
                }
            }
            else {
                std::cout << "Null";
            }

            std:: cout << std::endl;
        }
    }
};

// Class for The Problem
int main() {

    Graph australia_map(7);
    // Create Nodes (Regions)
    Node* wa_ = new Node("WA");
    Node* nt_ = new Node("NT");
    Node* sa_ = new Node("SA");
    Node* q_ = new Node("Q");
    Node* nsw_ = new Node("NSW");
    Node* v_ = new Node("V");
    Node* t_ = new Node("T");
    // Create Graph with Adjacency
    // WA
    australia_map.add_edge("WA", nt_);
    australia_map.add_edge("WA", sa_);
    // NT
    australia_map.add_edge("NT", wa_);
    australia_map.add_edge("NT", sa_);
    australia_map.add_edge("NT", q_);
    // SA
    australia_map.add_edge("SA", wa_);
    australia_map.add_edge("SA", nt_);
    australia_map.add_edge("SA", q_);
    australia_map.add_edge("SA", nsw_);
    australia_map.add_edge("SA", v_);
    // Q
    australia_map.add_edge("Q", nt_);
    australia_map.add_edge("Q", sa_);
    // NSW
    australia_map.add_edge("NSW", v_);
    australia_map.add_edge("NSW", sa_);
    // V
    australia_map.add_edge("V", nsw_);
    australia_map.add_edge("SA", sa_);
    // T
    australia_map.add_edge("T", nullptr);

    australia_map.print_graph();




    return 0;
}

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;
 
void CoverComponent(
    int vertex,
    const vector<unordered_set<int>>& neighbours_for_vertex,
    vector<bool>& used,
    vector<int>& component_for_vertex,
    int component
)
{
    used[vertex] = true;
    component_for_vertex[vertex] = component;
    for (auto neighbour : neighbours_for_vertex[vertex]) {
        if (used[neighbour]) {
            continue;
        }
        CoverComponent(
            neighbour, neighbours_for_vertex,
            used,component_for_vertex, component
        );
    }
}

void PrintAdditionalEdges(const vector<int>& representative)
{
    int number_of_components = representative.size() - 1;
    cout << number_of_components - 1 << "\n";
    for (int component = 2; component <= number_of_components; ++component) {
        cout << representative[component - 1] << " " << representative[component] << "\n";
    }
}
 
int main() {
 
    int number_of_vertices = 0;
    int number_of_edges = 0;
    cin >> number_of_vertices >> number_of_edges;
 
    vector<bool> used(number_of_vertices + 1, false);
    vector<unordered_set<int>> neighbours_for_vertex(number_of_vertices + 1);
    vector<int> component_for_vertex(number_of_vertices + 1, -1);
 
    for (int i = 0; i < number_of_edges; ++i) {
        int vertex1 = 0;
        int vertex2 = 0;
        cin >> vertex1 >> vertex2;
        neighbours_for_vertex[vertex1].insert(vertex2);
        neighbours_for_vertex[vertex2].insert(vertex1);
    }

    vector<int> member_for_component(1);
    int cur_component = 0;
    for (int vertex = 1; vertex <= number_of_vertices; ++vertex) {
        if (component_for_vertex[vertex] == -1) {
            ++cur_component;
            member_for_component.push_back(vertex);
            CoverComponent(
                vertex, neighbours_for_vertex,
                used,component_for_vertex, cur_component
            );
        }
    }

    PrintAdditionalEdges(member_for_component);

    return 0;
}

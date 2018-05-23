#include <iostream>
#include <memory>
#include <vector>

class Employee;
typedef std::shared_ptr<Employee> Employee_ptr;

struct Employee
{
    int my_cost;
    int min_cost_if_invited;
    int min_cost;
    bool invited;
    std::vector<Employee_ptr> children;
};

int min_cost(std::vector<Employee_ptr> & node_list)
{
    // Start with the right most node in the list
    // Time complexity of this loop is O(n)
    for (int i = node_list.size() - 1; i >= 0; --i)
    {
        if (node_list[i]->children.empty())
        {
            // If current node has no children
            node_list[i]->min_cost_if_invited = node_list[i]->my_cost;
            node_list[i]->min_cost = 0;
            node_list[i]->invited = false;
        }
        else
        {
            // Min cost of children if inviting these children is not compulsary
            int min_cost_of_children = 0;

            // Cost of children if these children are invited
            int cost_of_inviting_children = 0;

            // Sum min_cost_of_children and cost_of_inviting_children
            for (auto child : node_list[i]->children)
            {
                min_cost_of_children += child->min_cost;
                cost_of_inviting_children += child->min_cost_if_invited;
            }

            // If current node is not invited, then we should consider
            // cost of inviting all children of this node.
            int min_cost_if_not_invited = cost_of_inviting_children;

            // If current node is invited, then we do not need to care too much
            // that we should invite children or not. Just include cost of myself
            // and minimum cost of all children.
            node_list[i]->min_cost_if_invited = node_list[i]->my_cost + min_cost_of_children;


            if (min_cost_if_not_invited > node_list[i]->min_cost_if_invited)
            {
                // There is less cost if current node is invited
                node_list[i]->invited = true;
                node_list[i]->min_cost = node_list[i]->min_cost_if_invited;
            }
            else // There is less cost if current node is not invited
            {
                node_list[i]->invited = false;
                node_list[i]->min_cost = min_cost_if_not_invited;

                // All children should be invited
                for (auto child : node_list[i]->children)
                {
                    child->invited = true;
                }
            }
        }
    }

    // Return min cost of the root node
    return node_list[0]->min_cost;
}

void main()
{



}
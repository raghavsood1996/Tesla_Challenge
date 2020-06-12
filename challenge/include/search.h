#pragma once

#include<utils.h>

#include<network.h>
#include<node.h>
#include<vector>

class Search
{

public:
    Search(node start, node goal);


private:
    std::array<row, 303> *network;
    double max_range = 320;
    double speed = 105;
    double min_time_step = 0.001;
    node start;
    node goal;

    std::vector<node> GetSuccs(node *curr_node);
    std::vector<node> Get_reachable_nodes(node* curr_node);
    std::vector<node> Get_charging_nodes(std::vector<node> &rch_nodes);
    void Get_charging_node(node &rch_node, std::vector<node> &ch_nodes);
    double get_cost(node &curr_node, node &succ);
    std::vector<node> Solve();


    
};
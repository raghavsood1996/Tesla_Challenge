#pragma once

#include<utils.h>

#include<network.h>
#include<node.h>
#include<vector>
#include<queue>
#include<map>
#include<unordered_set>
#include<unordered_map>

class Search
{

public:
    Search(node start, node goal, std::array<row, 303> *network);
    std::vector<node> Solve();


private:
    std::array<row, 303> *network;
    double max_range = 320;
    double speed = 105;
    double min_time_step = 0.25;
    std::unordered_map<node,double,NodeHasher> dist_map;
    std::unordered_map<node,node,NodeHasher> parent_map;
    std::unordered_map<node,std::vector<double>node,NodeHasher> ngb_map; 
    std::unordered_set<node,NodeHasher,NodeComparator> closed_list;

    node start;
    node goal;

    void GetSuccs(node *curr_node,std::vector<node>& Succs);
    void Get_reachable_nodes(node* curr_node,std::vector<node> &rch_nodes);
    void Get_charging_nodes(std::vector<node> &rch_nodes,std::vector<node> &Succs);
    void Get_charging_node(node &rch_node, std::vector<node> &ch_nodes);
    double get_cost(node &curr_node, node &succ);
    double get_goal_heuristic(node &nd);
    bool is_goal(node &nd);
    


    
};
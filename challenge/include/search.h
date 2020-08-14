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
    Search(Node start, Node goal, std::array<row, 303> *network);
    std::vector<Node> Solve();
    void set_time_resolution(double res);
    
private:

    std::array<row, 303> *network;
    double max_range = 319.9;
    double speed = 105;
    double min_time_step = 0.25;
    std::unordered_map<Node,double,NodeHasher> dist_map;
    std::unordered_map<Node,Node,NodeHasher> parent_map;
    std::unordered_map<Node,std::vector<Node>,NodeHasher2> ngb_map; 
    std::unordered_set<Node,NodeHasher,NodeComparator> closed_list;

    Node start;
    Node goal;

    void getSuccs(Node *curr_Node,std::vector<Node>& Succs);
    std::vector<Node>* getReachableNodes(Node* curr_Node);
    void getChargingNodes(std::vector<Node> &rch_Nodes,std::vector<Node> &Succs);
    void getChargingNode(Node &rch_Node, std::vector<Node> &ch_Nodes);
    double getCost(Node &curr_Node, Node &succ);
    double getGoalHeuristic(Node &nd);
    bool isGoal(Node &nd);
    


    
};
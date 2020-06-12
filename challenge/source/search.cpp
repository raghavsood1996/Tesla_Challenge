#include <search.h>



Search::Search(node start, node goal){
    this->start = start;
    this->goal = goal;
} 


//get all charging station within reach
std::vector<node> Search::Get_reachable_nodes(node* curr_node){
    std::vector<node> rch_nodes;
    double curr_range = curr_node->curr_charge;
    for(int i=0 ;i<network->size(); i++){
        auto dist = get_distance(curr_node->station_data,&(*network)[i]);
        if(dist < curr_range){
            //update left range for the new node
            node tmp(&(*network)[i],curr_range-dist,-1);
            rch_nodes.push_back(tmp);
        }
    }

    return rch_nodes;
}

void Search::Get_charging_node(node& nd, std::vector<node> &ch_nodes){
    double diff_charge = nd.curr_charge - max_range;
    double max_charge_time = diff_charge/nd.station_data->rate;

    double charge_time = 0; //decide later where to start
    while(charge_time < max_charge_time){
        double updated_charge = charge_time*nd.station_data->rate;
        node tmp(nd.station_data,updated_charge,charge_time);
        ch_nodes.push_back(tmp);
        charge_time += min_time_step;
    }

    return;
}

//for all station get all possible charging times
std::vector<node> Search::Get_charging_nodes(std::vector<node> &rch_nodes){
    std::vector<node> charging_nodes;

    for(auto nd : rch_nodes){
        Get_charging_node(nd,charging_nodes);
    }

    return charging_nodes;
}


std::vector<node> Search::GetSuccs(node* curr_node){
    //Get nearby nodes according to distance

    auto rch_nodes = Get_reachable_nodes(curr_node);
    std::vector<node> Succs = Get_charging_nodes(rch_nodes);

    return Succs;

}

double Search::get_cost(node &curr_node, node &succ){
    double cost = get_distance(curr_node.station_data,succ.station_data)/speed + succ.charge_time;
    return cost;
}


//WHerever comparisons are made make sure they are not exact for double datatypea

std::vector<node> Search::Solve(){
    std::vector<node> solution;

    return solution;
}
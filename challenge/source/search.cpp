#include <search.h>



Search::Search(node start, node goal, std::array<row,303> *network){
    this->start = start;
    this->goal = goal;
    this->network = network;
} 


//get all charging station within reach
std::vector<node> Search::Get_reachable_nodes(node* curr_node){
    std::vector<node> rch_nodes;
    double curr_range = curr_node->curr_charge;
    for(size_t i=0 ;i<network->size(); i++){
        auto dist = get_distance(curr_node->station_data,&(*network)[i]);
        if(dist < curr_range && dist > 0.1){
            //update left range for the new node
            // std::cout<<(*network)[i].name<<"\n";
            // std::cout<<"new range "<<curr_range-dist<<"\n";
            // getchar();
            node tmp(&(*network)[i],curr_range-dist,-1);
            rch_nodes.push_back(tmp);
        }
    }

    return rch_nodes;
}

void Search::Get_charging_node(node& nd, std::vector<node> &ch_nodes){
    double diff_charge = max_range - nd.curr_charge;
    double max_charge_time = diff_charge/nd.station_data->rate;
    // std::cout<<"max charge time "<<max_charge_time<<"\n";

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

    std::vector<node> rch_nodes = Get_reachable_nodes(curr_node);
    // std::cout<<rch_nodes.size()<<" Reachable Nodes\n";
    std::vector<node> Succs = Get_charging_nodes(rch_nodes);

    return Succs;

}

double Search::get_cost(node &curr_node, node &succ){
    double cost = get_distance(curr_node.station_data,succ.station_data)/speed + succ.charge_time;
    return cost;
}

double Search::get_goal_heuristic(node &nd){

    return get_distance(nd.station_data,goal.station_data)/speed;

}

bool Search:: is_goal(node &nd){
    if(nd.station_data->name == goal.station_data->name){
        return true;
    }

    return false;
}
//Wherever comparisons are made make sure they are not exact for double datatype

std::vector<node> Search::Solve(){

    std::priority_queue<node,std::vector<node>,priority> open_list;
    std::unordered_set<node,NodeHasher,NodeComparator> closed_list;

    start.g_val = 0;
    dist_map[start] = 0;
    start.h_val = get_goal_heuristic(start);
    open_list.push(start);

    node parent_node;
    int itr = 0;
    while(!open_list.empty()){
        itr++;
        

        parent_node =open_list.top();
        open_list.pop();
        if(is_goal(parent_node)){
            // std::cout<<"[INFO] FOUND GOAL"<<"\n";
            break;
        }

        //check if already in closed list
        if(closed_list.find(parent_node) != closed_list.end()){
            itr--;
            
            continue;
        }

        // std::cout<<itr<<"\n";
        // std::cout<<"Expanding\n"<<parent_node.station_data->name<<" "<<
        // parent_node.curr_charge<<" "<<parent_node.charge_time<<"\n";
        closed_list.insert(parent_node);

        auto succs = GetSuccs(&parent_node);

        for(auto succ: succs){

            double temp_g = dist_map[parent_node] + get_cost(parent_node,succ);
            if(dist_map.find(succ) == dist_map.end()){
                dist_map[succ] = temp_g;
                parent_map[succ] = parent_node;
                succ.g_val = temp_g;
                succ.h_val = get_goal_heuristic(succ);
                open_list.push(succ);
              
            }

            else if(temp_g < dist_map[succ]  + 1e-5){
                dist_map[succ] = temp_g;
                parent_map[succ] = parent_node;
                succ.g_val = temp_g;
                succ.h_val = get_goal_heuristic(succ);
                open_list.push(succ);
               

            }

        }
    }

    std::vector<node> solution;

    node st = parent_node;
    std::cout<<"[INFO] States Expanded : "<<itr<<"\n";
    std::cout<<"[INFO] Path Cost : "<<st.g_val<<"\n";
    std::cout<<st.charge_time<<" "<<st.curr_charge<<" "<<st.g_val<<"\n";
    std::vector<std::string> res;
    res.push_back(parent_node.station_data->name);

    node temp = st;
    std:: string last_st= st.station_data->name;
   
    while(!(parent_map[temp] == start)){
        temp = parent_map[temp];
        std::string curr_name = temp.station_data->name;
        if(curr_name != last_st){
           
            res.push_back(std::to_string(temp.charge_time));
            res.push_back(curr_name);
            // std::cout<<curr_name<<" "<<temp.charge_time<<"\n";
            last_st = curr_name;
        }
        
    }

    res.push_back(parent_map[temp].station_data->name);
    std::string out="";
    for(int i=res.size()-1; i>=0;i--){
        if(i >0){
        out += res[i] + ", ";
        }
        else{
            out += res[i];
        }

    }

    // out += "\"";
    std::cout<<out<<"\n";

    return solution;
}
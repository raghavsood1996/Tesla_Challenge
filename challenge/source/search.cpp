#include <search.h>

Search::Search(node start, node goal, std::array<row, 303> *network)
{
    this->start = start;
    this->goal = goal;
    this->network = network;
}

//get all charging station within reach
void Search::Get_reachable_nodes(node *curr_node , std::vector<node> &rch_nodes)
{
    
    double curr_range = curr_node->curr_charge;
    
    for (size_t i = 0; i < network->size(); i++)
    {
        auto dist = get_distance(curr_node->station_data, &(*network)[i]);
        if (dist < curr_range && dist > 0.1)
        {
            node tmp(&(*network)[i], curr_range - dist, 0);
            rch_nodes.push_back(tmp);
        }
    }

    
}

//get all possible charging times for a current state at a current charger
void Search::Get_charging_node(node &nd, std::vector<node> &ch_nodes)
{
    double diff_charge = max_range - nd.curr_charge;
    double max_charge_time = diff_charge / nd.station_data->rate;

    double charge_time = 0; //decide later where to start
    double updated_charge;
    while (charge_time < max_charge_time)
    {
        updated_charge = charge_time * nd.station_data->rate;
        node tmp(nd.station_data, nd.curr_charge + updated_charge, charge_time);

        ch_nodes.push_back(tmp);
        charge_time += min_time_step;
    }

    return;
}

//for all station get all possible charging times
void Search::Get_charging_nodes(std::vector<node> &rch_nodes, std::vector<node> &Succs)
{

    for (auto nd : rch_nodes)
    {
        Get_charging_node(nd, Succs);
    }
}

//generates succesors for creating the search graph
void Search::GetSuccs(node *curr_node, std::vector<node> &Succs)
{
    std::vector<node> rch_nodes;
    Get_reachable_nodes(curr_node,rch_nodes);
    Get_charging_nodes(rch_nodes, Succs);
}

//returns cost between two graph edges
double Search::get_cost(node &curr_node, node &succ)
{
    double cost = get_distance(curr_node.station_data, succ.station_data) / speed + succ.charge_time;
    return cost;
}

//return a heuristic to the goal
double Search::get_goal_heuristic(node &nd)
{

    return get_distance(nd.station_data, goal.station_data) / speed;
}

//checks if the search has reached goal
bool Search::is_goal(node &nd)
{
    if (nd.station_data->name == goal.station_data->name)
    {
        return true;
    }

    return false;
}

//running a weighted A* search by making a simultaneous implicit graph
std::vector<node> Search::Solve()
{

    std::priority_queue<node, std::vector<node>, priority> open_list;
    clock_t start_time;
    start_time = clock();
    start.g_val = 0;
    dist_map[start] = 0;
    start.h_val = get_goal_heuristic(start);
    open_list.push(start);
    bool found_goal = false;
    node parent_node;
    int itr = 0;
    while (!open_list.empty())
    {
        itr++;

        parent_node = open_list.top();
        open_list.pop();
        if (is_goal(parent_node))
        {
            found_goal = true;
            break;
        }

        //check if already in closed list
        if (closed_list.find(parent_node) != closed_list.end())
        {
            itr--;

            continue;
        }

        // std::cout<<itr<<"\n";
        // std::cout<<"Expanding\n"<<parent_node.station_data->name<<" "<<
        // parent_node.curr_charge<<" "<<parent_node.charge_time<<"\n";
        closed_list.insert(parent_node);

        std::vector<node> succs;
        GetSuccs(&parent_node, succs);

        for (auto succ : succs)
        {

            double temp_g = dist_map[parent_node] + get_cost(parent_node, succ);
            if (dist_map.find(succ) == dist_map.end())
            {
                dist_map[succ] = temp_g;
                parent_map[succ] = parent_node;
                succ.g_val = temp_g;
                succ.h_val = get_goal_heuristic(succ);
                open_list.push(succ);
            }

            else if (temp_g < dist_map[succ] + 1e-5)
            {
                dist_map[succ] = temp_g;
                parent_map[succ] = parent_node;
                succ.g_val = temp_g;
                succ.h_val = get_goal_heuristic(succ);
                open_list.push(succ);
            }
        }
    }

    if (!found_goal)
    {
        std::cout << "Error: No Solution to the query Exists"
                  << "\n";
    }
    std::vector<node> solution;
    float time_passed = (float(clock() - start_time)) / CLOCKS_PER_SEC;

    std::cout<<"Time passed "<<time_passed<<" secs"<<"\n";
    node st = parent_node;

    std::vector<std::string> res;
    res.push_back(parent_node.station_data->name);

    node temp = st;
    std::string last_st = st.station_data->name;

    //extracting the path
    while (!(parent_map[temp] == start))
    {
        temp = parent_map[temp];
        std::string curr_name = temp.station_data->name;
        if (curr_name != last_st)
        {

            res.push_back(std::to_string(temp.charge_time));
            res.push_back(curr_name);
            last_st = curr_name;
        }
    }

    res.push_back(parent_map[temp].station_data->name);

    std::string out = "";
    for (int i = res.size() - 1; i >= 0; i--)
    {
        if (i > 0)
        {
            out += res[i] + ", ";
        }
        else
        {
            out += res[i];
        }
    }

    // out += "\"";
    std::cout << out << "\n";

    return solution;
}
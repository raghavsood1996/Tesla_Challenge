#include <search.h>

Search::Search(Node start, Node goal, std::array<row, 303> *network)
{
    this->start = start;
    this->goal = goal;
    this->network = network;
    
}

//set time resolution for search
void Search::set_time_resolution(double res){
    this->min_time_step = res;
}

//get all charging station within reach
std::vector<Node>* Search::getReachableNodes(Node *curr_Node)
{
    
    double curr_range = curr_Node->curr_charge;
    
    if(ngb_map.find(*curr_Node) !=  ngb_map.end()){

        return &ngb_map[*curr_Node];
    }

    for (size_t i = 0; i < network->size(); i++)
    {
        auto dist = getDistance(curr_Node->station_data, &(*network)[i]);
        if (dist < curr_range && dist > 0.1)
        {
            Node tmp(&(*network)[i], curr_range - dist, 0);
            ngb_map[*curr_Node].push_back(tmp);
        }
    }


    return &ngb_map[*curr_Node];
}

//get all possible charging times for a current state at a current charger
void Search::getChargingNode(Node &nd, std::vector<Node> &ch_Nodes)
{
    double diff_charge = max_range - nd.curr_charge;
    double max_charge_time = diff_charge / nd.station_data->rate;

    double charge_time = 0.01; //decide later where to start
    double updated_charge;
    while (charge_time < max_charge_time)
    {
        updated_charge = charge_time * nd.station_data->rate;
        Node tmp(nd.station_data, nd.curr_charge + updated_charge, charge_time);

        ch_Nodes.push_back(tmp);
        charge_time += min_time_step;
    }

    return;
}

//for all station get all possible charging times
void Search::getChargingNodes(std::vector<Node> &rch_Nodes, std::vector<Node> &Succs)
{

    for (auto nd : rch_Nodes)
    {
        getChargingNode(nd, Succs);
    }
}

//generates succesors for creating the search graph
void Search::getSuccs(Node *curr_Node, std::vector<Node> &Succs)
{
   
    auto rch_Nodes = getReachableNodes(curr_Node);
    getChargingNodes(*rch_Nodes, Succs);
}

//returns cost between two graph edges
double Search::getCost(Node &curr_Node, Node &succ)
{
    double cost = getDistance(curr_Node.station_data, succ.station_data) / speed + succ.charge_time;
    return cost;
}

//return a heuristic to the goal
double Search::getGoalHeuristic(Node &nd)
{

    return getDistance(nd.station_data, goal.station_data) / speed;
}

//checks if the search has reached goal
bool Search::isGoal(Node &nd)
{
    if (nd.station_data->name == goal.station_data->name)
    {
        return true;
    }

    return false;
}

//running a weighted A* search by making a simultaneous implicit graph
std::vector<Node> Search::Solve()
{
    std::priority_queue<Node, std::vector<Node>> open_list;
    clock_t start_time;
    start_time = clock();
    start.g_val = 0;
    dist_map[start] = 0;
    start.h_val = getGoalHeuristic(start);
    open_list.push(start);
    bool found_goal = false;
    Node parent_Node;
    int itr = 0;
    while (!open_list.empty())
    {
        itr++;

        parent_Node = open_list.top();
        open_list.pop();
        
        if (isGoal(parent_Node))
        {
            found_goal = true;
            break;
        }

        //check if already in closed list
        if (closed_list.find(parent_Node) != closed_list.end())
        {
            itr--;

            continue;
        }

        closed_list.insert(parent_Node);

        std::vector<Node> succs;
        getSuccs(&parent_Node, succs);

        for (auto succ : succs)
        {

            double temp_g = dist_map[parent_Node] + getCost(parent_Node, succ);
            if (dist_map.find(succ) == dist_map.end())
            {
                dist_map[succ] = temp_g;
                parent_map[succ] = parent_Node;
                succ.g_val = temp_g;
                succ.h_val = getGoalHeuristic(succ);
                open_list.push(succ);
            }

            else if (temp_g < dist_map[succ] + 1e-5)
            {
                dist_map[succ] = temp_g;
                parent_map[succ] = parent_Node;
                succ.g_val = temp_g;
                succ.h_val = getGoalHeuristic(succ);
                open_list.push(succ);
            }
        }
    }

    if (!found_goal)
    {
        std::cout << "Error: No Solution to the query Exists"
                  << "\n";
    }

    std::vector<Node> solution;
    float time_passed = (float(clock() - start_time)) / CLOCKS_PER_SEC;

    // std::cout<<"Time passed "<<time_passed<<" secs"<<"\n";
    Node st = parent_Node;

    std::vector<std::string> res;
    res.push_back(parent_Node.station_data->name);

    Node temp = st;
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

   
    std::cout << out << "\n";

    return solution;
}
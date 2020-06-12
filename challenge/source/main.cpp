
#include<network.h>
#include<node.h>
#include<search.h>
#include<utils.h>


//return reference to the station by reading station name
const row* get_station(std::string charger_name){
    int num_stations = network.size();
    for(int i=0 ; i<num_stations;i++){
        if(network[i].name == charger_name ){
            return &network[i];
        }
    }

    return NULL;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Error: requires initial and final supercharger names" << std::endl;        
        return -1;
    }
    
    std::string initial_charger_name = argv[1];
    std::string goal_charger_name = argv[2];

    // std::string initial_charger_name = "Lumberton_NC";
    // std::string goal_charger_name = "Cadillac_MI";
    // double max_range = 320;
    // double speed = 105;

    auto init_charger = get_station(initial_charger_name);
    auto goal_charger = get_station(goal_charger_name);

    node start(init_charger,320,0);
    node goal(goal_charger);

    // std::cout<<get_distance(init_charger,goal_charger)<<"\n";
    Search src_obj(start,goal,&network);
    src_obj.Solve();
    return 0;
}

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
    // if (argc != 3)
    // {
    //     std::cout << "Error: requires initial and final supercharger names" << std::endl;        
    //     return -1;
    // }
    
    // std::string initial_charger_name = argv[1];
    // std::string goal_charger_name = argv[2];

    std::string initial_charger_name = "Albany_NY";
    std::string goal_charger_name = "Sweetwater_TX";


    auto init_charger = get_station(initial_charger_name);
    auto goal_charger = get_station(goal_charger_name);
    if(init_charger == NULL || goal_charger == NULL){

        std::cout<<"Error: Invalid Query"<<"\n";
        return -1;
    }


    if(initial_charger_name == goal_charger_name){
        std::cout<<"Error: You are already at the destination"<<"\n";
        return -1;
    }


    node start(init_charger,320,0);
    node goal(goal_charger);

    Search src_obj(start,goal,&network);
    src_obj.Solve();
    return 0;
}
#include<network.h>
#include<node.h>
#include<search.h>
#include<utils.h>



// Inflation factor that controls optimality of the search
// Inflation factor of 1 will give optimal result with guarantee
// otherwise solution_cost <= compare_weight*(optimal_cost)

const double Node::compare_weight = 1.8; // if want optimal solution set to 1 (might be very slow for some cases)



int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Error: requires initial and final supercharger names" << std::endl;        
        return -1;
    }
    
    std::string initial_charger_name = argv[1];
    std::string goal_charger_name = argv[2];



    auto init_charger = getStation(initial_charger_name);
    auto goal_charger = getStation(goal_charger_name);
    if(init_charger == NULL || goal_charger == NULL){

        std::cout<<"Error: Invalid Query"<<"\n";
        return -1;
    }


    if(initial_charger_name == goal_charger_name){
        std::cout<<"Error: You are already at the destination"<<"\n";
        return -1;
    }

    //init start and goal for the search
    Node start(init_charger,320,0);
    Node goal(goal_charger);

    // time resolution for search in hours
    // higher the resolution slower the search runs but might get slightly better sols
    double search_res = 0.5;
    Search planner(start,goal,&network);
    planner.set_time_resolution(search_res);
    auto solution = planner.Solve();
    return 0;
}
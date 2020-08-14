#pragma once

#include <iostream>
#include <stdlib.h>
#include <network.h>
#include <string>

//Node class used for search
struct Node
{
    const row *station_data;
    double curr_charge;
    double charge_time;
    double g_val; // cost from start
    double h_val; //heuristic value
    
    static const double compare_weight;

    Node()
    {
        station_data = NULL;
        g_val = __DBL_MAX__;
        curr_charge = -1;
        charge_time = -1;
    }

    Node(const row *station_data, double curr_charge, double charge_time)
    {
        this->station_data = station_data;
        this->curr_charge = curr_charge;
        this->charge_time = charge_time;
        g_val = __DBL_MAX__;
        
    }

    Node(const row *station_data)
    {
        this->station_data = station_data;
        this->curr_charge = -1;
        this->charge_time = -1;
        g_val = __DBL_MAX__;
        
    }


    inline bool operator==(const Node &rhs) const
    {
        double dist_epsilon = 1e-5; //decide upon a correct resolution
        double t_epsilon = 1e-5; //decide upon a correct resolution

        if (this->station_data->name != rhs.station_data->name)
        {
            return false;
        }

        if (abs(this->curr_charge - rhs.curr_charge) > dist_epsilon )
        {
            return false;
        }
        if (abs(this->charge_time - rhs.charge_time) >t_epsilon)
        {
            return false;
        }

        return true;
    }


    inline int to_int() const{
        int temp = 0 ;
        temp += int(this->station_data->lat);
        temp -= int(this->station_data->lon);
        temp -= 10*this->curr_charge;
        temp += 10*this->charge_time;

        return temp;

    }

    inline int to_int2() const{
        int temp = 0 ;
        temp += int(this->station_data->lat);
        temp -= int(this->station_data->lon);
        temp -= 10*this->curr_charge;
        
        return temp;

    }

    friend bool operator<(const Node s1, const Node &s2){

       
        return s1.g_val + Node::compare_weight*s1.h_val > s2.g_val + Node::compare_weight*s2.h_val;
    }
};

struct NodeHasher
{
    size_t operator()(const Node &thestate) const
    {
        return std::hash<int>{}(thestate.to_int());
    }
};

struct NodeHasher2
{
    size_t operator()(const Node &thestate) const
    {
        return std::hash<int>{}(thestate.to_int2());
    }
};
// util function for unordred set of Nodes
struct NodeComparator
{
    bool operator()(const Node &lhs, const Node &rhs) const
    {
        return lhs == rhs;
    }
};


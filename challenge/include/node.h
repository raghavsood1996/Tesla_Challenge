#pragma once

#include <iostream>
#include <stdlib.h>
#include <network.h>
#include <string>

struct node
{
    const row *station_data;
    double curr_charge;
    double charge_time;
    double g_val; // cost from start
    double h_val; //heuristic value
    node *parent;

    node()
    {
        station_data = NULL;
        g_val = __DBL_MAX__;
        parent = NULL;
        curr_charge = -1;
        charge_time = -1;
    }

    node(const row *station_data, double curr_charge, double charge_time)
    {
        this->station_data = station_data;
        this->curr_charge = curr_charge;
        this->charge_time = charge_time;
        g_val = __DBL_MAX__;
        parent = NULL;
    }

    node(const row *station_data)
    {
        this->station_data = station_data;
        this->curr_charge = -1;
        this->charge_time = -1;
        g_val = __DBL_MAX__;
        parent = NULL;
    }

    inline bool operator==(const node &rhs) const
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

    inline std::string toString() const{
        std::string temp = "";

		temp += this->station_data->name + ",";
		temp += std::to_string(this->curr_charge);
        temp += std::to_string(this->charge_time);

		return temp;
    }
};

struct NodeHasher
{
    size_t operator()(const node &thestate) const
    {
        return std::hash<std::string>{}(thestate.toString());
    }
};
// util function for unordred set of nodes
struct NodeComparator
{
    bool operator()(const node &lhs, const node &rhs) const
    {
        return lhs == rhs;
    }
};

class priority
{
public:
    bool operator()(const node &s1, const node &s2)
    {
        return s1.g_val + s1.h_val > s2.g_val + s2.h_val;
    }
};
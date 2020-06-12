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
    double g_val;
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

        if (this->station_data->name != rhs.station_data->name)
        {
            return false;
        }

        if (this->curr_charge != rhs.curr_charge)
        {
            return false;
        }
        if (this->charge_time != rhs.charge_time)
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

struct stateHasher
{
    size_t operator()(const node &thestate) const
    {
        return std::hash<std::string>{}(thestate.toString());
    }
};
// util function for unordred set of nodes
struct stateComparator
{
    bool operator()(const node &lhs, const node &rhs) const
    {
        return lhs == rhs;
    }
};

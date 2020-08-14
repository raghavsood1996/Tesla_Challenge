#pragma once

#include<network.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>



//return reference to the station by reading station name
inline const row* getStation(std::string charger_name){
    int num_stations = network.size();
    for(int i=0 ; i<num_stations;i++){
        if(network[i].name == charger_name ){
            return &network[i];
        }
    }

    return NULL;
}

//convert degrees to radians
inline long double toRadians(const long double degree) 
{ 
    long double one_deg = (M_PI) / 180; 
    return (one_deg * degree); 
}

//get distance on the globe between two stations
inline double getDistance(const row *station_1, const row *station_2){
    
    double lat1 = toRadians(station_1->lat); 
    double long1 = toRadians(station_1->lon); 
    double lat2 = toRadians(station_2->lat); 
    double long2 = toRadians(station_2->lon); 
      
    // Haversine Formula 
    double dlong = long2 - long1; 
    double dlat = lat2 - lat1; 
    double dist = pow(sin(dlat / 2), 2) +  
                          cos(lat1) * cos(lat2)*  
                          pow(sin(dlong / 2), 2); 
  
    dist = 2 * asin(sqrt(dist)); 
  
    
    double R = 6356.752; 
      
    
    dist = dist * R; 
  
    return dist; 
}

#pragma once
#pragma once

#include<network.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>

inline long double toRadians(const long double degree) 
{ 
    long double one_deg = (M_PI) / 180; 
    return (one_deg * degree); 
}

//get distance on the globe between two stations
inline double get_distance(const row *station_1, const row *station_2){
    
    long double lat1 = toRadians(station_1->lat); 
    long double long1 = toRadians(station_1->lon); 
    long double lat2 = toRadians(station_2->lat); 
    long double long2 = toRadians(station_2->lon); 
      
    // Haversine Formula 
    long double dlong = long2 - long1; 
    long double dlat = lat2 - lat1; 
  
    long double dist = pow(sin(dlat / 2), 2) +  
                          cos(lat1) * cos(lat2)*  
                          pow(sin(dlong / 2), 2); 
  
    dist = 2 * asin(sqrt(dist)); 
  
    
    long double R = 6356.752; 
      
    
    dist = dist * R; 
  
    return dist; 
}

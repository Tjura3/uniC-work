#define _USE_MATH_DEFINES

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;
const double EARTH_RADIUS = 6371.0;
struct CityCoords{
    string loc; //location
    double lon;
    double lat;
    CityCoords(string location, double latitude, double longitude) : loc(location), lat(latitude), lon(longitude) {}
};
vector<CityCoords> cityCoords = {
    CityCoords("Frankfurt",50.1109, 8.6821),
    CityCoords("Copenhagen",55.6761, 12.5683),
    CityCoords("Prague",50.0755, 14.4378),
    CityCoords("Rome",41.9028, 12.4964),
    CityCoords("Vienna",48.2082, 16.3738),
    CityCoords("Budapest",47.4979, 19.0402),
    CityCoords("Barcelona",41.3784, 2.1915),
    CityCoords("Florence",43.7696, 11.2558),
    CityCoords("Berlin",52.52, 13.405),
    CityCoords("Amsterdam",52.3676, 4.9041),
    CityCoords("Paris",48.8566, 2.3522)
    
};
vector<CityCoords> cityCoords2 = {
    CityCoords("New York", 40.7128, -74.0060),
    CityCoords("Los Angeles", 34.0522, -118.2437),
    CityCoords("Chicago", 41.8781, -87.6298),
    CityCoords("Houston", 29.7604, -95.3698),
    CityCoords("Phoenix", 33.4484, -112.0740),
    CityCoords("Philadelphia", 39.9526, -75.1652),
    CityCoords("San Francisco", 37.7749, -122.4194),
    CityCoords("Seattle", 47.6062, -122.3321),
    CityCoords("Denver", 39.7392, -104.9903),
    CityCoords("Atlanta", 33.7490, -84.3880),
    CityCoords("Miami", 25.7617, -80.1918),
    CityCoords("Boston", 42.3601, -71.0589)
};
double toRadians(double degrees) {
    return degrees * M_PI / 180;
}
double calcDistance(double lat1, double lon1, double lat2, double lon2) {
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    // Haversine formula
    double a = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return EARTH_RADIUS * c;
}

double distanceBetween(const CityCoords& a, const CityCoords& b){
    return calcDistance(a.lat, a.lon, b.lat, b.lon);
}

void runMST(vector<CityCoords>& ccords){
    //Use distance between to find the weight of each edge, put them in MST
    // Stores each edge's minimum weight, the parent of each of those minimums, and lastly an extra vector for storing if we visited or not
    int csize = ccords.size();
    vector<double> minEdge(csize, numeric_limits<double>::infinity());
    vector<int> parent(csize, -1);
    vector<bool> visited(csize, false);

    minEdge[0] = 0;
    double totalDistance = 0;
    for(int i = 0; i < csize; i++){

        //this part finds the closest city to any of the current ones in the thing
        //if what is considered the closest is smaller than iterating, replace that with the closest.
        int close = -1;
        for (int j = 0; j < csize; ++j) {
            if (!visited[j] && (close == -1 || minEdge[j] < minEdge[close])) {
                close = j;
            }
        }
        visited[close] = true;
        totalDistance += minEdge[close];

        if(parent[close] != -1){
            cout << ccords[parent[close]].loc << " <---> " << ccords[close].loc << " Distance: " << minEdge[close] << endl;
        }
        for(int j = 0; j < csize; j++){
            double dist = distanceBetween(cityCoords[close], cityCoords[j]);
            if (dist < minEdge[j]) {
                minEdge[j] = dist;
                parent[j] = close;  
            }
        }
    }
}

int main(){
    runMST(cityCoords);
    runMST(cityCoords2);
    
    return 0;
}

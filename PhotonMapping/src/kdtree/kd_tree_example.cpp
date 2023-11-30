#include "kdtree.h"
#include "../Photon.hpp"


/*
    An additional struct that allows the KD-Tree to access your photon position
*/
struct PhotonAxisPosition {
    float operator()(const Photon& p, std::size_t i) const {
        return p.position(i);
    }
};

/*
    The KD-Tree ready to work in 3 dimensions, with Photon s, under a
    brand-new name: PhotonMap
*/
using PhotonMap = nn::KDTree<Photon, 3, PhotonAxisPosition>;


/*
    Example function to generate the photon map with the given photons
*/
// PhotonMap generation_of_photon_map(...) {
//     std::list<Photon> photons = ...;        // Create a list of photons
//     map = PhotonMap(photons, PhotonAxisPosition())
//         return map
// }


/*
    Example method to search for the nearest neighbors of the photon map
*/
void search_nearest(PhotonMap map, Photon photon) {
    // Position to look for the nearest photons
    Punto query_position = photon.getPosition();

    // Maximum number of photons to look for
    unsigned long nphotons_estimate = 100.0;

    // Maximum distance to look for photons
    float radius_estimate = 1.0;

    // nearest is the nearest photons returned by the KDTree
    auto nearest = map.nearest_neighbors(query_position,
        nphotons_estimate,
        radius_estimate);
}




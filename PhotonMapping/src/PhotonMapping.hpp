#ifndef PHOTON_MAPPING_HPP
#define PHOTON_MAPPING_HPP

#include <iostream>
#include "Photon.hpp"
#include "kdtree/kdtree.h"
#include "../../PathTracing/src/FuenteLuz.hpp"
#include "../../PathTracing/src/Materiales/Material.hpp"

using namespace std;

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
using vecPhotons = std::vector<const Photon*>;

class PhotonMapping {
private:
    PhotonMap map;
    vector<Geometria*> objects;
    vector<FuenteLuz*> sources;
    int numPhotons;
    int maxBounces;
    double nphotons_estimate;
    double radius_estimate;

public:
    PhotonMapping(vector<Geometria*> objects, vector<FuenteLuz*> sources,
        int numPhotons, int maxBounces, double nphotons_estimate, double radius_estimate);


    // Method to search for the nearest neighbors of the photon map
    vecPhotons search_nearest(const PhotonMap& map, const Photon& photon) const;

    // Method to generate the photon map given the light sources and the objects of the scene
    PhotonMap generatePhotonMap();

    // Method to calculate the total emissions of the light sources
    double calculateTotalEmissions();

};

#endif

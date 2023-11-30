#include "PhotonMapping.hpp"

#include <iostream>

using namespace std;

// Constructor
PhotonMapping::PhotonMapping(vector<Geometria*> _objects, vector<FuenteLuz*> _sources, int _numPhotons,
    int _maxBounces, double _nphotons_estimate, double _radius_estimate) :
    objects(_objects), sources(_sources), numPhotons(_numPhotons),
    maxBounces(_maxBounces), nphotons_estimate(_nphotons_estimate),
    radius_estimate(_radius_estimate) {
}

// Method to search for the nearest neighbors of the photon map
vecPhotons PhotonMapping::search_nearest(const PhotonMap& map, const Photon& photon) const {
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

    return nearest;
}

// Method to generate the photon map given the light sources and the objects of the scene
PhotonMap PhotonMapping::generatePhotonMap() {
    double totalEmissions = calculateTotalEmissions();

    // For each light source calculate the amount of photons to emit
    for (FuenteLuz* source : sources) {

        Color sourceEnergy = source->getEnergia();
        double maximumEmission = max(sourceEnergy.r, max(sourceEnergy.g, sourceEnergy.b));
        double photonsToEmit = numPhotons * (maximumEmission / totalEmissions);

        // Emit photons
        
        

    }

}

// Method to calculate the total emissions of the light sources
double PhotonMapping::calculateTotalEmissions() {
    double totalEmissions = 0;
    for (FuenteLuz* source : sources) {
        // Calculate the total emissions of the light sources
        Color aux = source->getEnergia();
        double maximumEmission = max(aux.r, max(aux.g, aux.b));
        totalEmissions = totalEmissions + maximumEmission;
    }

    return totalEmissions;
}

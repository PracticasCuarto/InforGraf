#ifndef PHOTON_MAPPING_HPP
#define PHOTON_MAPPING_HPP

#include <iostream>
#include <vector>
#include "Photon.hpp"
#include "kdtree/kdtree.h"
#include "FuenteLuz.hpp"
#include "Materiales/Material.hpp"
#include "RandomNumber.hpp"

using namespace std;

const int MODO = 1; // 0 = Event estimation, 1 = Luz directa sin primer rebote

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
    vector<Photon> photonsList;
    vector<Geometria*> objects;
    vector<FuenteLuz*> sources;
    int numPhotons;
    double nphotons_estimate;
    double radius_estimate;

public:
    PhotonMapping(vector<Geometria*> objects, vector<FuenteLuz*> sources,
        int numPhotons, double nphotons_estimate, double radius_estimate);

    // Empty constructor
    PhotonMapping();

    // PHASE 1: Generation of the photon map

    // Method to search for the nearest neighbors of the photon map
    vecPhotons search_nearest(const PhotonMap& map, const Photon& photon) const;

    // Method to generate the photon map given the light sources and the objects of the scene
    void generatePhotonMap();

    // Method to calculate the total emissions of the light sources
    double calculateTotalEmissions();

    // Method to emit a photon from a light source
    void emitPhoton(const Color& flux, const Rayo& ray, const bool firstIter);

    // Method to calculate the intersection of the ray with all the objects of the scene
    // and save the closest intersection, along with its information
    bool intersectionRayScene(const Rayo& ray, Material& material, Punto& intersectionPoint, Direccion& normal, int& resultIndex) const;

    // Method to calculate the light of a photon in a point of intersection
    void nextEventEstimation(const Punto intersectionPoint, const Material& material, const Direccion& normal, const Direccion& wo, const Color& flux, const bool firstIteration);

    // Method to calculate the diffuse component of a material
    Color calculateDiffuseComponent(const Material& material, const Punto& intersectionPoint, const Direccion& normal, const Punto& origin, const int& numPhotons) const;

    // Method to calculate the direct light of a source in a point of intersection
    Color directLight(const Punto& intersectionPoint, const Color& BRDF, const Direccion& normal) const;

    // Method to calculate the incident light of a source in a point of intersection
    Color calculateIncidentLight(const FuenteLuz& source, const Punto& intersectionPoint) const;

    // Method to calculate if the ray that joins a point and the light has any collision on its way
    bool intersectsObjectBeforeSource(const Punto& intersectionPoint, const Direccion& direction, const Punto& sourceOrigin) const;

    // PHASE 2: Calculation of the radiance of the scene

    // Method to calculate the color of a pixel given a ray
    Color calculatePixelColor(const Rayo& ray) const;

};

#endif

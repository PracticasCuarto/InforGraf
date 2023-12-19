#include "PhotonMapping.hpp"

#include <iostream>

using namespace std;

PhotonMapping::PhotonMapping() {
    // Create the empty list
    photonsList = vector<Photon>();
}

// Constructor
PhotonMapping::PhotonMapping(vector<Geometria*> _objects, vector<FuenteLuz*> _sources, int _numPhotons,
    double _nphotons_estimate, double _radius_estimate) :
    objects(_objects), sources(_sources), numPhotons(_numPhotons),
    nphotons_estimate(_nphotons_estimate),
    radius_estimate(_radius_estimate) {

    // Create the empty list
    photonsList = vector<Photon>();
}

// Función para generar un número aleatorio en el rango [0, 1)
double randomDouble() {
    static std::random_device rd;
    static std::mt19937 generator(rd()); // Inicializa el generador con una semilla aleatoria
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

void createCoordinateSystem(const Direccion& N, Direccion& Nt, Direccion& Nb) {
    if (std::fabs(N.x) > std::fabs(N.y))
        Nt = Direccion(N.z, 0, -N.x) / sqrtf(N.x * N.x + N.z * N.z);
    else
        Nt = Direccion(0, -N.z, N.y) / sqrtf(N.y * N.y + N.z * N.z);
    Nb = N.cross(Nt);
}

// Method to calculate the direction of a ray photon being emmited from a light source
Rayo randomRay(const Direccion& normal, const Punto& origin) {
    double rand1 = randomDouble();
    double rand2 = randomDouble();

    double theta = acos(2 * rand1 - 1);
    double phi = 2 * M_PI * rand2;

    double x = sin(theta) * cos(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(theta);

    Direccion randomDirection = Direccion(x, y, z);

    // Generate the local base
    Direccion axis1 = Direccion(-INFINITY, -INFINITY, -INFINITY);
    Direccion axis2 = Direccion(-INFINITY, -INFINITY, -INFINITY);

    createCoordinateSystem(normal, axis1, axis2);

    axis1 = axis1.normalizar();
    axis2 = axis2.normalizar();

    // Create the base matrix with the local base    
    Matriz baseMatrix = Matriz(
        axis1.x, axis2.x, normal.x, 0,
        axis1.y, axis2.y, normal.y, 0,
        axis1.z, axis2.z, normal.z, 0,
        0, 0, 0, 1
    );

    // // Change the direction of the ray to the world base
    Direccion rayDirection = randomDirection.multiplicarMatriz(baseMatrix).normalizar();
    return Rayo(origin, rayDirection);
}

// Method to generate a random ray in a hemisphere using the cosine distribution
Rayo randomRayCosine(const Punto& intersectionPoint, const Direccion& normal) {
    double r1 = randomDouble();
    double r2 = randomDouble();
    double theta = 2.0 * M_PI * r1; // Azimut angle
    double phi = acos(sqrt(1.0 - r2)); // Polar angle

    // Conver to cartesian coordinates
    double x = cos(theta) * sin(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(phi);

    Direccion randomDirection = Direccion(x, y, z);

    // Generate the local base
    Direccion axis1 = Direccion(-INFINITY, -INFINITY, -INFINITY);
    Direccion axis2 = Direccion(-INFINITY, -INFINITY, -INFINITY);

    createCoordinateSystem(normal, axis1, axis2);

    axis1 = axis1.normalizar();
    axis2 = axis2.normalizar();

    // Change the base using the matrix generated
    Matriz baseMatrix = Matriz(
        axis1.x, axis2.x, normal.x, 0,
        axis1.y, axis2.y, normal.y, 0,
        axis1.z, axis2.z, normal.z, 0,
        0, 0, 0, 1
    );

    // Change the direction of the ray to the world base
    Direccion rayDirection = randomDirection.multiplicarMatriz(baseMatrix).normalizar();
    return Rayo(intersectionPoint, rayDirection);
}

// Función para calcular la direccion del rayo entrante en una refraccion
Direccion refractedRay(const Direccion& wo, const Direccion& n, const double& refractiveIndex) {
    Direccion woNormal = wo.normalizar();
    Direccion nNormal = n.normalizar();
    double cosi = ((woNormal * -1) * nNormal);
    Direccion normal = nNormal;
    double refractiveIndexActual = 1.0f, refractiveIndexSiguiente = refractiveIndex;
    double coeficienteRefraccion;

    if (cosi < 0) {
        // Saliendo
        cosi = abs(cosi);
        coeficienteRefraccion = refractiveIndexSiguiente / refractiveIndexActual;
        normal = Direccion(-n.x, -n.y, -n.z).normalizar();
    }
    else {
        // Entrando
        coeficienteRefraccion = refractiveIndexActual / refractiveIndexSiguiente;
    }
    double sinI = sqrt(1 - (cosi * cosi));
    double sinT = coeficienteRefraccion * sinI;
    double cosT = sqrt(1 - (sinT * sinT));

    return  ((woNormal * coeficienteRefraccion) + (normal * ((coeficienteRefraccion * cosi) - cosT))).normalizar();
}

// Method to calculate the BRDF of a diffuse material
Color calculateDiffuseMaterial(const Color& color) {
    // Divide each component of the color by pi
    double r = (color.r / M_PI);
    double g = (color.g / M_PI);
    double b = (color.b / M_PI);

    return Color(r, g, b);
}

// Method to search for the nearest neighbors of the photon map
vecPhotons PhotonMapping::search_nearest(const PhotonMap& map, const Photon& photon) const {

    // Position to look for the nearest photons
    Punto query_position = photon.getPosition();

    // nearest is the nearest photons returned by the KDTree
    auto nearest = map.nearest_neighbors(query_position,
        nphotons_estimate,
        radius_estimate);

    return nearest;
}

// Method to generate the photon map given the light sources and the objects of the scene
void PhotonMapping::generatePhotonMap() {
    double totalEmissions = calculateTotalEmissions();

    // For each light source calculate the amount of photons to emit
    for (FuenteLuz* source : sources) {

        Color sourceEnergy = source->getEnergia();
        double maximumEmission = max(sourceEnergy.r, max(sourceEnergy.g, sourceEnergy.b));
        int photonsToEmit = numPhotons * (maximumEmission / totalEmissions);

        Punto origin = source->getOrigen();

        Color flux = (sourceEnergy * 4 * M_PI) / numPhotons;

        for (int i = 0; i < photonsToEmit; i++) {

            // Create the ray photon
            Rayo ray = randomRay(Direccion(0, 1, 0), origin);
            // Emit photons
            emitPhoton(flux, ray);
        }

    }

    // Show the photon map generated
    // for (Photon photon : photonsList) {
    //     cout << "POSITION: " << photon.getPosition().x << " " << photon.getPosition().y << " " << photon.getPosition().z << endl;
    //     cout << "PLEX: " << photon.getFlux().r << " " << photon.getFlux().g << " " << photon.getFlux().b << endl;
    // }

    // Create the photon map
    map = PhotonMap(photonsList, PhotonAxisPosition());
    cout << "Photon map generated" << endl;

    // Destroy photon list
    photonsList.clear();
}

// Method to emit a photon from a light source
void PhotonMapping::emitPhoton(const Color& flux, const Rayo& ray) {
    // Calculate the intersection of the ray with all the objects of the scene
    Punto point = Punto(-INFINITY, -INFINITY, -INFINITY);
    Material material = Material();
    Direccion normal = Direccion(-INFINITY, -INFINITY, -INFINITY);
    int index = -1;
    bool intersects = intersectionRayScene(ray, material, point, normal, index);

    if (!intersects) {
        // There is no intersection
        cout << "There is no intersection" << endl;
        return;
    }
    else {
        nextEventEstimation(point, material, normal, ray.getDireccion(), flux);
    }
}

// Method to calculate the light of a photon in a point of intersection
void PhotonMapping::nextEventEstimation(const Punto intersectionPoint, const Material& material, const Direccion& normal, const Direccion& wo, const Color& flux) {
    // Check the type of the material
    Componentes type = material.ruletaRusa();
    if (type == DIFUSO) {
        // Bounce the photon and calculate the next event estimation
        Color BRDF = calculateDiffuseMaterial(material.getDifuso());
        Color fluxActual = flux * BRDF * M_PI;
        // Store the photon in the photon map
        Photon photonNow = Photon(intersectionPoint, wo, fluxActual);
        photonsList.push_back(photonNow);

        // Generate the ray
        Rayo ray = randomRayCosine(intersectionPoint, normal);
        emitPhoton(flux * BRDF * M_PI, ray);
    }
    else if (type == ESPECULAR) {
        // Calculate the new direction of the photon
        Direccion wi = wo - (normal * (2 * (wo * normal)));
        wi = wi.normalizar();

        // Send the new photon to the scene
        Rayo ray = Rayo(intersectionPoint, wi);
        emitPhoton(flux, ray);
    }
    else if (type == REFRACCION) {
        //result = calcularComponenteRefractante(material, intersectionPoint, wo, normal);
    }
    else if (type == ABSORCION) {
        // The light is absorbed so nothing is done
    }
    else {
        cout << "Error: tipo de material no reconocido" << endl;
    }
}

// Method to calculate the direct light of a source in a point of intersection
Color PhotonMapping::directLight(const Punto& intersectionPoint, const Color& BRDF, const Direccion& normal) const {
    Color result = Color(0, 0, 0);
    // Calcular la luz directa a partir de las fuentes de luz
    for (FuenteLuz* lightSource : sources) {
        Punto sourceOrigin = lightSource->getOrigen();
        Direccion wi = (sourceOrigin - (intersectionPoint)).normalizar();

        if (intersectsObjectBeforeSource(intersectionPoint, wi, sourceOrigin)) {
            continue;
        }

        Color luzIncidente = calculateIncidentLight(*lightSource, intersectionPoint);
        double coseno = abs(normal * wi);
        Color material = luzIncidente * BRDF * coseno;

        // Calcular el color del pixel
        result += material;
    }
    return result;
}

// Method to calculate the incident light of a source in a point of intersection
Color PhotonMapping::calculateIncidentLight(const FuenteLuz& source, const Punto& intersectionPoint) const {
    double wi = (source.getOrigen() - intersectionPoint).modulo();
    return (source.getEnergia() / (wi * wi));
}

// Method to calculate if the ray that joins a point and the light has any collision on its way
bool PhotonMapping::intersectsObjectBeforeSource(const Punto& intersectionPoint, const Direccion& direction, const Punto& sourceOrigin) const {
    // Calcular la distance entre el punto y el origen de la fuente de luz
    double distance = intersectionPoint.distancia(sourceOrigin);
    Rayo ray = Rayo(intersectionPoint, direction);

    for (int k = 0; k < objects.size(); k++) {
        // Check the intersection of the ray with the objects of the scene
        Punto intersectionPointObject = objects[k]->interseccion(ray);

        // Comprobar si la interseccion es válida
        bool intersection = intersectionPointObject.x != -INFINITY;
        bool validIntersection = intersectionPointObject.distancia(intersectionPoint) < distance;
        if (intersection && validIntersection) {
            return true;
        }
    }
    return false;
}


// Method to calculate the diffuse component of a material
Color PhotonMapping::calculateDiffuseComponent(const Material& material, const Punto& intersectionPoint, const Direccion& normal, const Punto& origin, const int& numPhotons) const {

    Color diffuse = material.getDifuso();
    Color BRDF = calculateDiffuseMaterial(diffuse);

    Direccion wo = (origin - intersectionPoint).normalizar();

    // Calculate the direct light
    Color result = directLight(intersectionPoint, BRDF, normal);

    // Calculate the indirect light
    Rayo ray = randomRayCosine(intersectionPoint, normal);


    // result += color * BRDF * M_PI;
    return result;
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

// Calculate the intersection of the ray with all the objects of the scene
// and save the closest intersection, along with its information
bool PhotonMapping::intersectionRayScene(const Rayo& ray, Material& material, Punto& intersectionPoint, Direccion& normal, int& resultIndex) const {
    float distance = INFINITY;
    int index = -1;
    bool result = false;

    Punto origin = ray.getOrigen();

    for (Geometria* object : objects) {
        index++;
        Punto intersectionPointObject = object->interseccion(ray);
        if (intersectionPointObject.x == -INFINITY) {
            continue;
        }

        // Calculate the distance between the origin of the ray and the intersection point
        float intersectionDistance = origin.distancia(intersectionPointObject);
        if (intersectionDistance <= distance) {
            distance = intersectionDistance;
            material = object->getMaterial();
            intersectionPoint = intersectionPointObject;
            normal = object->getNormal(intersectionPoint);
            intersectionPoint = intersectionPoint + normal * 0.0001;
            resultIndex = index;
            result = true;
        }
    }
    return result;
}

// PHASE 2: Calculation of the radiance of the scene

Rayo specularReflectionRay(const Rayo& ray, const Direccion& wo, const Direccion& normal, const Punto& point) {
    // Calculate the new direction of the photon
    Direccion wi = ray.getDireccion() - (normal * (2 * (ray.getDireccion() * normal)));
    wi = wi.normalizar();

    // Send the new photon to the scene
    return Rayo(point, wi);
}


// Method to calculate the color of a pixel
Color PhotonMapping::calculatePixelColor(const Rayo& ray) const {
    // Calculate the intersection of the ray with all the objects of the scene
    Punto point = Punto(-INFINITY, -INFINITY, -INFINITY);
    Material material = Material();
    Direccion normal = Direccion(-INFINITY, -INFINITY, -INFINITY);
    int index = -1;
    bool intersects = intersectionRayScene(ray, material, point, normal, index);

    if (!intersects) {
        // There is no intersection
        cout << "There is no intersection (Camera)" << endl;
        return Color(0, 0, 0);
    }
    else {
        Componentes type = material.ruletaRusa();

        if (type == DIFUSO) {
            // Search for the nearest photons in a radius of radius_estimate
            vecPhotons nearest = search_nearest(map, Photon(point, Direccion(0, 0, 0), Color(0, 0, 0)));

            // Calculate the color of the pixel using the nearest photons
            Color color = Color(0, 0, 0);
            for (const Photon* photon : nearest) {
                //cout << "Near photon: " << photon->getPosition().x << " " << photon->getPosition().y << " " << photon->getPosition().z << endl;
                Color kernel = photon->getFlux();
                kernel /= (M_PI * radius_estimate * radius_estimate);

                Color BRDF = calculateDiffuseMaterial(material.getDifuso());

                color += kernel * BRDF;
            }

            return color;

        }
        else if (type == ESPECULAR) {
            Rayo ray = specularReflectionRay(ray, ray.getDireccion(), normal, point);
            calculatePixelColor(ray);
        }
        else if (type == REFRACCION) {
            // Direccion direccionRayoEntrante = refractedRay(wo, normal, material.getIndiceRefraccion());
            // if (direccionRayoEntrante.x == -INFINITY) {
            //     return Color(0, 0, 0);
            // }

            // // cout << "Direccion rayo original: " << wo.x << " " << wo.y << " " << wo.z << endl;
            // // cout << "Direccion del rayo entrante: " << direccionRayoEntrante.x << " " << direccionRayoEntrante.y << " " << direccionRayoEntrante.z << endl;

            // Direccion normalNegada = Direccion(-n.x, -n.y, -n.z);
            // Punto puntoInterseccionActualizado = puntoInterseccion + normalNegada * 0.0002;
            // // Lanzar un rayo a la escena
            // Rayo rayoEntrante = Rayo(puntoInterseccionActualizado, direccionRayoEntrante);

            // // Definir valores iniciales
            // float distancia = INFINITY;
            // Punto puntoInterseccionActual = Punto(-INFINITY, -INFINITY, -INFINITY);
            // Direccion normal = Direccion(-INFINITY, -INFINITY, -INFINITY);
            // int indice = -1;
            // Material basura = Material();
            // interseccionRayoEscena(rayoEntrante, puntoInterseccionActualizado, basura, puntoInterseccionActual, normal, indice);

            // Direccion direccionRayoSaliente = rayoRefraccion(direccionRayoEntrante, normal, material.getrefractiveIndex());
            // if (direccionRayoSaliente.x == -INFINITY) {
            //     return Color(0, 0, 0);
            // }

            // // cout << "Direccion del rayo saliente: " << direccionRayoSaliente.x << " " << direccionRayoSaliente.y << " " << direccionRayoSaliente.z << endl;

            // // Lanzar un rayo a la escena
            // Rayo rayoSaliente = Rayo(puntoInterseccionActual, direccionRayoSaliente);
            // Color color = calcularColorPixel(rayoSaliente, puntoInterseccionActual);
        }
        else if (type == ABSORCION) {
            // The light is absorbed so nothing is done
        }
        else {
            cout << "Error: tipo de material no reconocido" << endl;

        }

    }

    return Color(0, 0, 0);
}


#include "Terminal.h"
#include <string>


Terminal::Terminal(std::string _nom):
nom(_nom)
{
}

Terminal::Terminal(std::string _nom, double lat, double lng, double temps) :
latitude(lat), longitude(lng), temps_correspondance(temps), nom(_nom)
{
}

Terminal::~Terminal()
{
    std::cout << "destruction du Terminal " << this->getNom()<< std::endl;
    /*if(!liaisons.empty)
    {
      for(auto it = liaisons.begin; liaisons.end; it++)
      {
        delete (*it);
      }
    }
    liaisons.clear(); */
}
void Terminal::setLatitude(double lat) {
  this->latitude = lat;
}

void Terminal::setLongitude(double lng) {
  this->longitude = lng;
}

void Terminal::setTempsCorrespondance(double temps) {
  this->temps_correspondance = temps;
}

void Terminal::setNom(std::string _nom) {
  this->nom = _nom;
}

double Terminal::getLatitude() const{
  return latitude;
}

double Terminal::getLongitude() const{
  return longitude;
}

double Terminal::getTempsCorrespondance() const{
  return temps_correspondance;
}

int Terminal::getNbLiaisons() {
  return liaisons.size();
}

std::vector<Terminal*> Terminal::getLiasons() const{
  return liaisons;
}

std::string Terminal::getNom() {
  return nom;
}

 std::map<Terminal*, int> Terminal::getFlux() const{
      return flux;
  }



void Terminal::addFlux(Terminal* t, int n){
  // ajouter un flux
  try{
    if(t == NULL)
    {
      throw std::string ("Terminal NULL");
    }else{
      // verifier s'il existe et le mettre a jour
      auto it = flux.find(t);
      // si le terminal existe deja, on met a jour le flux
     if (it != flux.end())
       {
        it->second = n;
       }else{
         flux.insert(std::make_pair(t,n));
      }


    }
  }
  catch(std::string const& chaine)
  {
     std::cerr << chaine << std::endl;
  }

}

double Terminal::degree_to_radian(double d) const
{
  return (d * M_PI)/180;
}
double Terminal::distance(double lat, double lng) const{
    const double EARTH_RADIUS = 6371.0;
    double originLatR = degree_to_radian(this->latitude);
    double originLngR = degree_to_radian(this->longitude);
    double destinationLatR = degree_to_radian(lat);
    double destinationLngR = degree_to_radian(lng);
    double u = sinf((destinationLatR - originLatR) / 2);
    double v = sinf((destinationLngR - originLngR) / 2);
    return 2.0 * EARTH_RADIUS * asinf(sqrtf(u * u + cosf(originLatR) * cosf(destinationLatR) * v * v));
}

int Terminal::getNbFluxPassagers( Terminal *t) {

    for(std::map<Terminal* , int>::iterator it = flux.begin(); it != flux.end(); it++)
    {
      if(it->first->getNom().compare(t->getNom()) == 0)
      {
        return it->second;
      }
    }
    return 0;// si le terminal en paramètre n'est pas une destination finale des passagers;
}
void Terminal::afficher(){
  std::cout << "      Latitude: " << latitude << std::endl;
  std::cout << "      Longitude: " << longitude << std::endl;
  std::cout << "      Temps d'attente: " << temps_correspondance << std::endl;
  std::cout << "      Liaisons: (" << getNbLiaisons() << ")" << std::endl;
  for (std::vector<Terminal*>::iterator terminal = liaisons.begin(); terminal != liaisons.end(); ++terminal)
  {
    std::cout << "      "<<(*terminal)->getNom() << std::endl;
  }
  for(std::map<Terminal*, int>::iterator it = flux.begin(); it != flux.end(); it++)
  {
    std::cout << "      Passagers à destination de : " << it->first->getNom() << " flux: " << it->second << std::endl;
  }
}

bool Terminal::operator== (Terminal* t){
  std::cout << "operator ==" << std::endl;
  return (this->nom.compare(t->getNom()) == 0) && (this->latitude == t->getLatitude()) &&
  (this->longitude == t->getLongitude()) && (this->temps_correspondance == t->getTempsCorrespondance());
}

  bool Terminal::operator< (Terminal* t2 )const {
    return this->nom < t2->getNom();
  }

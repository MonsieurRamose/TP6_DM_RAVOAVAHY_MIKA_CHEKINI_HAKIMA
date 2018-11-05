#include "Terminal.h"


Terminal::Terminal(std::string _nom):
nom(_nom)
{
}

Terminal::Terminal(std::string _nom, double lat, double lng, double temps) :
latitude(lat), longitude(lng), temps_correspondance(temps), nom(_nom)
{
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

double Terminal::getLatitude() {
  return latitude;
}

double Terminal::getLongitude() {
  return longitude;
}

double Terminal::getTempsCorrespondance() {
  return temps_correspondance;
}

int Terminal::getNbLiaisons() {
  return liaisons.size();
}

std::string Terminal::getNom() {
  return nom;
}

double Terminal::distance(double lat, double lng) {
  return sqrt(pow((lat - this->latitude), 2) + pow((lng - this->longitude), 2));
}

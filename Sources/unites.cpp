#include "unites.h"

/* ********************************************************************************* */
/* ********************************************************************************* */
/*!
 * \class Unites
 * \brief Enumérés des différentes unités gérées par l'application.
 * \inmodule TiCalcul
 *
 * Pour chacune des unités, on a quelques infos utiles, telles que
 * la valeur max affichable dans l'appli, le ratio de conversion, etc.
 **/

Unites::Unites()
{}

/*!
  \variable Unites::usPerUnit
   \brief Nombre de microsecondes par unité.
*/

/*!
  \variable Unites::frameRate
   \brief Nombre d'unités par seconde.
*/

/*!
  \variable Unites::name
   \brief Nom de l'unité, utilisé par la reconnaissance logicielle entre C++ et QML.
*/

/*!
  \variable Unites::hint
   \brief Texte affiché en grisé dans l'afficheur QML, quand il n'y a pas de valeur.
*/

/*!
  \variable Unites::max
   \brief Valeur numérique maximale supportée par cette unité (plus ou moins 1000 jours).
*/
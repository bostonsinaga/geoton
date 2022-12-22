#ifndef __KML_PLACEMARK_CPP__
#define __KML_PLACEMARK_CPP__

#include "placemark.h"

void Placemark::pinsPath(
    xml::Node *kmlNode,
    std::vector<xml::Node*> &sortedPinNodes
) {
    Builder builderKML;

    std::string styleMapId;
    builderKML.insertStyleMap(
        kmlNode,
        builderKML.getPathStyleMap(&styleMapId)
    );

    std::vector<std::string> coorStrVec;
    for (auto &pinNode : sortedPinNodes) {
        coorStrVec.push_back(
            pinNode->getFirstDescendantByName("coordinates")->getInnerText()
        );
    }

    std::vector<xml::Node*> pathNodes {builderKML.getPath(
        builderKML.COORSTR_NO_ADD_ALTITUDE,
        styleMapId,
        coorStrVec,
        "Path of Selected Pins",
        "Created with KML-TOWN"
    )};

    General kmlGeneral;

    kmlGeneral.insertEditedPlacemarksIntoFolder(
        kmlGeneral.searchMainFolder(kmlNode),
        Builder().getFolder(PINS_PATH_COMMAND_WORKING_FOLDER),
        pathNodes,
        {"Pins-path unifying", "Pins-path unify"},
        ""
    );
}

#endif // __KML_PLACEMARK_CPP__

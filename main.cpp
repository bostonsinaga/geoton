#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <functional>
#include <algorithm>

#define X 0
#define Y 1

/* degree sign input in literal (°) reformatted with 2 characters */
#define DEG_INT_CHAR_PT1 -62 // normal degree sign
#define DEG_INT_CHAR_PT2 -80 // ...

/*
    degree sign anomaly may appear when
    receiving degree coordinate parameter from '.bat' or '.sh' file
*/
#define ANM_DEG_INT_CHAR_PT1 45 // anomaly degree sign
#define ANM_DEG_INT_CHAR_PT2 166 // ...

#include "mini-tool.cpp"
#include "menu.cpp"
#include "tools/xml/xml.h"
#include "tools/kml/kml.h"
#include "tools/txt/txt.h"
#include "tools/csv/csv.h"
#include "call-briefer.cpp"

int main(int argc, char *argv[]) {

    // convert 'argv' to vector start from index 1
    std::vector<std::string> inputStrings;
    for (int i = 1; i < argc; i++) {
        inputStrings.push_back(argv[i]);
    }

    ////////////////////////
    //// MENU SELECTION ////
    ////////////////////////

    Menu menu = Menu(&inputStrings);

    // make row space under the command in CLI
    std::cout << std::endl;

    int SELECTED_FLAG = menu.select();

    /////////////////////
    // MAIN MENU FLAGS //
    /////////////////////

    if (SELECTED_FLAG == MAIN_MENU_FLAG ||
        SELECTED_FLAG == HELP_MENU_FLAG
    ) {
        menu.displayAvailableCommands();
    }
    else if (SELECTED_FLAG == VERSION_NUMBER_FLAG) {
        menu.displayVersionNumber();
    }

    //////////////////////////
    // CONVERT TXT KML FLAG //
    //////////////////////////
    
    else if (SELECTED_FLAG == CONVERT_TXT_KML_FLAG) {

        std::string
            type_paramStr = menu.getParameterString("type"),
            fileIn_paramStr = menu.getParameterString("txt-in"),
            fileOut_paramStr = menu.getParameterString("kml-out");

        xml::Node *kmlNode = call_briefer::selectFunctionByType(
            type_paramStr,
            {"pin", "path"},
            {
                [&]()->xml::Node* {return txt::Scanner().parsePins(
                    fileIn_paramStr, fileOut_paramStr
                );},
                [&]()->xml::Node* {
                    std::cout << "KML-TOWN-> Parsing 'pins'..\n";

                    xml::Node *kmlNode_baby = txt::Scanner().parsePins(
                        fileIn_paramStr, fileOut_paramStr
                    );

                    if (kmlNode_baby) {
                        // from south west - north east
                        std::string selectCoorStr[2] = {
                            "90°0'0.0S 180°0'0.0W", "90°0'0.0N 180°0'0.0E"
                        };

                        std::vector<xml::Node*> selectedPinNodes;

                        if (mini_tool::isStringContains(type_paramStr, "sort", true)) {

                            // using sorter
                            std::cout << "KML-TOWN-> Sorting 'pins'..\n";

                            selectedPinNodes = call_briefer::sortPinsFunc(
                                menu,
                                kmlNode_baby,
                                {&selectCoorStr[0], &selectCoorStr[1]},
                                false
                            );
                        }
                        else {
                            selectedPinNodes = call_briefer::cropPinsFunc(
                                kmlNode_baby,
                                {&selectCoorStr[0], &selectCoorStr[1]},
                                false
                            );
                        }

                        if (selectedPinNodes.size() > 0) {
                            std::cout << "KML-TOWN-> Create 'path' segments..\n";

                            kml::Placemark().pinsPathSegments(
                                kmlNode_baby,
                                selectedPinNodes,
                                true
                            );
                        }
                    }

                    return kmlNode_baby;
                }
            }
        );

        call_briefer::writeFileFunc(kmlNode, fileOut_paramStr);
    }

    //////////////////////////
    // CONVERT KML CSV FLAG //
    //////////////////////////

    else if (SELECTED_FLAG == CONVERT_KML_CSV_FLAG) {

        std::string
            fileIn_paramStr = menu.getParameterString("kml-in"),
            fileOut_paramStr = menu.getParameterString("csv-out");

        xml::Reader kmlReader;
        xml::Node *kmlNode = kmlReader.fileParse(fileIn_paramStr);

        if (kmlNode) {
            std::string separatorSign = "|";

            menu.setNotification(
                std::string("\nCSV-> Consider to set column/folder name as 'PATH', 'PATHS' or 'JALUR'\n") +
                std::string("      to generate path column format\n")
            );

            if (menu.setAlert(
                "CSV-> Do you want to change columns separator? (default is '|')\n",
                false
            )) {
                csv::singleCharacterInputNotify(menu, false);
                std::string additionalInput = menu.setAdditionalInput(
                    "CSV-> Set columns separator sign:  "
                );
                separatorSign = additionalInput;
            }

            xml::Node *mainFolderNode = kml::General().searchMainFolder(kmlNode);

            if (mainFolderNode) {
                csv::Builder csvBuilder;
                if (csvBuilder.compose(fileOut_paramStr, mainFolderNode, separatorSign)) {
                    std::cout << "\n**SUCCEEDED**\n";
                }
            }
            else std::cerr << "\n**FAILED**\n";

            delete kmlNode;
        }
        else std::cerr
            << "KML-TOWN-> Error. '"
            << fileIn_paramStr
            << "' not found or empty\n"
            << "\n**FAILED**\n";
    }

    //////////////
    // KML CROP //
    //////////////
    
    else if (SELECTED_FLAG == KML_CROP_FLAG) {

        std::string
            fileIn_paramStr = menu.getParameterString("crop"),
            fileOut_paramStr = menu.getParameterString("out"),
            startPoint_paramStr = menu.getParameterString("start-point"),
            endPoint_paramStr = menu.getParameterString("end-point");
        
        kml::Cropper().printNotification(menu);

        std::string fileDir_check = call_briefer::checkOverwrite(
            menu,
            fileIn_paramStr,
            fileOut_paramStr
        );

        if (fileDir_check != "") {
            xml::Reader kmlReader;
            xml::Node *kmlNode = kmlReader.fileParse(fileIn_paramStr);

            if (call_briefer::cropPinsFunc(
                kmlNode,
                {&startPoint_paramStr, &endPoint_paramStr},
                true
            ).size() > 0) {
                call_briefer::writeFileFunc(kmlNode, fileDir_check);
            }
        }
    }

    //////////////
    // KML SORT //
    //////////////

    else if (SELECTED_FLAG == KML_SORT_FLAG) {

        std::string
            fileIn_paramStr = menu.getParameterString("sort"),
            fileOut_paramStr = menu.getParameterString("out"),
            startPoint_paramStr = menu.getParameterString("start-point"),
            endPoint_paramStr = menu.getParameterString("end-point");

        kml::Cropper().printNotification(menu);
        kml::Sorter().printNotification(menu);

        std::string fileDir_check = call_briefer::checkOverwrite(
            menu,
            fileIn_paramStr,
            fileOut_paramStr
        );
        
        if (fileDir_check != "") {
            xml::Reader kmlReader;
            xml::Node *kmlNode = kmlReader.fileParse(fileIn_paramStr);

            if (call_briefer::sortPinsFunc(
                menu,
                kmlNode,
                {&startPoint_paramStr, &endPoint_paramStr},
                true
            ).size() > 0) {
                call_briefer::writeFileFunc(kmlNode, fileDir_check);
            }
        }
    }

    //////////////////////
    // KML PINS TO PATH //
    //////////////////////

    else if (SELECTED_FLAG == KML_PINS_PATH_FLAG) {

        std::string
            fileIn_paramStr = menu.getParameterString("pins-path"),
            fileOut_paramStr = menu.getParameterString("out"),
            startPoint_paramStr = menu.getParameterString("start-point"),
            endPoint_paramStr = menu.getParameterString("end-point");
        
        kml::Cropper().printNotification(menu);
        kml::Sorter().printNotification(menu);

        std::string fileDir_check = call_briefer::checkOverwrite(
            menu,
            fileIn_paramStr,
            fileOut_paramStr
        );
        
        if (fileDir_check != "") {
            xml::Reader kmlReader;
            xml::Node *kmlNode = kmlReader.fileParse(fileIn_paramStr);

            std::vector<xml::Node*> sortedPinNodes = call_briefer::sortPinsFunc(
                menu,
                kmlNode,
                {&startPoint_paramStr, &endPoint_paramStr},
                false
            );

            if (sortedPinNodes.size() > 0) {
                kml::Placemark().pinsPath(
                    kmlNode,
                    sortedPinNodes
                );
                call_briefer::writeFileFunc(kmlNode, fileDir_check);
            }
        }
    }

    /////////////////////
    // KML TWINS CHECK //
    /////////////////////

    else if (SELECTED_FLAG == KML_TWINS_CHECK_FLAG) {

        std::string
            fileIn_paramStr = menu.getParameterString("twins-check"),
            fileOut_paramStr = menu.getParameterString("out"),
            type_paramStr = menu.getParameterString("type"),
            radius_paramStr = menu.getParameterString("radius");

        bool includeFolders_toggleBool = menu.isToggleExist("include-folders");

        std::string fileDir_check = call_briefer::checkOverwrite(
            menu,
            fileIn_paramStr,
            fileOut_paramStr
        );
        
        if (fileDir_check != "") {
            xml::Reader kmlReader;

            xml::Node
                *kmlNode = kmlReader.fileParse(fileIn_paramStr),
                *twinsCheckedFolder;

            // invers ignore style
            bool isOnlySimilarStyle = !mini_tool::isStringContains(type_paramStr, "ignore", true);

            // if not ignore style, not necessarily a similar style check
            if (isOnlySimilarStyle) {
                isOnlySimilarStyle = mini_tool::isStringContains(type_paramStr, "style", true);
            }

            if (kmlNode) {

                twinsCheckedFolder = call_briefer::selectFunctionByType(
                    type_paramStr,
                    {"pin", "path", "all"},
                    {
                        [=]()->xml::Node* {
                            return kml::TwinsChecker().findPins(
                                kmlNode, radius_paramStr, false, includeFolders_toggleBool, isOnlySimilarStyle
                            );
                        },
                        [=]()->xml::Node* {
                            return kml::TwinsChecker().findPaths(
                                kmlNode, radius_paramStr, false, includeFolders_toggleBool, isOnlySimilarStyle
                            );
                        },
                        [=]()->xml::Node* {
                            return kml::TwinsChecker().findAll(
                                kmlNode, radius_paramStr, includeFolders_toggleBool, isOnlySimilarStyle
                            );
                        }
                    }
                );

                if (twinsCheckedFolder) {
                    call_briefer::writeFileFunc(kmlNode, fileDir_check);
                }
                else {
                    delete kmlNode;
                    std::cerr << "\n**FAILED**\n";
                }
            }
            else std::cerr << "\n**FAILED**\n";
        }
    }

    ///////////////////////
    // KML MEASURE PATHS //
    ///////////////////////

    else if (SELECTED_FLAG == KML_MEASURE_PATHS_FLAG) {

        std::string
            fileIn_paramStr = menu.getParameterString("measure-paths"),
            fileOut_paramStr = menu.getParameterString("out");
        
        bool info_toggleBool = menu.isToggleExist("info");

        std::string fileDir_check = "";

        if (!info_toggleBool) {
            fileDir_check = call_briefer::checkOverwrite(
                menu,
                fileIn_paramStr,
                fileOut_paramStr
            );
        }
        
        if (fileDir_check != "" || info_toggleBool) {
            xml::Reader kmlReader;
            xml::Node *kmlNode = kmlReader.fileParse(fileIn_paramStr);

            if (kmlNode) {
                if (kml::Placemark().setPathDistance(
                    kmlNode,
                    info_toggleBool
                )) {
                    if (!info_toggleBool) {
                        call_briefer::writeFileFunc(kmlNode, fileDir_check);
                    }
                    else {
                        delete kmlNode;
                        std::cout << "\n**SUCCEEDED**\n";
                    }
                }
                else {
                    delete kmlNode;
                    std::cerr << "\n**FAILED**\n";
                }
            }
            else std::cerr << "\n**FAILED**\n";
        }
    }

    ////////////////////
    // KML CLASSIFIER //
    ////////////////////

    else if (SELECTED_FLAG == KML_CLASSIFY_FLAG) {

        std::string
            fileIn_paramStr = menu.getParameterString("classify"),
            fileOut_paramStr = menu.getParameterString("out");

        bool cleanFolders_toggleBool = menu.isToggleExist("clean-folders"),
             includeFolders_toggleBool = menu.isToggleExist("include-folders");

        std::string fileDir_check = call_briefer::checkOverwrite(
            menu,
            fileIn_paramStr,
            fileOut_paramStr
        );
        
        if (fileDir_check != "") {
            xml::Reader kmlReader;
            xml::Node *kmlNode = kmlReader.fileParse(fileIn_paramStr);

            bool isProceed = false;

            if ((cleanFolders_toggleBool &&
                menu.setAlert(
                    std::string("KML-> Classify warning. This will remove empty or previous folders.\n") +
                    std::string("      Keep proceeding?\n")
                )) ||
                !cleanFolders_toggleBool
            ) {
                isProceed = true;
            }
            
            if (isProceed && kmlNode) {
                kml::Classifier().rearrange(kmlNode, cleanFolders_toggleBool, includeFolders_toggleBool);
                call_briefer::writeFileFunc(kmlNode, fileDir_check);
            }
            else if (
                (!cleanFolders_toggleBool && !kmlNode) ||
                (isProceed && !kmlNode)
            ) {
                std::cerr << "\n**FAILED**\n";
            }
        }
    }

    ////////////////////////
    // KML FOLDER BY DATE //
    ////////////////////////

    else if (SELECTED_FLAG == KML_FOLDER_BY_DATE_FLAG) {

        std::string
            fileIn_paramStr = menu.getParameterString("folder-by-date"),
            fileOut_paramStr = menu.getParameterString("out");

        std::string fileDir_check = call_briefer::checkOverwrite(
            menu,
            fileIn_paramStr,
            fileOut_paramStr
        );
        
        if (fileDir_check != "") {
            xml::Reader kmlReader;
            xml::Node *kmlNode = kmlReader.fileParse(fileIn_paramStr);
            
            kml::DateFolder().packNumeral(kmlNode);
            call_briefer::writeFileFunc(kmlNode, fileDir_check);
        }
    }

    ///////////////////////
    // KML FILTER STRING //
    ///////////////////////

    else if (SELECTED_FLAG == KML_FILTER_STRING_FLAG) {

        std::string
            fileIn_paramStr = menu.getParameterString("filter-string"),
            fileOut_paramStr = menu.getParameterString("out"),
            text_paramStr = menu.getParameterString("text");

        std::string fileDir_check = call_briefer::checkOverwrite(
            menu,
            fileIn_paramStr,
            fileOut_paramStr
        );
        
        if (fileDir_check != "") {
            xml::Reader kmlReader;
            xml::Node *kmlNode = kmlReader.fileParse(fileIn_paramStr);
            
            if (kml::Classifier().filterString(kmlNode, text_paramStr)) {
                call_briefer::writeFileFunc(kmlNode, fileDir_check);
            }
            else std::cerr << "\n**FAILED**\n";
        }
    }

    //////////////////////
    // KML REMOVE PATHS //
    //////////////////////

    else if (SELECTED_FLAG == KML_REMOVE_PATHS_FLAG) {

        std::string
            fileIn_paramStr = menu.getParameterString("remove-paths"),
            fileOut_paramStr = menu.getParameterString("out"),
            distance_paramStr;

        // expected integer are '1' or '2'
        int isOver_oppositeCode = menu.checkOppositeParameterString(
            "over-distance", "under-distance", &distance_paramStr
        );

        // directly end
        if (isOver_oppositeCode == 0) {
            std::cerr << "\n**FAILED**\n";
            return 0;
        }

        std::string fileDir_check = call_briefer::checkOverwrite(
            menu,
            fileIn_paramStr,
            fileOut_paramStr
        );
        
        if (fileDir_check != "") {
            xml::Reader kmlReader;
            xml::Node *kmlNode = kmlReader.fileParse(fileIn_paramStr);

            kml::Placemark().removePathsByDistance(
                kmlNode,
                mini_tool::filterStringDecimal(distance_paramStr),
                isOver_oppositeCode
            );

            call_briefer::writeFileFunc(kmlNode, fileDir_check);
        }
    }

    //////////////////////////
    // CSV CHANGE SEPARATOR //
    //////////////////////////

    else if (SELECTED_FLAG == CSV_CHANGE_SEPARATOR_FLAG) {

        std::string
            fileIn_paramStr = menu.getParameterString("change-separator"),
            fileOut_paramStr = menu.getParameterString("out"),
            oldSign_paramStr = menu.getParameterString("old-sign"),
            newSign_paramStr = menu.getParameterString("new-sign");

        std::string fileDir_check = call_briefer::checkOverwrite(
            menu,
            fileIn_paramStr,
            fileOut_paramStr
        );
        
        if (fileDir_check != "") {
            csv::singleCharacterInputNotify(menu, true);

            csv::changeCSVSeparator(
                fileIn_paramStr,
                fileDir_check,
                oldSign_paramStr,
                newSign_paramStr
            );
        }
    }
    
    return 0;
}
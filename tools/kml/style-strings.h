#ifndef __KML_STYLE_STRINGS_H__
#define __KML_STYLE_STRINGS_H__

class StyleStrings {
    private:
        static const int pinIconUrlArray_count = 170;

    public:
        enum {
            PUSHPIN_PIN_TYPE_FLAG,
            PADDLE_PIN_TYPE_FLAG,
            SHAPES_PIN_TYPE_FLAG
        };

        std::string
            googleMapLink = "http://maps.google.com/mapfiles/kml/",
            mapLinkPushpin = googleMapLink + "pushpin/",
            mapLinkPaddle = googleMapLink + "paddle/",
            mapLinkShapes = googleMapLink + "shapes/";

        std::string pinIconUrlArray[pinIconUrlArray_count] = {

            ///////////////
            // PUSH PINS //
            ///////////////

            mapLinkPushpin + "ylw-pushpin.png",
            mapLinkPushpin + "blue-pushpin.png",
            mapLinkPushpin + "grn-pushpin.png",
            mapLinkPushpin + "ltblu-pushpin.png",
            mapLinkPushpin + "pink-pushpin.png",
            mapLinkPushpin + "purple-pushpin.png",
            mapLinkPushpin + "red-pushpin.png",
            mapLinkPushpin + "wht-pushpin.png",

            /////////////
            // PADDLES //
            /////////////

            mapLinkPaddle + "A.png",
            mapLinkPaddle + "B.png",
            mapLinkPaddle + "C.png",
            mapLinkPaddle + "D.png",
            mapLinkPaddle + "E.png",
            mapLinkPaddle + "F.png",
            mapLinkPaddle + "G.png",
            mapLinkPaddle + "H.png",
            mapLinkPaddle + "I.png",
            mapLinkPaddle + "J.png",
            mapLinkPaddle + "K.png",
            mapLinkPaddle + "L.png",
            mapLinkPaddle + "M.png",
            mapLinkPaddle + "N.png",
            mapLinkPaddle + "O.png",
            mapLinkPaddle + "P.png",
            mapLinkPaddle + "Q.png",
            mapLinkPaddle + "R.png",
            mapLinkPaddle + "S.png",
            mapLinkPaddle + "T.png",
            mapLinkPaddle + "U.png",
            mapLinkPaddle + "V.png",
            mapLinkPaddle + "W.png",
            mapLinkPaddle + "X.png",
            mapLinkPaddle + "Y.png",
            mapLinkPaddle + "Z.png",
            mapLinkPaddle + "1.png",
            mapLinkPaddle + "2.png",
            mapLinkPaddle + "3.png",
            mapLinkPaddle + "4.png",
            mapLinkPaddle + "5.png",
            mapLinkPaddle + "6.png",
            mapLinkPaddle + "7.png",
            mapLinkPaddle + "8.png",
            mapLinkPaddle + "9.png",
            mapLinkPaddle + "10.png",
            mapLinkPaddle + "blu-blank.png",
            mapLinkPaddle + "blu-diamond.png",
            mapLinkPaddle + "blu-circle.png",
            mapLinkPaddle + "blu-square.png",
            mapLinkPaddle + "blu-stars.png",
            mapLinkPaddle + "grn-blank.png",
            mapLinkPaddle + "grn-diamond.png",
            mapLinkPaddle + "grn-circle.png",
            mapLinkPaddle + "grn-square.png",
            mapLinkPaddle + "grn-stars.png",
            mapLinkPaddle + "ltblu-blank.png",
            mapLinkPaddle + "ltblu-diamond.png",
            mapLinkPaddle + "ltblu-circle.png",
            mapLinkPaddle + "ltblu-square.png",
            mapLinkPaddle + "ltblu-stars.png",
            mapLinkPaddle + "pink-blank.png",
            mapLinkPaddle + "pink-diamond.png",
            mapLinkPaddle + "pink-circle.png",
            mapLinkPaddle + "pink-square.png",
            mapLinkPaddle + "pink-stars.png",
            mapLinkPaddle + "ylw-blank.png",
            mapLinkPaddle + "ylw-diamond.png",
            mapLinkPaddle + "ylw-circle.png",
            mapLinkPaddle + "ylw-square.png",
            mapLinkPaddle + "ylw-stars.png",
            mapLinkPaddle + "wht-blank.png",
            mapLinkPaddle + "wht-diamond.png",
            mapLinkPaddle + "wht-circle.png",
            mapLinkPaddle + "wht-square.png",
            mapLinkPaddle + "wht-stars.png",
            mapLinkPaddle + "red-blank.png",
            mapLinkPaddle + "red-diamond.png",
            mapLinkPaddle + "red-circle.png",
            mapLinkPaddle + "red-square.png",
            mapLinkPaddle + "red-stars.png",
            mapLinkPaddle + "purple-blank.png",
            mapLinkPaddle + "purple-diamond.png",
            mapLinkPaddle + "purple-circle.png",
            mapLinkPaddle + "purple-square.png",
            mapLinkPaddle + "purple-stars.png",

            ////////////
            // SHAPES //
            ////////////

            mapLinkShapes + "arrow-reverse.png",
            mapLinkShapes + "arrow.png",
            mapLinkShapes + "track.png",
            mapLinkShapes + "donut.png",
            mapLinkShapes + "forbidden.png",
            mapLinkShapes + "info-i.png",
            mapLinkShapes + "polygon.png",
            mapLinkShapes + "open-diamond.png",
            mapLinkShapes + "square.png",
            mapLinkShapes + "star.png",
            mapLinkShapes + "target.png",
            mapLinkShapes + "triangle.png",
            mapLinkShapes + "cross-hairs.png",
            mapLinkShapes + "placemark_square.png",
            mapLinkShapes + "placemark_circle.png",
            mapLinkShapes + "shaded_dot.png",
            mapLinkShapes + "dining.png",
            mapLinkShapes + "coffee.png",
            mapLinkShapes + "bars.png",
            mapLinkShapes + "snack_bar.png",
            mapLinkShapes + "man.png",
            mapLinkShapes + "woman.png",
            mapLinkShapes + "wheel_chair_accessible.png",
            mapLinkShapes + "parking_lot.png",
            mapLinkShapes + "cabs.png",
            mapLinkShapes + "bus.png",
            mapLinkShapes + "truck.png",
            mapLinkShapes + "rail.png",
            mapLinkShapes + "airports.png",
            mapLinkShapes + "ferry.png",
            mapLinkShapes + "heliport.png",
            mapLinkShapes + "subway.png",
            mapLinkShapes + "tram.png",
            mapLinkShapes + "info.png",
            mapLinkShapes + "info_circle.png",
            mapLinkShapes + "flag.png",
            mapLinkShapes + "rainy.png",
            mapLinkShapes + "water.png",
            mapLinkShapes + "snowflake_simple.png",
            mapLinkShapes + "marina.png",
            mapLinkShapes + "fishing.png",
            mapLinkShapes + "sailing.png",
            mapLinkShapes + "swimming.png",
            mapLinkShapes + "ski.png",
            mapLinkShapes + "parks.png",
            mapLinkShapes + "campfire.png",
            mapLinkShapes + "picnic.png",
            mapLinkShapes + "campground.png",
            mapLinkShapes + "ranger_station.png",
            mapLinkShapes + "toilets.png",
            mapLinkShapes + "poi.png",
            mapLinkShapes + "hiker.png",
            mapLinkShapes + "cycling.png",
            mapLinkShapes + "motorcycling.png",
            mapLinkShapes + "horsebackriding.png",
            mapLinkShapes + "play.png",
            mapLinkShapes + "golf.png",
            mapLinkShapes + "trail.png",
            mapLinkShapes + "shopping.png",
            mapLinkShapes + "movies.png",
            mapLinkShapes + "convenience.png",
            mapLinkShapes + "grocery.png",
            mapLinkShapes + "arts.png",
            mapLinkShapes + "homegardenbusiness.png",
            mapLinkShapes + "electronics.png",
            mapLinkShapes + "mechanic.png",
            mapLinkShapes + "gas_stations.png",
            mapLinkShapes + "realestate.png",
            mapLinkShapes + "salon.png",
            mapLinkShapes + "dollar.png",
            mapLinkShapes + "euro.png",
            mapLinkShapes + "yen.png",
            mapLinkShapes + "firedept.png",
            mapLinkShapes + "hospitals.png",
            mapLinkShapes + "lodging.png",
            mapLinkShapes + "phone.png",
            mapLinkShapes + "caution.png",
            mapLinkShapes + "earthquake.png",
            mapLinkShapes + "falling_rocks.png",
            mapLinkShapes + "post_office.png",
            mapLinkShapes + "police.png",
            mapLinkShapes + "sunny.png",
            mapLinkShapes + "partly_cloudy.png",
            mapLinkShapes + "volcano.png",
            mapLinkShapes + "camera.png",
            mapLinkShapes + "webcam.png"
        };

        int getPinIconNamedIndex(std::string &pinIconNamed) {
            for (int i = 0;
                i < sizeof(pinIconUrlArray) / sizeof(std::string);
                i++
            ) {
                if (pinIconUrlArray[i].find(pinIconNamed) != std::string::npos) {
                    return i;
                }
            }
            return -1;
        }

        std::string getPinIconNamedUrl(std::string &pinIconNamed) {
            int index = getPinIconNamedIndex(pinIconNamed);
            if (index != -1) {
                return pinIconUrlArray[index];
            }
            return "";
        }

        int getPinTyleFlag(std::string &pinIconNamed) {
            std::string url = getPinIconNamedUrl(pinIconNamed);

            if (url != "") {
                
                if (url.find("/pushpin/") != std::string::npos) {
                    return PUSHPIN_PIN_TYPE_FLAG;
                }
                else if (url.find("/paddle/") != std::string::npos) {
                    return PADDLE_PIN_TYPE_FLAG;
                }
                else if (url.find("/shapes/") != std::string::npos) {
                    return SHAPES_PIN_TYPE_FLAG;
                }
            }
            return -1;
        }

        // identify if an icon
        bool isAnIconName(std::string &pinIconNamed) {
            for (int i = 0; i < pinIconUrlArray_count; i++) {
                if (pinIconNamed == pinIconUrlArray[i]) {
                    return true;
                }
            }
            return false;
        }

        // path's color codes from name
        std::string getPathColorCode(std::string pathColorNamed) {
            if (pathColorNamed == "red") {
                return "ff0000ff";
            }
            else if (pathColorNamed == "yellow") {
                return "ff00ffff";
            }
            else if (pathColorNamed == "magenta") {
                return "ffff00ff";
            }
            else if (pathColorNamed == "chocolate") {
                return "ff385294";
            }
            else if (pathColorNamed == "green") {
                return "ff00ff00";
            }
            else if (pathColorNamed == "orange") {
                return "ff007fff";
            }
            else if (pathColorNamed == "purple") {
                return "ffbf007f";
            }
            else if (pathColorNamed == "white") {
                return "ffffffff";
            }
            else if (pathColorNamed == "blue") {
                return "ffff0000";
            }
            else if (pathColorNamed == "cyan") {
                return "ffffff00";
            }
            else if (pathColorNamed == "black") {
                return "ff000000";
            }
            else if (pathColorNamed == "gray") {
                return "ff7f7f7f";
            }
            else return "ffffffff";
            return "";
        }
};

#endif // __KML_STYLE_STRINGS_H__
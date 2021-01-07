#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include "../Color/Color.hpp"
#include "../Camera/Camera.hpp"
#include "../Light/Light.hpp"
#include "../Vector/Vector.hpp"
#include "../Light/DirectedLight/DirectedLight.hpp"
#include "../PixelWithData/PixelWithData.hpp"

using namespace std;

class Scene {
    private:
        //Camera
        Camera camera;
        //Lights
        Light ambientLight;
        vector<DirectedLight> directedLights;
        //Pixels
        vector<PixelWithData *> pixelsToDraw;
    public:
        Scene() { };
        //Setters and getters
        void setCamera(Camera camera) {
            this->camera = camera;
        };
        void setCameraPosition(Vector *position) {
            camera.setPosition(position);
        };
        void setCameraFocalLength(double focalLength) {
            camera.setFocalLength(focalLength);
        };
        void setAmbientLight(Light ambientLight) {
            this->ambientLight = ambientLight;
        };
        void setAmbientLightColor(Color lightColor) {
            ambientLight.setLightColor(lightColor);
        }
        void setAmbientLightColor(unsigned char r, unsigned char g, unsigned char b) {
            ambientLight.setLightColor(r, g, b);
        };
        void setPixelsToDraw(vector<PixelWithData*> pixelsToDraw) {
            this->pixelsToDraw = pixelsToDraw;
        }
        Camera getCamera() {
            return camera;
        };
        Light getAmbienLight() {
            return ambientLight;
        };
        vector<PixelWithData *> getPixelsToDraw() {
            return pixelsToDraw;
        };
        //Light helpers
        void addDirectedLight(DirectedLight lightToAdd) {
            directedLights.push_back(lightToAdd);
        };
        vector<DirectedLight> getDirectedLights() {
            return directedLights;
        };
        void computePixelsColors() {
            vector<PixelWithData *> pixelsWithFinalColor;
            for(PixelWithData *currentPixel : pixelsToDraw) {
                Color pixelFinalColor = getPixelColor(currentPixel);
                PixelWithData *pixelWithFinalColor = new PixelWithData(
                    pixelFinalColor,
                    currentPixel->get3DSpaceCoordinates()
                );
                pixelsWithFinalColor.push_back(pixelWithFinalColor);
            }
            pixelsToDraw.clear();
            pixelsToDraw = pixelsWithFinalColor;
        }
        Color getPixelColor(PixelWithData *pixelData) {
            Color pixelFinalColor;
            //Pixel initial color
            Color pixelInitialColor = pixelData->getPixelColor();
            //Color from ambient light
            Color ambientLightColor = ambientLight.getLightColor();
            //Color from directed lights
            Color directedLightColor(0, 0, 0);
            for(DirectedLight currentDirectedLight : directedLights) {
                double distanceToPixel = pixelData->get3DSpaceCoordinates()->getDistanceTo(currentDirectedLight.getPosition());
                double attenuationFactor = currentDirectedLight.getLightIntensity(distanceToPixel);
                Color currentDirectedLightColor = (currentDirectedLight * attenuationFactor).getLightColor();
                //We add the current directed light color to the accumulated value
                directedLightColor = directedLightColor + currentDirectedLightColor;
            }
            //Color from spot lights
            //Color from specular lights
            pixelFinalColor = pixelInitialColor + ambientLightColor + directedLightColor;
            return pixelFinalColor;
        };
};

#endif
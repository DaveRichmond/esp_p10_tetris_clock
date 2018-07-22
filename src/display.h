#pragma once

#include <Adafruit_GFX.h>    // Core graphics library

#include <cstdint>
#include <memory>
#include <vector>

class DisplayEmulator {
public:
    DisplayEmulator(const int width, const int height)
        : _w(width), _h(height), 
          front_buffer(new std::vector<uint16_t>(width * height)),
          back_buffer(new std::vector<uint16_t>(width * height)){

          }
    void setTFT(std::shared_ptr<Adafruit_GFX> tft){
        this->tft = tft;
    }
    void drawPixel(int x, int y, uint16_t colour){
        if(x >= 0 && x < width()){
            if(y >= 0 && y < height()){
                (*front_buffer)[pos(x,y)] = colour;
            }
        }
    }
    void clear(void){
        // clear front buffer
        for(auto i = 0; i < front_buffer->size(); i++){
            (*front_buffer)[i] = color565(0,0,0);
        }
    }
    void swap(void){
        // swap front and back buffer
        std::swap(front_buffer, back_buffer);
    }
    void sync(void){
        int start = millis();
        for(int y = 0; y < height(); y++){
            for(int x = 0; x < width(); x++){
                auto new_pixel = (*front_buffer)[pos(x,y)];
                auto old_pixel = (*back_buffer)[pos(x,y)];
                if(new_pixel != old_pixel){
                    tft.get()->drawPixel(x, y, new_pixel);
                }
            }
        }
        Serial.println("Sync time: " + String(millis() - start) + "ms");
    }
    int width() const {
        return _w;
    }
    int height() const {
        return _h;
    }

    // text fucntions, just pass through to tft (with scaling?)
    void setTextColor(uint16_t colour){
        tft.get()->setTextColor(colour);
    }
    void setCursor(int x, int y){
        tft.get()->setCursor(x, y);
    }
    void print(String c){
        tft.get()->print(c);
    }
    uint16_t color565(uint8_t r, uint8_t g, uint8_t b){
        // FUXNE: the adafruit gfx lib should expose this interface, 
        // each tft seems to implement it, but because we're only dealing
        // with the gfx api, we can't access it :()
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
    }
private:
    int pos(int x, int y) const {
        return x + (width() * y);
    }
    const int _w, _h;
    std::vector<uint16_t> *front_buffer;
    std::vector<uint16_t> *back_buffer;
    std::shared_ptr<Adafruit_GFX> tft;
};
//
//  line.h
//  basicApp
//
//  Created by Yuki ANAI on 8/23/15.
//
//

#ifndef basicApp_line_h
#define basicApp_line_h

#include "hrfm.h"

class Line : public hrfm::display::DisplayNode {
public:
    Line() : hrfm::display::DisplayNode() {
        x = 160;
        y = 240;
        mPoints.push_back(Vec2f(x, y));

        //ci::gl::lineWidth(10.0);
        //ci::gl::glow(10);
    }

protected:
    vector<Vec2f>	mPoints;
    int direction = 1;
    float angle = 90.0;
    float velocity = 10.0;

    virtual void _draw() {
        if (mPoints.size() > 1) {
            //ci::gl::drawLine( mPoints.at(mPoints.size() - 2), mPoints.at(mPoints.size() - 1));
            for(int i = 1; i < mPoints.size(); i++) {
                ci::gl::drawLine(mPoints.at(i - 1), mPoints.at(i));
                
                //cout << mPoints.at(i - 1) << " /// " << mPoints.at(i) << endl;
            }
        }
        //ci::gl::drawLine(Vec2f(x, y), Vec2f(x + 100, y + 100));
        //ci::gl::drawSolidRect(Rectf(x, y, x + 100, y + 100));
    }
    
    virtual void _update() {
        angle = ci::Rand::randFloat(360);
        float radians = (angle * pi) / 180;
        x += velocity * cos(radians);
        y += velocity * sin(radians);
        
        velocity -= 0.01;
        if (velocity <= 0.0) {
            velocity = 0.0;
        }
        else {
            Vec2f vec = Vec2f(x, y);
            mPoints.push_back(vec);
        }

        //cout << "x: " << x << ", y:" << y << ", angle: " << angle << ", velocity: " << velocity << endl;
    }
};

#endif

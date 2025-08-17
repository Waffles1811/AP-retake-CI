#include "concreteCamera.h"


void repr::concreteCamera::updateCoords(const float _x, const float _y) {
    model->updatePosition(_x, -_y);
}

repr::concreteCamera::concreteCamera(std::shared_ptr<viewEntity> _model) : model(_model) {}


void repr::concreteAnimationObserver::startAnimation(std::string newAnimation) {
    if (curAnimation != newAnimation) { // don't restart an animation if it's already busy
        model->startAnimation(newAnimation);
        curAnimation = newAnimation;
    }
}

repr::concreteAnimationObserver::concreteAnimationObserver(std::shared_ptr<viewEntity> _model) : model(_model) {
    curAnimation == "default";
}

void repr::concreteAnimationObserver::stopAnimation() {
    curAnimation == "default";
    model->startAnimation(curAnimation);
}

void repr::concreteOrientationObserver::turn(bool direction) {
    if (facingLeft != direction) {
        model->changeOrientation();
        facingLeft = direction;
    }
}

repr::concreteOrientationObserver::concreteOrientationObserver(std::shared_ptr<viewEntity> _model) : model(_model) {
    facingLeft = false;
}

repr::concreteScoreObserver::concreteScoreObserver(std::shared_ptr<view> view) : playerView(view) {
    score = 0;
    height = -450;
}

void repr::concreteScoreObserver::updateHeight(float amount) {
    height = amount;
    playerView->updateHeight(height);
}

void repr::concreteScoreObserver::updateScore(int increase) {
    score += increase;
    playerView->updateScore(score);
}

void repr::concreteScoreObserver::reset() {
    score = 0;
    height = -450;
}

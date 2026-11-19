#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
using namespace geode::prelude;

class $modify(NeuroDashMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        auto menu = CCMenu::create();
        menu->setID("neurodash-ai-menu");
        menu->setPosition({0.f, 44.f});
        menu->setZOrder(100);
        auto sprite = ButtonSprite::create("AUTO PLAY", 110, 0, 0.6f, false, "goldFont.fnt", "GJ_button_01.png", 30.f);
        auto item = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(NeuroDashMenuLayer::onAutoPlay));
        item->setID("neurodash-ai-auto-play");
        menu->addChild(item);
        this->addChild(menu);
        return true;
    }
    void onAutoPlay(CCObject*) {
        FLAlertLayer::create("NEURODASH AI", "Prototype loaded! Autonomous gameplay is not implemented yet.", "OK")->show();
    }
};

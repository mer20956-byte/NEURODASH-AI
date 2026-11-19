#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

static bool g_autoPlay = false;
static bool g_wasPressed1 = false;
static bool g_wasPressed2 = false;

class $modify(NeuroDashPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        g_wasPressed1 = false;
        g_wasPressed2 = false;
        return true;
    }

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);

        if (!g_autoPlay || !m_player1 || m_player1->m_isDead)
            return;

        // Базовое управление: удержание прыжка.
        // Пока не анализируем препятствия — это следующий этап.
        if (!m_player1->m_isDead) {
            m_player1->pushButton(PlayerButton::Jump);
            g_wasPressed1 = true;
        }

        if (m_gameState.m_isDualMode && m_player2 && !m_player2->m_isDead) {
            m_player2->pushButton(PlayerButton::Jump);
            g_wasPressed2 = true;
        }
    }
};

#include <Geode/modify/MenuLayer.hpp>

class $modify(NeuroDashMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto menu = CCMenu::create();
        menu->setID("neurodash-ai-menu");
        menu->setPosition({0.f, 44.f});
        menu->setZOrder(100);

        auto sprite = ButtonSprite::create(
            "AUTO PLAY: OFF", 120, 0, 0.6f, false,
            "goldFont.fnt", "GJ_button_01.png", 30.f
        );

        auto item = CCMenuItemSpriteExtra::create(
            sprite, this,
            menu_selector(NeuroDashMenuLayer::onAutoPlay)
        );

        item->setID("neurodash-ai-toggle");
        menu->addChild(item);
        this->addChild(menu);
        return true;
    }

    void onAutoPlay(CCObject*) {
        g_autoPlay = !g_autoPlay;

        FLAlertLayer::create(
            "NEURODASH AI",
            g_autoPlay ? "AUTO PLAY enabled." : "AUTO PLAY disabled.",
            "OK"
        )->show();
    }
};

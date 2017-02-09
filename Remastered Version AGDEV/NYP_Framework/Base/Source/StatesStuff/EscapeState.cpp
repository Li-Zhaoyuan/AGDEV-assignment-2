#include "EscapeState.h"

EscapeState::EscapeState()
{
    name_ = "ESCAPING";
    Own_ID_ = ESCAPE_ID_;
    thePlayer = nullptr;
    owner_ = nullptr;
    influenceRadius = 4;
}

EscapeState::~EscapeState()
{

}

void EscapeState::Update(double dt)
{

}

bool EscapeState::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        influenceRadius = zeEvent;
        return true;
    }
    return false;
}

bool EscapeState::onNotify(EntityBase &zeEvent)
{
    return false;
}
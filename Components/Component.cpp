#include "Component.h"

Component::Component()
{
    m_GfxInfo.x1 = m_GfxInfo.y1 = 0;
    m_GfxInfo.x2 = m_GfxInfo.y2 = 0;

    selected = false; // NEW: default is not selected
}

Component::Component(const GraphicsInfo& r_GfxInfo)
{
    m_GfxInfo = r_GfxInfo;
    selected = false; // NEW: default is not selected
}

GraphicsInfo Component::GetGraphicsInfo() const
{
    return m_GfxInfo;
}

void Component::SetGraphicsInfo(GraphicsInfo r_GFX)
{
    m_GfxInfo = r_GFX;
}

bool Component::HitTest(int x, int y)
{
    return (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 &&
        y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2);
}

void Component::Save(ofstream& OutFile)
{
    // default empty implementation
}

void Component::Load(ifstream& InFile)
{
    // default empty implementation
}

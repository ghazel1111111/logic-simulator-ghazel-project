#include "Connection.h"
#include "Gate.h"
#include <cmath>

Connection::Connection(const GraphicsInfo& r_GfxInfo,
    OutputPin* pSrcPin,
    InputPin* pDstPin)
    : Component(r_GfxInfo), SrcPin(pSrcPin), DstPin(pDstPin)
{
    // Optionally, set the connection in the pins here if needed
}
Connection::~Connection()
{
    // Detach from source output pin: find this connection in the source pin and remove it.
    if (SrcPin)
    {
        int cnt = SrcPin->GetConnectionCount();
        for (int i = 0; i < cnt; ++i)
        {
            if (SrcPin->GetConnection(i) == this)
            {
                SrcPin->RemoveConnection(i);
                break;
            }
        }
        SrcPin = nullptr;
    }

    // Detach from destination input pin: clear its stored connection pointer.
    if (DstPin)
    {
        DstPin->setConnection(nullptr);
        DstPin = nullptr;
    }
}
void Connection::setSourcePin(OutputPin* pSrcPin)
{
    SrcPin = pSrcPin;
}

OutputPin* Connection::getSourcePin()
{
    return SrcPin;
}

void Connection::setDestPin(InputPin* pDstPin)
{
    DstPin = pDstPin;
}

InputPin* Connection::getDestPin()
{
    return DstPin;
}

void Connection::Operate()
{
    // Propagate the status from the source pin to the destination pin
    if (SrcPin && DstPin)
        DstPin->setStatus((STATUS)SrcPin->getStatus());
}

void Connection::Draw(Output* pOut)
{
    if (pOut)
        pOut->DrawConnection(m_GfxInfo, selected);
}

int Connection::GetOutPinStatus()
{
    // Connection does not have an output pin, return -1
    return -1; 
}

int Connection::GetInputPinStatus(int n)
{
    // Only one input pin, ignore n
    if (DstPin)
        return DstPin->getStatus();
    return -1;
}

void Connection::setInputPinStatus(int n, STATUS s)
{
    // Only one input pin, ignore n
    if (DstPin)
        DstPin->setStatus(s);
}

void Connection::UpdatePosition()
{
    // Implement if you want to update m_GfxInfo based on pin positions
}

void Connection::Save(std::ofstream& out)
{
    out << "CONNECTION " 
        << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " "
        << m_GfxInfo.x2 << " " << m_GfxInfo.y2 << " "
        << (straight ? 1 : 0) << " "
        << (selected ? 1 : 0) << std::endl;
}

void Connection::Load(std::ifstream& in)
{
    int s = 0, sel = 0;
    if (in >> m_GfxInfo.x1 >> m_GfxInfo.y1 >> m_GfxInfo.x2 >> m_GfxInfo.y2)
    {
        if (in >> s) straight = (s != 0);
        if (in >> sel) selected = (sel != 0);
    }
}
static bool PointNearSegment(double x1, double y1, double x2, double y2, double px, double py, double tol)
{
    double vx = x2 - x1;
    double vy = y2 - y1;

    double len2 = vx * vx + vy * vy;
    if (len2 == 0.0) {
        double dx = px - x1;
        double dy = py - y1;
        return (dx * dx + dy * dy) <= tol * tol;
    }

    double t = ((px - x1) * vx + (py - y1) * vy) / len2;
    if (t < 0.0) t = 0.0;
    else if (t > 1.0) t = 1.0;

    double cx = x1 + t * vx;
    double cy = y1 + t * vy;

    double dx = px - cx;
    double dy = py - cy;
    return (dx * dx + dy * dy) <= tol * tol;
}

// HitTest: return true if (x,y) is within tolerance pixels of the connection.
// If connection is drawn as two segments (L-shape) check both segments.
bool Connection::HitTest(int x, int y)
{
    const double tolerance = 6.0; // pixels

    double x1 = static_cast<double>(m_GfxInfo.x1);
    double y1 = static_cast<double>(m_GfxInfo.y1);
    double x2 = static_cast<double>(m_GfxInfo.x2);
    double y2 = static_cast<double>(m_GfxInfo.y2);
    double px = static_cast<double>(x);
    double py = static_cast<double>(y);

    if (straight) {
        return PointNearSegment(x1, y1, x2, y2, px, py, tolerance);
    }
    else {
        // DrawConnection uses a midpoint of (x1, y2) for L-shape:
        double midX = x1;
        double midY = y2;

        // Check first segment (x1,y1) -> (midX,midY)
        if (PointNearSegment(x1, y1, midX, midY, px, py, tolerance))
            return true;

        // Check second segment (midX,midY) -> (x2,y2)
        if (PointNearSegment(midX, midY, x2, y2, px, py, tolerance))
            return true;

        return false;
    }
}
//done
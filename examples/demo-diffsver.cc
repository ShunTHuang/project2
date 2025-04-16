#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/traffic-control-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/project2-module.h"  // Will modify later

using namespace ns3;

int main(int argc, char *argv[])
{
    Time::SetResolution(Time::NS);
    LogComponentEnable("DiffServ", LOG_LEVEL_INFO);

    NS_LOG_UNCOND("Running demo-diffserv...");

    Ptr<DiffServ> diffServQueue = CreateObject<DiffServ>();

    Ptr<Packet> packet = Create<Packet>(500);  // 500 bytes

    bool enq = diffServQueue->Enqueue(packet);
    NS_LOG_UNCOND("Enqueue success? " << enq);

    Ptr<Packet> outPacket = diffServQueue->Dequeue();
    if (outPacket != nullptr) {
        NS_LOG_UNCOND("Dequeued a packet of size: " << outPacket->GetSize());
    } else {
        NS_LOG_UNCOND("No packet dequeued.");
    }

    return 0;
}
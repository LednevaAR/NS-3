#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/mobility-module.h>
#include <ns3/lte-module.h>

using namespace ns3;

int main(int argc, char *argv[])
{
	CommandLine cmd(__FILE__); 
	cmd.Parse(argc, argv);
	
	Ptr<LteHelper> LTE = CreateObject<LteHelper>();
	LTE -> SetSchedulerType("ns3::PfFfMacScheduler");
	NodeContainer eNB;
	eNB.Create(1);
	NodeContainer UE;
	UE.Create(2);

    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(eNB);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(UE);
	
	NetDeviceContainer eNBdev;
	eNBdev = LTE -> InstallEnbDevice(eNB);
	NetDeviceContainer UEdev;
	UEdev = LTE -> InstallUeDevice(UE);
	LTE -> Attach(UEdev, eNBdev.Get(0));

	enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VIDEO;
	EpsBearer Bearer(q);
	LTE -> ActivateDataRadioBearer(UEdev, Bearer);
	
	LTE -> EnableMacTraces();
	LTE -> EnableRlcTraces();

	Simulator::Run();
	Simulator::Destroy();

	return 0;
}

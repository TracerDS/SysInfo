#include "pch.hpp"
#include <SysInfo/sysinfo.hpp>
#include <SysInfo/misc.hpp>

BOOL WINAPI DllMain (
	HINSTANCE instance,
	DWORD reason,
	LPVOID reserved
) {
	// Perform actions based on the reason for calling.
	switch (reason) {
		case DLL_PROCESS_ATTACH:
			// Initialize once for each new process.
			// Return FALSE to fail DLL load.
			//SysInfo::CPU::GetCPUInfo();
			//SysInfo::Motherboard::GetMotherboardInfo();
			//SysInfo::RAM::GetRAMInfo();
			break;

		case DLL_THREAD_ATTACH:
			// Do thread-specific initialization.
			break;

		case DLL_THREAD_DETACH:
			// Do thread-specific cleanup.
			break;

		case DLL_PROCESS_DETACH:
			if (reserved) {
				break; // do not do cleanup if process termination scenario
			}

			// Perform any necessary cleanup.
			break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

int main() {
	if (true) {
		auto info = SysInfo::Motherboard::GetMotherboardInfo();
		std::string data;

		data += "Vendor: " + info.GetVendor() + "\n";
		data += "Manufacturer: " + info.GetManufacturer() + "\n";
		data += "Family: " + info.GetFamily() + "\n";
		data += "Product name: " + info.GetProductName() + "\n";
		data += "Release date: " + info.GetReleaseDate() + "\n";
		data += "BIOS version: " + info.GetBiosVersion() + "\n";
		data += "Version: " + info.GetVersion() + "\n";
		data += "SKU Number: " + info.GetSKUNumber() + "\n";
		data += "Serial: " + info.GetSerial() + "\n";
		data += "WakeUpType: " + SysInfo::Motherboard::MotherboardInfo::WakeUpTypeToString(
			info.GetWakeUpType()) + "\n";
		data += "BaseboardFlags: " + std::to_string(info.GetBaseboardFlags()) + "\n";
		data += "BaseboardType: " + SysInfo::Motherboard::MotherboardInfo::BaseboardTypeToString(
			info.GetBaseboardType()) + "\n";

		MessageBoxA(nullptr, data.c_str(), "Motherboard", 0);
	}
	if (true) {
		auto info = SysInfo::CPU::GetCPUInfo();
		
		std::string data;
		data += "ArchitectureString: " + info.GetArchitectureString() + "\n";
		data += "ProcessorTypeString: " + info.GetProcessorTypeString() + "\n";
		data += "ProcessorID: " + info.GetProcessorID() + "\n";
		data += "Cores: " + std::to_string(info.GetCores()) + "\n";
		data += "Threads: " + std::to_string(info.GetThreads()) + "\n";
		data += "ProcessorRevision: " + std::to_string(info.GetProcessorRevision()) + "\n";
		data += "ClockSpeed: " + std::to_string(info.GetClockSpeed()) + "\n";
		data += "Socket: " + info.GetSocket() + "\n";
		data += "ProcessorVendorName: " + info.GetProcessorVendorName() + "\n";
		data += "ProcessorName: " + info.GetProcessorName() + "\n";

		MessageBoxA(nullptr, data.c_str(), "CPU", 0);
	}
	if (true) {
		auto info = SysInfo::RAM::GetRAMInfo();
		int i = 0;
		for (const auto& stick : info.GetSticks()) {
			std::string data;
			data += "Name: " + stick.GetName() + "\n";
			data += "Caption: " + stick.GetCaption() + "\n";
			data += "Description: " + stick.GetDescription() + "\n";
			data += "Speed: " + std::to_string(stick.GetSpeed()) + "\n";
			data += "ClockSpeed: " + std::to_string(stick.GetClockSpeed()) + "\n";
			data += "MinVoltage: " + std::to_string(stick.GetMinVoltage()) + "\n";
			data += "ConfiguredVoltage: " + std::to_string(stick.GetConfiguredVoltage()) + "\n";
			data += "MaxVoltage: " + std::to_string(stick.GetMaxVoltage()) + "\n";
			data += "Capacity: " + std::to_string(stick.GetCapacity()) + "\n";
			data += "Manufacturer: " + stick.GetManufacturer() + "\n";
			data += "PartNumber: " + stick.GetPartNumber() + "\n";
			data += "Serial: " + stick.GetSerial() + "\n";
			data += "BankName: " + stick.GetBankName() + "\n";
			data += "DeviceLocator: " + stick.GetDeviceLocator() + "\n";

			MessageBoxA(nullptr, data.c_str(), std::string("Stick " + std::to_string(++i)).c_str(), 0);
		}
	}
}
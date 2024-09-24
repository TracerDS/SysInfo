#include "pch.hpp"
#include <SysInfo/sysinfo.hpp>
#include <SysInfo/misc.hpp>

#include <SysInfo/os.hpp>

BOOL WINAPI DllMain (
	HINSTANCE instance,
	DWORD reason,
	LPVOID reserved
) {
	switch (reason) {
		case DLL_PROCESS_ATTACH:
			// Initialize once for each new process.
			// Return FALSE to fail DLL load.

#ifdef SYSINFO_PRE_INIT
			SysInfo::CPU::GetCPUInfoFuture();
			SysInfo::RAM::GetRAMInfoFuture();
			SysInfo::Motherboard::GetMotherboardInfoFuture();
			SysInfo::Disk::GetDiskInfoFuture();
			SysInfo::OS::GetOSInfoFuture();
#endif
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
	return true;
}

int main() {
	SysInfo::OS::GetOSInfo();
	return 1;
	std::vector<std::string> diskInfo;
	if (true) {
		auto info = SysInfo::Disk::GetDiskInfo();
		for (const auto& disk : info.GetDisks()) {
			std::string data;
			data += "Letter: " + disk.GetLetter() + "\n";
			data += "VolumeName: " + disk.GetVolumeName() + "\n";
			data += "FileSystem: " + disk.GetFileSystem() + "\n";
			data += "SerialNumber: " + disk.GetSerial() + "\n";
			data += "Type: " + disk.DiskTypeToString(disk.GetType()) + "\n";
			data += "FreeBytes: " + std::to_string(disk.GetFreeBytes()) + "\n";
			data += "TotalBytes: " + std::to_string(disk.GetTotalBytes()) + "\n";
			data += "FreeBytesAvailable: " + std::to_string(disk.GetFreeBytesAvailable()) + "\n";

			diskInfo.push_back(data);
		}
	}

	std::string moboInfo;
	if (true) {
		auto info = SysInfo::Motherboard::GetMotherboardInfo();

		moboInfo += "Vendor: " + info.GetVendor() + "\n";
		moboInfo += "Manufacturer: " + info.GetManufacturer() + "\n";
		moboInfo += "Family: " + info.GetFamily() + "\n";
		moboInfo += "Product name: " + info.GetProductName() + "\n";
		moboInfo += "Release date: " + info.GetReleaseDate() + "\n";
		moboInfo += "BIOS version: " + info.GetBiosVersion() + "\n";
		moboInfo += "Version: " + info.GetVersion() + "\n";
		moboInfo += "SKU Number: " + info.GetSKUNumber() + "\n";
		moboInfo += "Serial: " + info.GetSerial() + "\n";
		moboInfo += "WakeUpType: " + SysInfo::Motherboard::MotherboardInfo::WakeUpTypeToString(
			info.GetWakeUpType()) + "\n";
		moboInfo += "BaseboardFlags: " + std::to_string(info.GetBaseboardFlags()) + "\n";
		moboInfo += "BaseboardType: " + SysInfo::Motherboard::MotherboardInfo::BaseboardTypeToString(
			info.GetBaseboardType()) + "\n";
	}
	std::string cpuInfo;
	if (true) {
		auto info = SysInfo::CPU::GetCPUInfo();
		
		cpuInfo += "ArchitectureString: " + info.GetArchitectureString() + "\n";
		cpuInfo += "ProcessorTypeString: " + info.GetProcessorTypeString() + "\n";
		cpuInfo += "ProcessorID: " + info.GetProcessorID() + "\n";
		cpuInfo += "Cores: " + std::to_string(info.GetCores()) + "\n";
		cpuInfo += "Threads: " + std::to_string(info.GetThreads()) + "\n";
		cpuInfo += "ProcessorRevision: " + std::to_string(info.GetProcessorRevision()) + "\n";
		cpuInfo += "ClockSpeed: " + std::to_string(info.GetClockSpeed()) + "\n";
		cpuInfo += "Socket: " + info.GetSocket() + "\n";
		cpuInfo += "ProcessorVendorName: " + info.GetProcessorVendorName() + "\n";
		cpuInfo += "ProcessorName: " + info.GetProcessorName() + "\n";
	}
	std::vector<std::string> ramInfo;
	if (true) {
		auto info = SysInfo::RAM::GetRAMInfo();
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

			ramInfo.push_back(data);
		}
	}

	MessageBoxA(nullptr, moboInfo.c_str(), "Motherboard", 0);
	MessageBoxA(nullptr, cpuInfo.c_str(), "CPU", 0);
	int i = 0;
	for(const auto& ram : ramInfo)
		MessageBoxA(nullptr, ram.c_str(), std::string("Stick " + std::to_string(++i)).c_str(), 0);

	i = 0;
	for (const auto& disk : diskInfo)
		MessageBoxA(nullptr, disk.c_str(), std::string("Disk " + std::to_string(++i)).c_str(), 0);
}

#include "cudaUtils.hpp"

void CudaUtils::printCudaDevices(std::ostream &outputStream) {

	int nDevices;
	char buffer[100];

	cudaGetDeviceCount(&nDevices);
	outputStream << "==== CUDA DEVICES ====" << std::endl;
	outputStream << "Found " << nDevices << " devices !" << std::endl;
	for (int i = 0; i < nDevices; i++) {
		cudaDeviceProp prop;
		cudaGetDeviceProperties(&prop, i);
		outputStream << "Device Number: " << i << std::endl;
		outputStream << "\tDevice name:                   "  << prop.name << std::endl;
		outputStream << "\tPCI Device:                    " 
			<< prop.pciBusID << ":" << prop.pciDeviceID << ":" << prop.pciDomainID << std::endl;
		outputStream << "\tMajor revision number:         " << prop.major << std::endl;
		outputStream << "\tMinor revision number:         " <<   prop.minor << std::endl;
		outputStream << "\tMemory Clock Rate :            " << prop.memoryClockRate/1000 << " MHz" << std::endl;
		outputStream << "\tMemory Bus Width:              " << prop.memoryBusWidth << " bits" << std::endl;
		outputStream << "\tPeak Memory Bandwidth:         " 
			<< 2.0*prop.memoryClockRate*(prop.memoryBusWidth/8)/1.0e6 << " GB/s" << std::endl;
		outputStream << "\tTotal global memory:           " <<   prop.totalGlobalMem/(1024*1024) << " MB" << std::endl;
		outputStream << "\tTotal shared memory per block: " <<   prop.sharedMemPerBlock/1024 << " kB" << std::endl;
		outputStream << "\tTotal registers per block:     " <<   prop.regsPerBlock/1024 << " kB" << std::endl;
		outputStream << "\tTotal constant memory:         " <<   prop.totalConstMem/1024 << " kB" << std::endl;
		outputStream << "\tMaximum memory pitch:          " <<   prop.memPitch/(1024*1024) << " MB" << std::endl;
		outputStream << "\tNumber of multiprocessors:     " <<   prop.multiProcessorCount << std::endl;
		outputStream << "\tMaximum threads per SM:        " <<   prop.maxThreadsPerMultiProcessor << std::endl;
		outputStream << "\tMaximum threads per block:     " <<   prop.maxThreadsPerBlock << std::endl;

		sprintf(buffer, "%ix%ix%i", prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
		outputStream << "\tMaximum thread block dimension " <<  buffer << std::endl;
		sprintf(buffer, "%ix%ix%i", prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
		outputStream << "\tMaximum grid dimension         " <<  buffer << std::endl;
		outputStream << "\tWarp size:                     " <<   prop.warpSize << std::endl;
		outputStream << "\tTexture alignment:             " <<   prop.textureAlignment << std::endl;
		outputStream << "\tTexture picth alignment:       " <<   prop.texturePitchAlignment << std::endl;
		outputStream << "\tSurface alignment:             " <<   prop.surfaceAlignment << std::endl;
		outputStream << "\tConcurrent copy and execution: " <<   (prop.deviceOverlap ? "Yes" : "No") << std::endl;
		outputStream << "\tKernel execution timeout:      " <<   (prop.kernelExecTimeoutEnabled ?"Yes" : "No") << std::endl;
		outputStream << "\tDevice has ECC support:        " <<   (prop.ECCEnabled ?"Yes" : "No") << std::endl;
		outputStream << "\tCompute mode:                  " 
			<<   (prop.computeMode == 0 ? "Default" : prop.computeMode == 1 ? "Exclusive" :
					prop.computeMode == 2 ? "Prohibited" : "Exlusive Process") << std::endl;
	}

	outputStream << "======================" << std::endl;
}

void CudaUtils::logCudaDevices(log4cpp::Category &log_output) {
	int nDevices;

	cudaGetDeviceCount(&nDevices);
	char buffer[100];
	log_output.debugStream() << "==== CUDA DEVICES ====";
	log_output.debugStream() << "Found " << nDevices << " devices !";
	for (int i = 0; i < nDevices; i++) {
		cudaDeviceProp prop;
		cudaGetDeviceProperties(&prop, i);
		log_output.debugStream() << "Device Number: " << i;
		log_output.debugStream() << "\tDevice name:                   "  << prop.name;
		log_output.debugStream() << "\tPCI Device:                    " 
			<< prop.pciBusID << ":" << prop.pciDeviceID << ":" << prop.pciDomainID;
		log_output.debugStream() << "\tMajor revision number:         " << prop.major;
		log_output.debugStream() << "\tMinor revision number:         " <<   prop.minor;
		log_output.debugStream() << "\tMemory Clock Rate :            " << prop.memoryClockRate/1000 << " MHz";
		log_output.debugStream() << "\tMemory Bus Width:              " << prop.memoryBusWidth << " bits";
		log_output.debugStream() << "\tPeak Memory Bandwidth:         " 
			<< 2.0*prop.memoryClockRate*(prop.memoryBusWidth/8)/1.0e6 << " GB/s";
		log_output.debugStream() << "\tTotal global memory:           " <<   prop.totalGlobalMem/(1024*1024) << " MB";
		log_output.debugStream() << "\tTotal shared memory per block: " <<   prop.sharedMemPerBlock/1024 << " kB";
		log_output.debugStream() << "\tTotal registers per block:     " <<   prop.regsPerBlock/1024 << " kB";
		log_output.debugStream() << "\tTotal constant memory:         " <<   prop.totalConstMem/1024 << " kB";
		log_output.debugStream() << "\tMaximum memory pitch:          " <<   prop.memPitch/(1024*1024) << " MB";
		log_output.debugStream() << "\tNumber of multiprocessors:     " <<   prop.multiProcessorCount;
		log_output.debugStream() << "\tMaximum threads per SM:        " <<   prop.maxThreadsPerMultiProcessor;
		log_output.debugStream() << "\tMaximum threads per block:     " <<   prop.maxThreadsPerBlock;

		sprintf(buffer, "%ix%ix%i", prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
		log_output.debugStream() << "\tMaximum thread block dimension " <<  buffer;
		sprintf(buffer, "%ix%ix%i", prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
		log_output.debugStream() << "\tMaximum grid dimension         " <<  buffer;
		log_output.debugStream() << "\tWarp size:                     " <<   prop.warpSize;
		log_output.debugStream() << "\tTexture alignment:             " <<   prop.textureAlignment;
		log_output.debugStream() << "\tTexture picth alignment:       " <<   prop.texturePitchAlignment;
		log_output.debugStream() << "\tSurface alignment:             " <<   prop.surfaceAlignment;
		log_output.debugStream() << "\tConcurrent copy and execution: " <<   (prop.deviceOverlap ? "Yes" : "No");
		log_output.debugStream() << "\tKernel execution timeout:      " <<   (prop.kernelExecTimeoutEnabled ?"Yes" : "No");
		log_output.debugStream() << "\tDevice has ECC support:        " <<   (prop.ECCEnabled ?"Yes" : "No");
		log_output.debugStream() << "\tCompute mode:                  " 
			<<   (prop.computeMode == 0 ? "Default" : prop.computeMode == 1 ? "Exclusive" :
					prop.computeMode == 2 ? "Prohibited" : "Exlusive Process");
	}

	log_output.debugStream() << "======================";
}



void gpuAssert(cudaError_t code, const std::string &file, int line, bool abort) {
	if (code != cudaSuccess) 
	{
	log4cpp::log_console->errorStream() << "GPU Assert => " << cudaGetErrorString(code) << " in file " <<  file << ":" << line << ".";
		if (abort) 
			std::cout << std::endl;
			exit(1);
	}
}

void checkKernelExecution() {
		cudaError_t error = cudaGetLastError();
		if(error != cudaSuccess)
		{
		log4cpp::log_console->errorStream() << "Kernel launch failed : " << cudaGetErrorString(error);
			std::cout << std::endl;
			exit(1);
		}
}


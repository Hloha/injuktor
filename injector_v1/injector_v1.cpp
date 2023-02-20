#include <iostream>
#include <Windows.h>

int InjectDLL(DWORD, char*);
int getDLLpath(char*);
int getPID(int*);
int getProc(HANDLE*, DWORD);

int getDLLpath(char* dll) {
	std::cout << "Please enter the path to your Dll file\n";
	std::cin >> dll;
	return 1;
}

int getPID(int* PID) {
	std::cout << "Please enter the PID to your target process\n";
	std::cin >> *PID;
	return 1;
}

int getProc(HANDLE* handleToProc, DWORD PID) {
	*handleToProc = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
	DWORD dwLastError = GetLastError();

	if (*handleToProc == NULL) {
		std::cout << "Unable to open process.\n";
		return -1;
	}
	else {
		std::cout << "Process Opened.\n";
		return 1;
	}
}

int InjectDLL(DWORD PID, char* dll) {
	HANDLE handleToProc;
	LPVOID LoadLibddr;
	LPVOID baseAddr;
	HANDLE remThread;

	int dllLength = strlen(dll) + 1;

	if (getProc(&handleToProc, PID) < 0) {
		return -1;
	}

	LoadLibddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

	if (!LoadLibddr) {
		return -1;
	}

	baseAddr = VirtualAllocEx(handleToProc, NULL, dllLength, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (!baseAddr) {
		return -1;
	}

	if (!WriteProcessMemory(handleToProc, baseAddr, dll, dllLength, NULL)) {
		return -1;
	}

	remThread = CreateRemoteThread(handleToProc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibddr, baseAddr, 0, NULL);

	if (!remThread) {
		return -1;
	}

	WaitForSingleObject(remThread, INFINITE);

	VirtualFreeEx(handleToProc, baseAddr, dllLength, MEM_RELEASE);

	if (CloseHandle(remThread) == 0) {
		std::cout << "Failed to close handle to remote thread";
		return -1;
	}

	if (CloseHandle(handleToProc) == 0) {
		std::cout << "Failed to close handle to target proceess.\n";
		return -1;
	}
}

int main() {
	int PID = -1;
	char* dll = new char[255];

	getDLLpath(dll);
	getPID(&PID);

	InjectDLL(PID, dll);
	system("pause");

	return 0;
}
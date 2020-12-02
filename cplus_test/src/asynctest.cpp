#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std::chrono;

std::string fetchDataFromDB(std::string recvData) {
	//ȷ������Ҫ5�����ִ�����
	std::this_thread::sleep_for(seconds(5));

	//���������ݿ����ӡ���ȡ���ݵ�����
	return "DB_" + recvData;
}

std::string fetchDataFromFile(std::string recvData) {
	//ȷ������Ҫ5�����ִ�����
	std::this_thread::sleep_for(seconds(5));

	//�����ȡ�ļ�����
	return "File_" + recvData;
}

int test11() {
	//��ȡ��ʼʱ��
	system_clock::time_point start = system_clock::now();

	//�����ݿ��ȡ����
	std::string dbData = fetchDataFromDB("Data");

	//���ļ���ȡ����
	std::string fileData = fetchDataFromFile("Data");

	//��ȡ����ʱ��
	auto end = system_clock::now();

	auto diff = duration_cast<std::chrono::seconds>(end - start).count();
	std::cout << "Total Time taken= " << diff << "Seconds" << std::endl;

	//��װ����
	std::string data = dbData + " :: " + fileData;

	//�����װ������
	std::cout << "Data = " << data << std::endl;

	return 0;
}
#include <winsock2.h>

#define PORT            8000    //�ڑ��Ɏg���|�[�g�ԍ��i�T�[�o�[�N���C�A���g���ʁj
#define MAX_QUEUES      5       //�ڑ��v���̍ő吔
#define MAX_BUF_SIZE    32      //���M���郁�b�Z�[�W�̍ő啶����

int main () {
	WSADATA wsaData;                //winsock����ۊ�
	struct sockaddr_in server_addr; //�T�[�o�[��ip�A�h���X�ƃ|�[�g�ԍ����i�[
	struct sockaddr_in client_addr; //�N���C�A���g��ip�A�h���X�ƃ|�[�g�ԍ����i�[
	int client_addr_len;            //�N���C�A���g���̑傫��
	SOCKET srcSocket;               //�ڑ��O�̃\�P�b�g
	SOCKET dstSocket;               //�ڑ���̃\�P�b�g

	//winsock2�̏�����
	WSAStartup (MAKEWORD (2, 0), &wsaData);

	//�\�P�b�g�̍쐬
	srcSocket = socket (AF_INET, SOCK_STREAM, 0);

	//�\�P�b�g�̐ݒ�
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons (PORT);
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind (srcSocket, (struct sockaddr*) & server_addr, sizeof (server_addr));

	//TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
	listen (srcSocket, MAX_QUEUES);

	//TCP�N���C�A���g����̐ڑ��v�����󂯕t����
	client_addr_len = sizeof (client_addr);
	dstSocket = accept (srcSocket, (struct sockaddr*) & client_addr, &client_addr_len);

	//������̑��M
	send (dstSocket, "Hello, World!!!", MAX_BUF_SIZE, 0);

	//TCP�Z�b�V�����̏I��
	closesocket (dstSocket);

	//winsock2�̏I��
	WSACleanup ();

	return 0;
}
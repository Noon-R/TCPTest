#include <stdio.h>
#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT            8000    //�ڑ��Ɏg���|�[�g�ԍ��i�T�[�o�[�N���C�A���g���ʁj
#define MAX_BUF_SIZE    32      //��M���郁�b�Z�[�W�̍ő啶����

int main () {
	WSADATA wsaData;                //winsock����ۊ�
	struct sockaddr_in server_addr; //�T�[�o�[��ip�A�h���X�ƃ|�[�g�ԍ����i�[
	SOCKET sock;                    //�N���C�A���g�̃\�P�b�g
	char buf[MAX_BUF_SIZE];         //��M�������b�Z�[�W���i�[

	//winsock2�̏�����
	WSAStartup (MAKEWORD (2, 0), &wsaData);

	//�\�P�b�g�̍쐬
	sock = socket (AF_INET, SOCK_STREAM, 0);

	//�ڑ���w��p�\���̂̏���
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons (PORT);
	InetPton (AF_INET, ("127.0.0.1"), &server_addr.sin_addr.s_addr);

	//�T�[�o�ɐڑ�
	connect (sock, (struct sockaddr*) & server_addr, sizeof (server_addr));

	//�T�[�o����f�[�^����M
	memset (buf, 0, sizeof (buf));
	recv (sock, buf, sizeof (buf), 0);

	printf ("%s\n", buf);

	//winsock2�̏I��
	WSACleanup ();

	return 0;
}
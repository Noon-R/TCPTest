#include <stdio.h>
#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT            8000    //接続に使うポート番号（サーバークライアント共通）
#define MAX_BUF_SIZE    32      //受信するメッセージの最大文字数

int main () {
	WSADATA wsaData;                //winsock情報を保管
	struct sockaddr_in server_addr; //サーバーのipアドレスとポート番号情報格納
	SOCKET sock;                    //クライアントのソケット
	char buf[MAX_BUF_SIZE];         //受信したメッセージを格納

	//winsock2の初期化
	WSAStartup (MAKEWORD (2, 0), &wsaData);

	//ソケットの作成
	sock = socket (AF_INET, SOCK_STREAM, 0);

	//接続先指定用構造体の準備
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons (PORT);
	InetPton (AF_INET, ("127.0.0.1"), &server_addr.sin_addr.s_addr);

	//サーバに接続
	connect (sock, (struct sockaddr*) & server_addr, sizeof (server_addr));

	//サーバからデータを受信
	memset (buf, 0, sizeof (buf));
	recv (sock, buf, sizeof (buf), 0);

	printf ("%s\n", buf);

	//winsock2の終了
	WSACleanup ();

	return 0;
}
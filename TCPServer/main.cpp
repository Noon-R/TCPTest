#include <winsock2.h>

#define PORT            8000    //接続に使うポート番号（サーバークライアント共通）
#define MAX_QUEUES      5       //接続要求の最大数
#define MAX_BUF_SIZE    32      //送信するメッセージの最大文字数

int main () {
	WSADATA wsaData;                //winsock情報を保管
	struct sockaddr_in server_addr; //サーバーのipアドレスとポート番号情報格納
	struct sockaddr_in client_addr; //クライアントのipアドレスとポート番号情報格納
	int client_addr_len;            //クライアント情報の大きさ
	SOCKET srcSocket;               //接続前のソケット
	SOCKET dstSocket;               //接続後のソケット

	//winsock2の初期化
	WSAStartup (MAKEWORD (2, 0), &wsaData);

	//ソケットの作成
	srcSocket = socket (AF_INET, SOCK_STREAM, 0);

	//ソケットの設定
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons (PORT);
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind (srcSocket, (struct sockaddr*) & server_addr, sizeof (server_addr));

	//TCPクライアントからの接続要求を待てる状態にする
	listen (srcSocket, MAX_QUEUES);

	//TCPクライアントからの接続要求を受け付ける
	client_addr_len = sizeof (client_addr);
	dstSocket = accept (srcSocket, (struct sockaddr*) & client_addr, &client_addr_len);

	//文字列の送信
	send (dstSocket, "Hello, World!!!", MAX_BUF_SIZE, 0);

	//TCPセッションの終了
	closesocket (dstSocket);

	//winsock2の終了
	WSACleanup ();

	return 0;
}
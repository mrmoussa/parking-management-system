#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <mysql/mysql.h>
#include "queries.h"
#define BUFSIZE 4096
extern int errno;
void error(char *msg)
{
	perror(msg);
	exit(0);
}
char username[30];
char user_password[30];
int add_park(char buffer_in[]);
int delete_park(char buffer_in[]);
int update_park(char buffer_in[]);

int add_pm(char buffer_in[]);
int delete_pm(char buffer_in[]);
int update_pm(char buffer_in[]);
int login(char buffer_in[]);

int add_car(char buffer_in[]);
int delete_car(char buffer_in[]);


int main(int argc, char *argv[])
{
	int sock, clientfd, len, clientlen, n;
	unsigned short port;
	struct sockaddr_in server, client;
	char buffer[BUFSIZE];
	pid_t cpid;

	if (argc < 2) {
		fprintf(stderr,"usage %s portnumber\n",argv[0]);
		exit(0);
	}
	port = (unsigned short) atoi(argv[1]);
	
	sock=socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		error("Opening socket");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(port);
	
	len=sizeof(server);
	if (bind(sock, (struct sockaddr *)&server, len) < 0) 
		error("[-] Binding socket failed");

	clientlen=sizeof(clientlen);
	if (listen(sock,5) < 0) 
		error("[-] Listening failed");
	while (1) {
		clientfd = accept(sock, (struct sockaddr *)&client,
				  (socklen_t *)&clientlen);
		if (clientfd < 0)
			error("[-] Acception failed");
		printf("[+] Connected from %s\n",
		       inet_ntoa((struct in_addr)client.sin_addr));
		cpid = fork();
		if (cpid == -1) {
			perror("[-] Failed to fork");
			exit(1);
		} else if (cpid == 0) {
			/* child process*/
			close(sock);
			while (1) {
				recv(clientfd, buffer, BUFSIZE-1,0);
				// buffer[n]='\0';
				// printf("Message from client is: %s\n",buffer);
				if(!strncmp("lgn", buffer, 3)){
					int id = login(buffer);
					send(clientfd, &id, sizeof(id), 0);
					puts("All users function calling");
					
					memset(buffer, 0, 1024);
					memset(username, 0, 30);
					memset(user_password, 0, 30);
				}else if(!strncmp("apk", buffer, 3)){
					int result = add_park(buffer);
					memset(buffer, 0, 1024);
					send(clientfd, &result, sizeof(result), 0);
				}else if(!strncmp("dpk", buffer, 3)){
					int result = delete_park(buffer);
					memset(buffer, 0, 1024);
					send(clientfd, &result, sizeof(result), 0);
				}else if(!strncmp("upk", buffer, 3)){
					int result = update_park(buffer);
					memset(buffer, 0, 1024);
					send(clientfd, &result, sizeof(result), 0);
				}else if(!strncmp("apm", buffer, 3)){
					int result = add_pm(buffer);
					memset(buffer, 0, 1024);
					printf("Buffer is: %s", buffer);
					send(clientfd, &result, sizeof(result), 0);
				}else if(!strncmp("dpm", buffer, 3)){
					int result = delete_pm(buffer);
					memset(buffer, 0, 1024);
					send(clientfd, &result, sizeof(result), 0);
				}else if(!strncmp("upm", buffer, 3)){
					int result = update_pm(buffer);
					memset(buffer, 0, 1024);
					send(clientfd, &result, sizeof(result), 0);
				}else if(!strncmp("acr", buffer, 3)){
					int result =add_car(buffer);
					memset(buffer, 0, 1024);
					send(clientfd, &result, sizeof(result), 0);
				}else if(!strncmp("dcr", buffer, 3)){
					int result = delete_car(buffer);
					memset(buffer, 0, 1024);
					send(clientfd, &result, sizeof(result), 0);
				}else if(!strncmp("cls", buffer, 3)){
					if (close(clientfd) < 0){
							// error("[-] Unable to close socket");}
					}
					else{
						puts("[+] Client disconnected");
					}
				}else if(!strncmp("spm", buffer, 3)){
  				printf("Socket in main:%d", clientfd);
  					char users_all[1024];
					strcpy(users_all, all_users());
					int t = strlen(users_all);
					printf("All users from server: %s\n", users_all);
					int a = send(clientfd, users_all, t, 0);
					if(a<0){
						puts("Cant send data to client");
					}
					memset(buffer, 0, 1024);
				}else{

				}
				// fflush(stdout);
				// int user_id = login(buffer);
				// send(clientfd, &user_id, sizeof(user_id), 0);
				// len = strlen(buffer);
				// for (int i = 0; i < n; i++) {
				// 	buffer[i] = toupper(buffer[i]);
				// }
				// n = send(clientfd, buffer, n, 0);
				// if (n < len)
				// 	error("Error writing");
				
			}
			if (close(clientfd) < 0)
				error("[-] Unable1 to close socket");
			exit(0);
		} else {
			close(clientfd);
		}
	} 
	return 0;
}

int login(char buffer_in[]){
	puts("Inside login function");
	printf("Login function received: %s\n", buffer_in);

	int init_size = strlen(buffer_in);
	char delim[] = "_";

	char *ptr = strtok(buffer_in, delim);
	for(int i = 0; i<3; i++){
		if(i==1){
			for(int j = 0; j<strlen(ptr); j++){
				username[j] = ptr[j];
			}
		}else if(i==2){
			for(int j = 0; j<strlen(ptr); j++){
				user_password[j] = ptr[j];
			}
		}
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	printf("Username is: %s\n", username);
	printf("Password is: %s\n", user_password);
	
	int user_id = get_user_id(username, user_password);
	printf("User id is: %d\n", user_id);

	return user_id;
}

int add_park(char buffer_in[]){
	char location[30];
	memset(location, 0, 30);
	char capacity[30];
	memset(location, 0, 30);
	puts("Add park function");
	printf("Function received: %s\n", buffer_in);

	int init_size = strlen(buffer_in);
	char delim[] = "_";

	char *ptr = strtok(buffer_in, delim);
	for(int i = 0; i<3; i++){
		if(i==1){
			for(int j = 0; j<strlen(ptr); j++){
				location[j] = ptr[j];
			}
		}else if(i==2){
			for(int j = 0; j<strlen(ptr); j++){
				capacity[j] = ptr[j];
			}
		}
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	printf("Location is: %s\n", location);
	printf("Capacity is: %s\n", capacity);
	int query_status = add_park_query(location, capacity);
	printf("Query status: %d\n", query_status);
	// int user_id = get_user_id(username, user_password);
	// printf("User id is: %d\n", user_id);s

	return query_status;
}

int delete_park(char buffer_in[]){
	char id[30];
	memset(id, 0, 30);
	
	puts("Delete park function");
	printf("Delete received: %s\n", buffer_in);

	int init_size = strlen(buffer_in);
	char delim[] = "_";

	char *ptr = strtok(buffer_in, delim);
	for(int i = 0; i<3; i++){
		if(i==1){
			for(int j = 0; j<strlen(ptr); j++){
				id[j] = ptr[j];
			}
		}
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	int delete_id = atoi(id);
	printf("ID is: %d\n", delete_id);
	int query_status = delete_park_query(delete_id);
	printf("Query status: %d\n", query_status);
	return query_status;
}

int update_park(char buffer_in[]){
	char id[30];
	char location[30];
	char capacity[30];
	memset(id, 0, 30);
	memset(location, 0, 30);
	memset(capacity, 0, 30);
	puts("Update parking");
	
	puts("Update park function");
	printf("Update data received: %s\n", buffer_in);

	int init_size = strlen(buffer_in);
	char delim[] = "_";

	char *ptr = strtok(buffer_in, delim);
	for(int i = 0; i<4; i++){
		if(i==1){
			for(int j = 0; j<strlen(ptr); j++){
				id[j] = ptr[j];
			}
		}else if(i==2){
			for(int j = 0; j<strlen(ptr); j++){
				location[j] = ptr[j];
			}
		}else if(i==3){
			for(int j = 0; j<strlen(ptr); j++){
				capacity[j] = ptr[j];
			}
		}
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	int update_id = atoi(id);
	int update_capacity = atoi(capacity);
	printf("Updated capacity: %d\n", update_capacity);
	printf("ID is: %d\n", update_id);
	int query_status = update_park_query(update_id, location, update_capacity);
	printf("Query status: %d", query_status);

	return query_status;
}

int add_pm(char buffer_in[]){
	char username_new[30];
	memset(username_new, 0, 30);
	char password_new[30];
	memset(password_new, 0, 30);
	char parking_id[2];
	memset(parking_id, 0, 30);
	puts("Add pm function");
	printf("Function received: %s\n", buffer_in);

	int init_size = strlen(buffer_in);
	char delim[] = "_";

	char *ptr = strtok(buffer_in, delim);
	for(int i = 0; i<4; i++){
		if(i==1){
			for(int j = 0; j<strlen(ptr); j++){
				username_new[j] = ptr[j];
			}
		}else if(i==2){
			for(int j = 0; j<strlen(ptr); j++){
				password_new[j] = ptr[j];
			}
		}else if(i==3){
			for(int j = 0; j<strlen(ptr); j++){
				parking_id[j] = ptr[j];
			}
		}
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	int parking_id_int = atoi(parking_id);
	int query_status = add_pm_query(username_new, password_new, parking_id_int);
	printf("Query status: %d\n", query_status);
	return query_status;
}
int delete_pm(char buffer_in[]){
	char id[30];
	memset(id, 0, 30);
	
	puts("Delete pm function");
	printf("Delete received: %s\n", buffer_in);

	int init_size = strlen(buffer_in);
	char delim[] = "_";

	char *ptr = strtok(buffer_in, delim);
	for(int i = 0; i<3; i++){
		if(i==1){
			for(int j = 0; j<strlen(ptr); j++){
				id[j] = ptr[j];
			}
		}
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	int delete_id = atoi(id);
	printf("ID is: %d\n", delete_id);
	int query_status = delete_pm_query(delete_id);
	printf("Query status: %d\n", query_status);
	return query_status;
}
int update_pm(char buffer_in[]){
	char id[30];
	char username_new[30];
	char password_new[30];
	memset(id, 0, 30);
	memset(username_new, 0, 30);
	memset(password_new, 0, 30);
	puts("Update pm");
	

	int init_size = strlen(buffer_in);
	char delim[] = "_";

	char *ptr = strtok(buffer_in, delim);
	for(int i = 0; i<4; i++){
		if(i==1){
			for(int j = 0; j<strlen(ptr); j++){
				id[j] = ptr[j];
			}
		}else if(i==2){
			for(int j = 0; j<strlen(ptr); j++){
				username_new[j] = ptr[j];
			}
		}else if(i==3){
			for(int j = 0; j<strlen(ptr); j++){
				password_new[j] = ptr[j];
			}
		}
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	int update_id = atoi(id);
	printf("ID is: %d\n", update_id);
	int query_status = update_pm_query(update_id, username_new, password_new);
	printf("Query status: %d", query_status);
	return query_status;
}
int add_car(char buffer_in[]){
	char user_id_car[30];
	memset(user_id_car, 0, 30);
	char registration[30];
	memset(registration, 0, 30);
	char time_in[10];
	memset(time_in, 0, 30);
	puts("Add car function");

	int init_size = strlen(buffer_in);
	char delim[] = "_";

	char *ptr = strtok(buffer_in, delim);
	for(int i = 0; i<4; i++){
		if(i==1){
			for(int j = 0; j<strlen(ptr); j++){
				user_id_car[j] = ptr[j];
			}
		}else if(i==2){
			for(int j = 0; j<strlen(ptr); j++){
				registration[j] = ptr[j];
			}
		}else if(i==3){
			for(int j = 0; j<strlen(ptr); j++){
				time_in[j] = ptr[j];
			}
		}
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	int user_id_car_int = atoi(user_id_car);
	int query_status = add_car_query(user_id_car_int, registration, time_in);
	printf("Query status: %d\n", query_status);
	
	return query_status; 
}

int delete_car(char buffer_in[]){
	char user_id_car[30];
	memset(user_id_car, 0, 30);
	char car_id[30];
	memset(car_id, 0, 30);
	char time_out[10];
	memset(time_out, 0, 30);
	puts("Remove car function");

	int init_size = strlen(buffer_in);
	char delim[] = "_";

	char *ptr = strtok(buffer_in, delim);
	for(int i = 0; i<3; i++){
		if(i==1){
			for(int j = 0; j<strlen(ptr); j++){
				user_id_car[j] = ptr[j];
			}
		}else if(i==2){
			for(int j = 0; j<strlen(ptr); j++){
				car_id[j] = ptr[j];
			}
		}else if(i==3){
			for(int j = 0; j<strlen(ptr); j++){
				time_out[j] = ptr[j];
			}
		}
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
	int user_id_car_int = atoi(user_id_car);
	int car_id_int = atoi(car_id);
	int query_status = delete_car_query(user_id_car_int, car_id_int);
	printf("Query status: %d\n", query_status);
	return query_status;;
}
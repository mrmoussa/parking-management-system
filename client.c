#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include "interface-init.h"
// #include <gtk/gtkx.h>

//Making the GTK widgets global


char username[30];
char user_password[30];
int user_id = -1;
int sock; 

char addLocation[30];
char addCapacity[30];

int sock;
struct sockaddr_in server;
struct hostent *hp;
unsigned short port;
gchar buffer[1024];

void error(char *msg)
{
    perror(msg);
    exit(0);
}


void wait_for_login_reply();
void wait_for_addpark_reply();
void wait_for_all_user();

int main(int argc, char *argv[])
{

 	gtk_init(&argc, &argv); // init Gtk
    
    // establish contact with xml code used to adjust widge
    // Login page
    
 	
	
    // -----------------------------------------------------------------------------------------------------
	if (argc != 3) { 
		printf("[-] Usage: %s server port\n", argv[0]);
		exit(1);
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) error("[-] Opening socket failed");
	
	server.sin_family = AF_INET;
	hp = gethostbyname(argv[1]);
	if (hp == NULL)
		error("[-] Unknown host");
	
	memcpy((char *)&server.sin_addr, *hp->h_addr_list,
		  hp->h_length);
	port = (unsigned short)atoi(argv[2]);
	server.sin_port = htons(port);
	if (connect(sock, (struct sockaddr *)&server, sizeof server) < 0)
		error("[-] Connection failed");
// ---------------------------------------------------------------------------------------------------------

 	builder = gtk_builder_new_from_file ("Project.glade");
 
	

// g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);
 
 	init_all();

	gtk_widget_show_all(window);

	gtk_main();
	if (close(sock) < 0) {
		error("[-] Unable to close socket");
	}
	printf("[+] Client terminating\n");
	

}

void	on_usernameEntry_changed(GtkEntry *e) {
	char tmp[30];
	sprintf(username, gtk_entry_get_text(e));

	sprintf(tmp, gtk_entry_get_text(e));
	}

void	on_passwordEntry_changed(GtkEntry *e) {
	char tmp[30];
	sprintf(user_password, gtk_entry_get_text(e));
	sprintf(tmp, gtk_entry_get_text(e));
	}


void on_LoginBtn_clicked(GtkButton * b){

	puts("Clicked login button\n");

	printf("Username: %s\tPassword:%s\n", username, user_password);

	char message[150];
	memset(message, 0, 150);
	strcat(message, "lgn_");
	strcat(message, username);
    strcat(message,"_");
    strcat(message, user_password);
    strcat(message,"_");
    printf("Concatenated String: %s\n", message);

	printf("sending to server\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}

	wait_for_login_reply();
}
void wait_for_login_reply(){ 
	recv(sock, &user_id, sizeof(int), 0);
	printf("[+] User id received %d\n", user_id);

	if(user_id==0){
		gtk_widget_show(AdminWindow1);
		gtk_widget_hide(window);
		// open admin panel
	}else if(user_id > 0){
		// open pm panel
		gtk_widget_show(window1);
		gtk_widget_hide(window);
	}

	//AdminFunctions

}
	//AdminFunctions
//******************ADDPM interface*********************************
void on_AddPM_clicked(GtkButton *b){
   printf("Added\n");
   gtk_widget_show(AddWindow);
   printf("ADDED\n")  ;
   gtk_label_set_text (GTK_LABEL(TestLabel), (const gchar*) "Added");
}

//Add PM

char addPMent[30];
void on_UsernameEnt_changed(GtkEntry *e){
	sprintf(addPMent, "%s", gtk_entry_get_text(e));
}

char pmParkingID[30];
void on_ParkIDEnt_changed(GtkEntry *e){
	sprintf(pmParkingID, "%s", gtk_entry_get_text(e));
}

char PMpassword[30];
void on_PasswordEnt_changed(GtkEntry *e){
	sprintf(PMpassword, "%s", gtk_entry_get_text(e));
}

void on_AddBtn_clicked(GtkButton *b){
    puts("Add PM button clicked");

	char message[150];

   	memset(message, 0, 150);
		
	strcat(message, "apm_");
	strcat(message, addPMent);
    strcat(message,"_");
    strcat(message, PMpassword);
    strcat(message,"_");
    strcat(message, pmParkingID);
    strcat(message,"_");
    printf("Concatenated String: %s\n", message);

	printf("Sending to server...\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}    
	int result;
	recv(sock, &result, sizeof(result), 0);
	if(result == 1){
		puts("[+] PM added");
		gtk_widget_hide(AddWindow);
	}else{
		puts("[-] PM not added");
		gtk_widget_hide(AddWindow);
	}
}


void on_DelPM_clicked(GtkButton *b)
{ 
   printf("Delete\n");
   gtk_widget_show(DeleteWindow); 
   gtk_label_set_text (GTK_LABEL(TestLabel), (const gchar*) "Deleted");
}

void on_UpdatePM_clicked()
{
  gtk_widget_show(UpdWindow);
  gtk_label_set_text (GTK_LABEL(TestLabel), (const gchar*) "Updated");
  gtk_widget_hide(DeleteWindow);
}

//See all PM

void on_ViewAll_clicked()
{
  gtk_widget_show(WindowPM);
  gtk_label_set_text (GTK_LABEL(TestLabel), (const gchar*) "See");

  puts("See all PM button clicked");

	char message[150];

   memset(message, 0, 150);
		
	strcat(message, "spm_");
   printf("Concatenated String: %s\n", message);

	printf("Sending to server...\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}    
	wait_for_all_user();

}

void wait_for_all_user(){
	printf("Waiting for receiving data\n");
	char users_all[4096];
	while(1){
	if(recv(sock, users_all, strlen(users_all), 0)<0){
		// puts("[-] Cant receive data from server");
	}else{
		puts("[+] Data from server received");
		break;
	}	
	}
	printf("All users are: %s\n", users_all);
}

//Delete PM

char userID[30];
void on_DelEnt_changed(GtkEntry *e){
	sprintf(userID, "%s", gtk_entry_get_text(e));
}

void on_DelBtn_clicked ()
{
	puts("Delete PM button clicked");

	char message[150];

   	memset(message, 0, 150);
		
	strcat(message, "dpm_");
	strcat(message, userID);
    strcat(message,"_");
    
    printf("Concatenated String: %s\n", message);

	printf("Sending to server...\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}    

	int result;
	recv(sock, &result, sizeof(result), 0);
	if(result == 1){
		puts("[+] PM deleted");
		gtk_widget_hide(DeleteWindow);
	}else{
		puts("[-] PM not deleted");
		gtk_widget_hide(DeleteWindow);
	}

   
}

//Update PM
char UpdUserID[30];
void on_UserEnt_changed(GtkEntry *e){
	sprintf(UpdUserID, "%s", gtk_entry_get_text(e));
}

char newUser[30];
void on_NewUserEnt_changed(GtkEntry *e){
	sprintf(newUser, "%s", gtk_entry_get_text(e));
}

char newPass[30];
void on_NewPassEnt_changed(GtkEntry *e){
	sprintf(newPass, "%s", gtk_entry_get_text(e));
}
void on_UpdBtn_clicked () 
{
	puts("Update PM button clicked");

	char message[150];

   	memset(message, 0, 150);
		
	strcat(message, "upm_");
	strcat(message, UpdUserID);
    strcat(message,"_");
    strcat(message, newUser);
    strcat(message,"_");
    strcat(message, newPass);
    strcat(message,"_");
   
    printf("Concatenated String: %s\n", message);

	printf("Sending to server...\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}    

	int result;
	recv(sock, &result, sizeof(result), 0);
	if(result == 1){
		puts("[+] PM updated");
		gtk_widget_hide(UpdWindow);
	}else{
		puts("[-] PM not updated");
		gtk_widget_hide(UpdWindow);
	}

}



//******************ADDPM interface*********************************



//***************Parking interface**********************************

//Add parking
void on_AddParking_clicked(GtkButton *b) {
   puts("Add parking");
   gtk_widget_show(AddParkingWindow);
   gtk_label_set_text (GTK_LABEL(TestLabel), (const gchar*) "Added");
   
}


void on_AddLocationEnt_changed(GtkEntry *e){
	sprintf(addLocation, gtk_entry_get_text(e));

}


void on_AddCapacityEnt_changed(GtkEntry *e){
	sprintf(addCapacity, gtk_entry_get_text(e));
}

void on_AddParkingBtn_clicked(GtkButton *b){
   puts("Button clicked");
   gtk_widget_hide(AddParkingWindow);
   printf("%s", addLocation);
   printf("Location: %s\tCapacity: %s\n", addLocation, addCapacity);

	char message[150];

   	memset(message, 0, 150);
		
	strcat(message, "apk_");
	strcat(message, addLocation);
    strcat(message,"_");
    strcat(message, addCapacity);
    strcat(message,"_");
    printf("Concatenated String: %s\n", message);

	printf("Sending to server...\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}

	wait_for_addpark_reply();
   
}

void wait_for_addpark_reply(){
	int result;
	recv(sock, &result, sizeof(int), 0);
	if(result==1){
		puts("[+] Park added");
		gtk_widget_hide(AddParkingWindow);
		// open admin panel
	}else{
		puts("[-] Park not added");
		gtk_widget_hide(AddParkingWindow);
	}
}

//Delete parking



void on_DeleteParking_clicked(GtkButton *b){
   printf("Delete\n");
   gtk_widget_show(DeleteParkingWindow);
   gtk_label_set_text (GTK_LABEL(TestLabel), (const gchar*) "Deleted");
}

char deleteParking[30];
void on_DeleteParkingEnt_changed(GtkEntry *e){
	sprintf(deleteParking, gtk_entry_get_text(e));
}

void on_DeleteParkingBtn_clicked(GtkButton *b){
	printf("ID is:%s\n", deleteParking);

	char message[150];

   	memset(message, 0, 150);
		
	strcat(message, "dpk_");
	strcat(message, deleteParking);
    strcat(message,"_");
    printf("Concatenated String: %s\n", message);

	printf("sending to server\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}

	int result;
	recv(sock, &result, sizeof(result), 0);
	if(result == 1){
		puts("[+] Park deleted");
		gtk_widget_hide(DeleteParkingWindow);
	}else{
		puts("[-] Park not deleted");
		gtk_widget_hide(DeleteParkingWindow);
	}

}

//Update Parking

void on_UpdateParking_clicked(GtkButton *b){
   printf("Update\n");
   gtk_widget_show(UpdateParkingWindow);
   gtk_label_set_text (GTK_LABEL(TestLabel), (const gchar*) "Updated");
}

char parkingID[30];
void on_ParkingIDEnt_changed(GtkEntry *e){
	sprintf(parkingID, "%s", gtk_entry_get_text(e));
}

char newLocation[30];
void on_NewLocationEnt_changed(GtkEntry *e){
	sprintf(newLocation, "%s", gtk_entry_get_text(e));
}

char newCapacity[30];
void on_NewCapacityEnt_changed(GtkEntry *e){
	sprintf(newCapacity, "%s", gtk_entry_get_text(e));
}

void on_UpdateParkingBtn_clicked(GtkButton *b) {
	char message[150];
   	memset(message, 0, 150);
		
	strcat(message, "upk_");
	strcat(message, parkingID);
    strcat(message,"_");
    strcat(message, newLocation);
    strcat(message,"_");
    strcat(message, newCapacity);
    strcat(message,"_");
    printf("Concatenated String: %s\n", message);

	printf("sending to server\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}

	int result;
	recv(sock, &result, sizeof(result), 0);
	if(result == 1){
		puts("[+] Park updated");
		gtk_widget_hide(UpdateParkingWindow);
	}else{
		puts("[-] Park not updated");
		gtk_widget_hide(UpdateParkingWindow);
	}
}

//See all parkings

void on_ViewAllParking_clicked(GtkButton *b){
   gtk_widget_show(SeeParkingWindow);
   gtk_label_set_text (GTK_LABEL(TestLabel), (const gchar*) "See all");
}

//***************Parking interface************************************

void on_SelectParking_changed(GtkWidget *c){
   
    gchar *value2;
	GtkTreeIter iter2;
	GtkTreeModel *model2;

	if (gtk_tree_selection_get_selected
		(GTK_TREE_SELECTION(c), &model2, &iter2) == FALSE)
			return;

	gtk_tree_model_get(model2, &iter2, 0, &value2,  -1);
	printf("col 0 = %s; ", value2);

	gtk_tree_model_get(model2, &iter2, 1, &value2,  -1);
	printf("col 1  = %s; ", value2);
	
	gtk_tree_model_get(model2, &iter2, 2, &value2,  -1);
	printf("col 2 = %s\n", value2);
   
}

void	on_selectPM_changed(GtkWidget *c) { 
	gchar *value1;
	GtkTreeIter iter1;
	GtkTreeModel *model1;
	if (gtk_tree_selection_get_selected
		(GTK_TREE_SELECTION(c), &model1, &iter1) == FALSE)
			return;
	gtk_tree_model_get(model1, &iter1, 0, &value1,  -1);
	printf("col 0 = %s; ", value1);
	gtk_tree_model_get(model1, &iter1, 1, &value1,  -1);
	printf("col 1  = %s\n", value1);
	gtk_tree_model_get(model1, &iter1, 2, &value1,  -1);
	printf("col 0 = %s; ", value1);
	gtk_tree_model_get(model1, &iter1, 3, &value1,  -1);
	printf("col 1  = %s\n", value1);

	}

void on_LogoutBtn_clicked(GtkButton *b){
	user_id = -1;
	gtk_widget_hide(AdminWindow1);
	gtk_widget_show(window);
   printf("aaaa");
}

//*****************************Signal functions for Parking Manager*************************

// Entry signals

//Register Car

void on_RegBtn_clicked(GtkButton *b)
{
	gtk_widget_show(RegWindow);

}

void on_RelBtn_clicked(GtkButton *b)
{
	gtk_widget_show(RelWindow);

}
void on_SeeBtn_clicked(GtkButton *b)
{
	gtk_widget_show(SeeWindow);
}


char regCar[30];
void on_RegCarEntry1_changed(GtkEntry *e){
	sprintf(regCar, "%s", gtk_entry_get_text(e));
}

char regTimein[30];
void on_RegCarEntry2_changed(GtkEntry *e){
	sprintf(regTimein, "%s", gtk_entry_get_text(e));
}


void on_RegButton_clicked(GtkButton *b)
{
	puts("Register button clicked");
	char buf[3];
   	memset(buf, 0, 150);
	snprintf(buf, sizeof(buf), "%d", user_id);
	char message[150];

   	memset(message, 0, 150);
		
	strcat(message, "acr_");
	strcat(message, buf);
	strcat(message, "_");
	strcat(message, regCar);
    strcat(message,"_");
    strcat(message, regTimein);
    strcat(message,"_");
    printf("Concatenated String: %s\n", message);

	printf("Sending to server\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}

	int result;
	recv(sock, &result, sizeof(result), 0);
	if(result == 1){
		puts("[+] Car registered");
		gtk_widget_hide(RegWindow);
	}else{
		puts("[-] Car not registeres");
		gtk_widget_hide(RegWindow);
	}
}

char relCar[30];
void on_RelCarEntry1_changed(GtkEntry *e){
	sprintf(relCar, "%s", gtk_entry_get_text(e));
}

char relTimeout[30];
void on_RelCarEntry2_changed(GtkEntry *e){
	sprintf(relTimeout, "%s", gtk_entry_get_text(e));
}

void on_RelButton_clicked(GtkButton *b)
{
	puts("Release button clicked");
	char buf[3];
   	memset(buf, 0, 150);
	snprintf(buf, sizeof(buf), "%d", user_id);
	char message[150];

   	memset(message, 0, 150);
		
	strcat(message, "dcr_");
	strcat(message, buf);
	strcat(message, "_");
	strcat(message, relCar);
	strcat(message, "_");
	strcat(message, relTimeout);
    strcat(message,"_");
    printf("Concatenated String: %s\n", message);

	printf("Sending to server\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}

	int result;
	recv(sock, &result, sizeof(result), 0);
	if(result == 1){
		puts("[+] Car released");
		gtk_widget_hide(RelWindow);
	}else{
		puts("[-] Car not released");
		gtk_widget_hide(RelWindow);
	}
}

void	on_select_changed(GtkWidget *c) { 

	gchar *value;
	GtkTreeIter iter;
	GtkTreeModel *model;

	if (gtk_tree_selection_get_selected
		(GTK_TREE_SELECTION(c), &model, &iter) == FALSE)
			return;

	gtk_tree_model_get(model, &iter, 0, &value,  -1);
	printf("col 0 = %s; ", value);
	gtk_tree_model_get(model, &iter, 1, &value,  -1);
	printf("col 1  = %s\n", value);
	gtk_tree_model_get(model, &iter, 2, &value,  -1);
	printf("col 0 = %s; ", value);
	gtk_tree_model_get(model, &iter, 3, &value,  -1);
	printf("col 1  = %s\n", value);

	}
void on_LogOutPM_clicked(){
	gtk_widget_hide(window1);
	gtk_widget_show(window);

}
void on_ExitAdmin_clicked(){
	char message[10];
	memset(message, 0, 10);
		
	strcat(message, "cls_");

	printf("Sending to server\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}
	printf("Exit clicked\n");
	printf("[+] Client terminating\n");
	gtk_widget_hide(AdminWindow1);
}
void on_Exit_clicked(){
char message[10];
	memset(message, 0, 10);
		
	strcat(message, "cls_");

	printf("Sending to server\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}
	printf("Exit clicked\n");
	printf("[+] Client terminating\n");
	gtk_widget_hide(window);
}
void on_ExitPM_clicked(){
char message[10];
	memset(message, 0, 10);
		
	strcat(message, "cls_");

	printf("Sending to server\n");
	if(send(sock , message , strlen(message) , 0 )<0){
		printf("[-] Error in sending username");
	}else{
		printf("[+] Send to server\n");
	}
	printf("Exit clicked\n");
	printf("[+] Client terminating\n");
	gtk_widget_hide(window1);
}

void	on_destroy() {
		gtk_main_quit();
		}



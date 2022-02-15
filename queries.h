

static MYSQL * conn;

static MYSQL_RES * res;
static MYSQL_ROW row;

static char * server = "localhost";
static char * user = "root";
static char * password = "root"; /* set me first */
static char * database = "users";

void connect_to_database() {
  conn = mysql_init(NULL);
  /* Connect to database */
  if (!mysql_real_connect(conn, server,
      user, password, database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  puts("[+] Connected to database");
}

void disconnect() {
  puts("[+] Disconnected from database");
  mysql_close(conn);
}

char * all_users() {
connect_to_database();
  // /* send SQL query */
  if (mysql_query(conn, "select * from users;")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  res = mysql_use_result(conn);

    static char users_a[1024];
    memset(users_a, 0, 1024);
    printf("MySQL Tables in mysql database:\n");
     while ((row = mysql_fetch_row(res)) != NULL){
       strcat(users_a, row[0]);
       strcat(users_a, "_");
       strcat(users_a, row[1]);
       strcat(users_a, "_");
       strcat(users_a, row[2]);
       strcat(users_a, "_");
     }

  printf("All users\n%s",users_a);
 
  mysql_free_result(res);
  disconnect();

  return users_a;
}

int get_user_id(char username[30], char user_password[30]) {
  connect_to_database();
  int user_id = -1;
  char sql[1000];
  sprintf(sql, "select id from users where username='%s' and password='%s';", username, user_password);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  res = mysql_use_result(conn);
  while ((row = mysql_fetch_row(res)) != NULL) {
     user_id = atoi(row[0]);

  }
  mysql_free_result(res);
  disconnect();
  return user_id;

}


int add_park_query(char location[30], char capacity[30]){
  connect_to_database();
  char sql[1000];
  sprintf(sql, "insert into park(location, capacity) values('%s', '%s');", location, capacity);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  res = mysql_use_result(conn);


  mysql_free_result(res);
  disconnect();
  return 1;
}

int delete_park_query(int delete_id){
  connect_to_database();
  char sql[1000];
  sprintf(sql, "delete from park where id='%d'", delete_id);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
    
  puts("Deleted");
  res = mysql_use_result(conn);


  mysql_free_result(res);
  disconnect();
  return 1;
}
int update_park_query(int id, char location[], int capacity){
  connect_to_database();
  char sql[1000];
  sprintf(sql, "update park set location='%s', capacity='%d' where id='%d'", location, capacity, id);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  res = mysql_use_result(conn);
  mysql_free_result(res);
  disconnect();
   
  return 1;
}

int add_pm_query(char username_new[], char password_new[], int parking_id){
  connect_to_database();
  char sql[1000];
  sprintf(sql, "insert into users(username, password, manager_in) values('%s','%s', '%d')", username_new, password_new, parking_id);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
    
  puts("Added pm");
  res = mysql_use_result(conn);


  mysql_free_result(res);
  disconnect();
   
  return 1;
}

int delete_pm_query(int delete_id){
  connect_to_database();
  char sql[1000];
  sprintf(sql, "delete from users where id='%d'", delete_id);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
    
  puts("Deleted");
  res = mysql_use_result(conn);


  mysql_free_result(res);
  disconnect();
  return 1;
}

int update_pm_query(int id, char username_new[], char password_new[]){
  connect_to_database();
  char sql[1000];
  sprintf(sql, "update users set username='%s', password='%s' where id='%d'", username_new, password_new, id);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
    
  puts("Updated");
  res = mysql_use_result(conn);


  mysql_free_result(res);
  disconnect();
   
  return 1;
}

int add_car_query(int id, char registration[], char time_in[]){
  connect_to_database();
  char sql[1000];
  sprintf(sql, "select manager_in from users where id='%d'", id);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  
  res = mysql_use_result(conn);

   int temp;   
    while ((row = mysql_fetch_row(res)) != NULL){
       temp = atoi(row[0]);
  }
  printf("User id is: %d\n", temp);
  mysql_free_result(res);

  memset(sql, 0, 1000);
  sprintf(sql, "insert into cars(park_id, reg_number, time_in) values('%d', '%s', '%s')", temp,registration, time_in);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  res = mysql_use_result(conn);

  puts("Car added");

  mysql_free_result(res);
  disconnect();
   
  return 1;
}

int delete_car_query(int user_id_car, int car_id_int){
  connect_to_database();
  char sql[1000];
  sprintf(sql, "select manager_in from users where id='%d'", user_id_car);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  
  res = mysql_use_result(conn);

   int temp;   
    while ((row = mysql_fetch_row(res)) != NULL){
       temp = atoi(row[0]);
  }
  printf("User id is: %d\n", temp);
  mysql_free_result(res);

  memset(sql, 0, 1000);
  sprintf(sql, "delete from cars where id='%d' and park_id='%d'", car_id_int, temp);
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  res = mysql_use_result(conn);

  puts("Car removed");

  mysql_free_result(res);
  disconnect();
   
  return 1;
}
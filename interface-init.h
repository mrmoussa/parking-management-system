// Window of PM
GtkWidget	*window1;
GtkWidget	*PMfixed;
GtkWidget	*RegBtn;
GtkWidget	*RelBtn;
GtkWidget	*SeeBtn;
GtkWidget	*LogOutPM;
GtkWidget	*Loclabel;
GtkWidget	*PMlabel;
GtkBuilder	*builder; 

// Exit Buttons
GtkWidget   *Exit;
GtkWidget   *ExitAdmin;
GtkWidget   *ExitPM;

// See all cars
GtkWidget		*SeeWindow;
GtkWidget		*SeeFixed;
GtkWidget		*SeeView;
GtkTreeStore		*SeeTreeStore;
GtkTreeView		*SeeTreeView;
GtkTreeViewColumn	*SCol1;
GtkTreeViewColumn	*SCol2;
GtkTreeViewColumn	*SCol3;
GtkTreeViewColumn	*SCol4;
GtkTreeSelection	*selection;
GtkCellRenderer		*sw1;
GtkCellRenderer		*sw2;
GtkCellRenderer		*sw3;
GtkCellRenderer		*sw4;
GtkBuilder		*builder; 

//Register car

GtkWidget	*RegWindow;
GtkWidget	*RegFixed;
GtkWidget	*RegisterLabel;
GtkWidget	*RegCarID;
GtkWidget	*TimeIn;
GtkWidget	*RegButton;
GtkWidget	*RegCarEntry1;
GtkWidget	*RegCarEntry2;
GtkBuilder	*builder; 

//Release Slot

GtkWidget	*RelWindow;
GtkWidget	*RelFixed;
GtkWidget	*ReleaseLabel;
GtkWidget	*RelCarID;
GtkWidget	*TimeOut;
GtkWidget	*RelButton;
GtkWidget	*RelCarEntry1;
GtkWidget	*RelCarEntry2;
GtkBuilder	*builder; 

GtkWidget	*window;
GtkWidget	*fixed;
GtkWidget	*LoginBtn;
GtkWidget	*SignupBtn;
GtkWidget	*usernameEntry;
GtkWidget	*passwordEntry;
GtkWidget	*projectTitle;
GtkWidget	*usrnmlbl;
GtkWidget	*psswdlbl;
GtkWidget 	*window1;
GtkBuilder 	*builder_pm;
GtkBuilder	*builder; 

 // Window of Admin
 //Variables
 //ADDPM column
GtkWidget *AdminWindow1;
GtkWidget *AddPM;
GtkWidget *DelPM;
GtkWidget *UpdatePM;
GtkWidget *ViewAll;
GtkWidget *AdminCon1;
//Parking column
GtkWidget *AddParking;
GtkWidget *DeleteParking;
GtkWidget *UpdateParking;
GtkWidget *ViewAllParking;
GtkWidget *AddParkingWindow;
GtkWidget *DeleteParkingWindow;
GtkWidget *UpdateParkingWindow;
GtkWidget *DeleteWindow;
GtkWidget *UpdWindow;
GtkWidget *AddWindow;

GtkLabel *TestLabel;
GtkBuilder *builder;
GtkBuilder *LogoutBtn;

//ADD Window
//Project.glade
GtkWidget *UsernameEnt;
GtkWidget *ParkIDEnt;
GtkWidget *PasswordEnt;
GtkWidget *AddBtn;
GtkWidget *AddFixed;
//Parking.glade
GtkWidget *AddLocationEnt;
GtkWidget *AddCapacityEnt;
GtkWidget *AddParkingBtn;

//Delete Window
//ADPM.glade
GtkWidget *DelFixed;
GtkWidget *DelEnt;
GtkWidget *DelBtn;
//Parking.glade
GtkWidget *DeleteParkingFixed;
GtkWidget *DeleteParkingBtn;
GtkWidget *DeleteParkingEnt;

//Update Window
//Project.glade
GtkWidget *UpdFixed;
GtkWidget *UserEnt;
GtkWidget *NewUserEnt;
GtkWidget *NewPassEnt;
GtkWidget *UpdBtn;
//Parking.glade
GtkWidget *UpdLocationEnt;
GtkWidget *NewCapacityEnt;
GtkWidget *UpdCapacityEnt;
GtkWidget *NewLocationEnt;
GtkWidget *UpdateParkingBtn;
GtkWidget *UpdateParkingFixed;

//See all parkings
GtkWidget *SeeParkingWindow;
GtkWidget *SeeParkingFixed;
GtkWidget *SeeParkingViewport;
GtkTreeStore *SeeParkingStore;
GtkTreeView *SeeParkingTree;
GtkTreeViewColumn	*ParkingID;
GtkTreeViewColumn	*LocationCol;
GtkTreeViewColumn	*CapacityCol;
GtkTreeSelection *SelectParking;
GtkCellRenderer *cr1;
GtkCellRenderer *cr2;
GtkCellRenderer *cr3;
GtkBuilder *builder;

//See all PM
GtkWidget		*WindowPM;
GtkWidget		*FixedPM;
GtkWidget		*ViewPM;
GtkTreeStore		*treePM;
GtkTreeView		*TreeViewPM;
GtkTreeViewColumn	*Column1;
GtkTreeViewColumn	*Column2;
GtkTreeViewColumn	*Column3;
GtkTreeViewColumn	*Column4;
GtkTreeSelection	*selectPM;
GtkCellRenderer		*sa1;
GtkCellRenderer		*sa2;
GtkCellRenderer		*sa3;
GtkCellRenderer		*sa4;
GtkBuilder		*builder; 

void init_all()
{
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    LoginBtn = GTK_WIDGET(gtk_builder_get_object(builder, "LoginBtn"));
    SignupBtn = GTK_WIDGET(gtk_builder_get_object(builder, "SignupBtn"));
    projectTitle = GTK_WIDGET(gtk_builder_get_object(builder, "projectTitle"));
    usernameEntry = GTK_WIDGET(gtk_builder_get_object(builder, "usernameEntry"));
    passwordEntry = GTK_WIDGET(gtk_builder_get_object(builder, "passwordEntry"));
    usrnmlbl = GTK_WIDGET(gtk_builder_get_object(builder, "usrnmlbl"));
    psswdlbl = GTK_WIDGET(gtk_builder_get_object(builder, "psswdlbl"));

// ---------------------------------------------------------------------------------------------------------
    window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    PMfixed = GTK_WIDGET(gtk_builder_get_object(builder, "PMfixed"));
    RegBtn = GTK_WIDGET(gtk_builder_get_object(builder, "RegBtn"));
    RelBtn = GTK_WIDGET(gtk_builder_get_object(builder, "RelBtn"));
    SeeBtn = GTK_WIDGET(gtk_builder_get_object(builder, "SeeBtn"));
    Loclabel = GTK_WIDGET(gtk_builder_get_object(builder, "Loclabel"));
    PMlabel = GTK_WIDGET(gtk_builder_get_object(builder, "PMlabel"));
    LogOutPM = GTK_WIDGET(gtk_builder_get_object(builder, "LogOutPM"));
    //SeeMain
    SeeWindow = GTK_WIDGET(gtk_builder_get_object(builder, "SeeWindow"));
    SeeFixed = GTK_WIDGET(gtk_builder_get_object(builder, "SeeFixed"));
    SeeView = GTK_WIDGET(gtk_builder_get_object(builder, "SeeView"));
    SeeTreeStore = GTK_TREE_STORE(gtk_builder_get_object(builder, "SeeTreeStore"));
    SeeTreeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "SeeTreeView"));
    SCol1   = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "SCol1")); // col 1
    SCol2   = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "SCol2")); // col 2
    SCol3   = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "SCol3")); // col 1
    SCol4   = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "SCol4")); // col 2
    sw1 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "sw1")); // col 1 ren
    sw2 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "sw2")); // col 2 ren
    sw3 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "sw3")); // col 1 ren
    sw4 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "sw4")); // col 2 ren
    selection = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "selection")); // tree view selection

    gtk_tree_view_column_add_attribute(SCol1, sw1, "text", 0); // attach the renderer to the column
    gtk_tree_view_column_add_attribute(SCol2, sw2, "text", 1); // attach the renderer to the column
    gtk_tree_view_column_add_attribute(SCol3, sw3, "text", 2); // attach the renderer to the column
    gtk_tree_view_column_add_attribute(SCol4, sw4, "text", 3); // attach the renderer to the column



    GtkTreeIter iter;    // iterators


    gtk_tree_store_append (SeeTreeStore, &iter, NULL);
    gtk_tree_store_set(SeeTreeStore, &iter, 0, "in process", -1);
    gtk_tree_store_set(SeeTreeStore, &iter, 1, "in process", -1);
    gtk_tree_store_set(SeeTreeStore, &iter, 2, "in process", -1);
    gtk_tree_store_set(SeeTreeStore, &iter, 3, "in process", -1);


    gtk_tree_store_append (SeeTreeStore, &iter, NULL);
    gtk_tree_store_set(SeeTreeStore, &iter, 0, "in process", -1);
    gtk_tree_store_set(SeeTreeStore, &iter, 1, "in process", -1);
    gtk_tree_store_set(SeeTreeStore, &iter, 2, "in process", -1);
    gtk_tree_store_set(SeeTreeStore, &iter, 3, "in process", -1);



    // selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(SeeTreeView));

    //Reg Main
    RegWindow = GTK_WIDGET(gtk_builder_get_object(builder, "RegWindow"));
    RegFixed = GTK_WIDGET(gtk_builder_get_object(builder, "RegFixed"));
    RegisterLabel = GTK_WIDGET(gtk_builder_get_object(builder, "ReleaseLabel"));
    RegCarID = GTK_WIDGET(gtk_builder_get_object(builder, "RegCarID"));
    TimeIn = GTK_WIDGET(gtk_builder_get_object(builder, "TimeIn"));
    RegButton = GTK_WIDGET(gtk_builder_get_object(builder, "RegButton"));
    RegCarEntry1 = GTK_WIDGET(gtk_builder_get_object(builder, "RegCarEntry1"));
    RegCarEntry2 = GTK_WIDGET(gtk_builder_get_object(builder, "RegCarEntry2"));

    //Rel Main
    RelWindow = GTK_WIDGET(gtk_builder_get_object(builder, "RelWindow"));
    RelFixed = GTK_WIDGET(gtk_builder_get_object(builder, "RelFixed"));
    ReleaseLabel = GTK_WIDGET(gtk_builder_get_object(builder, "ReleaseLabel"));
    RelCarID = GTK_WIDGET(gtk_builder_get_object(builder, "RelCarID"));
    TimeOut = GTK_WIDGET(gtk_builder_get_object(builder, "TimeOut"));
    RelButton = GTK_WIDGET(gtk_builder_get_object(builder, "RelButton"));
    RelCarEntry1 = GTK_WIDGET(gtk_builder_get_object(builder, "RelCarEntry1"));
    RelCarEntry2 = GTK_WIDGET(gtk_builder_get_object(builder, "RelCarEntry2"));

    //Exit Buttons
    Exit = GTK_WIDGET(gtk_builder_get_object(builder, "Exit"));
    ExitPM = GTK_WIDGET(gtk_builder_get_object(builder, "ExitPM"));
    ExitAdmin = GTK_WIDGET(gtk_builder_get_object(builder, "ExitAdmin"));
//--------------------------------------------------------------------------------------------------
      //MainWindow
   //ADDPM column
   AdminWindow1 = GTK_WIDGET(gtk_builder_get_object(builder,"AdminWindow1"));
   TestLabel = GTK_LABEL(gtk_builder_get_object(builder,"TestLabel"));
   AddPM = GTK_WIDGET(gtk_builder_get_object(builder,"AddPM"));
   DelPM = GTK_WIDGET(gtk_builder_get_object(builder,"DelPM"));
   UpdatePM = GTK_WIDGET(gtk_builder_get_object(builder,"UpdatePM"));
   ViewAll = GTK_WIDGET(gtk_builder_get_object(builder,"ViewAll"));
   AddWindow = GTK_WIDGET(gtk_builder_get_object(builder, "AddWindow"));
   //Parking column
   AddParking = GTK_WIDGET(gtk_builder_get_object(builder,"AddParking"));
   DeleteParking = GTK_WIDGET(gtk_builder_get_object(builder,"DeleteParking"));
   UpdateParking = GTK_WIDGET(gtk_builder_get_object(builder,"UpdateParking"));
   ViewAllParking = GTK_WIDGET(gtk_builder_get_object(builder,"ViewAllParking"));
   AdminCon1 = GTK_WIDGET(gtk_builder_get_object(builder, "AdminCon1"));
   
       //window for adding ---> Parking Managers
       UsernameEnt = GTK_WIDGET(gtk_builder_get_object(builder, "UsernameEnt"));
   ParkIDEnt = GTK_WIDGET(gtk_builder_get_object(builder, "ParkIDEnt"));
   PasswordEnt = GTK_WIDGET(gtk_builder_get_object(builder, "PasswordEnt"));
   AddBtn = GTK_WIDGET(gtk_builder_get_object(builder, "AddBtn"));
   AddFixed = GTK_WIDGET(gtk_builder_get_object(builder, "AddFixed"));
   //window for adding ---> Parking
   AddLocationEnt = GTK_WIDGET(gtk_builder_get_object(builder, "AddLocationEnt"));
   AddCapacityEnt = GTK_WIDGET(gtk_builder_get_object(builder, "AddCapacityEnt"));
   AddParkingBtn = GTK_WIDGET(gtk_builder_get_object(builder, "AddParkingBtn"));
   AddParkingWindow = GTK_WIDGET(gtk_builder_get_object(builder, "AddParkingWindow"));



   //Window for deleting ---> Parking Managers
   DeleteWindow = GTK_WIDGET(gtk_builder_get_object(builder, "DeleteWindow"));
   DelFixed = GTK_WIDGET(gtk_builder_get_object(builder, "DelFixed"));
   DelEnt = GTK_WIDGET(gtk_builder_get_object(builder, "DelEnt"));
   DelBtn = GTK_WIDGET(gtk_builder_get_object(builder, "DelBtn"));
   //Window for deleting ---> Parkings
   DeleteParkingFixed = GTK_WIDGET(gtk_builder_get_object(builder, "DeleteParkingFixed")); 
   DeleteParkingWindow = GTK_WIDGET(gtk_builder_get_object(builder, "DeleteParkingWindow"));
   DeleteParkingBtn = GTK_WIDGET(gtk_builder_get_object(builder, "DeleteParkingBtn"));
   DeleteParkingEnt = GTK_WIDGET(gtk_builder_get_object(builder, "DeleteParkingEnt"));

   //Window for updating ---> Parking Managers
   UpdWindow = GTK_WIDGET(gtk_builder_get_object(builder, "UpdWindow"));
   UpdFixed = GTK_WIDGET(gtk_builder_get_object(builder, "UpdFixed"));
   UserEnt = GTK_WIDGET(gtk_builder_get_object(builder, "UserEnt"));
   NewUserEnt = GTK_WIDGET(gtk_builder_get_object(builder, "NewUserEnt"));
   NewPassEnt = GTK_WIDGET(gtk_builder_get_object(builder, "NewPassEnt"));
   UpdBtn = GTK_WIDGET(gtk_builder_get_object(builder, "UpdBtn"));
   //Window for updating ---> Parkings
   UpdateParkingWindow = GTK_WIDGET(gtk_builder_get_object(builder, "UpdateParkingWindow"));
   UpdateParkingFixed = GTK_WIDGET(gtk_builder_get_object(builder, "UpdateParkingFixed"));
   UpdLocationEnt = GTK_WIDGET(gtk_builder_get_object(builder, "UpdLocationEnt"));
   NewCapacityEnt = GTK_WIDGET(gtk_builder_get_object(builder, "NewCapacityEnt"));
   UpdCapacityEnt = GTK_WIDGET(gtk_builder_get_object(builder, "UpdCapacityEnt"));
   NewLocationEnt = GTK_WIDGET(gtk_builder_get_object(builder, "NewLocationEnt"));
   UpdateParkingBtn = GTK_WIDGET(gtk_builder_get_object(builder, "UpdateParkingBtn"));

   //Window for seeing all ---> PM
   WindowPM = GTK_WIDGET(gtk_builder_get_object(builder, "WindowPM"));
   FixedPM = GTK_WIDGET(gtk_builder_get_object(builder, "FixedPM"));
    ViewPM  = GTK_WIDGET(gtk_builder_get_object(builder, "ViewPM"));
    treePM = GTK_TREE_STORE(gtk_builder_get_object(builder, "treePM"));
    TreeViewPM  = GTK_TREE_VIEW(gtk_builder_get_object(builder, "TreeViewPM"));
    Column1 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "Column1")); // col 1
    Column2 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "Column2")); // col 2
    Column3 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "Column3")); // col 1
    Column4 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "Column4")); // col 2
    sa1 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "sa1")); // col 1 ren
    sa2 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "sa2")); // col 2 ren
    sa3 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "sa3")); // col 1 ren
    sa4 = GTK_CELL_RENDERER
    (gtk_builder_get_object(builder, "sa4")); // col 2 ren
    selectPM = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "selectPM")); // tree view selection

   gtk_tree_view_column_add_attribute(Column1, sa1, "text", 0); // attach the renderer to the column
    gtk_tree_view_column_add_attribute(Column2, sa2, "text", 1); // attach the renderer to the column
    gtk_tree_view_column_add_attribute(Column3, sa3, "text", 2); // attach the renderer to the column
    gtk_tree_view_column_add_attribute(Column4, sa4, "text", 3); // attach the renderer to the column

    GtkTreeIter iter1;
    gtk_tree_store_append (treePM, &iter1, NULL);
    gtk_tree_store_set(treePM, &iter1, 0, "in process", -1);
    gtk_tree_store_set(treePM, &iter1, 1, "in process", -1);
    gtk_tree_store_set(treePM, &iter1, 2, "in process", -1);
    gtk_tree_store_set(treePM, &iter1, 3, "in process", -1);


    gtk_tree_store_append (treePM, &iter1, NULL);
    gtk_tree_store_set(treePM, &iter1, 0, "in process", -1);
    gtk_tree_store_set(treePM, &iter1, 1, "in process", -1);
    gtk_tree_store_set(treePM, &iter1, 2, "in process", -1);
    gtk_tree_store_set(treePM, &iter1, 3, "in process", -1);

    gtk_tree_store_append (treePM, &iter1, NULL);
    gtk_tree_store_set(treePM, &iter1, 0, "in process", -1);
    gtk_tree_store_set(treePM, &iter1, 1, "in process", -1);
    gtk_tree_store_set(treePM, &iter1, 2, "in process", -1);
    gtk_tree_store_set(treePM, &iter1, 3, "in process", -1);


   selectPM = gtk_tree_view_get_selection(GTK_TREE_VIEW(TreeViewPM));


   //Window for seeing all ---> Parkings
   SeeParkingWindow = GTK_WIDGET(gtk_builder_get_object(builder, "SeeParkingWindow"));
   SeeParkingFixed = GTK_WIDGET(gtk_builder_get_object(builder, "SeeParkingFixed"));
   SeeParkingViewport = GTK_WIDGET(gtk_builder_get_object(builder, "SeeParkingViewport"));
   SeeParkingStore = GTK_TREE_STORE(gtk_builder_get_object(builder, "SeeParkingStore"));
   SeeParkingTree   = GTK_TREE_VIEW(gtk_builder_get_object(builder, "SeeParkingTree"));
   ParkingID = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "ParkingID")); // col 1
    LocationCol = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "LocationCol")); // col 2
    CapacityCol = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "CapacityCol")); // col 1
   cr1 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr1")); // col 1 ren
    cr2 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr2")); // col 2 ren
    cr3 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr3")); // col 3 ren
   SelectParking = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "SelectParking"));
   
   gtk_tree_view_column_add_attribute(ParkingID, cr1, "text", 0); // attach the renderer to the column
    gtk_tree_view_column_add_attribute(LocationCol, cr2, "text", 1); // attach the renderer to the column
    gtk_tree_view_column_add_attribute(CapacityCol, cr3, "text", 2); // attach the renderer to the column

   char ParkingID[10], LocationCol[1024], CapacityCol[1024];
   GtkTreeIter iter2;    // iterators

   gtk_tree_store_append (SeeParkingStore, &iter2, NULL);
    gtk_tree_store_set(SeeParkingStore, &iter2, 0, "in process", -1);
    gtk_tree_store_set(SeeParkingStore, &iter2, 1, "in process", -1);
    gtk_tree_store_set(SeeParkingStore, &iter2, 2, "in process", -1);

   gtk_tree_store_append (SeeParkingStore, &iter2, NULL);
    gtk_tree_store_set(SeeParkingStore, &iter2, 0, "in process", -1);
    gtk_tree_store_set(SeeParkingStore, &iter2, 1, "in process", -1);
    gtk_tree_store_set(SeeParkingStore, &iter2, 2, "in process", -1);

   SelectParking = gtk_tree_view_get_selection(GTK_TREE_VIEW(SeeParkingTree));
    gtk_builder_connect_signals(builder, NULL);
}